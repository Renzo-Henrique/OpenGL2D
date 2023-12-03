#ifndef TIRO_H
#define	TIRO_H
#include <GL/gl.h>
#include <GL/glu.h>

#define RAIO_TIRO 5

class Tiro {
    GLfloat gXInit; 
    GLfloat gYInit; 
    GLfloat gX; 
    GLfloat gY; 
    GLfloat raio;
    GLfloat gDirectionAng;
    GLfloat gVel;
    GLfloat distMax;
private:
    void desenhaCirc(GLint radius, GLfloat R, GLfloat G, GLfloat B);
    void desenhaTiro(GLfloat x, GLfloat y, GLfloat r, GLfloat g, GLfloat b);
public:
    Tiro(GLfloat x, GLfloat y, GLfloat directionAng, GLfloat distMax, GLfloat velocidade){
        this->gXInit = x; 
        this->gYInit = y; 
        this->gX = x; 
        this->gY = y; 
        this->gDirectionAng = directionAng; 
        this->gVel = velocidade;
        this->distMax = distMax;
        this->raio = RAIO_TIRO;
    };
    void desenha(GLfloat r, GLfloat g, GLfloat b){ 
        desenhaTiro(gX, gY, r, g, b);
    };
    void move(GLfloat timeDiference);
    bool valido();
    void getPos(GLfloat &xOut, GLfloat &yOut){
        xOut = gX;
        yOut = gY;
    };

    GLfloat getRaio(){
        return this->raio;
    }
};

#endif	/* TIRO_H */

