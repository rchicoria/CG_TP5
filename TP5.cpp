/*
Ricardo Pinto Lopes 2008114843
Rui Pedro da Cunha Santos Chicória 2008115099
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

//--------------------------------- Definir cores
#define AZUL     0.0, 0.0, 1.0, 1.0
#define VERMELHO 1.0, 0.0, 0.0, 1.0
#define AMARELO  1.0, 1.0, 0.5, 1.0
#define VERDE    0.0, 1.0, 0.0, alpha
#define LARANJA  1.0, 0.5, 0.1, alpha
#define WHITE    1.0, 1.0, 1.0, 1.0
#define BLACK    0.0, 0.0, 0.0, 1.0
#define GRAY     0.92, 0.92, 0.92, 1.0
#define NIGHT     0.2, 0.2, 0.2, 1.0
#define PI		 3.14159
//================================================================================
//===========================================================Variaveis e constantes

//------------------------------------------------------------ Sistema Coordenadas
GLfloat   xC=1.0, yC=1.0, zC=1.0;
GLint     wScreen=800, hScreen=600;

GLint    msec=10;

//------------------------------------------------------------ Observador

GLfloat  raio   = 1;

GLfloat  obsP[] = {raio/5, 0.3, raio};   //posicao inicial do observador

//------------------------------------------------------------- Esferas
GLfloat  incar   = 0.5; //rotaçao da esfera
GLfloat  alpha	 = 0.5;
GLfloat angRot = 0;

GLfloat   sphereP1[] = {0 ,0, 0}; //Posicao do sphere
GLfloat   sphereT1[] = {0.15, 100, 100}; //Tamanho do sphere

GLfloat   sphereP2[] = {0.3 ,0, 0.3}; //Posicao do sphere
GLfloat   sphereT2[] = {0.15, 100, 100}; //Tamanho do sphere

//================================================================================
//=========================================================================== INIT

void init(void)
{
	glShadeModel(GL_SMOOTH);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glClearColor(AMARELO);
	glEnable(GL_CULL_FACE);
}


void resizeWindow(GLsizei w, GLsizei h)
{
 	wScreen=w;
	hScreen=h;
	glutPostRedisplay();
}

void sphere1()
{
	glColor4f(VERDE);
	glTranslatef(sphereP1[0], sphereP1[1], sphereP1[2]);
	glutSolidSphere(sphereT1[0], sphereT1[1], sphereT1[2]);
}

void sphere2()
{
	glColor4f(LARANJA);
	glRotatef(angRot,0,1,0);
	glTranslatef(sphereP2[0], sphereP2[1], sphereP2[2]);
	glutSolidSphere(sphereT2[0], sphereT2[1], sphereT2[2]);
}

void drawScene(){
	
	if(angRot >= 360)
		angRot -= 360;
	else if(angRot < 0)
		angRot += 360;
	GLfloat tan = (obsP[0]/(GLfloat)raio)/(obsP[2]/(GLfloat)raio);
	GLfloat angLook = atan(tan);
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Eixos
	glColor4f(BLACK);
	glBegin(GL_LINES);
		glVertex3i( 0, 0, 0); 
		glVertex3i(xC, 0, 0); 
	glEnd();
	glBegin(GL_LINES);
		glVertex3i(0, 0, 0); 
		glVertex3i(0, yC, 0); 
	glEnd();
	glBegin(GL_LINES);
		glVertex3i( 0, 0, 0); 
		glVertex3i( 0, 0,zC); 
	glEnd();
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Sphere
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPushMatrix();
		if(angRot > angLook+90 && angRot < angLook+270)
			sphere2();
		else
			sphere1();
	glPopMatrix();
	
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPushMatrix();
		if(angRot > angLook+90 && angRot < angLook+270)
			sphere1();
		else
			sphere2();
	glPopMatrix();
}

void display(void){
	
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~[ Apagar ]
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~[ Projeccao]
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    gluPerspective(104, wScreen/hScreen, 0.01, zC*2);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~[ Modelo+View(camera/observador) ]
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(obsP[0], obsP[1], obsP[2], 0, 0, 0, 0, 1, 0);
	
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~[ Objectos ]
	drawScene();

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Actualizacao
	glutSwapBuffers();
}

//======================================================= EVENTOS
void keyboard(unsigned char key, int x, int y){	
    switch (key) {
    case 'T':
    case 't':
    	if(alpha<1)
    		alpha+=0.1;
	    break;
	case 'R':
    case 'r':
    	if(alpha>0)
    		alpha-=0.1;
	    break;
	
	case 'A':
    case 'a':
	    incar+=0.1;
	    break;
	
	case 'S':
    case 's':
	    incar-=0.1;
	    break;

    default:
	    break;
    }
	
    glutPostRedisplay();
}

void Timer(int value) 
{
	angRot+=incar;
	glutPostRedisplay();
	glutTimerFunc(msec,Timer, 1);
}

//======================================================= MAIN
int main(int argc, char** argv){

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
	glutInitWindowSize (wScreen, hScreen); 
	glutInitWindowPosition (100, 100); 
	glutCreateWindow ("TP5");
  
	init();

	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display); 
	glutReshapeFunc(resizeWindow);
	glutTimerFunc(msec,Timer, 1);

	glutMainLoop();

	return 0;
}
