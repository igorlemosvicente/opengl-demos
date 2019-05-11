/**
*   Programa para ilustrar:
*   - Uso da textura
*   - carregamento de arquivos BMP

*   Autor: Cesar Tadeu Pozzer
*   UFSM - 15/06/2007
*
*   pozzer@inf.ufsm.br
*   pozzer3@gmail.com
*
**/

#include <GL/glut.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "Bmp.h"

#define SCREEN_X 800
#define SCREEN_Y 800

#define RECT_SIZE 10
#define TEXT_COORD 2

#define MAX_TEXTURES 2


//Bmp *img1, *img2, *img3;
//unsigned char *data1, *data2, *data3;
//GLuint textureID[MAX_TEXTURES];
GLuint texturas[1];
unsigned char *box_image;
Bmp *box_bmp_loader;

float ang = 0;

void buildTextures();


void init() {
  glClearColor(0, 0, 0, 1);

  glShadeModel(GL_SMOOTH);
  glDepthFunc(GL_LESS);

  glEnable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);

  box_bmp_loader = new Bmp("/home/aluno-uffs/opengl-demos-igor/src/20190506_textura/box.bmp");
  box_bmp_loader->convertBGRtoRGB();
  box_image = box_bmp_loader->getImage();


  if (box_image != NULL) {
    glEnable(GL_TEXTURE);
    glEnable(GL_TEXTURE_2D);

    buildTextures();
  }
}

void buildTextures() {
  //GL_REPEAT e mipmap
  glGenTextures(1, texturas);
  glBindTexture(GL_TEXTURE_2D, texturas[0]);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  gluBuild2DMipmaps(GL_TEXTURE_2D,
                    GL_RGB,
                    box_bmp_loader->getWidth(),
                    box_bmp_loader->getHeight(),
                    GL_RGB,
                    GL_UNSIGNED_BYTE,
                    box_image);
}

////////////////////////////////////////////////////////////////////////////////////////
void display(void) {
  float abertura = 35;
  float znear = 1;
  float zfar = 200;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(abertura, SCREEN_X / SCREEN_Y, znear, zfar);

  glMatrixMode(GL_MODELVIEW);

  glLoadIdentity();
  glTranslated(0, 0, -10);
  glPushMatrix();

  glBindTexture(GL_TEXTURE_2D, texturas[0]);

  glDisable(GL_TEXTURE_GEN_S);
  glDisable(GL_TEXTURE_GEN_T);
  glBegin(GL_QUADS);

  GLfloat tex_coord = 1.5;

  glTexCoord2f(0.5, 0);
  glVertex3f(0.0f, 0.0f, 0);

  glTexCoord2f(1.5, 0);
  glVertex3f(1.0f, 0.0f, 0);

  glTexCoord2f(1.5, 1);
  glVertex3f(1.0f, 1.0f, 0);

  glTexCoord2f(0.5, 1);
  glVertex3f(0.0f, 1.0f, 0);
  glEnd();
  glPopMatrix();

  glutSwapBuffers();

}

////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[]) {
  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

  glutInitWindowSize(SCREEN_X, SCREEN_Y);
  glutInitWindowPosition(500, 500);
  glutCreateWindow("Texture Demo");
  init();

  glutDisplayFunc(display);
  glutIdleFunc(display);

  glutMainLoop();
  return 0;
}
