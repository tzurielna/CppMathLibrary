#include "Matrix.h"

#include <cmath>
#include <numeric>

#include "Exception.h"

namespace math {

	using std::abs;
	using std::fmax;
	using std::pow;

	template <size_t M, size_t N, class T>
	Matrix<M, N, T>::Matrix(const T& value) {
		for (size_t i = 0; i < M * N; i++) {
			m_values[i] = value;
		}
	}

	template <size_t M, size_t N, class T>
	Matrix<M, N, T>::Matrix(const T values[M * N]) {
		for (size_t i = 0; i < M * N; i++) {
			m_values[i] = values[i];
		}
	}

	template <size_t M, size_t N, class T>
	Matrix<M, N, T>::Matrix(const std::initializer_list<std::initializer_list<T>>& list) {
		auto it1 = list.begin();
		for (size_t i = 0; i < M; i++) {
			auto it2 = it1->begin();
			for (size_t j = 0; j < N; j++) {
				(*this)(i, j) = *it2;
				it2++;
			}
			it1++;
		}
	}

	template <size_t M, size_t N, class T>
	T* Matrix<M, N, T>::data() {
		return m_values;
	}

	template <size_t M, size_t N, class T>
	const T* Matrix<M, N, T>::data() const {
		return m_values;
	}

	template <size_t M, size_t N, class T>
	T& Matrix<M, N, T>::operator()(size_t i, size_t j) {
		if (i >= M) {
			throw OutOfRangeException<size_t>(0, M - 1, i);
		}
		if (j >= N) {
			throw OutOfRangeException<size_t>(0, N - 1, j);
		}
		return m_values[i * N + j];
	}

	template <size_t M, size_t N, class T>
	const T& Matrix<M, N, T>::operator()(size_t i, size_t j) const {
		if (i >= M) {
			throw OutOfRangeException<size_t>(0, M - 1, i);
		}
		if (j >= N) {
			throw OutOfRangeException<size_t>(0, N - 1, j);
		}
		return m_values[i * N + j];
	}

	template <size_t M, size_t N, class T>
	Matrix<M, N, T> Matrix<M, N, T>::operator+(const Matrix& other) const {
		Matrix<N, M, T> result;
		for (size_t i = 0; i < M; i++) {
			for (size_t j = 0; j < N; j++) {
				result(i, j) = (*this)(i, j) + other(i, j);
			}
		}
		return result;
	}

	template <size_t M, size_t N, class T>
	Matrix<M, N, T>& Matrix<M, N, T>::operator+=(const Matrix& other) {
		*this = *this + other;
		return *this;
	}

	template <size_t M, size_t N, class T>
	Matrix<M, N, T> Matrix<M, N, T>::operator-(const Matrix& other) const {
		Matrix<N, M, T> result;
		for (size_t i = 0; i < M; i++) {
			for (size_t j = 0; j < N; j++) {
				result(i, j) = (*this)(i, j) - other(i, j);
			}
		}
		return result;
	}

	template <size_t M, size_t N, class T>
	Matrix<M, N, T>& Matrix<M, N, T>::operator-=(const Matrix& other) {
		*this = *this - other;
		return *this;
	}

	template <size_t M, size_t N, class T>
	Matrix<M, N, T> Matrix<M, N, T>::operator-() const {
		Matrix<N, M, T> result;
		for (size_t i = 0; i < M; i++) {
			for (size_t j = 0; j < N; j++) {
				result(i, j) = -(*this)(i, j);
			}
		}
		return result;
	}

	template <size_t M, size_t N, class T>
	Matrix<N, M, T> Matrix<M, N, T>::operator!() const {
		Matrix<N, M, T> result;
		for (size_t i = 0; i < M; i++) {
			for (size_t j = 0; j < N; j++) {
				result(i, j) = (*this)(i, j);
			}
		}
		return result;
	}

