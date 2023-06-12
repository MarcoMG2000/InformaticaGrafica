// Etapa2.cpp
// Fichero principal 
// URL documentacion: https://docs.google.com/document/d/1X7sNgk3kwweKhRh_J-OF474CFo0evaiU/edit?usp=sharing&ouid=108901087742241995538&rtpof=true&sd=true 
// URL vídeo: https://youtu.be/zjRKEXU5ZO0
////////////////////////////////////////////////////
#include <glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

const GLint FPS = 60;

GLdouble g = 9.80665f; // Aceleración de la gravedad en la tierra
GLdouble PI = 3.1415926f;

// Primer péndulo
GLfloat w1 = 0.1f, d1 = 4.0f; // Ancho y largo
GLdouble theta1 = 160.0f, m1 = 0.3f, v1 = 0.0f;

// Segundo péndulo
GLfloat w2 = 0.1f, d2 = 2.0f; // Ancho y largo
GLdouble theta2 = 220.0f, m2 = 0.2f, v2 = 0.0f;

// Circulos
GLint num_segments = 200; // Definición de la circunferencia

double toRadians(GLfloat angle) {
	return (PI * angle) / 180.0f;
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	glTranslatef(0.0f, 5.0f, 0.0f); // Transladamos el origen del péndulo 
	glRotatef(theta1, 0.0f, 0.0f, 1.0f); // Rotamos el primer brazo del péndulo

	// Primer Rectángulo
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
	glBegin(GL_QUADS);
	glVertex2f(-w1, 0);
	glVertex2f(w1, 0);
	glVertex2f(w1, -d1);
	glVertex2f(-w1, -d1);
	glEnd();
	glPopMatrix();
	
	glTranslatef(0.0f, -d1, 0.0f); // Trasladamos el origen de coordenadas a la punta del primer rectángulo
	glRotatef(theta2-theta1, 0.0f, 0.0f, 1.0f); // Deshacemos la rotacion del primer brazo y rotamos el segundo

	// Segundo rectángulo
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
	glBegin(GL_QUADS);
	glVertex2f(-w2, 0);
	glVertex2f(w2, 0);
	glVertex2f(w2, -d2);
	glVertex2f(-w2, -d2);
	glEnd();
	glPopMatrix();

	// Punta del primer brazo
	glBegin(GL_TRIANGLE_FAN); // Dibujar círculo
	glColor3f(1.0f, 0.0f, 0.0f);
	for (int i = 0; i < num_segments; i++) {
		float theta = 2.0f * 3.1415926f * (float)(i) / (float)(num_segments);
		float x = m1 * (float)cos(theta);
		float y = m1 * (float)sin(theta);
		glVertex2f(x, y);
	}
	glEnd();
	
	glTranslatef(0.0f, -d2, 0.0f); // Movemos el centro de coordenadas al final del segundo brazo

	// Punta del segundo brazo
	glBegin(GL_TRIANGLE_FAN); // Dibujar círculo
	glColor3f(1.0f, 0.0f, 0.0f);
	for (int i = 0; i < num_segments; i++) {
		float theta = 2.0f * 3.1415926f * (float)(i) / (float)(num_segments);
		float x = m2 * (float)cos(theta);
		float y = m2 * (float)sin(theta);
		glVertex2f(x, y);
	}
	glEnd();

	glutSwapBuffers();
}

// Función para cambiar el tamaño de la ventana
void reshape(GLsizei width, GLsizei height) {
	// Establecer la ventana de visualización (viewport) a la misma dimensión que la ventana
	glViewport(0, 0, width, height);

	// Establecer la matriz de proyección para escalar los objetos
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10.0 * ((GLfloat)width / (GLfloat)height), 10.0 * ((GLfloat)width / (GLfloat)height), -10.0, 10.0, -10.0, 10.0);

	// Establecer la matriz de modelo-vista
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void timer(int value) {

	double angle1 = toRadians(theta1);
	double angle2 = toRadians(theta2);

	double num1 = -g * (2 * m1 + m2) * sin(angle1);
	double num2 = -m2 * g * sin(angle1 - 2 * angle2);
	double num3 = -2 * sin(angle1 - angle2) * m2;
	double num4 = v2 * v2 * d2 + v1 * v1 * d1 * cos(angle1 - angle2);
	double den = d1 * (2 * m1 + m2 - m2 * cos(2 * angle1 - 2 * angle2));
	double a1 = (num1 + num2 + num3 * num4) / den;

	num1 = 2 * sin(angle1 - angle2);
	num2 = (v1 * v1 * d1 * (m1 + m2));
	num3 = g * (m1 + m2) * cos(angle1);
	num4 = v2 * v2 * d2 * m2 * cos(angle1 - angle2);
	den = d2 * (2 * m1 + m2 - m2 * cos(2 * angle1 - 2 * angle2));
	double a2 = (num1 * (num2 + num3 + num4)) / den;
	
	a1 /= FPS;
	a2 /= FPS;

	v1 += a1;
	v2 += a2;

	// Añadimos un rozamiento
	v1 *= 0.999;
	v2 *= 0.999;

	theta1 += v1;
	theta2 += v2;

	if (theta1 > 360) {
		theta1 -= 360;
	}
	if (theta2 > 360) {
		theta2 -= 360;
	}

	glutPostRedisplay();
	glutTimerFunc(1000 / FPS, timer, 0);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(1000, 800);
	glutCreateWindow("Etapa2");
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glutDisplayFunc(display);
	glutTimerFunc(1000 / FPS, timer, 0);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}
