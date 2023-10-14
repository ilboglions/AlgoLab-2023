#include <iostream>
#include <vector>
#include <utility>
using std::vector;
using std::pair;

void solve();

int findbest(vector<vector<int> > &,  vector<int> &, int, int );

int main(){
    std::ios_base::sync_with_stdio(false);
    int t;
    std::cin>>t;
    while(t--){
        solve();
    }
}


void solve(){
    int n,m,k;
    int res;
    int tmp;
    int leftpos, rightpos;
    std::cin>>n>>m>>k;
    vector<int> cumsum(n+1, 0);
    vector<int>  pos(n,0);
    vector<vector<int> > mem(m,vector<int>(n,-1));
    cumsum[0] = 0;
    for(int i=1; i <= n; i++){
        std::cin>>tmp;
        cumsum[i] = cumsum[i-1]+tmp;
    }
    leftpos=0;
    rightpos=1;
    while(rightpos <= n){
        if(leftpos < rightpos && cumsum[rightpos]-cumsum[leftpos] > k){
            leftpos++;
        }
        else if(rightpos < n && cumsum[rightpos]-cumsum[leftpos] < k){
            rightpos++;
            }   
        else if(cumsum[rightpos] - cumsum[leftpos] == k){
            pos[rightpos-1] = rightpos-leftpos;
            leftpos++;
            rightpos++;
            }
        else{
            rightpos++;
            }
    }
    mem[0][0] = pos[0];
    res = findbest(mem, pos, n-1, m-1);
    if(res){
        std::cout<<res<<"\n";
    }
    else{
        std::cout<<"fail"<<"\n";
    }
}

int findbest(vector<vector<int> > &mem, vector< int > &pos,int rightlim, int level){
    int previous;
    if(mem[level][rightlim] == -1){
        if(!level){
            mem[level][rightlim] = std::max( findbest(mem, pos, rightlim-1,level), pos[rightlim]);
        }
        else{
            if(rightlim == 0){
                mem[level][0] = 0;
            }
            else{
                previous = findbest(mem, pos, rightlim-pos[rightlim], level-1);
                if(pos[rightlim] && previous){
                    mem[level][rightlim] = std::max(findbest(mem, pos, rightlim-1,level), pos[rightlim] + previous);
                }
                else{
                   mem[level][rightlim] =  findbest(mem, pos, rightlim-1,level);
                }
            }
        }
    }
    return mem[level][rightlim];
}