	template <size_t M, size_t N, class T>
	Matrix<M, N, T> Matrix<M, N, T>::operator*(const T& scalar) const {
		Matrix<N, M, T> result;
		for (size_t i = 0; i < M; i++) {
			for (size_t j = 0; j < N; j++) {
				result(i, j) = (*this)(i, j) * scalar;
			}
		}
		return result;
	}

	template <size_t M, size_t N, class T>
	Matrix<M, N, T>& Matrix<M, N, T>::operator*=(const T& scalar) {
		*this = *this * scalar;
		return *this;
	}

	template <size_t M, size_t N, class T>
	Matrix<M, N, T> Matrix<M, N, T>::operator/(const T& scalar) const {
		Matrix<N, M, T> result;
		for (size_t i = 0; i < M; i++) {
			for (size_t j = 0; j < N; j++) {
				result(i, j) = (*this)(i, j) / scalar;
			}
		}
		return result;
	}

	template <size_t M, size_t N, class T>
	Matrix<M, N, T>& Matrix<M, N, T>::operator/=(const T& scalar) {
		*this = *this / scalar;
		return *this;
	}

	template <size_t M, size_t N, class T>
	template <size_t K>
	Matrix<M, K, T> Matrix<M, N, T>::operator*(const Matrix<N, K, T>& other) const {
		Matrix<M, K, T> result;
		for (size_t i = 0; i < M; i++) {
			for (size_t j = 0; j < K; j++) {
				for (size_t k = 0; k < N; k++) {
					result(i, j) += (*this)(i, k) * other(k, j);
				}
			}
		}
		return result;
	}

	template <size_t M, size_t N, class T>
	template <size_t K>
	Matrix<M, K, T>& Matrix<M, N, T>::operator*=(const Matrix<N, K, T>& other) {
		*this = *this * other;
		return *this;
	}

	template <size_t M, size_t N, class T>
	Matrix<M, N, T>& Matrix<M, N, T>::normalize(size_t order) {
		*this /= norm(*this, order);
		return *this;
	}

	template <size_t M, size_t N, class T>
	Matrix<M, N, T> Matrix<M, N, T>::normalized(size_t order) const {
		return *this / norm(*this, order);
	}

	template <size_t M, size_t N, class T>
	Matrix<M, N, T> operator*(const T& scalar, const Matrix<M, N, T>& matrix) {
		return matrix * scalar;
	}

	template <size_t M, size_t N, class T>
	std::ostream& operator<<(std::ostream& os, const Matrix<M, N, T>& matrix) {
		for (size_t i = 0; i < M; i++) {
			os << "[ ";
			for (size_t j = 0; j < N; j++) {
				os << matrix(i, j) << " ";
			}
			os << "]" << std::endl;
		}
		return os;
	}

	template <size_t M, size_t N, class T>
	std::istream& operator>>(std::istream& is, const Matrix<M, N, T>& matrix) {
		for (size_t i = 0; i < M; i++) {
			for (size_t j = 0; j < N; j++) {
				is >> matrix(i, j);
			}
		}
		return is;
	}

	template <size_t M, size_t N, class T>
	std::vector<size_t> dimension(const Matrix<M, N, T>& matrix) {
		std::vector<size_t> dim = { M, N };
		return dim;
	}

	template <size_t M, size_t N, class T>
	T norm(const Matrix<M, N, T>& matrix, size_t order) {
		if (order > 0) {
			T result(0.0f);
			for (size_t i = 0; i < M; i++) {
				for (size_t j = 0; j < N; j++) {
					result += T(pow(abs(matrix(i, j)), order));
				}
			}
			return T(pow(double(result), 1.0 / order));
		}
		else {
			T result = matrix(0, 0);
			for (size_t i = 0; i < M; i++) {
				for (size_t j = 0; j < N; j++) {
					result = fmax(result, abs(matrix(i, j)));
				}
			}
			return result;
		}
	}

	template <size_t M, size_t N, class T>
	T distance(const Matrix<M, N, T>& lhs, const Matrix<M, N, T>& rhs, size_t order) {
		return norm(lhs - rhs, order);
	}

}
