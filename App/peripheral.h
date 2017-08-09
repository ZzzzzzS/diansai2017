#ifndef __PERIPHERAL_H__
#define __PERIPHERAL_H__

extern void Send_Data();
extern void Receive_Data();
extern void Init_Key();
extern void OLED_Interface();
extern void DeBug_Interface();
extern void Debug_Init();
extern char CharAbs(char a);
extern void init_LED();
extern void LED_Interface();
extern void System_Error(char Error_Number);


#endif // __PERIPHERAL_H__