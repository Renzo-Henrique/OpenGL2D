#include "arma.h"
#include <math.h>
#include <stdio.h>
#include <iostream>
void Arma::desenhaRect(GLint height, GLint width, GLfloat R, GLfloat G, GLfloat B){
    glColor3f(R, G, B);
    glBegin(GL_QUADS);
        glVertex2f(-width/2, 0);
        glVertex2f( width/2, 0);
        glVertex2f( width/2, height);
        glVertex2f(-width/2, height);
    glEnd();

}


void Arma::desenhaArma(GLfloat x, GLfloat y){
    glPushMatrix();
        glTranslatef(x,y,0);
        glRotatef(this->get_angulo(),0,0,1);
        glTranslatef(-0.2*x,0,0);
        desenhaRect(this->get_altura(), this->get_largura(), gArmaCorExterna[0], 
                                        gArmaCorExterna[1], gArmaCorExterna[2]);
        
        glPushMatrix();
            GLfloat diminuiPorcentagem = 0;
            GLfloat porcentualBorda = 0.15;
            if(this->get_largura() < this->get_altura()){
                diminuiPorcentagem = this->get_largura()*porcentualBorda;
            }
            else{
                diminuiPorcentagem = this->get_altura()*porcentualBorda;
            }

            glTranslatef( 0, diminuiPorcentagem, 0);

            desenhaRect(this->get_altura()- 2*diminuiPorcentagem, this->get_largura() - 2*diminuiPorcentagem, 
                                        gArmaCor[0], gArmaCor[1], gArmaCor[2]);
        glPopMatrix();
    glPopMatrix();
}

void Arma::mexeAngulo(GLfloat angulo){  
    GLfloat angulo_final = angulo;
    if(angulo_final > 30){
       angulo_final = 30; 
    } 
    else if(angulo_final < -30){
        angulo_final = -30;
    }
    this->set_angulo( angulo_final);
}

void Arma::modificaAngulo(GLfloat angulo){
    GLfloat angulo_final = angulo;
    if(angulo_final >= 30){
       angulo_final = 30; 
    } 
    else if(angulo_final <= -30){
        angulo_final = -30;
    }
    this->set_angulo( angulo_final);
}


