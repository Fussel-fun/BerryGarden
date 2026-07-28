#!/bin/bash
sudo apt install pip
cd /
mkdir /berrypy
python3 -m venv myenv
python3 -m pip install adafruit-circuitpython-dht
echo updating .bashrc
cd 
echo "echo staring python env" >> .bashrc
echo "cd /berrypy" >> .bashrc
echo "source myenv/bin/activate" >> .bashrc
echo "echo Starting BerryGarden" >> .bashrc
echo "exec sudo berryg" >> .bashrc
echo Updating System 
sudo apt update && sudo apt upgrade 
sudo apt-get update && sudo apt-get upgrade
echo installing waht missing
echo installing Gcc
sudo apt install gcc 
echo installing git 
sudo apt-get install git git-core
echo installing Tmux
sudo apt install tmux
echo installing nginx
sudo apt install nginx

cd /
echo installing WiringPilib for C
sudo git clone https://github.com/wiringpi/wiringpi
cd wiringpi
./build

echo installing BerryGarden 
cd /
sudo git clone https://github.com/Fussel-fun/BerryGarden
cd /BerryGarden/BerryGardenV0.4
gcc BerryGardenMon.c -o monitor -l wiringPi
gcc BerryGardenmain.c -o berryg -l wiringPi
echo copie berryg031 and monitor
sudo cp berryg /usr/bin
sudo cp log.md /usr/bin
sudo cp monitor /usr/bin
sudo cp temp.py /berrypy
cd /BerryGarden/versions
gcc uniup.c -o uniup
sudo cp uniup uniup.sh uninstall.sh /usr/bin
echo cleanup
echo remove berryg.elf
cd /BerryGarden/BerryGardenV0.4
rm berryg

echo run up
cd /usr/bin
chmod u+x uniup.sh
./uniup.sh
sudo uniup
cd 
echo Open Readme...
nano READMEV0.4.md


