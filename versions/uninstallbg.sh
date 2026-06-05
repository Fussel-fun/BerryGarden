#!/bin/bash 

echo uninstalling BerryGarden 

cd 
rm log.md 

cd / 
sudo rm -rf BerryGarden wiringpi

cd /usr/bin 
sudo rm berryg log.md monitor updatev03.sh updatev031.sh

echo Please Delete Last to lines of .bashrc
