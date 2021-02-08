#include "bits/stdc++.h"

const int LOG=30;
int basis[LOG];
void add(int x){
	for(int i=LOG-1;i>=0;i--){
		if(!(x>>i&1))continue;
		if(!basis[i]){basis[i]=x;return;}
		x^=basis[i];
	}
}
int main(){
	int n,x;
    scanf("%d",&n);
	while(n--)
		scanf("%d",&x),add(x);
	for(int i=LOG-1;i>=0;i--)
		for(int j=i+1;j<LOG;j++)
			if(basis[j]>>i&1)
				basis[j]^=basis[i];
	return 0;
}
