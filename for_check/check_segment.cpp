//
// Created by xiuye on 3/29/21.
//
#include<iostream>

#define seg(v) __attribute__((section(#v)))

__attribute__((section(".test"))) long a = 100;

seg(.no) long b = 99;

using namespace std;

int main() {

    cout << "a = " << a << endl;

    return 0;
}
