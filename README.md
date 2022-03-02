Client Server libraries:

1. sudo apt install libboost-dev
2. sudo apt install libboost-system-dev
3. sudo apt-get install libpthread-stubs0-dev (maybe)
4. sudo apt install libboost-thread-dev (maybe)


//g++ -lpthread -lboost_system server.cpp -o server    or    g++ main.cpp -o server -L /usr/lib -lpthread -lboost_system -lboost_thread




################################################################################################################
I2C configuration:


1. Install i2c-tools:
sudo apt install i2c-tools

2. Activate i2c on raspberry pi:
Edit "/boot/config.txt" by changing "dtparam=i2c_arm=on"

3. Check i2c connection:
i2cdetect -y 1

You can also change the multiplexer channel by:
i2cset -y 1 0x70 0x01
or
i2cset -y 1 0x70 0x02
or 
i2cset -y 1 0x70 0x03 
...

4. Reduce the frequency rate:
Edit "/boot/config.txt" by changing "dtparam=i2c_arm=on, i2c_arm_baudrate=10000"