// Etapa5.cpp
// Fichero principal 
// URL documentacion: https://docs.google.com/document/d/1X7sNgk3kwweKhRh_J-OF474CFo0evaiU/edit?usp=sharing&ouid=108901087742241995538&rtpof=true&sd=true 
// URL vídeo: https://youtu.be/zjRKEXU5ZO0
////////////////////////////////////////////////////
#include <glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

const GLdouble PI = 3.1415926f;
const GLint WIDTH = 1000;
const GLint HEIGHT = 800;
const GLint FPS = 60;
const GLfloat BLANCO[] = { 1.0, 1.0, 1.0 };
const GLfloat NEGRO[] = { 0.0, 0.0, 0.0 };
const GLfloat ROJO[] = { 1.0, 0.0, 0.0 };
const GLfloat VERDE[] = { 0.0, 1.0, 0.0 };
const GLfloat AZUL[] = { 0.0, 0.0, 1.0 };
const GLfloat MORADO[] = { 1.0, 0.0, 1.0 };
const GLfloat CYAN[] = { 0.0, 1.0, 1.0 };
const GLfloat AMARILLO[] = { 1.0, 1.0, 0.0 };

GLfloat angle = 0.0f;
GLint figure = 0;

// Variables de las luces
bool smoothShadeModel = true;
bool luzEncendida0 = true;
bool luzEncendida1 = true;
float posicionLight1[] = { 0.0f, 5.0f, 0.0f, 1.0f };
float difuse1[] = { 1.0f, 1.0f, 1.0f, 1.0f };
float specular1[] = { 1.0f, 1.0f, 1.0f, 1.0f };

// Variables para el control de la cámara
float cameraAngleX = 10 * PI / 8, cameraAngleY = PI / 5;
float cameraPosX = 3.0f, cameraPosY = 3.0f, cameraPosZ = 3.0f;
int mouseX, mouseY;
int windowCenterX, windowCenterY;
bool hasFocus = false;

// Declaración de funciones
void init();
void idle();
void display();
void timer(int value);
void reshape(GLsizei width, GLsizei height);
void passiveMotionFunc(int x, int y);
void updateCamera();
void dibujarCubo(float lado);
void dibujarSuelo(int numCuadros, float ladoCuadro, float altura);

// Establece el color de fondo a blanco
void init() {
	glClearColor(0.0, 0.0, 0.0, 1.0);

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_SMOOTH);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	windowCenterX = WIDTH / 2;
	windowCenterY = HEIGHT / 2;
	glutWarpPointer(windowCenterX, windowCenterY);
}

void display() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	if (smoothShadeModel)
		glShadeModel(GL_SMOOTH);
	else
		glShadeModel(GL_FLAT);

	// Deshabilitamos el GL_LIGHTING para dar el efecto encendido a las esferas
	if (luzEncendida0 || luzEncendida1)
		glDisable(GL_LIGHTING);

	// Pintamos la esfera orbitante iluminada
	if (luzEncendida0) {
		glPushMatrix();
		glRotatef(2 * angle, 0.0, -1.0, 0.0); // Rotamos la esfera al doble de velocidad en la direeción opuesta
		glTranslatef(3.0, 0.0, 0.0); // La desplazamos del centro
		glColor3fv(BLANCO);
		glutSolidSphere(0.25, 100, 100);
		glPopMatrix();

		float posicionLight0[] = { 3.0 * cos(2 * (double)angle * (PI / 180)), 0.0f, 3.0 * sin(2 * (double)angle * (PI / 180)) , 1.0f };
		glLightfv(GL_LIGHT0, GL_POSITION, posicionLight0);
		glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.3);
	}

	// Pintamos la esfera libre iluminada
	if (luzEncendida1 && specular1[0] > 0) { 
		glPushMatrix();
		glTranslatef(posicionLight1[0], posicionLight1[1], posicionLight1[2]); // La desplazamos a su posición
		glColor3fv(BLANCO);
		glutSolidSphere(0.25, 100, 100);
		glPopMatrix();

		glLightfv(GL_LIGHT1, GL_POSITION, posicionLight1);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, difuse1);
		glLightfv(GL_LIGHT1, GL_SPECULAR, specular1);
		glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 3.0);
	}
	
	if (luzEncendida0 || luzEncendida1)
		glEnable(GL_LIGHTING);

	if (!luzEncendida0) { // Pintamos la esfera orbitante sin iluminar
		glPushMatrix();
		glRotatef(2 * angle, 0.0, -1.0, 0.0); // Rotamos la esfera al doble de velocidad en la direeción opuesta
		glTranslatef(3.0, 0.0, 0.0); // La desplazamos del centro
		glColor3fv(BLANCO);
		glutSolidSphere(0.25, 100, 100);
		glPopMatrix();
	}

	if (!luzEncendida1 || specular1[0] <= 0) { // Pintamos la esfera libre sin iluminar
		glPushMatrix();
		glTranslatef(posicionLight1[0], posicionLight1[1], posicionLight1[2]); // La desplazamos a su posición
		glColor3fv(BLANCO);
		glutSolidSphere(0.25, 100, 100);
		glPopMatrix();
	}

	glColor3fv(CYAN);
	dibujarSuelo(100, 0.4f, -3.0f);	

	glPushMatrix();
	glRotatef(angle, 0.0, 1.0, 0.0); // Rotamos el cubo por la base
	glColor3fv(BLANCO);
	if (figure == 0)
		glutSolidTeapot(1.0);
	else if (figure == 1)
		dibujarCubo(1.0);
	else
		glutSolidSphere(1.0, 10, 10);
	glPopMatrix();

	glFlush();
	glutSwapBuffers();

}

