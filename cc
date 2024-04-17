cd /tmp
wget https://project-downloads.drogon.net/wiringpi-latest.deb   //Download wiringpi library
sudo dpkg -i wiringpi-latest.deb  //Install wiringpi library
cd .....                                                     //Enter the content you want to save file in
git clone https://github.com/DFRobotdl/RS485_Wind_Speed_Transmitter.git     //Download program in github
cd RS485_Wind_Speed_Transmitter/



gcc -Wall -lwiringPi -o Wind_Speed *.c
sudo ./Wind_Speed
