#include <iostream>
#include <vector>
#include <climits>
using std::vector;
void find_cost(const vector<vector<int> > & tree, const vector<int> & cost, vector<int> & subcost, vector<int> & origincost, int root){
    if(!tree[root].size()){
        subcost[root] = cost[root];
        origincost[root] = cost[root];
        return;
    }
    int fix_cost = cost[root];
    int nofix_cost = 0;
    int grandson_cost;
    for(int son: tree[root]){
        find_cost(tree,cost,subcost,origincost,son);
        grandson_cost=0;
        for(int grandson: tree[son]){
            grandson_cost += subcost[grandson];
        }
        nofix_cost += subcost[son];
        fix_cost += std::min(subcost[son], grandson_cost);
    }
    int nofix = INT_MAX;
    for(int i=0; i < tree[root].size(); i++){
        nofix = std::min(nofix, nofix_cost - subcost[tree[root][i]] + origincost[tree[root][i]]);
    }
    origincost[root] = fix_cost;
    subcost[root] = std::min(nofix, fix_cost);
    //std::cout<<"In "<<root<<" il subcost "<<subcost[root]<<" l'origin cost "<<origincost[root]<<"\n";
}
void solve(){
    int n; std::cin>>n;
    int a,b;
    vector< vector<int> > sons(n);
    vector <int> cost(n);
    vector <int> subcost(n,0);
    vector <int> origincost(n);
    for(int i=1; i < n; i++){
        std::cin>>a>>b;
        sons[a].push_back(b);
    }
    for(int i=0; i < n; i++)
        std::cin>>cost[i];
    find_cost(sons, cost, subcost, origincost, 0);
    std::cout<<subcost[0]<<"\n";
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