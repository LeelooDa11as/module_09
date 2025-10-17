#include "RPN.hpp"

RPN::RPN(void) {
	//std::cout << "RPN default constructor called" << std::endl;
	return;
}

RPN::RPN(const std::string &op) : _op(op) {
	//std::cout << "RPN full constructor called" << std::endl;
	return;
}

RPN::RPN(const RPN &other) : _op(other._op) {
	//std::cout << "RPN full constructor called" << std::endl;
	return;
}

RPN&	RPN::operator=(const RPN &other) {
	//std::cout << "RPN full constructor called" << std::endl;
	if (this != &other)
		this->_op = other._op;
	return *this;
}

RPN::~RPN(void) {
	//std::cout << "RPN class destructor called" << std::endl;
}


void	RPN::operate(char c) {
	int	base;
	int	top;

	if (_stack.empty())
		throw("Error");
	top = _stack.top();
	_stack.pop();
	if (_stack.empty())
		throw("Error");
	base = _stack.top();
	_stack.pop();

	if (c == '+')
		base = base +top;
	else if (c == '-')
		base = base - top;
	else if (c == '*')
		base = base * top;
	else if (c == '/')
		base = base / top;
	//std::cout << base << std::endl;
	_stack.push(base);
	return;
}


void	RPN::calculate(void) {
	for (size_t i = 0; i < _op.size(); i++) {
		if (_op[i] == '+' || _op[i] == '-' || _op[i] == '*' || _op[i] == '/') {
			operate(_op[i]);
		}
		else if (_op[i] >= '0' && _op[i] <= '9')
		{
			int	num = _op[i] - '0';
			_stack.push(num);
		}
		else if (_op[i] != ' ') {
			throw("Error");
		}
	}
	std::cout << _stack.top() << std::endl;
	return;
}