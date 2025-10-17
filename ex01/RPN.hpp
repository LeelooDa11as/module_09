#pragma once

#include <iostream>
#include <stack>

class RPN
{
	private:
		std::stack<int> _stack;
		std::string	_op;
		void	operate(char c);

	public:
		RPN(void);
		RPN(const std::string &op);
		RPN(const RPN &other);
		RPN& operator=(const RPN &other);
		~RPN(void);

		void	calculate(void);
};
