#include "Vector.h"

#include <algorithm>
#include <cmath>
#include <numeric>
#include <functional>
#include <utility>

#include "Exception.h"

namespace math {

	using std::abs;
	using std::accumulate;
	using std::fmax;
	using std::minus;
	using std::negate;
	using std::plus;
	using std::pow;
	using std::transform;

	template <size_t DIM, class T>
	Vector<DIM, T>::Vector(const T& value)
		: m_values(DIM, value) { }

	template <size_t DIM, class T>
	Vector<DIM, T>::Vector(const T values[DIM])
		: m_values(values) { }

	template <size_t DIM, class T>
	Vector<DIM, T>::Vector(const valarray<T>& values)
		: m_values(values) { }

	template <size_t DIM, class T>
	valarray<T>& Vector<DIM, T>::data() {
		return m_values;
	}

	template <size_t DIM, class T>
	const valarray<T>& Vector<DIM, T>::data() const {
		return m_values;
	}

	template <size_t DIM, class T>
	T& Vector<DIM, T>::operator[](size_t index) {
		if (!index || index > DIM) {
			throw OutOfRangeException<size_t>(1, DIM, index);
		}
		return m_values[index - 1];
	}

	template <size_t DIM, class T>
	const T& Vector<DIM, T>::operator[](size_t index) const {
		if (!index || index > DIM) {
			throw OutOfRangeException<size_t>(1, DIM, index);
		}
		return m_values[index - 1];
	}

	template <size_t DIM, class T>
	Vector<DIM, T>&& Vector<DIM, T>::operator+(const Vector& other) const {
		Vector<DIM, T> result;
		transform(m_values.begin(), m_values.end(), other.m_values.begin(), result.m_values.begin(), plus);
		return move(result);
	}

	template <size_t DIM, class T>
	Vector<DIM, T>& Vector<DIM, T>::operator+=(const Vector& other) {
		transform(m_values.begin(), m_values.end(), other.m_values.begin(), m_values.begin(), plus);
		return *this;
	}

	template <size_t DIM, class T>
	Vector<DIM, T>&& Vector<DIM, T>::operator-(const Vector& other) const {
		Vector<DIM, T> result;
		transform(m_values.begin(), m_values.end(), other.m_values.begin(), result.m_values.begin(), minus);
		return move(result);
	}

	template <size_t DIM, class T>
	Vector<DIM, T>& Vector<DIM, T>::operator-=(const Vector& other) {
		transform(m_values.begin(), m_values.end(), other.m_values.begin(), m_values.begin(), minus);
		return *this;
	}

	template <size_t DIM, class T>
	const Vector<DIM, T>& Vector<DIM, T>::operator-() const {
		transform(m_values.begin(), m_values.end(), m_values.begin(), negate);
		return *this;
	}

	template <size_t DIM, class T>
	Vector<DIM, T>& Vector<DIM, T>::operator-() {
		transform(m_values.begin(), m_values.end(), m_values.begin(), negate);
		return *this;
	}

	template <size_t DIM, class T>
	Vector<DIM, T>&& Vector<DIM, T>::operator*(const T& scalar) const {
		Vector<DIM, T> result;
		transform(m_values.begin(), m_values.end(), result.m_values.begin(),
			[](const T& elem) { return elem * scalar; });
		return move(result);
	}

	template <size_t DIM, class T>
	Vector<DIM, T>& Vector<DIM, T>::operator*=(const T& scalar) {
		transform(m_values.begin(), m_values.end(), m_values.begin(),
			[](const T& elem) { return elem * scalar; });
		return *this;
	}

	template <size_t DIM, class T>
	Vector<DIM, T>&& Vector<DIM, T>::operator/(const T& scalar) const {
		if (!scalar) {
			throw DivisionByZeroException();
		}
		Vector<DIM, T> result;
		transform(m_values.begin(), m_values.end(), result.m_values.begin(),
			[](const T& elem) { return elem / scalar; });
		return move(result);
	}

	template <size_t DIM, class T>
	Vector<DIM, T>& Vector<DIM, T>::operator/=(const T& scalar) {
		if (!scalar) {
			throw DivisionByZeroException();
		}
		transform(m_values.begin(), m_values.end(), m_values.begin(),
			[](const T& elem) { return elem / scalar; });
		return *this;
	}

	template <size_t DIM, class T>
	Vector<DIM, T>& Vector<DIM, T>::normalize() {
		T&& length = len(*this);
		if (!length) {
			throw TringNormalizeZeroVectorException();
		}
		*this /= length;
		return *this;
	}

	template <size_t DIM, class T>
	Vector<DIM, T>&& Vector<DIM, T>::normalized() const {
		T&& length = len(*this);
		if (!length) {
			throw TringNormalizeZeroVectorException();
		}
		return *this / length;
	}

	template <size_t DIM, class T>
	Vector<DIM, T>& operator*(const T& scalar, const Vector<DIM, T>& vector) {
		return vector * scalar;
	}

	template <class T>
	Vector<3, T>&& operator^<T>(const Vector<3, T>& lhs, const Vector<3, T>& rhs) {
		Vector<3, T> result;
		result[1] = lhs[2] * rhs[3] - lhs[3] * rhs[2];
		result[2] = lhs[3] * rhs[1] - lhs[1] * rhs[3];
		result[3] = lhs[1] * rhs[2] - lhs[2] * rhs[1];
		return move(result);
	}

	template <class T>
	Vector<3, T>& operator^=<T>(Vector<3, T>& lhs, const Vector<3, T>& rhs) {
		lhs = lhs ^ rhs;
		return lhs;
	}

	template <size_t DIM, class T>
	std::ostream& operator<<<DIM, T>(std::ostream& os, const Vector<DIM, T>& vector) {
		os << "(";
		if (DIM > 0) {
			os << vector[1];
			for (size_t i = 2; i <= DIM; i++) {
				os << ", " << vector[i];
			}
		}
		os << ")";
		return os;
	}

	template <size_t DIM, class T>
	std::istream& operator>><DIM, T>(std::istream& is, const Vector<DIM, T>& vector) {
		if (DIM > 0) {
			for (size_t i = 1; i <= DIM; i++) {
				is >> vector[i];
			}
		}
		return is;
	}

	template <size_t DIM, class T>
	size_t dim(const Vector<DIM, T>& vector) {
		return DIM;
	}

	template <size_t DIM, class T>
	T&& len(const Vector<DIM, T>& vector, size_t norm) {
		if (DIM > 0) {
			T result;
			for (T& elem : vector) {
				result += pow(elem, norm);
			}
			return pow(result, 1.0 / norm);
		}
		else {
			T result = vector[1];
			for (T& elem : vector) {
				result = fmax(result, elem);
			}
			return result;
		}
	}

	template <size_t DIM, class T>
	T&& dist(const Vector<DIM, T>& lhs, const Vector<DIM, T>& rhs, size_t norm) {
		return len(lhs - rhs, norm);
	}
}

