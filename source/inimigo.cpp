#include "inimigo.h"
#include <cmath>

Ponto2D Inimigo::obtemGlobalPontaArma(GLfloat x, GLfloat y){
    Ponto2D ponto;

    //Arma do personagem
    Arma arma = this->get_arma();
    //Translada altura da arma
    ponto.transladar(0,arma.get_altura());
    //Rotaciona posicao da arma
    ponto.rotacionarZ(arma.get_angulo());
    //Translada posicao da arma
    ponto.transladar(arma.get_gX(),arma.get_gY());


    // Personagem
    //Transformacoes do circulo da cabeca
    ponto.transladar(this->get_gX(),this->get_gY());

    // Barril
    //fazer o inimigo olhar para o personagem
    ponto.rotacionarZ(180);
    //fazer transladar o barril
    ponto.transladar(x,y);

    return ponto;
}
Ponto2D Inimigo::obtemGlobalBaseArma(GLfloat x, GLfloat y){
    Ponto2D ponto;
    Arma arma = this->get_arma();
    //Rotaciona posicao da arma
    ponto.rotacionarZ(arma.get_angulo());
    //Translada posicao da arma
    ponto.transladar(arma.get_gX(),arma.get_gY());
    //Transformacoes do circulo da cabeca
    ponto.transladar(this->get_gX(),this->get_gY());
    //fazer o inimigo olhar para o personagem
    ponto.rotacionarZ(180);
    //fazer transladar o barril
    ponto.transladar(x,y);

    return ponto;
}

Ponto2D Inimigo::obtemBaseArmaNaoRotacionada(GLfloat x, GLfloat y){
    Ponto2D ponto;
    Arma arma = this->get_arma();
    //Translada posicao da arma
    ponto.transladar(arma.get_gX(),arma.get_gY());
    //Transformacoes do circulo da cabeca
    ponto.transladar(this->get_gX(),this->get_gY());
    //fazer o inimigo olhar para o personagem
    ponto.rotacionarZ(180);
    //fazer transladar o barril
    ponto.transladar(x,y);
    return ponto;
}

void Inimigo::miraPonto(GLfloat x, GLfloat y, GLfloat barrilX, GLfloat barrilY){
    Ponto2D objetivo = Ponto2D(x,y);
    GLfloat angulo = this->obtemBaseArmaNaoRotacionada(barrilX,barrilY).anguloEntre(objetivo);
    this->get_arma().modificaAngulo(angulo*(180.0 / M_PI) - 90);
}

Tiro* Inimigo::atira(GLfloat distMax, GLfloat x, GLfloat y)
{   
    glLoadIdentity();
    glPushMatrix();

        Ponto2D pontaArma = obtemGlobalPontaArma(x, y);
        Ponto2D baseArma = obtemGlobalBaseArma(x, y);
        GLfloat angulo = pontaArma.anguloEntre(baseArma);

    glPopMatrix();
    return new Tiro(pontaArma.getX(),pontaArma.getY(), angulo, distMax, this->getVelocidadeTiro());
}
void Inimigo::desenhaInimigo( GLfloat x, GLfloat y){
    GLdouble currentTime = glutGet(GLUT_ELAPSED_TIME);
    GLfloat timeDiference = currentTime - this->getUltimoDesenho();
    this->setUltimoDesenho(currentTime);
    glPushMatrix();
        glRotatef(180,0,0,1);
        this->movimentaEmY(timeDiference);
        this->desenhaPersonagem(x,y, gInimigoCorExterna, gInimigoCor);
    glPopMatrix();
}

void Inimigo::movimentaEmY(GLfloat timeDiference){
    this->get_pernaEsquerda().animacaoPerna(timeDiference);
    this->get_pernaDireita().animacaoPerna(timeDiference);
}