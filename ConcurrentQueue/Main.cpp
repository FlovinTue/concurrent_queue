// ThreadSafeConsumptionQueue.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <vector>
#include <iostream>
#include "Tester.h"
#include <string>
//#include <vld.h>

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
	for (uint32_t i = 0; i < 800; ++i)
	{
		uint32_t runs(500);

		TestRun(runs);
	}

	return 0;
}

