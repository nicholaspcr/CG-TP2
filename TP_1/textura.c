void carregaTextura(int *textura, char *arquivo) { 
    *textura = SOIL_load_OGL_texture(
      arquivo,
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y);

    if (textura == 0) {
        printf("Erro do SOIL: '%s'\n", SOIL_last_result());
    }
}

void colocaTextura(OBJETO obj, GLuint textura){ 
    glColor3f (1, 1, 1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textura);
    glPushMatrix();
    glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(0, 0); glVertex2f(obj.x - obj.larg/2, obj.y - obj.alt/2);
        glTexCoord2f(1, 0); glVertex2f(obj.x + obj.larg/2, obj.y - obj.alt/2); 
        glTexCoord2f(1, 1); glVertex2f(obj.x + obj.larg/2, obj.y + obj.alt/2);
        glTexCoord2f(0, 1); glVertex2f(obj.x - obj.larg/2, obj.y + obj.alt/2); 
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
