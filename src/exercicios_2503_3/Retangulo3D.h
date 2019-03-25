//
// Created by aluno-uffs on 25/03/19.
//

#ifndef OPENGL_DEMOS_IGOR_RETANGULO3D_H
#define OPENGL_DEMOS_IGOR_RETANGULO3D_H


class Retangulo3D {
public:
    GLfloat x, y, z, red, green, blue, size;
    GLint vertical_angle, horizontal_angle;

    Retangulo3D(GLfloat x_, GLfloat y_, GLfloat z_, GLfloat size_) :
    x(x_), y(y_), z(z_), red(1), green(0), blue(1), size(size_), vertical_angle(0), horizontal_angle(0) {}
};


#endif //OPENGL_DEMOS_IGOR_RETANGULO3D_H
