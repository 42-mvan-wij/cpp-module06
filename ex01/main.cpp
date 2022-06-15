#include <iostream>
#include <cmath>
#include <sstream>

__attribute__((destructor))
void check_leaks() {
	std::cout << std::endl;
	system("leaks -q serialize");
}

struct Data {
	std::string content;
	int value;
};

uintptr_t serialize(Data *ptr) {
	return reinterpret_cast<uintptr_t>(ptr);
}

Data *deserialize(uintptr_t raw) {
	return reinterpret_cast<Data *>(raw);
}

int main() {
	Data data;
	data.content = "Hello";
	data.value = 42;

	std::cout << "ptr:          " << &data << std::endl;
	uintptr_t raw = serialize(&data);
	std::cout << "Serialized:   " << raw << std::endl;
	Data *ptr2 = deserialize(raw);
	std::cout << "Deserialized: " << ptr2 << std::endl;

	assert(ptr2 == &data);
	assert(ptr2->content == data.content);
	assert(ptr2->value == data.value);

	return (0);
}
