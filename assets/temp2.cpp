using namespace std;

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

int drop_no = 100;
int windowid = 0;
int raininit = 1;
void init();

void display();
void reshape(int w, int h);
/* Get single random number
 * in given range
 */
inline int getnos(int range){
	return ( rand() % range );
}
inline float getnosf(int range){
	return (rand() % range + (rand() % 10 * 0.1));
}
inline float getcolf(){
	return (rand() % 11 * 0.1);
}
/*
 *Config
 *Config for each droplet
 */

class Config{
public:
	int speed;
	int angle;
	int intensity ;
	float color[3];
	int size;

	Config(){
		speed = 0;
		angle = 0;
		intensity = 0;
		color[1] = 0, color[2] = 0, color[3] = 0 ;
		size = 0;
	}
};
class Drop{
public:

};
class Area{
public:
	int width;
	int height;
};
void keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 'q':
	case 'Q':
		glutDestroyWindow(windowid);
		exit(0);
		break;

	case 'r':
	case 'R':
		raininit = 0;
		// int temp = getnos(10);
		// if(temp < 5)
		//    	drop_no -= 15;
		// else
		// 	drop_no += 20;
		//glRotatef(10,0, 0, 1);
		break;
	}
	glutPostRedisplay();
}


int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800, 700);
	glutInitWindowPosition(0, 0);
 	glutCreateWindow("RainGL");
	glutSetWindowTitle("RainGL");
	windowid = glutGetWindow();
	init();
	glutFullScreen();
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
    return 0;
}

void init()
{
	glClearColor (0, 0, 0, 1);
	glColor4f(1.0, 1.0, 1.0, 0.5);

	/* Set background in window to white
	 */

	/* Set window co-ordinate system
	 */
	glOrtho(0.0, 10.0, 0.0, 10.0, 0.0, 10.0);
}

void display()
{
	/* Clear all pixels
	 */
	char projname[] = "RainGL";
	char name[] = "r: rain q:quit";
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_FOG);
	GLfloat fogColor[4] = {1, 1, 1, 0.5};
	GLfloat density = 1;
	int fogMode = GL_LINEAR;
	glFogi (GL_FOG_MODE, fogMode);
	glFogfv (GL_FOG_COLOR, fogColor);
	glFogf (GL_FOG_DENSITY, density);
	glHint (GL_FOG_HINT, GL_DONT_CARE);
	glFogf (GL_FOG_START, 0.0);
	glFogf (GL_FOG_END, 9.0);
	glColor3f(1, 1, 1);
	for(int i = 0; i < 14; i++)
	{
		if(i < 7 && raininit)
		{
			glRasterPos3f(4.5 + 0.1 * i, 5, 0);
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, projname[i]);
			//glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, projname[i]);
		}
		else if(i < 7)
		{
			glRasterPos3f(8 + 0.1 * i, 9.5, 0);
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, projname[i]);
		}
		else
		{}
		glRasterPos3f(8+ 0.1 * i, 9, 0);
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, name[i]);
	}
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_DEPTH_TEST);

    GLfloat light_position1[] = { 0.0, 0.0, 0.0, 0.0 };
	GLfloat light_position2[] = { 7.0, 0.0, 0.0, 0.0 };
	GLfloat light_position3[] = { 0.0, 7.0, 0.0, 0.0 };

	for(int i = 0; i < drop_no; i++){
		glPushMatrix();

		glLightfv(GL_LIGHT0, GL_POSITION, light_position1);
		glLightfv(GL_LIGHT1, GL_POSITION, light_position2);
		glLightfv(GL_LIGHT2, GL_POSITION, light_position3);

		glTranslatef(0, 0, 0);
		glTranslatef(getnosf(10), getnosf(10), 0);
		glColor4f(0.5, 0.5, 0.5, 0.4);
		//glColor4f(getcolf(), getcolf(), getcolf(), 0.6);
		glutSolidSphere(0.5*getcolf(), 100, 10 );

		glPopMatrix();
	}

	///glutSolidSphere(GLdouble radius, GLint slices, GLint stacks)
	glutSwapBuffers();
}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	glOrtho(0.0, 10.0, 0.0, 10.0, 0.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
