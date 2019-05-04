//
// Created by aluno-uffs on 03/05/19.
//

#ifndef OPENGL_DEMOS_IGOR_FIREPARTICLE_H
#define OPENGL_DEMOS_IGOR_FIREPARTICLE_H

#include <math.h>


class FireParticle {
  GLfloat x, y, z, maximum_size;
  GLfloat alpha, beta;
  GLfloat lerp_increments = 0.05;

public:
  FireParticle(GLfloat _x, GLfloat _y, GLfloat _z, GLfloat _maximum_size) :
  x(_x),
  y(_y),
  z(_z),
  maximum_size(_maximum_size),
  alpha(0),
  beta(0) {}

  void display() {
    glPushMatrix();
    glColor3f(1 - beta, alpha - beta, 0);
    glTranslatef(x, y * (alpha + beta), z);
    glutSolidSphere(sin(alpha + beta) * maximum_size, 50, 50);
    glPopMatrix();
  }

  void update() {
    if (alpha < 1.0) {
      alpha += lerp_increments;
    } else if (beta < 1.0) {
      beta += lerp_increments;
    } else {
      alpha = beta = 0.0;
    }
  }
};


#endif //OPENGL_DEMOS_IGOR_FIREPARTICLE_H
