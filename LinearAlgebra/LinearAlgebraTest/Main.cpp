#include "Vector.h"

int main() {

	// Vector Test

	auto vector1 = math::get_vector(1.0f, 2.0f, 3.0f);
	auto vector2 = math::get_vector(1.5f, -2.5f, 0.0f);
	auto vector3 = math::Vector<3>();
	std::cout << vector1 << ' ' << vector2 << ' ' << vector3 << std::endl;
	std::cout << (vector1 + vector2) << ' ' << (vector1 - vector2) << ' ' << (-vector1) << std::endl;
	std::cout << vector1 * vector2 << ' ' << vector1 % vector2 << std::endl;
	std::cout << vector1 * 2.5f << ' ' << vector1 / 2.5f << std::endl;
	std::cout << dimension(vector1) << ' ' << norm(vector1) << ' ' << distance(vector1, vector2) << std::endl;
	std::cout << vector1.normalized(0) << std::endl;

	// Matrix Test


}
