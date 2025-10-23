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

int		get_index(int num, const std::vector<int> &big_nums);
int		get_index_deque(int num, const std::deque<int> &big_nums);

template <typename Container>
void 	jacobsthal_order(Container &cont){
	int i = 1;
	int j = 0;
	for (size_t jacob_sum = 0; jacob_sum < cont.size(); ++i){
		int jn = 2 * i + j;
		// if the jacobsthal number is too big, we reverse what we can
		if (jn + jacob_sum > cont.size())
			jn = cont.size() - jacob_sum;
		// it starts from the sum of all previous jacobstal numbers up to the end of current one
		std::reverse(cont.begin() + jacob_sum, cont.begin() + jacob_sum + jn);
		jacob_sum += jn;
		//actualisation of jacobsthal previous numbers
		std::swap(i, j);
		std::swap(j, jn);
	}

}