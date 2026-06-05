#!/bin/bash 

cd /BerryGarden
git pull 
cd /BerryGarden/versions
gcc uniup.c -o uniup
sudo cp uniup updatev03.sh updatev031.sh /usr/bin
cd /usr/bin
chmod u+x updatev03.sh
chmod u+x updatev031.sh
cd
