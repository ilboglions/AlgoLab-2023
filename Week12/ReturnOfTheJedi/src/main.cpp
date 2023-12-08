#include <iostream>
#include <vector>
#include <utility>
#include <unordered_set>
#include <climits>
#include <boost/pending/disjoint_sets.hpp>
using namespace std;
typedef pair < int, pair<int,int> > channel;
typedef boost::disjoint_sets_with_storage<> Union_find;
typedef std::size_t                              Index;
void solve(){
    int n,i; cin>>n>>i;
    int cost;
    vector <vector<int> >  cost_to_link(n, vector<int>(n));
    vector < unordered_set<int> > components(n);
    int extracost = INT_MAX;
    vector<channel> connections;
    for(int i=0; i < n-1; i++){
        for(int j=i+1; j < n; j++){
            cin>>cost;
            connections.push_back(make_pair(cost, make_pair(i,j)));
        }
    }
    for(int i=0 ; i < n; i ++) components[i].insert(i);
    sort(connections.begin(), connections.end());
    Union_find uf(n);
    cost = 0;
    for(channel ch: connections){
        Index c1 = uf.find_set(ch.second.first);
        Index c2 = uf.find_set(ch.second.second);
        if(c1 != c2){
            cost += ch.first;
            for(auto elem1: components[(int)c1]){
                for(auto elem2: components[(int)c2]){
                    cost_to_link[elem1][elem2] = ch.first;
                    cost_to_link[elem2][elem1] = ch.first;
                }
            }
            uf.link(c1, c2);
            Index parent = uf.find_set(c1);
            components[(int)parent].insert(components[(int)c1].begin(),components[(int)c1].end());
            components[(int)parent].insert(components[(int)c2].begin(),components[(int)c2].end());
        }
        else{
            extracost = min(extracost, ch.first - cost_to_link[ch.second.first][ch.second.second]);
        }
    }
    cost += extracost;
    cout<<cost<<"\n";
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
