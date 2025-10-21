#pragma once

#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <sstream>

class BitcoinExchange
{
	private:
		std::map<std::string, float> data_base;

		
	public:
		BitcoinExchange(void);
		BitcoinExchange(const BitcoinExchange &other);
		BitcoinExchange&	operator=(const BitcoinExchange &other);
		~BitcoinExchange(void);

		bool	build_data_base(std::string const &data_base);
		void	exchange(const std::string &input_file);
};

bool	csv_extension(const std::string &filename);
bool	valid_date_format(std::string &date);
bool	valid_value(std::string &value, int flag);
