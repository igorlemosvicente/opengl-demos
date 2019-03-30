#include <GL/glut.h>
#include <GL/gl.h>
#include "Tabuleiro.h"

const unsigned int FRAMES_PER_SECOND = 30;
const unsigned int UPDATE_INTERVAL_MS = 1000 / FRAMES_PER_SECOND;
const int WIDTH = 800;
const int HEIGHT = 800;

int gTimeLastUpdateMs = 0;

Tabuleiro primeira_entidade;

void display() {
  glClearColor(1, 0, 1, 0.5);
  glClear(GL_COLOR_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0, 0, -20);

  primeira_entidade.display();

  glutSwapBuffers();
}

void update(int value) {
  int timeNowMs = glutGet(GLUT_ELAPSED_TIME);
//  double deltaSeconds = (timeNowMs - gTimeLastUpdateMs) / 1000.0;

  // Save the time update() was called
  gTimeLastUpdateMs = timeNowMs;
  //std::cout << "timeNOw = " << timeNowMs << ", deltaSeconds = " << deltaSeconds << std::endl;
  // Invoke our update() function
//  update(deltaSeconds);

  // Request a new frame rendering
  glutPostRedisplay();

  // Re-schedule the update() function to be called after a few
  // milliseconds again.
  glutTimerFunc(UPDATE_INTERVAL_MS, update, 0);
}


void initView() {
  // We want a window to the world that is a rectangle starting at (0,0)
  // and ending at (WIDTH, HEIGHT).
  glViewport(0, 0, (GLsizei) WIDTH, (GLsizei) HEIGHT);

  // Adjust the global projection (camera)
  glMatrixMode(GL_PROJECTION);

  // Reset any existing projection settings and adjust the field-of-view (FOV)
  glLoadIdentity();
  glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 200.0);

  // From now on, every transformation is to be applied on each object, e.g. modelview.
  glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(WIDTH, HEIGHT);
  glutCreateWindow("Tabuleiro - Aula de 29 de março de 2019");

  // Register a few callback functions
  glutDisplayFunc(display);
//  glutKeyboardFunc(keyboard);
//  glutMouseFunc(mouse);

  initView();

  // Schedule the update() function to be called after a few
  // milliseconds (calculated as 1000 milliseconds divided by FPS).
  glutTimerFunc(UPDATE_INTERVAL_MS, update, 0);

  glutMainLoop();
  return 0;
}