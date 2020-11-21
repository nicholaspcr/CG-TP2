void parametrosIniciais() {
    movNave=0;
    contVida=3; 
    movHorInimigo=VELOC_INIMIGO;
    movVertInimigo=VELOC_INIMIGO; 
    movTiro=VELOC_TIRO; 
    inimigoRand1=0; 
    inimigoRand2=0;
    inimigoRand3=0;
    delayGameOver=0; 
    rasante=0;
    naveAtirando=false;
    inimigoAtirando=false; 
    inimigoAtacando=false; 
    mouseHabilitado=false; 
    pause=false; 
}

// cria uma probabilidade de um evento qualquer ocorrer
bool probEventoOcorrer(int range, int min, int max) {
    int numAleatorio = rand()%range;
    bool evento = false;
    if ((numAleatorio >= min) && (numAleatorio < max)) {
        evento = true;
    }
    return evento;
}

// detecta a colisão entre dois objetos distintos
bool detectaColisao(OBJETO obj1, OBJETO obj2) {
    if ((obj1.y - obj1.alt/2) > (obj2.y + obj2.alt/2))
        return false;
    if ((obj1.y + obj1.alt/2) < (obj2.y - obj2.alt/2))
        return false;
    if ((obj1.x + obj1.larg/2) < (obj2.x - obj2.larg/2))
        return false;
    if ((obj1.x - obj1.larg/2) > (obj2.x + obj2.larg))
        return false; 
    return true;
}

bool detectaGameOver() {
    if (contVida == 0) {
        return true;
    } else {
        return false;
    }
}