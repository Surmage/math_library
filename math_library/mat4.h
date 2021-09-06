#define _USE_MATH_DEFINES
#pragma once
#include <iostream>
#include "vec4.h"
#include "vec3.h"
#include <array>
#include <math.h>

class mat4 {
public:
	std::array<vec4, 4> matrix;
	mat4()
		:matrix({ vec4{1, 0, 0, 0}, vec4{0, 1, 0, 0}, vec4{0, 0, 1, 0}, vec4{0, 0, 0, 1 } })
	{
	}
	mat4(const vec4& r0, const vec4& r1, const vec4& r2, const vec4& r3) 
		:matrix({r0, r1, r2, r3 })
	{
	}
	mat4(const mat4& m) 
	{
		for (unsigned int i = 0; i < 4; i++) {
			vec4 temp{ m.matrix[i].x, m.matrix[i].y, m.matrix[i].z, m.matrix[i].w };
			matrix[i] = temp;
		}
	}

	mat4 operator=(const mat4& rhs) {
		for (int i = 0; i < 4; i++) {
			matrix[i].x = rhs.matrix[i].x;
			matrix[i].y = rhs.matrix[i].y;
			matrix[i].z = rhs.matrix[i].z;
			matrix[i].w = rhs.matrix[i].w;
		}			
		return *this;
	}
	
	mat4 operator*(const mat4& rhs)const{
		mat4 temp;
		for (int i = 0; i < 4; i++) {
			vec4 transpose;
			for (int j = 0; j < 4; j++) {
				vec4 tempVec = rhs.matrix[j];
				transpose.setElement(j, tempVec[i]);
			}
			for (int k = 0; k < 4; k++) {
				//temp[k].setElement(i, matrix[k].dot(matrix[k], transpose));
				temp[k].setElement(i, dot(matrix[k], transpose));
			}
		}
		return temp;
	}
	vec4 operator*(const vec4& rhs)const {
		vec4 temp;
		temp.x = matrix[0].x * rhs.x + matrix[1].x * rhs.y + matrix[2].x * rhs.z + matrix[3].x * rhs.w;
		temp.y = matrix[0].y* rhs.x + matrix[1].y * rhs.y + matrix[2].y * rhs.z + matrix[3].y * rhs.w;
		temp.z = matrix[0].z * rhs.x + matrix[1].z * rhs.y + matrix[2].z * rhs.z + matrix[3].z * rhs.w;
		temp.w = matrix[0].w * rhs.x + matrix[1].w * rhs.y + matrix[2].w * rhs.z + matrix[3].w * rhs.w;
		return temp;
	}
	bool operator==(const mat4& rhs) {
		if (matrix[0] == rhs.matrix[0] && matrix[1] == rhs.matrix[1] && matrix[2] == rhs.matrix[2] && matrix[3] == rhs.matrix[3]) 
			return true;			
		else 
			return false;
	}
	bool operator!=(const mat4& rhs) {
		if (matrix[0] != rhs.matrix[0] || matrix[1] != rhs.matrix[1] || matrix[2] != rhs.matrix[2] || matrix[3] != rhs.matrix[3])
			return true;
		else
			return false;
	} 
	vec4& operator[](const int i) {
		if (i > 3)
			std::cerr << "Error\n";		
		else
			return matrix[i];
	}
	const vec4& operator[](const int i) const {
		if (i > 3)
			std::cerr << "Error\n";
		else
			return matrix[i];
	}
	
	
};

mat4 rotationx(const float rad) {
	mat4 temp;

	temp[0][0] = 1;
	temp[1][1] = cos(rad);
	temp[1][2] = sin(rad);
	temp[2][1] = -sin(rad);
	temp[2][2] = cos(rad);
	temp[3][3] = 1;

	return temp;
}
mat4 rotationy(const float rad) {
	mat4 temp;

	temp[0][0] = cos(rad);
	temp[0][2] = -sin(rad);
	temp[1][1] = 1;
	temp[2][0] = sin(rad);
	temp[2][2] = cos(rad);
	temp[3][3] = 1;

	return temp;
}
mat4 rotationz(const float rad) {
	mat4 temp;

	temp[0][0] = cos(rad);
	temp[0][1] = -sin(rad);
	temp[1][0] = sin(rad);
	temp[1][2] = cos(rad);
	temp[2][2] = 1;
	temp[3][3] = 1;

	return temp;
}

