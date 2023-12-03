#include "barril.h"
#include <cmath>


void Barril::desenhaRetanguloArredondado(GLfloat largura, GLfloat altura, GLfloat radius,
                            GLfloat R, GLfloat G, GLfloat B) {
    glColor3f(R, G, B);
    glBegin(GL_QUADS);
        glVertex2f(-largura/2, 0);
        glVertex2f( largura/2, 0);
        glVertex2f( largura/2, altura);
        glVertex2f(-largura/2, altura);
    glEnd();
}
void Barril::desenhaBarril(GLfloat x, GLfloat y){

    // Defindo sistema de coordenadas
    glLoadIdentity();
    glPushMatrix();
        glTranslatef(this->get_gX(), this->get_gY(), 0);
        Inimigo* inimigo = this->getInimigo();
        desenhaRetanguloArredondado(this->getLargura(), this->getAltura(),this->getAltura()*0.05, 
                                gBarrilCorExterna[0], gBarrilCorExterna[1],   gBarrilCorExterna[2]);
        glPushMatrix();
            GLfloat diminuiPorcentagem = 0;
            GLfloat porcentualBorda = 0.05;
            if(this->getLargura() < this->getAltura()){
                diminuiPorcentagem = this->getLargura()*porcentualBorda;
            }
            else{
                diminuiPorcentagem = this->getAltura()*porcentualBorda;
            }

            glTranslatef( 0, diminuiPorcentagem, 0);


            desenhaRetanguloArredondado(this->getLargura() - 2*diminuiPorcentagem, this->getAltura() - 2*diminuiPorcentagem,
                                        this->getAltura()*0.05, gBarrilCor[0], gBarrilCor[1],   gBarrilCor[2]);
        glPopMatrix();
        //Desenha inimigo se houver                            
        if(inimigo){
            inimigo->desenha();
        }
        this->imprimeVida( 0.7*this->getLargura()/2 , 0.8*this->getAltura()/2);

    glPopMatrix();
    

}
void Barril::move(GLfloat timeDifference){
    this->set_gY( - timeDifference/10 * this->getVelocidade() + this->get_gY());
}

//Impressão da vida
static char str[1000];
void * fonteVida = GLUT_BITMAP_HELVETICA_18;

void Barril::imprimeVida(GLfloat x, GLfloat y){
    glColor3f(0, 0, 0);
    //Cria a string a ser impressa
    char *tmpStr;
    sprintf(str, "%d", this->get_vidaAtual() );
    //Define a posicao onde vai comecar a imprimir
    glRasterPos2f(x, y);
    //Imprime um caractere por vez
    tmpStr = str;
    while( *tmpStr ){
        glutBitmapCharacter(fonteVida, *tmpStr);
        tmpStr++;
    }
}
GLfloat Barril::distPonto(GLfloat x, GLfloat y){
    return sqrt(pow(this->get_gX() - x, 2) + pow( (this->get_gY() - this->getAltura()/2) - y, 2));
}
bool Barril::colisao(GLfloat x, GLfloat y, GLfloat raio){
    //Sera tratado como colisao entre retangulo - quadrado
    //colisao em cima
    if( y <= this->get_gY() + this->getAltura() + raio){
        //colisao em baixo
        if( y >= this->get_gY() - raio){
            //colisao direita
            if( x <= this->get_gX() + this->getLargura()/2 + raio){
                //colisao esquerda
                if( x >= this->get_gX() - this->getLargura()/2 - raio){
                    return true;
                }
            }
        }
    }
    return false;
}

bool Barril::colisaoTiro(Tiro* tiro){
    GLfloat x, y;
    tiro->getPos(x, y);
    
    return this->colisao(x, y, tiro->getRaio());
}
