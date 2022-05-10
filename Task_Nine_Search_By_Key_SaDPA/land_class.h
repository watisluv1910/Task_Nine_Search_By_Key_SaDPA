#ifndef LAND_CLASS_H
#define LAND_CLASS_H

#include "landplot_struct.h"
#include "address_struct.h"

class Land
{
public:

	// Parametrized constructor that initializes array
	Land(size_t size) : size_(size), data_(new landplot[size_]) {};

	size_t get_size() { return size_; };
	landplot* get_data() { return data_; };

	bool FillData(const size_t& new_size);

	void SortData();
private:

	size_t size_;
	landplot* data_;

	void Resize(const size_t& new_size);

	size_t GenerateUniqueNumber();
	address GenerateUniqueAddress();
};

#endif