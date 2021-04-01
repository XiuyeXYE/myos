//
// Created by xiuye on 4/1/21.
//
#include<iostream>

using namespace std;

class A {
    int a{200};
    int b{100};
public:
    virtual void f();
};

void A::f() {
    cout << "a = " << a
         << ";b = " << b
         << endl;
}

int main() {

    A a;
    a.f();
    //check object layout
    size_t *p = (size_t * ) & a;
    //two members
    size_t *pm = p + 2;
    //one vptr
    size_t *ptr_table = p + 3;
    //get call f by offset table
    //1.rtti
    //2.deconstructor
    //3.void f()
    size_t *f = ptr_table + 2;
    cout << f << hex << endl;
    cout << &A::f << hex << endl;


    return 0;
}
