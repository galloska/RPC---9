#include <stdio.h>
#include <algorithm>

using namespace std;

int altura[105];
int num[10005][105];

int main(){
	int n,m,a,h,w;
	scanf("%d %d",&n,&m);
	scanf("%d %d",&h,&w);
	for(int i=0;i<n;i++)
		for(int j=0;j<h;j++)
			scanf("%d",&num[i][j]);
	
	while(m--){
		for(int i=0;i<h;i++){
			scanf("%d",&a);
			altura[i] = max( altura[i] , a );
		}
	}

	/*for(int i=0;i<h;i++)
		printf("%d ",altura[i]);
	printf("\n");*/

	for(int i=0;i<n;i++){
		for(int j=0;j<h;j++){
			num[i][j] = min( w - altura[j] , num[i][j] );
			if(j!=0) printf(" ");
			printf("%d",num[i][j]);
		}
		printf("\n");
	}
	return 0;
}
