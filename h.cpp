#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1005;

string cad,cad2;
bool v[MAXN];
int cont;
vector<int> lista[MAXN];
map<string,int> check;

void dfs(int u){
	v[u] = true;
	cont++;
	for(int i=0;i<lista[u].size();i++){
		int vy = lista[u][i];
		if(!v[vy])
			dfs(vy);
	}
}

int main(){
	int n,m,u=1;
	vector<int> tira;
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>cad>>m;
		//cout<<cad<<" "<<m<<endl;
		if(check.find(cad)==check.end()) check[cad] = u++;
		string otro = "";
		int k = cad.size() -1;

		while(cad[k]!=':'){
			otro += cad[k];
			k--;
		}
		if(otro=="MARGORP") tira.push_back(check[cad]);
		if(m==0){
			cin.ignore();
			continue;
		}
		while(m--){
			cin>>cad2;
			if(check.find(cad2)==check.end()) check[cad2] = u++;
			lista[ check[cad2] ].push_back( check[cad] );
			otro = "";
			k = cad2.size() -1;

			while(cad2[k]!=':'){
				otro += cad2[k];
				k--;
			}
			if(otro=="MARGORP") tira.push_back(check[cad]);
		}
	}

	for(int i=0;i<tira.size();i++)
		if(!v[tira[i]])
			dfs(tira[i]);
	
	printf("%d\n",(int)check.size() - cont);
	return 0;
}
