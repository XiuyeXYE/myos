//
// Created by xiuye on 4/2/21.
//

//#include<iostream>
#include <cstring>

using namespace std;

template<typename T>
T const &max(T const &a, T const &b) {
//    cout << "max 2 T const&"  <<endl;
    return b < a ? a : b;
}

char const *max(char const *a, char const *b) {
//    cout << "max 2 char const*" << endl;
    return ::strcmp(b, a) < 0 ? a : b;
}

template<typename T>
T const &max(T const &a, T const &b, T const &c) {
//    cout << "max 3" << endl;
    return max(max(a, b), c);
}


int main() {

    auto m1 = ::max(7, 42, 68);
    char const *s1 = "ABCD";
    char const *s2 = "EDad";
    char const *s3 = "vsdfa";

    auto m2 = ::max(s1, s2, s3);

    return 0;
}