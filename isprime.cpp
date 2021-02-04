#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
typedef __int128 bint;
ll mul(bint a,bint b,ll c){
	return (a*b)%c;
}
ll mpow(ll n, ll p, ll m) {
	if(!p) return 1; 
	else if(p & 1) return mul(n , mpow(n, p-1, m), m);
	ll v = mpow(n, p/2, m); 
	return mul(v,v,m);
}
ll gcd(ll x,ll y){
	if(!y)return x;
	return gcd(y,x%y);	
}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<unsigned long long> dis(0, ll(2e18));
int isprime(ll n){
	if(n==1)return 0;
	if(n==2)return 1;
	if(n%2==0) return 0;
	for(ll i=3;i*i*i<=n;i+=3) if(n%i==0) return 0;
	for(int it=0;it<(int)1e5;++it){
		ll i = dis(rng)%(n-1)+1;
		if(gcd(i,n)!=1)return 0;
		if(mpow(i,n-1,n)!=1)return 0;
	}return 1;
}
int main(){
	printf("%d\n",isprime(4));
	printf("%d\n",isprime(5));
	printf("%d\n",isprime(17));
	printf("%d\n",isprime(1000000016000000063LL));
}
