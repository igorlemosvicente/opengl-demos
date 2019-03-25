//
// Created by aluno-uffs on 25/03/19.
//

#ifndef OPENGL_DEMOS_IGOR_QUADRADO_H
#define OPENGL_DEMOS_IGOR_QUADRADO_H

#include <GL/glut.h>
#include <GL/gl.h>

class Quadrado {
public:
    GLfloat x, y, z, red, green, blue, size;

    Quadrado(GLfloat x_, GLfloat y_, GLfloat z_, GLfloat size_) :
        x(x_), y(y_), z(z_), red(1), green(1), blue(0), size(size_) {}
};


#endif //OPENGL_DEMOS_IGOR_QUADRADO_H
