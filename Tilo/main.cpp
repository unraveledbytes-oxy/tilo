#include <iostream>
#include <string>
#include "init.hpp"
#include "StackAllocator.hpp"
#include "PoolAllocator.hpp"
#include "TurboAllocator.hpp"
#include "nothing.hpp"
#include "CPUInfo.hpp"
#include "math.hpp"
#include <chrono>

class Person {
public:
	int age;
	std::string name;
	std::string haircolor;

	Person(int age, std::string name, std::string haircolor)
		: age(age), name(name), haircolor(haircolor) {
		std::cout << "Bin im Konstruktor!" << std::endl;
		te::nothing();
	}

	~Person() {
		std::cout << "Bin im Destruktor!" << std::endl;
	}

	void print() {
		std::cout << name << " " << age << " " << haircolor << std::endl;
	}
};

int main(void) {
	te::init();


	te::TurboAllocator<80, te::TEnotype> personenAllocator(10);
	Person* p1 = personenAllocator.allocate<Person>(18, "Peter", "braun");
	Person* p2 = personenAllocator.allocate<Person>(20, "Petra", "blond");
	p1->print();
	p2->print();
	personenAllocator.deallocate(p1);
	personenAllocator.deallocate(p2);
	personenAllocator.~TurboAllocator();



	/*
	te::StackAllocator<te::TEnotype> personenStackAllocator;
	auto marker = personenStackAllocator.getMarker();
	Person* ps1 = personenStackAllocator.allocate<Person>(10, 18, "Peter", "braun");

	for (size_t i = 0; i < 10; i++) {
		ps1[i].print();
	}

	personenStackAllocator.deallocate(marker);

	

	te::PoolAllocator<Person> personenPoolAllocator;
	Person* p1 = personenPoolAllocator.allocate(18, "Peter", "braun");
	Person* p2 = personenPoolAllocator.allocate(20, "Petra", "blond");

	p1->print();
	p2->print();

	personenPoolAllocator.deallocate(p1);
	personenPoolAllocator.deallocate(p2);
	*/


	/*
	te::TEdouble result;
	auto start = std::chrono::high_resolution_clock::now();
	for (te::TEdouble i = 0; i < 1000000000; i++) {
		// te::nothing();
		volatile te::TEint tmp = 0;
		// result = 1 / std::sqrt(i);
		result = te::invsqrt(i);
	}
	auto end = std::chrono::high_resolution_clock::now();

	std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << std::endl;
	*/

	return 0;
}
