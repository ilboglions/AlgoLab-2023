#include <iostream>
#include <vector>
#include <climits>
using namespace std;

void compute_value(vector<vector<int> > & dp,  vector<int> & coins ,int left, int right, int n){
  if(dp[left][right] != -1){
    return;
  }
  if(right - left <= 1){
    dp[left][right] = max(coins[left], coins[right]);
    return;
  }
  compute_value(dp, coins, left+2, right, n);
  compute_value(dp, coins, left, right-2, n);
  compute_value(dp, coins, left+1, right-1, n);
  int minleft = min(dp[left+1][right-1], dp[left+2][right]);
  int minright = min(dp[left+1][right-1], dp[left][right-2]);
  dp[left][right] = max(minleft + coins[left], minright + coins[right]);
}

void solve(){
  int n; cin>>n;
  vector <int> coins(n);
  for(int i=0; i < n; i++) cin >>coins[i];
  vector < vector <int> > dp(n, vector<int>(n, -1));
  compute_value(dp, coins, 0, n-1, n);
  cout<<dp[0][n-1]<<"\n";  
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int t; cin>>t;
  while(t--) solve();
}