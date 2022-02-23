#include <iostream>
#include "sender.h"
#include "i2c_imu.h"

using namespace std;



int main(int argc, char *argv[])
{
    int n = 0;

    if (argc != 3)
    {
        std::cout << "Wrong parameter\n"
                  << "Example usage ./client 127.0.0.1 1234" << std::endl;
        return -1;
    }



    while (1)
    {
        std::vector<float> msg = {0,0,0,0,0,0,0,0,0};

        ////////////////////////////////////////////////
        i2cmultiplexer multi;

        //vector<multiplexer_t> ch = {channel1, channel2, channel3, channel4, channel5, channel6};
        imuSensor imu;
        imu.mode(ndof_fmc);

        int *imuData;

        multi.switch_channel(channel1);
        imuData = imu.imu_data();

        msg[0] = *(imuData + 9);
        msg[1] = *(imuData + 10);
        msg[2] = *(imuData + 11);

        multi.switch_channel(channel2);
        imuData = imu.imu_data();

        msg[3] = *(imuData + 9);
        msg[4] = *(imuData + 10);
        msg[5] = *(imuData + 11);

        multi.switch_channel(channel3);
        imuData = imu.imu_data();

        msg[6] = *(imuData + 9);
        msg[7] = *(imuData + 10);
        msg[8] = *(imuData + 11);

        cout << "imu 1: " << msg[0] << "," << msg[1] << "," << msg[2] << " imu 2: " << msg[3] << "," << msg[4] << "," << msg[5] << " imu 3: " << msg[6] << "," << msg[7] << "," << msg[8] << endl;
        //////////////////////////////////////////////////////////

        sending(argv[1], argv[2], msg);

    }
    return 0;
}