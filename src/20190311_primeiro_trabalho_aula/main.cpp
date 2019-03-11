//
// Created by aluno-uffs on 11/03/19.
//

#include "Vetor.h"

/**
 * From: http://makble.com/draw-coordinate-lines-in-opengl
 */

#include <GL/glut.h>
#include <GL/gl.h>

#include <iostream>
#include <iomanip>

class RenderState {
public:
    float mouseX, mouseY, cameraX, cameraY;
    bool mouseLeftDown, mouseRightDown;
    RenderState() {
        this->mouseX = 0;
        this->mouseY = 0;
        this->mouseLeftDown = false;
        this->mouseRightDown = false;
        this->cameraX = 0.0f;
        this->cameraY = 0.0f;
    }

};

RenderState rs;

Vetor primeiro_ponteiro(0, 0, 0, 1.0, 0.0, 0.0, 0.001);
Vetor segundo_ponteiro(0, 0, 0, 0.0, 1.0, 0.0, 0.01);

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);

    RenderState* rsp = new RenderState();
    rs = *rsp;
}

void exit() {
    delete &rs;
    delete &primeiro_ponteiro;
    delete &segundo_ponteiro;
}

void drawCoordinates() {
    primeiro_ponteiro.roda();
    segundo_ponteiro.roda();
    primeiro_ponteiro.draw();
    segundo_ponteiro.draw();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glLoadIdentity();
    glTranslatef(0, 0, -10.0f);
    glRotatef(rs.cameraX, 1, 0, 0);
    glRotatef(rs.cameraY, 0, 1, 0);

    glScalef(1.0, 2.0, 1.0);
    glutWireCube(1.0);
    drawCoordinates();

    glFlush();

}

void mouseCallback(int button, int state, int x, int y)
{
    rs.mouseX = x;
    rs.mouseY = y;

    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            rs.mouseLeftDown = true;
        }
        else if (state == GLUT_UP)
            rs.mouseLeftDown = false;
    }
}

void mouseMotionCallback(int x, int y)
{
    if (rs.mouseLeftDown)
    {
        rs.cameraY += (x - rs.mouseX);
        rs.cameraX += (y - rs.mouseY);
        rs.mouseX = x;
        rs.mouseY = y;
    }
}


void idleCallback()
{
    glutPostRedisplay();
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutIdleFunc(idleCallback);
    glutMouseFunc(mouseCallback);
    glutMotionFunc(mouseMotionCallback);

    glViewport(0, 0, (GLsizei)500, (GLsizei)500);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
    glMatrixMode(GL_MODELVIEW);

    glutMainLoop();
    exit();
    return 0;
}