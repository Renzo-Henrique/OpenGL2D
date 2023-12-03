#include "personagem.h"
#include <math.h>
#include <stdio.h>
#include <iostream>

void Personagem::desenhaCirc(GLint radius, GLfloat R, GLfloat G, GLfloat B){
    const int numero_lados = 360;
    const GLfloat angulo = 360/numero_lados * ( M_PI / 180.0);
    
    glColor3f(R, G, B);

    glPushMatrix();
        glBegin(GL_POLYGON);
        GLfloat x = 0, y = radius;

        //faz  um polígono de "n" lados que se parece um círculo
        for(int i = 0;  i < numero_lados ; i++){
            glVertex3f(x,y,0);
            //Rotaciona o tiro
            x = cos(angulo * i * (  180.0/ M_PI)) * radius;
            y = sin(angulo * i * (  180.0/ M_PI)) * radius;            
        }
        glEnd();

    glPopMatrix();
}

void Personagem::desenhaPernas(){
    this->pernasPersonagem[0].desenha();
    this->pernasPersonagem[1].desenha();
}
 
void Personagem::desenhaPersonagem(GLfloat x, GLfloat y, GLfloat* gPersonagemCorExterna, GLfloat* gPersonagemCor){
    // Defindo sistema de coordenadas
    glPushMatrix();
        glTranslatef(gX, gY, 0);
        // Desenha pernas pro lado esquerdo e direito
        desenhaPernas();
        // Desenha cabeca externa e interna
        desenhaCirc(this->get_raioCabeca(),     gPersonagemCorExterna[0], 
                    gPersonagemCorExterna[1],   gPersonagemCorExterna[2]);
        desenhaCirc(0.9*this->get_raioCabeca(),     gPersonagemCor[0], 
                    gPersonagemCor[1], gPersonagemCor[2]);

        this->armaPersonagem.desenha(); // deixar para o especifico de inimigo e jogador?
    glPopMatrix();
}
bool Personagem::movimentoValido(GLfloat dX, GLfloat dY, GLfloat arenaLargura, GLfloat arenaAltura){
    return true;
}
void Personagem::moveEmX(GLfloat movimento){
    this->gX += movimento;
}
void Personagem::moveEmY(GLfloat movimento){
    this->gY += movimento;
}

bool Personagem::atingido(Tiro *tiro){
    GLfloat x ,y;
    tiro->getPos(x, y);
    GLfloat distancia = sqrt( pow(this->get_gX() - x, 2) + pow( this->get_gY() - y, 2));
    return distancia - tiro->getRaio()< this->get_raioCabeca();
}





