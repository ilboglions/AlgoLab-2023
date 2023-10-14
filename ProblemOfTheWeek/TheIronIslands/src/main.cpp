#include <iostream>
#include <vector>
#include <unordered_map>
#include <utility>
void solve();

using std::vector;
using std::unordered_map;
using std::pair;

int main(){
    std::ios_base::sync_with_stdio(false);
    int t;
    std::cin>>t;
    while(t--){
        solve();
    }
}

void solve(){
    int n, k, w;
    int tmp;
    std::cin>>n>>k>>w;
    int l;
    vector <int> c(n);
    unordered_map <int, vector< pair <int, int> > > ways;
    unordered_map <int, vector< pair <int, int> > >::iterator finder;
    int pyke;
    int best=0;
    for(int i=0; i < n; i++){
        std::cin>>c[i];
        if(c[i] == k){
            best=1;
        }
    }
    int prefixsum;
    for(int i=0; i < w; i++){
        std::cin>>l;
        prefixsum = 0;
        for(int j=0; j < l; j++){
            std::cin>>tmp;
            prefixsum += c[tmp];
            finder = ways.find(prefixsum);
            if(finder == ways.end()){
                vector <pair <int, int> > pos;
                pos.push_back(std::make_pair(j, i));
                ways.insert(std::make_pair(prefixsum, pos));
            }
            else{
                finder->second.push_back(pair<int, int>(j, i));
            }
        }
    }
    pyke = c[0];
    for (auto it=ways.begin(); it!=ways.end(); ++it){
        for(pair<int, int> i: it->second){
            finder = ways.find(k - it->first + pyke);
            if(finder != ways.end()){
                for(pair<int, int> other: finder->second){
                    if(other.second != i.second){
                        best = std::max(best, i.first + other.first +1);
                    }
                }
            }
            finder = ways.find(it->first - k);
            if(finder != ways.end()){
                for(pair<int, int> other: finder->second){
                    if(other.second == i.second && other != i){
                       best = std::max(best, i.first - other.first); 
                    }
                }
            }
        }
    }      
    std::cout<<best<<"\n";
}