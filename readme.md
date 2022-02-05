# Pixel Osc Overview

*Updated February 2022*

[TOC]

## Hardware:

### *PART1 - CORE_BOARD*

![image-20220206025503564](https://github.com/mangogu/PixelOsc/blob/master/images/image-20220206025139658.png)

![image-20220206025517163](https://github.com/mangogu/PixelOsc/blob/master/images/image-20220206025517163.png)

![image-20220206025139658](https://github.com/mangogu/PixelOsc/blob/master/images/image-20220206025139658.png)

![image-20220206025325724](https://github.com/mangogu/PixelOsc/blob/master/images/image-20220206025325724.png)

### *PART2 - CTR_PAD*

![image-20220206025553371](https://github.com/mangogu/PixelOsc/blob/master/images/image-20220206025553371.png)

![image-20220206025309964](https://github.com/mangogu/PixelOsc/blob/master/images/image-20220206025309964.png)

![image-20220206025611494](https://github.com/mangogu/PixelOsc/blob/master/images/image-20220206025611494.png)

### *PART3 - PANNEL_BOARD*

![image-20220206025221994](https://github.com/mangogu/PixelOsc/blob/master/images/image-20220206025221994.png)

*PART4 - ANALOG_BOARD*

![image-20220206025723231](https://github.com/mangogu/PixelOsc/blob/master/images/image-20220206025723231.png)![image-20220206025729307](https://github.com/mangogu/PixelOsc/blob/master/images/image-20220206025729307.png)![image-20220206025738316](https://github.com/mangogu/PixelOsc/blob/master/images/image-20220206025738316.png)

![image-20220206025749313](https://github.com/mangogu/PixelOsc/blob/master/images/image-20220206025749313.png)![image-20220206025757531](https://github.com/mangogu/PixelOsc/blob/master/images/image-20220206025757531.png)

### *3D case model*

![image-20220206030629616](https://github.com/mangogu/PixelOsc/blob/master/images/image-20220206030629616.png)

![image-20220206030918797](https://github.com/mangogu/PixelOsc/blob/master/images/image-20220206030918797.png)

## Firmware:

- Developed in keil environment
- Use STM32Cube for configuration
- Use 2 MCU chips (stm32h750vbt6 & stm32f030k6)
- Task dispatch is similar to the OSAL
- Use linux-like commands to operate

### STM32H750 code

![image-20220206030226418](https://github.com/mangogu/PixelOsc/blob/master/images/image-20220206030226418.png)

### STM32F030 code

![image-20220206030356912](https://github.com/mangogu/PixelOsc/blob/master/images/image-20220206030356912.png)

![image-20220206030414105](https://github.com/mangogu/PixelOsc/blob/master/images/image-20220206030414105.png)