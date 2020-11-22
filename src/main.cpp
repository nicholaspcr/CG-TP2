#include <GL/glew.h>
#include <GL/freeglut.h>

#include <GL/glext.h>
#include <SOIL/SOIL.h>

#include <iostream>

#pragma comment(lib, "glew32.lib")

using namespace std;


struct planet { 
  float radius, distance, orbit, orbitSpeed, axisTilt, axisAni;  
  // default values -> define
  planet(){    
    // talvez o sol como o padrão
    radius = 5.0;
    distance = 0.0;
    orbit = 0.0;
    orbitSpeed = 0.0;
    axisTilt = 0.0;
    axisAni = 0.0;
  }
  planet(
    float _radius, 
    float _distance,
    float _orbit,
    float _orbitSpeed,
    float _axisTilt,
    float _axisAni) 
  {
    radius = _radius;
    distance = _distance;
    orbit = _orbit;
    orbitSpeed = _orbitSpeed;
    axisTilt = _axisTilt;
    axisAni = _axisAni;
  }
};


// global variables
int animation = 0;
int orbitActive = 0;
int changeCamera = 0;
int frames = 0;
int labelsActive = 0;
int cameraDistance = 50;

// Sun, Planets and Stars
planet sun = planet();                              // Sun
planet mer = planet(1.0, 7, 0, 4.74, 02.11, 0);     // Mercury
planet ven = planet(1.5, 11, 0, 3.50, 177.0, 0);    // Venus
planet ear = planet(2.0, 16, 0, 2.98, 23.44, 0);    // Earth
planet mar = planet(1.2, 21, 0, 2.41, 25.00, 0);    // Mars
planet jup = planet(3.5, 28, 0, 1.31, 03.13, 0);    // Jupiter
planet sat = planet(3.0, 37, 0, 0.97, 26.70, 0);    // Saturn
planet ura = planet(2.5, 45.5, 0, 0.68, 97.77, 0);  // Uranus
planet nep = planet(2.3, 53.6, 0, 0.54, 28.32, 0);  // Neptune
planet plu = planet(0.4, 59, 0, 0.47, 119.6, 0);    // Pluto

// Texturas
GLuint sunTexture;
GLuint merTexture;
GLuint venTexture;
GLuint earTexture;
GLuint marTexture;
GLuint jupTexture;
GLuint satTexture;
GLuint uraTexture;
GLuint nepTexture;
GLuint pluTexture;
GLuint staTexture;
GLuint logTexture;


// Função dos exemplos
GLuint carregaTextura(const char* arquivo)
{
    // cria um id para a textura
    GLuint idTextura;
    glGenTextures(1, &idTextura);
    glBindTexture(GL_TEXTURE_2D, idTextura);

    int largura, altura, canais;
    unsigned char* texels = SOIL_load_image(arquivo, &largura, &altura, &canais, SOIL_LOAD_RGBA);

    // inverte o eixo t (a SOIL_load_OGL_texture fazia isso automaticamente...)
    for(int j = 0; j < altura / 2; j++ )
    {
        int index1 = j * largura * 4;
        int index2 = (altura - 1 - j) * largura * canais;

        for(int i = largura * canais; i > 0; i--)
        {
            unsigned char temp = texels[index1];
            texels[index1] = texels[index2];
            texels[index2] = temp;
            ++index1;
            ++index2;
        }
    }

    // envia os texels da textura para a VRAM (memória da placa de vídeo_
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, largura, altura, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, texels);

    // libera a RAM que estava guardando a textura (já que ela já foi para a VRAM)
    SOIL_free_image_data(texels);

    if (texels == nullptr) {
        printf("Erro do SOIL '%s' tentando carregar o arquivo '%s'.\n", SOIL_last_result(), arquivo);
    }    
    return idTextura;
}

// escreve string com glut escreve char
void writeBitmapString(void* font, string str) {  
  for(auto ch : str)
    glutBitmapCharacter(font, ch);
}

