//Faiz Ahmed

// This code includes C++ libraries (iostream, set, mutex, thread, vector, chrono, algorithm, atomic, and random), 
// defines some constants for the program (NUM_SERVANTS, NUM_PRESENTS, and EMPTY_BAG), 
// and declares a mutex object called bag_mutex.
#include <iostream>
#include <set>
#include <mutex>
#include <thread>
#include <vector>
#include <chrono>
#include <algorithm>
#include <atomic>
#include <random>
using namespace std;
const int NUM_SERVANTS = 4;
const int NUM_PRESENTS = 500000;
const int EMPTY_BAG = -1;

mutex bag_mutex;

class ConcurrentMinotaurList {
private:
    set<int> presents;
    mutex list_mutex;

public:
    void add_present(int tag_number) {
        lock_guard<mutex> lock(list_mutex);
        presents.insert(tag_number);
    }

    bool remove_present(int tag_number) {
        lock_guard<mutex> lock(list_mutex);

        auto it = presents.find(tag_number);
        if (it != presents.end()) {
            presents.erase(it);
            return true;
        }
        return false;
    }

    bool find_present(int tag_number) {
        lock_guard<mutex> lock(list_mutex);

        return presents.count(tag_number);
    }

    size_t present_count() {
        lock_guard<mutex> lock(list_mutex);

        return presents.size();
    }
};

// This is a class definition for ConcurrentMinotaurList, representing the concurrent set that "chains" the presents together. 
// It has a private set variable called "presents", 
// which is accessed only through four member functions (add_present, remove_present, find_present, and present_count). 
// All member functions lock the "list_mutex" variable before accessing or modifying the presents set.

void servant_tasks(ConcurrentMinotaurList &chain, vector<int> &bag, atomic<int> &count, atomic<int> &cards_written) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 3);

    while (count.load() > 0) {
        int tag = EMPTY_BAG;

        {
            lock_guard<mutex> lock_bag(bag_mutex);
            if (count.load() > 0){
                tag = bag[count-1];
                count--;
            }
        }

        if (tag != EMPTY_BAG) {
            if (!chain.find_present(tag)) {
                chain.add_present(tag);
            }
            if (chain.remove_present(tag)) {
                cards_written++;
            }
        }
    }
}

// This is the main function executed by each thread (servant). 
// It takes in a ConcurrentMinotaurList object, a vector representing the bag of presents, 
// and two atomic integer variables (count and cards_written). 
// Inside the function, a random tag number is picked from the bag vector, 
// and if it hasn't already been seen, it is added to the chain. 
// Then, if it was already seen, a thank you card is written for it.
// The while loop runs while there are still tags left in the bag (indicated by the count variable), 
// and it exits when all tags are removed from the bag.

int main() {
    ConcurrentMinotaurList chain;
    vector<thread> servants;

    vector<int> bag(NUM_PRESENTS);
    iota(bag.begin(), bag.end(), 1);
    random_device rd;
    mt19937 g(rd());
    shuffle(bag.begin(), bag.end(), g);

    atomic<int> count(NUM_PRESENTS);
    atomic<int> cards_written(0);

    auto start = chrono::high_resolution_clock::now();

    for (int i = 0; i < NUM_SERVANTS; ++i) {
        servants.push_back(thread(servant_tasks, ref(chain), ref(bag), ref(count), ref(cards_written)));
    }

    for (int i = 0; i < NUM_SERVANTS; ++i) {
        servants[i].join();
    }

    cout << "Presents in the chain: " << chain.present_count() << endl;
    cout << "Thank you cards written: " << cards_written << endl;

    auto end = chrono::high_resolution_clock::now();
    cout << "Servants completed the tasks in: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms" << endl;

    return 0;
}