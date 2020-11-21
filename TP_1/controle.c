// callback de evento de movimento do mouse
void movimentoMouse(int x, int y) {
    posicaoMouse.x = x;
    posicaoMouse.y = y;
}

// callback de evento de clique do mouse
void cliqueMouse(int button, int state, int x, int y) {
    // se clicar no botão esquerdo
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (mouseHabilitado) {
            naveAtirando = true;
        }
        if (tela == 0) {
            if ((x >= 252) && (x <= 577) && (y >= 162) && (y <= 237)) {
                tela = 1;
            }
            if ((x >= 280) && (x <= 550) && (y >= 267) && (y <= 332)) {
                exit(0);                
            }
        }
    }

    // se liberar o botão esquerdo  
    if ((button == GLUT_LEFT_BUTTON ) && (state == GLUT_UP)) {
        naveAtirando = false;        
    }    
}

// callback de evento de teclado
void teclaPressionada(unsigned char key, int x, int y) {
   switch(key) {
        // tecla ESC
        case 27:    
            exit(0);
            break;
        // tecla ESPAÇO
        case 32:
            naveAtirando = true;
            break;
        // habilita ou desabilita jogar pelo mouse
        case 'm':
        case 'M':
            mouseHabilitado = !mouseHabilitado;                      
        case 'p':
        case 'P':
            pause = !pause;
            if (pause == 1) {
                //glutTimerFunc(16, frame, 0);
            }
            break;
        default:
            break;
   }
}

// callback de evento de teclado
void teclaLiberada(unsigned char key, int x, int y) {
   switch(key) {
        // tecla ESPAÇO
        case 32:
            naveAtirando = false;
            break;
        default:
            break;
   }
}

// callback de evento de teclado de movimento
void teclaMovimentoPressionada(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_RIGHT:
            movNave = VELOC_NAVE;
            break;
        case GLUT_KEY_LEFT:
            movNave = -VELOC_NAVE;
            break;
        default:
            break;
    }
}

// callback de evento de teclado de movimento
void teclaMovimentoLiberada(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_RIGHT:
            movNave = 0;
            break;
        case GLUT_KEY_LEFT:
            movNave = 0;
            break;
        default:
            break;
    }
}