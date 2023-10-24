#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <limits>

using std::pair;
using std::vector;
void solve();
bool sortbysec(const pair<int,int> &a,
              const pair<int,int> &b)
{
    return (a.second < b.second);
}

int main(){
    std::ios_base::sync_with_stdio(false);
    int t;
    std::cin>>t;
    while(t--){
        solve();
    }
}

void solve(){
    int n;
    std::cin>>n;
    int l,p;
    vector <pair<int,int> > boats(n);
    for(int i=0; i < n; i++){
        std::cin>>l>>p;
        boats[i] = std::make_pair(l, p);
    }
    std::sort(boats.begin(), boats.end(), sortbysec);

    int sum=1;
    int min = boats[0].second;
    int left=1;
    int posmax;
    int postmp;
    int i;
    while(left < n){
        l = boats[left].first;
        p = boats[left].second;
        posmax = std::max(min, p-l) + l;
        i = left+1;
        while(i < n && boats[i].second < posmax){
            postmp = std::max(min, boats[i].second - boats[i].first) + boats[i].first;
            if(postmp < posmax){
                left = i;
                posmax = postmp;
            }
            i++;
        }
        min = posmax;
        sum++;
        left++;
        while(left < n && boats[left].second < min){
          left++;
        }
    }
    std::cout<<sum<<"\n";
}