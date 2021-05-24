#pragma once

#include <iostream>
#include <valarray>

namespace math {

	using std::valarray;

	template <size_t DIM, class T = float>
	class Vector {
	public:
		Vector(const T& value = 0);
		Vector(const T values[DIM]);
		Vector(const valarray<T>& values);

		valarray<T>& data();
		const valarray<T>& data() const;

		T& operator[](size_t index);
		const T& operator[](size_t index) const;

		Vector&& operator+(const Vector& other) const;
		Vector& operator+=(const Vector& other);

		Vector&& operator-(const Vector& other) const;
		Vector& operator-=(const Vector& other);

		const Vector& operator-() const;
		Vector& operator-();

		Vector&& operator*(const T& scalar) const;
		Vector& operator*=(const T& scalar);

		Vector&& operator/(const T& scalar) const;
		Vector& operator/=(const T& scalar);

		T&& operator*(const T& other) const;

		Vector& normalize();
		Vector&& normalized() const;

	private:
		valarray<T> m_values;

	};

	template <size_t DIM, class T>
	Vector<DIM, T>& operator*(const T& scalar, const Vector<DIM, T>& vector);

	template <class T>
	Vector<3, T>&& operator^(const Vector<3, T>& lhs, const Vector<3, T>& rhs);

	template <class T>
	Vector<3, T>& operator^=(Vector<3, T>& lhs, const Vector<3, T>& rhs);

	template <size_t DIM, class T = float>
	std::ostream& operator<<(std::ostream& os, const Vector<DIM, T>& vector);

	template <size_t DIM, class T = float>
	std::istream& operator>>(std::istream& is, const Vector<DIM, T>& vector);

	template <size_t DIM, class T = float>
	size_t dim(const Vector<DIM, T>& vector);

	template <size_t DIM, class T = float>
	T&& len(const Vector<DIM, T>& vector, size_t norm = 2);

	template <size_t DIM, class T = float>
	T&& dist(const Vector<DIM, T>& lhs, const Vector<DIM, T>& rhs, size_t norm = 2);

}

#include "Vector.inl"

