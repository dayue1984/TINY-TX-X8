#ifndef _LED_H_
#define _LED_H_

//����LED��ʾʱҪע�� : ��������Դָʾ��(��Դָʾ��ֻ�ɵ�Դ������������)
#define LED_NONE	0x01	 
#define LED_ALL		0xFE   

#define LED_VOLT	0x01
#define LED_BIND	0x02

#define LED_CH6_H	0x04
#define LED_CH6_M	0x08
#define	LED_CH5 	0x10

#define LED_CH8_H	0x20
#define LED_CH8_M	0x40
#define LED_CH7 	0x80

extern uint8_t LED_State_ON     ;
extern uint8_t LED_State_Shake  ; 
extern uint8_t LED_Status_SendDat ; 

void LED_UART1_Init(void);
void LED_Usart1Send(void);
void Volt_LED(float Volt_Value);

#endif
