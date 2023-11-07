#include <iostream>
#include <vector>
#include <tuple> 
#include <algorithm>
#define HMAX 1025
using std::get;
using std::vector;
// firstpart, secondpart, p_a;
typedef std::tuple<long long, long long, long> Comb;
// firstpart, secondpart, p_a, h_a;
typedef std::tuple<long long, long long, long, long> Potion_a;

void solve();
bool iscompatible(Comb &, Potion_a & );
int main(){
    std::ios_base::sync_with_stdio(false);
    int t;
    std::cin>>t;
    while(t--){
        solve();
    }
}
void solve(){
    int n,m;
    long acoeff,bcoeff;
    long tmp1, tmp2;
    long p,h,w;
    long long firstpart;
    long long secondpart;
    long target;
    int bsips=0;
    std::cin>>n>>m;
    std::cin>>acoeff>>bcoeff;
    std::cin>>p>>h>>w;
    vector<long > b;
    vector<Potion_a> potions_a(n);
    vector < vector<Comb> > combinations_a(n+1, vector<Comb>(HMAX, {0,0,0}));
    vector < int > available_b(n+1, -1);

    for(int i=0; i < n; i++){
        std::cin>>tmp1>>tmp2;
        if(i < 50){
            firstpart=0;
            secondpart = ((long long)1)<<i;
        }
        else{
            firstpart= ((long long)1)<<(i-50);
            secondpart=0;
        }
        potions_a[i] = std::make_tuple(firstpart, secondpart,tmp1,tmp2);
    }
    for(int i=0; i < m; i++){
      std::cin>>tmp1;
      b.push_back(tmp1);
    }
    std::sort (b.begin(), b.end());
    tmp1 = 0;
    for(int i=0; i<=n; i++){
        target = w + i*acoeff;
        while(tmp1 < target && b.size()){
            tmp1 += b.back();
            b.pop_back();
            bsips++;
        }
        if(tmp1 >= target){
            available_b[i] = bsips;
        }
        else
            break;
    }
    Comb * tmp;
    Potion_a tmp_potion;
    int sum=-1;
    target = p+(available_b[1]*bcoeff);
    for(Potion_a i: potions_a){
        tmp = &combinations_a[1][get<3>(i)];
        if(get<2>(i) >= target  && get<3>(i) >= h){
            sum= 1+available_b[1];
            break;
        }
        if(get<2>(i) > get<2>(*tmp)){
            get<0>(*tmp) = get<0>(i);
            get<1>(*tmp) = get<1>(i);
            get<2>(*tmp) = get<2>(i);
        }
    }
    int nsips=2;
    Comb * tmp_comb;
    while(sum == -1 && nsips <= n && available_b[nsips]!=-1){
        target = p +(available_b[nsips]*bcoeff);
        for(int i=1; i < HMAX && sum==-1; i++){
            tmp_comb = &combinations_a[nsips-1][i];
            if(get<2>(*tmp_comb)){
                for(int j=0; j < n && sum==-1; j++){
                    tmp_potion = potions_a[j];
                    if(iscompatible(*tmp_comb, tmp_potion)){
                        firstpart = get<0>(*tmp_comb) | get<0>(tmp_potion);
                        secondpart = get<1>(*tmp_comb) | get<1>(tmp_potion);
                        tmp1 = get<2>(*tmp_comb) + get<2>(tmp_potion);
                        tmp2 = std::min(get<3>(tmp_potion) + i,(long)HMAX-1);
                        tmp = &combinations_a[nsips][tmp2];
                        if(tmp1 > get<2>(*tmp)){
                            get<0>(*tmp) = firstpart;
                            get<1>(*tmp) = secondpart;
                            get<2>(*tmp) = tmp1;
                            if(tmp1 >= target  && tmp2 >= h){
                                sum = available_b[nsips] + nsips;
                            }
                        }
                    }
                }
            }
        }  
        nsips++;
    }
    std::cout<<sum<<"\n";
}
bool iscompatible(Comb & combination, Potion_a & toadd){
    long long firstcomb = get<0>(combination);
    long long secondcomb = get<1>(combination);
    long long firsttoadd =get<0>(toadd);
    long long secondtoadd = get<1>(toadd);
    return (((firstcomb & firsttoadd) | (secondcomb & secondtoadd)) == 0);
}