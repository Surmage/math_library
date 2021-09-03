#pragma once
#include <iostream>
#include "vec4.h"
#include "vec3.h"
#include <array>


class Mat4 {
public:
	std::array<Vec4, 4> matrix;
	Mat4()
		:matrix({ Vec4{1, 0, 0, 0}, Vec4{0, 1, 0, 0}, Vec4{0, 0, 1, 0}, Vec4{0, 0, 0, 1 } })
	{
	}
	Mat4(const Vec4& r0, const Vec4& r1, const Vec4& r2, const Vec4& r3) 
		:matrix({r0, r1, r2, r3 })
	{
	}
	Mat4(const Mat4& m) 
	{
		for (unsigned int i = 0; i < 4; i++) {
			Vec4 temp{ m.matrix[i].x, m.matrix[i].y, m.matrix[i].z, m.matrix[i].w };
			matrix[i] = temp;
		}
	}

	Mat4 operator=(const Mat4& rhs) {
		for (int i = 0; i < 4; i++) {
			matrix[i].x = rhs.matrix[i].x;
			matrix[i].y = rhs.matrix[i].y;
			matrix[i].z = rhs.matrix[i].z;
			matrix[i].w = rhs.matrix[i].w;
		}			
		return *this;
	}
	Mat4 operator*(const Mat4& rhs) {
		Mat4 temp;
		for (int i = 0; i < 4; i++) {
			Vec4 transpose;
			for (int j = 0; j < 4; j++) {
				Vec4 tempVec = rhs.matrix[j];
				transpose.setElement(j, tempVec[i]);
			}
			for (int k = 0; k < 4; k++) {
				temp[k].setElement(i, matrix[k].dot(matrix[k], transpose));
			}
		}
		return temp;
	}
	bool operator==(const Mat4& rhs) {
		if (matrix[0] == rhs.matrix[0] && matrix[1] == rhs.matrix[1] && matrix[2] == rhs.matrix[2] && matrix[3] == rhs.matrix[3]) 
			return true;			
		else 
			return false;
	}
	bool operator!=(const Mat4& rhs) {
		if (matrix[0] != rhs.matrix[0] || matrix[1] != rhs.matrix[1] || matrix[2] != rhs.matrix[2] || matrix[3] != rhs.matrix[3])
			return true;
		else
			return false;
	} 
	Vec4& operator[](const unsigned int i) {
		if (i > 3)
			std::cerr << "Error\n";		
		else
			return matrix[i];
	}

	float determinant(const Mat4 m) {
		float deter = 
		(m.matrix[0].x * 
		(m.matrix[1].y * (m.matrix[2].z * m.matrix[3].w - m.matrix[2].w * m.matrix[3].z)
		-m.matrix[1].z * (m.matrix[2].y * m.matrix[3].w - m.matrix[2].w * m.matrix[3].y)
		+m.matrix[1].w * (m.matrix[2].y * m.matrix[3].z - m.matrix[2].z * m.matrix[3].y)) 
			
		-m.matrix[0].y *
		(m.matrix[1].x * (m.matrix[2].z * m.matrix[3].w - m.matrix[2].w * m.matrix[3].z)
		-m.matrix[1].z * (m.matrix[2].x * m.matrix[3].w - m.matrix[2].w * m.matrix[3].x)
		+m.matrix[1].w * (m.matrix[2].x * m.matrix[3].z - m.matrix[2].z * m.matrix[3].x)) 

		+m.matrix[0].z *
		(m.matrix[1].x*(m.matrix[2].y * m.matrix[3].w - m.matrix[2].w * m.matrix[3].y)
		-m.matrix[1].y*(m.matrix[2].x * m.matrix[3].w - m.matrix[2].w * m.matrix[3].x)
		+m.matrix[1].w*(m.matrix[2].x * m.matrix[3].y - m.matrix[2].y * m.matrix[3].x)) 

		-m.matrix[0].w * 
		(m.matrix[1].x * (m.matrix[2].y * m.matrix[3].z - m.matrix[2].z * m.matrix[3].y)
		-m.matrix[1].y * (m.matrix[2].x * m.matrix[3].z - m.matrix[2].z * m.matrix[3].x)
		+m.matrix[1].z * (m.matrix[2].x * m.matrix[3].y - m.matrix[2].y * m.matrix[3].x)) 
				
		); 
			
		return deter;
	}
		
