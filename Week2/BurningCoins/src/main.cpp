#include <iostream>
#include <vector>
using std::vector;
int findbest( vector<int> &, vector<vector<int> > & , int ,int);
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
    std::cin>>n;
    vector<int> coins(n);
    for(int i=0; i < n;i++){
        std::cin>>coins[i];
    }
    vector< vector <int> > mem (n, vector<int>(n,-1));

    int res = findbest(coins, mem, 0, n-1);
    std::cout<<res<<"\n";
}


int findbest( vector<int> &coins, vector<vector<int> > &mem , int left,int right){
    if(mem[left][right]==-1){
        if(left==right){
            mem[left][right] = coins[left];
        }
        else if(left+1 == right){
            mem[left][right] = std::max(coins[left],coins[right]);
        }
        else{
            int minleft, minright;
            minleft = std::min( findbest(coins, mem, left+2, right),findbest(coins,mem, left+1, right-1));
            minright = std::min(findbest(coins, mem, left, right-2),findbest(coins,mem, left+1, right-1));
            mem[left][right] = std::max(coins[left]+ minleft, coins[right] + minright);    
        }
    }
    return mem[left][right];
}