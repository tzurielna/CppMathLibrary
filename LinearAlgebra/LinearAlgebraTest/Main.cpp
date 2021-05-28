#include "Vector.h"
#include "Matrix.h"

int main() {

	// Vector Test

	math::Vector<3> vector1 = { 1.0f, 2.0f, 3.0f };
	math::Vector<3> vector2 = { 1.5f, -2.5f, 0.0f };
	math::Vector<3> vector3;
	std::cout << vector1 << " " << vector2 << " " << vector3 << std::endl;
	std::cout << (vector1 + vector2) << " " << (vector1 - vector2) << " " << (-vector1) << std::endl;
	std::cout << vector1 * vector2 << " " << vector1 % vector2 << std::endl;
	std::cout << vector1 * 2.5f << " " << vector1 / 2.5f << std::endl;
	std::cout << dimension(vector1) << " " << norm(vector1) << " " << distance(vector1, vector2) << std::endl;
	std::cout << vector1.normalized(0) << std::endl;

	// Matrix Test

	math::Matrix<2> matrix1 = { { 1.0f, 2.0f } , { 3.0f, 4.0f } };
	math::Matrix<2> matrix2 = { { 0.5f, -0.5f } , { 1.0f, 0.0f } };
	math::Matrix<2> matrix3;
	std::cout << matrix1 << matrix2 << matrix3 << std::endl;
	std::cout << (matrix1 + matrix2) << (matrix1 - matrix2) << (-matrix1) << std::endl;
	std::cout << matrix1 * matrix2 << std::endl;
	std::cout << matrix1 * 2.5f << matrix1 / 2.5f << std::endl;
	std::cout << dimension(matrix1)[0] << " " << dimension(matrix1)[1] << " " << norm(matrix1) << " " << distance(matrix1, matrix2) << std::endl;
	std::cout << matrix1.normalized(0) << std::endl;

}