void timer(int value) {

	angle += 0.15f;
	if (angle > 360.0) {
		angle -= 360.0;
	}

	// Calculamos las coordenadas del centro de la pantalla
	int centerX = WIDTH / 2;
	int centerY = HEIGHT / 2;

	// Ponemos el ratón en el centro de la pantalla
	glutWarpPointer(centerX, centerY);

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
	gluPerspective(45.0f, (float)width / height, 0.1f, 100.0f);

}

void passiveMotionFunc(int x, int y) {
	int deltaX = x - mouseX;
	int deltaY = y - mouseY;

	mouseX = x;
	mouseY = y;

	updateCamera();
}

void updateCamera()
{
	float deltaX = (mouseX - windowCenterX) * 0.005f;
	float deltaY = (mouseY - windowCenterY) * 0.005f;

	cameraAngleX += deltaX;
	cameraAngleY += deltaY;

	if (cameraAngleX < -PI)
		cameraAngleX += 2 * PI;
	if (cameraAngleX >= PI)
		cameraAngleX -= 2 * PI;

	if (cameraAngleY < -PI / 2)
		cameraAngleY = -PI / 2;
	if (cameraAngleY > PI / 2)
		cameraAngleY = PI / 2;

	float cameraDirX = cos(cameraAngleX) * cos(cameraAngleY);
	float cameraDirY = -sin(cameraAngleY);
	float cameraDirZ = sin(cameraAngleX) * cos(cameraAngleY);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(cameraPosX, cameraPosY, cameraPosZ,
		cameraPosX + (double)cameraDirX, cameraPosY + (double)cameraDirY, cameraPosZ + (double)cameraDirZ,
		0.0f, 1.0f, 0.0f);
}

void keyboard(unsigned char key, int x, int y) {

	float cameraSpeed = 0.1f;

	float directionX = cos(cameraAngleY) * cos(cameraAngleX);
	float directionY = -sin(cameraAngleY);
	float directionZ = cos(cameraAngleY) * sin(cameraAngleX);

	switch (key) {
	case 'w':
	case 'W':
		// movemos la cámara hacia delante
		cameraPosX += directionX * cameraSpeed;
		cameraPosY += directionY * cameraSpeed;
		cameraPosZ += directionZ * cameraSpeed;
		break;
	case 's':
	case 'S':
		// movemos la cámara hacia atrás
		cameraPosX -= directionX * cameraSpeed;
		cameraPosY -= directionY * cameraSpeed;
		cameraPosZ -= directionZ * cameraSpeed;
		break;
	case 'a':
	case 'A':
		// movemos la cámara a la izquierda en el plano xz
		cameraPosX += sin(cameraAngleX) * cameraSpeed;
		cameraPosZ -= cos(cameraAngleX) * cameraSpeed;
		break;
	case 'd':
	case 'D':
		// movemos la cámara a la derecha en el plano xz
		cameraPosX -= sin(cameraAngleX) * cameraSpeed;
		cameraPosZ += cos(cameraAngleX) * cameraSpeed;
		break;
	case 'c':
	case 'C':
		// movemos la cámara hacia abajo
		cameraPosY -= cameraSpeed;
		break;
	case ' ': // Espacio
		// movemos la cámara hacia arriba
		cameraPosY += cameraSpeed;
		break;
	case 'q':
	case 'Q':
		// Apagamos/encendemos la luz 0
		if (luzEncendida0) {
			glDisable(GL_LIGHT0);
			luzEncendida0 = false;
		}
		else {
			glEnable(GL_LIGHT0);
			luzEncendida0 = true;
		}
		break;
	case 'e':
	case 'E':
		// Apagamos/encendemos la luz 1
		if (luzEncendida1) {
			glDisable(GL_LIGHT1);
			luzEncendida1 = false;
		}
		else {
			glEnable(GL_LIGHT1);
			luzEncendida1 = true;
		}
		break;
	case 'u':
	case 'U':
		// Movemos la luz libre hacia X+
		posicionLight1[0] += 0.1;
		break;
	case 'j':
	case 'J':
		// Movemos la luz libre hacia X-
		posicionLight1[0] -= 0.1;
		break;
	case 'i':
	case 'I':
		// Movemos la luz libre hacia Y+
		posicionLight1[1] += 0.1;
		break;
	case 'k':
	case 'K':
		// Movemos la luz libre hacia Y-
		posicionLight1[1] -= 0.1;
		break;
	case 'o':
	case 'O':
		// Movemos la luz libre hacia Z+
		posicionLight1[2] += 0.1;
		break;
	case 'l':
	case 'L':
		// Movemos la luz libre hacia Z-
		posicionLight1[2] -= 0.1;
		break;
	case 'n':
	case 'N':
		if (specular1[0] >= 2) break;
		// Subimos la intensidad de la luz especular y difusa de la luz 1
		specular1[0] += 0.1;
		specular1[1] += 0.1;
		specular1[2] += 0.1;
		difuse1[0] += 0.1;
		difuse1[1] += 0.1;
		difuse1[2] += 0.1;
		break;
	case 'm':
	case 'M':
		if (specular1[0] <= 0) break;
		// Bajamos la intensidad de la luz especular y difusa de la luz 1
		specular1[0] -= 0.1;
		specular1[1] -= 0.1;
		specular1[2] -= 0.1;
		difuse1[0] -= 0.1;
		difuse1[1] -= 0.1;
		difuse1[2] -= 0.1;
		break;
	case 'p':
	case 'P':
		if (smoothShadeModel) 
			smoothShadeModel = false;
		else
			smoothShadeModel = true;
		break;
	case 'f':
	case 'F':
		figure = ++figure % 3;
		break;
	case 27: // Esc
		exit(0); // Cierra la aplicación
		break;
	}

}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Etapa5");
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	init();
	glutDisplayFunc(display);
	glutTimerFunc(1000 / FPS, timer, 0);
	glutReshapeFunc(reshape);
	glutPassiveMotionFunc(passiveMotionFunc);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}

