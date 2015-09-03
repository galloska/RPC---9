#include <bits/stdc++.h>

using namespace std;

const int MAXN = 105;

int g,c,n,total;
int price[MAXN];
int change[MAXN];
char cad[MAXN][20];
int memo[MAXN][MAXN][10005];

int techo(int a,int b){
    int c = ( b / a )*a;
    if(c<b) c+=a;
    return c;
}

int suelo(int a,int b){
    int c = ( b / a )*a;
    return c;
}

int calcula(int id){
    int cambio = g - price[ id ];
    int a = techo( change[id] , cambio );
    int b = suelo( change[id] , cambio );
    if(cad[id][0]=='h'){
        if( abs(cambio - a) <= abs(cambio - b) ) return a;
        else return b;
    }
    else if(cad[id][1]=='r') return b;
    return a;
}

int DP(int id,int oro,int plata){

    if(id==n) return 0;

    if(memo[id][oro][plata]!=-1) return memo[id][oro][plata];

    if(cad[id][1]=='e' && plata>=price[id])
        return memo[id][oro][plata] = max( DP(id+1,oro,plata) , DP( id + 1 , oro , plata - price[id] ) + 1 );
    else{
        int res = DP( id + 1 , oro , plata );
        if(oro>0 && plata>=price[id]) 
            res = max( res , max( DP( id + 1 , oro - 1 , plata + calcula(id) ) , DP( id + 1 , oro , plata - price[id] ) ) + 1 );
        else if(oro>0) res = max(res , DP(id+1,oro-1,plata+calcula(id)) + 1);
        else if(plata>=price[id]) res = max(res , DP( id + 1 , oro , plata-price[id] ) + 1);

        return memo[id][oro][plata] = res;
    }
}

int main(){

    scanf("%d %d %d",&g,&c,&n);
    for(int i=0;i<n;i++){
        scanf("\n%s %d %d",cad[i],&change[i],&price[i]);
        total += change[i];
    }

    for(int id=n-1;id>=0;id--)
        for(int gold=0;gold<=c;gold++)
            for(int silver=total;silver>=0;silver--)
                memo[id][gold][silver] = -1;

    printf("%d\n",DP(0,c,0));
    return 0;
}
