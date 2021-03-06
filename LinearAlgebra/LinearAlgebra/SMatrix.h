#pragma once

#include "Matrix.h"

namespace math {

	template <size_t M, class T = float>
	Matrix<M, M, T> pow(const Matrix<M, M, T>& matrix, size_t exp);

	template <size_t M, class T = float>
	T trace(const Matrix<M, M, T>& matrix);

	template <size_t M, class T = float>
	T determinant(const Matrix<M, M, T>& matrix, size_t exp);

	template <class T = float>
	class RotationMatrix : public Matrix<2, 2, T> {
	public:
		RotationMatrix(const T& angle);
	};

	template <size_t M, class T = float>
	class TranslationMatrix : public Matrix<M + 1, M + 1, T> {
	public:
		TranslationMatrix(const Vector<M, T>& vector);
	};

	template <size_t M, class T = float>
	class ScaleMatrix : public Matrix<M, M, T> {
	public:
		ScaleMatrix(const T& scalar);
	};

	template <size_t M, class T = float>
	class DiagnolMatrix : public Matrix<M, M, T> {
	public:
		DiagnolMatrix(const Vector<M, T>& vector);
	};

	template <size_t M, class T = float>
	const Matrix<M, M, T> IDENTITY_MATRIX = DiagnolMatrix<M, T>(Vector<M, T>(1.0f));

}

#include "SMatrix.inl"

