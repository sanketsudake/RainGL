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
#define MAXX 160
#define MAXY 90
#define DROP_RADIUS 6
// Load windowid for current window
int windowid = 0;
int raininit = 1;
int drop_no = 100;

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

class BackGround
{
	int bg;
public:
	BackGround(const char *filename);
	void display();
};
BackGround :: BackGround(const char *filename)
{
	bg =  loadTexture(filename);
}
void BackGround :: display(void)
{
	// Bind texture according to ortho parameters
	glPushMatrix();
	glColor4f(0, 1, 0, 0.5);
	glBindTexture(GL_TEXTURE_2D, bg);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0, 0, 0.0);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0, MAXY, 0.0);
	glTexCoord2f(1.0,  0.0);
	glVertex3f(MAXX, MAXY, 0.0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(MAXX, 0, 0.0);
	glEnd();
	glPopMatrix();
}

class InfoText
{
	char projname[10];
	char name[20];
public:
	InfoText();
	void display(int raininit);
};
InfoText :: InfoText()
{
	strcpy(projname, "RainGL");
	strcpy(name, "R: Rain Q: Quit");
}
void InfoText :: display(int raininit)
{
	/* Show project title
	 * Interface information
	 */
	glPushMatrix();
	glColor4f(1, 1, 1, 1);
	for(int i = 0; i < 15; i++)
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
}

class FancyBox
{
	GLfloat color[3];
	GLfloat pos[3];
	GLfloat angle;
	GLfloat size;
	public:
	FancyBox(
		GLfloat color1, GLfloat color2, GLfloat color3,
		GLfloat x, GLfloat y, GLfloat z,
		GLfloat boxangle, GLfloat boxsize	);
	void display(void);
};
FancyBox :: FancyBox(
	GLfloat color1, GLfloat color2, GLfloat color3,
	GLfloat x, GLfloat y, GLfloat z,
	GLfloat boxangle, GLfloat boxsize
	)
{
	color[0] = color1;
	color[1] = color2;
	color[2] = color3;
	pos[0] = x;
	pos[1] = y;
	pos[2] = z;
	angle = boxangle;
	size = boxsize;
}
void FancyBox :: display(void)
{
	/* Show project title
	 * Interface information
	 */
	glPushMatrix();
	glColor4f(color[0], color[1], color[2], 0.5);
	glTranslatef(pos[0], pos[1], pos[2]);
	glRotatef(angle, 0, 0, 1);
	glutSolidCube(size);
	glColor4f(0, 0, 0, 0.5);
	glutWireCube(size);
	glPopMatrix();
}

class Drop
{
	GLfloat trans[3];
	GLfloat color[3];
	GLfloat radius;
public:
	Drop();
	void display();
};
Drop :: Drop()
{
	trans[0] = getnosf(MAXX);
	trans[1] = getnosf(MAXY);
	trans[2] = 0;
	color[0] = getcolf();
	color[1] = getcolf();
	color[2] = getcolf();
	// color[0] = 0;
	// color[1] = 0;
	// color[2] = 0;
	radius = getnosf(DROP_RADIUS);
}
void Drop :: display()
{
	glPushMatrix();
	glTranslatef(trans[0], trans[1], trans[2]);
	glColor4f(color[0], color[1], color[2], 1);
	glutSolidSphere(radius, 100, 10);
	glPopMatrix();
}

// Stores background texture id
BackGround *background;
InfoText *infotext;
FancyBox *box1, *box2;
Drop *drops[100];
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
	infotext = new InfoText();
	box1 = new FancyBox(0, 0, 1, 50, 50, 0, 10, 10);
	box2 = new FancyBox(1, 1, 1, 55, 50, 0, 80, 10);
	background = new BackGround("assets/bg2.bmp");
}

/*
 * Display routine for window
 */
static void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	infotext->display(raininit); // Project title information
	if(raininit)
	{
		box1->display();			// FancyBox in title
		box2->display();			// FancyBox in title
	}
	for (int i = 0; i < drop_no; ++i)
	{
		drops[i] = new Drop();
		drops[i]->display();
	}
	background->display();		 // Background
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
	glOrtho(0, MAXX, 0, MAXY, 0, 100);
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
