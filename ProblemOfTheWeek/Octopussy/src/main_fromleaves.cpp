#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <utility>

using std::pair;
using std::multiset;
using std::vector;
using std::make_pair;
vector<int> bombs;
struct comp {
    bool operator() (const pair<int,int> &a, const pair<int,int> &b) const{
       if(a.first == b.first){
            return bombs[a.second] < bombs[b.second];
       }
       return a.first < b.first;
    }
};
void solve();
int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int t;
    std::cin>>t;
    while(t--){
        solve();
    }
}

void solve(){
    int n;
    std::cin>>n;
    bombs = vector<int>(n);
    for(int i=0; i < n; i++){
        std::cin>>bombs[i];
    }
    vector<int> mintime(n);
    multiset< pair<int,int>, comp> available;
    vector<int> lock(n,2);
    mintime[0] = bombs[0];
    int lim = (n-3)/2;
    int son;
    for(int i=0; i <= lim; i++){
        son = (i*2)+1;
        mintime[son] = std::min(bombs[son], mintime[i]);
        mintime[son+1] = std::min(bombs[son+1], mintime[i]);
    }
    for(int i=(n-1)/2; i < n; i++){
        available.insert(make_pair(mintime[i],i));
    }
    int elapsed =0;
    int parent;
    while(available.size()){
        auto toremove = available.begin();
        if(elapsed >= bombs[toremove->second]){
            std::cout<<"no\n";
            return;
        }
        parent =((toremove->second)-1)/2;
        available.erase(toremove);
        if(parent >= 0){
            lock[parent]--;
            if(!lock[parent]){
                available.insert(make_pair(mintime[parent], parent));
            }
        }
        elapsed++;
    }
    std::cout<<"yes\n";
    return;
}