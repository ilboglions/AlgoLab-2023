#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using std::pair;
using std::vector;

void solve();
int countchildren( const int , const int &, vector<bool>&);
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
    int tmp;
    int elapsed;
    vector<int> bombs = vector<int>(n);
    vector< pair<int, int> > pos(n);
    vector< bool > activated(n, true);
    vector<int> mintime(n);
    for(int i=0; i < n; i++){
        std::cin>>tmp;
        pos[i] = std::make_pair(tmp,i);
    }
    elapsed=0;
    int son;
    std::sort(pos.begin(), pos.end());
    for(int i=0; i < n ; i++){
        if(activated[pos[i].second]){
            son = (pos[i].second * 2) +1;
            elapsed += countchildren(son,n, activated) + countchildren(son+1,n, activated);
            if(elapsed >= pos[i].first){
                std::cout<<"no\n";
                return;
            }
            activated[pos[i].second] = false;
            elapsed++;
        }
    }
    std::cout<<"yes\n";
}
int countchildren( const int pos, const int & n, vector<bool>& activated){
    if(pos >= n){
        return 0;
    }
    if(activated[pos]){
        activated[pos] = false;
        return 1 + countchildren(pos*2+1,n, activated)+ countchildren((pos*2)+2,n, activated);
    }
    return 0;
}