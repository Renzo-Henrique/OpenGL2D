#include "configuracoes.h"

int Configuracoes::geraPosXBarril(int x){
    int intervalo = std::abs(this->getLimiteXSuperiorBarril() - this->getLimiteXInferiorBarril());
    return (x % intervalo) + this->getLimiteXInferiorBarril();
}

bool Configuracoes::geraInimigo(int x){ 
    return x % this->getProbabilidadeInimigo() == 0;
}

void Configuracoes::criaPernaArma(GLfloat raioCabeca, GLfloat velocidadePerna, Arma &arma, Perna &esq, Perna &dir){
    esq = Perna(2 * raioCabeca, raioCabeca/2, 
                        velocidadePerna, +3*raioCabeca/5, 0, 1);
    dir = Perna(2 * raioCabeca, raioCabeca/2, 
                        velocidadePerna, -3*raioCabeca/5, -2 * raioCabeca, -1);

    arma = Arma(3.7 * raioCabeca, raioCabeca/2, 0,  raioCabeca + raioCabeca/4, -0.8*raioCabeca);
}

Inimigo* Configuracoes::criaComponentesBase(Arma& arma, Perna& pernaEsquerda, Perna& pernaDireita, Jogador& jogadorVazio){

    this->criaPernaArma(this->getJogadorRaioCabeca(), this->getJogadorVelocidade()*3, arma, pernaEsquerda, pernaDireita);
    jogadorVazio = Jogador(this->getJogadorRaioCabeca(), arma, pernaEsquerda, pernaDireita, 
                    0, -this->getArenaAltura()/4, this->getJogadorVelocidade(), 1);
    
    this->criaPernaArma(this->getInimigoRaioCabeca(), this->getBarrilVelocidade(), arma, pernaEsquerda, pernaDireita);

    return new Inimigo(this->getInimigoRaioCabeca(), arma, pernaEsquerda, pernaDireita, 
                    this->getBarrilLargura()/4, -this->getBarrilAltura()/2, 0, 
                    this->getInimigoTirosPorSegundo(), this->getInimigoVelocidadeTiro());

}


void Configuracoes::obtemInformacoesJogo(){
    tinyxml2::XMLDocument xmlDoc;
    if(xmlDoc.LoadFile("configuracoes.xml") != tinyxml2::XML_SUCCESS) {
        cerr << "Erro ao carregar o arquivo XML." << endl;
        return;
    }
    tinyxml2::XMLElement* jogoElement = xmlDoc.FirstChildElement("jogo");
    if (jogoElement) {
        // Lendo a tag <arena>
        tinyxml2::XMLElement* arenaElement = jogoElement->FirstChildElement("arena");
        if (arenaElement) {
            int altura, largura;
            arenaElement->QueryIntAttribute("altura", &altura);
            arenaElement->QueryIntAttribute("largura", &largura);
            this->setArenaAltura(altura);
            this->setArenaLargura(largura);
            this->atualizaDistMaxTiro();
            
        }

        // Lendo a tag <jogador>
        tinyxml2::XMLElement* jogadorElement = jogoElement->FirstChildElement("jogador");
        if (jogadorElement) {
            GLfloat raioCabeca, velocidade;
            jogadorElement->QueryFloatAttribute("raioCabeca", &raioCabeca);
            jogadorElement->QueryFloatAttribute("velocidade", &velocidade);
            this->setJogadorRaioCabeca(raioCabeca);
            this->setJogadorVelocidade(velocidade);
        }

        // Lendo a tag <inimigo>
        tinyxml2::XMLElement* inimigoElement = jogoElement->FirstChildElement("inimigo");
        if (inimigoElement) {
            GLfloat raioCabeca, tirosPorSegundo, velocidadeTiro;
            inimigoElement->QueryFloatAttribute("raioCabeca", &raioCabeca);
            inimigoElement->QueryFloatAttribute("tirosPorSegundo", &tirosPorSegundo);
            inimigoElement->QueryFloatAttribute("velocidadeTiro", &velocidadeTiro);
            this->setInimigoRaioCabeca(raioCabeca);
            this->setInimigoTirosPorSegundo(tirosPorSegundo);
            this->setInimigoVelocidadeTiro(velocidadeTiro);
            this->setProbabilidadeInimigo(PROBABILIDADE_INIMIGO);
        }

        // Lendo a tag <barril>
        tinyxml2::XMLElement* barrilElement = jogoElement->FirstChildElement("barril");
        if (barrilElement) {
            GLfloat altura, largura, numeroTiros, nParaGanhar, velocidade;
            barrilElement->QueryFloatAttribute("altura", &altura);
            barrilElement->QueryFloatAttribute("largura", &largura);
            barrilElement->QueryFloatAttribute("numeroTiros", &numeroTiros);
            barrilElement->QueryFloatAttribute("nParaGanhar", &nParaGanhar);
            barrilElement->QueryFloatAttribute("velocidade", &velocidade);
            this->setBarrilAltura(altura);
            this->setBarrilLargura(largura);
            this->setBarrilNumeroTiros(numeroTiros);
            this->setBarrilnParaGanhar(nParaGanhar);
            this->setBarrilVelocidade(velocidade);

            // Mudando o intervalo da distribuição para ficar dentro da tela
            GLfloat LimiteXInferiorBarril = -this->getArenaLargura()/2 + this->getBarrilLargura()/2;
            GLfloat LimiteXSuperiorBarril = -1*LimiteXInferiorBarril;
            this->setLimiteXInferiorBarril(LimiteXInferiorBarril);
            this->setLimiteXSuperiorBarril(LimiteXSuperiorBarril);

        } else {
            cerr << "Tag <barril> não encontrada." << endl;
        }
    } else {
        cerr << "Tag <jogo> não encontrada." << endl;
    }
    xmlDoc.Clear();

}

