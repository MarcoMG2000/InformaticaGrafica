// Etapa3.cpp
// Fichero principal 
// URL documentacion: https://docs.google.com/document/d/1X7sNgk3kwweKhRh_J-OF474CFo0evaiU/edit?usp=sharing&ouid=108901087742241995538&rtpof=true&sd=true 
// URL vídeo: https://youtu.be/zjRKEXU5ZO0
////////////////////////////////////////////////////
#include <glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

const GLdouble PI = 3.1415926f;
const GLint FPS = 60;
const GLfloat BLANCO[] = { 1.0, 1.0, 1.0 };
const GLfloat NEGRO[] = { 0.0, 0.0, 0.0 };
const GLfloat ROJO[] = { 1.0, 0.0, 0.0 };
const GLfloat VERDE[] = { 0.0, 1.0, 0.0 };
const GLfloat AZUL[] = { 0.0, 0.0, 1.0 };
const GLfloat MORADO[] = { 1.0, 0.0, 1.0 };
const GLfloat CYAN[] = { 0.0, 1.0, 1.0 };

GLfloat angle = 0.0f;

// Declaración de funciones
void init();
void idle();
void display();
void reshape(GLsizei width, GLsizei height);
void timer(int value);
void dibujarCubo(float lado);

// Establece el color de fondo a blanco
void init() {
	glClearColor(0.0, 0.0, 0.0, 1.0); 
	glEnable(GL_DEPTH_TEST);
}

void display() {
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glRotatef(angle, 0.0, 1.0, 0.0); // Rotamos el cubo por la base
	glColor3fv(NEGRO);
	dibujarCubo(1.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(2*angle, 0.0, -1.0, 0.0); // Rotamos la esfera al doble de velocidad en la direeción opuesta
	glTranslatef(1.5, 0.0, 0.0); // La desplazamos del origen
	glColor3fv(BLANCO);
	glutWireSphere(0.5, 20, 20);
	glPopMatrix();

	glFlush();
	glutSwapBuffers();

}

void timer(int value) {
	
	angle += 0.3f;
	if (angle > 360.0) {
		angle -= 360.0;
	}
	
	glutPostRedisplay();
	glutTimerFunc(1000 / FPS, timer, 0);
}

// Función para cambiar el tamaño de la ventana
void reshape(GLsizei width, GLsizei height) {
	
	// Establecemos el viewport a la misma dimensión que la ventana
	glViewport(0, 0, width, height);

	// Matriz de proyección
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	float fovy = 45.0;
	float nearVal = 0.1;
	float farVal = 100.0;
	float aspect = (float)width / (float)height;

	float top = tan(fovy * PI / 360.0f) * nearVal;
	float bottom = -top;
	float left = aspect * bottom;
	float right = aspect * top;

	glFrustum(left, right, bottom, top, nearVal, farVal);

	// Establecemos la matriz de modelo-vista
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(3.0, 3.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(1000, 800);
	glutCreateWindow("Etapa3");
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	
	init();
	glutDisplayFunc(display);
	glutTimerFunc(1000 / FPS, timer, 0);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}

void dibujarCubo(float lado) {
	
	float lado2 = lado / 2;

	// Anverso
	glBegin(GL_POLYGON);
	glColor3fv(ROJO);
	glVertex3f(lado2, -lado2, -lado2);
	glVertex3f(lado2, lado2, -lado2);
	glVertex3f(-lado2, lado2, -lado2);
	glVertex3f(-lado2, -lado2, -lado2);
	glEnd();

	// Reverso
	glBegin(GL_POLYGON);
	glColor3fv(VERDE);
	glVertex3f(lado2, -lado2, lado2);
	glVertex3f(lado2, lado2, lado2);
	glVertex3f(-lado2, lado2, lado2);
	glVertex3f(-lado2, -lado2, lado2);
	glEnd();

	// Lateral derecho
	glBegin(GL_POLYGON);
	glColor3fv(AZUL);
	glVertex3f(lado2, -lado2, -lado2);
	glVertex3f(lado2, lado2, -lado2);
	glVertex3f(lado2, lado2, lado2);
	glVertex3f(lado2, -lado2, lado2);
	glEnd();

	// Lateral izquierdo 
	glBegin(GL_POLYGON);
	glColor3fv(MORADO);
	glVertex3f(-lado2, -lado2, lado2);
	glVertex3f(-lado2, lado2, lado2);
	glVertex3f(-lado2, lado2, -lado2);
	glVertex3f(-lado2, -lado2, -lado2);
	glEnd();

	// Cara superior
	glBegin(GL_POLYGON);
	glColor3fv(CYAN);
	glVertex3f(lado2, lado2, -lado2);
	glVertex3f(lado2, lado2, lado2);
	glVertex3f(-lado2, lado2, lado2);
	glVertex3f(-lado2, lado2, -lado2);
	glEnd();

	// Cara inferior
	glBegin(GL_POLYGON);
	glColor3fv(NEGRO);
	glVertex3f(lado2, -lado2, lado2);
	glVertex3f(lado2, -lado2, -lado2);
	glVertex3f(-lado2, -lado2, -lado2);
	glVertex3f(-lado2, -lado2, lado2);
	glEnd();
}
