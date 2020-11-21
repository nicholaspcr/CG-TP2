int escolheInimigo(int range) {    
    int numAleatorio = rand()%range;
    return numAleatorio;
}

OBJETO executaMovInimigo(OBJETO inimigo) {
    // faz o inimigo andar horizontalmente
    inimigo.x += movHorInimigo;
    return inimigo;    
}

void executaMovHorInimigo() {
    for (int i=0; i<QTD_INIMIGOS; i++) {
        inimigo[i] = executaMovInimigo(inimigo[i]);
    }
    for (int i=0; i<QTD_CHEFES; i++) {
        inimigoChefe[i] = executaMovInimigo(inimigoChefe[i]);
    }
}

void controleMovHorInimigo() {
    for (int i=0; i<QTD_INIMIGOS; i++) {
        if (inimigo[i].existe == true) {
            if ((inimigo[i].x <= inimigo[i].larg/2) || (inimigo[i].x >= (LARGURA_DO_MUNDO-2) - (inimigo[i].larg/2))) {
                movHorInimigo *= -1;   
                break;  
            }
        }
    }
    for (int i=0; i<QTD_CHEFES; i++) {
        if (inimigoChefe[i].existe == true) {
            if ((inimigoChefe[i].x <= inimigoChefe[i].larg/2) || (inimigoChefe[i].x >= (LARGURA_DO_MUNDO-2) - (inimigoChefe[i].larg/2))) {
                movHorInimigo *= -1;   
                break;  
            }
        }
    }    
}

void detectaColisaoInimigo() {
    for (int i=0; i<QTD_INIMIGOS; i++) {
        if (inimigo[i].existe == true) {
            if (detectaColisao(inimigo[i], tiroNave) == true) {
                inimigo[i].existe = false;
                inimigo[i].x = -100;
                inimigo[i].y = -100;
                tiroNave.y = ALTURA_DO_MUNDO + (tiroNave.alt/2);
                return;
            }
        }
    }
    for (int i=0; i<QTD_CHEFES; i++) {
        if (detectaColisao(inimigoChefe[i], tiroNave) == true) {
            inimigoChefe[i].existe = false;
            inimigoChefe[i].x = -100;
            inimigoChefe[i].y = -100;            
            tiroNave.y = ALTURA_DO_MUNDO + (tiroNave.alt/2);           
            return;
        }
    }
}