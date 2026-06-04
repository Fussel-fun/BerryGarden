#!/bin/bash
echo Updating System 
apt update && sudo apt upgrade 
sudo apt-get update && sudo apt-get upgrade

echo installing Gcc
sudo apt install gcc 

echo installing git 
sudo apt-get install git git-core

git clone https://github.com/Fussel-fun/BerryGarden
cd BerryGarden
cd BerryGardenV0.3

echo installing WiringPilib for C
git clone https://github.com/wiringpi/wiringpi

cd wiringPi
./build

echo Running Gcc

gcc BerryGardenmon.c -o monitor -l wiringPi
gcc BerryGardenmain.c -o berryg03 -l wiringPi

echo copie berryg03 and monitor

sudo cp berryg02 /usr/bin
sudo cp log.md /usr/bin
sudo cp monitor /usr/bin

echo remove berryg02.elf
rm berryg02

echo Add Auto Start on Login
sudo echo "echo Starting BerryGarden" >> .bashrc
sudo echo "berryg02" >> .bashrc
cd BerryGardenV0.3

echo Open Readme...

nano READMEV0.3.md


