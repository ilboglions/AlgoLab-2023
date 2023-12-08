#include <iostream>
#include <vector>
#include <utility>
#include <deque>
#include <set>
int n,m,k;
using namespace std;
void find_depth(const vector < vector<int> > & tree, int elem, deque<int> & parents, multiset<int> & tree_temperatures, const vector<int> & temperatures , vector<bool> & source){
    parents.push_back(elem);
    int root = -1;
    tree_temperatures.insert(temperatures[elem]);
    if(parents.size() == (unsigned long) m){
        root = parents.front(); parents.pop_front();
        if( (*tree_temperatures.rbegin() - *tree_temperatures.begin()) <= k){
            source[root] = true;
        }
        tree_temperatures.erase(tree_temperatures.find(temperatures[root]));
    }
    for(int son: tree[elem]){
        find_depth(tree, son, parents, tree_temperatures, temperatures, source);
    }
    parents.pop_back();
    tree_temperatures.erase(tree_temperatures.find(temperatures[elem]));
    if(root != -1){
        parents.push_front(root);
        tree_temperatures.insert(temperatures[root]);
    }  
}
void solve(){
    cin>>n>>m>>k;
    int u,v;
    bool found=false;
    vector< int > temperatures(n);
    vector < vector<int> > tree(n);
    for(int i=0; i < n; i++)
        cin>>temperatures[i];
    for(int i=1; i < n; i++){
        cin>>u>>v;
        tree[u].push_back(v);
    }
    vector< bool > source(n, false);
    deque<int> parents; multiset<int> tree_temperatures;
    find_depth(tree, 0, parents, tree_temperatures, temperatures, source);
    for(int i=0; i < n; i++){
        if(source[i]){ cout<<i<<" "; found = true; }
    }
    if(!found)
      cout<<"Abort mission";
    cout<<"\n";
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