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

}

