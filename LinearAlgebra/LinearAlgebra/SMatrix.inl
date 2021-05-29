#include "SMatrix.h"

#include <cmath>

namespace math {

	template <size_t M, class T>
	Matrix<M, M, T> pow(const Matrix<M, M, T>& matrix, size_t exp) {
		Matrix<M, M, T> result = IDENTITY_MATRIX<M, T>;
		for (size_t i = 0; i < exp; i++) {
			result *= matrix;
		}
		return result;
	}

	template <size_t M, class T>
	T trace(const Matrix<M, M, T>& matrix) {
		T result = T(0.0);
		for (size_t i = 0; i < M; i++) {
			result += matrix(i, i);
		}
		return result;
	}

	template <size_t M, class T>
	T determinant(const Matrix<M, M, T>& matrix, size_t exp) {
		return T(0.0f);  // TODO: implement this function
	}

	template <class T>
	RotationMatrix<T>::RotationMatrix(const T& angle) {
		(*this)(0, 0) = std::cos(double(angle));
		(*this)(0, 1) = -std::sin(double(angle));
		(*this)(1, 0) = std::sin(double(angle));
		(*this)(1, 1) = std::cos(double(angle));
	}

	template <size_t M, class T>
	TranslationMatrix<M, T>::TranslationMatrix(const Vector<M, T>& vector) {
		for (size_t i = 0; i <= M; i++) {
			(*this)(i, i) = 1;
		}
		for (size_t i = 0; i < M; i++) {
			(*this)(i, M) = vector(i);
		}
	}

	template <size_t M, class T>
	ScaleMatrix<M, T>::ScaleMatrix(const T& scalar) {
		for (size_t i = 0; i < M; i++) {
			(*this)(i, i) = scalar;
		}
	}

	template <size_t M, class T>
	DiagnolMatrix<M, T>::DiagnolMatrix(const Vector<M, T>& vector) {
		for (size_t i = 0; i < M; i++) {
			(*this)(i, i) = vector(i);
		}
	}

}
