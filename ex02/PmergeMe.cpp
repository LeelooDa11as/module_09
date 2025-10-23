#include "PmergeMe.hpp"

PmergeMe::PmergeMe(void) {

}
PmergeMe::PmergeMe(int ac, char **av) : ac(ac), av(av) {

}

PmergeMe::PmergeMe(const PmergeMe &other) : ac(other.ac), av(other.av){

}

PmergeMe&	PmergeMe::operator=(const PmergeMe &other) {
	if (this != &other) {
		av = other.av;
		ac = other.ac;
	}
	return *this;
}

PmergeMe::~PmergeMe(void) {

}

void	PmergeMe::is_pos_int(void) {
	for (int i = 1; i < ac; i++) {
		std::string	aux = av[i];
		if (aux.size() > 10)
			throw ("Error");
		for (size_t x = 0; x < aux.size(); x++) {
			if (!isdigit(av[i][x]))
				throw ("Error");
		}
		long int	num = atoi(aux.c_str());
		if (num < 0 || num > INT_MAX)
			throw ("Error");
	}
}

int		get_index(int num, const std::vector<int> &big_nums) {
	for (size_t i = 0; i < big_nums.size(); i++) {
		if (num == big_nums[i])
			return (i);
	}
	return -1;
}

int		get_index_deque(int num, const std::deque<int> &big_nums) {
	int i = 0;
	for (std::deque<int>::const_iterator it = big_nums.begin(); it != big_nums.end(); it++) {
		if (num == *it)
			return (i);
		i++;
	}
	return -1;
}

void	PmergeMe::ford_johnson_vector(std::vector<int> &v_cont) {
	std::vector<int>	big_nums;
	std::vector<int>	big_nums_raw;
	std::vector<int>	small_nums;
	std::vector<int>	small_nums_sort_index;

	if (v_cont.size() < 2)
		return;
	
	for (size_t i = 1; i < v_cont.size(); i += 2) {
		int big = v_cont[i];
		int small = v_cont[i-1];
		if (big < small)
			std::swap(big, small);
		big_nums.push_back(big);
		small_nums.push_back(small);
	}
	//it saves the old position on big_nums in order to do big-small same index position
	big_nums_raw = big_nums;
	ford_johnson_vector(big_nums);
	//put small nums in the index order of their big brother 
	for (size_t i = 0; i < big_nums.size(); i++) {
		int ind = get_index(big_nums[i], big_nums_raw);
		small_nums_sort_index.push_back(small_nums[ind]);
	}
	if (v_cont.size() % 2 == 1)
		small_nums_sort_index.push_back(*(v_cont.end()-1));

	jacobsthal_order(small_nums_sort_index);

	for (size_t i = 0; i < small_nums_sort_index.size(); i++) {
		int insert = small_nums_sort_index[i];
		std::vector<int>::iterator it = std::lower_bound(big_nums.begin(), big_nums.end(), insert);
		big_nums.insert(it, insert);
	}
	//this works if not passed as ref, else = is enough
	v_cont.assign(big_nums.begin(), big_nums.end());
	return;
}

void	PmergeMe::sort_vector(std::vector<int> &v_cont) {

    for (int i = 1; i < ac; i++) {
        std::string	aux = av[i];
		int			num = atoi(aux.c_str());
		v_cont.push_back(num);
    }
	ford_johnson_vector(v_cont);
}

void	PmergeMe::ford_johnson_deque(std::deque<int> &d_cont) {
	std::deque<int>	big_nums;
	std::deque<int>	big_nums_raw;
	std::deque<int>	small_nums;
	std::deque<int>	small_nums_sort_index;
	int				last_num;

	if (d_cont.size() < 2)
		return;
	
	for (std::deque<int>::iterator it = d_cont.begin(); it != d_cont.end(); it += 2) {
		std::deque<int>::iterator next = it + 1;
		// odd deque size, deal later
		if (next == d_cont.end()) {
			last_num = *it;
			break;
		}
		if (*next < *it)
			std::iter_swap(next, it);
		big_nums.push_back(*next);
		small_nums.push_back(*it);
	}
	// old positions of bigger numbers
	big_nums_raw = big_nums;
	ford_johnson_deque(big_nums);

	// putting small nums in the index of their bigger brother
	for (std::deque<int>::iterator it = big_nums.begin(); it != big_nums.end(); it++) {
		int ind = get_index_deque(*it, big_nums_raw);
		small_nums_sort_index.push_back(*(small_nums.begin()+ind));
	}
	if (d_cont.size() % 2 == 1)
		small_nums_sort_index.push_back(last_num);
	
	jacobsthal_order(small_nums_sort_index);

	for (std::deque<int>::iterator it = small_nums_sort_index.begin(); it != small_nums_sort_index.end(); it++) {
		std::deque<int>::iterator pos = std::lower_bound(big_nums.begin(), big_nums.end(), *it);
		big_nums.insert(pos, *it);
	}
	d_cont = big_nums;
	return;
}

void	PmergeMe::sort_deque(std::deque<int> &d_cont) {
	for (int i = 1; i < ac; i++) {
        std::string	aux = av[i];
		int			num = atoi(aux.c_str());
		d_cont.push_back(num);
    }
	ford_johnson_deque(d_cont);
}

void	PmergeMe::sort() {
	try {
		is_pos_int();
	}

	catch (const char *e)
	{
		std::cerr << e << std::endl;
		return; // not sure
	}

	std::vector<int>	v_cont;
	std::deque<int>		d_cont;
	clock_t start_vec = clock();
	sort_vector(v_cont);
	clock_t end_vec = clock();
	clock_t total_vec = end_vec - start_vec;
	double seconds_vec = static_cast<double>(total_vec) * 1000 / CLOCKS_PER_SEC;


	clock_t start_deq = clock();
	sort_deque(d_cont);
	clock_t end_deq = clock();
	clock_t total_deq = end_deq - start_deq;
	double seconds_deq = static_cast<double>(total_deq) * 1000 / CLOCKS_PER_SEC;

	//print before
	std::cout << "Before:";
	for (int i = 1; i < ac; i++)
		std::cout << " " << av[i];
	std::cout << std::endl;
	std::cout << "After: ";
	for (size_t i = 0; i < v_cont.size(); i++)
		std::cout << " " << v_cont[i];
	std::cout << std::endl;
	std::cout << "After: ";
	for (std::deque<int>::iterator it = d_cont.begin(); it != d_cont.end(); it++)
		std::cout << " " << *it;
	std::cout << std::endl;
	std::cout << "Time to process a range of " << v_cont.size() << " elements with ";
	std::cout << "std::deque<int> is " << seconds_deq << " ms" << std::endl;
	std::cout << "Time to process a range of " << v_cont.size() << " elements with ";
	std::cout << "std::vector<int> is " << seconds_vec << " ms" << std::endl;
    //for (size_t i = 1; i < v_cont.size(); ++i) {
    //     if (v_cont[i-1] > v_cont[i]){
    //         std::cout << "Not sorted <<" << std::endl;
	// 		return; 
	// 	}
    //}
    //std::cout << "Sorted <<" << std::endl;
	return;
}