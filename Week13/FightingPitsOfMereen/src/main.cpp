#include <iostream>
#include <vector>
#include <tuple>
using namespace std;


int n,k,m; 
//POINTS, NORTH, SOUTH, LAST M ELEMS NORTH, LAST M ELEMS SOUTH
typedef tuple <int, int, int , vector<int>, vector<int> > state;

void solve(){
  cin>>n>>k>>m;
  vector<int> warriors(n);
  for(int i=0; i < n; i++)
    cin>>warriors[i];

  vector < vector < state> > dp(n+1, vector<state>(n+1));
  dp[0][0] = make_tuple(0, 0 , 0 , vector<int>(k,0), vector<int>(k,0));
  for(int i=0; i <= n; i++){
    for(int j=i+1; j <= n; j++){
      
      
    }


  }

  
}


int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int t; cin>>t;
  while(t--) solve();
}