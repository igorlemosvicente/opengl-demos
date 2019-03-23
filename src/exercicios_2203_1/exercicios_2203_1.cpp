/**
 * 1 - Faça um programa que mostra um quadrado girando na origem. Ao redor dele, outro quadrado gira a uma certa distância da origem, porém rotacionando no próprio eixo em sentido contrário.
 * Dica: rotating-cube e rotation
 */


#include <GL/glut.h>
#include <math.h>

#define SCREEN_X 500
#define SCREEN_Y 500

#define PI 3.14

GLint angGraus = 0;

////////////////////////////////////////////////////////////////////////////////////////
void display(void) {
    if (angGraus > 360) {
        angGraus = 0;
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity( );
    glOrtho(-100, 100, 100, -100, 1, 1000);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity( );
    gluLookAt(0, 0, 2,  //from. Posicao onde a camera esta posicionada
              0, 0, 0,  //to. Posicao absoluta onde a camera esta vendo
              0, 1, 0); //up. Vetor Up.

//    float raio = 30; //raio do virabrequim
//
//    //desenha o virabrequim
    glPushMatrix();
    glRotatef (angGraus, 0.0f, 0.0f, 1.0f); //rotacao no eixo z
//    glutWireCube(6);
//    glTranslated(raio, 0,0);
    glutWireCube(6);
    glPopMatrix();

    glPushMatrix();
        glRotatef(angGraus, 0.0f, 0.0f, 1.0f);
        glTranslated(0, 50, 0);
        glRotated(-angGraus * 2, 0, 0, 1);
        glutWireCube(6);
    glPopMatrix();
//
//    //calcula o ponto de apoio usando coordenadas polares.
//    float angRad = angGraus * PI / 180.0;
//    float y = sin(angRad) * raio;
//    float x = cos(angRad) * raio;
//
//    //desenha o ponto de apoio da biela no virabrequim
//    glPushMatrix();
//    glTranslated(x, y, 0);
//    glutWireCube(10);
//    glPopMatrix();
//
//    //desenha uma "biela hipotetica" conectada ao virabrequim e a um ponto fixo
//    glBegin(GL_LINES);
//    glVertex3d(x, y, 0);
//    glVertex3d(100,100,0);
//    glEnd();
//
    glutSwapBuffers();
//
    angGraus++;
}


////////////////////////////////////////////////////////////////////////////////////////
int main ()
{
    int  argc=0;
    glutInit(&argc, NULL);

    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );

    glutInitWindowSize (SCREEN_X, SCREEN_Y);
    glutInitWindowPosition (250, 10);
    /* create window */
    glutCreateWindow ("Rotacao via GL e Coord Polares");

    glutDisplayFunc(display);
    glutIdleFunc(display);

    glutMainLoop();
    return 0;
}
