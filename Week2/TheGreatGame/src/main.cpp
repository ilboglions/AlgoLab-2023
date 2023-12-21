#include <iostream>
#include <vector>
#include <climits>
using namespace std;

void solve(){
    int n,m; cin>>n>>m;
    int r,b; cin>>r>>b; r--; b--;
    int u,v;
    vector < vector<int> > transitions(n);
    for(int i=0; i < m; i++){
        cin>>u>>v; transitions[u-1].push_back(v-1);
    }
    vector<int> even_distance(n, INT_MAX);
    vector<int> odd_distance(n, -1);
    even_distance[n-1] = 0; odd_distance[n-1] = 0;
    for(int i=n-2; i >= 0; i--){
        for(next: transitions[i]){
            even_distance[i] = min(even_distance[i], odd_distance[next] + 1);
            odd_distance[i] = max(odd_distance[i], even_distance[next] + 1);
        }
    }
    if(even_distance[r] < even_distance[b] || (even_distance[r]==even_distance[b] && even_distance[r] % 2)){
        cout<<"0\n";
    }
    else (even_distance[r] > even_distance[b]){
        cout<<"1\n";
    }
    
}


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin>>t;
    while(t--) solve();
}