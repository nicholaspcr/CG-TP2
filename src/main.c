// inclui todas as bibliotecas necessárias
// ao bom funcionamento do programa
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <SOIL/SOIL.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


struct Esfera {
  
}

// função principal
int main(int argc, char** argv) {
  // acordando o GLUT
  glutInit(&argc, argv);

  // definindo a versão do OpenGL que vamos usar
  glutInitContextVersion(1, 1);
  glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

  // Configuração inicial da janela do GLUT
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowSize(800, 600);
  glutInitWindowPosition(100, 100);

  // abre a janela
  glutCreateWindow("Solar System");

  // configura valor inicial de algumas
  // variáveis de estado do OpenGL
  // inicializa();

  // // registra callbacks para alguns eventos
  // glutDisplayFunc(desenhaCena);
  // glutReshapeFunc(redimensiona);

  // glutKeyboardFunc(teclaPressionada);
  // glutKeyboardUpFunc(teclaLiberada);

  // glutSpecialFunc(teclaMovimentoPressionada);
  // glutSpecialUpFunc(teclaMovimentoLiberada);

  // // registra a função "movimentoMouse" para executar sempre que o mouse
  // mexer glutPassiveMotionFunc(movimentoMouse);
  // // registra o clique do mouse
  // glutMouseFunc(cliqueMouse);

  // registra a função "atualiza" para executar daqui a 0 milissegundos
  // glutTimerFunc(0, atualizaCena, 33);

  glutMainLoop();
  return 0;
}

