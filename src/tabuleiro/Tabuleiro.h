//
// Created by aluno-uffs on 29/03/19.
//

#ifndef OPENGL_DEMOS_IGOR_TABULEIRO_H
#define OPENGL_DEMOS_IGOR_TABULEIRO_H

#include <GL/glut.h>
#include <GL/gl.h>


class Tabuleiro {
public:
  // x, y e z definem o canto superior esquerdo do tabuleiro
  GLint x, y, z, depth_angle;
  GLfloat primary_color_red, primary_color_green, primary_color_blue;
  GLfloat secondary_color_red, secondary_color_green, secondary_color_blue;

  Tabuleiro() : x(-4), y(4), z(0),
                depth_angle(-45),
                primary_color_red(1), primary_color_green(1), primary_color_blue(1),
                secondary_color_red(0), secondary_color_green(0), secondary_color_blue(0) {}

  void display() {
    glPushMatrix();
    glRotatef(depth_angle, 1, 0, 0);
    displayPrimaryColorSquares();
    displaySecondaryColorSquares();
    glPopMatrix();
  }

private:
  void displayPrimaryColorSquares() {
    glColor3f(primary_color_blue, primary_color_green, primary_color_blue);
    glPushMatrix();

    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 8; j++) {
        GLint new_x = (j % 2) + x + i * 2;
        GLint new_y = y - j;
        GLint new_z = z;
        glRecti(new_x, new_y, new_x + 1, new_y - 1);
      }
    }

    glPopMatrix();
  }

  void displaySecondaryColorSquares() {
    glColor3f(secondary_color_blue, secondary_color_green, secondary_color_blue);
    glPushMatrix();

    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 8; j++) {
        GLint new_x = !(j % 2) + x + i * 2;
        GLint new_y = y - j;
        GLint new_z = z;
        glRecti(new_x, new_y, new_x + 1, new_y - 1);
      }
    }

    glPopMatrix();
  }
};


#endif //OPENGL_DEMOS_IGOR_TABULEIRO_H
