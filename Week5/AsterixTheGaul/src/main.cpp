#include <iostream>
#include <vector>
#include <utility>
#include <climits>
#include <algorithm>
using namespace std;

typedef pair<long,long> moves;

bool binary_search( vector <moves> & s, long distance, long maxtime){
  long left = 0; 
  long right = s.size()-1;
  while(left <= right){
    long mid = (left+right)/2;
    if(s[mid].first >= distance){
      if(s[mid].second < maxtime)
        return true;
      right = mid-1;
    }
    else
      left = mid+1;
  }
  return false;
}
bool find_optimal(int n, vector<moves> & movements, long distance, long bonus, long timer){
  vector < moves > s1;
  int first_half = n/2;
  int second_half = n - first_half;
  long lim = ((long)1)<<(first_half);
  for(long i=0; i < lim; i++){
    long total_distance = 0;
    long total_time =0;
    for(long j=0; j < first_half; j++){
      if((((long)1)<<j) & i){
        total_distance += (movements[j].first + bonus);
        total_time += movements[j].second;
      }
    }
    s1.push_back(make_pair(total_distance, total_time));
  }
  sort(s1.begin(), s1.end(), [](moves a, moves b) {
    if(a.first == b.first){
      return a.second > b.second;
    }
      return a.first < b.first;   
  });
  long minimum = LONG_MAX;
  for(int i=(int)s1.size()-1; i>=0; i--){
    s1[i].second = min(minimum, s1[i].second);
    minimum = s1[i].second;
  }
  lim = ((long)1)<<(second_half);
  for(long i=0; i < lim; i++){
    long total_distance = 0;
    long total_time =0;
    for(long j = first_half ; j < n; j++){
      if(((long)1)<<j & (i<<(first_half))){
        total_distance += movements[j].first + bonus;
        total_time += movements[j].second;
      }
    }
    if(binary_search(s1, distance-total_distance, timer-total_time))
      return true;
  }
  return false;
}

void solve(){
  int n,m; long d,t; cin>>n>>m>>d>>t;
  vector<moves> movements(n);
  long a,b;
  for(int i=0; i< n;i++){
    cin>>a>>b; movements[i] = make_pair(a,b);
  }
  vector<long> gulps(m+1);
  gulps[0] = 0;
  for(int i=1; i<=m; i++){
    cin>>gulps[i];
  }

  int res=-1;
  int left = 0;
  int right = m;
  while(left <= right){
    int mid = (left + right)/2;
    if(find_optimal(n, movements, d, gulps[mid], t)){
      res = mid;
      right = mid-1;
    }
    else{
      left = mid+1;
    }
  }
  if(res == -1)
    cout<<"Panoramix captured\n";
  else
    cout<<res<<"\n";
}
int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int t; cin>>t;
  while(t--) solve();
}