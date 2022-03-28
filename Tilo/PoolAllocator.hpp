// Basic pool allocator
#ifndef TILO_POOLALLOCATOR_HPP
#define TILO_POOLALLOCATOR_HPP

#include <type_traits>
#include "types.hpp"
#include "TEnotype.hpp"
#include "math.hpp"
#include "DefaultAllocator.hpp"
#include "forward.hpp"
#include "addressof.hpp"
#include "runtimeAssert.hpp"
#include "attributes.hpp"

namespace te {
	namespace {
	template <typename T>
		union PoolChunk {
		private:
			friend class PoolAllocator;
			T value;
			PoolChunk<T>* next;
	
			PoolChunk() {};
		public:
			~PoolChunk() {};
		};
	}

	template <typename T, class Allocator = DefaultAllocator<PoolChunk<T>>::type>
	class PoolAllocator {
	private:
		static constexpr TEsize DEFAULT_SIZE = 1024;

		TEsize openAllocations = 0;
		TEsize size = 0;
		PoolChunk<T>* data = nullptr;
		PoolChunk<T>* head = nullptr;

		Allocator* parentAllocator;
		TEbool needsToDeleteParentAllocator = false;


		inline TEvoid baseConstructor() {
			head = data;
			for (TEsize i = 0; i < size - 1; i++)
				data[i].next = addressof(data[i + 1]);
			data[size - 1].next = nullptr;
		}

		inline TEvoid baseDestructor1() {
			runtimeAssert(!openAllocations, "PoolAllocator not fully deallocated!");
		}

		inline TEvoid baseDestructor2() {
			data = nullptr;
			head = nullptr;
		}

	public:
		explicit PoolAllocator(TEsize size = DEFAULT_SIZE, Allocator* parentAllocator = nullptr) requires (std::is_same_v<Allocator, TEnotype>)
			: size(size), parentAllocator(parentAllocator) {
			data = new PoolChunk<T>[size];
			baseConstructor();
		}

		explicit PoolAllocator(TEsize size = DEFAULT_SIZE, Allocator* parentAllocator = nullptr) requires (!std::is_same_v<Allocator, TEnotype>)
			: size(size), parentAllocator(parentAllocator) {
			if (parentAllocator == nullptr) [[likely]] {
				this->parentAllocator = new Allocator();
				needsToDeleteParentAllocator = true;
			} else [[unlikely]] {
				this->parentAllocator = parentAllocator;
			}
			data = parentAllocator->allocate(size);
			baseConstructor();
		}

		PoolAllocator(const PoolAllocator& other) = delete;
		PoolAllocator(PoolAllocator&& other) = delete;
		PoolAllocator& operator=(const PoolAllocator& other) = delete;
		PoolAllocator& operator=(PoolAllocator&& other) = delete;

		~PoolAllocator() requires (std::is_same_v<Allocator, TEnotype>) {
			baseDestructor1();
			delete[] data;
			baseDestructor2();
		}

		~PoolAllocator() requires (!std::is_same_v<Allocator, TEnotype>) {
			baseDestructor1();
			parentAllocator->deallocate(data, size);
			if (needsToDeleteParentAllocator)
				delete parentAllocator;
			baseDestructor2();
		}

		TEvoid deallocate(T* data) {
			runtimeAssert(labs(reinterpret_cast<TEpointer>(addressof(this->data)) - reinterpret_cast<TEpointer>(data)) / sizeof(T) > size - 1,
				"Trying to deallocate data that doesn't belong to PoolAllocator!");

			openAllocations--;

			data->~T();	
			PoolChunk<T>* poolChunk = reinterpret_cast<PoolChunk<T>*>(data);
			poolChunk->next = head;
			head = poolChunk;
		}

		template <typename... Args>
		TILO_ALLOCATOR TILO_RESTRICT_FUNC T* allocate(Args&&... args) {
			if (head == nullptr) {
				return nullptr;
			}

			openAllocations++;

			PoolChunk<T>* poolChunk = head;
			head = head->next;
			return new (addressof(poolChunk->value)) T(forward<Args>(args)...);
		}
	};
}

#endif
