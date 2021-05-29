#pragma once

#include <initializer_list>
#include <iostream>
#include <vector>

#include "Vector.h"

namespace math {

	template <size_t M, size_t N = M, class T = float>
	class Matrix {
	public:
		Matrix(const T& value = 0);
		Matrix(const T values[M * N]);
		Matrix(const std::initializer_list<std::initializer_list<T>>& list);

		T* data();
		const T* data() const;

		T& operator()(size_t i, size_t j);
		const T& operator()(size_t i, size_t j) const;

		Matrix operator+(const Matrix& other) const;
		Matrix& operator+=(const Matrix& other);

		Matrix operator-(const Matrix& other) const;
		Matrix& operator-=(const Matrix& other);

		Matrix operator-() const;
		Matrix<N, M, T> operator!() const;

		Matrix operator*(const T& scalar) const;
		Matrix& operator*=(const T& scalar);

		Matrix operator/(const T& scalar) const;
		Matrix& operator/=(const T& scalar);

		template <size_t K>
		Matrix<M, K, T> operator*(const Matrix<N, K, T>& other) const;
		template <size_t K>
		Matrix<M, K, T>& operator*=(const Matrix<N, K, T>& other);

		Matrix& normalize(size_t order = 2);
		Matrix normalized(size_t order = 2) const;

	private:
		T m_values[M * N];
	};

	template <size_t M, size_t N, class T = float>
	Matrix<M, N, T> operator*(const T& scalar, const Matrix<M, N, T>& matrix);

	template <size_t M, size_t N, class T = float>
	std::ostream& operator<<(std::ostream& os, const Matrix<M, N, T>& matrix);

	template <size_t M, size_t N, class T = float>
	std::istream& operator>>(std::istream& is, const Matrix<M, N, T>& matrix);

	template <size_t M, size_t N, class T = float>
	std::vector<size_t> dimension(const Matrix<M, N, T>& matrix);

	template <size_t M, size_t N, class T = float>
	T norm(const Matrix<M, N, T>& matrix, size_t order = 2);

	template <size_t M, size_t N, class T = float>
	T distance(const Matrix<M, N, T>& lhs, const Matrix<M, N, T>& rhs, size_t order = 2);

}

#include "Matrix.inl"

