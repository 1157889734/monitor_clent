
#ifndef LED_H
#define LED_H

#ifdef __cplusplus
extern "C"{
#endif /* End of #ifdef __cplusplus */
#define  LED_ON    0x01
#define  LED_OFF   0x00


#define   LED_DEVICE   95

void LED_Init();
int gpio_output_ctrl(int gpio, int value);

#ifdef __cplusplus
}
#endif /* End of #ifdef __cplusplus */


#endif
