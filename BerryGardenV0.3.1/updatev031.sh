#!/bin/bash

echo Updating BerryGarden
sudo apt update && sudo apt upgrade

cd /BerryGarden/BerryGardenV0.3.1
git pull 
sudo rm /usr/bin/berryg
sudo rm /usr/bin/monitor 
gcc BerryGardenMon.c -o monitor -l wiringPi
gcc BerryGardenmain.c -o berryg -l wiringPi

echo copie berryg and monitor (Version 0.3.1)
sudo cp berryg /usr/bin
sudo cp monitor /usr/bin

cd /BerryGarden
gcc uniup.c -o uniup
sudo cp uniup /usr/bin
sudo cp uniup.sh /usr/bin
cd /usr/bin
chmod u+x uniup.sh

cd /BerryGarden/BerryGardenV0.3.1
echo remove berryg.elf
rm berryg
echo Add Auto Start on Login
echo Open Readme...
nano READMEV0.3.1.md
