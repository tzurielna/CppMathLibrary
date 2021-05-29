#include "Exception.h"

#include <strstream>

namespace math {

	using std::ostrstream;

	template <class T>
	OutOfRangeException<T>::OutOfRangeException(const T& minValue, const T& maxValue, const T& value)
		: m_minValue(minValue), m_maxValue(maxValue), m_value(value) { }

	template <class T>
	const char* OutOfRangeException<T>::what() const {
		ostrstream message;
		message << "Object " << m_value << " is out of range [" << m_minValue << ", " << m_maxValue << "]";
		return message.rdbuf()->str();
	}

	template <class T>
	InmatchDimensionsException<T>::InmatchDimensionsException(size_t expectedDim, size_t givenDim, string message)
		: m_expectedDim(expectedDim), m_givenDim(givenDim), m_message(message) { }

	template <class T>
	const char* InmatchDimensionsException<T>::what() const {
		ostrstream message;
		message << "Given dimension " << m_givenDim << " instead of " << m_expectedDim << " at " << m_message;
		return message.rdbuf()->str();
	}

	template <class T>
	const char* DivisionByZeroException<T>::what() const {
		return "Division by zero";
	}

	template <class T>
	const char* TringNormalizeZeroVectorException<T>::what() const {
		return "Tring to normalize a zero vector";
	}

}

