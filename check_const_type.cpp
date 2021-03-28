#include<iostream>
using namespace std;


int main(){

	int a = 10;
	const int *cia = &a;
	
	int * const ica = &a;

	//*cip = 12; // error! 
	//ica = &a; // error!

	return 0;
}


