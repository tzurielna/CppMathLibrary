#pragma once

#include <initializer_list>
#include <iostream>

namespace math {

	template <size_t DIM, class T = float>
	class Vector {
	public:
		Vector(const T& value = 0);
		Vector(const T values[DIM]);
		Vector(const std::initializer_list<T>& list);

		T* data();
		const T* data() const;

		T& operator()(size_t index);
		const T& operator()(size_t index) const;

		Vector operator+(const Vector& other) const;
		Vector& operator+=(const Vector& other);

		Vector operator-(const Vector& other) const;
		Vector& operator-=(const Vector& other);

		Vector operator-() const;

		Vector operator*(const T& scalar) const;
		Vector& operator*=(const T& scalar);

		Vector operator/(const T& scalar) const;
		Vector& operator/=(const T& scalar);

		T operator*(const Vector& other) const;

		Vector& normalize(size_t order = 2);
		Vector normalized(size_t order = 2) const;

	private:
		T m_values[DIM];

	};

	template <size_t DIM, class T = float>
	Vector<DIM, T>& operator*(const T& scalar, const Vector<DIM, T>& vector);

	template <class T = float>
	Vector<3, T> operator%(const Vector<3, T>& lhs, const Vector<3, T>& rhs);

	template <class T = float>
	Vector<3, T>& operator%=(Vector<3, T>& lhs, const Vector<3, T>& rhs);

	template <size_t DIM, class T = float>
	std::ostream& operator<<(std::ostream& os, const Vector<DIM, T>& vector);

	template <size_t DIM, class T = float>
	std::istream& operator>>(std::istream& is, const Vector<DIM, T>& vector);

	template <size_t DIM, class T = float>
	size_t dimension(const Vector<DIM, T>& vector);

	template <size_t DIM, class T = float>
	T norm(const Vector<DIM, T>& vector, size_t order = 2);

	template <size_t DIM, class T = float>
	T distance(const Vector<DIM, T>& lhs, const Vector<DIM, T>& rhs, size_t order = 2);

}

#include "Vector.inl"

