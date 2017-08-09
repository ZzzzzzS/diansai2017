#ifndef _ENTER_H_
#define _ENTER_H_
#include "stdint.h"

/*
    FWD 文件为山外UD版核心板专用的固件文件，提供常用字库和函数功能，加快开发速度和调试速度。
    FWD是可执行的文件。直接烧录到指定的位置，即可在 APP中调用相关的 API 函数。非UD版，请勿使用FWD固件。

    烧录方法：

        插好usb线，按着 独立按键(默认是 PTD7，即核心板上的独立按键)，然后复位，即可进入UD模式。

        电脑会识别到插入UD下载盘，把FWD文件复制到U盘的根目录即可。


    若在使用中发现有bug，请发邮件到此邮箱：minimcu@foxmail.com。我们会尽快更新。

*/


//用户的API 函数接口，可看下面的结构体的注释，有注明函数原型
//一般看注释里的函数原型即可使用的。
//APP需要初始化时执行 ASSERT(enter_init());判断是否已经烧录了固件

#define FWD_VER     101

typedef struct
{
    uint16_t    flag;       //标记
    uint16_t    ver;        //版本

    //字库
    uint8_t *   ascii;      //英文字库      6x12
    uint8_t *   chinese;    //中文字库入口  12x12

    //常用小功能
    void *      cpy;        //void *    memcpy  ( uint8_t *dst, uint8_t *src, uint32_t count)       内存复制
    void *      memset;     //void *    memset  (void *src, int c, int count);                      内存设置数值
    void *      img_ext;    //void      img_extract(void *dst, void *src, uint32_t srclen);         摄像头解压

    //字符串 变量 转换
    void *      sptf;       //int       sprintf (char *buf, const char *fmt, ...)
    void *      ptf;        //void      printf  (fp,fmt, ...)
    void *      atoi;       //int       atoi    (char *str);                                        字符串转成整型
    void *      itoa;       //char *    itoa    (int n, char * chBuffer);                           整型转换为字符串
    void *      ftoa;       //char *    ftoa    (double dValue, char * chBuffer);                   浮点转换为字符串

    void *      get_isr;    //int       get_isr_info(char * str);

    //flash API
    void *      flash_init;         //void    flash_init();                                 初始化Flash
    void *      flash_erase_sector; //uint8   flash_erase_sector  (uint16 sectorNum);             //擦除指定flash扇区
    void *      flash_write;        //uint8   flash_write         (uint16 sectorNum, uint16 offset, FLASH_WRITE_TYPE data);                //写入flash操作
    void *      flash_write_buf;    //uint8   flash_write_buf     (uint16 sectorNum, uint16 offset, uint16 cnt, uint8 buf[]);              //从缓存区写入flash操作
    //还有一个flash API接口：                  flash_read          (sectorNum,offset,type)


    //flash 存储数据
    void *      flash_data_init;    //void      flash_data_init     (flash_data_t *d);      //对结构体数据进行预处理，若flash的数据还没初始化，则重置flash
    void *      flash_data_reset;   //void      flash_data_reset    (flash_datasave_t *d);  //重置flash，就是对存储数据进行清空
    void *      flash_data_load;    //uint8_t   flash_data_load     (flash_datasave_t *d);  //从 flash 加载数据
    void *      flash_data_save;    //uint8_t   flash_data_save     (flash_datasave_t *d);  //保存数据到flash



}mydata_in_t;


//数据的尺寸 必须是 FLASH_ALIGN_ADDR 对齐
//
typedef struct
{
    uint16_t    sectornum_start;        //开始的扇区
    uint16_t    sectornum_end;          //结束的扇区
    void *     data_addr;              //数据的地址
    uint16_t    data_size;              //数据的尺寸
    uint16_t    res1;                    //保留，底层使用 （勿删）
    uint32_t    res2[2];                 // 保留，底层使用 （勿删）


}flash_data_t;

//     固件的起始地址
#define START_APP_ADDR  (32*1024)
#if defined(MK60DZ10)
#define START_FWD_ADDR  (256*1024)
#elif defined(MK60F15)
#define START_FWD_ADDR  (512*1024)
#endif

//内部用，用户无需关注
#define OFFSET(type, member)    (uint32)(&(((type *)0)->member))
#define IN_ADDR(member)         (*((uint32_t *)(START_FWD_ADDR + OFFSET(mydata_in_t, member)) ))


//用户的 API 接口调用
//
#ifndef FWD_LIB         //请勿在工程中定义此宏定义(内部识别用的) by 山外

#define  enter_init()      (((uint16_t)IN_ADDR(flag)==0x55A5) && (uint16_t)IN_ADDR(ver)==FWD_VER)      //用于判断固件文件是否存在 ,APP需要初始化时执行 ASSERT(enter_init());

#define  ASCII              ((uint8_t *)(IN_ADDR(ascii)))              // ASCII 6x12 字库
#define  CHINESE            ((uint8_t *)(IN_ADDR(chinese)))            // 汉字 12x12 字库

//内存复制函数
typedef void * (*memcpy_t)( uint8_t *dst, uint8_t *src, uint32_t count);
#define memcpy(dst,src,n)                       (*(memcpy_t)(IN_ADDR(cpy)))((uint8_t *)dst,(uint8_t *)src,n)

typedef void *    (*memset_t)  (void *src, int c, int count);
#define memset(src,c,n)                       (*(memset_t)(IN_ADDR(memset)))((void *)src,c,n)

