// Etapa6.cpp
// Fichero principal 
// URL documentacion: https://docs.google.com/document/d/1X7sNgk3kwweKhRh_J-OF474CFo0evaiU/edit?usp=sharing&ouid=108901087742241995538&rtpof=true&sd=true 
// URL vídeo: https://youtu.be/zjRKEXU5ZO0
////////////////////////////////////////////////////
#include "Etapa6.h"

void init() {
	glClearColor(0.0, 0.0, 0.0, 1.0);

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_SMOOTH);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	glEnable(GL_TEXTURE_2D);
	cargarTexturas();

	windowCenterX = WIDTH / 2;
	windowCenterY = HEIGHT / 2;
	glutWarpPointer(windowCenterX, windowCenterY);
}

void cargarTexturas() {

	texturaEstrellasID = SOIL_load_OGL_texture(
		"estrellas.bmp",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_TEXTURE_REPEATS
	);
	if (texturaEstrellasID == 0) {
		printf("Error loading texture: %s\n", SOIL_last_result());
	}

	texturaTierraID = SOIL_load_OGL_texture(
		"tierra_espejo.bmp",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_TEXTURE_REPEATS
	);
	if (texturaTierraID == 0) {
		printf("Error loading texture: %s\n", SOIL_last_result());
	}

	texturaSolID = SOIL_load_OGL_texture(
		"sol_espejo.bmp",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_TEXTURE_REPEATS
	);
	if (texturaSolID == 0) {
		printf("Error loading texture: %s\n", SOIL_last_result());
	}
	
	texturaLunaID = SOIL_load_OGL_texture(
		"luna_espejo.bmp",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_TEXTURE_REPEATS
	);
	if (texturaLunaID == 0) {
		printf("Error loading texture: %s\n", SOIL_last_result());
	}

	texturaMercurioID = SOIL_load_OGL_texture(
		"mercurio_espejo.bmp",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_TEXTURE_REPEATS
	);
	if (texturaMercurioID == 0) {
		printf("Error loading texture: %s\n", SOIL_last_result());
	}

	texturaVenusID = SOIL_load_OGL_texture(
		"venus_espejo.bmp",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_TEXTURE_REPEATS
	);
	if (texturaVenusID == 0) {
		printf("Error loading texture: %s\n", SOIL_last_result());
	}

	leyendaID = SOIL_load_OGL_texture(
		"leyenda.bmp",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_TEXTURE_REPEATS
	);
	if (leyendaID == 0) {
		printf("Error loading texture: %s\n", SOIL_last_result());
	}

}

void display() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_LIGHTING);
	glColor3fv(BLANCO);

	if (smoothShadeModel) glShadeModel(GL_SMOOTH);
	else glShadeModel(GL_FLAT);

	pintarEstrellas();

	if (!luzEncendida) // Si la luz está apagada, activamos la luz antes de dibujar la esfera
		glEnable(GL_LIGHTING);

	pintarSol();

	if (luzEncendida) {
		float posicionLight0[] = { radioOrbitaSol * cos((double)anguloSol * (PI / 180)), 0.0f, radioOrbitaSol * sin((double)anguloSol * (PI / 180)) , 1.0f };
		glLightfv(GL_LIGHT0, GL_POSITION, posicionLight0);
		glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.5);

		glEnable(GL_LIGHTING);
	}

	pintarMercurio();
	pintarVenus();
	pintarTierra();
	pintarLuna();

	if (ozono != 0)
		dibujarHUD();

	glFlush();
	glutSwapBuffers();

}

