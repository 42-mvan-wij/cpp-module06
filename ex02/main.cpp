#include <iostream>
#include <cstdlib>
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

void check_leaks() {
	std::cout << std::endl;
	std::system("leaks -q real-type");
}

Base * generate() {
	int rnd = rand() % 3;
	if (rnd == 0) {
		std::cout << "Generated A" << std::endl;
		return new A();
	}
	if (rnd == 1) {
		std::cout << "Generated B" << std::endl;
		return new B();
	}
	std::cout << "Generated C" << std::endl;
	return new C();
}

void identify(Base* p) {
	try {
		(void)dynamic_cast<A&>(*p);
		std::cout << "Found A*" << std::endl;
		return ;
	} catch (std::bad_cast&) {}

	try {
		(void)dynamic_cast<B&>(*p);
		std::cout << "Found B*" << std::endl;
		return ;
	} catch (std::bad_cast&) {}

	try {
		(void)dynamic_cast<C&>(*p);
		std::cout << "Found C*" << std::endl;
		return ;
	} catch (std::bad_cast&) {}
}

void identify(Base& p) {
	try {
		(void)dynamic_cast<A&>(p);
		std::cout << "Found A&" << std::endl;
		return ;
	} catch (std::bad_cast&) {}

	try {
		(void)dynamic_cast<B&>(p);
		std::cout << "Found B&" << std::endl;
		return ;
	} catch (std::bad_cast&) {}

	try {
		(void)dynamic_cast<C&>(p);
		std::cout << "Found C&" << std::endl;
		return ;
	} catch (std::bad_cast&) {}
}

int main() {
	std::atexit(&check_leaks);

	srand(time(NULL));

	for (int i = 0; i < 5; i++) {
		Base *p = generate();
		identify(p);
		identify(*p);
		delete p;
		std::cout << std::endl;
	}

	return (0);
}
