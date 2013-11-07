/*
 * Filename: main.cpp
 * Author: Sanket Sudake <sanketsudake at gmail.com>
 * Licence: GNU GPL v3
 */

using namespace std;

#include <cstdio>
#include <cstdlib>
#include <cmath>
// SDL Dev header file
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
// OpenGL header files
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

class Drop
{
public:
};

// Load windowid for current window
int windowid = 0;
// Stores background texture id
unsigned int bg = 0;
int raininit = 1;

// Get random number
inline int getnos(int range)
{
	return ( rand() % range );
}

// Get random floating number
inline float getnosf(int range)
{
	return (rand() % range + (rand() % 10 * 0.1));
}

// Get random value for color
inline float getcolf()
{
	return (rand() % 11 * 0.1);
}

/*
 * Load texture image with specified name
 * prints error and exists program if specified image
 * not working properly
 * return texture image id
 */
unsigned int loadTexture(const char* filename)
{
	unsigned int id;
	SDL_Surface* img = SDL_LoadBMP(filename);

	if(img == 0)
	{
		printf("\nBinding error .\n");
		exit(1);
	}
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->w, img->h, 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, img->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	SDL_FreeSurface(img);
	return id;
}

/*
 * Innitialize all parameters for opengl window
 * Enable all required features
 */
static void init()
{
	glClearColor(0, 0.5, 0.6, 0.5);
	glMatrixMode(GL_PROJECTION);
	glOrtho(0, 10, 0, 10, 0, 10);
	glEnable(GL_DEPTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);

	bg =  loadTexture("assets/picture.bmp");
}

/*
 * Display routine for window
 */
static void display()
{
	char projname[] = "RainGL";
	char name[] = "r: rain q:quit";
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);



	/* Show project title
	 * Interface information
	 */
	glPushMatrix();
	glColor4f(0, 0, 0, 0.5);
	for(int i = 0; i < 14; i++)
	{
		if(i < 7)
		{
			if(raininit)
			{
				glRasterPos3f(50 + 2 * i, 45, 0);
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, projname[i]);
				//glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, projname[i]);
			}
			else
			{
				glRasterPos3f(140 + 1.1 * i, 85, 0);
				glutBitmapCharacter(GLUT_BITMAP_9_BY_15, projname[i]);
			}
		}
		glRasterPos3f(140+ 1 * i, 80, 0);
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, name[i]);
	}
	glPopMatrix();

	glPushMatrix();
	glColor4f(0, 0, 1, 0.5);
	glTranslatef(50, 50, 0);
	glRotatef(10, 0, 0, 1);
	glutSolidCube(10);
	glColor4f(0, 0, 0, 0.5);
	glutWireCube(10);
	glPopMatrix();

	glPushMatrix();
	glColor4f(1, 1, 0, 0.5);
	glTranslatef(55, 50, 0);
	glRotatef(80, 0, 0, 1);
	glutSolidCube(10);
	glColor4f(0, 0, 0, 0.5);
	glutWireCube(10);
	glPopMatrix();

	// Bind texture according to ortho parameters
	glPushMatrix();
	glColor4f(1, 1, 0, 0.5);
	glBindTexture(GL_TEXTURE_2D, bg);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0, 0, 0.0);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0, 90, 0.0);
	glTexCoord2f(1.0,  0.0);
	glVertex3f(160, 90, 0.0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(160, 0, 0.0);
	glEnd();
	glPopMatrix();

	glutSwapBuffers();
}

/*
 * Reshapes window when maximized
 */
static void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 160, 0, 90, 0, 100);

}

static void keyboard(unsigned char key, int x, int y)
{
	/*
	 * Keyboard event handling function
	 * @key - Character code
	 * @x   - x position on display
	 * @y   - y position on display
	 */
	x = x + 1;
	y = y + 1;
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
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(900, 700);
	glutCreateWindow("RainGL");
	windowid = glutGetWindow();
	init();
	glutFullScreen();
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}
