// Fichero de cabecera para Etapa6.cpp
#include <glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <stdio.h>
#include <SOIL2.h>

// Constantes de la aplicación
const GLdouble PI = 3.1415926f;
const GLint WIDTH = 1000;
const GLint HEIGHT = 800;
const GLint FPS = 60;

// Colores
const GLfloat BLANCO[] = { 1.0, 1.0, 1.0 };
const GLfloat NEGRO[] = { 0.0, 0.0, 0.0 };

// Radio de orbita los cuerpos celestes 
const GLfloat radioOrbitaSol = 30.0f;
const GLfloat radioOrbitaLuna = 5.0f;
const GLfloat radioOrbitaMercurio = 10.0f;
const GLfloat radioOrbitaVenus = 20.0f;

// Radio de los cuerpos celestes
const GLfloat radioTierra = 2.0f;
const GLfloat radioSol = 5.0f;
const GLfloat radioLuna = 0.5f;
const GLfloat radioMercurio = 0.6f;
const GLfloat radioVenus = 1.7f;

// Inclinación de los planetas respecto del eje Y
const GLfloat inclinacionTierra = 23.5f;
const GLfloat inclinacionVenus = 177.4;
const GLfloat inclinacionLuna = -6.68f;

// Inclinación del plano de rotación de la luna respecto del plano xz
const GLfloat inclinacionPlanoLuna = 5.14f;

GLfloat speedRate = 1; // Ratio de velocidad de rotación y traslación de los cuerpos celestes
GLint ozono = 0; // Textura que aplicar a la tierra (0-7)
GLint polo = 0; // Desplazar la camara a uno de los polos (alterna al pulsar)

// Angulos de los cuerpos celestes
GLfloat anguloSol = 0.0f; // Ángulo de traslación del sol respecto de la tierra
GLfloat anguloLuna = 0.0f; // Ángulo de traslación de la luna respecto de la tierra
GLfloat anguloMercurio = 120.0f; // Ángulo de traslación de mercurio respecto del sol
GLfloat anguloVenus = -60.0f; // Ángulo de traslación de venus respecto del sol
GLfloat rotacionTierra = 0.0f; // Ángulo de rotación de la tierra
GLfloat rotacionSol = 0.0f; // Ángulo de rotación del sol
GLfloat rotacionMercurio = 0.0f; // Ángulo de rotación de mercurio
GLfloat rotacionVenus = 0.0f; // Ángulo de rotación de venus

// Identificadores de texturas
GLuint leyendaID;		   // Identificador de la textura de la leyenda
GLuint texturaEstrellasID; // Identificador de la textura de las estrellas
GLuint texturaTierraID;    // Identificador de la textura de la tierra
GLuint texturaSolID;       // Identificador de la textura del sol
GLuint texturaLunaID;      // Identificador de la textura de la luna
GLuint texturaMercurioID;  // Identificador de la textura de mercurio
GLuint texturaVenusID;     // Identificador de la textura de venus
GLuint ozono2023;		   // Identificador de la textura de la capa de ozono 2023
GLuint ozono2018;		   // Identificador de la textura de la capa de ozono 2018
GLuint ozono2013;		   // Identificador de la textura de la capa de ozono 2013
GLuint ozono2008;		   // Identificador de la textura de la capa de ozono 2008
GLuint ozono2003;		   // Identificador de la textura de la capa de ozono 2003
GLuint ozono1998;		   // Identificador de la textura de la capa de ozono 1998

// Variables para el control de la cámara
GLfloat cameraAngleX = 10 * PI / 8, cameraAngleY = 0;
GLfloat cameraPosX = 5.0f, cameraPosY = 0.0f, cameraPosZ = 5.0f;
GLfloat cameraSpeed = 0.1f;;
GLint mouseX, mouseY;
GLint windowCenterX, windowCenterY;

// Variables de las luces
bool smoothShadeModel = true;
bool luzEncendida = true;

// Declaración de funciones
void init();
void cargarTexturas();
void display();
void idle();
void timer(int value);
void reshape(GLsizei width, GLsizei height);
void passiveMotionFunc(int x, int y);
void updateCamera();
void dibujarEsfera(GLdouble radius, GLint slices, GLint stacks);
void pintarEstrellas();
void pintarSol();
void pintarMercurio();
void pintarVenus();
void pintarTierra();
void pintarLuna();
void dibujarHUD();
