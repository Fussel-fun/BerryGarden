#!/bin/bash

echo Updating BerryGarden
echo Updating BerryGarden
sudo apt update && sudo apt upgrade
cd /BerryGarden/BerryGardenV0.3
git pull 
sudo rm /usr/bin/berryg03 
sudo rm /usr/bin/monitor 
chmod u+x updatev03.sh
gcc BerryGardenMon.c -o monitor -l wiringPi
gcc BerryGardenmain.c -o berryg03 -l wiringPi
echo copie berryg03 and monitor
sudo cp berryg03 /usr/bin
sudo cp monitor /usr/bin
sudo cp updatev03.sh /usr/bin
echo remove berryg03.elf
rm berryg03
echo Add Auto Start on Login
cd /BerryGarden/BerryGardenV0.3
echo Open Readme...
nano READMEV0.3.md
