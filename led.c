#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "led.h"

const char *const GPIOSysfsPath = "/sys/class/gpio";

static int export_gpio(const int gpio)
{
  char value[5];
  int rw, fd;
  char file_name[30];
  char gpio_name[30];
  sprintf(file_name, "%s/export", GPIOSysfsPath);
  fd = open(file_name, O_WRONLY);
  if (fd < 0)
  {
    return -1;
  }
  sprintf(gpio_name, "%s/gpio%d", GPIOSysfsPath, gpio);
  if (!access(gpio_name, 0))
    return 0;
  sprintf(value, "%d", gpio);
  rw = write(fd, value, strlen(value));
  if (rw < 0)
  {
    close(fd);
    return -1;
  }
  fsync(fd);
  close(fd);
  return 0;
}

static int set_direction_gpio(const int gpio, const char *value)
{
  int rw, fd;
  char file_name[100];
  sprintf(file_name, "%s/gpio%d/direction", GPIOSysfsPath, gpio);
  fd = open(file_name, O_WRONLY);
  if (fd < 0)
  {
    return -1;
  }
  rw = write(fd, value, strlen(value));
  if (rw < 0)
  {
    close(fd);
    return -1;
  }
  fsync(fd);
  close(fd);
  return 0;
}

static int write_gpio(const int gpio, int value)
{
  int rw, fd;
  char file_name[100];
  char str_value;
  sprintf(file_name, "%s/gpio%d/value", GPIOSysfsPath, gpio);
  fd = open(file_name, O_WRONLY);
  if (fd < 0)
  {
    return -1;
  }
  str_value = (value == 1) ? '1' : '0';
  rw = write(fd, &str_value, 1);
  if (rw < 0)
  {
    close(fd);
    return -1;
  }
  fsync(fd);
  close(fd);
  return 0;
}


int  GPIO_Init(const int _iGpio,const int _iDir)
{ 
 int iRet = -1;
 if (export_gpio(_iGpio) == 0)
    {
      if (_iDir == 0)
      {
        if (set_direction_gpio(_iGpio, "out") != 0)
        {
          
          printf("[gpio]: error init gpio:%d,set_direction:%d\r\n", _iGpio,_iDir);
        }else
        {
            iRet = 0;
        }
        
      }
      else
      {
        if (set_direction_gpio(_iGpio, "in") != 0)
        {
          iRet = -1;
          printf("[gpio]:error init gpio:%d,set_direction:%d\r\n", _iGpio, _iDir);
        }else
        {
              iRet = 0;
        }
        
      }
    }
    return iRet;
}

void LED_Init()
{
    GPIO_Init(LED_DEVICE,0);
}

int gpio_output_ctrl(int gpio, int value)
{
    return write_gpio(gpio, value);  
}
