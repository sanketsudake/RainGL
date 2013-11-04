using namespace std;

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

int windowid = 0;
unsigned int bg = 0;

unsigned int loadTexture(const char* filename)
{
	unsigned int id;
	SDL_Surface* img = SDL_LoadBMP(filename);
	if(img == 0)
	{
		printf("Binding error");
		exit(1);
	}
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img->w, img->h, 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, img->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	SDL_FreeSurface(img);
	return id;
}
static void init()
{
	/*
	 *Innitialize OpenGL
	 */
	glClearColor(0, 0, 0, 0);
	glMatrixMode(GL_PROJECTION);
	glOrtho(0, 10, 0, 10, 0, 10);
	bg =  loadTexture("castle.bmp");
}
static void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(1, 0, 0, 1);
	glBindTexture(GL_TEXTURE_2D, bg);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0, 0, 0.0);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0, 80, 0.0);
	glTexCoord2f(1.0,  0.0);
	glVertex3f(150, 80, 0.0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(150, 0, 0.0);
	glEnd();

	glutSwapBuffers();
}
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
	switch(key)
	{
	case 'q':
	case 'Q':
		glutDestroyWindow(windowid);
		exit(0);
		break;
	case 'r':
	case 'R':
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
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
