#include "i2c_imu.h"


char addr::senaddr_[256] = "0x70";
char addr::i2c_bus[256] = I2CBUS;
char addr::senaddr[256] = "0x28";


i2cmultiplexer::i2cmultiplexer()
{
    get_i2cbus_multiplexer(addr::i2c_bus, addr::senaddr_);
}

void i2cmultiplexer::switch_channel(multiplexer_t channel)
{
    set_multiplexer(channel);
}

imuSensor::imuSensor()
{
    get_i2cbus(addr::i2c_bus, addr::senaddr);
}
void imuSensor::mode(opmode_t newmode)
{
    //set the sensor operational mode
    set_mode(newmode);
    //newmode = acconly;
    //newmode = magonly;
    //newmode = gyronly;
    //newmode = accmag;
    //newmode = accgyro;
    //newmode = maggyro;
    //newmode = amg;
    //newmode = imu;
    //newmode = compass;
    //newmode = m4g;
    //newmode = ndof;
    //newmode = ndof_fmc;
}

void imuSensor::power(power_t newmode1)
{
    //set the sensor power mode
    set_power(newmode1);
    //newmode1 = normal;
    //newmode1 = low;
    //newmode1 = suspend;
}

int *imuSensor::imu_data()
{
    static int imu_data[22];

    struct bnoacc bnod1;
    get_acc(&bnod1);
    imu_data[0] = bnod1.adata_x;
    imu_data[1] = bnod1.adata_y;
    imu_data[2] = bnod1.adata_z;

    struct bnomag bnod2;
    get_mag(&bnod2);
    imu_data[3] = bnod2.mdata_x;
    imu_data[4] = bnod2.mdata_y;
    imu_data[5] = bnod2.mdata_z;

    struct bnogyr bnod3;
    get_gyr(&bnod3);
    imu_data[6] = bnod3.gdata_x;
    imu_data[7] = bnod3.gdata_y;
    imu_data[8] = bnod3.gdata_z;

    struct bnoeul bnod4;
    get_eul(&bnod4);
    imu_data[9] = bnod4.eul_head;
    imu_data[10] = bnod4.eul_roll;
    imu_data[11] = bnod4.eul_pitc;

    struct bnoqua bnod5;
    get_qua(&bnod5);
    imu_data[12] = bnod5.quater_w;
    imu_data[13] = bnod5.quater_x;
    imu_data[14] = bnod5.quater_y;
    imu_data[15] = bnod5.quater_z;

    struct bnogra bnod6;
    get_gra(&bnod6);
    imu_data[16] = bnod6.gravityx;
    imu_data[17] = bnod6.gravityy;
    imu_data[18] = bnod6.gravityz;

    struct bnolin bnod7;
    get_lin(&bnod7);
    imu_data[19] = bnod7.linacc_x;
    imu_data[20] = bnod7.linacc_y;
    imu_data[21] = bnod7.linacc_z;

    return imu_data;
}
