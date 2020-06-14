#include <bits/stdc++.h>
using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int main(){
    int pos = uniform_int_distribution<int>(1,n)(rng);
    printf("%d\n",pos);
    return 0;
}
