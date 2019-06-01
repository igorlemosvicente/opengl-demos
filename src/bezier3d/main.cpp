#include <GL/freeglut.h>
#include <iostream>

#include "Point.h"

using namespace std;

GLdouble pontos[][3] = {
    {0, 0, 0},
    {1, 5, 1},
    {0, -0.2, 0.5},
    {1, 1, 1}
};
GLdouble coordenadas_bola[] = {0.9, 0.9, 1};
GLdouble t_bola = 0;
GLint segmento_bola = 1;
const GLdouble PASSO = 0.01;
const int X = 0;
const int Y = 1;
const int Z = 2;
GLint ponto_para_atualizar = 0;
char left_mouse_down = 0;

GLdouble power(GLdouble value, GLdouble power_value) {
  if (!power_value) {
    return 1.0;
  }
  return value * power(value, power_value - 1);
}
const unsigned int FRAMES_PER_SECOND = 30;
const unsigned int UPDATE_INTERVAL_MS = 1000 / FRAMES_PER_SECOND;
GLint gTimeLastUpdateMs;

// global variables
static struct {
  // current parameters for controlling glulookat
  double alpha, beta, dist;
  // viewing mode state (depending on which mouse button is being used)
  enum {
    NONE, ROTATING, ZOOMING
  } viewingMode;
  // last mouse position
  int mouseX, mouseY;
  // current recursion for drawing the spheres
} globals;

// draw checkerboard floor
static void drawFloor(void) {
  int n = 10;
  double x1 = 0, x2 = 10, y1 = 0, y2 = 10;
  double dx = (x2 - x1) / n, dy = (y2 - y1) / n;
  glBegin(GL_QUADS);

  // same normal for everything
  glNormal3d(0, 0, 1);

  for (int ix = 0; ix < n; ix++) {
    for (int iy = 0; iy < n; iy++) {
      if ((ix + iy) % 2)
        glColor3f(1, 1, 1);
      else
        glColor3f(1, 0, 0);

      glVertex3d(x1 + ix * dx, y1 + iy * dy, 0);
      glVertex3d(x1 + (ix + 1) * dx, y1 + iy * dy, 0);
      glVertex3d(x1 + (ix + 1) * dx, y1 + (iy + 1) * dy, 0);
      glVertex3d(x1 + ix * dx, y1 + (iy + 1) * dy, 0);
    }
  }

  glEnd();
}