void dibujarCubo(float lado) {
	float lado2 = lado / 2;

	// Anverso
	glNormal3f(0.0, 0.0, -1.0);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(lado2, -lado2, -lado2);
	glVertex3f(-lado2, -lado2, -lado2);
	glVertex3f(-lado2, lado2, -lado2);
	glVertex3f(lado2, lado2, -lado2);
	glEnd();

	// Reverso
	glNormal3f(0.0, 0.0, 1.0);
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(lado2, -lado2, lado2);
	glVertex3f(-lado2, -lado2, lado2);
	glVertex3f(-lado2, lado2, lado2);
	glVertex3f(lado2, lado2, lado2);
	glEnd();

	// Lateral derecho
	glNormal3f(1.0, 0.0, 0.0);
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3f(lado2, -lado2, -lado2);
	glVertex3f(lado2, -lado2, lado2);
	glVertex3f(lado2, lado2, lado2);
	glVertex3f(lado2, lado2, -lado2);
	glEnd();

	// Lateral izquierdo 
	glNormal3f(-1.0, 0.0, 0.0);
	glColor3f(1.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3f(-lado2, -lado2, -lado2);
	glVertex3f(-lado2, -lado2, lado2);
	glVertex3f(-lado2, lado2, lado2);
	glVertex3f(-lado2, lado2, -lado2);
	glEnd();

	// Cara superior
	glNormal3f(0.0, 1.0, 0.0);
	glColor3f(0.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3f(lado2, lado2, -lado2);
	glVertex3f(-lado2, lado2, -lado2);
	glVertex3f(-lado2, lado2, lado2);
	glVertex3f(lado2, lado2, lado2);
	glEnd();

	// Cara inferior
	glNormal3f(0.0, -1.0, 0.0);
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(lado2, -lado2, -lado2);
	glVertex3f(-lado2, -lado2, -lado2);
	glVertex3f(-lado2, -lado2, lado2);
	glVertex3f(lado2, -lado2, lado2);
	glEnd();
}

void dibujarSuelo(int numCuadros, float ladoCuadro, float altura) {

	float lado2 = ladoCuadro / 2;
	int numCuadros2 = numCuadros / 2;

	for (int i = 0; i < numCuadros; i++) {
		for (int j = 0; j < numCuadros; j++) {
			glBegin(GL_QUADS);
			glNormal3f(0.0, 1.0, 0.0); // Añadimos una normal para que la iluminación sea correcta
			glVertex3f(lado2 * (j - numCuadros2), altura, lado2 * (i - numCuadros2));
			glVertex3f(lado2 * (j + 1 - numCuadros2), altura, lado2 * (i - numCuadros2));
			glVertex3f(lado2 * (j + 1 - numCuadros2), altura, lado2 * (i + 1 - numCuadros2));
			glVertex3f(lado2 * (j - numCuadros2), altura, lado2 * (i + 1 - numCuadros2));
			glEnd();
		}
	}

}
