// Inicia algumas variáveis de estado
void inicializa() {
    tocar_musica("../mus/musTema.ogg", -1);    

    srand(time(NULL));
    inimigoRand1 = escolheInimigo(QTD_INIMIGOS);
    inimigoRand2 = escolheInimigo(QTD_CHEFES);
    inimigoRand3 = escolheInimigo(QTD_INIMIGOS);

    glClearColor(1, 1, 1, 1); // branco

    // habilita mesclagem de cores, para termos suporte a texturas
    // com transparência
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // instancia menu e carrega sua textura
    menu = instanciaObjeto((LARGURA_DO_MUNDO/2), (ALTURA_DO_MUNDO/2), LARGURA_DO_MUNDO-2, ALTURA_DO_MUNDO-2);
    carregaTextura(&idTexturaMenu, "../img/menu.png");   

    // instancia mundo e carrega sua textura
    mundo = instanciaObjeto((LARGURA_DO_MUNDO/2), (ALTURA_DO_MUNDO/2), LARGURA_DO_MUNDO-2, ALTURA_DO_MUNDO-2);
    carregaTextura(&idTexturaMundo, "../img/mundo.png");

    // instancia game over e carrega sua textura
    gameOver = instanciaObjeto((LARGURA_DO_MUNDO/2), (ALTURA_DO_MUNDO/2), LARGURA_DO_MUNDO-2, ALTURA_DO_MUNDO-2);
    carregaTextura(&idTexturaGameOver, "../img/gameOver.png");        
    
    // instancia nave e carrega sua textura
    nave = instanciaObjeto(LARGURA_DO_MUNDO/2, 45, 64, 64);
    carregaTextura(&idTexturaNave, "../img/nave.png");

    // instancia o tiro da nave e carrega sua textura
    tiroNave = instanciaObjeto(nave.x, ALTURA_DO_MUNDO-2, 16, 16);
    carregaTextura(&idTexturaTiroNave, "../img/tiroNave.png");

    // instancia as vidas da nave
    vidaNave1 = instanciaObjeto(15, 15, 20, 20);
    vidaNave2 = instanciaObjeto(45, 15, 20, 20);
    vidaNave3 = instanciaObjeto(75, 15, 20, 20);    

    // instancia a primeira linha de inimigos e carrega sua textura
    inimigo[0] = instanciaObjeto(250, ALTURA_DO_MUNDO-150, 32, 32);
    inimigo[1] = instanciaObjeto(300, ALTURA_DO_MUNDO-150, 32, 32);
    inimigo[2] = instanciaObjeto(350, ALTURA_DO_MUNDO-150, 32, 32);
    inimigo[3] = instanciaObjeto(400, ALTURA_DO_MUNDO-150, 32, 32);
    inimigo[4] = instanciaObjeto(450, ALTURA_DO_MUNDO-150, 32, 32);     
    inimigo[5] = instanciaObjeto(500, ALTURA_DO_MUNDO-150, 32, 32);
    inimigo[6] = instanciaObjeto(550, ALTURA_DO_MUNDO-150, 32, 32);
    carregaTextura(&idTexturaInimigoComum1, "../img/inimigoComum1.png");     

    // instancia a segunda linha de inimigos e carrega sua textura
    inimigo[7] = instanciaObjeto(250, ALTURA_DO_MUNDO-200, 32, 32);    
    inimigo[8] = instanciaObjeto(300, ALTURA_DO_MUNDO-200, 32, 32);
    inimigo[9] = instanciaObjeto(350, ALTURA_DO_MUNDO-200, 32, 32);  
    inimigo[10] = instanciaObjeto(400, ALTURA_DO_MUNDO-200, 32, 32);  
    inimigo[11] = instanciaObjeto(450, ALTURA_DO_MUNDO-200, 32, 32);  
    inimigo[12] = instanciaObjeto(500, ALTURA_DO_MUNDO-200, 32, 32);                       
    inimigo[13] = instanciaObjeto(550, ALTURA_DO_MUNDO-200, 32, 32);
    carregaTextura(&idTexturaInimigoComum2, "../img/inimigoComum2.png");           

    // instancia a terceira linha de inimigos e carrega sua textura
    inimigo[14] = instanciaObjeto(250, ALTURA_DO_MUNDO-250, 32, 32);        
    inimigo[15] = instanciaObjeto(300, ALTURA_DO_MUNDO-250, 32, 32);
    inimigo[16] = instanciaObjeto(350, ALTURA_DO_MUNDO-250, 32, 32);  
    inimigo[17] = instanciaObjeto(400, ALTURA_DO_MUNDO-250, 32, 32);  
    inimigo[18] = instanciaObjeto(450, ALTURA_DO_MUNDO-250, 32, 32);  
    inimigo[19] = instanciaObjeto(500, ALTURA_DO_MUNDO-250, 32, 32);
    inimigo[20] = instanciaObjeto(550, ALTURA_DO_MUNDO-250, 32, 32);
    carregaTextura(&idTexturaInimigoComum3, "../img/inimigoComum3.png");       

    // instancia a linha de inimigos chefe e carrega sua textura
    inimigoChefe[0] = instanciaObjeto(310, ALTURA_DO_MUNDO-90, 48, 48);
    inimigoChefe[1] = instanciaObjeto(400, ALTURA_DO_MUNDO-90, 48, 48);
    inimigoChefe[2] = instanciaObjeto(490, ALTURA_DO_MUNDO-90, 48, 48);
    carregaTextura(&idTexturaInimigoChefe, "../img/inimigoChefe.png");

    // carrega a textura do tiro do inimigo
    carregaTextura(&idTexturaTiroInimigo, "../img/tiroInimigo.png");

    glutSwapBuffers();
}