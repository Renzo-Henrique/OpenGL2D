#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <list>
#include <cstdlib>
#include "source/barril.h"
#include "source/personagem.h"
#include "source/jogador.h"
#include "source/perna.h"
#include "source/arma.h"
#include "source/configuracoes.h"
#include "source/inimigo.h"

using namespace std;
#define INC_KEY 1
#define INC_KEYIDLE 0.1 * 5
#define INTERVALO_TIROS 100*2
#define TEMPO_ESPERA 2000
//Key status
int keyStatus[256];

/*Mouse global*/
typedef struct mouse Mouse;
struct mouse{
    GLfloat gX = 0,gY = 0;
};
Mouse gMouse;

//Controla a animacao do robo
int animate = 0;

//Gerador de numeros aleatorios
// Define uma semente específica (por exemplo, 42)
#define SEED 42

//Componentes do mundo virtual sendo modelado
Configuracoes config;
GLfloat gArenaCor[4] = {0.40234, 0.3046875, 0.8828, 1}; 
//Componentes base do jogo

Perna pernaEsquerda;
Perna pernaDireita;
Arma armaJogador;
Jogador person;
Inimigo* inimigoBase = NULL;
bool gameStart = false;
bool gamePausado = false;
bool gameWin = false;
bool gameOver = false;
bool setouSeed = false;
list<Tiro*> listaTiros;
list<Tiro*> listaTirosInimigo;
list<Barril*> listaBarris;


// Obtem as configuracoes iniciais dos componentes
void configuracoesIniciais(){
    // Obtem informacoes do .xml
    config.obtemInformacoesJogo();

    inimigoBase = config.criaComponentesBase(armaJogador, pernaEsquerda, pernaDireita, person);
    gMouse.gX = 0;
    gMouse.gY = -config.getArenaAltura()/4;
    //setar seed
    srand(SEED);
}




/***
 * FUNCOES DE CALLBACK PARA O GLUT
 * 
 * ----------------------------------------------
 * 
 * FUNCOES DE CALLBACK PARA O GLUT
*/
void renderScene(void){   
    if(gameWin and gamePausado){
        // Clear the screen.
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(gArenaCor[0], gArenaCor[1], gArenaCor[2], gArenaCor[3]);
        config.desenhaLimite();

        config.imprimeTexto(-40,config.getArenaAltura()/4, "GANHOU! ");
    }
    else if(gameOver){
        // Clear the screen.
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(1, 0, 0, 1);
        config.desenhaLimite();

        config.imprimeTexto(-40,config.getArenaAltura()/4, "PERDEU! ");
    }
    else{
        if(gameWin){
            gamePausado = true;
        }
        // Clear the screen.
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(gArenaCor[0], gArenaCor[1], gArenaCor[2], gArenaCor[3]);
        config.desenhaLimite();

        person.desenha();
        Inimigo* inimigoCriado = NULL;
        //somente gera barris se passar de TEMPOESPERA segundos
        if(gameStart){
            if( ! setouSeed ){
                setouSeed = true;
                srand(SEED);
            }
            //Cria novos barris se nao existir um como head
            if(listaBarris.empty()){
                int posX = config.geraPosXBarril(rand());
                //cria quando for 1
                if(config.geraInimigo(rand())){
                    inimigoCriado = inimigoBase->copia();
                }
                //cria outro barril
                Barril* barrilAtual = new Barril(config.getBarrilAltura(), config.getBarrilLargura(),
                                                config.getBarrilVelocidade(), config.getBarrilNumeroTiros(),
                                                    posX, config.getArenaAltura()/2, inimigoCriado);
                listaBarris.push_back(barrilAtual);
            }
            else if( listaBarris.back()->get_gY() < config.getBarrilLimite()){
                //int aleatorio = rand();
                //cout << "aleatorio " << aleatorio << endl;
                int posX = config.geraPosXBarril(rand());
                
                //cria quando for 1
                if(config.geraInimigo(rand())){
                    inimigoCriado = inimigoBase->copia();
                }
                //cria outro barril
                Barril* barrilAtual = new Barril(config.getBarrilAltura(), config.getBarrilLargura(),
                                                config.getBarrilVelocidade(), config.getBarrilNumeroTiros(),
                                                    posX, config.getArenaAltura()/2, inimigoCriado);
                listaBarris.push_back(barrilAtual);
            }
        }
        //tempo maior que TEMPO_ESPERA segundos
        else if(glutGet(GLUT_ELAPSED_TIME) > TEMPO_ESPERA){
            gameStart = true;
        }
        //desenhando lista de tiros do jogador
        config.desenhaTiros(listaTiros, 0, 0, 0);
        config.desenhaTiros(listaTirosInimigo, 1, 1, 1);
        config.desenhaBarris(listaBarris, listaTirosInimigo, person);

        //confere colisao Barris
        config.imprimePlacar( -20*config.getArenaLargura()/100 , 47*config.getArenaAltura()/100);
    }
    
    glutSwapBuffers(); // Desenha the new frame of the game.
}
void keyPress(unsigned char key, int x, int y){   
    switch (key)
    {
        case '1':
            animate = !animate;
            break;
        case 'a':
        case 'A':
            keyStatus[(int)('a')] = 1; //Using keyStatus trick
            break;
        case 'd':
        case 'D':
            keyStatus[(int)('d')] = 1; //Using keyStatus trick
            break;
        case 'w':
        case 'W':
            keyStatus[(int)('w')] = 1; //Using keyStatus trick
            break;
        case 's':
        case 'S':
            keyStatus[(int)('s')] = 1; //Using keyStatus trick
            break;
            
            break;
        case 27 :
            exit(0);
    }
    glutPostRedisplay();
}

