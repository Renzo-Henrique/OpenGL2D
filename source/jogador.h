#ifndef JOGADOR_H
#define	JOGADOR_H
#include <GL/gl.h>
#include <GL/glu.h>
#include <string>
#include "personagem.h"
#include "arma.h"
#include "perna.h"
#include "tiro.h"
#include "ponto2D.h"


class Jogador : public Personagem {
    GLfloat gJogadorCor[4] = {0.605, 0.730, 0.3475, 1}; 
    GLfloat gJogadorCorExterna[4] = {0.246, 0.300, 0.129, 1};
private:
    void desenhaJogador(GLfloat x, GLfloat y);
public:
    Jogador(GLfloat raioCabeca, Arma arma, Perna perna1, Perna perna2, 
            GLfloat gX, GLfloat gY, GLfloat velocidadePersonagem, GLfloat velocidadeTiro): 
            Personagem(raioCabeca, arma, perna1, perna2, gX, gY, velocidadePersonagem, velocidadeTiro){};
    Jogador() : Personagem(){};
    Tiro* atira(GLfloat distMax);
    void movimentaEmX(GLfloat timeDiference, GLfloat dx, GLfloat arenaLargura);
    void movimentaEmY(GLfloat timeDiference, GLfloat dy, GLfloat arenaAltura);
    void desenha(){
        desenhaJogador(this->get_gX(), this->get_gY());
    }
    bool atingido(Tiro *tiro);
    Ponto2D obtemGlobalPontaArma();
    Ponto2D obtemGlobalBaseArma();
};
#endif /*JOGADOR_H*/