void setup(void) {
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glEnable(GL_DEPTH_TEST);

  // Carrega texturas com função do exemplo
  glEnable(GL_NORMALIZE);
  glEnable(GL_COLOR_MATERIAL);  
  staTexture = carregaTextura("../textures/png/stars.png");
  sunTexture = carregaTextura("../textures/png/sun.png");
  merTexture = carregaTextura("../textures/png/mercury.png");  
  venTexture = carregaTextura("../textures/png/venus.png");  
  earTexture = carregaTextura("../textures/png/earth.png");
  marTexture = carregaTextura("../textures/png/mars.png");
  jupTexture = carregaTextura("../textures/png/jupiter.png");  
  satTexture = carregaTextura("../textures/png/saturn.png");  
  uraTexture = carregaTextura("../textures/png/uranus.png");
  nepTexture = carregaTextura("../textures/png/neptune.png");  
  logTexture = carregaTextura("../textures/png/stars.png");


  // TODO: Fix lights
  float lightPos[] = {0.0, 0.0, -75.0, 1.0};  // Spotlight position.
  static float spotAngle = 210;                // Spotlight cone half-angle.
  float spotDirection[] = {0.0, 0.0, 0.0};    // Spotlight direction.
  static float spotExponent = 2.0;  // Spotlight exponent = attenuation factor.
  glEnable(GL_LIGHTING);  
  glEnable(GL_LIGHT0);  
  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
  glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
  glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
  glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, spotAngle);
  glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDirection);
  glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, spotExponent);
}


// Desenha o caminho dos planetas
void orbitalTrails(void) {
  glPushMatrix();
  glColor3ub(255, 255, 255);
  glTranslatef(0.0, 0.0, 0.0);
  glRotatef(90.0, 1.0, 0.0, 0.0);
  glutWireTorus(0.001, mer.distance, 100.0, 100.0);
  glutWireTorus(0.001, ven.distance, 100.0, 100.0);
  glutWireTorus(0.001, ear.distance, 100.0, 100.0);
  glutWireTorus(0.001, mar.distance, 100.0, 100.0);
  glutWireTorus(0.001, jup.distance, 100.0, 100.0);
  glutWireTorus(0.001, sat.distance, 100.0, 100.0);
  glutWireTorus(0.001, ura.distance, 100.0, 100.0);
  glutWireTorus(0.001, nep.distance, 100.0, 100.0);
  glutWireTorus(0.001, plu.distance, 100.0, 100.0);
  glPopMatrix();
}

void drawPlanet(planet p, GLuint texture, string planetName, GLUquadric *quad){  
  glPushMatrix();
  glRotatef(p.orbit, 0.0, 1.0, 0.0);
  glTranslatef(p.distance, 0.0, 0.0);
  if (labelsActive == 1) {
    glRasterPos3f(-1.2, 7.0, 0.0);
    glColor3ub(255, 255, 255);
    writeBitmapString(GLUT_BITMAP_HELVETICA_12, planetName);
  }  
  glRotatef(p.axisTilt, 1.0, 0.0, 0.0);
  glRotatef(p.axisAni, 0.0, 1.0, 0.0);
  glRotatef(90.0, 1.0, 0.0, 0.0);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  gluQuadricTexture(quad, 1);
  gluSphere(quad, p.radius, 20.0, 20.0);
  glDisable(GL_TEXTURE_2D);  
  glPopMatrix();
}