// function called by GLUT whenever a redraw is needed
static void display() {
  // clear the window with the predefined color
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // setup viewing transformation
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  double r = globals.dist;
  double a = globals.alpha * M_PI / 180.0;
  double b = globals.beta * M_PI / 180.0;
  Point p(r * cos(a) * cos(b), r * sin(a) * cos(b), r * sin(b));
  Point c(5, 5, 1.5);
  p = p + c;

  GLfloat lightPos[] = {10.0, 10.0, 10.0, 1.0};
  glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

  gluLookAt(p.x(), p.y(), p.z(), c.x(), c.y(), c.z(), 0, 0, 1);

  drawFloor();

  GLdouble primeiro_ponto_bola[] = {pontos[0][X] + segmento_bola, pontos[0][Y] + segmento_bola, pontos[0][Z] + segmento_bola};
  GLdouble segundo_ponto_bola[] = {pontos[1][X] + segmento_bola, pontos[1][Y] + segmento_bola, pontos[1][Z] + segmento_bola};
  GLdouble terceiro_ponto_bola[] = {pontos[2][X] + segmento_bola, pontos[2][Y] + segmento_bola, pontos[2][Z] + segmento_bola};
  GLdouble ultimo_ponto_bola[] = {pontos[3][X] + segmento_bola, pontos[3][Y] + segmento_bola, pontos[3][Z] + segmento_bola};

  if (segmento_bola == 4) {
    ultimo_ponto_bola[X] = pontos[0][X] + 1;
    ultimo_ponto_bola[Y] = pontos[0][Y] + 1;
    ultimo_ponto_bola[Z] = pontos[0][Z] + 1;
  }

  coordenadas_bola[X] = power((1 - t_bola), 3) * primeiro_ponto_bola[X] + 3 * t_bola * power((1 - t_bola), 2) * segundo_ponto_bola[X] +
               3 * power(t_bola, 2) * (1 - t_bola) * terceiro_ponto_bola[X] + power(t_bola, 3) * ultimo_ponto_bola[X];
  coordenadas_bola[Y] = power((1 - t_bola), 3) * primeiro_ponto_bola[Y] + 3 * t_bola * power((1 - t_bola), 2) * segundo_ponto_bola[Y] +
               3 * power(t_bola, 2) * (1 - t_bola) * terceiro_ponto_bola[Y] + power(t_bola, 3) * ultimo_ponto_bola[Y];
  coordenadas_bola[Z] = power((1 - t_bola), 3) * primeiro_ponto_bola[Z] + 3 * t_bola * power((1 - t_bola), 2) * segundo_ponto_bola[Z] +
               3 * power(t_bola, 2) * (1 - t_bola) * terceiro_ponto_bola[Z] + power(t_bola, 3) * ultimo_ponto_bola[Z];
  t_bola += PASSO;
  if (t_bola > 1) {
    t_bola = 0;
    segmento_bola = segmento_bola + 1;
    if (segmento_bola == 5) {
      segmento_bola = 1;
    }
  }

  glPushMatrix();
  glPointSize(30);
  glBegin(GL_POINTS);
  glColor3f(1.0, 0.0, 1.0);
  glVertex3dv(coordenadas_bola);
  glEnd();
  glPopMatrix();

  glPushMatrix();
  // pontos de controle
  glPointSize(20);
  glBegin(GL_POINTS);
  for (int i = 0; i < 4; i++) {
    if (ponto_para_atualizar == i) {
      glColor3f(0.0, 0.0, 1.0);
    } else {
      glColor3f(0.0, 0.0, 1.0);
    }
    glVertex3d(pontos[i][X], pontos[i][Y], pontos[i][Z]);
  }
  glEnd();
  glPopMatrix();


  glPushMatrix();
  // pontos da reta
  glColor3f(0, 1.0, 0.0);  // red
  glPointSize(5);
  glBegin(GL_POINTS);
  for (GLint i = 1; i < 5; i++) {
    for (GLdouble t = 0.0; t < 1; t += PASSO) {
      GLdouble primeiro_ponto[] = {pontos[0][X] + i, pontos[0][Y] + i, pontos[0][Z] + i};
      GLdouble segundo_ponto[] = {pontos[1][X] + i, pontos[1][Y] + i, pontos[1][Z] + i};
      GLdouble terceiro_ponto[] = {pontos[2][X] + i, pontos[2][Y] + i, pontos[2][Z] + i};
      GLdouble ultimo_ponto[] = {pontos[3][X] + i, pontos[3][Y] + i, pontos[3][Z] + i};

      if (i == 4) {
        ultimo_ponto[X] = pontos[0][X] + 1;
        ultimo_ponto[Y] = pontos[0][Y] + 1;
        ultimo_ponto[Z] = pontos[0][Z] + 1;
      }

      GLdouble x = power((1 - t), 3) * primeiro_ponto[X] + 3 * t * power((1 - t), 2) * segundo_ponto[X] +
                   3 * power(t, 2) * (1 - t) * terceiro_ponto[X] + power(t, 3) * ultimo_ponto[X];
      GLdouble y = power((1 - t), 3) * primeiro_ponto[Y] + 3 * t * power((1 - t), 2) * segundo_ponto[Y] +
                   3 * power(t, 2) * (1 - t) * terceiro_ponto[Y] + power(t, 3) * ultimo_ponto[Y];
      GLdouble z = power((1 - t), 3) * primeiro_ponto[Z] + 3 * t * power((1 - t), 2) * segundo_ponto[Z] +
                   3 * power(t, 2) * (1 - t) * terceiro_ponto[Z] + power(t, 3) * ultimo_ponto[Z];
      glVertex3d(x, y, z);
    }
  }
  glEnd();
  glPopMatrix();

  // make sure everything gets drawn
  glFlush();
}

