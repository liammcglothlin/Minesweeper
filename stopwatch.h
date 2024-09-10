#include <iostream>
#include <chrono>
#include <thread>
class Stopwatch {
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;

public:
    void start() {
        start_time = std::chrono::high_resolution_clock::now();
    }

    void stop() {
        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time);
        std::cout << "Elapsed time: " << duration.count() << " milliseconds" << std::endl;
    }

    std::chrono::seconds elapsed() const {
        auto end_time = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time);
    }
};

