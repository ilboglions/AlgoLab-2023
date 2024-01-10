#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
#define MAXDIFFERENCE 12

const long mask_north = (long)8191 << (long)25; const long shift_north = 25;
const long mask_south = (long)8191 << (long)12; const long shift_south = 12;
const long mask_lastnorth = (long)7 << (long)9; const long shift_lastnorth = 9;
const long mask_beforenorth = (long)7 << (long)6; const long shift_beforenorth = 6;
const long mask_lastsouth = (long)7 << (long)3; const long shift_lastsouth = 3;
const long mask_beforesouth = (long)7 ; const long shift_beforesouth = 0;
 
typedef long state;


void get_from_state(state current, long & north, long & south, long & lastnorth, long & beforenorth, long & lastsouth, long & beforesouth){

  north = (long)((current & mask_north)>> shift_north);
  south = (long)((current & mask_south)>> shift_south);
  lastnorth = (long)((current & mask_lastnorth)>> shift_lastnorth);
  beforenorth = (long)((current & mask_beforenorth)>> shift_beforenorth);
  lastsouth = (long)((current & mask_lastsouth)>> shift_lastsouth);
  beforesouth = (long)((current & mask_beforesouth)>> shift_beforesouth);
  //cout<<north<<" "<<south<<" "<<lastnorth<<" "<<beforenorth<<" "<<lastsouth<<" "<<beforesouth<<"\n";
  return;

}

state build_state (long  north, long  south, long  lastnorth, long  beforenorth, long  lastsouth, long  beforesouth){

  long current = ((long)north) << shift_north;
  current += ((long)south) << shift_south;
  current += ((long)lastnorth) << shift_lastnorth;
  current += ((long)beforenorth) << shift_beforenorth;
  current += ((long)lastsouth) << shift_lastsouth;
  current += ((long) beforesouth) << shift_beforesouth;
  return current;

}


void solve(){
  long n,k,m; cin>>n>>k>>m;
  long NOTHING = k;
  vector<long> warriors(n);
  for(int i=0; i < n; i++)
    cin>>warriors[i];
  unordered_map < state , long > dp;

  state current = build_state(1,0,warriors[0], NOTHING, NOTHING, NOTHING);
  dp.insert(make_pair(current, 998));
  state previous;
  long points;
  long pointsn, pointss;
  long different_n, different_s;
  long different_n1, different_s1;
  for(long i=1; i < n; i++){ //ASSIGNED ELEMENTS
    long this_warrior = warriors[i];
    for(long j=max((long)0, i/2 - MAXDIFFERENCE); j <= min(n,i/2 + MAXDIFFERENCE); j++){ //ELEMENTS ASSIGNED TO NORTH
      for(long l=0; l <= k; l++){ //LAST NORTH
        different_n1 = (l != NOTHING && l != this_warrior) ? 2 : 1;
        for(long o=0; o <= k; o++){ //LAST SOUTH
          different_s1 = (o != NOTHING && o != this_warrior) ? 2 : 1;
          for(long p=0; p <= k; p++){ //BEFORE NORTH
            if((m == 3) && p != NOTHING && p != this_warrior && p != l) different_n = different_n1+1;
            else different_n = different_n1; 
            for(long q=0; q <= k; q++){ //BEFORESOUTH
              if((m == 3) && q != NOTHING && q != this_warrior && q != o) different_s = different_s1+1; 
              else different_s = different_s1;
              previous = build_state(j, i-j, l, p, o , q);
              auto finder = dp.find(previous);
              if(finder != dp.end()){
                points = finder->second;
                pointsn = (different_n*1000) - (1<<(abs(j+1 - i + j)));
                pointss = (different_s*1000) - (1<<(abs(j - i + j - 1)));
                if(pointsn >= 0){
                  current = build_state(j+1, i-j, this_warrior, l, o, q);
                  finder = dp.find(current);
                  if(finder != dp.end()){
                    finder->second = max(finder->second, pointsn+points);
                  }
                  else{
                    dp.insert(make_pair(current, pointsn+points));
                  }
                } 
                if(pointss >= 0){
                  current = build_state(j, i-j+1, l, p, this_warrior, o);
                  finder = dp.find(current);
                  if(finder != dp.end()){
                    finder->second = max(finder->second, pointss+points);
                  }
                  else{
                    dp.insert(make_pair(current, pointss+points));
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  long maximum = -1;
  long lim = min(n,n/2 + MAXDIFFERENCE);
  for(long j=max((long)0,n/2-MAXDIFFERENCE); j <= lim; j++){ //ELEMENTS ASSIGNED TO NORTH
    for(long l=0; l <= k; l++){ //LAST NORTH
      for(long o=0; o <= k; o++){ //LAST SOUTH
        for(long p=0; p <= k; p++){ //BEFORE NORTH
          for(long q=0; q <= k; q++){ //BEFORE SOUTH
            current = build_state(j, n-j , l, p, o , q);
            auto finder = dp.find(current);
            if(finder != dp.end()){
              maximum  =  max(maximum, finder->second);
            }
          }
        }
      }
    }
  }
  cout<<maximum<<"\n";
}


int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int t; cin>>t;
  while(t--) solve();
}