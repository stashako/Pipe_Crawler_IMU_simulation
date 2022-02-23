#pragma once

#include "i2c_multiplexer.h"
#include "getbno055.h"


struct addr
{
    static char senaddr_[256];
    static char i2c_bus[256];
    static char senaddr[256];
};



class i2cmultiplexer
{

public:
    i2cmultiplexer();
    void switch_channel(multiplexer_t channel);
};

class imuSensor
{

public:
    imuSensor();
    void mode(opmode_t newmode);
    void power(power_t newmode1);
    int *imu_data();
};

