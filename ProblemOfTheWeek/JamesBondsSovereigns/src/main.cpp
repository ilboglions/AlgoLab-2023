#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#define DIM_MAX 2000

using std::vector;

void solve();
int draw(int, int);
int players,k;
int n;
vector<int> values;
vector< vector<int> > mem;
int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int t;
    std::cin>>t;
    mem = vector< vector<int> >(DIM_MAX, vector<int>(DIM_MAX, -1));
    while(t--){
        solve();
    }
    return 0;
}

void solve(){
    std::cin>>n>>players>>k;
    values.clear();
    values.resize(n);
    for(int i=0; i < n; i++){
        std::cin>>values[i];
    }
    //mem.clear();
    //mem.resize(n, vector<int>(n, -1));
    for(int i=0; i < n; i++){
        for(int j=0; j <n; j++){
            mem[i][j] = -1;
        }
    }
    int res = draw(0, n-1);
    std::cout<<res<<std::endl;
}

int draw(int left, int right){
    if(mem[left][right] ==-1){
        if(((left + n-right -1 - k )%players)==0){
            if(left+players-1 >= right){
                mem[left][right] = std::max(values[left],values[right]);
            }
            else{
                mem[left][right] = std::max(values[left]+ draw(left+1, right),values[right] + draw(left, right-1));
            }
        }
        else{
            mem[left][right] = std::min(draw(left+1, right),draw(left, right-1));
        }
    }
    return mem[left][right];
}