//图像解压函数
typedef void (*img_ext_t)(void *dst, void *src, uint32_t srclen);
#define  img_extract(dst,src,srclen)            (*(img_ext_t)(IN_ADDR(img_ext)))(dst,src,srclen)

//sprintf，变量转换为字符串
typedef int (*sprintf_t)(char *buf, const char *fmt, ...);
#define sprintf(buf,fmt, ...)                   (*(sprintf_t)(IN_ADDR(sptf)))(buf,fmt, ## __VA_ARGS__)

//printf，打印函数，需要自己实现 enter_fputc 函数
extern int enter_fputc(char ch);                    //需要用户自定义实现此函数
typedef int fputc_t (char c);
typedef int (*printf_t)(fputc_t *fp, const char *fmt, ...);
#define printf(fmt, ...)                        (*(printf_t)(IN_ADDR(ptf)))(enter_fputc,fmt, ## __VA_ARGS__)

//获取中断提示信息（哪个端口触发中断）
typedef int (*get_isr_info_t)(char * str);
#define  get_isr_info(str)                      (*(get_isr_info_t)(IN_ADDR(get_isr)))(str)

//字符串转成整型
typedef int (*atoi_t)(char * str);
#define  atoi(str)                      (*(atoi_t)(IN_ADDR(atoi)))(str)

//整型转换为字符串
typedef char * (*itoa_t)(int n, char * str);
#define  itoa(n,str)                      (*(itoa_t)(IN_ADDR(itoa)))(n,str)     //int n=123;char buff[20]; itoa(n,buff);   //把变量123转换为字符串

//浮点转换为字符串
typedef char * (*ftoa_t)(double dValue, char * str);
#define  ftoa(d,str)                      (*(ftoa_t)(IN_ADDR(ftoa)))(d,str)     //


// ****************** FLASH API 专区 ******************
#if defined(MK60DZ10)
#define     FLASH_SECTOR_SIZE       (2*1024)                //扇区大小 为 2k 字节
#define     FLASH_SECTOR_NUM        (256)                   //扇区数

#define     FLASH_ALIGN_ADDR        4                       //地址对齐整数倍
typedef     uint32                  FLASH_WRITE_TYPE;       //flash_write 函数写入 的数据类型


#elif defined(MK60FX15)
#define     FLASH_SECTOR_SIZE       (4*1024)                //扇区大小 为 4k 字节
#define     FLASH_SECTOR_NUM        (128)                   //扇区数

#define     FLASH_ALIGN_ADDR        8                       //地址对齐整数倍
typedef     uint64                  FLASH_WRITE_TYPE;       //flash_write 函数写入 的数据类型

#elif defined(MK60FN15)
#define     FLASH_SECTOR_SIZE       (4*1024)                //扇区大小 为 4k 字节
#define     FLASH_SECTOR_NUM        (256)                   //扇区数

#define     FLASH_ALIGN_ADDR        8                       //地址对齐整数倍
typedef     uint64                  FLASH_WRITE_TYPE;       //flash_write 函数写入 的数据类型
#endif

// 初始化Flash
typedef void  (*flash_init_t)(void);
#define  flash_init()                      (*(flash_init_t)(IN_ADDR(flash_init)))()     //

// 擦除指定flash扇区
typedef uint8  (*flash_erase_sector_t)(uint16 sectorNum);
#define  flash_erase_sector(sectorNum)     (*(flash_erase_sector_t)(IN_ADDR(flash_erase_sector)))(sectorNum)

// 写入flash操作
typedef uint8  (*flash_write_t)(uint16 sectorNum, uint16 offset, FLASH_WRITE_TYPE data);
#define  flash_write(sectorNum,offset,data)  (*(flash_write_t)(IN_ADDR(flash_write)))(sectorNum,offset,data)

// 写入flash操作
typedef uint8  (*flash_write_buf_t)(uint16 sectorNum, uint16 offset, uint16 cnt, uint8 buf[]);
#define  flash_write_buf(sectorNum,offset,cnt,buf)  (*(flash_write_buf_t)(IN_ADDR(flash_write_buf)))(sectorNum,offset,cnt,buf)

#define     flash_off(sectorNo,offset)              ((uint32)(((sectorNo)*FLASH_SECTOR_SIZE) + (offset)))
#define     flash_read(sectorNo,offset,type)        (*(type *)flash_off(sectorNo,offset) )         //读取扇区

//flash 存储数据

//对结构体数据进行预处理，若flash的数据还没初始化，则重置flash (含 flash初始化)
typedef void  (*flash_data_init_t)(flash_data_t *d);
#define  flash_data_init(d)                      (*(flash_data_init_t)(IN_ADDR(flash_data_init)))(d)     //

//重置flash，就是对存储数据进行清空
typedef void  (*flash_data_reset_t)(flash_data_t *d);
#define  flash_data_reset(d)                      (*(flash_data_reset_t)(IN_ADDR(flash_data_reset)))(d)     //

//从 flash 加载数据
typedef uint8_t  (*flash_data_load_t)(flash_data_t *d);
#define  flash_data_load(d)                      (*(flash_data_load_t)(IN_ADDR(flash_data_load)))(d)     //

//保存数据到flash
typedef uint8_t  (*flash_data_save_t)(flash_data_t *d);
#define  flash_data_save(d)                      (*(flash_data_save_t)(IN_ADDR(flash_data_save)))(d)     //





#endif    //

#endif   //_ENTER_H_

