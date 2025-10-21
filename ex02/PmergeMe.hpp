#pragma once

#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>
#include <ctime>
#include <climits>


class PmergeMe
{
	private:
		int					ac;
		char				**av;
		void				ford_johnson_vector(std::vector<int> &v_cont);
		void				ford_johnson_deque(std::deque<int> &d_cont);
		void				sort_vector(std::vector<int> &v_cont);
		void				sort_deque(std::deque<int> &d_cont);
		void				is_pos_int();
		
	public:
		PmergeMe(void);
		PmergeMe(int ac, char **str);
		PmergeMe(const PmergeMe &other);
		PmergeMe&	operator=(const PmergeMe &other);
		~PmergeMe(void);

		void	sort();
};
