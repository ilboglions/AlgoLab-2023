#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
using std::pair;
using std::vector;
vector< vector <pair<int,long> > > sons;
vector<long>  chambers;
vector<int>  subnodes;
vector<long>  subtime;
vector<long>  submoney; 
int parent;
int n;
bool orderSons(const int & a, const int & b){
    int x = sons[parent][a].first;
    int y= sons[parent][b].first;
    return  (subtime[x] + sons[parent][a].second*2)*(long)subnodes[y] <  (subtime[y] + sons[parent][b].second*2)*(long)subnodes[x];
}
void findmoney(int start){
    int tmp;
    for(auto e: sons[start])
        findmoney(e.first); 
    vector < int > sonsorder(sons[start].size());
    int size = sons[start].size();
    for(int i=0; i < size ; i++){
        sonsorder[i]=i;
    }
    parent = start;
    std::sort(sonsorder.begin(), sonsorder.end(), orderSons);
    long totaltime = 0;
    long totalmoney = chambers[start];
    int totalnodes = 1;
    for(int index: sonsorder){
        tmp = sons[start][index].first;
        totalmoney += submoney[tmp] - totaltime*subnodes[tmp] - (sons[start][index].second * subnodes[tmp]);
        totaltime += subtime[tmp] + 2 * sons[start][index].second;
        totalnodes += subnodes[tmp];
    }
    subtime[start]= totaltime;
    submoney[start]=totalmoney;
    subnodes[start]= totalnodes;
}
using std::vector;
void solve(){
    std::cin>>n;
    int u,v;
    long l;
    chambers= vector<long> (n+1);
    sons = vector<vector<pair<int, long> > >(n+1);
    subnodes = vector<int> (n+1);
    subtime = vector <long> (n+1);
    submoney= vector <long>(n+1);
    for(int i=1; i <= n; i++){
        std::cin>>chambers[i];
    }
    for(int i=0; i < n; i++){
        std::cin>>u>>v>>l;
        sons[u].push_back(std::make_pair(v,l));
    }
    findmoney(0);
    std::cout<<submoney[0]<<"\n";
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
