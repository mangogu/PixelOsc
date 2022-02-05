# Pixel Osc Overview

*Updated February 2022*

[TOC]

## Hardware:

### *PART1 - CORE_BOARD*

![image-20220206025503564](.\images\image-20220206025503564.png)

![image-20220206025517163](.\images\image-20220206025517163.png)

![image-20220206025139658](.\images\image-20220206025139658.png)

![image-20220206025325724](.\images\image-20220206025325724.png)

### *PART2 - CTR_PAD*

![image-20220206025553371](.\images\image-20220206025553371.png)

![image-20220206025309964](.\images\image-20220206025309964.png)

![image-20220206025611494](.\images\image-20220206025611494.png)

### *PART3 - PANNEL_BOARD*

![image-20220206025221994](.\images\image-20220206025221994.png)

*PART4 - ANALOG_BOARD*

![image-20220206025723231](.\images\image-20220206025723231.png)![image-20220206025729307](.\images\image-20220206025729307.png)![image-20220206025738316](.\images\image-20220206025738316.png)

![image-20220206025749313](.\images\image-20220206025749313.png)![image-20220206025757531](.\images\image-20220206025757531.png)

### *3D case model*

![image-20220206030629616](.\images\image-20220206030629616.png)

![image-20220206030918797](.\images\image-20220206030918797.png)

## Firmware:

- Developed in keil environment
- Use STM32Cube for configuration
- Use 2 MCU chips (stm32h750vbt6 & stm32f030k6)
- Task dispatch is similar to the OSAL
- Use linux-like commands to operate

### STM32H750 code

![image-20220206030226418](.\images\image-20220206030226418.png)

### STM32F030 code

![image-20220206030356912](.\images\image-20220206030356912.png)

![image-20220206030414105](.\images\image-20220206030414105.png)