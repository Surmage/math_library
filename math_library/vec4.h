#pragma once
#include <iostream>

namespace Math {

	class Vec4 {
	public:
		float x;
		float y;
		float z;
		float w;

		Vec4() {
			x = 0;
			y = 0;
			z = 0;
			w = 0;
		}
		Vec4(const float nx, const float ny, const float nz, const float nw) {
			x = nx;
			y = ny;
			z = nz;
			w = nw;
		}
		Vec4(const Vec4& v) {
			x = v.x;
			y = v.y;
			z = v.z;
			w = v.w;
		}

		Vec4 operator=(const Vec4& v) {
			Vec4 newVec(v.x, v.y, v.z, v.w);
			return newVec;
		}
		Vec4 operator-() {
			Vec4 newVec(-x, -y, -z, -w);
			return newVec;
		}
		Vec4 operator+(const Vec4& v) {
			Vec4 newVec(x + v.x, y + v.y, z + v.z, w + v.w);
			return newVec;
		}
		void operator+=(const Vec4& v) {
			x += v.x;
			y += v.y;
			z += v.z;
			w += v.w;
		}
		Vec4 operator-(const Vec4& v) {
			Vec4 newVec(x - v.x, y - v.y, z - v.z, w - v.w);
			return newVec;
		}
		void operator-=(const Vec4& v) {
			x -= v.x;
			y -= v.y;
			z -= v.z;
			w -= v.w;
		}
		void operator*=(const float v) {
			x *= v;
			y *= v;
			z *= v;
			w *= v;
		}
		Vec4 operator*(const float v) {
			Vec4 newVec(x * v, y * v, z * v, w * v);
			return newVec;
		}
		bool operator==(const Vec4& v) {
			if ((x == v.x) && (y == v.y) && (z == v.z) && (w == v.w))
				return true;
			else
				return false;
		}
		bool operator!=(const Vec4& v) {
			if ((x != v.x) || (y != v.y) || (z != v.z) || (w != v.w))
				return true;
			else
				return false;
		}
		float operator[](const unsigned int i) {
			if (i > 3) {
				std::cerr << "Error\n";
			}
			else {
				if (i == 0) {
					return x;
				}
				else if (i == 1) {
					return y;
				}
				else if (i == 2) {
					return z;
				}
				else if (i == 3) {
					return w;
				}
			}
			return -1;
		}

		float dot(const Vec4& a, const Vec4& b) {
			return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
		}
		float length(const Vec4& v) {
			return sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2) + pow(v.w, 2));
		}
		Vec4 normalize(const Vec4& v) { //convert to unit vector
			float vecLen = length(v);
			Vec4 newVec;
			newVec.x = v.x / vecLen;
			newVec.y = v.y / vecLen;
			newVec.z = v.z / vecLen;
			newVec.w = v.w / vecLen;
			return newVec;
		}
	};
}