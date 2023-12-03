#include "perna.h"
#include <math.h>

void Perna::desenhaRect(GLint height, GLint width, GLfloat R, GLfloat G, GLfloat B){
    glColor3f(R, G, B);

    glBegin(GL_QUADS);
        glVertex2f(-width/2, 0);
        glVertex2f( width/2, 0);
        glVertex2f( width/2, height);
        glVertex2f(-width/2, height);
    glEnd();

}

void Perna::desenhaPerna(GLfloat x, GLfloat y){
    glPushMatrix();
        glRotatef(this->get_angulo(), 1, 0, 0);
        glTranslatef(x,y,0);
        desenhaRect(this->get_altura(), this->get_largura(), 0, 0, 0);
    glPopMatrix();
}

void Perna::animacaoPerna(GLfloat timeDifference){

    this->set_angulo(this->get_angulo() + 1 * 360*timeDifference/(1500) *this->get_velocidadeMudanca());
}