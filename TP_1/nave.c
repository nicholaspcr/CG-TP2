OBJETO controleMovNave(OBJETO nave) {
    if (nave.x <= nave.larg/2) {
        nave.x = (LARGURA_DO_MUNDO-2)- (nave.larg/2);
    }
    if (nave.x > (LARGURA_DO_MUNDO-2) - (nave.larg/2)) {
        nave.x = (nave.larg/2) + 2;
    }
    return nave;
} 

OBJETO executaMovNave(OBJETO nave) {
    // faz a nave andar na direção do teclado   
    nave.x += movNave;
    return nave;    
}

void detectaColisaoNave() {
    if ((detectaColisao(nave, tiroIniComum) == true)) {
        tiroIniComum.y = -tiroIniComum.alt/2;
        nave.x = LARGURA_DO_MUNDO/2;
        contVida--;   
    }
    if ((detectaColisao(nave, tiroIniChefe) == true)) {
        tiroIniChefe.y = -tiroIniChefe.alt/2;        
        nave.x = LARGURA_DO_MUNDO/2;
        contVida--;             
    }
    if ((detectaColisao(nave, tiroIniAtacando) == true)) {
        tiroIniAtacando.y = -tiroIniAtacando.alt/2;        
        nave.x = LARGURA_DO_MUNDO/2;
        contVida--;              
    }    
    if ((detectaColisao(nave, inimigo[inimigoRand3]) == true)) {
        inimigo[inimigoRand3].y = -inimigo[inimigoRand3].alt/2;
        nave.x = LARGURA_DO_MUNDO/2;
        contVida--;              
    }
}

void verificaVidas() {
    if (contVida == 2) {
        vidaNave3.existe = false;
    }
    if (contVida == 1) {
        vidaNave2.existe = false;        
    }
    if (contVida == 0) {
        vidaNave1.existe = false;
    }
}