void timer(int value) {

	rotacionSol += speedRate * 0.011111f; // Rotación del sol 27 dias
	if (rotacionSol > 360.0) {
		rotacionSol -= 360.0;
	}

	rotacionTierra += speedRate * 0.3f; // Rotación de la tierra 1 día
	if (rotacionTierra > 360.0) {
		rotacionTierra -= 360.0;
	}

	rotacionMercurio += speedRate * 0.005f; // Rotación de mercurio 59 dias
	if (rotacionMercurio > 360.0) {
		rotacionMercurio -= 360.0;
	}

	rotacionVenus += speedRate * 0.0012; // Rotación de venus 243 dias
	if (rotacionVenus > 360.0) {
		rotacionVenus -= 360.0;
	}

	anguloSol -= speedRate * 0.0008219f; // Año en la tierra 365 días (0.2)
	if (anguloSol < 0) {
		anguloSol += 360.0;
	}

	anguloLuna -= speedRate * 0.011111f; // Año en la luna 27 días
	if (anguloLuna < 0) {
		anguloLuna += 360.0;
	}

	anguloMercurio -= speedRate * 0.0034; // Año en venus 88 días
	if (anguloMercurio < 0) {
		anguloMercurio += 360.0;
	}

	anguloVenus -= speedRate * 0.0013; // Año en venus 225 días
	if (anguloVenus < 0) {
		anguloVenus += 360.0;
	}

	// Calculamos las coordenadas del centro de la pantalla
	int centerX = WIDTH / 2;
	int centerY = HEIGHT / 2;

	// Ponemos el ratón en el centro de la pantalla
	glutWarpPointer(centerX, centerY);

	glutPostRedisplay();
	glutTimerFunc(1000 / FPS, timer, 0);
}

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
	case 'e':
	case 'E':
		// Apagamos/encendemos la luz 1
		if (luzEncendida) {
			glDisable(GL_LIGHT0);
			luzEncendida = false;
		}
		else {
			glEnable(GL_LIGHT0);
			luzEncendida = true;
		}
		break;
	case 'f':
	case 'F':
		if (smoothShadeModel)
			smoothShadeModel = false;
		else
			smoothShadeModel = true;
		break;
	case 'M':
	case 'm':
		// Aumentamos el ratio de velocidad de rotacion-traslación
		if (speedRate < 100)
			speedRate += 1.0f;
		break;
	case 'N':
	case 'n':
		// Aumentamos el ratio de velocidad de rotacion-traslación
		if (speedRate > 0)
			speedRate -= 1.0f;
		break;
	case 'o':
	case 'O':
		ozono = (ozono + 1) % 7;
		switch (ozono) {
		case 1:
			if (ozono2023 == NULL)
				ozono2023 = SOIL_load_OGL_texture(
					"ozono2023.bmp",
					SOIL_LOAD_AUTO,
					SOIL_CREATE_NEW_ID,
					SOIL_FLAG_TEXTURE_REPEATS
				);
			if (ozono2023 == 0) {
				printf("Error loading texture: %s\n", SOIL_last_result());
			}
			break;
		case 2:
			if (ozono2018 == NULL)
				ozono2018 = SOIL_load_OGL_texture(
					"ozono2018.bmp",
					SOIL_LOAD_AUTO,
					SOIL_CREATE_NEW_ID,
					SOIL_FLAG_TEXTURE_REPEATS
				);
			if (ozono2018 == 0) {
				printf("Error loading texture: %s\n", SOIL_last_result());
			}
			break;
		case 3:
			if (ozono2013 == NULL) 
				ozono2013 = SOIL_load_OGL_texture(
					"ozono2013.bmp",
					SOIL_LOAD_AUTO,
					SOIL_CREATE_NEW_ID,
					SOIL_FLAG_TEXTURE_REPEATS
				);
			if (ozono2013 == 0) {
				printf("Error loading texture: %s\n", SOIL_last_result());
			}
			break;
		case 4:
			if (ozono2008 == NULL)
				ozono2008 = SOIL_load_OGL_texture(
					"ozono2008.bmp",
					SOIL_LOAD_AUTO,
					SOIL_CREATE_NEW_ID,
					SOIL_FLAG_TEXTURE_REPEATS
				);
			if (ozono2008 == 0) {
				printf("Error loading texture: %s\n", SOIL_last_result());
			}
			break;
		case 5:
			if (ozono2003 == NULL)
				ozono2003 = SOIL_load_OGL_texture(
					"ozono2003.bmp",
					SOIL_LOAD_AUTO,
					SOIL_CREATE_NEW_ID,
					SOIL_FLAG_TEXTURE_REPEATS
				);
			if (ozono2003 == 0) {
				printf("Error loading texture: %s\n", SOIL_last_result());
			}
			break;
		case 6:
			if (ozono1998 == NULL)
				ozono1998 = SOIL_load_OGL_texture(
					"ozono1998.bmp",
					SOIL_LOAD_AUTO,
					SOIL_CREATE_NEW_ID,
					SOIL_FLAG_TEXTURE_REPEATS
				);
			if (ozono1998 == 0) {
				printf("Error loading texture: %s\n", SOIL_last_result());
			}
			break;
		}
		break;
	case 'p':
	case 'P':
		polo = (polo + 1) % 2;
		if (polo == 0) { // Apuntamos la cámara al polo norte
			cameraPosX = 0.027076;
			cameraPosY = 4.398188;
			cameraPosZ = -2.059221;
			cameraAngleX = 1.591990;
			cameraAngleY = 1.125000;
		} 
		else { // Apuntamos la cámara al polo sur
			cameraPosX = -0.131993;
			cameraPosY = -4.553777;
			cameraPosZ = 1.830603;
			cameraAngleX = -1.464823;
			cameraAngleY = -1.194202;
		}
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
	glutCreateWindow("Etapa6 - José Mario Molina Henríquez");
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

