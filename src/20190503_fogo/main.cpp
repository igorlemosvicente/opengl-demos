/**
 * From: http://makble.com/draw-coordinate-lines-in-opengl
 */

#include <GL/glut.h>
#include <GL/gl.h>

#include <iostream>
#include <iomanip>


#include <time.h>
#include <stdlib.h>


//int r = rand();

#include "FireParticle.h"

#define NUMBER_PARTICLES 100

const unsigned int FRAMES_PER_SECOND = 30;
const unsigned int UPDATE_INTERVAL_MS = 1000 / FRAMES_PER_SECOND;

int gTimeLastUpdateMs = 0;

FireParticle fires[NUMBER_PARTICLES];

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

void init(void)
{
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glShadeModel(GL_FLAT);

  RenderState* rsp = new RenderState();
  rs = *rsp;
}

void exit() {
  delete &rs;
}

void drawCoordinates() {

  // draw some lines
//  glColor3f(1.0, 0.0, 0.0); // red x
//  glBegin(GL_LINES);
//  // x aix
//
//  glVertex3f(-4.0, 0.0f, 0.0f);
//  glVertex3f(4.0, 0.0f, 0.0f);
//
//  glVertex3f(4.0, 0.0f, 0.0f);
//  glVertex3f(3.0, 1.0f, 0.0f);
//
//  glVertex3f(4.0, 0.0f, 0.0f);
//  glVertex3f(3.0, -1.0f, 0.0f);
//  glEnd();
//
//  // y
//  glColor3f(0.0, 1.0, 0.0); // green y
//  glBegin(GL_LINES);
//  glVertex3f(0.0, -4.0f, 0.0f);
//  glVertex3f(0.0, 4.0f, 0.0f);
//
//  glVertex3f(0.0, 4.0f, 0.0f);
//  glVertex3f(1.0, 3.0f, 0.0f);
//
//  glVertex3f(0.0, 4.0f, 0.0f);
//  glVertex3f(-1.0, 3.0f, 0.0f);
//  glEnd();
//
//  // z
//  glColor3f(0.0, 0.0, 1.0); // blue z
//  glBegin(GL_LINES);
//  glVertex3f(0.0, 0.0f, -4.0f);
//  glVertex3f(0.0, 0.0f, 4.0f);
//
//
//  glVertex3f(0.0, 0.0f, 4.0f);
//  glVertex3f(0.0, 1.0f, 3.0f);
//
//  glVertex3f(0.0, 0.0f, 4.0f);
//  glVertex3f(0.0, -1.0f, 3.0f);
//  glEnd();

}

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1.0, 1.0, 1.0);
  glLoadIdentity();
  glTranslatef(0, 0, -10.0f);
  glRotatef(rs.cameraX, 1, 0, 0);
  glRotatef(rs.cameraY, 0, 1, 0);

//  glScalef(1.0, 2.0, 1.0);
//  glutWireCube(1.0);
//  drawCoordinates();

  for (int i = 0; i < NUMBER_PARTICLES; i++) {
    fires[i].display();
  }

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

void internalUpdate(int value)
{
  int timeNowMs = glutGet(GLUT_ELAPSED_TIME);
  double deltaSeconds = (timeNowMs - gTimeLastUpdateMs) / 1000.0;

  // Save the time update() was called
  gTimeLastUpdateMs = timeNowMs;
  //std::cout << "timeNOw = " << timeNowMs << ", deltaSeconds = " << deltaSeconds << std::endl;
  // Invoke our update() function
  //  update(deltaSeconds);
  for (int i = 0; i < NUMBER_PARTICLES; i++) {
    fires[i].update();
  }

  // Request a new frame rendering
  glutPostRedisplay();

  // Re-schedule the update() function to be called after a few
  // milliseconds again.
  glutTimerFunc(UPDATE_INTERVAL_MS, internalUpdate, 0);
}


int main(int argc, char** argv)
{
  srand(time(NULL));   // Initialization, should only be called once.
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

  glutTimerFunc(UPDATE_INTERVAL_MS, internalUpdate, 0);

  glutMainLoop();
  exit();
  return 0;
}