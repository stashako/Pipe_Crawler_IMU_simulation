#include <iostream>
#include <boost/asio.hpp>
#include <unistd.h>
#include <vector>
#include "i2c_multiplexer.h"
#include "getbno055.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

using namespace std;

char senaddr_[256] = "0x70";
char i2c_bus[256] = I2CBUS;
char senaddr[256] = "0x28";

class i2cmultiplexer
{

public:
    i2cmultiplexer()
    {
        get_i2cbus_multiplexer(i2c_bus, senaddr_);
    }

    void switch_channel(multiplexer_t channel)
    {
        set_multiplexer(channel);
    }
};

class imuSensor
{

public:
    imuSensor()
    {
        get_i2cbus(i2c_bus, senaddr);
    }
    void mode(opmode_t newmode)
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

    void power(power_t newmode1)
    {
        //set the sensor power mode
        set_power(newmode1);
        //newmode1 = normal;
        //newmode1 = low;
        //newmode1 = suspend;
    }

    int *imu_data()
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
};

float roll1 = 0.0;
float pitch1 = 0.0;
float yaw1 = 0.0;

float roll2 = 0.0;
float pitch2 = 0.0;
float yaw2 = 0.0;

float roll3 = 0.0;
float pitch3 = 0.0;
float yaw3 = 0.0;

int main(int argc, char *argv[])
{
    int n = 0;

    if (argc != 3)
    {
        std::cout << "Wrong parameter\n"
                  << "Example usage ./client 127.0.0.1 1234 hello" << std::endl;
        return -1;
    }

    auto const address = boost::asio::ip::make_address(argv[1]);
    auto const port = std::atoi(argv[2]);


    while (1)
    {
        std::string number1 = std::to_string(roll1);
        std::string number2 = std::to_string(pitch1);
        std::string number3 = std::to_string(yaw1);
        std::string number4 = std::to_string(roll2);
        std::string number5 = std::to_string(pitch2);
        std::string number6 = std::to_string(yaw2);
        std::string number7 = std::to_string(roll3);
        std::string number8 = std::to_string(pitch3);
        std::string number9 = std::to_string(yaw3);
        std::string msg;
        msg = "IMU_1: " + number1 +  "," + number2 + "," + number3 + " IMU_2: " + number4 +  "," + number5 + "," + number6 + " IMU_3: " + number7 +  "," + number8 + "," + number9 +'\n';

////////////////////////////////////////////////
    i2cmultiplexer multi;

    //vector<multiplexer_t> ch = {channel1, channel2, channel3, channel4, channel5, channel6};
    imuSensor imu;
    imu.mode(ndof_fmc);

    int *imuData;

    multi.switch_channel(channel1);
    imuData = imu.imu_data();

    roll1 = *(imuData + 9);
    pitch1 = *(imuData + 10);
    yaw1 = *(imuData + 11);


    multi.switch_channel(channel2);
    imuData = imu.imu_data();

    roll2 = *(imuData + 9);
    pitch2 = *(imuData + 10);
    yaw2 = *(imuData + 11);

    multi.switch_channel(channel3);
    imuData = imu.imu_data();

    roll3 = *(imuData + 9);
    pitch3 = *(imuData + 10);
    yaw3 = *(imuData + 11);

    cout << "imu 1: " << roll1 << "," << pitch1 << "," << yaw1 << " imu 2: " << roll2 << "," << pitch2 << "," << yaw2 << " imu 3: " << roll3 << "," << pitch3 << "," << yaw3 << endl;
//////////////////////////////////////////////////////////




        boost::asio::io_service io_service;
        //socket creation
        boost::asio::ip::tcp::socket socket(io_service);
        //connection
        boost::system::error_code ec;
        socket.connect(boost::asio::ip::tcp::endpoint(address, port), ec);
        if (ec)
        {
            std::cout << ec.message() << std::endl;
            return 1;
        }
        // request/message from client
        //const string msg = "Hello from Client!\n";
        boost::system::error_code error;
        boost::asio::write(socket, boost::asio::buffer(msg), error);
        if (error)
        {
            std::cout << "send failed: " << error.message() << std::endl;
        }
        // getting response from server
        boost::asio::streambuf receive_buffer;
        boost::asio::read(socket, receive_buffer, boost::asio::transfer_all(), error);
        if (error && error != boost::asio::error::eof)
        {
            std::cout << "receive failed: " << error.message() << std::endl;
        }
        else
        {
            const char *data = boost::asio::buffer_cast<const char *>(receive_buffer.data());
            std::cout << data << std::endl;
        }
    }
    return 0;
}