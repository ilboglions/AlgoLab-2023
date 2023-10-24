#include <iostream>
#include <algorithm>
#include <vector>

using std::vector;

void solve();
int findweakest(vector<int> &, int, int , int );

int main(){
    std::ios_base::sync_with_stdio(false);
    int t;
    std::cin>>t;
    while(t--){
        solve();
    }
}


void solve(){
    int n,m;
    std::cin>>n>>m;
    vector<int> friends(n);
    vector<int> tocarry(n,0);
    vector<int> boxes(m);
    
    for(int i=0; i < n; i++){
        std::cin>>friends[i];
    }
    std::sort(friends.begin(), friends.end(),  std::greater<int>());

    for(int i=0; i < m; i++){
        std::cin>>boxes[i];
    }
    std::sort(boxes.begin(), boxes.end(),  std::greater<int>());

    if(friends[0] < boxes[0]){
        std::cout<<"impossible\n";
        return;
    }
    int min =0;
    for(int i=0; i < m; i++){
        while(min < n && friends[min] >= boxes[i]){
          min++;
        }
        min--;
        auto tmp = std::lower_bound(tocarry.begin(), tocarry.begin() + min, tocarry[min],std::greater<int>());
        *tmp += 1;
    }

    int elapsed = (tocarry[0]-1)*3 +2;
    std::cout<<elapsed<<"\n";
    return;
}


