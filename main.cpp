#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>

std::mutex mtx; 

void performWork(int id) {
    std::this_thread::sleep_for(std::chrono::milliseconds(200)); 
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << "Task " << id << " is being processed by Thread: " << std::this_thread::get_id() << std::endl;
}

int main() {
    std::vector<std::thread> workers;
    std::cout << "Launching 8 parallel threads..." << std::endl;

    for (int i = 1; i <= 8; ++i) {
        workers.emplace_back(performWork, i);
    }

    for (auto& t : workers) {
        t.join();
    }

    std::cout << "All parallel tasks completed." << std::endl;
    return 0;
}