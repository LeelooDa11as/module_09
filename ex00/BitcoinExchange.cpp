#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(void) { 
	//std::cout << "BitcoinExchange class default constructor called" << std::endl;
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) : data_base(other.data_base) {
	//std::cout << "BitcoinExchange class copy constructor called" << std::endl;
}

BitcoinExchange&	BitcoinExchange::operator=(const BitcoinExchange &other) {
	//std::cout << "BitcoinExchange class assign operator called" << std::endl;
	if (this != &other)
		this->data_base = other.data_base;
	return (*this);
}

BitcoinExchange::~BitcoinExchange(void) {
	//std::cout << "BitcoinExchange class destructor called" << std::endl;
};


bool	BitcoinExchange::build_data_base(std::string const &data_base_name) {
	
	std::map<std::string, float> data;
    std::string line;

	if (!csv_extension(data_base_name))
		return false;

	// this is optional and can be omitted
	std::ifstream data_file(data_base_name);
	if (!data_file.is_open()) {
    	std::cerr << "Failed to create file\n";
		return false;
	}

	// to skip first line as it is header
	if (!std::getline(data_file, line)) {
        std::cerr << "Error: empty file\n";
        return false;
    }

	while (std::getline(data_file, line))
	{
    	std::stringstream ss(line);
        std::string date, valueStr;

        if (!std::getline(ss, date, ',') || !std::getline(ss, valueStr)) {
            std::cerr << "Bad line: " << line << "\n";
            continue;
        }

        if (!valid_date_format(date) || !valid_value(valueStr, 1)) {
            std::cerr << "Invalid data: " << line << "\n";
            continue;
        }

        data[date] = atof(valueStr.c_str());
		//for (std::map<std::string,float>::iterator it = data.begin(); it != data.end(); ++it)
        //	std::cout << it->first << " => " << it->second << "\n";
    }
	this->data_base = data;
    // test print
	/*
    for (std::map<std::string,float>::iterator it = data_base.begin(); it != data_base.end(); ++it)
        std::cout << it->first << " => " << it->second << "\n";
	*/
	return true;
}

void	BitcoinExchange::exchange(const std::string &input_file) {
	std::ifstream input_data(input_file);
	if (!input_data.is_open()) {
    	std::cerr << "Failed to create file\n";
	}

	if (data_base.size() == 0)
		throw("Error");
	
	std::string line;	
	// to skip first line as it is header
	if (!std::getline(input_data, line))
        throw ("Error: empty file");
	
	while (std::getline(input_data, line)) {
		std::stringstream ss(line);
		std::string date, valueStr;

		// mirar si encaja
		if (!std::getline(ss, date, '|') || !std::getline(ss, valueStr)) {
            std::cerr << "Bad input => " << line << "\n";
            continue;
        }

		if (!date.empty() && date.back() == ' ')
    		date = date.substr(0, date.size() - 1);
		if (!valueStr.empty() && valueStr.front() == ' ')
    		valueStr = valueStr.substr(1, valueStr.size());
        if (!valid_date_format(date)) {
			std::cerr << "Invalid data: |" << date << "|" << "\n";
			continue;
		}
		if (!valid_value(valueStr, 0)) 
		{
            std::cerr << "Invalid value string: |" << valueStr << "|" << "\n";
            continue;
        }
		if (!this->data_base[date])
		{
			std::map<std::string, float>::iterator it = data_base.lower_bound(date);
			if (it == data_base.begin()){
				std::cerr << "Invalid data: " << date << "" << "\n";
				continue;
			}
			date = (--it)->first;
		}
		std::cout << date << " => " << this->data_base[date]* atof(valueStr.c_str()) << std::endl;
	}

    input_data.close();
	return;
}


// --------------------------------------- Non-class functions --------------------------------------

bool csv_extension(const std::string &filename) {
	if (filename.size() < 5)
		return false;
    std::string::size_type	pos = filename.rfind('.');
    if (pos == std::string::npos)
        return false;
	if (filename.substr(pos) == ".csv")
		return true;
    return false;
}

bool	valid_date_format(std::string &date) {
	if (date.size() != 10)
		return false;
	if (date[4] != '-' || date[7] != '-')
		return false;

	//year
	if (!isdigit(date[0]) || !isdigit(date[1]) || !isdigit(date[2]) || !isdigit(date[3]))
		return false;

	//month
	if (!isdigit(date[5]) || !isdigit(date[6]))
		return false;
	int month = (date[5] - '0') * 10 + (date[6] - '0');
    if (month < 1 || month > 12)
		return false;
	
	//day
	if (!isdigit(date[8]) || date[8] > '3' || !isdigit(date[9]) || date[5] > '2')
		return false;
    int day = (date[8] - '0') * 10 + (date[9] - '0');
    if (day < 1 || day > 31)
		return false;
	
	//month-day relationship, not 4 year account for february
	if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
        return false;
    if (month == 2 && day > 29)
        return false;

	return true;
}

bool	valid_value(std::string &value, int flag) {
	if (value.size() == 0)
		return false;
	int		dot = 0;
	bool	has_digit = false;
	size_t	i = 0;

	if (value[0] == '+')
		i++;
	for ( ; i < value.size(); i++) {
		if (!isdigit(value[i]) && value[i] != '.')
			return false;
		 if (isdigit(value[i]))
            has_digit = true;
		if (value[i] == '.')
			dot++;
	}

	if ( dot > 1 || !has_digit)
		return false;

	double num = atof(value.c_str());
	if (num > 1000 && flag == 0) 
		return false;
	return true;
}
