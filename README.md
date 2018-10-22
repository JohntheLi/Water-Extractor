# Water-Extractor
Device built to optimally remove drinkable water from the air

## Introduction:
Water is a necessity for life. However, imagine being stuck in the wilderness, without any clean water to drink from. This brings up the problem: How do you get a sustainable source of water in the outdoors that can be easily carried with you wherever you go?

The goal of this project was to construct a device that uses condensation to extract drinking water from the air. A controller will be implemented to monitor and adjust the device to make it an accurate testing platform and to maiximize efficiency. 

This project was inspired by a DARPA challenge to create water from the atmosphere using low energy system.


## What this project uses:
- TI MSP430 - *Microcontroller used to control device settings and request temperature readings*
- C - *Program that instructs the microcontroller when to read data from temperature sensors and to adjust fan speeds*
- Java -  *GUI terminal to recieve data on PC* 

## How it works:

![alt text](https://imgur.com/UIItl8t.png)

Fresh air is pulled into the device using a PWM-speed controlled fan. The air first moves past a series of cold copper tubes, the "heat recovery", which initially lowers the air temperature. The air is then funneled into a smaller tunnel, where a thermoelectric cooler lowers the air temperature to the dew point, forming water that is collected in a tank. The cold air with water removed is then looped around back into the original copper tubes, exchanging heat with incoming air. Finally, the cold air is used to help remove waste heat from the cooler.

This way, the device is running at optimal efficiency as the energy used to cool down the air is not wasted, but rather recycled back into the system.

## System Design:

![alt text](https://imgur.com/ND0aTu7.png)

Java Terminal:
![alt text](https://imgur.com/Ol8tfbR.png)

## 3D Modeling:

![alt text](https://imgur.com/CbQxpIg.png)

## Result:

The created device was capable of extracting ~0.3L of water per night. Although this is not as much as I initially intended, there were several issues that reduced the effectiveness of my device. 
- The cooler temperature often reached negative values, causing the formation of ice, reducing airflow 
  - Fixable by increasing airflow or lowering cooler power
- Based on the temperature readings as the air moved around the tunnels, there was still significant heat loss 
  - Fixable by adding better insulations (such as vacuum insulation)
- The fans were not powerful enough to create large airflow in the device, so not much moisture was processed 
  - Fixable with larger, more powerful fans

Overall, the cost effectiveness of my device is still very high:
  Compared to the average cost of $30 per gallon of water delivered to Afghanistan using a C-17 plane, my device only requires $0.93 of electricity cost per gallon of water.
  
  My test was conducted in a 67% humidity environment, whereas in Afghanistan the average humidity is around 65% at night (according to weatherspark.com)
