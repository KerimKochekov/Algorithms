#include "bits/stdc++.h"
using namespace std;
int main(){
	mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<unsigned long long> dis(1, 123123123);
	for(int i=0;i<100;i++)
		cout<<dis(rng)<<endl;
	return 0;
}
