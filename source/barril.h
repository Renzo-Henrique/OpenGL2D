#ifndef BARRIL_H
#define	BARRIL_H
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <string>
#include <list>
#include "inimigo.h"
#include "ponto2D.h"
#include "tiro.h"
#include <cmath>

class Barril {
    GLfloat altura, largura, velocidade;
    GLfloat gX, gY;
    GLint numeroTiros, vidaAtual;
    Inimigo* inimigo;
    GLfloat distQuina;
    GLfloat gBarrilCor[4] = {0.9649, 0.5859, 0.2734}; 
    GLfloat gBarrilCorExterna[4] = {0.9649*0.5, 0.5859*0.5, 0.2734*0.5};

protected:
    void desenhaRetanguloArredondado(GLfloat width, GLfloat height, GLfloat radius,
                            GLfloat R, GLfloat G, GLfloat B);
    void desenhaBarril(GLfloat x, GLfloat y);
    void imprimeVida(GLfloat x, GLfloat y);
    
public:
    // Construtor
    Barril(GLfloat altura, GLfloat largura, GLfloat velocidade, int numeroTiros, 
            GLfloat gX, GLfloat gY, Inimigo* inimigo) {
        this->altura = altura;
        this->largura = largura;
        this->velocidade = velocidade;
        this->numeroTiros = numeroTiros;
        this->vidaAtual = numeroTiros;
        this->inimigo = inimigo;
        this->gX = gX;
        this->gY = gY;
        this->atualizaDistQuina();

    }
    // Destrutor
    ~Barril() {
        // Faça qualquer limpeza necessária aqui, como liberar memória alocada dinamicamente
        delete inimigo;
    }
    // Métodos Get
    GLfloat getAltura() const {
        return this->altura;
    }
    GLfloat getLargura() const {
        return this->largura;
    }
    GLfloat getVelocidade() const {
        return this->velocidade;
    }
    GLint getNumeroTiros() const {
        return this->numeroTiros;
    }
    Inimigo* getInimigo() const {
        return this->inimigo;
    }
    GLfloat get_gX() const {
        return this->gX;
    }
    GLfloat get_gY() const {
        return this->gY;
    }
    GLint get_vidaAtual(){
        return this->vidaAtual;
    }
    GLfloat get_distQuina(){
        return this->distQuina;
    }

    // Métodos Set
    void setAltura(GLfloat altura) {
        this->altura = altura;
    }
    void setLargura(GLfloat largura) {
        this->largura = largura;
    }
    void setVelocidade(GLfloat velocidade) {
        this->velocidade = velocidade;
    }
    void setNumeroTiros(GLint numeroTiros) {
        this->numeroTiros = numeroTiros;
    }
    void setInimigo(Inimigo* inimigo) {
        this->inimigo = inimigo;
    }
    void set_gX(GLfloat gX) {
        this->gX = gX;
    }
    void set_gY(GLfloat gY) {
        this->gY = gY;
    }
    void diminuiVidaAtual(){
        this->vidaAtual-=1;
    }
    void desenha(){
        this->desenhaBarril(this->get_gX(), this->get_gY());
    }
    void atualizaDistQuina(){
        this->distQuina = sqrt(pow(this->largura/2, 2) + pow( this->altura/2, 2));
    }   
    bool valido(GLfloat alturaArena){
        return this->get_gY() > - alturaArena/2 - this->getAltura();
    }
    bool destruido(){
        return this->get_vidaAtual() <= 0;
    }
    void move(GLfloat timeDifference);
    bool colisao(GLfloat x, GLfloat y, GLfloat raio);
    bool colisaoTiro(Tiro* tiro);
    GLfloat distPonto(GLfloat x, GLfloat y);
};
#endif	/* BARRIL_H */

