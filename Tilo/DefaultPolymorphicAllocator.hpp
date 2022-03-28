// Default polymorphic parent allocator
#ifndef TILO_DEFAULTPOLYMORPHICALLOCATOR_HPP
#define TILO_DEFAULTPOLYMORPHICALLOCATOR_HPP

#include <memory_resource>

namespace te {
	template <typename T>
	struct DefaultPolymorphicAllocator {
	public:
		typedef std::pmr::polymorphic_allocator<T> type;

		DefaultPolymorphicAllocator() = delete;
		~DefaultPolymorphicAllocator() = delete;
	};
}

#endif
