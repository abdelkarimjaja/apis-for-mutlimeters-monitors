# stm32-control-pump
This repository aims to create the APIs for Multimeters monitor device.
\
Hardware Used: 
1. Nucleo-F302R8 Board, its description: https://os.mbed.com/platforms/ST-Nucleo-F302R8/.
2. PicoScope 3203D MSO, you find its specifications in the following link: https://www.picotech.com/oscilloscope/3000/picoscope-3000-oscilloscope-specifications
3. XGZP6859D Pressure Sensor Module, below its datasheet: 
    http://cfsensor.com/static/upload/file/20210731/XGZP6859D%20Pressure%20Sensor%20Module%20V2.pdf
\
Software Used:
1. STM32CubeIDE is an all-in-one multi-OS development tool, which is part of the STM32Cube software ecosystem, you find more details about it from this link: https://www.st.com/en/development-tools/stm32cubeide.html
\
The APIs are shown below:
1. PWM API for control the speed of an pomp. Show the folder  ./PWM API
2. Pression API for read the pression from XGZP6859D Pressure Sensor Module. Show the folder  ./pression API