mat4 rotationaxis(const vec3 v, const float rad) {
	float degrees = (rad * 180) / M_PI;
	vec3 normalizeAxis = normalize(v);

	float normAxisX = normalizeAxis[0];
	float normAxisY = normalizeAxis[1];
	float normAxisZ = normalizeAxis[2];

	vec4 column1((pow(normAxisX, 2) + ((pow(normAxisY, 2) + pow(normAxisZ, 2)) * cos(degrees))),
		(normAxisX * normAxisY * (1 - cos(degrees)) + normAxisZ * sin(degrees)),
		(normAxisX * normAxisZ * (1 - cos(degrees)) - normAxisY * sin(degrees)), 0);

	vec4 column2((normAxisX * normAxisY * (1 - cos(degrees)) - normAxisZ * sin(degrees)),
		(pow(normAxisY, 2) + ((pow(normAxisX, 2) + pow(normAxisZ, 2)) * cos(degrees))),
		(normAxisY * normAxisZ * (1 - cos(degrees)) + normAxisX * sin(degrees)), 0);

	vec4 column3((normAxisX * normAxisZ * (1 - cos(degrees)) + normAxisY * sin(degrees)),
		(normAxisX * normAxisZ * (1 - cos(degrees)) - normAxisX * sin(degrees)),
		(pow(normAxisZ, 2) + ((pow(normAxisX, 2) + pow(normAxisY, 2)) * cos(degrees))), 0);

	vec4 column4(
		(v.x * (pow(normAxisY, 2) + pow(normAxisZ, 2)) - normAxisX * (v.y * normAxisY + v.z * normAxisZ)
			* (1 - cos(degrees) + (v.y * normAxisZ - v.z * normAxisY) * sin(degrees))),

		(v.y * (pow(normAxisX, 2) + pow(normAxisZ, 2)) - normAxisY * (v.x * normAxisX + v.z * normAxisZ)
			* (1 - cos(degrees) + (v.z * normAxisX - v.x * normAxisZ) * sin(degrees))),

		(v.z * (pow(normAxisX, 2) + pow(normAxisY, 2)) - normAxisZ * (v.x * normAxisX + v.y * normAxisY)
			* (1 - cos(degrees) + (v.x * normAxisY - v.y * normAxisX) * sin(degrees))), 0);

	mat4 rotMatrix{ column1, column2, column3, column4 };
	return rotMatrix;
}

float determinant(const mat4 m) {
	float deter =
		(m.matrix[0].x *
			(m.matrix[1].y * (m.matrix[2].z * m.matrix[3].w - m.matrix[2].w * m.matrix[3].z)
				- m.matrix[1].z * (m.matrix[2].y * m.matrix[3].w - m.matrix[2].w * m.matrix[3].y)
				+ m.matrix[1].w * (m.matrix[2].y * m.matrix[3].z - m.matrix[2].z * m.matrix[3].y))

			- m.matrix[0].y *
			(m.matrix[1].x * (m.matrix[2].z * m.matrix[3].w - m.matrix[2].w * m.matrix[3].z)
				- m.matrix[1].z * (m.matrix[2].x * m.matrix[3].w - m.matrix[2].w * m.matrix[3].x)
				+ m.matrix[1].w * (m.matrix[2].x * m.matrix[3].z - m.matrix[2].z * m.matrix[3].x))

			+ m.matrix[0].z *
			(m.matrix[1].x * (m.matrix[2].y * m.matrix[3].w - m.matrix[2].w * m.matrix[3].y)
				- m.matrix[1].y * (m.matrix[2].x * m.matrix[3].w - m.matrix[2].w * m.matrix[3].x)
				+ m.matrix[1].w * (m.matrix[2].x * m.matrix[3].y - m.matrix[2].y * m.matrix[3].x))

			- m.matrix[0].w *
			(m.matrix[1].x * (m.matrix[2].y * m.matrix[3].z - m.matrix[2].z * m.matrix[3].y)
				- m.matrix[1].y * (m.matrix[2].x * m.matrix[3].z - m.matrix[2].z * m.matrix[3].x)
				+ m.matrix[1].z * (m.matrix[2].x * m.matrix[3].y - m.matrix[2].y * m.matrix[3].x))

			);
	return deter;
}
mat4 transpose(const mat4& m) {
	mat4 temp;
	vec4 transpose;
	for (int i = 0; i < 4; i++) {

		for (int j = 0; j < 4; j++) {
			transpose.setElement(j, m.matrix[j].getElement(i));
		}
		temp[i] = transpose;
	}
	return temp;
}

