// Vector
#ifndef TILO_VECTOR_HPP
#define TILO_VECTOR_HPP

#include <vector>

namespace te {
	template <typename T>
	struct Vector {
	public:
		typedef std::vector<T> type;
		Vector() = delete;
		~Vector() = delete;
	};
}

#endif