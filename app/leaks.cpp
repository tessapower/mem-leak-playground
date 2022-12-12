#include "leaks.h"

#include <iostream>
#include <memory>
#include <vector>

// Leak category 1: new[] without delete[]
void missing_delete() {
    int* arr = new int[100];
    arr[0] = 42;
    std::cout << "missing_delete: allocated int[100], never freed\n";
    // no delete[] arr;
}

// Leak category 2: pointer reassignment loses the original allocation
void lost_pointer() {
    int* p = new int(1);
    int* q = new int(2);
    p = q;  // original *p is now leaked
    std::cout << "lost_pointer: reassigned pointer, original allocation leaked\n";
    delete p;
}

// Leak category 3: early return skips cleanup
void error_path() {
    int* data = new int[50];
    bool error = true;  // simulate an error condition
    if (error) {
        std::cout << "error_path: early return skipped delete[]\n";
        return;  // leak!
    }
    delete[] data;
}

// Leak category 4: clearing a vector of raw pointers without deleting elements
void container_of_raw_ptrs() {
    std::vector<int*> vec;
    for (int i = 0; i < 5; ++i) {
        vec.push_back(new int(i));
    }
    std::cout << "container_of_raw_ptrs: cleared vector without deleting elements\n";
    vec.clear();  // pointers gone, memory leaked
}

// Leak category 5: two shared_ptrs forming a reference cycle
struct Node {
    std::shared_ptr<Node> peer;
    ~Node() { std::cout << "  ~Node()\n"; }
};

void circular_shared_ptr() {
    auto a = std::make_shared<Node>();
    auto b = std::make_shared<Node>();
    a->peer = b;
    b->peer = a;
    std::cout << "circular_shared_ptr: two shared_ptrs point at each other (ref count never hits 0)\n";
    // a and b go out of scope but ref counts stay at 1 — leaked
}
