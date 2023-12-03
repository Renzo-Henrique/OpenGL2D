#include "ponto2D.h"
#include <math.h>
#include <iostream>
#include <cstdio>

void Ponto2D::rotacionarZ(GLfloat angle){
    GLfloat ang_rad = angle *( M_PI / 180.0);
    GLfloat x = 0, y = 0;
    x = this->getX();
    y = this->getY();
    this->setX((x * cos(ang_rad)) - (y * sin(ang_rad)));
    this->setY((x * sin(ang_rad)) + (y * cos(ang_rad)));
}

void Ponto2D::transladar (GLfloat dx, GLfloat dy){
    this->set_ponto2D( this->getX() + dx , this->getY() + dy);
}

GLfloat Ponto2D::anguloEntre(Ponto2D& ponto2){
    //retorna em radianos
    GLfloat x = this->getX() - ponto2.getX();
    GLfloat y = this->getY() - ponto2.getY();
    return atan2( y, x);
}