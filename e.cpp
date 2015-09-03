#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> pii;
typedef pair<int,pii> psi;

const int MAXN = 10005;
const int INF = 1e8;

vector<psi> aris;
vector<pii> lista[MAXN];
vector< vector<int> > total;

void Dijsktra(int ini,int n){
    vector<int> dist( n , INF );
    priority_queue< pii , vector<pii> , greater<pii> > q;
    dist[ini] = 0;
    q.push( pii( 0 , ini ) );

    while(!q.empty()){
        pii u = q.top();
        q.pop();

        if(u.first>dist[u.second]) continue;

        for(int i=0;i<lista[u.second].size();i++){
            int v = lista[u.second][i].first;
            int d = lista[u.second][i].second;
            if( d + dist[u.second] < dist[v] ){
                dist[v] = dist[u.second] + d;
                q.push( pii( dist[v] , v ) );
            }
        }
    }

    total.push_back(dist);
}

int main(){
    int n,m,k,a,b,c,d,cont = 0;

    scanf("%d %d %d",&n,&m,&k);

    for(int i=0;i<k;i++)
        scanf("%d",&a);

    while(m--){
        scanf("%d %d %d",&a,&b,&c);
        a--,b--;
        aris.push_back( psi( c , pii( a , b ) ) );
        lista[a].push_back(pii(b,c));
        lista[b].push_back(pii(a,c));
    }

    Dijsktra(0 , n );
    Dijsktra( n - 1 , n );

    for(int i=0;i<aris.size();i++){
        a = aris[i].second.first;
        b = aris[i].second.second;
        d = aris[i].first;
        if( total[0][a] + d + total[1][b] == total[0][n-1] || 
            total[1][a] + d + total[0][b] == total[0][n-1]) cont++;
    }

    if(cont>=k) printf("yes\n");
    else printf("no\n");
}
