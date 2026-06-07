#!/bin/bash 

cd /BerryGarden/Version
git pull 
sudo cp updatev03.sh updatev031.sh uninstallbg.sh /usr/bin
cd /usr/bin
chmod u+x updatev03.sh
chmod u+x updatev031.sh
chmod u+x uninstall.sh
