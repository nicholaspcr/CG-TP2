void desenhaObjeto(OBJETO obj) {
    if (obj.existe == true) {
        glPushMatrix();
            glTranslatef(obj.x, obj.y, 0);
            glBegin(GL_TRIANGLE_FAN);
                glVertex2f(-obj.larg/2, -obj.alt/2); // v3---v2
                glVertex2f( obj.larg/2, -obj.alt/2); // |     |
                glVertex2f( obj.larg/2,  obj.alt/2); // |     |
                glVertex2f(-obj.larg/2,  obj.alt/2); // v0---v1
            glEnd();
        glPopMatrix();
    }
}

void fase1() {
        colocaTextura(mundo, idTexturaMundo);
        
        // desenha a nave e o tiro da nave   
        colocaTextura(nave, idTexturaNave);
        colocaTextura(tiroNave, idTexturaTiroNave);

        // desenha vidas
        glColor3f(1, 0, 0);
        if (vidaNave1.existe == true) {
            desenhaObjeto(vidaNave1);
        }
        if (vidaNave2.existe == true) {
            desenhaObjeto(vidaNave2);
        }
        if (vidaNave3.existe == true) {
            desenhaObjeto(vidaNave3); 
        }

        // desenha a primeira fileira de inimigos
        colocaTextura(inimigo[0], idTexturaInimigoComum1);
        colocaTextura(inimigo[1], idTexturaInimigoComum1);
        colocaTextura(inimigo[2], idTexturaInimigoComum1);
        colocaTextura(inimigo[3], idTexturaInimigoComum1);
        colocaTextura(inimigo[4], idTexturaInimigoComum1);
        colocaTextura(inimigo[5], idTexturaInimigoComum1);
        colocaTextura(inimigo[6], idTexturaInimigoComum1);                        

        // desenha a segunda fileira de inimigos
        colocaTextura(inimigo[7], idTexturaInimigoComum2);
        colocaTextura(inimigo[8], idTexturaInimigoComum2);
        colocaTextura(inimigo[9], idTexturaInimigoComum2);
        colocaTextura(inimigo[10], idTexturaInimigoComum2);
        colocaTextura(inimigo[11], idTexturaInimigoComum2);
        colocaTextura(inimigo[12], idTexturaInimigoComum2);
        colocaTextura(inimigo[13], idTexturaInimigoComum2);    

        // desenha a terceira fileira de inimigos
        colocaTextura(inimigo[14], idTexturaInimigoComum3);
        colocaTextura(inimigo[15], idTexturaInimigoComum3);
        colocaTextura(inimigo[16], idTexturaInimigoComum3);
        colocaTextura(inimigo[17], idTexturaInimigoComum3);
        colocaTextura(inimigo[18], idTexturaInimigoComum3);
        colocaTextura(inimigo[19], idTexturaInimigoComum3);
        colocaTextura(inimigo[20], idTexturaInimigoComum3);      

        // desenha a fileira de inimigos chefe
        colocaTextura(inimigoChefe[0], idTexturaInimigoChefe);
        colocaTextura(inimigoChefe[1], idTexturaInimigoChefe);
        colocaTextura(inimigoChefe[2], idTexturaInimigoChefe);         

        //desenha o tiro dos inimigos
        colocaTextura(tiroIniComum, idTexturaTiroInimigo);
        colocaTextura(tiroIniAtacando, idTexturaTiroInimigo);
        colocaTextura(tiroIniChefe, idTexturaTiroInimigo);
}

// rotina de desenho
void desenhaCena() {
    // limpa a tela (com a cor definida por glClearColor(r,g,b)) para que
    // possamos desenhar    
    glClear(GL_COLOR_BUFFER_BIT);

  switch (tela) {
      case (0):
        colocaTextura(menu, idTexturaMenu);                   
        break;
    case (1):   
        fase1();
        if (detectaGameOver()) {
            colocaTextura(gameOver, idTexturaGameOver);
            delayGameOver++;
            if (delayGameOver >= 100) {
                tela = 0;
                parametrosIniciais();
                inicializa();                
            }
        }
        break;
    }

    glutSwapBuffers();
}