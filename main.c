#include "MemMap.h"
#include "StdTypes.h"

#include "MCAL/DIO_int.h"
#include "MCAL/DIO_private.h"

#include "LCD_int.h"
#include "Keypad_int.h"

#define  F_CPU 16000000
#include "util/delay.h"

#include "Timers.h"

#include "Timers_Services.h"


#include "Sensor_DHT22_int.h"

u8 x, str[20] ,SETFLAG=0;



int main(void)
{
	
	DIO_Init();
	LCD_Init();
	KEYPAD_Init();
	UART_Init();
	
	 	Timer1_Init(TIMER1_FASTPWM_OCRA_TOP_MODE,TIMER1_SCALER_8);
	 	Timer1_OCRB1Mode(OCRB_NON_INVERTING);
	 	OCR1A=39999;
	 	TCNT1=0;
	GLOBAL_ENABLE();

	 	DHT_SensorINT();
	while (1)
	{
		
		
		if(SETFLAG){
			CarRunnable_Tasks(str);
			SETFLAG=0;
		}
		
				DHT_SensorRunnable();
	     		_delay_ms(10);
		 		LCD_SetCursor(line_1,0);
		 		LCD_WriteString((u8*)"T=");
		 		LCD_WriteNumber(DHT_Tempgetter());
		 		LCD_SetCursor(line_2 , 0);
		 		LCD_WriteString((u8*)"H=");
		 		LCD_WriteNumber(DHT_Humiditygetter());
		 	    LCD_SetCursor(line_1 , 8);
		 		LCD_WriteString((u8*)"S=");
		 		LCD_WriteNumber(DHT_CRCSumgetter());
		 		if(DHT_CheckSum()==DHT_CRCSumgetter()){
		 			LCD_SetCursor(line_2,8);
		 			LCD_WriteString((u8*)"Ch=");
		 			LCD_WriteNumber(DHT_CheckSum());
		 		}
		 		_delay_ms(1000);
		


	}
}

