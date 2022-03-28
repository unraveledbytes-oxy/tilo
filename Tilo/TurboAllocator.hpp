// Super fast, but memory hungry allocator

#ifndef TILO_TURBOALLOCATOR_HPP
#define TILO_TURBOALLOCATOR_HPP

#include <type_traits>
#include "types.hpp"
#include "runtimeAssert.hpp"
#include "math.hpp"
#include "addressof.hpp"
#include "forward.hpp"
#include "DefaultPolymorphicAllocator.hpp"
#include "TEnotype.hpp"
#include "TErawbyte.hpp"
#include "fill.hpp"
#include "prefetch.hpp"

namespace te {
	template <TEsize chunkSize, class PolymorphicAllocator = DefaultPolymorphicAllocator<TErawbyte>::type>
	class TurboAllocator {
	private:
		TEsize chunks;
		TErawbyte* data = nullptr;
		TEfastbyte* mask = nullptr;

		PolymorphicAllocator* parentAllocator;
		TEbool needsToDeleteParentAllocator = false;

		
		inline TEvoid baseConstructor() {
			static_assert(chunkSize % 16 == 0, "TurboAllocator's chunkSize must be a multiple of 16!");
			fill(mask, &mask[chunks - 1], 0);
		}

		inline TEvoid baseDestructor1() {
			TEfastbyte anyOpenAllocations = 0;
			TILO_PREFETCH_READ_T1(mask)
			for (TEsize i = 0; i < chunks; i++) {
				TILO_ASSUME(!mask[i])
				if (mask[i]) [[unlikely]] {
					anyOpenAllocations = 1;
				}
			}
			runtimeAssert(!anyOpenAllocations, "TurboAllocator not fully deallocated!");
		}

		inline TEvoid baseDestructor2() {
			data = nullptr;
			mask = nullptr;
		}
	public:
		explicit TurboAllocator(TEsize chunks, PolymorphicAllocator* parentAllocator = nullptr) requires (std::is_same_v<PolymorphicAllocator, TEnotype>)
			: chunks(chunks), parentAllocator(parentAllocator) {
			data = new TILO_ALIGN(16) TErawbyte[chunkSize * chunks];
			mask = new TEfastbyte[chunks];
			baseConstructor();
		}

		explicit TurboAllocator(TEsize chunks, PolymorphicAllocator* parentAllocator = nullptr) requires (!std::is_same_v<PolymorphicAllocator, TEnotype>)
			: chunks(chunks), parentAllocator(parentAllocator) {
			if (parentAllocator == nullptr) [[likely]] {
				this->parentAllocator = new PolymorphicAllocator();
				needsToDeleteParentAllocator = true;
			} else [[unlikely]] {
				this->parentAllocator = parentAllocator;
			}
			data = reinterpret_cast<TErawbyte*>(parentAllocator->allocate_bytes(chunkSize * chunks, 16));
			mask = reinterpret_cast<TEfastbyte*>(parentAllocator->allocate_bytes(sizeof(TEfastbyte) * chunks));
			baseConstructor();
		}

		TurboAllocator(const TurboAllocator& other) = delete;
		TurboAllocator(TurboAllocator&& other) = delete;
		TurboAllocator& operator=(const TurboAllocator& other) = delete;
		TurboAllocator& operator=(TurboAllocator&& other) = delete;

		~TurboAllocator() requires (std::is_same_v<PolymorphicAllocator, TEnotype>) {
			baseDestructor1();
			delete[] data;
			delete[] mask;
			baseDestructor2();
		}

		~TurboAllocator() requires (!std::is_same_v<PolymorphicAllocator, TEnotype>) {
			baseDestructor1();
			parentAllocator->deallocate_bytes(reinterpret_cast<void*>(data), chunkSize * chunks, 16);
			parentAllocator->deallocate_bytes(reinterpret_cast<void*>(mask), sizeof(TEfastbyte) * chunks);
			baseDestructor2();
		}
		
		template <typename T>
		TEvoid deallocate(T* data) {
			auto distance = labs(reinterpret_cast<TEpointer>(data) - reinterpret_cast<TEpointer>(&this->data));
			runtimeAssert(static_cast<std::make_unsigned_t<decltype(distance)>>(distance) <= chunkSize * (chunks - 1) , "Trying to deallocate data that doesn't belong to TurboAllocator!");
			data->~T();
			mask[distance / chunkSize] = 0;
		}

		template <typename T, typename... Args>
		TILO_ALLOCATOR TILO_RESTRICT_FUNC T* allocate(Args&&... args) {
			static_assert(sizeof(T) <= chunkSize, "Trying to allocate an object that is bigger than TurboAllocator's chunkSize!");
			for (TEsize i = 0; i < chunks; i++) {
				if (!mask[i]) {
					mask[i] = 1;
					return new (&data[chunkSize * i]) T(forward<Args>(args)...);
				}
			}

			TILO_UNREACHABLE
			return nullptr;
		}
	};
}

#endif
