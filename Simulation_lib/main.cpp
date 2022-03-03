#include"sim.h"

int main(int argc, char **argv)
{
    static vector<float> IMU_data = {0.1,0.1,0.1,0.2,0.2,0.2,0.3,0.3,0.3};

    angles::data = IMU_data;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(500, 500);
    glutCreateWindow("OpenGl");

    glutDisplayFunc(render);
    glutReshapeFunc(reshape);
    init();
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);

    glutTimerFunc(0, timer, 0);

    glutMainLoop();

    return 0;
}

