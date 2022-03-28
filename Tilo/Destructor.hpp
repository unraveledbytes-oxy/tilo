// Class that can destroy objects

#ifndef TILO_DESTRUCTOR_HPP
#define TILO_DESTRUCTOR_HPP

#include "types.hpp"
#include "addressof.hpp"

namespace te {
	class Destructor {
	private:
		const TEvoid* data;
		TEvoid(*destructor)(const TEvoid*);

	public:
		template <class T>
		explicit Destructor(const T& data)
			: data(addressof(data)) {
			destructor = [](const TEvoid* lambdaData) {
				auto original = static_cast<const T*>(lambdaData);
				original->~T();
			};
		}

		~Destructor() {}

		TEvoid operator()() {
			destructor(data);
		}
	};
}

#endif