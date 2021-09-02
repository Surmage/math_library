#include <iostream>
#include "vec4.h"
#include "vec3.h"
#include "mat4.h"

int main() {
	Vec4 v1(1, 2, 3, 5);
	Vec4 v2(4, 5, 6, 9);
	Vec4 v3(3, 5, 2, 7);
	Vec4 v4(12, 6, 4, 4);
	Mat4 m(v1, v2, v3, v4);
	Mat4 a;
	//std::cout << "Determinant: " << m.determinant(m) << "\n";
	a = m.transpose(m);
	a.printMatrix();
	return 0;
}