void Configuracoes::imprimeTexto(GLfloat x, GLfloat y, const string& text){
    glColor3f(1, 1, 1);
    // Define a posição onde vai começar a imprimir
    glRasterPos2f(x, y);
    // Imprime a string diretamente
    for (char c : text) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c); // Use o tipo de fonte desejado (GLUT_BITMAP_TIMES_ROMAN_24 neste exemplo)
    }
}

void Configuracoes::imprimePlacar(GLfloat x, GLfloat y){
    static char str[1000];
    //void * font = GLUT_BITMAP_9_BY_15;
    static void * font = GLUT_BITMAP_HELVETICA_18;
    glColor3f(0, 0, 0);
    //Cria a string a ser impressa
    char *tmpStr;
    sprintf(str, "Barris destruidos: %d / %d", this->getBarrisDestruidos(), (int)this->getBarrilnParaGanhar());
    //Define a posicao onde vai comecar a imprimir
    glRasterPos2f(x, y);
    //Imprime um caractere por vez
    tmpStr = str;
    while( *tmpStr ){
        glutBitmapCharacter(font, *tmpStr);
        tmpStr++;
    }
}

void Configuracoes::desenhaLimite() {
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_LINE_STIPPLE);
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineStipple(1, 0x0F0F); // Padrão de linha pontilhada (alternância de 1 bit ligado/desligado)
    glBegin(GL_LINES);
    glVertex2f(-this->getArenaLargura()/2, 0); // Ponto inicial da linha
    glVertex2f(this->getArenaLargura()/2, 0);  // Ponto final da linha
    glEnd();
    glDisable(GL_LINE_STIPPLE);
    glFlush();
}

void Configuracoes::removeTiros(GLfloat timeDiference, list<Tiro*>& listaTiros){
    auto it = listaTiros.begin();
    while (it != listaTiros.end()) {

        (*it)->move(timeDiference);

        if ( !(*it)->valido()) {
            Tiro* tiroAtual = *it;
            it = listaTiros.erase(it);  // Remove o elemento e retorna o próximo iterador válido
            delete tiroAtual;
        } else {
            ++it;  // Avança para o próximo elemento
        }
    }
}

void Configuracoes::removeTirosInimigo(GLfloat timeDiference, list<Tiro*>& listaTirosInimigo, Jogador& person, bool& gameOver){
    auto it_inimigo = listaTirosInimigo.begin();
    while (it_inimigo != listaTirosInimigo.end()) {

        Tiro* tiroAtual = *it_inimigo;
        tiroAtual->move(timeDiference);

        if ( !tiroAtual->valido()) {
            
            it_inimigo = listaTirosInimigo.erase(it_inimigo);  // Remove o elemento e retorna o próximo iterador válido
            delete tiroAtual;
        }
        //Colisao com o personagem!
        else if(person.atingido(tiroAtual)){
            gameOver = true;
        }
        else {
            ++it_inimigo;  // Avança para o próximo elemento
        }
    }
}

