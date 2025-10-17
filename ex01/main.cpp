#include "RPN.hpp"

int	main(int ac, char **av) {
	if (ac == 1 || ac > 2) {
		std::cerr << "Error" << std::endl;
		return 1;
	}
	std::string op = av[1];
	if (op.empty()) {
		std::cerr << "Error" << std::endl;
		return 1;
	}
	try {
		RPN	rpn(op);
		rpn.calculate();
	}
	catch (const char *e) {
		std::cerr << e << std::endl;
	}
	return 0;
}