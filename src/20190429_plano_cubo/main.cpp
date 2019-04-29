#include <GL/glut.h>
#include <GL/gl.h>

#define QUAD_SIZE 20

GLint depthFunc = GL_LESS;

void display() {
  // Set Background Color
  glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
  // Clear screen
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glDepthFunc(depthFunc);

  // Reset transformations
  glLoadIdentity();
  glTranslatef(0.0, 0.0, -10.0);

  glPushMatrix();
    glRotated(-60, 1.0, 0.0, 0.0);

    glPushMatrix();
      GLfloat cubeSize = 4.0;
      glTranslatef(-1.0, 0.0, cubeSize / 2.0);
      glColor3d(0.01, 0.20, 0.56);
      glutSolidCube(cubeSize);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(1.0, 5.0, cubeSize / 2.0);
      glColor3d(0.11, 0.60, 0.3);
      glutSolidCube(cubeSize);
    glPopMatrix();

    glPushMatrix();
      glColor3d(0.78, 0.31, 0.0);
      glRectf(-QUAD_SIZE, QUAD_SIZE, QUAD_SIZE, -QUAD_SIZE);
    glPopMatrix();

  glPopMatrix();


  glFlush();
  glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
  switch (key) {
    case '1':
      depthFunc = GL_ALWAYS;
      break;
    case '2':
      depthFunc = GL_LESS;
      break;
    case '3':
      depthFunc = GL_NEVER;
      break;
  }

  // Request display update
  glutPostRedisplay();
}

int main(int argc, char **argv) {
  // Initialize GLUT and process user parameters
  glutInit(&argc, argv);

  // Request double buffered true color window with Z-buffer
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

  glutInitWindowSize(700, 700);
  glutInitWindowPosition(100, 100);

  // Create window
  glutCreateWindow("OpenGL Cube");

  // Enable Z-buffer depth test
  glEnable(GL_DEPTH_TEST);

  // Callback functions
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
  glMatrixMode(GL_MODELVIEW);

  // Pass control to GLUT for events
  glutMainLoop();

  return 0;
}