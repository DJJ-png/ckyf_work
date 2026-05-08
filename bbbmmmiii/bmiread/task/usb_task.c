#include "main.h"
#include "BMI088driver.h"
#include "BMI088Middleware.h"
#include "bsp_usb.h"
#include "usb_task.h"
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#define CH_COUNT 6

extern osThreadId USB_TASKHandle;
struct Frame
{
    float fdata[CH_COUNT];
    unsigned char tail[4];
};
struct Frame sine_frame = {
    .fdata = {0},
    .tail = {0x00, 0x00, 0x80, 0x7f}
};


float gyro[3], accel[3], temp;


void usb_task(void const * argument){
	BMI088_init();
	usb_init();
	while(1){
		BMI088_read(gyro,accel,&temp);
		sine_frame.fdata[0]=gyro[0];
		sine_frame.fdata[1]=gyro[1];
		sine_frame.fdata[2]=gyro[2];
		usb_data_send((uint8_t*)&sine_frame,sizeof(struct Frame));
		vTaskDelay(10);
	}
}