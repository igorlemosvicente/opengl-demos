//
// Created by Igor Lemos Vicente on 11/03/19.
//

#ifndef OPENGL_DEMOS_IGOR_VETOR_H
#define OPENGL_DEMOS_IGOR_VETOR_H

#include <GL/glut.h>
#include <GL/gl.h>

#include <iostream>
#include <iomanip>

#include <math.h>

#define EPS 1e-5


class Vetor {
public:
    float x, y, z;
    float mudanca, controle;
    float red, green, blue;

    Vetor(float _x, float _y, float _z, float _red, float _green, float _blue, float _mudanca) {
        x = _x;
        y = _y;
        z = _z;
        red = _red;
        green = _green;
        blue = _blue;
        controle = 0;
        mudanca =_mudanca;
    }

    void draw() {
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_LINES);

        glVertex3f(this->red, this->green, this->blue);
        glVertex3f(this->x, this->y, this->z);
        glEnd();
    }

    void integracao_euler(Vetor vetor_velocidade) {
        this->x += vetor_velocidade.x;
        this->y += vetor_velocidade.y;
        this->z += vetor_velocidade.z;
    }

    void roda() {
        if (10000.0 - this->controle < EPS) {
            this->controle = 0.0;
        }

        this->controle += this->mudanca;
        this->x = 2 * sin(controle);
        this->y = cos(controle);
    }

};


#endif //OPENGL_DEMOS_IGOR_VETOR_H
