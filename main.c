#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#include <GL/glut.h>

enum {
    RESET, DEPTH, ALIASING, EXIT
};

GLfloat rot = 0;

bool depth = true, aliasing = true;

void render(void);

void resize(int, int);

void menuHandler(int);

void drawPyramid(void);

int main(int argc, char **argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(700, 400);

    glutCreateWindow("Rotating Pyramid");

    glutDisplayFunc(&render);
    glutReshapeFunc(&resize);
    glutKeyboardFunc(NULL);
    glutIdleFunc(&render);
    glutMouseFunc(NULL);

    glutCreateMenu(&menuHandler);

    glutAddMenuEntry("Reset rotation", RESET);
    glutAddMenuEntry("Toggle depth", DEPTH);
    glutAddMenuEntry("Toggle smoothing", ALIASING);
    glutAddMenuEntry("Exit", EXIT);

    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();

    return EXIT_SUCCESS;
}

void render(void)
{
    glClearColor(0, 0, 0, 0);

    if (depth) {
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
    } else {
        glDisable(GL_DEPTH_TEST);
    }

    if (aliasing) {
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    glColor3f(1, 1, 0);
    glTranslatef(0, .5f, -2.5f);
    glRotatef(rot, 0, 1, 0);

    if (rot > 360) {
        rot = 0;
    } else {
        rot += 0.05f;
    }

    drawPyramid();

    glutSwapBuffers();

    glutPostRedisplay();
}

void resize(int x, int y)
{
    glViewport(0, 0, x, y);
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    GLdouble aspect = x / fmax(1, y);

    gluPerspective(90, aspect, 0.1, 10.0);

    render();
}

void menuHandler(int option)
{
    switch (option) {
        case RESET:
            rot = 0;
            break;
        case DEPTH:
            depth = !depth;
            break;
        case ALIASING:
            aliasing = !aliasing;
            break;
        case EXIT:
            exit(0);
    }
}

void drawPyramid()
{
    glBegin(GL_QUADS);

    glColor3f(1, 1, 1);
    glVertex3f(-1, -1, -1);

    glColor3f(1, 1, 0);
    glVertex3f(-1, -1, 1);

    glColor3f(1, 0, 0);
    glVertex3f(1, -1, 1);

    glColor3f(0, 0, 0);
    glVertex3f(1, -1, -1);

    glEnd();

    glBegin(GL_TRIANGLE_FAN);

    glColor3f(0, 0, 1);
    glVertex3f(0, 1, 0);

    glColor3f(1, 1, 1);
    glVertex3f(-1, -1, -1);

    glColor3f(1, 1, 0);
    glVertex3f(-1, -1, 1);

    glColor3f(1, 0, 0);
    glVertex3f(1, -1, 1);

    glColor3f(0, 0, 0);
    glVertex3f(1, -1, -1);

    glColor3f(1, 1, 1);
    glVertex3f(-1, -1, -1);

    glEnd();

    glFlush();
}
