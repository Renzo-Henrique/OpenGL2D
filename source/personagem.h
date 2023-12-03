#ifndef PERSONAGEM_H
#define	PERSONAGEM_H
#include <GL/gl.h>
#include <GL/glu.h>
#include <string>
#include "arma.h"
#include "perna.h"
#include "tiro.h"
#include "ponto2D.h"

#define PERSONAGEM_RAIO_CABECA 20

class Personagem {
    GLfloat raioCabeca, velocidadePersonagem;
    Arma armaPersonagem;
    Perna pernasPersonagem[2];
    GLfloat gX, gY;
    GLfloat velocidadeTiro;

protected:
    void desenhaCirc(GLint radius, GLfloat R, GLfloat G, GLfloat B);
    void desenhaPernas();
    bool movimentoValido(GLfloat dX, GLfloat dY, GLfloat arenaLargura, GLfloat arenaAltura);
public:
    Personagem(GLfloat raioCabeca, Arma arma, Perna perna1, Perna perna2, GLfloat gX, GLfloat gY, 
                GLfloat velocidadePersonagem, GLfloat velocidadeTiro){
        this->raioCabeca = raioCabeca;
        this->armaPersonagem = arma;
        this->pernasPersonagem[0] = perna1;
        this->pernasPersonagem[1] = perna2;
        this->gX = gX;
        this->gY = gY;
        this->velocidadePersonagem = velocidadePersonagem;
        this->velocidadeTiro = velocidadeTiro; 
    };
    Personagem(GLfloat raioCabeca, GLfloat gX, GLfloat gY, GLfloat velocidadePersonagem, GLfloat velocidadeTiro){
        this->raioCabeca = raioCabeca;
        this->armaPersonagem = Arma();
        this->pernasPersonagem[0] = Perna(-raioCabeca, 0);
        this->pernasPersonagem[1] = Perna(+raioCabeca, 0);
        this->gX = gX;
        this->gY = gY;
        this->velocidadePersonagem = velocidadePersonagem;
        this->velocidadeTiro = velocidadeTiro; 
    };
    Personagem(){

    };
    //Getters
    void getPos(GLfloat &xOut, GLfloat &yOut){
        xOut = gX;
        yOut = gY;
    };
    GLfloat get_gX(){
        return gX;
    };
    GLfloat get_gY(){
        return gY;
    };
    GLfloat get_raioCabeca(){
        return raioCabeca;
    };
    GLfloat get_velocidadePersonagem(){
        return velocidadePersonagem;
    };
    GLfloat getVelocidadeTiro() const {
        return velocidadeTiro;
    }
    Perna& get_pernaDireita(){
        return pernasPersonagem[0];
    };
    Perna& get_pernaEsquerda(){
        return pernasPersonagem[1];
    };
    Arma& get_arma(){
        return armaPersonagem;
    };

    //Setters
    void setVelocidadeTiro(GLfloat valor) {
        velocidadeTiro = valor;
    }
    void set_gX(GLfloat gX){
        this->gX = gX;
    };
    void set_gY(GLfloat gY){
        this->gY = gY;
    };

    void moveEmX(GLfloat movimento);
    void moveEmY(GLfloat movimento);
    void desenhaPersonagem(GLfloat x, GLfloat y, GLfloat* gPersonagemCorExterna, GLfloat* gPersonagemCor);
    bool atingido(Tiro *tiro);
};

#endif	/* PERSONAGEM_H */

