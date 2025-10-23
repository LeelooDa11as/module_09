#include "PmergeMe.hpp"
void removeDuplicates(int &ac, char **av) {
	for (int i = 1; i < ac; i++) {
		for (int j = i + 1; j < ac; ) {
			if (std::string(av[i]) == std::string(av[j])) {
				// Shift everything left
				for (int k = j; k < ac - 1; k++)
					av[k] = av[k + 1];
				ac--;  // total count decreases
			} else {
				j++; // only move forward if no deletion
			}
		}
	}
}

int main(int ac, char **av) {
    if (ac == 1) {
        std::cerr << "Error" << std::endl;
        return 1;
    }

    removeDuplicates(ac, av);
	PmergeMe	res(ac, av);
	res.sort();
    return 0;
}