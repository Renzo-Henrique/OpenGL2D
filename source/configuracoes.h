#ifndef CONFIGURACOES_H
#define	CONFIGURACOES_H
#include <GL/gl.h>
#include <GL/glu.h>
#include <string>
#include <iostream>
#include <list>
#include <cmath>
#include "inimigo.h"
#include "jogador.h"
#include "perna.h"
#include "arma.h"
#include "barril.h"
#include "tinyxml2.h"

// Um a cada 'n' barris tera inimigo
#define PROBABILIDADE_INIMIGO 2

using namespace std;

class Configuracoes {
    int arenaAltura, arenaLargura;
    GLfloat distMaxTiro;
    GLfloat jogadorRaioCabeca, jogadorVelocidade;
    GLfloat inimigoRaioCabeca, inimigoTirosPorSegundo, inimigoVelocidadeTiro;
    GLfloat barrilAltura, barrilLargura, barrilNumeroTiros, barrilnParaGanhar;
    GLfloat barrilVelocidade, barrilLimite;
    GLint LimiteXInferiorBarril;
    GLint LimiteXSuperiorBarril;
    GLint probabilidadeInimigo;
    GLint barrisDestruidos = 0;
    //Fazer um jogador exemplo (naturalmente ele é)
    //Fazer inimigo e barril exemplo
public:
    Configuracoes(int arenaAltura, int arenaLargura, GLfloat jogadorRaioCabeca, GLfloat jogadorVelocidade,
                  GLfloat inimigoRaioCabeca, GLfloat inimigoTirosPorSegundo, GLfloat inimigoVelocidadeTiro,
                  GLfloat barrilAltura, GLfloat barrilLargura, GLfloat barrilNumeroTiros, 
                          GLfloat barrilnParaGanhar, GLfloat barrilVelocidade, GLfloat barrilLimite){
        this->arenaAltura = arenaAltura;
        this->arenaLargura = arenaLargura;
        this->distMaxTiro = sqrt(pow(this->arenaAltura, 2) + pow(this->arenaLargura, 2));
        this->barrilLimite = barrilLimite;
        this->jogadorRaioCabeca = jogadorRaioCabeca;
        this->jogadorVelocidade = jogadorVelocidade;
        this->inimigoRaioCabeca = inimigoRaioCabeca;
        this->inimigoTirosPorSegundo = inimigoTirosPorSegundo;
        this->inimigoVelocidadeTiro = inimigoVelocidadeTiro;
        this->barrilAltura = barrilAltura;
        this->barrilLargura = barrilLargura;
        this->barrilnParaGanhar = barrilnParaGanhar;
        this->barrilNumeroTiros = barrilNumeroTiros;
        this->barrilVelocidade = barrilVelocidade;
        
    };
    Configuracoes(){
        this->arenaAltura = 0;
        this->arenaLargura = 0;
        this->distMaxTiro = 0;
        this->barrilLimite = 0;
        this->jogadorRaioCabeca = 0;
        this->jogadorVelocidade = 0;
        this->inimigoRaioCabeca = 0;
        this->inimigoTirosPorSegundo = 0;
        this->inimigoVelocidadeTiro = 0;
        this->barrilAltura = 0;
        this->barrilLargura = 0;
        this->barrilnParaGanhar = 0;
        this->barrilNumeroTiros = 0;
        this->barrilVelocidade = 0;
        this->LimiteXInferiorBarril = 0;
        this->LimiteXSuperiorBarril = 0;
        this->probabilidadeInimigo = 0;
    };
    // Métodos getter
    int getArenaAltura() const {
        return this->arenaAltura;
    }

    int getArenaLargura() const {
        return this->arenaLargura;
    }
    GLfloat getDistMaxTiro(){
        return this->distMaxTiro;
    }

    GLfloat getJogadorRaioCabeca() const {
        return this->jogadorRaioCabeca;
    }

    GLfloat getJogadorVelocidade() const {
        return this->jogadorVelocidade;
    }

    GLfloat getInimigoRaioCabeca() const {
        return this->inimigoRaioCabeca;
    }

    GLfloat getInimigoTirosPorSegundo() const {
        return this->inimigoTirosPorSegundo;
    }

    GLfloat getInimigoVelocidadeTiro() const {
        return this->inimigoVelocidadeTiro;
    }

    GLfloat getBarrilAltura() const {
        return this->barrilAltura;
    }

    GLfloat getBarrilLargura() const {
        return this->barrilLargura;
    }

    GLfloat getBarrilNumeroTiros() const {
        return this->barrilNumeroTiros;
    }

    GLfloat getBarrilnParaGanhar() const {
        return this->barrilnParaGanhar;
    }

