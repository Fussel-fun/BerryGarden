#!/bin/bash

echo Updating BerryGarden
echo Updating BerryGarden
sudo apt update && sudo apt upgrade
cd /BerryGarden/BerryGardenV0.3
git pull 
sudo rm /usr/bin/berryg03 
sudo rm /usr/bin/monitor 

gcc BerryGardenMon.c -o monitor -l wiringPi
gcc BerryGardenmain.c -o berryg -l wiringPi
echo copie berryg and monitor
sudo cp berryg /usr/bin
sudo cp monitor /usr/bin
sudo cp updatev03.sh /usr/bin
cd /usr/bin 
chmod u+x updatev03.sh
echo remove berryg.elf
cd /BerryGarden/BerryGardenV0.3
rm berryg
echo Add Auto Start on Login
echo Open Readme...
nano READMEV0.3.md
