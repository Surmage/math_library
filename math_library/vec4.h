#pragma once
#include <iostream>

class vec4 {
public:
	float x;
	float y;
	float z;
	float w;

	vec4() {
		x = 0;
		y = 0;
		z = 0;
		w = 0;
	}
	vec4(const float nx, const float ny, const float nz, const float nw) {
		x = nx;
		y = ny;
		z = nz;
		w = nw;
	}
	vec4(const vec4& v) {
		x = v.x;
		y = v.y;
		z = v.z;
		w = v.w;
	}

	vec4 operator=(const vec4& v) { 
		x = v.x;
		y = v.y;
		z = v.z;
		w = v.w;
		return *this;
	}
	vec4 operator-() {
		vec4 newVec(-x, -y, -z, -w);
		return newVec;
	}
	vec4 operator+(const vec4& v) {
		vec4 newVec(x + v.x, y + v.y, z + v.z, w + v.w);
		return newVec;
	}
	void operator+=(const vec4& v) {
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;
	}
	vec4 operator-(const vec4& v) {
		vec4 newVec(x - v.x, y - v.y, z - v.z, w - v.w);
		return newVec;
	}
	void operator-=(const vec4& v) {
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
	vec4 operator*(const float scalar) {
		vec4 newVec(x * scalar, y * scalar, z * scalar, w * scalar);
		return newVec;
	}
	bool operator==(const vec4& v) {
		if ((x == v.x) && (y == v.y) && (z == v.z) && (w == v.w))
			return true;
		else
			return false;
	}

	bool operator!=(const vec4& v) {
		if ((x != v.x) || (y != v.y) || (z != v.z) || (w != v.w))
			return true;
		else
			return false;
	}
	float& operator[](unsigned int i) {
		float returnValue;
		if (i > 3) {
			std::cerr << "Error\n";		
			returnValue = -1;
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
		return returnValue;
	}
	const float operator[](const unsigned int i) const{
		float returnValue = -1;
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
		return returnValue;
	}

	
	float setElement(const unsigned int i, const float value) {
		if (i > 3) {
			std::cerr << "Error\n";
			return -1;
		}

		if (i == 0)
			x = value;
		else if (i == 1)
			y = value;
		else if (i == 2)
			z = value;
		else if (i == 3)
			w = value;
		return 0;
	}
	float getElement(const unsigned int i)const {
		if (i > 3) {
			std::cerr << "Error\n";
			return -1;
		}

		if (i == 0)
			return x;
		else if (i == 1)
			return y;
		else if (i == 2)
			return z;
		else if (i == 3)
			return w;
		return 0;
	}
	int printVec4()const {
		std::cout << x << ", " << y << ", " << z << ", " << w << "\n";
		return 0;
	}
};

float dot(const vec4& a, const vec4& b) {
	return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}
float length(const vec4& v) {
	return sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
}
vec4 normalize(const vec4& v) { //convert to unit vector
	float vecLen = length(v);
	vec4 newVec;
	newVec.x = v.x / vecLen;
	newVec.y = v.y / vecLen;
	newVec.z = v.z / vecLen;
	newVec.w = v.w;
	return newVec;
}