    GLfloat getBarrilVelocidade() const {
        return this->barrilVelocidade;
    }

    GLfloat getBarrilLimite(){
        return this->barrilLimite;
    }

    GLint getLimiteXInferiorBarril() const {
        return this->LimiteXInferiorBarril;
    }

    GLint getLimiteXSuperiorBarril() const {
        return this->LimiteXSuperiorBarril;
    }

    GLint getProbabilidadeInimigo() const {
        return this->probabilidadeInimigo;
    }

    GLint getBarrisDestruidos() const {
        return this->barrisDestruidos;
    }
    

    // Métodos setter
    void setArenaAltura(int altura) {
        this->arenaAltura = altura;
    }

    void setArenaLargura(int largura) {
        this->arenaLargura = largura;
    }

    void setBarrilLimite(GLfloat limite){
        this->barrilLimite = limite;
    }

    void setJogadorRaioCabeca(GLfloat raio) {
        this->jogadorRaioCabeca = raio;
    }

    void setJogadorVelocidade(GLfloat velocidade) {
        this->jogadorVelocidade = velocidade;
    }

    void setInimigoRaioCabeca(GLfloat raio) {
        this->inimigoRaioCabeca = raio;
    }

    void setInimigoTirosPorSegundo(GLfloat tirosPorSegundo) {
        this->inimigoTirosPorSegundo = tirosPorSegundo;
    }

    void setInimigoVelocidadeTiro(GLfloat velocidadeTiro) {
        this->inimigoVelocidadeTiro = velocidadeTiro;
    }

    void setBarrilAltura(GLfloat altura) {
        this->barrilAltura = altura;
    }

    void setBarrilLargura(GLfloat largura) {
        this->barrilLargura = largura;
    }

    void setBarrilNumeroTiros(GLfloat numeroTiros) {
        this->barrilNumeroTiros = numeroTiros;
    }

    void setBarrilnParaGanhar(GLfloat nParaGanhar) {
        this->barrilnParaGanhar = nParaGanhar;
    }

    void setBarrilVelocidade(GLfloat velocidade) {
        this->barrilVelocidade = velocidade;
    }

    void setLimiteXInferiorBarril(GLfloat LimiteXInferior) {
        this->LimiteXInferiorBarril = LimiteXInferior +0.5;
    }

    void setLimiteXSuperiorBarril(GLfloat LimiteXSuperior) {
        this->LimiteXSuperiorBarril = LimiteXSuperior-0.5;
    }

    void setProbabilidadeInimigo(GLfloat probabilidadeInimigo) {
        this->probabilidadeInimigo = probabilidadeInimigo;
    }

    void atualizaDistMaxTiro(){
        this->distMaxTiro = sqrt(pow(this->arenaAltura, 2) + pow(this->arenaLargura, 2));
    }

    void aumentaBarrisDestruidos(){
        this->barrisDestruidos++;
    }
    bool geraInimigo(int x);
    int geraPosXBarril(int x);

    void obtemInformacoesJogo();
    
    //Criar componentes do jogo
    void criaPernaArma(GLfloat raioCabeca, GLfloat velocidadePerna, Arma &arma, Perna &esq, Perna &dir);
    Inimigo* criaComponentesBase(Arma& arma, Perna& pernaEsquerda, Perna& pernaDireita, Jogador& jogadorVazio);
    
    // Funcao que desenha algo na tela
    void imprimeTexto(GLfloat x, GLfloat y, const string& text);
    void imprimePlacar(GLfloat x, GLfloat y);
    void desenhaLimite();

    //Atualizar/remover listas
    void removeTiros(GLfloat timeDiference, list<Tiro*>& listaTiros);
    void removeTirosInimigo(GLfloat timeDiference, list<Tiro*>& listaTirosInimigo, 
                            Jogador& person, bool& gameOver);
    void removeBarris(GLfloat timeDiference, Jogador& person,list<Barril*>& listaBarris, 
                    Inimigo* inimigoBase, bool& gameOver, bool& gameWin);
    //Desenha componentes
    void desenhaTiros(list<Tiro*>& listaTiros, GLfloat r, GLfloat g, GLfloat b);
    void desenhaBarris(list<Barril*>& listaBarris, list<Tiro*>& listaTirosInimigo, Jogador& person);

    //Verificador de colisoes com barril
    void colisaoTiroBarril(list<Barril*>& listaBarris, list<Tiro*>& listaTiros);

    //Liberar memoria de ponteiros
    void liberaMemoria(list<Tiro*>&listaTiros , list<Tiro*>&listaTirosInimigo , 
                        list<Barril*>& listaBarris, Inimigo* inimigoBase);
};

#endif	/* Configuracoes_H */

