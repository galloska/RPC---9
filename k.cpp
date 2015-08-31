#include <bits/stdc++.h>

using namespace std;

char cad[1005];

bool Primo(long long n){
	if(n==1) return false;
	if(n==2) return true;
	if(n%2==0) return false;
	long long aux = sqrt(n);
	for(int i=3;i<=aux;i+=2)
		if(n%i==0)
			return false;
	return true;
}

int main(){
	//criba(10000001);
	long long n;
	scanf("\n%s",cad);
	bool flag = true;
	n = 0;
	for(int i=0;cad[i];i++)
		n = cad[i] - 48 + n*10;
	flag = min( flag , Primo( n ) );
	if(!flag){
		printf("no\n");
		return 0;
	}
	for(int i=0;cad[i];i++){
		if(cad[i]=='3' || cad[i]=='7' || cad[i]=='4') flag = false;
		if(cad[i]=='6')
			cad[i] = '9';
		else if(cad[i]=='9')
			cad[i] = '6';
	}
	if(!flag){
		printf("no\n");
		return 0;
	}
	n = 0;
	reverse( cad , cad + strlen(cad) );
	for(int i=0;cad[i];i++)
		n = cad[i] - 48 + n*10;
	flag = min( flag , Primo( n ) );
	if(flag && n!=1) printf("yes\n");
	else printf("no\n");
	return 0;
}
