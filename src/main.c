/*****************************************************************************
 * ADuCM3029_ADXL372_demo.c
 *****************************************************************************/
#include <sys/platform.h>
#include "adi_initialize.h"
#include "Communication.h"
#include "adsap_proto.h"
#include "Timer.h"
#include <drivers/gpio/adi_gpio.h>
#include <drivers/xint/adi_xint.h>
#include <common/adi_error_handling.h>
#include <common/adi_timestamp.h>
#include "adxl372.h"

//#define FIFO_READ
#define ADXL372_DEBUG

/*LCD backlight pin*/
#define BLLCD_PORT ADI_GPIO_PORT1
#define BLLCD_PIN  ADI_GPIO_PIN_12

/*DS3/DS4 led pin*/
#define DS3_PORT ADI_GPIO_PORT2
#define DS3_PIN  ADI_GPIO_PIN_0
#define DS4_PORT ADI_GPIO_PORT1
#define DS4_PIN  ADI_GPIO_PIN_15

#define PERIPHERAL_ADV_MODE      ((ADI_BLE_GAP_MODE)(ADI_BLE_GAP_MODE_NOTCONNECTABLE |  \
			                             ADI_BLE_GAP_MODE_DISCOVERABLE))

#define GENERIC_SENSOR_TYPE 0
#define CURRENT_DATE_TIME 1495715651 //25 May 2017 12:34 PM

uint8_t gpioMemory[ADI_GPIO_MEMORY_SIZE];
uint8_t xintMemory[ADI_XINT_MEMORY_SIZE];
uint8_t FIFO_Buf1[1024] = {0};
uint8_t ui8Status2, ui8Status;
bool boInterruptFlag = false;
uint32_t LowPwrExitFlag;

/*
 * GPIO event Callback function
 */
static void pinIntCallback(void* pCBParam, uint32_t Port,  void* PinIntData)
{
	boInterruptFlag = true;
	LowPwrExitFlag++;
}


int main(int argc, char *argv[])
{
	ADSENSORAPP_RESULT_TYPE enResult;
	uint32_t u32RTCTime;
	int16_t data;
	float f[520];


	timer_start(); // Start timer

	/**
	 * Initialize managed drivers and/or services that have been added to 
	 * the project.
	 * @return zero on success 
	 */
	adi_initComponents();
	adi_initpinmux();

	adsAPI_Init_Devices();

	/* Initialize UART at 9600 baudrate */
	UART_Init();
	AppPrintf("UART IOT drivers test\n\r");

	/*Initialize RTC*/
	adi_RTCInit();

	/* Initialize ADXL372 accelerometer */
	//ADXL372_Init();

	/*Verify the interface between ADICUP3029 and ADXL372*/
	enResult = Detect_ADXL372_Sensor();

	if (enResult != ADI_ADS_API_SUCCESS)
	{
		AppPrintf("Error communicating to ADXL372\n\r");
	}

	/* Set interrupt pin */
	adi_gpio_Init(gpioMemory, ADI_GPIO_MEMORY_SIZE); //initialize gpio
	adi_gpio_OutputEnable(INTACC_PORT, INTACC_PIN, false);
	adi_gpio_InputEnable(INTACC_PORT, INTACC_PIN, true);    // Set INTACC_PORT as input
	adi_gpio_PullUpEnable(INTACC_PORT, INTACC_PIN, false); 	// Disable pull-up resistors
//	adi_gpio_SetGroupInterruptPolarity(INTACC_PORT, INTACC_PIN);
//	adi_gpio_SetGroupInterruptPins(INTACC_PORT,  SYS_GPIO_INTA_IRQn, INTACC_PIN);
//	adi_gpio_RegisterCallback (SYS_GPIO_INTA_IRQn, pinIntCallback, NULL );


	adi_xint_Init(xintMemory, ADI_XINT_MEMORY_SIZE);
	adi_xint_EnableIRQ(ADI_XINT_EVENT_INT0, ADI_XINT_IRQ_RISING_EDGE);
	adi_xint_RegisterCallback (ADI_XINT_EVENT_INT0, pinIntCallback, NULL);

	/* Turn off LCD backlight */
//	adi_gpio_OutputEnable(BLLCD_PORT, BLLCD_PIN, true);
//	adi_gpio_SetLow(BLLCD_PORT, BLLCD_PIN);

	/*Turn off leds DS3 and DS4*/
	adi_gpio_OutputEnable(DS3_PORT, DS3_PIN, true);
	adi_gpio_SetLow(DS3_PORT, DS3_PIN);
	adi_gpio_OutputEnable(DS4_PORT, DS4_PIN, true);
	adi_gpio_SetLow(DS4_PORT, DS4_PIN);

	/* Set impact detection mode */
	ADXL372_Set_Impact_Detection();

//	ADI_BLER_CONN_INFO connInfo = {0};
//	ADI_BLER_EVENT BleEvent;
	while(1)
	{
		if (boInterruptFlag) {
			/*Clear interrupt on ADXL and reenter instant-on mode*/
			adxl372_Get_Status_Register(&ui8Status);
			adxl372_Get_ActivityStatus_Register(&ui8Status2);


			ADI_SPI_TRANSCEIVER sTransceive;
			ADI_SPI_RESULT      eSpiResult;
			uint8_t             aTxBuffer[1] = {(uint8_t)((ADI_ADXL372_FIFO_DATA << 1) | 1)};
			extern ADI_SPI_HANDLE hSPI0MasterDev;

			ASSERT(pBuffer != NULL);

			sTransceive.TransmitterBytes = 1u;
			sTransceive.ReceiverBytes    = 1024;
			sTransceive.nTxIncrement     = 1u;
			sTransceive.nRxIncrement     = 1u;
			sTransceive.bRD_CTL          = true;
			sTransceive.bDMA             = false;
			sTransceive.pTransmitter     = aTxBuffer;
			sTransceive.pReceiver        = FIFO_Buf1;

			timer_sleep(15);
			eSpiResult = adi_spi_MasterReadWrite(hSPI0MasterDev, &sTransceive);


			for(int i = 0; i < 508; i++)
			{
				data = (int16_t)((((int16_t)FIFO_Buf1[(2*i)] << 8 ) | (int16_t)FIFO_Buf1[(2*i)+1]) >> 4);

				if((FIFO_Buf1[(2*i)] & 0x80) == 0x80)
					data |= 0xF000;
				else
					data &= 0x0FFF;
				f[i] = (float)data*100/1000;
			}

			for(int i=0; i<505; i+=3)
			{
				AppPrintf(",%5.2f,%5.2f,%5.2f\n\r",(float)f[i],(float)f[i+1],(float)f[i+2]);
			}


			adxl372_Set_Op_mode(INSTANT_ON);
			boInterruptFlag = false;
			LowPwrExitFlag = 0;
		}

		/* Enter Flexi mode - low power */
		adi_pwr_EnterLowPowerMode ( ADI_PWR_MODE_FLEXI, &LowPwrExitFlag, 0u);
	}
}
