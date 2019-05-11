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

#define SCREEN_X 900
#define SCREEN_Y 300

#define RECT_SIZE 10
#define TEXT_COORD 2

#define MAX_TEXTURES 2


Bmp *img1, *img2, *img3;
unsigned char *data1, *data2, *data3;
GLuint textureID[MAX_TEXTURES];

float ang = 0;

void buildTextures();


void init() {
  glClearColor(0, 0, 0, 1);

  glShadeModel(GL_SMOOTH);
  glDepthFunc(GL_LESS);

  glEnable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);

  img1 = new Bmp("/home/aluno-uffs/opengl-demos-igor/src/20190506_textura/floor.bmp");
  img1->convertBGRtoRGB();
  data1 = img1->getImage();

  img2 = new Bmp("/home/aluno-uffs/opengl-demos-igor/src/20190506_textura/sky.bmp");
  img2->convertBGRtoRGB();
  data2 = img2->getImage();

  img3 = new Bmp("/home/aluno-uffs/opengl-demos-igor/src/20190506_textura/box.bmp");
  img3->convertBGRtoRGB();
  data3 = img3->getImage();

  if (data1 != NULL) {
    glEnable(GL_TEXTURE);
    glEnable(GL_TEXTURE_2D);

    buildTextures();
  }
}

void buildTextures() {
  //----------------------------------------------------------------------------------
  //GL_REPEAT e mipmap
  glGenTextures(1, &textureID[0]);
  glBindTexture(GL_TEXTURE_2D, textureID[0]);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  gluBuild2DMipmaps(GL_TEXTURE_2D,
                    GL_RGB,
                    img1->getWidth(),
                    img1->getHeight(),
                    GL_RGB,
                    GL_UNSIGNED_BYTE,
                    data1);
//----------------------------------------------------------------------------------
  //GL_REPEAT e mipmap
  glGenTextures(1, &textureID[1]);
  glBindTexture(GL_TEXTURE_2D, textureID[1]);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  gluBuild2DMipmaps(GL_TEXTURE_2D,
                    GL_RGB,
                    img2->getWidth(),
                    img2->getHeight(),
                    GL_RGB,
                    GL_UNSIGNED_BYTE,
                    data2);
  //----------------------------------------------------------------------------------
  //GL_REPEAT e mipmap
  glGenTextures(1, &textureID[2]);
  glBindTexture(GL_TEXTURE_2D, textureID[2]);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  gluBuild2DMipmaps(GL_TEXTURE_2D,
                    GL_RGB,
                    img3->getWidth(),
                    img3->getHeight(),
                    GL_RGB,
                    GL_UNSIGNED_BYTE,
                    data3);
  //----------------------------------------------------------------------------------
//  //GL_CLAMP e glTextImage2D. Soh aceita texturas em potencia de 2.
//  glGenTextures( 1, &textureID[1] );
//  glBindTexture( GL_TEXTURE_2D, textureID[1] );
//
//  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
//  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
//
//  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//
//  glTexImage2D(GL_TEXTURE_2D,
//               0,
//               GL_RGB,
//               img2->getWidth(),
//               img2->getHeight(),
//               0,
//               GL_RGB,
//               GL_UNSIGNED_BYTE,
//               data2);

  //----------------------------------------------------------------------------------
  //geracao automatica de coordenadas
//  glGenTextures( 1, &textureID[2] );
//  glBindTexture( GL_TEXTURE_2D, textureID[2] );
//
//  float escala = 1.0 / 10;
//  float p1[4] = { escala, 0,      0, 0 };
//  float p2[4] = { 0,      escala, 0, 0 };
//  glTexGenfv(GL_S, GL_OBJECT_PLANE, p1);
//  glTexGenfv(GL_T, GL_OBJECT_PLANE, p2);
//
//  glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
//  glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
//
//  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//
//  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
//  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//  gluBuild2DMipmaps(GL_TEXTURE_2D,
//                    GL_RGB,
//                    img1->getWidth(),
//                    img1->getHeight(),
//                    GL_RGB,
//                    GL_UNSIGNED_BYTE,
//                    data1);
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

  glPushMatrix();
  glLoadIdentity();
  glTranslated(0, 0, -40);

  glBindTexture(GL_TEXTURE_2D, textureID[2]);

  glDisable(GL_TEXTURE_GEN_S);
  glDisable(GL_TEXTURE_GEN_T);
  glBegin(GL_QUADS);
  glTexCoord2f(0, 0);
  glVertex3f(-10, -10, 5);

  glTexCoord2f(TEXT_COORD, 0);
  glVertex3f(10, -10, 5);

  glTexCoord2f(TEXT_COORD, TEXT_COORD);
  glVertex3f(10, 10, 5);

  glTexCoord2f(0, TEXT_COORD);
  glVertex3f(-10, 10, 5);
  glEnd();
  glPopMatrix();

  int indice_textura = 0;
  glPushMatrix();
  glLoadIdentity();
  glTranslated(0, 0, -40);

  glBindTexture(GL_TEXTURE_2D, textureID[indice_textura]);

  glDisable(GL_TEXTURE_GEN_S);
  glDisable(GL_TEXTURE_GEN_T);
  glBegin(GL_QUADS);
  glTexCoord2f(0, 0);
  glVertex3f(-10, 0, 0);

  glTexCoord2f(TEXT_COORD, 0);
  glVertex3f(10, 0, 0);

  glTexCoord2f(TEXT_COORD, TEXT_COORD);
  glVertex3f(4.8, -1.5, 35);

  glTexCoord2f(0, TEXT_COORD);
  glVertex3f(-4.8, -1.5, 35);
  glEnd();
  glPopMatrix();

  indice_textura = 1;
  glPushMatrix();
  glLoadIdentity();
  glTranslated(0, 0, -40);

  glBindTexture(GL_TEXTURE_2D, textureID[indice_textura]);

  glDisable(GL_TEXTURE_GEN_S);
  glDisable(GL_TEXTURE_GEN_T);
  glBegin(GL_QUADS);
  glTexCoord2f(0, 0);
  glVertex3f(-10, 0, 0);

  glTexCoord2f(TEXT_COORD, 0);
  glVertex3f(10, 0, 0);

  glTexCoord2f(TEXT_COORD, TEXT_COORD);
  glVertex3f(4.8, 1.5, 35);

  glTexCoord2f(0, TEXT_COORD);
  glVertex3f(-4.8, 1.5, 35);
  glEnd();
  glPopMatrix();
//    }
//    else    //com geracao automatica de coordenadas e textura
//    {
//      glEnable(GL_TEXTURE_GEN_S);
//      glEnable(GL_TEXTURE_GEN_T);
//      glBegin(GL_QUADS);
//      glVertex3f(0, 0, 0);
//      glVertex3f(RECT_SIZE, 0, 0);
//      glVertex3f(RECT_SIZE, RECT_SIZE, 0);
//      glVertex3f(0, RECT_SIZE, 0);
//      glEnd();
//      //glutSolidTeapot(2);
//    }

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
