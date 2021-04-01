//
// Created by xiuye on 4/1/21.
//

#include <iostream>

using namespace std;

class A {
public:
    virtual void f();
};

void A::f() {
    cout << "A::f" << endl;
}

class B : public A {
public:
    void f();
};

void B::f() {
    cout << "B::f" << endl;
}


int main() {

    B b;
    //polymorphism
    A &a = b;
    a.f();

    return 0;
}

