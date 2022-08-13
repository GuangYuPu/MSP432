/****************************************************/
// MSP432P401R
// 配置Keil独立空工程 (已将ti固件库打包至工程)
// Keil工程已配置开启FPU
// Bilibili：m-RNA
// E-mail:m-RNA@qq.com
// 创建日期:2021/9/28
/****************************************************/

#include "sysinit.h"
#include "usart.h"
#include "delay.h"
#include "led.h"
#include "tim32.h"

//usercode:include(begin)
#include "key.h"
#include "key4x4.h"
#include "oled.h"
#include "timA.h"
#include "adc.h"
#include "usercode_driver.h"
//usercode:include(end)

//usercode:pv(begin)
int flag = 0;
int key_id = 0;
uint8_t* title = "OLED";
uint8_t* number_1 = "Key number:";
uint8_t* number_2 = "ADC1:";
uint8_t* number_3 = "ADC2:";
uint8_t* mv = "(mv)";

volatile uint_fast16_t  duty1 = 500;
volatile uint_fast16_t  duty2 = 333;
volatile uint_fast16_t  duty3 = 750;

uint16_t Counter_sine1 = 0;		//A相
uint16_t Counter_sine2 = 83;	//滞后A相120度
uint16_t Counter_sine3 = 166;	//超前A相120度

uint32_t adc1_value = 0;
uint32_t adc2_value = 0;
//usercode:pv(end)

int main(void)
{
    SysInit();         // 第3讲 时钟配置
    uart_init(115200); // 第7讲 串口配置
    delay_init();      // 第4讲 滴答延时

    /*开始填充初始化代码*/
	KEY_Init(0);
	LED_Init();
	KEY4x4_Init();	
	OLED_Init();
	ADC_Config();
	TimA0_Int_Init(1000,TIMER_A_CLOCKSOURCE_DIVIDER_48);
	TimA1_PWM_Init(1000,TIMER_A_CLOCKSOURCE_DIVIDER_48);
	/*svpwm init*/
	Counter_sine1 = (uint16_t)(((float)0)*T_sine/250.f);
	Counter_sine2 = (uint16_t)(((float)83)*T_sine/250.f);
	Counter_sine3 = (uint16_t)(((float)166)*T_sine/250.f);

    /*停止填充初始化代码*/

    // printf("Hello,MSP432!\r\n");
    MAP_Interrupt_enableMaster(); // 开启总中断

    while (1)
    {
        /*开始填充用户代码*/

		/* --------check the keyboard--------- */
        key_id = KEY4x4_Scan(1);

		
		
        /*停止填充用户代码*/
		delay_ms(1);
    }
}

//user ISR begin
void TA0_0_IRQHandler(void)
{
	Timer_A_clearCaptureCompareInterrupt(TIMER_A0_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_0);
	/*timer_a0 定时器中断 1ms*/
	flag++;
	if(flag%1000 == 0)
	{
	/*间隔1s进入一次，检测单片机运行状态*/
		LED_RED_Tog();
		flag = 0;
	}
	if(flag%150 == 0)
	{
	/*间隔150ms进入一次，向oled打印*/
	/* --------print on oled----------- */
		//title:
		OLED_ShowString(9*16,0,title,8);
		//1st number:
		OLED_ShowString(0,1,number_1,8);
		OLED_ShowNum(12*16,1,key_id,5,8);
		//2nd number:
		OLED_ShowString(0,2,number_2,8);
		OLED_ShowNum(6*6,2,adc1_value,5,8);
		OLED_ShowString(12*6,2,mv,8);
		//3rd number:
		OLED_ShowString(0,3,number_3,8);
		OLED_ShowNum(6*6,3,adc2_value,5,8);
		OLED_ShowString(12*6,3,mv,8);
		//4th number:
	}

	/* -----spwm----- */
	if(Counter_sine1>=T_sine)
	{
		Counter_sine1 = 0;
	}
	if(Counter_sine2>=T_sine)
	{
		Counter_sine2 = 0;
	}
	if(Counter_sine3>=T_sine)
	{
		Counter_sine3 = 0;
	}
	duty1 = (uint_fast16_t)(sine_tabel[(uint16_t)(((float)Counter_sine1)*250.f/T_sine)]*MODULAT);
	Counter_sine1++;
	duty2 = (uint_fast16_t)(sine_tabel[(uint16_t)(((float)Counter_sine1)*250.f/T_sine)]*MODULAT);
	Counter_sine2++;
	duty3 = (uint_fast16_t)(sine_tabel[(uint16_t)(((float)Counter_sine1)*250.f/T_sine)]*MODULAT);
	Counter_sine3++;

	/* -------change the duty of the pwm------- */
		// p7.7
		Timer_A_setCompareValue(TIMER_A1_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_1,duty1);
		// p7.6
		Timer_A_setCompareValue(TIMER_A1_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_2,duty2);
		// p7.5
		Timer_A_setCompareValue(TIMER_A1_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_3,duty3);

	/* -----pid----- */
	adc1_value = (uint32_t)(resultsBuffer[0]*1000*3.242/16383);
	adc2_value = (uint32_t)(resultsBuffer[1]*1000*3.242/16383);
	

}
//user ISR end
