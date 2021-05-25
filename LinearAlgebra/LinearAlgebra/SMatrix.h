#pragma once

#include "Matrix.h"

namespace math {

	template <size_t M, class T = float>
	using SMatrix = Matrix<M, M, T>;

	template <size_t M, class T = float>
	SMatrix<M, T> pow(const SMatrix<M, T>& matrix, size_t exp);

	template <size_t M, class T = float>
	T& trace(const SMatrix<M, T>& matrix);

	template <size_t M, class T = float>
	SMatrix<M, T> determinant(const SMatrix<M, T>& matrix, size_t exp);

	template <size_t M, class T = float>
	class RotateMatrix : public SMatrix {
		RotateMatrix(const T& angle);
	};

	template <size_t M, class T = float>
	class TranslationMatrix : public SMatrix {
		TranslationMatrix(const Vector<M, T>& vector);
	};

	template <size_t M, class T = float>
	class ScaleMatrix : public SMatrix {
		ScaleMatrix(const T& scalar);
	};

	template <size_t M, class T = float>
	class DiagnolMatrix : public SMatrix {
		DiagnolMatrix(const Vector<M, T>& vector);
	};

	template <size_t M, class T = float>
	const SMatrix<M, T> IdentityMatrix;

}
