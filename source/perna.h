#ifndef PERNA_H
#define	PERNA_H
#include <GL/gl.h>
#include <GL/glu.h>
#include <string>
#include <iostream>

#define PERNA_ALTURA 40
#define PERNA_LARGURA 10
#define PERNA_VELOCIDADE_MUDANCA 1

class Perna {
    GLfloat altura, largura, velocidadeMudanca;
    GLfloat gX, gY;
    GLint dir;
    GLfloat angulo;

private:
    void desenhaRect(  GLint height, GLint width, 
                    GLfloat R, GLfloat G, GLfloat B);
    void desenhaPerna(GLfloat x, GLfloat y);
public:
    Perna(GLfloat altura, GLfloat largura, GLfloat velocidadeMudanca, GLfloat gX, GLfloat gY, GLint dir){
        this->altura = altura;
        this->largura = largura;
        this->velocidadeMudanca = velocidadeMudanca;
        this->gX = gX;
        this->gY = gY;
        this->dir = dir;
        this->angulo = 0;
    };

    Perna( GLfloat gX, GLfloat gY){
        this->altura = PERNA_ALTURA;
        this->largura = PERNA_LARGURA;
        this->velocidadeMudanca = PERNA_VELOCIDADE_MUDANCA;
        this->gX = gX;
        this->gY = gY;
        this->dir = 1;
    };
    Perna(){
        this->altura = PERNA_ALTURA;
        this->largura = PERNA_LARGURA;
        this->velocidadeMudanca = PERNA_VELOCIDADE_MUDANCA;
        this->gX = 0;
        this->gY = 0;
        this->dir = 1;
    };
    //Getters
    GLfloat get_gX(){
        return gX;
    };
    GLfloat get_gY(){
        return gY;
    };
    GLfloat get_velocidadeMudanca(){
        return velocidadeMudanca;
    };
    
    GLfloat get_altura(){
        return altura;
    };
    GLfloat get_largura(){
        return largura;
    };
    GLfloat get_angulo(){
        return angulo;
    };
    GLint get_dir(GLint dir){
       return this->dir;
    };

    //Setters
    void set_gX(GLfloat x){
        this->gX = x;
    };
    void set_gY(GLfloat y){
        this->gY = y;
    };
    void set_angulo(GLfloat angulo){
       this->angulo = angulo;
    };
    void set_dir(GLint dir){
        this->dir = dir;
    };
    void set_velocidadeMudanca(GLfloat velocidade){
        this->velocidadeMudanca = velocidade;
    };
    void desenha(){
        desenhaPerna(this->get_gX(), this->get_gY());
    }
    void animacaoPerna(GLfloat timeDifference);
};

#endif	/* PERNA_H */

