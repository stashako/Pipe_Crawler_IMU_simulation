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