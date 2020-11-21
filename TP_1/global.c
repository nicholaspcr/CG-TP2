// definição do tipo objeto que será usado
// para definir um ponto
typedef struct ponto {
    float x, y;
} PONTO;

// definição do tipo objeto que será usado
// para desenhar quadrados na tela
typedef struct objeto {
    float x, y, larg, alt;
    bool existe;
} OBJETO;

// cria a instancia de um objeto qualquer
OBJETO instanciaObjeto(int x, int y, int w, int h) {
    OBJETO obj;
    obj.x = x;
    obj.y = y;
    obj.larg = w;
    obj.alt = h;
    obj.existe = true;
    return obj;
}

// texturas relacionadas ao fundo e à nave
// texturas relacionadas aos inimigos
GLuint idTexturaMenu=0, idTexturaMundo=0, idTexturaNave=0, idTexturaTiroNave=0, idTexturaInimigoComum1=0, idTexturaInimigoComum2=0, 
    idTexturaInimigoComum3=0, idTexturaInimigoChefe=0, idTexturaTiroInimigo=0, idTexturaGameOver=0;

// declaração de todas as variáveis globais necessárias ao programa
// variáveis globais
OBJETO menu, mundo, gameOver, nave, tiroNave, vidaNave1, vidaNave2, vidaNave3, tiroIniComum, tiroIniChefe, tiroIniAtacando, 
    inimigo[QTD_INIMIGOS], inimigoChefe[QTD_CHEFES];
PONTO posicaoMouse;
int movNave=0, contVida=3, movHorInimigo=VELOC_INIMIGO, movVertInimigo=VELOC_INIMIGO, movTiro=VELOC_TIRO, inimigoRand1=0, inimigoRand2=0, inimigoRand3=0,
    tela=0, delayGameOver=0, rasante=0;
bool naveAtirando=false, inimigoAtirando=false, inimigoAtacando=false, mouseHabilitado=false, pause=false;