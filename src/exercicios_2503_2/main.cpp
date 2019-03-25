/**
 * This demo shows how to periodically call an update() function to create
 * animations over time. In this case, the animation is to rotate a red square.
 *
 * Author: Fernando Bevilacqua <fernando.bevilacqua@uffs.edu.br>
 * License: MIT
 */

#include <GL/glut.h>
#include <GL/gl.h>
#include <iostream>

#include "Retangulo3D.h"

// Constants to define the width/height of the window
const int WIDTH = 800;
const int HEIGHT = 800;

// Define how many frames per seconds we want our
// applications to run.
const unsigned int FRAMES_PER_SECOND = 30;
const unsigned int UPDATE_INTERVAL_MS = 1000 / FRAMES_PER_SECOND;

Retangulo3D g_retangulo(0, 0, 0, 1);

void drawRetangulo(Retangulo3D retangulo);

void display()
{
    // Clear the screen painting it with the white color
    glClearColor(1, 1, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    // Inform we want to make changes to the modelview matrix, starting
    // with no transformation at all.
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Move the camera away from the origin along the Z axis by 10 pixels.
    glTranslatef(0, 0, -10.0f);

    drawRetangulo(g_retangulo);

    glutSwapBuffers();
}

void drawRetangulo(Retangulo3D retangulo) {
    glColor3f(retangulo.red, retangulo.green, retangulo.blue);
    glPushMatrix();
        glTranslatef(retangulo.x, retangulo.y, retangulo.z);
        glRotated(retangulo.vertical_angle, 0, 1, 0);
        glRotated(retangulo.horizontal_angle, 1, 0, 0);
        glutWireCube(retangulo.size);
    glPopMatrix();
}

void update(int value)
{
    // Request a new frame rendering
    glutPostRedisplay();

    // Re-schedule the update() function to be called after a few
    // milliseconds again.
    glutTimerFunc(UPDATE_INTERVAL_MS, update, 0);
}

void keyboard(int key, int x, int y)
{

    GLfloat increment = 0.1;
    GLint angle_increment = 1;

    switch (key) {
        case GLUT_KEY_END:
            exit(0);
        case GLUT_KEY_UP: // Cima
            g_retangulo.y += increment;
            return;
        case GLUT_KEY_DOWN: // Baixo
            g_retangulo.y -= increment;
            return;
        case GLUT_KEY_LEFT: // Esquerda
            g_retangulo.x -= increment;
            return;
        case GLUT_KEY_RIGHT: // Direita
            g_retangulo.x += increment;
            return;
        case GLUT_KEY_F1:
            g_retangulo.vertical_angle += angle_increment;
            return;
        case GLUT_KEY_F2:
            g_retangulo.vertical_angle -= angle_increment;
            return;
        case GLUT_KEY_F3:
            g_retangulo.horizontal_angle += angle_increment;
            return;
        case GLUT_KEY_F4:
            g_retangulo.horizontal_angle -= angle_increment;
            return;
    }
}

void initView()
{
    // We want a window to the world that is a rectangle starting at (0,0)
    // and ending at (WIDTH, HEIGHT).
    glViewport(0, 0, (GLsizei)WIDTH, (GLsizei)HEIGHT);

    // Adjust the global projection (camera)
    glMatrixMode(GL_PROJECTION);

    // Reset any existing projection settings and adjust the field-of-view (FOV)
    glLoadIdentity();
    glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 200.0);

    // From now on, every transformation is to be applied on each object, e.g. modelview.
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Retangulo3D móvel");
    glutDisplayFunc(display);
    glutSpecialFunc(keyboard);

    initView();

    // Schedule the update() function to be called after a few
    // milliseconds (calculated as 1000 milliseconds divided by FPS).
    glutTimerFunc(UPDATE_INTERVAL_MS, update, 0);

    glutMainLoop();
    return 0;
}