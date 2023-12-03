#ifndef PONTO2D_H
#define	PONTO2D_H
#include <GL/gl.h>
#include <GL/glu.h>
#include <string>
#include <iostream>

class Ponto2D {
    GLfloat gX; 
    GLfloat gY;
    
public:
    Ponto2D(GLfloat x, GLfloat y){
        gX = x; 
        gY = y;
    };
    Ponto2D(){
        gX = 0; 
        gY = 0;
    };
    void GetPos(GLfloat &xOut, GLfloat &yOut){
        xOut = gX;
        yOut = gY;
    };
    void setX(GLfloat x){
        this->gX = x;
        }
    void setY(GLfloat y){
        this->gY = y;
        }
    void set_ponto2D(GLfloat x, GLfloat y){
        gX = x; 
        gY = y;
    };
    GLfloat getX(){ 
        return this->gX; 
    }
    GLfloat getY(){ 
        return this->gY; 
    }
    void mostrar(){
        std:: cout << "(" << this->getX() << "," << this->getY() << ")\n";
    }
    void rotacionarZ(GLfloat angle);
    void transladar (GLfloat dx, GLfloat dy);
    float anguloEntre(Ponto2D& p2);
    
};

#endif	/* TIRO_H */