mat4 inverse(const mat4& m) {
	float deter = determinant(m);
	mat4 temp;
	if (deter == 0) { 
		return temp;
	}
	temp[0].x = m.matrix[1].y * (m.matrix[2].z * m.matrix[3].w - m.matrix[2].w * m.matrix[3].z) //a corrected
		- m.matrix[1].z * (m.matrix[2].y * m.matrix[3].w - m.matrix[2].w * m.matrix[3].y)
		+ m.matrix[1].w * (m.matrix[2].y * m.matrix[3].z - m.matrix[2].z * m.matrix[3].y);
	temp[0].y = m.matrix[1].x * (m.matrix[2].z * m.matrix[3].w - m.matrix[2].w * m.matrix[3].z) //b corrected
		- m.matrix[1].z * (m.matrix[2].x * m.matrix[3].w - m.matrix[2].w * m.matrix[3].x)
		+ m.matrix[1].w * (m.matrix[2].x * m.matrix[3].z - m.matrix[2].z * m.matrix[3].x);
	temp[0].z = m.matrix[1].x * (m.matrix[2].y * m.matrix[3].w - m.matrix[2].w * m.matrix[3].y) //c corrected
		- m.matrix[1].y * (m.matrix[2].x * m.matrix[3].w - m.matrix[2].w * m.matrix[3].x)
		+ m.matrix[1].w * (m.matrix[2].x * m.matrix[3].y - m.matrix[2].y * m.matrix[3].x);
	temp[0].w = m.matrix[1].x * (m.matrix[2].y * m.matrix[3].z - m.matrix[2].z * m.matrix[3].y) //d corrected
		- m.matrix[1].y * (m.matrix[2].x * m.matrix[3].z - m.matrix[2].z * m.matrix[3].x)
		+ m.matrix[1].z * (m.matrix[2].x * m.matrix[3].y - m.matrix[2].y * m.matrix[3].x);
	temp[1].x = m.matrix[0].y * (m.matrix[2].z * m.matrix[3].w - m.matrix[2].w * m.matrix[3].z) //e corrected
		- m.matrix[0].z * (m.matrix[2].y * m.matrix[3].w - m.matrix[2].w * m.matrix[3].y)
		+ m.matrix[0].w * (m.matrix[2].y * m.matrix[3].z - m.matrix[2].z * m.matrix[3].y);
	temp[1].y = m.matrix[0].x * (m.matrix[2].z * m.matrix[3].w - m.matrix[2].w * m.matrix[3].z) //f corrected
		- m.matrix[0].z * (m.matrix[2].x * m.matrix[3].w - m.matrix[2].w * m.matrix[3].x)
		+ m.matrix[0].w * (m.matrix[2].x * m.matrix[3].z - m.matrix[2].z * m.matrix[3].x);
	temp[1].z = m.matrix[0].x * (m.matrix[2].y * m.matrix[3].w * m.matrix[2].w * m.matrix[3].y) //g corrected
		- m.matrix[0].y * (m.matrix[2].x * m.matrix[3].w - m.matrix[2].w * m.matrix[3].x)
		+ m.matrix[0].w * (m.matrix[2].x * m.matrix[3].y - m.matrix[2].y * m.matrix[3].x);
	temp[1].w = m.matrix[0].x * (m.matrix[2].y * m.matrix[3].z - m.matrix[2].z * m.matrix[3].y) //h corrected
		- m.matrix[0].y * (m.matrix[2].x * m.matrix[3].z - m.matrix[2].z * m.matrix[3].x)
		+ m.matrix[0].z * (m.matrix[2].x * m.matrix[3].y - m.matrix[2].y * m.matrix[3].x);
	temp[2].x = m.matrix[0].y * (m.matrix[1].z * m.matrix[3].w - m.matrix[1].w * m.matrix[3].z) //i corrected
		- m.matrix[0].z * (m.matrix[1].y * m.matrix[3].w - m.matrix[1].w * m.matrix[3].y)
		+ m.matrix[0].w * (m.matrix[1].y * m.matrix[3].z - m.matrix[1].z * m.matrix[3].y);
	temp[2].y = m.matrix[0].x * (m.matrix[1].z * m.matrix[3].w - m.matrix[1].w * m.matrix[3].z) //j
		- m.matrix[0].z * (m.matrix[1].x * m.matrix[3].w - m.matrix[1].w * m.matrix[3].x)
		+ m.matrix[0].w * (m.matrix[1].x * m.matrix[3].z - m.matrix[1].z * m.matrix[3].x);
	temp[2].z = m.matrix[0].x * (m.matrix[1].y * m.matrix[3].w - m.matrix[1].w * m.matrix[3].y) //k
		- m.matrix[0].y * (m.matrix[1].x * m.matrix[3].w - m.matrix[1].w * m.matrix[3].x)
		+ m.matrix[0].w * (m.matrix[1].x * m.matrix[3].y - m.matrix[1].y * m.matrix[3].x);
	temp[2].w = m.matrix[0].x * (m.matrix[1].y * m.matrix[3].z - m.matrix[1].z * m.matrix[3].y) //L
		- m.matrix[0].y * (m.matrix[1].x * m.matrix[3].z - m.matrix[1].z * m.matrix[3].x)
		+ m.matrix[0].z * (m.matrix[1].x * m.matrix[3].y - m.matrix[1].y * m.matrix[3].x);
	temp[3].x = m.matrix[0].y * (m.matrix[1].z * m.matrix[2].w - m.matrix[1].w * m.matrix[2].z) //m
		- m.matrix[0].z * (m.matrix[1].y * m.matrix[2].w - m.matrix[1].w * m.matrix[2].y)
		+ m.matrix[0].w * (m.matrix[1].y * m.matrix[2].z - m.matrix[1].z * m.matrix[2].y);
	temp[3].y = m.matrix[0].x * (m.matrix[1].z * m.matrix[2].w - m.matrix[1].w * m.matrix[2].z) //n
		- m.matrix[0].z * (m.matrix[1].x * m.matrix[2].w - m.matrix[1].w * m.matrix[2].x)
		+ m.matrix[0].w * (m.matrix[1].x * m.matrix[2].z - m.matrix[1].z * m.matrix[2].x);
	temp[3].z = m.matrix[3].z * (m.matrix[1].y * m.matrix[2].w - m.matrix[1].w * m.matrix[2].y) //o
		- m.matrix[0].y * (m.matrix[1].x * m.matrix[2].w - m.matrix[1].w * m.matrix[2].x)
		+ m.matrix[0].w * (m.matrix[1].x * m.matrix[2].y - m.matrix[1].y * m.matrix[2].x);
	temp[3].w = m.matrix[0].x * (m.matrix[1].y * m.matrix[2].z - m.matrix[1].z * m.matrix[2].y) //p corrected
		- m.matrix[0].y * (m.matrix[1].x * m.matrix[2].z - m.matrix[1].z * m.matrix[2].x)
		+ m.matrix[0].z * (m.matrix[1].x * m.matrix[2].y - m.matrix[1].y * m.matrix[2].x);

	//adjugate and then multiply the adjugate by (1/determinant) using original matrix
	temp = transpose(temp);
	for (int i = 0; i < 4; i++) {
		temp[i].x = (1 / deter) * temp[i].x;
		temp[i].y = (1 / deter) * temp[i].y;
		temp[i].z = (1 / deter) * temp[i].z;
		temp[i].w = (1 / deter) * temp[i].w;
	}
	return temp;
}

int printMatrix(const mat4& m) {
	for (int i = 0; i < 4; i++) {
		m.matrix[i].printVec4();
	}
	return 0;
}

