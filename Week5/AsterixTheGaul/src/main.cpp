#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <climits>

using std::map;
using std::vector;
void solve();
int findbest(const vector<long>&,const vector<long>& ,const vector<long>& ,const  int, const  int, const long&,const long&);
bool isdoable(const vector<long>& , const vector<long> &, long, const long &, const long & );

int main(){
    std::ios_base::sync_with_stdio(false);
    int t;
    std::cin>>t;
    while(t--){
        solve();
    }
}
void solve(){
    int n, m;
    long d,t;
    std::cin>>n>>m>>d>>t;
    vector<long> movements(n);
    vector<long> elapsed(n);
    
    for(int i=0; i < n; i++){ 
        std::cin>>movements[i]>>elapsed[i];
    }
    vector<long> boost(m+1);
    boost[0]=0;
    for(int i=1; i <= m; i++){
        std::cin>>boost[i];
    }


    int res = findbest(movements, elapsed, boost, 0, m, d, t);
    if(res == -1){
        std::cout<<"Panoramix captured\n";
        return;
    } 
    std::cout<<res<<"\n";
}
int findbest(const vector<long>& movements,const vector<long>& elapsed,const vector<long>& boost,const int left,const int right, const long & distance,const long & maxtime){
    int res;
    if(left>right){
        return -1;
    }
    int center =(left+right)/2;
    if(isdoable(movements, elapsed, boost[center], distance, maxtime)){
        res = findbest(movements, elapsed, boost, left, center-1, distance, maxtime);
        if(res != -1)
            return res;
        return center;
    }
    else{
        return findbest(movements, elapsed, boost, center+1, right, distance, maxtime);
    }
}
bool isdoable(const vector<long>& movements, const vector<long> & elapsed, long boost, const long & distance, const long & maxtime){
    int size = movements.size();
    int len = size/2;
    int max1 = 1<<(size-len);
    int max2 = 1<<len;
    long sum;
    long totaltime;
    int tmp;
    long tofind;
    long min;
    map <long, long > othersector;
    for(int i=0; i < max1; i++){
        sum =0;
        totaltime=0;
        for(int j = len; j < size; j++){
            tmp = j-len;
            if(i & 1<<tmp){
                sum += movements[j] + boost;
                totaltime += elapsed[j];
            }
        }
        othersector.insert(std::make_pair(sum, totaltime));
    }
    min = LONG_MAX;
    for(auto iter = othersector.rbegin(); iter != othersector.rend(); iter++){
        if(iter->second < min){
            min = iter->second;
        }
        else{
            iter->second = min;
        }
    }
    for(int i=0; i < max2; i++){
        sum=0;
        totaltime=0;
        for(int j=0; j < len; j++){
            if(i & 1<<j){
                sum += movements[j] + boost;
                totaltime += elapsed[j];
            }
        }
        tofind = distance-sum;
        auto finder = othersector.lower_bound(tofind);
        if(finder != othersector.end() && finder->second + totaltime < maxtime){
            return true;
        }
    }
    return false;
}