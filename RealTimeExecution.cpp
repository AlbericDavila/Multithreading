/*
 * This program blocks theards for a specific real time.
 */

#include <iostream>
#include <iomanip> 
#include <thread> 
#include <chrono>
#include <ctime>
using namespace std;
using std::chrono::system_clock;

int main()
{
	cout << "The id of current thread is " << this_thread::get_id << endl;

	// Sleep while next minute is not reached.

	// Get current time.
	time_t timet = system_clock::to_time_t(system_clock::now());

	// Convert it to tm struct.
	struct tm * time = localtime(&timet);

	cout << "Current time: " << put_time(time, "%X") << '\n';
	cout << "Waiting for the next minute to begin..." << endl;
	time->tm_min++; time->tm_sec = 0;

	// Sleep until next minute is not reached.
	this_thread::sleep_until(system_clock::from_time_t(mktime(time)));
	cout << std::put_time(time, "%X") << " reached!" << endl;

	// Sleep for 5 seconds.
	this_thread::sleep_for(chrono::seconds(5));

	// Get current time.
	timet = system_clock::to_time_t(system_clock::now());

	// Convert it to tm struct.
	time = std::localtime(&timet);
	cout << "Current time: " << put_time(time, "%X") << endl;
}