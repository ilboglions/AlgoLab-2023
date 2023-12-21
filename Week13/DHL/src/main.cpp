#include <iostream>
#include <vector>
#include <climits>
#define LIM 1000000
using namespace std;

void solve(){
  int n; cin>>n;
  vector<int> a(n);
  vector<int> b(n);
  for(int i=0; i < n; i++)
    cin>>a[i];
  for(int i=0; i < n; i++)
    cin>>b[i];
  vector < vector<int> > costs(n+1, vector<int>(n+1, LIM));
  costs[0][0] = 0;
  for(int i=1; i <= n; i++)
    for(int j=1; j <= n; j++)
      costs[i][j] = min(costs[i-1][j], min(costs[i][j-1], costs[i-1][j-1])) + ((a[i-1]-1)*(b[j-1]-1));
  cout<<costs[n][n]<<"\n";
}
int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int t; cin>>t;
  while(t--) 
    solve();
}