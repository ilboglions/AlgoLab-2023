#include <iostream>
#include <vector>
#include <tuple>
using std::tuple;
using std::vector;
typedef tuple < int , int , long> connection;
void solve(){
    int n,m, k;
    long x;
    std::cin>>n>>m>>x>>k;
    int u,v;
    long p;
    vector <vector<long> > dp(k, vector<long>(n,-1));
    vector < connection > connections(m);
    vector < bool > finals(n,false);

    for(int i=0; i < m; i++){
        std::cin>>u>>v>>p;
        connections[i] = std::make_tuple(u,v,p);
        dp[0][u] = std::max(dp[0][u], p);
    }
    for(int i=0; i < n; i++){
        if(dp[0][i]==-1){
            finals[i]= true;
        }
    }
    for(int i=0; i < m; i++){
        v = std::get<1>(connections[i]);
        if(finals[v]){
              std::get<1>(connections[i])=0;
        }
    }
    int found = 0;
    for(int i=1; i < k && !found; i++){
        for(int j=0; j < m; j++){
            u = std::get<0>(connections[j]);
            v = std::get<1>(connections[j]);
            p = std::get<2>(connections[j]);
            dp[i][u] = std::max(dp[i][u], dp[i-1][v]+p);
        }
        if(dp[i][0]>= x){
            found = i;
        }
    }
    if(found){
        std::cout<<found+1<<"\n";
    }
    else{
        std::cout<<"Impossible\n";
    }
}
int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int t;
    std::cin>>t;
    while(t--){
        solve();
    }
}