void keyup(unsigned char key, int x, int y){   
    keyStatus[(int)(key)] = 0;
    glutPostRedisplay();
}

void ResetKeyStatus(){
    int i;
    //Initialize keyStatus
    for(i = 0; i < 256; i++)
       keyStatus[i] = 0; 
}

void miraDeslocamentoMouse(int x, int y){
    x = config.getArenaLargura()/2 - x;
    y = config.getArenaAltura()/2 - y;

    // Converte o ângulo de radianos para graus
    GLfloat anguloRadianos = atan2( x - gMouse.gX , y - gMouse.gY );
    GLfloat angulo = anguloRadianos * (180.0 / M_PI);
    //cout << (x - gMouse.gX ) << "::angulo que sera movido\n";
    person.get_arma().mexeAngulo((x - gMouse.gX )/5 + person.get_arma().get_angulo());
    gMouse.gX = x;
    gMouse.gY = y;
}
void miraBaseArma(int x, int y){
    y = config.getArenaAltura()/2 - y;
    x = x - config.getArenaLargura()/2 ;
    Ponto2D pontaArma = person.obtemGlobalBaseArma();
    Ponto2D mousePos = Ponto2D(x, y);

    GLfloat anguloGraus = mousePos.anguloEntre(pontaArma) * (180.0 / M_PI);

    person.get_arma().modificaAngulo(anguloGraus - 90);
}

void motion(int x, int y){
    //mexer a mira
    miraDeslocamentoMouse(x, y);
}
void mouse(int button, int state, int x, int y){
    //somente botao esquerdo
    if(GLUT_LEFT_BUTTON == button){
        static GLdouble previousTimeTiro = -5;
        GLdouble currentTime, timeDiferenceTiro;
        //Pega o tempo que passou do inicio da aplicacao
        currentTime = glutGet(GLUT_ELAPSED_TIME);
        // Calcula o tempo decorrido desde de o ultima tiro
        timeDiferenceTiro = currentTime - previousTimeTiro;
        
        //Atira num intervalo de tempo especifico
        if(timeDiferenceTiro > INTERVALO_TIROS){
            listaTiros.push_front(person.atira(config.getDistMaxTiro()));
            previousTimeTiro = currentTime;
        }
    }
    
    glutPostRedisplay();
   
}

void init(void){
    ResetKeyStatus();
    // The color the windows will redraw. Its done to erase the previous frame.
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black, no opacity(alpha).
 
    glMatrixMode(GL_PROJECTION); // Select the projection matrix
    glOrtho(-(config.getArenaLargura()/2),     // X coordinate of left edge             
            (config.getArenaLargura()/2),     // X coordinate of right edge            
            -(config.getArenaAltura()/2),     // Y coordinate of bottom edge             
            (config.getArenaAltura()/2),     // Y coordinate of top edge             
            -100,     // Z coordinate of the “near” plane            
            100);    // Z coordinate of the “far” plane
    glMatrixMode(GL_MODELVIEW); // Select the projection matrix   
    glLoadIdentity();
      
}

void idle(void)
{   
    static GLdouble previousTime = glutGet(GLUT_ELAPSED_TIME);
    
    GLdouble currentTime, timeDiference;
    //Pega o tempo que passou do inicio da aplicacao
    currentTime = glutGet(GLUT_ELAPSED_TIME);
    // Calcula o tempo decorrido desde de a ultima frame.
    timeDiference = currentTime - previousTime;
    //Atualiza o tempo do ultimo frame ocorrido
    previousTime = currentTime;

    double inc = INC_KEYIDLE;
    //Treat keyPress
    if(keyStatus[(int)('a')]){
        person.movimentaEmX(timeDiference, -inc, config.getArenaLargura());
    }
    if(keyStatus[(int)('d')]){
        person.movimentaEmX(timeDiference, +inc, config.getArenaLargura());
    }
    if(keyStatus[(int)('w')]){
        person.movimentaEmY(timeDiference, +inc, config.getArenaAltura());
    }
    if(keyStatus[(int)('s')]){
        person.movimentaEmY(timeDiference, -inc, config.getArenaAltura());
    }
    
    // Percorrendo a lista e removendo tiros nao validos
    config.removeTiros(timeDiference, listaTiros);
    // Percorrendo a lista e removendo tiros nao validos
    config.removeTirosInimigo(timeDiference, listaTirosInimigo, person, gameOver);
    // Percorrendo a lista e removendo barris nao validos, além de colisao
    config.removeBarris(timeDiference, person, listaBarris, inimigoBase, 
                    gameOver, gameWin);
   
    /*Tentativa de colisao de barril-tiro*/
    config.colisaoTiroBarril(listaBarris, listaTiros);

    glutPostRedisplay();
}
 
int main(int argc, char *argv[]){   
    //configura o inicial dos componentes do jogo
    configuracoesIniciais();

    // Initialize openGL with Double buffer and RGB color without transparency.
    // Its interesting to try GLUT_SINGLE instead of GLUT_DOUBLE.
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
 
    // Create the window.
    glutInitWindowSize(config.getArenaLargura(), config.getArenaAltura());
    glutInitWindowPosition(500,50);
    glutCreateWindow("Trabalho 2D");
 
    // Define callbacks.
    glutDisplayFunc(renderScene);
    glutKeyboardFunc(keyPress);
    glutKeyboardUpFunc(keyup);
    glutIdleFunc(idle);
    glutMouseFunc(mouse);
    glutPassiveMotionFunc(motion);
    
    init();
 
    glutMainLoop();
    
    config.liberaMemoria(listaTiros , listaTirosInimigo ,listaBarris, inimigoBase);
    return 0;
}
