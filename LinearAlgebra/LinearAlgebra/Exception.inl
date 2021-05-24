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

	InmatchDimensionsException::InmatchDimensionsException(size_t expectedDim, size_t givenDim, string message)
		: m_expectedDim(expectedDim), m_givenDim(givenDim), m_message(message) { }

	const char* InmatchDimensionsException::what() const {
		ostrstream message;
		message << "Given dimension " << m_givenDim << " instead of " << m_expectedDim << " at " << m_message;
		return message.rdbuf()->str();
	}

	const char* DivisionByZeroException::what() const {
		return "Division by zero";
	}

	const char* TringNormalizeZeroVectorException::what() const {
		return "Tring to normalize a zero vector";
	}

}

