#pragma once
#ifndef VECTOR3D_H
#define VECTOR3D_H

#include<iostream>
#include<cmath>

using namespace std;

class vector3d {



public:

	float x, y, z;
	vector3d();
	vector3d(float a, float b);
	vector3d(float a, float b, float c);

	//not useful ATM
	float dotProduct(const vector3d& vec2);

	//gets 2 vectors and calculate a vector perpandicular to those 2 (not used)
	vector3d crossProduct(const vector3d& vec2);


	//get length of the vector with Pythagoras Formula
	float length();

	//get the lentgh of the vector and divide x y z with it (so to define a direction)
    void normalize();


	//change x y and z coordinates of the vector
	void change(float a , float b , float c);

	//overloaded function
	void change(vector3d& vec);
	//void change(vector3d vec); MIGHT NOT BE NEEDED
	void changeX(float a);
	void changeY(float a);
    void changeZ(float a);

	//this will add the curent x y z to the current vectors x y z 
	vector3d operator+(const vector3d& vec2);

	vector3d operator-(const vector3d& vec2);

	vector3d operator*(float num);

	vector3d operator/(float num);


	

	vector3d& operator+=(const vector3d& vec2);

	vector3d& operator-=(const vector3d& vec2);

	vector3d& operator*=(float num);

	vector3d& operator/=(float num);



	bool operator==(const vector3d vec2);
	bool operator!=(const vector3d vec2);


	
	friend std::ostream& operator<<(std::ostream& out, const vector3d& vec);



};














#endif VECTOR3D_H
