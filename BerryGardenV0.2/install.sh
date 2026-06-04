#!/bin/bash
echo Running Gcc

gcc MainMenuGPIO.c -o berryg02 -l wiringPi

echo copie berryg02


sudo cp berryg02 log.md /usr/bin

echo remove berryg02.elf

rm berryg02

echo Add Auto Start on Login
cd
sudo echo "echo Starting BerryGarden" >> .bashrc
sudo echo "berryg02" >> .bashrc
cd BerryGardenV0.2

echo Open Readme...

nano README.md


