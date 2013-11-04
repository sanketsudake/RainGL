#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

float angle = 0.0;
const int triangle = 1;

unsigned int loadTexture(const char* filename)
{
	SDL_Surface* img = SDL_LoadBMP(filename);
	unsigned int id;
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img->w, img->h, 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, img->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	SDL_FreeSurface(img);
	return id;
}

unsigned int face1;

void init()
{
	glClearColor(0.0,0.0,0.0,1.0);	//background color and alpha
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45,640.0/480.0,1.0,500.0);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	face1 = loadTexture("./picture.bmp");
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.0,0.0,-10.0);
	// glRotatef(angle,1.0,1.0,1.0);	// angle, x-axis, y-axis, z-axis
	glBindTexture(GL_TEXTURE_2D, face1);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0,2.0);
		glVertex3f(-2.0,2.0,2.0);
		glTexCoord2f(0.0,0.0);
		glVertex3f(-2.0,-2.0,2.0);
		glTexCoord2f(2.0,0.0);
		glVertex3f(2.0,-2.0,2.0);
		glTexCoord2f(2.0,2.0);
		glVertex3f(2.0,2.0,2.0);
	glEnd();
}

int main(int argc, char** argv)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Surface *screen;
	screen = SDL_SetVideoMode(1024, 720, 32, SDL_SWSURFACE|SDL_OPENGL | SDL_FULLSCREEN);
//	screen = SDL_SetVideoMode(640, 480, 8, SDL_SWSURFACE|SDL_OPENGL|SDL_FULLSCREEN);
	bool running = true;
	const int FPS = 30;
	Uint32 start;
	SDL_Event event;
	init();
	while(running) {
		start = SDL_GetTicks();
		while(SDL_PollEvent(&event)) {
			switch(event.type) {
				case SDL_QUIT:
					running = false;
					break;
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym)
					{
						case SDLK_ESCAPE:
							running = false;
							break;
					}
					break;
			}
		}

		display();
		SDL_GL_SwapBuffers();
		angle += 0.9;
		if(angle > 360)
			angle -= 360;
		if(1000/FPS > SDL_GetTicks()-start)
			SDL_Delay(1000/FPS-(SDL_GetTicks()-start));
	}
	//SDL_Quit();
	atexit(SDL_Quit);
	return 0;
}
