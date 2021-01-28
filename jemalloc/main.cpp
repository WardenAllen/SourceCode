
#include <iostream>
#include <map>
#include <thread>
#include <vector>

#include <stdio.h>
#include <pthread.h>
#include <jemalloc/jemalloc.h>

#include "TimeHelper.h"

using namespace std;

extern const uint8_t small_size2bin[];

int main(int argc, const char* argv[])
{
	/*CTimeHelper timer;
	timer.StartTimer();

	Func();

	cout << timer.EndTimer() / 1000 / 1000 << "ms" << endl;*/

	je_malloc(4);



	return 0;
}