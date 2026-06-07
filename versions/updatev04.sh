#!/bin/bash

echo Updating BerryGarden
sudo apt update && sudo apt upgrade

cd /BerryGarden
git pull 
cd /BerryGarden/BerryGardenV0.4
sudo rm /usr/bin/berryg
sudo rm /usr/bin/monitor 
gcc BerryGardenMon.c -o monitor -l wiringPi
gcc BerryGardenmain.c -o berryg -l wiringPi
echo copie berryg and monitor 
sudo cp berryg /usr/bin
sudo cp monitor /usr/bin

cd /BerryGarden/versions
sudo cp uniup /usr/bin
sudo cp uniup.sh /usr/bin
cd /usr/bin
chmod u+x uniup.sh

cd /BerryGarden/versions
cp updatev04.sh /usr/bin
cd /usr/bin
chmod u+x updatev04.sh 


echo Add Temp Script
cd /BerryGarden/BerryGardenV0.4/temp
python3 -m venv myenv
source myenv/bin/activate
python3 -m pi install adafruit-circuitpython-dht
cd /BerryGarden/BerryGardenV0.4
echo remove berryg.elf
rm berryg
echo Open Readme...
nano READMEV0.4.md
