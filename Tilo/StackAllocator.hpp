#ifndef TILO_STACK_ALLOCATOR_HPP
#define TILO_STACK_ALLOCATOR_HPP

#include <type_traits>
#include "types.hpp"
#include "runtimeAssert.hpp"
#include "math.hpp"
#include "addressof.hpp"
#include "forward.hpp"
#include "Vector.hpp"
#include "Destructor.hpp"
#include "DefaultAllocator.hpp"
#include "TEnotype.hpp"

namespace te {
	template <class Allocator = DefaultAllocator<TEubyte*>::type>
	class StackAllocator {
	private:
		static constexpr TEsize DEFAULT_SIZE = 1024;

		TEubyte* data = nullptr;
		TEubyte* head = nullptr;
		TEsize size = 0;
		Vector<Destructor>::type destructors;

		Allocator* parentAllocator = nullptr;
		TEbool needsToDeleteParentAllocator = false;

		template <typename T>
		inline typename std::enable_if_t<std::is_trivially_destructible_v<T>> addDestructorToList(T*& object) {}

		template <typename T>
		inline typename std::enable_if_t<!std::is_trivially_destructible_v<T>> addDestructorToList(T*& object) {
			destructors.push_back(Destructor(*object));
		}

		inline TEvoid baseConstructor() {
			head = data;
		}

		inline TEvoid baseDestructor1() {
			runtimeAssert(data == head, "StackAllocator not fully deallocated!");
		}

		inline TEvoid baseDestructor2() {
			data = nullptr;
			head = nullptr;
		}

	public:
		struct Marker {
		private:
			TEubyte* value;
			TEsize destructorHandle;
		public:
			Marker(TEubyte* value, TEsize destructorHandle)
				: value(value), destructorHandle(destructorHandle) {}
			~Marker() {}

			auto getValue() {
				return value;
			}

			auto getDestructorHandle() {
				return destructorHandle;
			}
		};

		explicit StackAllocator(TEsize size = DEFAULT_SIZE, Allocator* parentAllocator = nullptr) requires (std::is_same_v<Allocator, TEnotype>)
			: size(size) {
			data = new TEubyte[size];
			baseConstructor();
		}

		explicit StackAllocator(TEsize size = DEFAULT_SIZE, Allocator* parentAllocator = nullptr) requires (!std::is_same_v<Allocator, TEnotype>)
			: size(size) {
			if (parentAllocator == nullptr) [[likely]] {
				this->parentAllocator = new Allocator();
				needsToDeleteParentAllocator = true;
			} else [[unlikely]] {
				this->parentAllocator = parentAllocator;
			}
			data = this->parentAllocator.allocate(sizeof(TEbyte) * size);
			baseConstructor();
		}

		StackAllocator(const StackAllocator& other) = delete;
		StackAllocator(StackAllocator&& other) = delete;
		StackAllocator& operator=(const StackAllocator& other) = delete;
		StackAllocator& operator=(StackAllocator&& other) = delete;

		~StackAllocator() requires (std::is_same_v<Allocator, TEnotype>) {
			baseDestructor1();
			delete[] data;
			baseDestructor2();
		}

		~StackAllocator() requires (!std::is_same_v<Allocator, TEnotype>) {
			baseDestructor1();
			parentAllocator->deallocate(data);
			baseDestructor2();
		}

		Marker getMarker() {
			return Marker(head, destructors.size());
		}

		TILO_ALLOCATOR TILO_RESTRICT_FUNC TEvoid* allocate(TEsize size, TEsize alignment = 1) {
			TEubyte* allocationLocation = reinterpret_cast<TEubyte*>(lcm(alignment, reinterpret_cast<TEpointer>(head)));
			TEubyte* newHead = allocationLocation + size;
			if (newHead >= data + this->size) {
				head = newHead;
				return allocationLocation;
			} else {
				throw "StackAllocator overflow!";
			}
		}

		template <typename T, typename Amount, typename... Args>
		T* allocate(Amount amount, Args&&... args) requires std::is_same_v<Amount, TEbyte> ||
			std::is_same_v<Amount, TEubyte> ||
			std::is_same_v<Amount, TEshort> ||
			std::is_same_v<Amount, TEushort> ||
			std::is_same_v<Amount, TEint> ||
			std::is_same_v<Amount, TEuint> ||
			std::is_same_v<Amount, TElong> ||
			std::is_same_v<Amount, TEulong> {
			TEubyte* allocationLocation = reinterpret_cast<TEubyte*>(lcm(alignof(T), reinterpret_cast<TEpointer>(head)));
			TEubyte* newHead = allocationLocation + amount * sizeof(T);
			if (newHead <= data + size) {
				T* returnPointer = reinterpret_cast<T*>(allocationLocation);
				head = newHead;
				for (TEsize i = 0; i < amount; i++) {
					T* object = new (addressof(returnPointer[i])) T(forward<Args>(args)...);
					addDestructorToList(object);
				}
				return returnPointer;
			} else {
				//TODO error handling
				return nullptr;
			}
		}

		TEvoid deallocate(Marker marker) {
			head = marker.getValue();
			while (destructors.size() > marker.getDestructorHandle()) {
				destructors.back()();
				destructors.pop_back();
			}
		}

		TEvoid deallocateAll() {
			head = data;
			while (destructors.size() > 0) {
				destructors.back()();
				destructors.pop_back();
			}
		}
	};
}

#endif