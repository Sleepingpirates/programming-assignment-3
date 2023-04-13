// Include necessary libraries
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;
// Global data and lock
vector<vector<int>> temperatures(8, vector<int>(60)); // 8 sensors each collecting data for 60 minutes
mutex mtx; // mutex object to handle shared memory space

// Sensor thread function to simulate operation of temperature reading sensor
void sensor_thread(int id) {
    for (int i = 0; i < 60; ++i) {
        // this_thread::sleep_for(chrono::seconds(1));
        int temperature = rand() % 171 - 100; // generate random temperature value between -100F and 70F

        // Lock mutex to prevent other threads from accessing shared memory space
        unique_lock<mutex> lock(mtx);
        temperatures[id][i] = temperature; // store temperature reading in shared memory space
        lock.unlock(); // unlock mutex
    }
}

int main() {
    srand(time(NULL)); // seed random number generator with current time

    vector<thread> threads; // vector to hold threads for each sensor
    for (int i = 0; i < 8; ++i) {
        threads.push_back(thread(sensor_thread, i)); // create thread for each sensor and add to vector
    }
    // Join threads to prevent program from exiting before all threads finish execution
    for (thread &th : threads) {
        th.join();
    }

    // Compile report
    vector<int> highest, lowest;
    int largest_interval_start = 0, largest_interval_end = 0, largest_temperature_diff = -1;

    for (int i = 0; i < 60; ++i) {
        int min_val = INT32_MAX, max_val = INT32_MIN;

        // Iterate over all temperature readings for each time interval
        for (int j = 0; j < 8; ++j) {
            min_val = min(min_val, temperatures[j][i]); // find lowest temperature value for current interval
            max_val = max(max_val, temperatures[j][i]); // find highest temperature value for current interval
        }

        highest.push_back(max_val); // add highest temperature value to vector
        lowest.push_back(min_val); // add lowest temperature value to vector

        if(i >= 10) { // check if interval is at least 10 "minutes" long :P
            int temp_diff = *max_element(highest.end() - 10, highest.end()) - *min_element(lowest.end() - 10, lowest.end()); // find largest temperature difference in last 10 minutes
            if (temp_diff > largest_temperature_diff) { // update largest temperature difference if current is larger
                largest_temperature_diff = temp_diff;
                largest_interval_start = i - 9; // update start of largest interval with temperature difference
                largest_interval_end = i; // update end of largest interval with temperature difference
            }
        }
    }

    sort(highest.rbegin(), highest.rend()); // sort highest temperature values in descending order
    sort(lowest.begin(), lowest.end()); // sort lowest temperature values in ascending order

    // Print report
    cout << "Top 5 Highest Temperatures: ";
    for (int i = 0; i < 5; ++i) {
        cout << highest[i] << " ";
    }
    
    cout << "\nTop 5 Lowest Temperatures: ";
    for (int i = 0; i < 5; ++i) {
        cout << lowest[i] << " ";
    }

    cout << "\n10-minute interval with largest temperature difference: ";
    cout << largest_interval_start << " to " << largest_interval_end << "\n";

    return 0;
}