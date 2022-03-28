// Special type for signaling the non-use of templates
#ifndef TILO_TENOTYPE_HPP
#define TILO_TENOTYPE_HPP

namespace te {
	struct TEnotype {
	public:
		TEnotype() = delete;
		~TEnotype() = delete;
	};
}

#endif