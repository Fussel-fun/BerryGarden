Welcome To BerryGarden 
Version 0.2

This is a early version of a programm for the Raspberrypi Computers to Monitor GrowTents and Gardens.

BerryGarden is writen in C and by one Person (until now), so the Code might not be the best.

Since BerryGarden is Writen only by Me im more than Thankfull if anyone wanna help and become a part of this Hobby projekt.

FUNCTIONS:

BerryGarden is a CLI Monitor for Plants that can Read if the Light is on or off, the Soil has enought Water, Waht the Temp and Humidity is, and the Abillity to Turn on a 5V Fans and a 5V Diver Pump
For Reading The Light its easy and Cheap to use a LDR 
For Reading The Water in the Soil you could use a Sensor but two unshielded Wires do the same Job(for safety reasons its not recommended to run it for Long periods of Time)
Temp and Humidity Sensor arnt included in the Code yet but will come untill next Month :)

INSTALL:

To install BerryGarden on your RasPi: 
1. clone the github repo 

2. Run the Install.sh of the version you wanna install file with chmod u+x (Which compiles the C file and moves the .elf file and log.md file in to /usr/bin)

3. run berryg02 to open BerryGarden

!! Make Sure to install gcc and the wiringPi libray on the Pi before installing!!

After the installation BerryGarden Auto runs after Login for an easy use with ssh on phones

Options: 
1 = TEMP MENU
Read Temp 
Turn ON Fan 

2 = LIGHT MENU
Read Light On or Off

3 = WATER MENU
Turn Pump on 
Turn Pump Of 
Read Soil 

4 = AIR MENU
Read Humidity 
Turn On Fans 
Turn Off Fans 

5 = LOGS
Printf Log file To Console (See all GPIO Actions)

9 = QUIT

PINOUT:

PIN17, OUTPUT   //FAN
PIN27, INPUT    //FAN READ
PIN26, OUTPUT   //LIGHTCHECK
PIN16, INPUT    //LIGHTCHECK READ
PIN14, OUTPUT   //SOILPROB
PIN15, INPUT    //SOILPROB READ
PIN2,  OUTPUT   //PUMP
PIN3,  INPUT    //PUMP READ

PS: 
This Is Purely a Hobby Projekt so im Sorry if the Code is Messy. If you have any ideas how to Make Projekt Better Let me Know or Send a PR :) !!!
