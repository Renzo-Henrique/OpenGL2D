#include "tiro.h"
#include "ponto2D.h"
#include <math.h>

void Tiro::desenhaCirc(GLint radius, GLfloat r, GLfloat g, GLfloat b)
{   
    const int numero_lados = 360;
    const GLfloat anguloRadiano = 360/numero_lados * ( M_PI / 180.0);
    glColor3f(r, g, b);
    glPointSize(1);
    glPushMatrix();
        glBegin(GL_POLYGON);
        GLfloat x = 0, y = radius;
        //faz  um polígono de "n" lados que se parece um círculo
        for(int i = 0;  i < numero_lados ; i++){
            glVertex3f(x,y,0);
            //Rotaciona o tiro
            x = cos(anguloRadiano * i) * radius;
            y = sin(anguloRadiano * i) * radius;  
        }
        glEnd();
    glPopMatrix();
}

void Tiro::desenhaTiro(GLfloat x, GLfloat y, GLfloat r, GLfloat g, GLfloat b){   
    // Defindo sistema de coordenadas
    glLoadIdentity();
    glPushMatrix();
        glTranslatef(x, y, 0);
        desenhaCirc(this->getRaio(),r,g,b);
        
    glPopMatrix();
}

void Tiro::move(GLfloat timeDiference){
    timeDiference/= 10;
    //calcular angulo
    this->gX += ( gVel * timeDiference ) * cos(this->gDirectionAng);
    this->gY += ( gVel * timeDiference ) * sin(this->gDirectionAng);
}

bool Tiro::valido(){
    return sqrt( (gX - gXInit)*(gX - gXInit) + (gY - gYInit)*(gY - gYInit) ) < this->distMax;
}
