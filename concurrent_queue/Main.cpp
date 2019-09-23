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

#include <vld.h>
#include <mutex>


#pragma warning(disable : 4324)

class Thrower
{
public:
	Thrower() = default;
	Thrower(uint32_t aCount) : count(aCount){}
	Thrower& operator=(Thrower&&) = delete;
	Thrower& operator=(const Thrower& aOther)
	{
		count = aOther.count;
#ifdef CQ_ENABLE_EXCEPTIONHANDLING
		if (!--throwTarget) {
			throwTarget = rand() % 5000;
			throw std::runtime_error("Test");
		}
#endif
		return *this;
	}
	Thrower& operator+=(uint32_t aCount)
	{
		count += aCount;
		return *this;
	}

	uint32_t count = 0;
#ifdef CQ_ENABLE_EXCEPTIONHANDLING
	uint32_t throwTarget = rand() % 5000;
#endif
};
template <class T>
class tracking_allocator : public std::allocator<T>
{
public:
	tracking_allocator() = default;

	T* allocate(std::size_t count) {
		ourAllocated += count * sizeof(T);
		mtx.lock();
		std::cout << "allocated " << count * sizeof(T) <<"                 " << " this makes the new value " << ourAllocated << std::endl;
		mtx.unlock();
		return std::allocator<T>::allocate(count);
	}
	void deallocate(T* obj, std::size_t count) {
		ourAllocated -= count * sizeof(T);
		mtx.lock();
		std::cout << "deallocated " << count * sizeof(T) << "                 " << " this makes the new value " << ourAllocated << std::endl;

		mtx.unlock();
		std::allocator<T>::deallocate(obj, count);
	}
	static std::mutex mtx;
	static std::atomic<int64_t> ourAllocated;
};
template <class Allocator>
void TestRun(uint32_t aRuns, Allocator& alloc)
{
	aRuns;
	Tester<Thrower, Allocator>* tester = new Tester<Thrower, Allocator>(alloc);

	double result =  tester->ExecuteConcurrent(aRuns);

	delete tester;

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


	std::cout << "Post run delete the current allocated value is " << tracking_allocator<uint8_t>::ourAllocated << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(1));
}
template <class T>
std::mutex tracking_allocator<T>::mtx;
template <class T>
std::atomic<int64_t> tracking_allocator<T>::ourAllocated(0LL);

int main()
{
	tracking_allocator<uint8_t> alloc;

		for (uint32_t i = 0; i < 4; ++i)
		{
	#ifdef CQ_ENABLE_EXCEPTIONHANDLING
#ifdef NDEBUG
			uint32_t runs(1000);
#else
			uint32_t runs(100);
#endif
	#else
			#ifdef NDEBUG
			uint32_t runs(100000);
#else
			uint32_t runs(1000);
#endif
	#endif
		
			TestRun(runs, alloc);
		}

	return 0;
}
