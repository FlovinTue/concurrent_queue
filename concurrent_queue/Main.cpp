// ThreadSafeConsumptionQueue.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <vector>
#include <iostream>
#include "Tester.h"
#include <string>
#include <random>
#include <functional>
#include <atomic_shared_ptr.h>

#include <vld.h>

#pragma warning(disable : 4324)
//
//class Thrower
//{
//public:
//	Thrower() = default;
//	Thrower(uint32_t aCount) : count(aCount){}
//	Thrower& operator=(Thrower&&) = delete;
//	Thrower& operator=(const Thrower& aOther)
//	{
//		count = aOther.count;
//#ifdef CQ_ENABLE_EXCEPTIONHANDLING
//		if (!--throwTarget) {
//			throwTarget = rand() % 5000;
//			throw std::runtime_error("Test");
//		}
//#endif
//		return *this;
//	}
//	Thrower& operator+=(uint32_t aCount)
//	{
//		count += aCount;
//		return *this;
//	}
//
//	uint32_t count = 0;
//#ifdef CQ_ENABLE_EXCEPTIONHANDLING
//	uint32_t throwTarget = rand() % 5000;
//#endif
//};
//void TestRun(uint32_t aRuns)
//{
//	aRuns;
//	Tester<Thrower>* tester = new Tester<Thrower>();
//
//	double result = tester->ExecuteConcurrent(aRuns);
//
//#ifdef _DEBUG
//	std::string config("Debug mode");
//#else
//	std::string config("Release mode");
//#endif
//	std::string str = std::string(
//		std::string("Executed a total of ") +
//		std::to_string(Writes * aRuns) +
//		std::string(" read & write operations") +
//		std::string(" averaging ") +
//		std::to_string(result / static_cast<double>(aRuns)) +
//		std::string("s per " + std::to_string(Writes) + " read & write operations with a total time of ") +
//		std::to_string(result) +
//		std::string("s in ") +
//		config);
//
//	std::cout << str << std::endl;
//
//	delete tester;
//}

int main()
{
	//	for (uint32_t i = 0; i < 800; ++i)
	//	{
	//#ifdef CQ_ENABLE_EXCEPTIONHANDLING
	//		uint32_t runs(1000);
	//#else
	//		uint32_t runs(100000);
	//#endif
	//	
	//		TestRun(runs);
	//	}

	gdul::concurrent_queue<int> heja;
	heja.push(1);
	
	int out(0);
	heja.try_pop(out);
	

	return 0;
}




//<CustomListItems>
//<Variable Name = "sizeAccumulator" InitialValue = "0" / >
//<Variable Name = "producerIndex" InitialValue = "0" / >
//<Variable Name = "pBuffer" InitialValue = "myDebugView[producerIndex]" / >
//<Loop>
//<Break Condition = "producerIndex == myProducerCount._My_val" / >
//<Loop>
//<Exec>sizeAccumulator += (pBuffer->myPostWriteIterator._My_val - pBuffer->myReadSlot._My_val) < / Exec >
//<Break Condition = "pBuffer->myNext == nullptr" / >
//<Exec>pBuffer = pBuffer->myNext< / Exec>
//< / Loop>
//<Exec>++producerIndex< / Exec>
//<Exec>pBuffer = myDebugView[producerIndex]< / Exec>
//< / Loop>
//<Item Name = "[size]">sizeAccumulator< / Item>
//<Item Name = "[producer_count]">myProducerCount._My_val< / Item>
//< / CustomListItems>