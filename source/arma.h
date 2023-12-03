#ifndef ARMA_H
#define	ARMA_H
#include <GL/gl.h>
#include <GL/glu.h>

#define ARMA_ALTURA 20
#define ARMA_LARGURA 20
#define ARMA_ANGULO_MAX 60

class Arma {
    GLfloat altura, largura, anguloArma;
    GLfloat gX, gY;
    GLfloat gArmaCor[4] = {0.8, 0, 0.2, 1};
    GLfloat gArmaCorExterna[4] = {0.8 * 0.5, 0, 0.2*0.5, 1}; 

private:
    void desenhaRect(  GLint height, GLint width, 
                    GLfloat R, GLfloat G, GLfloat B);
    void desenhaArma(GLfloat x, GLfloat y);
public:
    Arma(GLfloat altura, GLfloat largura, GLfloat anguloArma, GLfloat gX, GLfloat gY){
        this->altura = altura;
        this->largura = largura;
        this->anguloArma = anguloArma;
        this->gX = gX;
        this->gY = gY;
    };

    Arma(){
        this->altura = ARMA_ALTURA;
        this->largura = ARMA_LARGURA;
        this->anguloArma = ARMA_ANGULO_MAX;
        this->gX = 0;
        this->gY = 0;
    };
    GLfloat get_gX(){
        return gX;
    };
    GLfloat get_gY(){
        return gY;
    };
    GLfloat get_altura(){
        return altura;
    };
    GLfloat get_largura(){
        return largura;
    };
    GLfloat get_angulo(){
        return anguloArma;
    };
    void set_angulo(GLfloat angulo){
        this->anguloArma = angulo;
    };
    void mexeAngulo(GLfloat angulo);
    void modificaAngulo(GLfloat angulo);
    void desenha(){
        desenhaArma(this->get_gX(), this->get_gY());
    }
    
};

#endif	/* ARMA_H */

