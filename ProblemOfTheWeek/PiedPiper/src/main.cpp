#include <iostream>
#include <vector>
using namespace std;
int n;
void find_path (const vector< vector<long> > & streets, vector<vector<long> > & paths, int go, int back){
    if(paths[go][back] == -1) return;
    int minimum = min(go , back);
    if (minimum == 0){
        if(streets[0][go] || streets[back][0]){
            paths[0][0] = max(paths[0][0], paths[go][back] + streets[0][go] + streets[back][0]);
        }
        return;
    }
    for(int i=0; i < minimum; i++){
        if(streets[i][go]){
            paths[i][back] = max(paths[i][back], paths[go][back] + streets[i][go]);
        }
        if(streets[back][i]){
            paths[go][i] = max( paths[go][i] , paths[go][back] + streets[back][i]);
        }
    }
}
void solve(){
    int m, u ,v; long f;
    std::cin>>n>>m;
    vector< vector<long> > streets(n, vector<long>(n, 0));
    for(int i=0; i < m; i++){
        std::cin>>u>>v>>f;
        streets[u][v] = f;
    }
    vector < vector < long > >paths_rats(n, vector<long>(n, -1)); paths_rats[n-1][n-1]=0;
    find_path(streets, paths_rats, n-1, n-1);
    
    for(int i=n-2; i >= 0; i--){
        int length = n-i;
        for(int j=0; j < length; j++){
            if(i+j != n-1-j)
                find_path(streets, paths_rats, i+j, n-1-j);
        }
    }
    for(int i=n-2; i> 0; i--){
        int length = i+1;
        for(int j=0; j < length; j++){
            if(2*j != i)
                find_path(streets, paths_rats, j ,i-j);
        }
    }
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
