#pragma once
#include <iostream>

namespace Math {

	class Vec3 {
	public:
		float x;
		float y;
		float z;

		Vec3() {
			x = 0;
			y = 0;
			z = 0;
		}
		Vec3(const float nx, const float ny, const float nz) {
			x = nx;
			y = ny;
			z = nz;
		}
		Vec3(const Vec3& v) { //copy constructor
			x = v.x;
			y = v.y;
			z = v.z;
		}

		Vec3 operator=(const Vec3& v) {

		}
		Vec3 operator-() {

		}
		Vec3 operator+(const Vec3& v) {

		}
		void operator+=(const Vec3& v) {

		}
		Vec3 operator-(const Vec3& v) {

		}
		void operator-=(const Vec3& v) {

		}
		void operator*=(const float v) {

		}
		Vec3 operator*(const float v) {

		}
		bool operator==(const Vec3& v) {
			if ((x == v.x) && (y == v.y) && (z = v.z))
				return true;
			else
				return false;
		}
		bool operator!=(const Vec3& v) {

		}
		float operator[](const unsigned int i) {

		}

		float dot(const Vec3& a, const Vec3& b) {
			return a.x * b.x + a.y * b.y + a.z * b.z;
		}
		float length(const Vec3& v) {			
			return sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
		}
		Vec3 cross(const Vec3& a, const Vec3& b) {
			Vec3 crossVec;
			crossVec.x = a.y * b.z - a.z * a.y;
			crossVec.y = -(a.x * b.z - a.z * b.x);
			crossVec.z = a.x * b.y - a.y * b.x;
			return crossVec;
		}
		Vec3 normalize(const Vec3& v) { //convert to unit vector
			float vecLen = length(v);
			Vec3 newVec;
			newVec.x = v.x / vecLen;
			newVec.y = v.y / vecLen;
			newVec.z = v.z / vecLen;
			return newVec;
		}		
	};


}