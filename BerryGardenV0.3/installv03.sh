#!/bin/bash
echo updating .bashrc
echo "echo Starting BerryGarden" >> .bashrc
echo "berryg03" >> .bashrc
echo Updating System 
sudo apt update && sudo apt upgrade 
sudo apt-get update && sudo apt-get upgrade
echo installing Gcc
sudo apt install gcc 
echo installing git 
sudo apt-get install git git-core
cd /
echo installing WiringPilib for C
sudo git clone https://github.com/wiringpi/wiringpi
cd wiringpi
./build
echo Running Gcc
cd /
sudo git clone https://github.com/Fussel-fun/BerryGarden
cd /BerryGarden/BerryGardenV0.3
gcc BerryGardenMon.c -o monitor -l wiringPi
gcc BerryGardenmain.c -o berryg03 -l wiringPi
echo copie berryg03 and monitor
sudo cp berryg03 /usr/bin
sudo cp log.md /usr/bin
sudo cp monitor /usr/bin
echo remove berryg03.elf
rm berryg03
echo Add Auto Start on Login
cd /BerryGarden/BerryGardenV0.3
echo Open Readme...
nano READMEV0.3.md


