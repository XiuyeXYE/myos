#include<iostream>
using namespace std;

#define str(type) #type
#define sz(type) cout<< str(type) << ":" << sizeof(type) << "B"<< endl; 

int main(){

	sz(void);
	
	
	sz(char);
	sz(unsigned char);
	sz(short);
	sz(unsigned short);
	sz(int);
	sz(unsigned int);
	sz(long);
	sz(unsigned long);
	sz(int long);
	sz(unsigned int long);
	sz(long long);
	sz(unsigned long long);
	
	sz(float);
	sz(double);
	sz(long double);
	
	return 0;
}
