#include <iostream>
#include <cmath>
#include <sstream>

__attribute__((destructor))
void check_leaks() {
	std::cout << std::endl;
	system("leaks -q convert");
}

std::string trim(std::string str) {
	std::string::size_type pos = str.find_first_not_of(" \t\n\r\f\v");
	if (pos != std::string::npos)
		str = str.substr(pos);
	pos = str.find_last_not_of(" \t\n\r\f\v");
	if (pos != std::string::npos)
		str = str.substr(0, pos + 1);
	return str;
}

bool as_char(std::string input, char &result) {
	if (input.length() != 1)
		return (false);
	if (!std::isprint(input[0]) || std::isdigit(input[0]))
		return (false);
	result = input[0];
	return (true);
}

bool as_int(std::string input, int &result) {
	std::stringstream ss(input);
	ss >> result;
	return (!ss.fail() && ss.eof());
}

bool as_float(std::string input, float &result) {
	if (input.back() == 'f')
		input.pop_back();
	else
		return false;
	std::stringstream ss(input);
	ss >> result;
	return (!ss.fail() && ss.eof());
}

bool as_double(std::string input, double &result) {
	std::stringstream ss(input);
	ss >> result;
	return (!ss.fail() && ss.eof());
}

template<typename T>
std::string print_char(T input) {
	std::stringstream ss;
	if (std::isnan(input) || std::isinf(input) || input < CHAR_MIN || input > CHAR_MAX) {
		ss << "impossible";
	}
	else if (std::isprint(input)) {
		ss << "'" << static_cast<char>(input) << "'";
	}
	else {
		ss << "Non displayable";
	}
	return ss.str();
}

template<typename T>
std::string print_int(T input) {
	std::stringstream ss;
	if (std::isnan(input) || std::isinf(input) || input < INT_MIN || input > INT_MAX) {
		ss << "impossible";
	}
	else {
		ss << static_cast<int>(input);
	}
	return ss.str();
}

template<typename T>
std::string print_float(T input) {
	std::stringstream ss;
	ss << static_cast<float>(input);
	if (!std::isinf(input) && input == roundf(input) && ss.str().find("e") == std::string::npos) {
		ss << ".0";
	}
	ss << "f";
	return ss.str();
}

template<typename T>
std::string print_double(T input) {
	std::stringstream ss;
	ss << static_cast<double>(input);
	if (!std::isinf(input) && input == round(input) && ss.str().find("e") == std::string::npos) {
		ss << ".0";
	}
	return ss.str();
}

template<typename T>
void print(T input) {
	std::cout << "char: " << print_char(input) << std::endl;
	std::cout << "int: " << print_int(input) << std::endl;
	std::cout << "float: " << print_float(input) << std::endl;
	std::cout << "double: " << print_double(input) << std::endl;
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		std::cerr << "Expected 1 argument, got: " << argc - 1 << " instead" << std::endl;
		return (1);
	}
	std::string input(argv[1]);
	input = trim(input);

	char c;
	int i;
	float f;
	double d;

	if (as_char(input, c)) {
		std::cerr << "type: char" << std::endl << std::endl;
		print(c);
	}
	else if (as_int(input, i)) {
		std::cerr << "type: int" << std::endl << std::endl;
		print(i);
	}
	else if (as_float(input, f)) {
		std::cerr << "type: float" << std::endl << std::endl;
		print(f);
	}
	else if (as_double(input, d)) {
		std::cerr << "type: double" << std::endl << std::endl;
		print(d);
	}
	else {
		std::cerr << "Could not convert to a scalar type" << std::endl;
		return (1);
	}

	return (0);
}
