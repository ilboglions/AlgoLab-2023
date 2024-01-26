#include <iostream>
#include <vector>
using namespace std;
void solve(){
    int n,m,k; cin>>n>>m>>k;
    vector<int> horcruxes(n+1);
    int tmp;
    horcruxes[0]=0;
    for(int i=1; i<=n; i++){
        cin>>tmp;  horcruxes[i] = tmp+horcruxes[i-1];
    }
    vector< vector<int> > dp(m+1, vector<int> (n+1, 0));
    vector<int> previous(n+1);
    int left=0;
    int right = 1;
    int last=0;
    while(right <= n){
        while(left < (right-1) && horcruxes[right] - horcruxes[left] > k)
            left++;
        if(horcruxes[right] - horcruxes[left] == k){
            dp[0][right] = right - left;
            last = right;
        }
        previous[right] = last;
        right++;
    }
    for(int i=0; i<= m; i++) dp[i][0]=0;
    for(int i=1; i<=n; i++){
        dp[1][i] = max(dp[1][i-1], dp[0][previous[i]]);
    }
    for(int i=2; i <= m; i++){
        for(int j=1; j <= n; j++){
            if(previous[j] == j && (j - dp[0][j]) > 0 && dp[i-1][j - dp[0][j]] != 0)
                dp[i][j]= max(dp[i][j-1], dp[0][j] + dp[i-1][j - dp[0][j]]);
            else
                dp[i][j] = dp[i][j-1];
        }
    }
    if(dp[m][n] == 0)
        cout<<"fail\n";
    else
        cout<<dp[m][n]<<"\n";
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin>>t;
    while(t--) solve();
}