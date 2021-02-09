# alarm-clock-AVR
Alarm clock for atmega328p with out complex eletronics. Require a atmega328p and a TM1638 module

It's important to note that the times values are no rounded numbers, as 100 or 1000 or 500 or 60. This happened cause I made this for an atmega328p without external crystal.
That means the code will run with internal clock that is not so precise (around 8Mhz). After some fast calcs and tests I constated the aprox real internal clock and calculated the adequade (not such) numbers for the parameters
![imagem](https://github.com/PJbourne/alarm-clock-AVR/blob/main/photo_2021-02-09_12-20-57.jpg?raw=true)

I used a Aduino Leonard as ISP programmer
![imagem2](https://github.com/PJbourne/alarm-clock-AVR/blob/main/photo_2021-02-09_12-20-52.jpg?raw=true)
