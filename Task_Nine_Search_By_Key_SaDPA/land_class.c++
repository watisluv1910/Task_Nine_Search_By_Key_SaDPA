#include "land_class.h"

#include <random>

bool Land::FillData(const size_t& new_size)
{
	if (new_size < 2) { return false; }

	Resize(new_size);

	for (size_t i = 0; i < size_; i++)
	{
		data_[i].number = GenerateUniqueNumber();
		data_[i].address = GenerateUniqueAddress();
	}

	return true;
}

void Land::SortData()
{
	// This is a Shell sort with displacement divided by 2.

	for (size_t d = size_ / 2; d > 0; d /= 2)
	{
		for (size_t i = d; i < size_; ++i)
		{
			for (int j = i - d; j >= 0 && (data_[j].number > data_[j + d].number); j -= d)
			{
				std::swap(data_[j], data_[j + d]);
			}
		}
	}
}

void Land::Resize(const size_t& new_size)
{
	delete[] data_;

	data_ = new landplot[new_size];

	size_ = new_size;
}

size_t Land::GenerateUniqueNumber()
{
	std::random_device randomizer;
	std::uniform_int_distribution<size_t> spread(1000000, 10000000);

	size_t new_number = spread(randomizer);

	for (size_t i = 0; i < size_; i++)
	{
		if (data_[i].number == new_number)
		{
			return GenerateUniqueNumber();
		}
	}

	return new_number;
}

address Land::GenerateUniqueAddress()
{
	std::vector<std::string>
		states_list = { "Virginia", "Nevada", "Texas", "Florida", "Ohio" };

	std::vector<std::string>
		cities_list = { "Alexandria", "Fernley", "Flat", "Miami Springs", "Metamora" };

	std::vector<std::string> streets_list = {
		"Ashford Drive", "Sheila Lane",
		"Sussex Court", "Steve Hunt Road", "Still Street"
	};

	address temp_address;

	std::random_device randomizer;
	std::uniform_int_distribution<int> spread(10000, 99999);

	int new_zip_code = spread(randomizer);

	temp_address.zip_code = new_zip_code;

	temp_address.state = states_list.at(rand() % 5);

	temp_address.city = cities_list.at(rand() % 5);

	temp_address.street = streets_list.at(rand() % 5);

	return temp_address;
}
