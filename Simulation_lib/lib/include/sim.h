#pragma once

#include <iostream>
#include <unistd.h>
#include <vector>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

using namespace std;

struct angles
{
    static float shift;
    static float roll1;
    static float pitch1;
    static float yaw1;

    static float roll2;
    static float pitch2;
    static float yaw2;

    static float roll3;
    static float pitch3;
    static float yaw3;

    static vector<float> data;
};

void init();
void render();
void reshape(int w, int h);
void update();
void timer(int);
