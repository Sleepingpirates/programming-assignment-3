# programming-assignment-3

# Problem 1: The Birthday Presents Party

The Minotaur’s birthday party was a success. The Minotaur received a lot of presents from his guests. The next day he decided to sort all of his presents and start writing “Thank you” cards. Every present had a tag with a unique number that was associated with the guest who gave it. Initially all of the presents were thrown into a large bag with no particular order. The Minotaur wanted to take the presents from this unordered bag and create a chain of presents hooked to each other with special links (similar to storing elements in a linked-list). In this chain (linked-list) all of the presents had to be ordered according to their tag numbers in increasing order. The Minotaur asked 4 of his servants to help him with creating the chain of presents and writing the cards to his guests. Each servant would do one of three actions in no particular order: 1. Take a present from the unordered bag and add it to the chain in the correct location by hooking it to the

predecessor’s link. The servant also had to make sure that the newly added present is also linked with the next present in the chain. 2. Write a “Thank you” card to a guest and remove the present from the chain. To do so, a servant had to unlink the gift from its predecessor and make sure to connect the predecessor’s link with the next gift in the chain. 3. Per the Minotaur’s request, check whether a gift with a particular tag was present in the chain or not; without adding or removing a new gift, a servant would scan through the chain and check whether a gift with a particular tag is already added to the ordered chain of gifts or not. As the Minotaur was impatient to get this task done quickly, he instructed his servants not to wait until all of the presents from the
unordered bag are placed in the chain of linked and ordered presents. Instead, every servant was asked to alternate adding gifts to the ordered chain and writing “Thank you” cards. The servants were asked not to stop or even take a break until the task of writing cards to all of the Minotaur’s guests was complete. After spending an entire day on this task the bag of unordered presents and the chain of ordered presents were both finally empty! Unfortunately, the servants realized at the end of the day that they had more presents than “Thank you” notes. What could have gone wrong? Can we help the Minotaur and his servants improve their strategy for writing “Thank you” notes? Design and implement a concurrent linked-list that can help the Minotaur’s 4 servants with this task. In your test, simulate this concurrent “Thank you” card writing scenario by dedicating 1 thread per servant and assuming that the Minotaur received 500,000
presents from his guests.

# Run Instructions:

1. Clone the repository from GitHub:
   `git clone https://github.com/sleepingpirates/programming-assignment-3.git`
2. Navigate into the directory with the code:
   `cd programming-assignment-3`
3. Compile the program:
   `g++ -std=c++11 -pthread problem1.cpp -o pb1`
4. Run the program:
   `./pb1`

# Proof of Correctness:

The ConcurrentMinotaurList class ensures that the linked list is thread-safe, and that no two threads can modify or access the same variable simultaneously. The program guarantees that the presents are added to the linked list in increasing order, and that a thank you card for each present is written only once.

# Experimental Evaluation:

The program uses multithreading to simulate four servants processing the presents. The use of atomic variables ensures that multiple threads can safely access shared data, and the mutex objects protect the shared data from simultaneous modification. The total number of presents in the chain and the number of thank you cards written are outputted at the end of the simulation. The efficiency of the program depends on the number of presents and the number of threads running.

# Problem 2: Atmospheric Temperature Reading Module

You are tasked with the design of the module responsible for measuring the atmospheric temperature of the next generation Mars Rover, equipped with a multi-core CPU and 8 temperature sensors. The sensors are responsible for collecting temperature readings at regular intervals and storing them in shared memory space. The atmospheric temperature module has to compile a report at the end of every hour, comprising the top 5 highest temperatures recorded for that hour, the top 5 lowest temperatures recorded for that hour, and the 10-minute interval of time when the largest temperature difference was observed. The data storage and retrieval of the shared memory region must be carefully handled, as we do not want to delay a sensor and miss the interval of time when it is supposed to conduct temperature reading. Design and implement a solution using 8 threads that will offer a solution for this task. Assume that the temperature readings are taken every 1 minute. In your solution, simulate the operation of the temperature reading sensor by generating a random number from -100F to 70F at every reading. In your report, discuss the efficiency, correctness, and progress guarantee of your program.

# Run Instructions:

1. Clone the repository from GitHub:
   `git clone https://github.com/sleepingpirates/programming-assignment-3.git`
2. Navigate into the directory with the code:
   `cd programming-assignment-3`
3. Compile the program:
   `g++ -std=c++11 -pthread problem2.cpp -o pb2`
4. Run the program:
   `./pb2`

# Proof of Correctness:

The solution guarantees that the atmospheric temperature module compiles a report at the end of every hour, comprising the top 5 highest temperatures recorded for that hour, the top 5 lowest temperatures recorded for that hour, and the 10-minute interval of time when the largest temperature difference was observed. To achieve this, the program creates 8 threads, one for each temperature sensor, which collect temperature readings and store them in a shared memory space. The program then compiles a report by iterating over the temperature readings for each time interval, finding the highest and lowest temperatures and the largest temperature difference in the last 10 minutes. The program correctly sorts the highest and lowest temperatures in descending and ascending order respectively and prints the report with the expected format.

# Experimental Evaluation, Efficiency:

The program efficiently simulates the operation of the temperature sensors using threads and shared memory space. To avoid race conditions or deadlocks, the program uses a mutex object to control access to shared data. The program generates random numbers to simulate temperature readings and compiles the report after all sensors have completed their readings. The program runs efficiently and completes execution in a reasonable amount of time, given the number of temperature sensors and the number of minutes of readings. The correctness of the program is tested and verified with different inputs for the number of sensors, and number of temperature readings. The program works as expected when the number of readings and sensors is increased.
