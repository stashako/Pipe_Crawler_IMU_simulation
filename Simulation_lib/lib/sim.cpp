#include "sim.h"

float angles::shift = 4.0;
float angles::roll1 = 90.0;
float angles::pitch1 = 0.0;
float angles::yaw1 = 0.0;

float angles::roll2 = 90.0;
float angles::pitch2 = 0.0;
float angles::yaw2 = 0.0;

float angles::roll3 = 0.0;
float angles::pitch3 = 0.0;
float angles::yaw3 = 0.0;


vector<float> angles::data = {};

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

    glTranslatef(0, 0, angles::shift);
    glRotatef(angles::roll1, 1, 0, 0);
    glRotatef(angles::pitch1, 0, 1, 0);
    glRotatef(angles::yaw1, 0, 0, 1);

    GLUquadricObj *quadratic0;
    quadratic0 = gluNewQuadric();
    glColor3f(1.0, 0.0, 0.0);
    gluCylinder(quadratic0, 1.0f, 1.0f, 4.0f, 32, 2);

    glTranslatef(0, 0, angles::shift);
    glRotatef(angles::roll2 - angles::roll1, 1, 0, 0);
    glRotatef(angles::pitch2 - angles::pitch1, 0, 1, 0);
    glRotatef(angles::yaw2 - angles::yaw1, 0, 0, 1);

    GLUquadricObj *quadratic1;
    quadratic1 = gluNewQuadric();
    glColor3f(0.0, 1.0, 0.0);
    gluCylinder(quadratic1, 1.0f, 1.0f, 4.0f, 32, 2);

    glTranslatef(0, 0, angles::shift);
    glRotatef(angles::roll3 - angles::roll2 + angles::roll1, 1, 0, 0);
    glRotatef(angles::pitch3 - angles::pitch2 + angles::pitch1, 0, 1, 0);
    glRotatef(angles::yaw3 - angles::yaw2 + angles::yaw1, 0, 0, 1);

    GLUquadricObj *quadratic2;
    quadratic2 = gluNewQuadric();
    glColor3f(0.0, 0.0, 1.0);
    gluCylinder(quadratic2, 1.0f, 1.0f, 4.0f, 32, 2);

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

void update()
{
    angles::roll1 = angles::roll1 + angles::data[1];
    angles::pitch1 = angles::pitch1 + angles::data[2];
    angles::yaw1 = angles::yaw1 + angles::data[3];
    angles::roll2 = angles::roll2 + angles::data[4];
    angles::pitch2 = angles::pitch2 + angles::data[5];
    angles::yaw2 = angles::yaw2 + angles::data[6];
    angles::roll3 = angles::roll3 + angles::data[7];
    angles::pitch3 = angles::pitch3 + angles::data[8];
    angles::yaw3 = angles::yaw3 + angles::data[9];
}

void timer(int)
{
    glutPostRedisplay();
    glutTimerFunc(1000 / 60, timer, 0);
    update();
    // cout << "imu 1: " << roll1 << "," << pitch1 << "," << yaw1 << " imu 2: " << roll2 << "," << pitch2 << "," << yaw2 << " imu 3: " << roll3 << "," << pitch3 << "," << yaw3 << endl;
}