	Mat4 inverse(const Mat4& m) {
		Mat4 temp;
		temp[0].x = m.matrix[1].y * (m.matrix[2].z * m.matrix[3].w - m.matrix[2].w * m.matrix[3].z) //a
			- m.matrix[1].z * (m.matrix[2].y * m.matrix[3].w - m.matrix[2].w * m.matrix[3].y)
			+ m.matrix[1].w * (m.matrix[2].y * m.matrix[3].z - m.matrix[2].z * m.matrix[3].x);
		temp[0].y = m.matrix[1].x * (m.matrix[2].z * m.matrix[3].w - m.matrix[2].w * m.matrix[3].z) //b
			- m.matrix[1].z * (m.matrix[2].x * m.matrix[3].w - m.matrix[2].w * m.matrix[3].x)
			+ m.matrix[1].w * (m.matrix[2].x * m.matrix[3].z - m.matrix[2].z * m.matrix[3].x);
		temp[0].z = m.matrix[1].x * (m.matrix[2].y * m.matrix[3].w - m.matrix[2].w * m.matrix[3].y) //c
			- m.matrix[1].y * (m.matrix[2].x * m.matrix[3].w - m.matrix[2].w * m.matrix[3].x)
			+ m.matrix[1].w * (m.matrix[2].x * m.matrix[3].y - m.matrix[2].y * m.matrix[3].x);
		temp[0].w = m.matrix[1].x * (m.matrix[2].y * m.matrix[3].z - m.matrix[2].z * m.matrix[3].y) //d
			- m.matrix[1].y * (m.matrix[2].x * m.matrix[3].z - m.matrix[2].z * m.matrix[3].x)
			+ m.matrix[1].z * (m.matrix[2].x * m.matrix[3].y - m.matrix[2].y * m.matrix[3].x);
		temp[1].x = m.matrix[0].y * (m.matrix[2].z * m.matrix[3].w - m.matrix[2].w * m.matrix[3].z) //e
			- m.matrix[0].z * (m.matrix[2].y * m.matrix[3].w - m.matrix[2].w * m.matrix[3].y)
			+ m.matrix[0].w * (m.matrix[2].y * m.matrix[3].z - m.matrix[2].z * m.matrix[3].y);
		temp[1].y = m.matrix[0].x * (m.matrix[2].z * m.matrix[3].w - m.matrix[2].w * m.matrix[3].z) //f
			- m.matrix[0].z * (m.matrix[2].x * m.matrix[3].w - m.matrix[2].w * m.matrix[3].x)
			+ m.matrix[0].w * (m.matrix[2].x * m.matrix[3].z - m.matrix[2].z * m.matrix[3].x);
		temp[1].z = m.matrix[0].x * (m.matrix[2].y * m.matrix[3].w * m.matrix[2].w * m.matrix[3].y) //g
			- m.matrix[0].y * (m.matrix[2].x * m.matrix[3].w - m.matrix[2].w * m.matrix[3].x)
			+ m.matrix[9].w * (m.matrix[2].x * m.matrix[3].y - m.matrix[2].y * m.matrix[3].x);
		temp[1].w = m.matrix[0].x * (m.matrix[2].y * m.matrix[3].z - m.matrix[2].z * m.matrix[3].y) //h
			- m.matrix[0].y * (m.matrix[2].x * m.matrix[3].z - m.matrix[2].z * m.matrix[3].x)
			+ m.matrix[0].z * (m.matrix[2].x * m.matrix[3].y - m.matrix[2].y * m.matrix[3].x);

	}
	Mat4 transpose(const Mat4& m) { 
		Mat4 temp;
		Vec4 transpose;
		for (int i = 0; i < 4; i++) {
			
			for (int j = 0; j < 4; j++) {
				transpose.setElement(j, m.matrix[j].getElement(i)); 
			}
			temp[i] = transpose; 
		}
		return temp;
	}
	int printMatrix() {
		for (int i = 0; i < 4; i++) {
			matrix[i].printVec4();
		}
		return 0;
	}
	Mat4 rotationx(const float rad) {

	}
	Mat4 rotationy(const float rad) {

	}
	Mat4 rotationz(const float rad) {

	}
	Mat4 rotationaxis(const Vec3 v, const float rad) {

	}
	Mat4 perspective() {

	}
	Mat4 lookat() {

	}
};
