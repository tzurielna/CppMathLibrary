#pragma once

#include <iostream>

namespace math {

	template <size_t M, size_t N = M, class T = float>
	class Matrix {
	public:
		Matrix(const T& value = 0);
		Matrix(const T values[M * N]);

		T* data();
		const T* data() const;

		T& operator[](size_t i, site_t j);
		const T& operator[](size_t i, size_t j) const;

		Matrix operator+(const Matrix& other) const;
		Matrix& operator+=(const Matrix& other);

		Matrix operator-(const Matrix& other) const;
		Matrix& operator-=(const Matrix& other);

		Matrix operator-() const;

		Matrix operator*(const T& scalar) const;
		Matrix& operator*=(const T& scalar);

		Matrix operator/(const T& scalar) const;
		Matrix& operator/=(const T& scalar);

		T operator*(const Matrix& other) const;

		Matrix& normalize(size_t order = 2);
		Matrix normalized(size_t order = 2) const;

	private:
		T m_values[DIM];
	};

	template <size_t M, size_t N = M, class T = float>
	Matrix<M, N, T>& operator*(const T& scalar, const Matrix<M, N, T>& vector);

	template <size_t M, size_t N = M, class T = float>
	std::ostream& operator<<(std::ostream& os, const Matrix<M, N, T>& vector);

	template <size_t M, size_t N = M, class T = float>
	std::istream& operator>>(std::istream& is, const Matrix<M, N, T>& vector);

	template <size_t M, size_t N = M, class T = float>
	size_t dimension(const Matrix<M, N, T>& vector);

	template <size_t M, size_t N = M, class T = float>
	T norm(const Matrix<M, N, T>& vector, size_t order = 2);

	template <size_t M, size_t N = M, class T = float>
	T distance(const Matrix<M, N, T>& lhs, const Matrix<M, N, T>& rhs, size_t order = 2);
}

