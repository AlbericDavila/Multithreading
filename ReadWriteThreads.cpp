/*
* Controlling thread execution within a set time.
*/

#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <vector>
#include <time.h>
#include <algorithm>

using namespace std;

condition_variable data_cond;
mutex mut;

atomic<int> readers;

void reader(int id) {
	unique_lock<mutex> lk(mut);

	cout << id;
	++readers;

	lk.unlock();

	this_thread::sleep_for(chrono::milliseconds(10));

	--readers;
	cout << id;

	data_cond.notify_all();
}

void writer() {
	unique_lock<std::mutex> lk(mut);

	data_cond.wait(lk, [] {
		return readers == 0;
	});

	cout << endl;
	this_thread::sleep_for(chrono::milliseconds(1000));
	cout << "Hello ";
	this_thread::sleep_for(chrono::milliseconds(10));
	cout << "World ";
	this_thread::sleep_for(chrono::milliseconds(1000));
	cout << "in a ";
	this_thread::sleep_for(chrono::milliseconds(10));
	cout << "timely ";
	this_thread::sleep_for(chrono::milliseconds(1000));
	cout << "manner.";
	this_thread::sleep_for(chrono::milliseconds(10));
	cout << std::endl;
}

int main() {
	vector<thread> threads;

	srand(time(NULL));

	for (int i = 0; i<10; ++i)
		if (rand() % 2)
			threads.push_back(thread(reader, i));
		else
			threads.push_back(thread(writer));

	for_each(threads.begin(), threads.end(), mem_fn(&thread::join));

	return 0;
}