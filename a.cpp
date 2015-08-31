#include <bits/stdc++.h>
#define pii pair<int,int>
#define lli long long int

using namespace std;

const lli MAXN = 20005;
const lli INF = 1e8;

vector<pii> grafo[MAXN];
vector< vector<lli> > res;
lli quiero[MAXN];

vector<lli> Dijkstra(lli o, lli n) {
    vector<lli> dist(n, INF);
    priority_queue<pii, vector<pii>,
             	greater<pii> > pq;
    pq.push(pii(0, o)); dist[o] = 0;
    
    while (!pq.empty()) {
        lli u = pq.top().second;
        lli p = pq.top().first; pq.pop();
        if (dist[u] < p) continue;        
        for (lli i = 0; i <grafo[u].size(); ++i) {
            p = grafo[u][i].second;
            lli v = grafo[u][i].first;
            if (dist[u] + p < dist[v]) {
                dist[v] = dist[u] + p;
                pq.push(pii(dist[v], v));
            }
        }
    }
    return dist;
}

lli p;
bool valid[MAXN];
lli numero[MAXN];
lli mat[20][20];
lli memo[20][ (1<<16) + 5];
lli memo2[20][ (1<<16) + 5][3];
lli t;
lli valor[MAXN];

lli DP(lli actual,lli mask){
	if(mask==(1LL<<p)-1)
		return mat[actual][numero[0]] + valor[numero[0]];
	lli res = 1e8;
	if(memo[actual][mask]!=-1) return memo[actual][mask];

	for(lli i=0;i<p;i++)
		if( !( ( 1<<i )&mask) )
			res = min(res , DP( i , mask|(1<<i) ) + mat[actual][i] + valor[i]);

	return memo[actual][mask] = res;
}

lli DP2(lli actual,lli mask,bool taxi){
	if(mask==(1LL<<p)-1 && taxi) return mat[actual][numero[0]] + valor[numero[0]];
	if(mask==(1LL<<p)-1) return 1e8;
	lli res = 1e8;
	if(memo2[actual][mask][taxi]!=-1) return memo2[actual][mask][taxi];

	for(lli i=0;i<p;i++){
		if( !( ( 1<<i )&mask) && !taxi )
			res = min(res , DP2( i , mask|(1<<i) , true ) + t + valor[i]);
		if(!( (1<<i)&mask ) )
			res = min( res , DP2( i , mask|(1<<i) , taxi ) + mat[actual][i] + valor[i] );
	}

	return memo2[actual][mask][taxi] = res;
}

int main(){
	lli n,m,g,a,b,c,u=0;
	scanf("%lld %lld %lld %lld %lld",&n,&p,&m,&g,&t);

	for(lli i=0;i<p;i++){
		scanf("%lld %lld",&quiero[i],&a);
		valid[quiero[i]] = true;
		numero[quiero[i]] = u++;
		valor[numero[quiero[i]]] = a;
	}

    if(!valid[0]){
        valid[0] = true;
	    numero[0] = u++;
	    valor[numero[0]] = 0;
	    p++;
    }

	for(lli i=0;i<m;i++){
		scanf("%lld %lld %lld",&a,&b,&c);
		grafo[a].push_back(pii(b,c));
		grafo[b].push_back(pii(a,c));
	}

	for(lli i=0;i<p;i++){
		res.push_back( Dijkstra(quiero[i] , n) );
		//printf("Quiero -> %d\n",quiero[i] );
		for(lli j=0;j<res[i].size();j++){
			if(valid[j]){
				//printf("( %d ,%d ) ",j,res[i][j] );
				mat[numero[quiero[i]]][numero[j]] = res[i][j];
			}
		}
		//printf("\n");
	}

	memset(memo,-1LL,sizeof memo);
	
	lli aux = DP( numero[0] , 1LL<<numero[0] );
	if(aux<=g){
		printf("possible without taxi\n");
		return 0;
	}

	memset(memo2,-1LL,sizeof memo2);
	aux = DP2( numero[0] , 1LL<<numero[0] , false );

	if(aux<=g) printf("possible with taxi\n");
	else printf("impossible\n");
	return 0;
}
