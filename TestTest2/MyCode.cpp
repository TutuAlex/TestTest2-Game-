/*#include <windows.h>

#include<SDL.h>

#include<GL\glew.h>
#include<GL\GL.h>                              
#include<GL\GLU.h>


#include <cstdlib>
#include<vector>
#include<string>
#include<algorithm>
#include<fstream>
#include<cstdio>
#include<iostream>




#include "vector3d.h"






FILE _iob[] = { *stdin, *stdout, *stderr };

extern "C" FILE * __cdecl __iob_func(void)
{
	return _iob;
}











struct coordinate {

	float x, y, z;
	coordinate(float a, float b, float c) : x(a), y(b), z(c) {};
};


struct face {
	int facenum;
	bool four;
	int faces[4];

	face(int facen, int f1, int f2, int f3) : facenum(facen) {
		faces[0] = f1;
		faces[1] = f2;
		faces[2] = f3;
		four = false;

	}



	face(int facen, int f1, int f2, int f3, int f4) : facenum(facen) {
		faces[0] = f1;
		faces[1] = f2;
		faces[2] = f3;
		faces[3] = f4;
		four = true;

	}

};






float angle = 0.0;

//this is for the triangle
//const int triangle = 1;


int loadObject(const char* filename)
{
	std::vector<std::string*> coord;
	std::vector<coordinate*> vertex;
	std::vector<face*>faces;
	std::vector<coordinate*> normals;
	std::ifstream in(filename);

	if (!in.is_open()) 
	{

		std::cout << "not oppened" << std::endl;
		return -1;
	}

	char buf[256];
	while (!in.eof())
	{
		in.getline(buf, 256);
		coord.push_back(new std::string(buf));

	}

	for (int i = 0; i < coord.size(); i++) {

		if (coord[i]->c_str()[0] == '#')
			continue;
		else if (coord[i]->c_str()[0] == 'v' && coord[i]->c_str()[1] == ' ')
		{


			float tmpx, tmpy, tmpz;

			sscanf(coord[i]->c_str(), "v %f %f %f", &tmpx, &tmpy, &tmpz);
			vertex.push_back(new coordinate(tmpx, tmpy, tmpz));
		}
		else if (coord[i]->c_str()[0] == 'v' && coord[i]->c_str()[1] == 'n')
		{

			float tmpx, tmpy, tmpz;
			sscanf(coord[i]->c_str(), "vn %f %f %f", &tmpx, &tmpy, &tmpz);
			normals.push_back(new coordinate(tmpx, tmpy, tmpz));
		}
		else if (coord[i]->c_str()[0] == 'f')
		{
			int a, b, c, d, e;
			if (count(coord[i]->begin(), coord[i]->end(), ' ') == 4)
			{
				sscanf(coord[i]->c_str(), "f %d//%d %d//%d %d//%d %d//%d", &a, &b, &c, &b, &d, &b, &e, &b);
				faces.push_back(new face(b, a, c, d, e));
			}
			else {
				sscanf(coord[i]->c_str(), "f %d//%d %d//%d %d//%d", &a, &b, &c, &b, &d, &b);
				faces.push_back(new face(b, a, c, d));
			}

		}


	}

	//draw

	int num;
	num = glGenLists(1);
	glNewList(num, GL_COMPILE);

	for (int i = 0; i < faces.size(); i++)
	{
		if (faces[i]->four)
		{
			glBegin(GL_QUADS);
			glNormal3f(normals[faces[i]->facenum - 1]->x, normals[faces[i]->facenum - 1]->y, normals[faces[i]->facenum - 1]->z);
			glVertex3f(vertex[faces[i]->faces[0] - 1]->x, vertex[faces[i]->faces[0] - 1]->y, vertex[faces[i]->faces[0] - 1]->z);

			glVertex3f(vertex[faces[i]->faces[1] - 1]->x, vertex[faces[i]->faces[1] - 1]->y, vertex[faces[i]->faces[1] - 1]->z);

			glVertex3f(vertex[faces[i]->faces[2] - 1]->x, vertex[faces[i]->faces[2] - 1]->y, vertex[faces[i]->faces[2] - 1]->z);

			glVertex3f(vertex[faces[i]->faces[3] - 1]->x, vertex[faces[i]->faces[3] - 1]->y, vertex[faces[i]->faces[3] - 1]->z);


			glEnd();
		}
		else
		{
			glBegin(GL_TRIANGLES);
			glNormal3f(normals[faces[i]->facenum - 1]->x, normals[faces[i]->facenum - 1]->y, normals[faces[i]->facenum - 1]->z);
			glVertex3f(vertex[faces[i]->faces[0] - 1]->x, vertex[faces[i]->faces[0] - 1]->y, vertex[faces[i]->faces[0] - 1]->z);

			glVertex3f(vertex[faces[i]->faces[1] - 1]->x, vertex[faces[i]->faces[1] - 1]->y, vertex[faces[i]->faces[1] - 1]->z);

			glVertex3f(vertex[faces[i]->faces[2] - 1]->x, vertex[faces[i]->faces[2] - 1]->y, vertex[faces[i]->faces[2] - 1]->z);


			glEnd();

		}




	}




	glEndList();











	for (int i = 0; i < coord.size(); i++)
		delete coord[i];

	for (int i = 0; i < faces.size(); i++)
		delete faces[i];

	for (int i = 0; i < normals.size(); i++)
		delete normals[i];

	for (int i = 0; i < vertex.size(); i++)
		delete vertex[i];



	return num;

}





void drawCube(float size)
{


	//actuall color of the material
	float difamb[] = { 1.0, 0.5, 0.3, 1.0 };

	glBegin(GL_QUADS);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, difamb);


	//front face
	glNormal3f(0.0, 0.0, 1.0);


	glColor3f(1.0, 0.0, 0.0);

	//material

	glVertex3f(size / 2, size / 2, size / 2);
	glVertex3f(-size / 2, size / 2, size / 2);
	glVertex3f(-size / 2, -size / 2, size / 2);
	glVertex3f(size / 2, -size / 2, size / 2);



	//left face
	glNormal3f(-1.0, 0.0, 0.0);

	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(-size / 2, size / 2, size / 2);
	glVertex3f(-size / 2, size / 2, -size / 2);
	glVertex3f(-size / 2, -size / 2, -size / 2);
	glVertex3f(-size / 2, -size / 2, size / 2);

	//back face
	glNormal3f(0.0, 0.0, -1.0);
	glColor3f(0.0, 0.0, 1.0);


	glVertex3f(size / 2, size / 2, -size / 2);
	glVertex3f(-size / 2, size / 2, -size / 2);
	glVertex3f(-size / 2, -size / 2, -size / 2);
	glVertex3f(size / 2, -size / 2, -size / 2);

	//right
	glNormal3f(1.0, 0.0, 0.0);
	glColor3f(0.0, 0.5, 1.0);


	glVertex3f(size / 2, size / 2, -size / 2);
	glVertex3f(size / 2, size / 2, size / 2);
	glVertex3f(size / 2, -size / 2, size / 2);
	glVertex3f(size / 2, -size / 2, -size / 2);


	//top face
	glNormal3f(0.0, 1.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);

	glVertex3f(size / 2, size / 2, size / 2);
	glVertex3f(-size / 2, size / 2, size / 2);
	glVertex3f(-size / 2, size / 2, -size / 2);
	glVertex3f(size / 2, size / 2, -size / 2);

	//bottom face
	glNormal3f(0.0, -1.0, 0.0);
	glColor3f(1.0, 0.0, 1.0);

	glVertex3f(size / 2, -size / 2, size / 2);
	glVertex3f(-size / 2, -size / 2, size / 2);
	glVertex3f(-size / 2, -size / 2, -size / 2);
	glVertex3f(size / 2, -size / 2, -size / 2);



	glEnd();

}











unsigned int loadTexture(const char* filename)
{
	//SDL has functions to load an image NOT OpenGL

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








//texture
unsigned int  tex;


//cube .obj
int cube;

void init()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
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
	cube = loadObject("box.obj");




	//glEnable(GL_TEXTURE_2D);

	//tex = loadTexture("bricks3.bmp");

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

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

	glTranslatef(0.0, 0.0, -5.0);
	glRotatef(angle, 1.0, 1.0, 1.0);

	// glBindTexture(GL_TEXTURE_2D, tex);

	//makes plane
	//glBegin(GL_QUADS);
	//	glTexCoord2f(0.0, 1.0);
	//	glVertex3f(-2.0, 2.0, 0.0);
	//  glTexCoord2f(0.0, 0.0);
	//	glVertex3f(-2.0, -2.0, 0.0);
	//	glTexCoord2f(1.0, 0.0);
	//	glVertex3f(2.0, -2.0, 0.0);
	//   glTexCoord2f(1.0, 1.0);
	//	glVertex3f(2.0, 2.0, 0.0);

	//glEnd();
	//this draws the cube above
	//drawCube(1.0);


	//this scales
	//glScalef(1.0, 0.5, 1.0);


	//this calls the triangle list above
	//glCallList(triangle);

	glCallList(cube);

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

*/