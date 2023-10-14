///3
#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;


void solve();

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
    vector<int> xbest;
    std::cin>>n;
    vector<int> parasol(n);
    for(int i=0; i < n; i++){
        std::cin>>parasol[i];
    }
    std::sort (parasol.begin(), parasol.end());
    int limit = n-1;
    int tmpleft =0;
    int tmpright=0;
    int mindistance = parasol[n-1]-parasol[0]+1;
    int tmpdistance;
    int max=0;
    mindistance = parasol[tmpright]-parasol[0];
    for(int x=parasol[0]; x < parasol[limit]; x++){
        while(tmpleft < tmpright && parasol[tmpleft] + 100 < x){
            tmpleft++;
        }
        while(tmpright < limit && parasol[tmpright+1] - 100 <= x){
            tmpright++;
        }
        if(tmpright-tmpleft+1 > max){
            max = tmpright-tmpleft+1;
            xbest.clear();
            xbest.push_back(x);
            mindistance = std::max(x-parasol[tmpleft], parasol[tmpright]-x);
        }
        else if(tmpright-tmpleft+1 == max){
            tmpdistance =  std::max(x-parasol[tmpleft], parasol[tmpright]-x);
            if(tmpdistance < mindistance){
                xbest.clear();
                xbest.push_back(x);
                mindistance = tmpdistance;
            }
            else if(tmpdistance == mindistance){
                xbest.push_back(x);
            }
        }
    }
    std::cout<<max<<" "<<mindistance<<"\n";
    for(int i: xbest){
        std::cout<<i<<" ";
    }
    std::cout<<"\n";
}