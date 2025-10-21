#include "BitcoinExchange.hpp"


int	main(int ac, char **av){
    if (ac == 2) {
		std::string	data_file = "data.csv";
		std::string	input_file = av[1];
		BitcoinExchange	test;
		if (test.build_data_base(data_file) == false)
			return 1;
		try {
			test.exchange(input_file);
		}
		catch (const char *e) {
			std::cerr << e << std::endl;
		}
	}
	else
		std::cerr << "Error" << std::endl;

    return 0;
}