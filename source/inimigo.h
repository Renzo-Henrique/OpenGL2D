#ifndef INIMIGO_H
#define	INIMIGO_H
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <string>
#include <iostream>
#include "tiro.h"
#include "personagem.h"
//#include "barril.h"

class Inimigo : public Personagem{
    GLfloat tirosPorSegundo = 0;
    GLfloat ultimoTiro = -1;
    GLfloat ultimoDesenho = -1;
    GLfloat gInimigoCor[4] = {0.5781, 0, 0.8242, 1}; 
    GLfloat gInimigoCorExterna[4] = {0.5781 * 0.7, 0, 0.8242 * 0.7, 1};
    
private:
    void desenhaInimigo(GLfloat x, GLfloat y);
public:
    Inimigo(GLfloat raioCabeca, Arma arma, Perna perna1, Perna perna2, 
            GLfloat gX, GLfloat gY, GLfloat velocidadePersonagem, GLfloat tirosPorSegundo, GLfloat velocidadeTiro): 
            Personagem(raioCabeca, arma, perna1, perna2, gX, gY, velocidadePersonagem, velocidadeTiro){
              this->tirosPorSegundo = tirosPorSegundo;
              this->ultimoTiro = -10;
              this->ultimoDesenho = -1;
            };
    Inimigo() : Personagem(){};

    GLfloat getTirosPorSegundo() const {
        return tirosPorSegundo;
    }
    GLfloat getUltimoTiro(){
        return ultimoTiro;
    }
    GLfloat getUltimoDesenho(){
        return ultimoDesenho;
    }
    void setTirosPorSegundo(GLfloat valor) {
        tirosPorSegundo = valor;
    }
    void setUltimoTiro(GLfloat valor) {
        ultimoTiro = valor;
    }
    void setUltimoDesenho(GLfloat valor) {
        ultimoDesenho = valor;
    }
    Inimigo* copia(){
      return new Inimigo( this->get_raioCabeca(), this->get_arma(), this->get_pernaEsquerda(),
                           this->get_pernaDireita(), 
                         this->get_gX(), this->get_gY(), this->get_velocidadePersonagem(), 
                         this->getTirosPorSegundo(), this->getVelocidadeTiro());
    }
    void desenha(){
      desenhaInimigo(this->get_gX(), this->get_gY());
    }
    //Tempo em milissegundos
    bool podeAtirar(GLfloat tempo,GLfloat posY, GLfloat miraY){
        //pode atirar se o ponto estiver abaixo OU no intervalo de tempo
        return (this->get_gY() + posY > miraY) and 
                ( tempo - this->getUltimoTiro())/1000 >= 1/this->getTirosPorSegundo() ;
    }

    void movimentaEmY(GLfloat timeDiference);
    void miraPonto(GLfloat x, GLfloat y, GLfloat barrilX, GLfloat barrilY);
    Ponto2D obtemBaseArmaNaoRotacionada(GLfloat x, GLfloat y);
    Ponto2D obtemGlobalPontaArma(GLfloat x, GLfloat y);
    Ponto2D obtemGlobalBaseArma(GLfloat x, GLfloat y);
    Tiro* atira(GLfloat distMax, GLfloat x, GLfloat y);
    
};

#endif	/* INIMIGO_H */

