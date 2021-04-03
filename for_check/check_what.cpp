//
// Created by xiuye on 4/3/21.
//
#include <iostream>
#include <thread>

using namespace std;

int main() {

    char table[26];

    for (int i = 0; i < 26; i++) {
        table[i] = 'a' + i;
    }

    for (int i = 0; i < 26; ++i) {
        cout << table[i];
    }
    cout << endl;

    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) {
            this_thread::sleep_for(chrono::seconds(1));
            cout << table[i] << table[j] << endl;
        }
    }
    cout << 26 * 26 << endl;

    return 0;
}

