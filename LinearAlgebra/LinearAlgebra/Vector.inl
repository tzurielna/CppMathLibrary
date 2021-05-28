#include "Vector.h"

#include <cmath>
#include <numeric>

#include "Exception.h"

namespace math {

	using std::abs;
	using std::fmax;
	using std::pow;

	template <size_t DIM, class T>
	Vector<DIM, T>::Vector(const T& value) {
		for (size_t i = 0; i < DIM; i++) {
			m_values[i] = value;
		}
	}

	template <size_t DIM, class T>
	Vector<DIM, T>::Vector(const T values[DIM]) {
		for (size_t i = 0; i < DIM; i++) {
			m_values[i] = values[i];
		}
	}

	template <size_t DIM, class T>
	T* Vector<DIM, T>::data() {
		return m_values;
	}

	template <size_t DIM, class T>
	const T* Vector<DIM, T>::data() const {
		return m_values;
	}

	template <size_t DIM, class T>
	T& Vector<DIM, T>::operator[](size_t index) {
		if (index >= DIM) {
			throw OutOfRangeException<size_t>(0, DIM - 1, index);
		}
		return m_values[index];
	}

	template <size_t DIM, class T>
	const T& Vector<DIM, T>::operator[](size_t index) const {
		if (index >= DIM) {
			throw OutOfRangeException<size_t>(0, DIM - 1, index);
		}
		return m_values[index];
	}

	template <size_t DIM, class T>
	Vector<DIM, T> Vector<DIM, T>::operator+(const Vector& other) const {
		Vector<DIM, T> result;
		for (size_t i = 0; i < DIM; i++) {
			result[i] = (*this)[i] + other[i];
		}
		return result;
	}

	template <size_t DIM, class T>
	Vector<DIM, T>& Vector<DIM, T>::operator+=(const Vector& other) {
		for (size_t i = 0; i < DIM; i++) {
			(*this)[i] += other[i];
		}
		return *this;
	}

	template <size_t DIM, class T>
	Vector<DIM, T> Vector<DIM, T>::operator-(const Vector& other) const {
		Vector<DIM, T> result;
		for (size_t i = 0; i < DIM; i++) {
			result[i] = (*this)[i] - other[i];
		}
		return result;
	}

	template <size_t DIM, class T>
	Vector<DIM, T>& Vector<DIM, T>::operator-=(const Vector& other) {
		for (size_t i = 0; i < DIM; i++) {
			(*this)[i] -= other[i];
		}
		return *this;
	}

	template <size_t DIM, class T>
	Vector<DIM, T> Vector<DIM, T>::operator-() const {
		Vector<DIM, T> result;
		for (size_t i = 0; i < DIM; i++) {
			result[i] = -(*this)[i];
		}
		return result;
	}

	template <size_t DIM, class T>
	Vector<DIM, T> Vector<DIM, T>::operator*(const T& scalar) const {
		Vector<DIM, T> result;
		for (size_t i = 0; i < DIM; i++) {
			result[i] = (*this)[i] * scalar;
		}
		return result;
	}

	template <size_t DIM, class T>
	Vector<DIM, T>& Vector<DIM, T>::operator*=(const T& scalar) {
		for (size_t i = 0; i < DIM; i++) {
			(*this)[i] *= scalar;
		}
		return *this;
	}

	template <size_t DIM, class T>
	Vector<DIM, T> Vector<DIM, T>::operator/(const T& scalar) const {
		if (!scalar) {
			throw DivisionByZeroException<T>();
		}
		Vector<DIM, T> result;
		for (size_t i = 0; i < DIM; i++) {
			result[i] = (*this)[i] / scalar;
		}
		return result;
	}

	template <size_t DIM, class T>
	Vector<DIM, T>& Vector<DIM, T>::operator/=(const T& scalar) {
		if (!scalar) {
			throw DivisionByZeroException<T>();
		}
		for (size_t i = 0; i < DIM; i++) {
			(*this)[i] /= scalar;
		}
		return *this;
	}

