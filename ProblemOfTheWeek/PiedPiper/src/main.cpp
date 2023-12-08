#include <iostream>
#include <vector>
#include <utility>
using namespace std;
int n;

typedef pair< vector<int>, int> path

void find_path (){
    
}
void solve(){
    int m, u ,v,f;
    std::cin>>n>>m;
    vector< vector <bool> > checked(n, vector<bool>(n, false));
    vector< vector<int> > streets(n, vector<int>(n, 0));
    for(int i=0; i < m; i++){
        std::cin>>u>>v>>f;
        streets[u][v] = f;
    }
    vector < vector < path > paths_rats(n, vector<path>(n));
    vector < bool > path(n,false);
    
    std::cout<<paths_rats[0][0]<<"\n";
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin>>t;
    while(t--){
        solve();
    }
}
