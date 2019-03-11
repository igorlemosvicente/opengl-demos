//
// Created by aluno-uffs on 11/03/19.
//

#ifndef OPENGL_DEMOS_IGOR_VETOR_H
#define OPENGL_DEMOS_IGOR_VETOR_H

#include <GL/glut.h>
#include <GL/gl.h>

#include <iostream>
#include <iomanip>


class Vetor {
public:
    float x, y, z;

    Vetor(float _x, float _y, float _z) {
        x = _x;
        y = _y;
        z = _z;
    }

    void draw() {
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_LINES);

        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(this->x, this->y, this->z);
        glEnd();
    }

    void integracao_euler(Vetor vetor_velocidade) {
        this->x += vetor_velocidade.x;
        this->y += vetor_velocidade.y;
        this->z += vetor_velocidade.z;
    }

};


#endif //OPENGL_DEMOS_IGOR_VETOR_H