void Configuracoes::removeBarris(GLfloat timeDiference, Jogador& person,list<Barril*>& listaBarris, 
                    Inimigo* inimigoBase, bool& gameOver, bool& gameWin){
    auto it_ = listaBarris.begin();
    while (it_ != listaBarris.end()) {
        
    
        Barril* barrilAtual = *it_;

        if(barrilAtual){
            barrilAtual->move(timeDiference);
            //colisao com personagem
            if(barrilAtual->colisao(person.get_gX(), person.get_gY(), person.get_raioCabeca())){
            
                gameOver = true;
            }
            //tirando barril da arena
            if ( !barrilAtual->valido(this->getArenaAltura())) {
                it_ = listaBarris.erase(it_);  // Remove o elemento e retorna o próximo iterador válido

                delete barrilAtual;
            } 
            else if(barrilAtual->destruido()){
                this->aumentaBarrisDestruidos();
                it_ = listaBarris.erase(it_);  // Remove o elemento e retorna o próximo iterador válido

                delete barrilAtual;

                if(this->getBarrilnParaGanhar() <= this->getBarrisDestruidos()){
                    gameWin = true;
                }
            }
            else {
                ++it_;  // Avança para o próximo elemento
            }
        }
        
    }
}



void Configuracoes::desenhaTiros(list<Tiro*>& listaTiros, GLfloat r, GLfloat g, GLfloat b){
    // Tiros
    auto it = listaTiros.begin();
    while (it != listaTiros.end()) {
        (*it)->desenha(r,g,b);
        
        ++it;
    }
}

void Configuracoes::desenhaBarris(list<Barril*>& listaBarris, list<Tiro*>& listaTirosInimigo, Jogador& person){
    // Barris
    auto it = listaBarris.begin();
    while (it != listaBarris.end()) {
        Barril* barril = *it;

        Inimigo* inimigoAtual = barril->getInimigo();
        if(inimigoAtual){
            
            //verificar se pode atirar
            GLdouble currentTime = glutGet(GLUT_ELAPSED_TIME);
            if(inimigoAtual->podeAtirar(currentTime, barril->get_gY() , person.get_gY())){

                //mirando no ponto
                inimigoAtual->miraPonto(person.get_gX(), person.get_gY(), barril->get_gX(), barril->get_gY());
                inimigoAtual->setUltimoTiro(currentTime);
                listaTirosInimigo.push_front( inimigoAtual->atira(this->getDistMaxTiro(),barril->get_gX(), barril->get_gY()));
            }
        }
        
        barril->desenha();
        
        ++it;
    }
}

void Configuracoes::colisaoTiroBarril(list<Barril*>& listaBarris, list<Tiro*>& listaTiros){

    auto it_barril = listaBarris.begin();
    while (it_barril != listaBarris.end()) {

        Barril* barrilAtual = (*it_barril);

        //percorrendo a lista de barris
        auto it_tiro = listaTiros.begin();
        while (it_tiro != listaTiros.end()){
            Tiro* tiroAtual = *it_tiro;

            //verifica se ja esta na lista
            if(barrilAtual->colisaoTiro(tiroAtual)){
                barrilAtual->diminuiVidaAtual();
                //retira iterador
                it_tiro = listaTiros.erase(it_tiro);  // Remove o elemento e retorna o próximo iterador válido
                delete tiroAtual;
            }
            else{
                ++it_tiro;
            }
        }
        
        ++it_barril;
    }
}

void Configuracoes::liberaMemoria(list<Tiro*>&listaTiros , list<Tiro*>&listaTirosInimigo , 
                                    list<Barril*>& listaBarris, Inimigo* inimigoBase){
    // Libere a memória alocada para cada ponteiro na lista
    for (Tiro* ptr : listaTiros) {
        delete ptr;
    }
    for (Tiro* ptr : listaTirosInimigo) {
        delete ptr;
    }
    for (Barril* ptr : listaBarris) {
        delete ptr;
    }

    delete inimigoBase;
}