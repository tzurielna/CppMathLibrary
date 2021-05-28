#pragma once

#include <exception>
#include <string>

namespace math {

	using std::exception;
	using std::string;

	template <class T>
	class OutOfRangeException : public exception {
	public:
		OutOfRangeException(const T& minValue, const T& maxValue, const T& value);
		const char* what() const override;

	private:
		T m_minValue;
		T m_maxValue;
		T m_value;
	};

	template <class T = float>
	class InmatchDimensionsException : public exception {
	public:
		InmatchDimensionsException(size_t expectedDim, size_t givenDim, string message = "");
		const char* what() const override;

	private:
		size_t m_expectedDim;
		size_t m_givenDim;
		string m_message;
	};

	template <class T = float>
	class DivisionByZeroException : public exception {
	public:
		const char* what() const override;
	};

	template <class T = float>
	class TringNormalizeZeroVectorException : public exception {
	public:
		const char* what() const override;
	};

}

#include "Exception.inl"

