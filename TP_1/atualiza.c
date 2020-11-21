// callback do evento timer
void atualizaCena(int periodo) {

    nave = executaMovNave(nave);
    nave = controleMovNave(nave);

    if (mouseHabilitado == true) {
        nave.x += (posicaoMouse.x - nave.x)/50.0f;
    }

    executaMovHorInimigo();
    controleMovHorInimigo();

    if (naveAtirando == true && tiroNave.y >= ALTURA_DO_MUNDO-2) {
        tiroNave = instanciaObjeto(nave.x, nave.y + (nave.alt/2), 16, 16);
        //parar_musica();        
        //tocar_musica("../mus/musTiro.ogg", 1);  
    }
    tiroNave.y += movTiro; 

    // probabilidade do inimigo comum atirar
    inimigoAtirando = probEventoOcorrer(1000, 950, 1000);
    if (inimigoAtirando == true && tiroIniComum.y <= 0) {
        inimigoRand1 = escolheInimigo(QTD_INIMIGOS);
        if (inimigo[inimigoRand1].existe == true) {
            tiroIniComum = instanciaObjeto(inimigo[inimigoRand1].x, inimigo[inimigoRand1].y - ((inimigo[inimigoRand1].alt/2)-4), 16, 16);         
        }        
    }
    // decrementa o y da bala somente até ela sair completamente da tela
    if (tiroIniComum.y > -tiroIniComum.alt/2) {
        tiroIniComum.y -= movTiro/3;
    }    

    // probabilidade do inimigo chefe atirar
    inimigoAtirando = probEventoOcorrer(1000, 975, 1000);
    if (inimigoAtirando == true && tiroIniChefe.y <= 0) {
        inimigoRand2 = escolheInimigo(QTD_CHEFES);
        if (inimigoChefe[inimigoRand2].existe == true) {
            tiroIniChefe = instanciaObjeto(inimigoChefe[inimigoRand2].x, inimigoChefe[inimigoRand2].y - ((inimigoChefe[inimigoRand2].alt/2)-4), 24, 24); 
        }
    }
    // decrementa o y da bala somente até ela sair completamente da tela
    if (tiroIniChefe.y > -tiroIniChefe.alt/2) {
        tiroIniChefe.y -= movTiro/3;
    }

    // inimigo comum ataca periodicamente
    if (rasante%230 == 0 && rasante>=230) {
        // escolhe um inimigo comum para atacar
        inimigoAtacando = true;
        inimigoRand3 = escolheInimigo(QTD_INIMIGOS);           
    }

    if (inimigoAtacando == true) {
        inimigo[inimigoRand3].y -= movVertInimigo;
        if (inimigo[inimigoRand3].y == 300) {
            tiroIniAtacando = instanciaObjeto(inimigo[inimigoRand3].x, inimigo[inimigoRand3].y - ((inimigo[inimigoRand3].alt/2)-4), 16, 16);                        
        }
        tiroIniAtacando.y -= movTiro/3;        
    }
    
    detectaColisaoNave();
    verificaVidas();

    detectaColisaoInimigo(); 

    rasante++;

    // Pede ao GLUT para redesenhar a tela, assim que possível
    glutPostRedisplay();

    // Se registra novamente, para que fique sempre sendo chamada (30 FPS)
    glutTimerFunc(periodo, atualizaCena, periodo);
}