#include "jogador.h"
#include <cmath>

Ponto2D Jogador::obtemGlobalPontaArma(){
    Ponto2D ponto;
    //Translada altura da arma
    ponto.transladar(0,get_arma().get_altura());
    //Rotaciona posicao da arma
    ponto.rotacionarZ(get_arma().get_angulo());
    //Translada posicao da arma
    ponto.transladar(get_arma().get_gX(),get_arma().get_gY());
    //Transformacoes do circulo da cabeca
    ponto.transladar(this->get_gX(),this->get_gY());

    return ponto;
}

Ponto2D Jogador::obtemGlobalBaseArma(){
    Ponto2D ponto;
    
    //Rotaciona posicao da arma
    ponto.rotacionarZ(get_arma().get_angulo());
    //Translada posicao da arma
    ponto.transladar(get_arma().get_gX(),get_arma().get_gY());
    //Transformacoes do circulo da cabeca
    ponto.transladar(this->get_gX(),this->get_gY());
    return ponto;
}

Tiro* Jogador::atira(GLfloat distMax)
{
    glLoadIdentity();
    glPushMatrix();

        Ponto2D pontaArma = obtemGlobalPontaArma();
        Ponto2D baseArma = obtemGlobalBaseArma();
        GLfloat angulo = pontaArma.anguloEntre(baseArma);

    glPopMatrix();
    return new Tiro(pontaArma.getX(),pontaArma.getY(), angulo, distMax, this->getVelocidadeTiro());
}
void Jogador::desenhaJogador(GLfloat x, GLfloat y){
    glLoadIdentity();
    glPushMatrix();
        this->desenhaPersonagem(x,y, gJogadorCorExterna, gJogadorCor);
    glPopMatrix();
}

void Jogador::movimentaEmX(GLfloat timeDiference, GLfloat dx, GLfloat arenaLargura){
    GLfloat posicaoFinal = dx * this->get_velocidadePersonagem() * timeDiference + this->get_gX();
    //somente a borda pode encostar na arena
    if( -arenaLargura/2 > posicaoFinal - this->get_raioCabeca()){
        //posicaoFinal = arenaLargura/2 - this->get_raioCabeca();//feature teleporte
        posicaoFinal = -arenaLargura/2 + this->get_raioCabeca();
    }
    else if( posicaoFinal + this->get_raioCabeca() > arenaLargura/2){
        //posicaoFinal = - arenaLargura/2 + this->get_raioCabeca();//feature teleporte
        posicaoFinal = arenaLargura/2 - this->get_raioCabeca();
    }
    this->set_gX(posicaoFinal);
}
void Jogador::movimentaEmY(GLfloat timeDiference, GLfloat dy, GLfloat arenaAltura){
    GLfloat posicaoFinal = dy * this->get_velocidadePersonagem() * timeDiference + this->get_gY();
    if( -arenaAltura/2 > posicaoFinal - this->get_raioCabeca()){
        posicaoFinal = -arenaAltura/2 + this->get_raioCabeca();
    }
    else if( posicaoFinal + this->get_raioCabeca() > 0){
        posicaoFinal = 0 - this->get_raioCabeca();
    }
    this->set_gY(posicaoFinal);
    this->get_pernaEsquerda().animacaoPerna(timeDiference);
    this->get_pernaDireita().animacaoPerna(timeDiference);
}

bool Jogador::atingido(Tiro *tiro){   
    GLfloat x ,y;
    tiro->getPos(x, y);
    GLfloat distancia = sqrt( pow(this->get_gX() - x, 2) + pow( this->get_gY() - y, 2));
    return distancia - tiro->getRaio()< this->get_raioCabeca();
}