// we recompute projection matrix on every resize, and reset the viewport
static void resizeCB(int w, int h) {
  // setup perspective transformation
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60, double(w) / h, 0.1, 100);
  //glOrtho(-10.0, 10.0, -10.0, 10.0, 5, 100);

  glViewport(0, 0, w, h);
}

// when mouse button is clicked, we determine which viewing mode to
// initialize and also remember where the mouse was clicked
static void mouseClickCB(int button, int state, int x, int y) {
  globals.mouseX = x;
  globals.mouseY = y;

  if (state == GLUT_UP) {
    globals.viewingMode = globals.NONE;
  } else if (button == GLUT_LEFT_BUTTON) {
    globals.viewingMode = globals.ROTATING;
  } else if (button == GLUT_MIDDLE_BUTTON) {
    globals.viewingMode = globals.ZOOMING;
  } else {
    globals.viewingMode = globals.NONE;
  }
}

// when user drags the mouse, we either rotate or zoom
static void mouseMotionCB(int x, int y) {
  int dx = x - globals.mouseX;
  int dy = y - globals.mouseY;
  globals.mouseX = x;
  globals.mouseY = y;

  if (globals.viewingMode == globals.ROTATING) {
    globals.alpha -= dx / 10.0;
    globals.beta += dy / 10.0;
    if (globals.beta < -80) globals.beta = -80;
    if (globals.beta > 80) globals.beta = 80;
//    glutPostRedisplay();
  } else if (globals.viewingMode == globals.ZOOMING) {
    globals.dist = std::max(1.0, globals.dist - dy / 10.0);
//    glutPostRedisplay();
  }
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

  // Request a new frame rendering
  glutPostRedisplay();

  // Re-schedule the update() function to be called after a few
  // milliseconds again.
  glutTimerFunc(UPDATE_INTERVAL_MS, internalUpdate, 0);
}


static void init() {
  globals.alpha = 30;
  globals.beta = 30;
  globals.dist = 10;
  globals.viewingMode = globals.NONE;

  // initial window size
  glutInitWindowSize(800, 600);

  // what buffers we need
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB
                      | GLUT_MULTISAMPLE | GLUT_DEPTH);

  // create a window
  glutCreateWindow("MD2 Viewer");

  // register callbacks
  glutDisplayFunc(display);
  glutReshapeFunc(resizeCB);
  glutMouseFunc(mouseClickCB);
  glutMotionFunc(mouseMotionCB);

  // use black as the background color
  glClearColor(0, 0, 0, 0);

  // enable depth buffer
  glEnable(GL_DEPTH_TEST);

  // this is for drawing transparencies
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // enable antialiasing (just in case)
  //    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
  glEnable(GL_POLYGON_SMOOTH);

  // enable lighting
  glEnable(GL_LIGHTING);

  // enable use of glColor() to specify ambient & diffuse material properties
  glEnable(GL_COLOR_MATERIAL);
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

  // set some common light & material properties, which don't have to
  // be re-specified later
  glEnable(GL_LIGHT0);
  GLfloat ambientLight[] = {0.1, 0.1, 0.1, 1.0};
  glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
  GLfloat specularLight[] = {1.0, 1.0, 1.0, 1.0};
  glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
  GLfloat specularColor[] = {0.7, 0.7, 0.7, 1.0};
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specularColor);
  GLfloat shininess[] = {95.0};
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
  glutTimerFunc(UPDATE_INTERVAL_MS, internalUpdate, 0);

  // since we are going to use scaling, and possibly non-uniform, we'll
  // ask OpenGL to re-normalize our normals
  glEnable(GL_NORMALIZE);
}

// main function
int main(int argc, char **argv) {
  glutInit(&argc, argv);
  init();
  glutMainLoop();
  return 0;
}