	template <size_t DIM, class T>
	T Vector<DIM, T>::operator*(const Vector& other) const {
		T result(0.0f);
		for (size_t i = 0; i < DIM; i++) {
			result += (*this)[i] * other[i];
		}
		return result;
	}

	template <size_t DIM, class T>
	Vector<DIM, T>& Vector<DIM, T>::normalize(size_t order) {
		T length = norm(*this, order);
		if (!length) {
			throw TringNormalizeZeroVectorException<T>();
		}
		*this /= length;
		return *this;
	}

	template <size_t DIM, class T>
	Vector<DIM, T> Vector<DIM, T>::normalized(size_t order) const {
		T length = norm(*this, order);
		if (!length) {
			throw TringNormalizeZeroVectorException<T>();
		}
		return *this / length;
	}

	template <size_t DIM, class T>
	Vector<DIM, T>& operator*(const T& scalar, const Vector<DIM, T>& vector) {
		return vector * scalar;
	}

	template <class T>
	Vector<3, T> operator%<T>(const Vector<3, T>& lhs, const Vector<3, T>& rhs) {
		Vector<3, T> result;
		result[0] = lhs[1] * rhs[2] - lhs[2] * rhs[1];
		result[1] = lhs[2] * rhs[0] - lhs[0] * rhs[2];
		result[2] = lhs[0] * rhs[1] - lhs[1] * rhs[0];
		return result;
	}

	template <class T>
	Vector<3, T>& operator%=<T>(Vector<3, T>& lhs, const Vector<3, T>& rhs) {
		lhs = lhs ^ rhs;
		return lhs;
	}

	template <size_t DIM, class T>
	std::ostream& operator<<<DIM, T>(std::ostream& os, const Vector<DIM, T>& vector) {
		os << "(";
		if (DIM > 0) {
			os << vector[0];
			for (size_t i = 1; i < DIM; i++) {
				os << ", " << vector[i];
			}
		}
		os << ")";
		return os;
	}

	template <size_t DIM, class T>
	std::istream& operator>><DIM, T>(std::istream& is, const Vector<DIM, T>& vector) {
		if (DIM > 0) {
			for (size_t i = 0; i < DIM; i++) {
				is >> vector[i];
			}
		}
		return is;
	}

	template <size_t DIM, class T>
	size_t dimension(const Vector<DIM, T>& vector) {
		return DIM;
	}

	template <size_t DIM, class T>
	T norm(const Vector<DIM, T>& vector, size_t order) {
		if (order > 0) {
			T result(0.0f);
			for (size_t i = 0; i < DIM; i++) {
				result += T(pow(abs(vector[i]), order));
			}
			return T(pow(double(result), 1.0 / order));
		}
		else {
			T result = vector[0];
			for (size_t i = 1; i < DIM; i++) {
				result = fmax(result, abs(vector[i]));
			}
			return result;
		}
	}

	template <size_t DIM, class T>
	T distance(const Vector<DIM, T>& lhs, const Vector<DIM, T>& rhs, size_t order) {
		return norm(lhs - rhs, order);
	}

	template <class T>
	Vector<1, T> get_vector(const T& x) {
		T arr[1] = { x };
		return Vector<1, T>(arr);
	}

	template <class T>
	Vector<2, T> get_vector(const T& x, const T& y) {
		T arr[2] = { x,y };
		return Vector<2, T>(arr);
	}

	template <class T>
	Vector<3, T> get_vector(const T& x, const T& y, const T& z) {
		T arr[3] = { x,y,z };
		return Vector<3, T>(arr);
	}

	template <class T>
	Vector<4, T> get_vector(const T& x, const T& y, const T& z, const T& w) {
		T arr[4] = { x,y,z,w };
		return Vector<4, T>(arr);
	}

}

