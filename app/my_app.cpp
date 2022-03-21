#include <chrono>
#include <iostream>
#include <thread>

#include <my_lib/my_lib.h>

int main(const int argc, const char* argv[]) {
  std::cout << "starting mem leak" << std::endl;

//  while (true) {
    using namespace std::chrono_literals;
    bool* arr = new bool[1025];
    std::this_thread::sleep_for(10ms);
    delete[] arr;
//  }
}
