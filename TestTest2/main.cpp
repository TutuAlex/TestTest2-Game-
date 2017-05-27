#include "functions.h"



#include "vector3d.h"






FILE _iob[] = { *stdin, *stdout, *stderr };

extern "C" FILE * __cdecl __iob_func(void)
{
	return _iob;
}
























float angle = 0.0;

//this is for the triangle
//const int triangle = 1;
























//texture
unsigned int  tex;


//cube .obj
int cube;

void init()
{
	glClearColor(0.5, 0.5, 0.5, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, 640.0 / 480.0, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
	//glShadeModel(GL_SMOOTH);

	//glNewList(triangle, GL_COMPILE);


	//	glScalef(1.0, 0.5, 1.0);
	//glBegin(GL_TRIANGLES);
	//glColor3f(1.0, 0.0, 0.0);
	//	glVertex3f(0.0, 2.0, 0.0);
	//	glColor3f(0.0, 1.0, 0.0);
	//	glVertex3f(-2.0, -2.0, 0.0);
	//	glColor3f(0.0, 0.0, 1.0);
	//	glVertex3f(2.0, -2.0, 0.0);
	//   glEnd();

	//glEndList();

	glEnable(GL_DEPTH_TEST);
	cube = loadObject("suzanne.obj");




	//glEnable(GL_TEXTURE_2D);

	//tex = loadTexture("bricks3.bmp");

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	//glEnable(GL_FOG);

	//glFogi(GL_FOG_MODE, GL_EXP);

	//THESE FOR LINEAR FOG (instead of expodential (EXP))

	//glFogf(GL_FOG_START, 1.0);
	//glFogf(GL_FOG_END, 5.0);

	//glFogf(GL_FOG_DENSITY, 0.6);
	
	float color[] = { 0.5, 0.5, 0.5, 1.0 };

	glFogfv(GL_FOG_COLOR, color);

	//glEnable(GL_COLOR_MATERIAL);


	float col[] = { 1.0,1.0,1.0,1.0 };  //light color is white
	glLightfv(GL_LIGHT0, GL_DIFFUSE, col);

	//float dif[] = {1.0, 1.0, 1.0, 1.0};
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, dif);

	//float amb[] = { 0.2, 0.2, 0.2, 0.2 };
	//	glLightfv(GL_LIGHT0, GL_AMBIENT, amb);


}



void display()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	float pos[] = { -2.0, 2.0, -3.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, pos);

	glPushMatrix();

	glTranslatef(-2.0, 0.0, -10.0);
	//glRotatef(angle, 1.0, 1.0, 1.0);


	// glBindTexture(GL_TEXTURE_2D, tex);

	//makes plane
glBegin(GL_QUADS);
	//	glTexCoord2f(0.0, 1.0);
		glVertex3f(-2.0, 2.0, -10.0);
	//  glTexCoord2f(0.0, 0.0);
		glVertex3f(-2.0, -2.0, -10.0);
	//	glTexCoord2f(1.0, 0.0);
		glVertex3f(2.0, -2.0, -10.0);
	//   glTexCoord2f(1.0, 1.0);
		glVertex3f(2.0, 2.0, -10.0);



		glVertex3f(-1.0, 3.0, -9.0);
		glVertex3f(-1.0, -3.0, -9.0);
		glVertex3f(3.0, -3.0, -9.0);
		glVertex3f(3.0, 3.0, -9.0);




glEnd();
	//this draws the cube above
	//drawCube(1.0);


	//this scales
	//glScalef(1.0, 0.5, 1.0);


	//this calls the triangle list above
	//glCallList(triangle);
/*
	glCallList(cube);
	glPopMatrix();

	glTranslatef(2.0, 0.0, -8.0);
	glRotatef(-angle ,1, 1, 1);
	glCallList(cube);
	*/
}




int main(int argc, char **argv) {

	//if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {

	//	std::cout <<"SDL could not initialize.. SDL error: " << SDL_GetError() << std::endl;
	//}

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Surface* screen;
	screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE | SDL_OPENGL);
	bool running = true;

	const int FPS = 30;
	Uint32  start;
	SDL_Event event;

	init();

	while (running)
	{
		start = SDL_GetTicks();

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{

			case SDL_QUIT:
				running = false;
				break;
			}
		}

		//logic and render

		display();
		SDL_GL_SwapBuffers();
		angle += 0.5;

		if (angle > 360) {
			angle -= 360;

		}

		//SDL_Flip(screen);
		if (1000 / FPS > SDL_GetTicks() - start)
		{
			SDL_Delay(1000 / FPS - (SDL_GetTicks() - start));
		}

	}


	SDL_Quit();













	vector3d vec1;
	vector3d vec2(1, 2, 3);
	vector3d vec3(6, 5, 4);
	std::cout << vec1 << vec2;
	std::cout << vec2.length() << std::endl;

	vec2.normalize();
	std::cout << vec2;
	vector3d vec4 = vec2 + vec3;

	std::cout << vec4;

	vec4 = vec2;
	std::cout << vec4;
	//







	//return EXIT_SUCCESS;
	//system("pause");
	return 0;
}