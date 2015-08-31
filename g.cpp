#include <bits/stdc++.h>

using namespace std;

int num[100005];

int main(){
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		scanf("%d",&num[i]);
	bool flag = true;
	for(int i=0;i<n;i++)
		for(int j=i+1;j<n;j++)
			if(num[j]-num[i]<0)
				flag = false;
	if(flag) printf("yes\n");
	else printf("no\n");
	return 0;
}
