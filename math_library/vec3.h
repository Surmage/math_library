#pragma once
#include <cmath>

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
		Vec3 cross(const Vec3& a, const Vec3& b, const Vec3& c) {

		}
		Vec3 normalize(const Vec3& v) {

		}
		
	};


}