void dibujarEsfera(GLdouble radius, GLint slices, GLint stacks) {
	GLUquadric* quadric = gluNewQuadric();
	gluQuadricNormals(quadric, GLU_SMOOTH);
	gluQuadricTexture(quadric, GL_TRUE);
	gluSphere(quadric, radius, slices, stacks);
	gluDeleteQuadric(quadric);
}

void pintarEstrellas() {
	glPushMatrix();
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f); // Alinear la esfera en el eje Y
	glBindTexture(GL_TEXTURE_2D, texturaEstrellasID);
	glEnable(GL_TEXTURE_2D);
	dibujarEsfera(55.0, 500, 500);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void pintarSol() {
	glPushMatrix();
	glRotatef(anguloSol, 0.0, -1.0, 0.0); // Rotación del sol respecto de la tierra
	glTranslatef(radioOrbitaSol, 0.0, 0.0); // La desplazamos del centro
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f); // Alinear la esfera en el eje Y
	glRotatef(rotacionSol, 0.0f, 0.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, texturaSolID);
	glEnable(GL_TEXTURE_2D);
	dibujarEsfera(radioSol, 50, 50);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void pintarMercurio() {
	glPushMatrix();
	// Nos posicionamos en el centro del sol
	glRotatef(anguloSol, 0.0, -1.0, 0.0);
	glTranslatef(radioOrbitaSol, 0.0, 0.0);
	glRotatef(anguloSol, 0.0, 1.0, 0.0);
	// Movemos el planeta a su órbita
	glRotatef(anguloMercurio, 0.0, -1.0, 0.0); // Traslación de la órbita
	glTranslatef(radioOrbitaMercurio, 0.0, 0.0); // Movemos el planeta a su órbita
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f); // Alinear la esfera en el eje Y
	// Rotamos el planeta, aplicamos texturas y dibujamos la esfera
	glRotatef(rotacionMercurio, 0.0f, 0.0f, 1.0f); // Mercurio tiene rotación ~ 0.0º
	glBindTexture(GL_TEXTURE_2D, texturaMercurioID);
	glEnable(GL_TEXTURE_2D);
	dibujarEsfera(radioMercurio, 50, 50);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void pintarVenus() {
	glPushMatrix();
	// Nos posicionamos en el centro del sol
	glRotatef(anguloSol, 0.0, -1.0, 0.0);
	glTranslatef(radioOrbitaSol, 0.0, 0.0);
	glRotatef(anguloSol, 0.0, 1.0, 0.0);
	// Movemos el planeta a su órbita
	glRotatef(anguloVenus, 0.0, -1.0, 0.0); // Traslación de la órbita
	glTranslatef(radioOrbitaVenus, 0.0, 0.0); // Movemos el planeta a su órbita
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f); // Alinear la esfera en el eje Y
	// Inclinamos, rotamos el planeta, aplicamos texturas y dibujamos la esfera
	glRotatef(inclinacionVenus, -1.0f, 0.0f, 0.0f); // Dar la inclinación real de la tierra
	glRotatef(rotacionVenus, 0.0f, 0.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, texturaVenusID);
	glEnable(GL_TEXTURE_2D);
	dibujarEsfera(radioMercurio, 50, 50);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void pintarTierra() {
	glPushMatrix();
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f); // Alinear la esfera por los polos
	glRotatef(inclinacionTierra, -1.0f, 0.0f, 0.0f); // Dar la inclinación real de la tierra
	glRotatef(rotacionTierra, 0.0f, 0.0f, 1.0f); // Realizar la rotación de la tierra
	
	// Seleccinamos la textura dependiendo de la variable ozono
	switch (ozono) {
	case 0: glBindTexture(GL_TEXTURE_2D, texturaTierraID); break;
	case 1: glBindTexture(GL_TEXTURE_2D, ozono2023); break;
	case 2: glBindTexture(GL_TEXTURE_2D, ozono2018); break;
	case 3: glBindTexture(GL_TEXTURE_2D, ozono2013); break;
	case 4: glBindTexture(GL_TEXTURE_2D, ozono2008); break;
	case 5: glBindTexture(GL_TEXTURE_2D, ozono2003); break;
	case 6: glBindTexture(GL_TEXTURE_2D, ozono1998); break;
	}
	
	glEnable(GL_TEXTURE_2D);
	dibujarEsfera(1.5, 50, 50);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void pintarLuna() {
	glPushMatrix();
	glRotatef(inclinacionPlanoLuna, 1.0f, 0.0f, 0.0f); // Dar la inclinación al plano de orbitación de la luna
	glRotatef(anguloLuna, 0.0, -1.0, 0.0); // Rotación de la luna respecto de la tierra
	glTranslatef(radioOrbitaLuna, 0.0, 0.0); // La desplazamos del centro
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f); // Alinear la esfera en el eje Y
	glRotatef(-90, 0.0f, 0.0f, 1.0f); // La luna siempre da la misma cara a la tierra
	glRotatef(inclinacionLuna, -1.0f, 0.0f, 0.0f); // Dar la inclinación del eje real de la luna
	glBindTexture(GL_TEXTURE_2D, texturaLunaID);
	glEnable(GL_TEXTURE_2D);
	dibujarEsfera(radioLuna, 50, 50);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void dibujarHUD() {

	glDisable(GL_LIGHTING);

	// Guardamos la matriz de proyección y modelview
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0, WIDTH, HEIGHT, 0.0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	// Añadimos la imagen de la leyenda
	glBindTexture(GL_TEXTURE_2D, leyendaID);
	glEnable(GL_TEXTURE_2D);

	// Escribimos el año de la gráfica
	glColor3fv(NEGRO); // Color del texto
	glRasterPos2i(WIDTH - 120 + 40, 80); // Establece la posición inicial del texto
	const char* texto1;
	switch (ozono) {
	case 1: texto1 = "2023"; break;
	case 2: texto1 = "2018"; break;
	case 3: texto1 = "2013"; break;
	case 4: texto1 = "2008"; break;
	case 5: texto1 = "2003"; break;
	case 6: texto1 = "1998"; break;
	default: texto1 = "ERROR"; break;
	}
	for (int i = 0; texto1[i] != '\0'; ++i) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, texto1[i]);
	}

	// Escribimos la unidad de medida
	glColor3fv(NEGRO); // Color del texto
	glRasterPos2i(WIDTH - 120 + 10, HEIGHT - 35); // Establece la posición inicial del texto
	const char* texto2 = "Ozono total (DU)"; // Ozono total en Dobson Units
	for (int i = 0; texto2[i] != '\0'; ++i) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, texto2[i]);
	}

	// Pintamos el Rectángulo de la leyenda
	glColor3fv(BLANCO);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex2i(WIDTH - 120, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex2i(WIDTH, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex2i(WIDTH, HEIGHT);
	glTexCoord2f(0.0f, 1.0f);
	glVertex2i(WIDTH - 120, HEIGHT);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	// Devolvemos el estado a la matriz de proyección
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}
