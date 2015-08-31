#include <bits/stdc++.h>
#define pii pair<int,int>

using namespace std;
// Definiciones iniciales
typedef pair<int, int> Arista;

const int INF = 1 << 30;
const int MAXN = 10005;

vector<int> grafo[MAXN];

// Maximo emparejamiento en grafo bipartito. Nodos indexados
// de 0 a n - 1. Recibe dos parametros: Un vector con los indices
// del conjunto izquierdo y otro con los indices del derecho.

int pareja[MAXN];
bool visitado[MAXN];

int CaminoIncremental(int u) {
    visitado[u] = true;
    for (int i = 0; i < grafo[u].size(); ++i) {
        int v = grafo[u][i];
        if (pareja[v] == -1) 
            return pareja[v] = u;
        if (visitado[pareja[v]]) continue;
        if (CaminoIncremental(
            pareja[v]) != -1) return pareja[v] = u;
    }
    return -1;
}

vector<int> l;
vector<int> r;

vector<pii> MaxEmparejamientoBipartito() {
    int n = l.size() + r.size();
    fill(pareja, pareja + n, -1);
    for (int i = 0; i < l.size(); ++i) {
        fill(visitado, visitado + n, false);
        CaminoIncremental(l[i]);
    }
    vector<pii> parejas;
    for (int i = 0; i < r.size(); ++i)
        if (pareja[r[i]] != -1) parejas.push_back(
            Arista(pareja[r[i]], r[i]));
    return parejas;
}

bool v[MAXN];

int main(){
	int n,m,a;
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%d",&m);
        l.push_back(i);
        r.push_back(i+n);
		while(m--){
			scanf("%d",&a);
			grafo[i].push_back(a + n);
		}
	}
	printf("%d\n",n - (int)MaxEmparejamientoBipartito().size());
	return 0;
}
