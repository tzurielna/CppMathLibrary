#include "SMatrix.h"

namespace math {

	template <size_t M, class T>
	Matrix<M, M, T> pow(const Matrix<M, M, T>& matrix, size_t exp) {
		Matrix<M, M, T> result = IdentityMatrix<M, T>;
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
	Matrix<M, M, T> determinant(const Matrix<M, M, T>& matrix, size_t exp) {
		return IdentityMatrix<M, T>;  // TODO: FIX
	}

	template <size_t M, class T>
	RotateMatrix<M, T>::RotateMatrix(const T& angle) {
		// TODO: FIX
	}

	template <size_t M, class T>
	TranslationMatrix<M, T>::TranslationMatrix(const Vector<M, T>& vector) {
		// TODO: FIX
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
