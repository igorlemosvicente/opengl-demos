#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#include <stdio.h>
#include <stdlib.h>

const GLdouble NUMERAO = 1;

GLdouble pontos[][2] = {
    {0, 0},
    {-0.2, -0.3},
    {0, -0.2},
    {NUMERAO, 0}
};
const GLdouble PASSO = 0.005;
const int X = 0;
const int Y = 1;

GLdouble power(GLdouble value, GLdouble power_value) {
  if (!power_value) {
    return 1.0;
  }
  return value * power(value, power_value - 1);
}

void init() {
  glClearColor(1, 1, 1, 1);
  glPolygonMode(GL_FRONT, GL_FILL);
}

void render() {
  glLoadIdentity();
  glTranslated(-NUMERAO / 2.0, 0, 0);

  glColor3f(1.0, 0.0, 0.0);  // red
  glBegin(GL_POINTS);
  for (GLdouble t = 0.0; t < 1; t += PASSO) {
    GLdouble x = power((1 - t), 3)*pontos[0][X] + 3*t*power((1-t), 2)*pontos[1][X] + 3*power(t,2)*(1-t)*pontos[2][X] + power(t, 3)*pontos[3][X];
    GLdouble y = power((1 - t), 3)*pontos[0][Y] + 3*t*power((1-t), 2)*pontos[1][Y] + 3*power(t,2)*(1-t)*pontos[2][Y] + power(t, 3)*pontos[3][Y];
    glVertex2d(x, y);
  }
  glEnd();
}

void display(void) {
  glClear(GL_COLOR_BUFFER_BIT);
  render();
  glutSwapBuffers();
}

////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[]) {
  glutInit(&argc, argv);

  //glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

  glutInitWindowSize(600, 600);
  glutInitWindowPosition(250, 100);
  glutCreateWindow("");

  init();

  glutDisplayFunc(render);

  glutAttachMenu(GLUT_RIGHT_BUTTON);  //associa ao botao direito (0, 1, ou 2)

  glutIdleFunc(display);

  glutMainLoop();

  return 0;
}
