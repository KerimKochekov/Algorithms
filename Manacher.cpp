#include "bits/stdc++.h"
#define MAXN 100009
using namespace std;
char s[MAXN],tmp[MAXN<<1];
int n,rad[MAXN<<1];
int main(){
  scanf("%s",s+1);
  n=strlen(s+1);
  for(int i=0;i<2*n+1;i++)tmp[i]='#';
	for(int i=0;i<n;i++)tmp[i*2+1]=s[i+1];
	for(int i=0,j=0,k;i<n*2+1;i+=k){
		while(i-j>=0&&i+j<n*2+1&&tmp[i-j]==tmp[i+j])j++;
		rad[i]=j;k=1;
		while(rad[i-k]<rad[i]-k)rad[i+k]=rad[i-k],k++;
		j=max(0,j-k);
	}
  return 0;
}
