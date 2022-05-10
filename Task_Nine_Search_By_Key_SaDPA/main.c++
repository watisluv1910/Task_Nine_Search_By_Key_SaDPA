#include "land_class.h"
#include "landplot_struct.h"

#include <chrono>
#include <time.h>

size_t min(const size_t x, const size_t y);
inline void OutputMenu(const size_t& current_key);
inline void OutputAddress(const address& found_address);
size_t UpdateKey(Land& land, const size_t& current_key);

size_t LinearSearch(Land& land, const size_t& required_key, 
	std::chrono::steady_clock::time_point& begin, 
	std::chrono::steady_clock::time_point& end);

size_t BarierSearch(Land& land, const size_t& required_key, 
	std::chrono::steady_clock::time_point& begin, 
	std::chrono::steady_clock::time_point& end);

size_t FibonaccianSearch(Land land, const size_t& required_key, 
	std::chrono::steady_clock::time_point& begin, 
	std::chrono::steady_clock::time_point& end);

int main()
{
	srand(time(0));

	size_t current_key = 0;

	OutputMenu(current_key);

	std::cout << "\nYour choise is:\n";

	unsigned path = 0; // Menu navigation variable
	std::cin >> path;

	// cin.clear and cin.ignore are used to prevent fake input:
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<int>::max(), '\n');

	// Timestamp for the start of sorting function (zero value by default)
	auto begin = std::chrono::steady_clock::time_point();

	// Timestamp for the end of sorting function (zero value by default)
	auto end = std::chrono::steady_clock::time_point();

	Land land(0); // Object of Land class

	while (path)
	{
		if (path == 1) // Filling the array and initializing the key
		{
			std::cout << "\nEnter the length of the array:\n";
			size_t array_size = 0;
			std::cin >> array_size;

			if (!land.FillData(array_size))
			{
				std::cerr << "\nError (1): Unacceptable array size.\n"; // Error 1
				break;
			}

			current_key = UpdateKey(land, current_key);
		}
		else if (path == 2) // Updating the key
		{
			current_key = UpdateKey(land, current_key);

			if (!current_key)
			{
				std::cerr << "\nError (2): Key is not set.\n"; // Error 2
			}
		}
		else if (path >= 3 && path <= 5) // Searching
		{
			if (!current_key)
			{
				std::cerr << "\nError (2): Key is not set.\n"; // Error 2
				break;
			}

			size_t found_index;

			switch (path)
			{
			case 3:

				found_index = LinearSearch(land, current_key, begin, end);
				break;
			case 4:

				found_index = BarierSearch(land, current_key, begin, end);
				break;
			case 5:

				found_index = FibonaccianSearch(land, current_key, begin, end);			
				break;
			default:

				break;
			}
			
			if (found_index == std::numeric_limits<size_t>::max())
			{
				std::cerr << "\nError (3): Required landplot was not found.\n"; // Error 3
				break;
			}

			// Calculation of the final difference between 
			// the start and end points of the time interval
			auto elapsed_ms = 
				std::chrono::duration_cast<std::chrono::microseconds>(end - begin);

			std::cout << "\nThe sorting time is: " 
				<< elapsed_ms.count() << " microseconds.\n";

			OutputAddress(land.get_data()[found_index].address);
		}
		else
		{
			std::cerr << "\nError (0): Wrong path entered.\n"; // Error 0
		}

		system("pause");
		system("cls"); // clear screen

		OutputMenu(current_key);

		// Next menu navigation step:
		std::cout << "\nYour choise is:\n";
		std::cin >> path;

		// cin.clear and cin.ignore are used to prevent fake input
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<int>::max(), '\n');
	}

	return 0;
}

// Utility function to find minimum of two elements
size_t min(const size_t x, const size_t y) { return (x <= y) ? x : y; }

inline void OutputMenu(const size_t& current_key)
{
	std::cout << "Practical task num.9\nIKBO-03-21 Nasevich V.V.\n"
		"Variant num. 19.\n\nMenu:\n"
		"1)Enter <1> to fill the array.\n"
		"2)Enter <2> to update the key.\n"
		"3)Enter <3> to do a linear search.\n"
		"4)Enter <4> to do a sentinel search.\n"
		"5)Enter <5> to do a Fibonacci search.\n"
		"6)Enter <0> to end the programm.\n";

	if (current_key)
	{
		std::cout << "\nCurrent key is the number: " << current_key << ".\n";
	}
}

inline void OutputAddress(const address& found_address)
{
	std::cout << "\nLandplot data:";

	std::cout << "\n State: " << found_address.state << "."
		<< "\n City: " << found_address.city << "."
		<< "\n Street: " << found_address.street << "."
		<< "\n Zipcode: " << found_address.zip_code << "." << "\n\n";
}

