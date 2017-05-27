#include "vector3d.h"


vector3d::vector3d() {
	x = y = z = 0;
}
vector3d::vector3d(float a, float b) {

	x = a;
	y = b;
	z = 0;

}
vector3d::vector3d(float a, float b, float c) {

	x = a;
	y = b;
	z = c;

}

//not useful ATM
float vector3d::dotProduct(const vector3d& vec2) {
	
	return (x*vec2.x + y*vec2.y + z*vec2.z);

}

//gets 2 vectors and calculate a vector perpandicular to those 2 (not used)
vector3d vector3d:: crossProduct(const vector3d& vec2) {

	return (vector3d(y*vec2.z-z*vec2.y,x*vec2.z-z*vec2.x,x*vec2.y-y*vec2.x) );
}


//get length of the vector with Pythagoras Formula
float vector3d::length() {

	return sqrt(x*x + y*y + z*z);
}

//get the lentgh of the vector and divide x y z with it (so to define a direction)
void vector3d::normalize() {

	float len = length();
	if (len != 0) {

		x /= len;
		y /= len;
		z /= len;
	}
}


//change x y and z coordinates of the vector
void vector3d::change(float a, float b, float c) {

	x = a;
	y = b;
	z = c;
}

//overloaded function
void vector3d::change(vector3d& vec) {

	x = vec.x;
	y = vec.y;
	z = vec.z;
}
//void change(vector3d vec); MIGHT NOT BE NEEDED
void vector3d::changeX(float a) {

	x = a;
}
void vector3d::changeY(float a) {
	y = a;

}
void vector3d::changeZ(float a) {
	z = a;

}

//this will add the curent x y z to the current vectors x y z 
vector3d vector3d::operator+(const vector3d& vec2) {
	return vector3d(x + vec2.x, y + vec2.y, z + vec2.z);

}

vector3d vector3d::operator-(const vector3d& vec2) {

	return vector3d(x - vec2.x, y - vec2.y, z - vec2.z);
}

vector3d vector3d::operator*(float num) {

	return vector3d(x * num, y *num, z * num);

}

vector3d vector3d::operator/(float num) {
	if (num != 0) 
		return vector3d(x / num, y / num, z / num);
	
	else
		return vector3d();
}




vector3d& vector3d::operator+=(const vector3d& vec2) {

	x += vec2.x;
	y += vec2.y;
	z += vec2.z;


	return *this;
}

vector3d& vector3d::operator-=(const vector3d& vec2) {
	x -= vec2.x;
	y -= vec2.y;
	z -= vec2.z;


	return *this;
}



vector3d& vector3d::operator*=(float num) {


	x *= num;
	y *= num;
	z *= num;



	return *this;
}

vector3d& vector3d::operator/=(float num) {
	if (num != 0) {
		x /= num;
		y /= num;
		z /= num;
	}


	return *this;

}



bool vector3d::operator==(const vector3d vec2) {

	return (x == vec2.x && y == vec2.y && z == vec2.z);
}
bool vector3d::operator!=(const vector3d vec2) {


  return !(*this == vec2);

}



std::ostream&  operator<< (std::ostream& out,
	const vector3d& vec) {

	out << vec.x << " " << vec.y << "  " << vec.z <<
		std::endl;

	return out;

}
