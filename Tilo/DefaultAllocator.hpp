// Default parent allocator
#ifndef TILO_DEFAULTALLOCATOR_HPP
#define TILO_DEFAULTALLOCATOR_HPP

#include <memory>

namespace te {
	template <typename T>
	struct DefaultAllocator {
	public:
		typedef std::allocator<T> type;

		DefaultAllocator() = delete;
		~DefaultAllocator() = delete;
	};
}

#endif