size_t UpdateKey(Land& land, const size_t& current_key)
{
	if (land.get_size() < 2) { return 0; }
	
	size_t random_index = rand() % land.get_size();

	if (land.get_data()[random_index].number == current_key)
	{
		return UpdateKey(land, current_key);
	}

	return land.get_data()[random_index].number;
}

size_t LinearSearch(Land& land, const size_t& required_key, 
	std::chrono::steady_clock::time_point& begin, 
	std::chrono::steady_clock::time_point& end)
{
	// Fixing a begin point in time:
	begin = std::chrono::steady_clock::now();

	for (size_t i = 0; i < land.get_size(); i++)
	{
		if (land.get_data()[i].number == required_key)
		{
			// Fixing an end point in time:
			end = std::chrono::steady_clock::now();

			return i;
		}
	}

	// Fixing an end point in time:
	end = std::chrono::steady_clock::now();

	return std::numeric_limits<size_t>::max();
}

size_t BarierSearch(Land& land, const size_t& required_key,
	std::chrono::steady_clock::time_point& begin,
	std::chrono::steady_clock::time_point& end)
{
	// Explanation:
	// Here the idea is to reduce the number of comparisons 
	// required to find an element in a list. 
	// Here we replace the last element of the list with
	// the search element itself and run a while loop to see 
	// if there exists any copy of the search element in the list
	// and quit the loop as soon as we find the search element.

	// Fixing a begin point in time:
	begin = std::chrono::steady_clock::now();

	size_t i = 0;

	for (; land.get_data()[i].number != required_key; i++) {}

	if (i != land.get_size() - 1)
	{
		// Fixing an end point in time:
		end = std::chrono::steady_clock::now();

		return i;
	}

	// Fixing an end point in time:
	end = std::chrono::steady_clock::now();

	return std::numeric_limits<size_t>::max();
}

size_t FibonaccianSearch(Land land, const size_t& required_key,
	std::chrono::steady_clock::time_point& begin,
	std::chrono::steady_clock::time_point& end)
{
	// Explanation:
	// The idea is to first find the smallest Fibonacci number that 
	// is greater than or equal to the length of the given array. 
	// Let the found Fibonacci number be fib (m’th Fibonacci number).
	// We use (m-2)’th Fibonacci number as the index (If it is a valid index).
	// Let (m-2)’th Fibonacci Number be i, we compare arr[i] with x, 
	// if x is same, we return i. 
	// Else if x is greater, we recur for subarray after i, 
	// else we recur for subarray before i.

	land.SortData(); // Searching method works only with data, sorted ascending

	// Fixing a begin point in time:
	begin = std::chrono::steady_clock::now();

	// Initializing Fibonacci numbers:
	int second_priv_fib = 0; // (m-2)'th Fibonacci number
	int first_prev_fib = 1; // (m-1)'th Fibonacci number
	int current_fib = second_priv_fib + first_prev_fib; // m'th Fibonacci number

	// Fitting the current_fib to the size of the array (greater of equal):
	while (current_fib < land.get_size()) 
	{
		// Shifting to the next level:
		second_priv_fib = first_prev_fib;
		first_prev_fib = current_fib;
		current_fib = second_priv_fib + first_prev_fib;
	}

	int offset = -1; // Marks the eliminated range from the front

	// While the array has elements to be inspected:
	while (current_fib > 1)
	{
		// The last element of the range covered by second_priv_fib
		size_t i = min(static_cast<size_t>(offset + second_priv_fib), land.get_size() - 1);

		// If required_key is less than the value at index second_priv_fib,
		// cutting the subarray array from offset to i:
		if (land.get_data()[i].number < required_key)
		{
			// Shifting to the previous level:
			current_fib = first_prev_fib;
			first_prev_fib = second_priv_fib;
			second_priv_fib = current_fib - first_prev_fib;

			offset = i;
		}
		// If required_key is greater than the value at index second_priv_fib,
		// cutting the subarray after i + 1:
		else if (land.get_data()[i].number > required_key)
		{
			current_fib = second_priv_fib;
			first_prev_fib -= second_priv_fib;
			second_priv_fib = current_fib - first_prev_fib;
		}
		else // Element is found:
		{
			// Fixing an end point in time:
			end = std::chrono::steady_clock::now();

			return i;
		}
	}

	// Comparing the last element with required_key:
	if (first_prev_fib && land.get_data()[offset + 1].number == required_key)
	{
		// Fixing an end point in time:
		end = std::chrono::steady_clock::now();

		return static_cast<size_t>(offset + 1);
	}

	// Fixing an end point in time:
	end = std::chrono::steady_clock::now();

	// Element is not found:
	return std::numeric_limits<size_t>::max();
}