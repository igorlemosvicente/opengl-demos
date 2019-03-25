/**
 * 3 - Faça um retângulo (glutWireCube()) aumentar e diminuir de tamanho a cada 3 segundos.
 * Dica: demo glut-update-delta
 */



#include <GL/glut.h>
#include <GL/gl.h>
#include <iostream>
#include <math.h>

// Constants to define the width/height of the window
const int WIDTH = 800;
const int HEIGHT = 800;

// Define how many frames per seconds we want our
// applications to run.
const unsigned int FRAMES_PER_SECOND = 30;
const unsigned int UPDATE_INTERVAL_MS = 1000 / FRAMES_PER_SECOND;

// Control when was the last update() called.
int gTimeLastUpdateMs = 0;

// Control the value of each color channel used to display a square.
GLfloat gValueR = 0.0f;
GLfloat gValueG = 0.0f;
GLfloat gValueB = 0.0f;

GLdouble pulsing_value = 0;

void display()
{
    // Move the camera away from the origin along the Z axis by 10 pixels.
    glTranslatef(0, 0, -10.0f);

    glColor3f(0.4f, 0.3f, 0.5f);
    glPushMatrix();
        glRotated(15, 0, 1, 0);
        glRotated(15, 1, 0, 0);
        glutWireCube(pulsing_value);
    glPopMatrix();
}

// This function is called periodically. The param delta contains the time
// difference between the current and the last frame, in seconds.
void update(double delta)
{
    pulsing_value = delta * 100;

    // Update the color of the square based on the time
    gValueR += (GLfloat)delta;
    gValueG += (GLfloat)(delta * 1.3);
    gValueB += (GLfloat)(delta * 1.5);
}

void keyboard(unsigned char key, int x, int y)
{
    if (key == 27) {
        // ESC key
        exit(0);
    }
}

void internalDisplay()
{
    // Clear the screen painting it with the white color
    glClearColor(1, 1, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    // Inform we want to make changes to the modelview matrix, starting
    // with no transformation at all.
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Call our display() function
    display();

    // Start the rendering on a new frame
    glutSwapBuffers();
}

void internalUpdate(int value)
{
    int timeNowMs = glutGet(GLUT_ELAPSED_TIME);
    double deltaSeconds = (timeNowMs - gTimeLastUpdateMs) / 1000.0;

    // Save the time update() was called
    gTimeLastUpdateMs = timeNowMs;

    update(deltaSeconds);

    // Request a new frame rendering
    glutPostRedisplay();

    // Re-schedule the update() function to be called after a few
    // milliseconds again.
    glutTimerFunc(UPDATE_INTERVAL_MS, internalUpdate, 0);
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
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Pulsing Cube");

    // Register a few callback functions
    glutDisplayFunc(internalDisplay);
    glutKeyboardFunc(keyboard);

    initView();

    // Schedule the update() function to be called after a few
    // milliseconds (calculated as 1000 milliseconds divided by FPS).
    glutTimerFunc(UPDATE_INTERVAL_MS, internalUpdate, 0);

    glutMainLoop();
    return 0;
}