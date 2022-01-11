#include <iostream>
#include <unistd.h>
#include <vector>
#include "i2c_multiplexer.h"
#include "getbno055.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

using namespace std;

char senaddr_[256] = "0x70";  //multiplexer address
char i2c_bus[256] = I2CBUS;   //  /dev/i2c-1
char senaddr[256] = "0x28";   //imu address

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

void render();
void init();
void reshape(int w, int h);
void timer(int);

float shift = 4.0;
float roll1 = 0.0;
float pitch1 = 0.0;
float yaw1 = 0.0;

float roll2 = 0.0;
float pitch2 = 0.0;
float yaw2 = 0.0;

float roll3 = 0.0;
float pitch3 = 0.0;
float yaw3 = 0.0;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv)
{


    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    glutInitWindowPosition(100, 100);
    glutInitWindowSize(500, 500);

    glutCreateWindow("Crawler");

    glutDisplayFunc(render);
    glutReshapeFunc(reshape);
    init();

    glutTimerFunc(0, timer, 0);

    glutMainLoop();

    return 0;
}

void init()
{

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);
}

void render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(0.0, 0.0, 30.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    glRotatef(roll1, 1, 0, 0);
    glRotatef(pitch1, 0, 1, 0);
    glRotatef(yaw1, 0, 0, 1);

    GLUquadricObj* quadratic0;
    quadratic0 = gluNewQuadric();
    glColor3f(1.0, 0.0, 0.0);
    gluCylinder(quadratic0, 1.0f, 1.0f, 3.0f, 32, 2);

    glTranslatef(0, 0, shift);
    glRotatef(roll2-roll1, 1, 0, 0);
    glRotatef(pitch2-pitch1, 0, 1, 0);
    glRotatef(yaw2-yaw1, 0, 0, 1);

    GLUquadricObj* quadratic1;
    quadratic1 = gluNewQuadric();
    glColor3f(0.0, 1.0, 0.0);
    gluCylinder(quadratic1, 1.0f, 1.0f, 3.0f, 32, 2);

    glTranslatef(0, 0, shift);
    glRotatef(roll3-roll2-roll1, 1, 0, 0);
    glRotatef(pitch3-pitch2-pitch1, 0, 1, 0);
    glRotatef(yaw3-yaw2-yaw1, 0, 0, 1);

    GLUquadricObj* quadratic2;
    quadratic2 = gluNewQuadric();
    glColor3f(0.0, 0.0, 1.0);
    gluCylinder(quadratic2, 1.0f, 1.0f, 3.0f, 32, 2);

    glutSwapBuffers();
}

void reshape(int w, int h)
{

    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1, 2.0, 50.0);
    glMatrixMode(GL_MODELVIEW);
}

void timer(int)
{
    glutPostRedisplay();
    glutTimerFunc(1000 / 60, timer, 0);
    i2cmultiplexer multi;

    vector<multiplexer_t> ch = {channel1, channel2, channel3, channel4, channel5, channel6};
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
}