void drawScene(void) {
  frames++;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  if (changeCamera == 0)
    gluLookAt(0.0, cameraDistance, 65.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  if (changeCamera == 1)
    gluLookAt(0.0, cameraDistance, 0.00001, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

  if (orbitActive == 1) orbitalTrails();

  GLUquadric* quadric;
  quadric = gluNewQuadric();

  // Sun
  drawPlanet(sun, sunTexture, "Sun", quadric);
  // glPushMatrix();
  // glRotatef(sun.orbit, 0.0, 1.0, 0.0);
  // glTranslatef(sun.distance, 0.0, 0.0);
  // if (labelsActive == 1) {
  //   glRasterPos3f(-1.2, 7.0, 0.0);
  //   glColor3ub(255, 255, 255);
  //   writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Sun");
  // }  
  // glRotatef(sun.axisTilt, 1.0, 0.0, 0.0);
  // glRotatef(sun.axisAni, 0.0, 1.0, 0.0);
  // glRotatef(90.0, 1.0, 0.0, 0.0);
  // glEnable(GL_TEXTURE_2D);
  // glBindTexture(GL_TEXTURE_2D, sunTexture);
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  // gluQuadricTexture(quadric, 1);
  // gluSphere(quadric, sun.radius, 20.0, 20.0);
  // glDisable(GL_TEXTURE_2D);  
  // glPopMatrix();

  // Mercury
  drawPlanet(mer, merTexture, "Mercury", quadric);
  // glPushMatrix();
  // glRotatef(mer.orbit, 0.0, 1.0, 0.0);
  // glTranslatef(mer.distance, 0.0, 0.0);
  // if (labelsActive == 1) {
  //   glRasterPos3f(0.0, 3, 0.0);
  //   glColor3ub(255, 255, 255);
  //   writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Mercury");
  // }  
  // glRotatef(mer.axisTilt, 1.0, 0.0, 0.0);
  // glRotatef(mer.axisAni, 0.0, 1.0, 0.0);
  // glRotatef(90.0, 1.0, 0.0, 0.0);
  // glEnable(GL_TEXTURE_2D);
  // glBindTexture(GL_TEXTURE_2D, merTexture);
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  // gluQuadricTexture(quadric, 1);
  // gluSphere(quadric, mer.radius, 20.0, 20.0);
  // glDisable(GL_TEXTURE_2D);  
  // glPopMatrix();

  // Venus
  glPushMatrix();
  glRotatef(ven.orbit, 0.0, 1.0, 0.0);
  glTranslatef(ven.distance, 0.0, 0.0);
  if (labelsActive == 1) {
    glRasterPos3f(0.0, 3, 0.0);
    glColor3ub(255, 255, 255);
    writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Venus");
  }  
  glRotatef(ven.axisTilt, 1.0, 0.0, 0.0);
  glRotatef(ven.axisAni, 0.0, 1.0, 0.0);
  glRotatef(90.0, 1.0, 0.0, 0.0);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, venTexture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  gluQuadricTexture(quadric, 1);
  gluSphere(quadric, ven.radius, 20.0, 20.0);
  glDisable(GL_TEXTURE_2D);  
  glPopMatrix();

  // Earth
   glPushMatrix();
  glRotatef(ear.orbit, 0.0, 1.0, 0.0);
  glTranslatef(ear.distance, 0.0, 0.0);
  if (labelsActive == 1) {
    glRasterPos3f(0.0, 3, 0.0);
    glColor3ub(255, 255, 255);
    writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Earth");
  }  
  glRotatef(ear.axisTilt, 1.0, 0.0, 0.0);
  glRotatef(ear.axisAni, 0.0, 1.0, 0.0);
  glRotatef(90.0, 1.0, 0.0, 0.0);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, earTexture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  gluQuadricTexture(quadric, 1);
  gluSphere(quadric, ear.radius, 20.0, 20.0);
  glDisable(GL_TEXTURE_2D);
  glPopMatrix();  

  // Mars, Orbits, Moons
  glPushMatrix();
  glRotatef(mar.orbit, 0.0, 1.0, 0.0);
  glTranslatef(mar.distance, 0.0, 0.0);
  if (labelsActive == 1) {
    glRasterPos3f(0.0, 3, 0.0);
    glColor3ub(255, 255, 255);
    writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Mars");
  }  
  glRotatef(mar.axisTilt, 1.0, 0.0, 0.0);
  glRotatef(mar.axisAni, 0.0, 1.0, 0.0);
  glRotatef(90.0, 1.0, 0.0, 0.0);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, marTexture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  gluQuadricTexture(quadric, 1);
  gluSphere(quadric, mar.radius, 20.0, 20.0);
  glDisable(GL_TEXTURE_2D);  
  glPopMatrix();

  // Jupiter, Orbits, Moons
  glPushMatrix();
  glRotatef(jup.orbit, 0.0, 1.0, 0.0);
  glTranslatef(jup.distance, 0.0, 0.0);
  if (labelsActive == 1) {
    glRasterPos3f(0.0, 4.4, 0.0);
    glColor3ub(255, 255, 255);
    writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Jupiter");
  }  
  glRotatef(jup.axisTilt, 1.0, 0.0, 0.0);
  glRotatef(jup.axisAni, 0.0, 1.0, 0.0);
  glRotatef(90.0, 1.0, 0.0, 0.0);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, jupTexture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  gluQuadricTexture(quadric, 1);
  gluSphere(quadric, jup.radius, 20.0, 20.0);
  glDisable(GL_TEXTURE_2D);  
  glPopMatrix();

  // Saturn
  glPushMatrix();
  glRotatef(sat.orbit, 0.0, 1.0, 0.0);
  glTranslatef(sat.distance, 0.0, 0.0);
  if (labelsActive == 1) {
    glRasterPos3f(0.0, 4.4, 0.0);
    glColor3ub(255, 255, 255);
    writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Saturn");
  }
  glPushMatrix();
  glRotatef(sat.axisTilt, 1.0, 0.0, 0.0);
  glRotatef(sat.axisAni, 0.0, 1.0, 0.0);
  glRotatef(90.0, 1.0, 0.0, 0.0);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, satTexture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  gluQuadricTexture(quadric, 1);
  gluSphere(quadric, sat.radius, 20.0, 20.0);  
  glDisable(GL_TEXTURE_2D);
  glPopMatrix();
  glColor3ub(158, 145, 137);
  glRotatef(-63.0, 1.0, 0.0, 0.0);
  glutWireTorus(0.2, 6.0, 30.0, 30.0);
  glutWireTorus(0.4, 5.0, 30.0, 30.0);  
  glPopMatrix();
  
  //glColor3ub(255, 255, 255);  // FIXES SHADING ISSUE

  // Uranus
  glPushMatrix();
  glRotatef(ura.orbit, 0.0, 1.0, 0.0);
  glTranslatef(ura.distance, 0.0, 0.0);
  if (labelsActive == 1) {
    glRasterPos3f(0.0, 4.4, 0.0);
    glColor3ub(255, 255, 255);
    writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Uranus");
  }  
  glRotatef(ura.axisTilt, 1.0, 0.0, 0.0);
  glRotatef(ura.axisAni, 0.0, 1.0, 0.0);
  glRotatef(90.0, 1.0, 0.0, 0.0);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, uraTexture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  gluQuadricTexture(quadric, 1);
  gluSphere(quadric, ura.radius, 20.0, 20.0);
  glDisable(GL_TEXTURE_2D);  
  glPopMatrix();

  // Neptune
  glPushMatrix();
  glRotatef(nep.orbit, 0.0, 1.0, 0.0);
  glTranslatef(nep.distance, 0.0, 0.0);
  if (labelsActive == 1) {
    glRasterPos3f(0.0, 4.4, 0.0);
    glColor3ub(255, 255, 255);
    writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Neptune");
  }  
  glRotatef(nep.axisTilt, 1.0, 0.0, 0.0);
  glRotatef(nep.axisAni, 0.0, 1.0, 0.0);
  glRotatef(90.0, 1.0, 0.0, 0.0);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, nepTexture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  gluQuadricTexture(quadric, 1);
  gluSphere(quadric, nep.radius, 20.0, 20.0);
  glDisable(GL_TEXTURE_2D);  
  glPopMatrix();

  // Pluto
  glPushMatrix();
  glRotatef(plu.orbit, 0.0, 1.0, 0.0);
  glTranslatef(plu.distance, 0.0, 0.0);
  if (labelsActive == 1) {
    glRasterPos3f(0.0, 3.0, 0.0);
    glColor3ub(255, 255, 255);
    writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Pluto");
  }  
  glRotatef(plu.axisTilt, 1.0, 0.0, 0.0);
  glRotatef(plu.axisAni, 0.0, 1.0, 0.0);
  glRotatef(90.0, 1.0, 0.0, 0.0);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, pluTexture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  gluQuadricTexture(quadric, 1);
  gluSphere(quadric, plu.radius, 20.0, 20.0);
  glDisable(GL_TEXTURE_2D);  
  glPopMatrix();


  // 
  glPushMatrix();
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, staTexture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glBegin(GL_POLYGON);
  glTexCoord2f(-1.0, 0.0);
  glVertex3f(-200, -200, -100);
  glTexCoord2f(2.0, 0.0);
  glVertex3f(200, -200, -100);
  glTexCoord2f(2.0, 2.0);
  glVertex3f(200, 200, -100);
  glTexCoord2f(-1.0, 2.0);
  glVertex3f(-200, 200, -100);
  glEnd();

  glBindTexture(GL_TEXTURE_2D, staTexture);
  glBegin(GL_POLYGON);
  glTexCoord2f(0.0, 0.0);
  glVertex3f(-200, -83, 200);
  glTexCoord2f(8.0, 0.0);
  glVertex3f(200, -83, 200);
  glTexCoord2f(8.0, 8.0);
  glVertex3f(200, -83, -200);
  glTexCoord2f(0.0, 8.0);
  glVertex3f(-200, -83, -200);
  glEnd();
  glDisable(GL_TEXTURE_2D);
  glPopMatrix();

  glutSwapBuffers();
}


void resize(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 200.0);
  glMatrixMode(GL_MODELVIEW);
}

void animate(int n) {
  if (animation) {
    mer.orbit += mer.orbitSpeed;
    ven.orbit += ven.orbitSpeed;
    ear.orbit += ear.orbitSpeed;
    mar.orbit += mar.orbitSpeed;
    jup.orbit += jup.orbitSpeed;
    sat.orbit += sat.orbitSpeed;
    ura.orbit += ura.orbitSpeed;
    nep.orbit += nep.orbitSpeed;
    plu.orbit += plu.orbitSpeed;        
    if (mer, ven, ear, mar, jup, sat, ura, nep, plu.orbit > 360.0) {
      mer, ven, ear, mar, jup, sat, ura, nep, plu.orbit -= 360.0;
    }
    mer.axisAni += 10.0;
    ven.axisAni += 10.0;
    ear.axisAni += 10.0;
    mar.axisAni += 10.0;
    jup.axisAni += 10.0;
    sat.axisAni += 10.0;
    ura.axisAni += 10.0;
    nep.axisAni += 10.0;
    plu.axisAni += 10.0;
    if (mer, ven, ear, mar, jup, sat, ura, nep, plu.axisAni > 360.0) {
      mer, ven, ear, mar, jup, sat, ura, nep, plu.axisAni -= 360.0;
    }
    glutPostRedisplay();
    glutTimerFunc(30, animate, 1);
  }
}

void keyInput(unsigned char key, int x, int y) {
  switch (key) {
    case 27:
      exit(0);
      break;    
    case ' ':
      animation = (animation) ? 0 : 1;
      if (animation)        
        animate(1);      
      break;
    case 'o':
    case 'O':
      orbitActive = (orbitActive) ? 0 : 1;      
      glutPostRedisplay();
      break;
    case 'l':
    case 'L':
      labelsActive = (labelsActive) ? 0 : 1;      
      glutPostRedisplay();
      break;
    case '1':
      changeCamera = 0;
      glutPostRedisplay();
      break;
    case '2':
      changeCamera = 1;
      glutPostRedisplay();
      break;    
  }
}

void intructions(void) {
  cout << "SPACE to play/pause the simulation." << endl;
  cout << "ESC to exit the simulation." << endl;
  cout << "O/o to show/hide Big Orbital Trails." << endl;    
  cout << "L/l to show/hide labels" << endl;
  cout << "1 or 2 to change camera angles." << endl;  
}

int main(int argc, char** argv) {
  intructions();
  glutInit(&argc, argv);

  glutInitContextVersion(4, 2);
  glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  glutInitWindowSize(1024, 768);
  glutInitWindowPosition(500, 0);
  glutCreateWindow("Solar System");  
  glutReshapeFunc(resize);  
  glutKeyboardFunc(keyInput);  
  glutDisplayFunc(drawScene);
  glewExperimental = GL_TRUE;
  glewInit(); 
  setup();
  glutMainLoop();
}