// ThreadSafeConsumptionQueue.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <vector>
#include <iostream>
#include "Tester.h"
#include <string>
//#include <vld.h>

class Thrower
{
public:

	Thrower& operator=(Thrower&&) = delete;
	Thrower& operator=(const Thrower& aOther)
	{
		count = aOther.count;
		if (false) {
			throw std::runtime_error("Something");
		}
		return *this;
	}

	uint32_t count = 0;
};
void TestRun(uint32_t aRuns)
{
	Tester<int>* tester = new Tester<int>();

	double result = tester->ExecuteConcurrent(aRuns);

#ifdef _DEBUG
	std::string config("Debug mode");
#else
	std::string config("Release mode");
#endif
	std::string str = std::string(
		std::string("Executed a total of ") +
		std::to_string(Writes * aRuns) +
		std::string(" read & write operations") +
		std::string(" averaging ") +
		std::to_string(result / static_cast<double>(aRuns)) +
		std::string("s per " + std::to_string(Writes) + " read & write operations with a total time of ") +
		std::to_string(result) +
		std::string("s in ") +
		config);

	std::cout << str << std::endl;

	delete tester;
}
int main()
{
	for (uint32_t i = 0; i < 200; ++i)
	{
		uint32_t runs(100000);

		TestRun(runs);
	}

	return 0;
}

