/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2013,山外科技
 *     All rights reserved.
 *     技术讨论：山外论坛 http://www.vcan123.com
 *
 *     除注明出处外，以下所有内容版权均属山外科技所有，未经允许，不得用于商业用途，
 *     修改内容时必须保留山外科技的版权声明。
 *
 * @file       MK60_conf.c
 * @brief      山外K60 平台配置功能实现文件
 * @author     山外科技
 * @version    v5.1
 * @date       2013-06-26
 */

#include    "common.h"
#include    "MK60_uart.h"
#include    "VCAN_KEY.h"
#include    "VCAN_LED.h"




/*!
 *  @brief      断言失败所执行的函数
 *  @param      file    文件路径地址
 *  @param      line    行数
 *  @since      v6.0
 *  Sample usage:       assert_failed(__FILE__, __LINE__);
 */
const char ASSERT_FAILED_STR[] = "断言失败，在%s的第%d行。请检查改行的代码，传递的参数异常。\n";

void assert_failed(char *file, int line)
{
    led_init(LED0);
    while (1)
    {

        if(enter_init())
        {
            DEBUG_PRINTF(ASSERT_FAILED_STR, file, line);      //通过串口提示断言失败
        }

        //死循环等待程序员检测为何断言失败
        led_turn(LED0);
        DELAY_MS(1000);

    }
}

/*!
 *  @brief      重定义printf 到串口
 *  @param      ch      需要打印的字节
 *  @param      stream  数据流
 *  @since      v6.0
 *  @note       此函数由FWD的printf所调用
 */
int enter_fputc(char ch)
{
    uart_putchar(VCAN_PORT, (char)ch);
    return(ch);
}




#include "VCAN_LCD.h"

/*!
 *  @brief      默认中断服务函数
 *  @since      v6.0
 *  @note       此函数写入中断向量表里，不需要用户执行
 */
void default_isr(void)
{
    uint8_t tip_str[100];
    Site_t site     = {0, 0};
    Size_t size ;

    get_isr_info((char *)tip_str) ;

    led_init(LED1);

    LCD_INIT();                             //初始化LCD

    size.W = LCD_W;
    size.H = LCD_H;

    LCD_rectangle(site, size, BCOLOUR);     //初始化背景
     
    site.y=10;
    LCD_Str_ENCH(site,tip_str , FCOLOUR,BCOLOUR);

    while(1)
    {
        led_turn(LED1);

        DEBUG_PRINTF("%s", tip_str);
        DELAY_MS(1000);
    }
}

/* hard fault interrupt handler */
void hardfault_isr(void)
{
    //进入这个中断，表示程序跑飞了，执行有误，或者调用未初始化的模块。
    default_isr();
}
