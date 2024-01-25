#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

typedef long IT;
typedef CGAL::Gmpz ET;


typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;
typedef pair<long,long> point;

void solve(){
  Program lp (CGAL::SMALLER, true, 1, false, 0); 
  long costraints=0;
  long n,m,h,w; cin>>n>>m>>h>>w;
  long x,y;
  vector<point> toadd(n);
  vector<point> fixed(m);
  vector<long> costraintsh(n, INT_MAX);
  vector<long> costraintsw(n, INT_MAX);
  for(int i=0; i < n; i++){
    cin>>x>>y; toadd[i]= make_pair(x,y);
  }
  for(int i=0; i < m; i++){
    cin>>x>>y; fixed[i]= make_pair(x,y);
  }
  long poslow, poshigh;
  for(int i=0; i<n; i++){
    for(int j=0; j < m; j++){
      if(fixed[j].first < toadd[i].first){
        poslow =  h*(fixed[j].first - toadd[i].first) + toadd[i].second * w;
        poshigh =  - h*(fixed[j].first - toadd[i].first) + toadd[i].second * w;
      }
      else{
        poslow =   - h*(fixed[j].first - toadd[i].first) + toadd[i].second * w; 
        poshigh =  h*(fixed[j].first - toadd[i].first) + toadd[i].second * w;
      }
      if(poslow >= w * fixed[j].second || poshigh <= w * fixed[j].second)
          costraintsh[i] = min(costraintsh[i], abs(fixed[j].second - toadd[i].second)*2 - h);
      else
         costraintsw[i] = min(costraintsw[i], abs(fixed[j].first - toadd[i].first)*2 - w);
    }
    lp.set_a(i, costraints, h); lp.set_b(costraints, costraintsh[i]);
    lp.set_a(i, costraints+1, w); lp.set_b(costraints+1, costraintsw[i]);
    costraints += 2;
    for(int j=i+1; j < n; j++){
      if(toadd[j].first < toadd[i].first){
        poslow =  h*(toadd[j].first - toadd[i].first) + toadd[i].second * w;
        poshigh =  -h*(toadd[j].first - toadd[i].first) + toadd[i].second * w;
      }
      else{
        poslow =   -h*(toadd[j].first - toadd[i].first) + toadd[i].second *w; 
        poshigh =  h*(toadd[j].first - toadd[i].first) + toadd[i].second *w;
      }
      if(poslow >= w * toadd[j].second || poshigh <= w * toadd[j].second){
          lp.set_a(i, costraints, h);lp.set_a(j, costraints, h); lp.set_b(costraints, abs(toadd[j].second - toadd[i].second) * 2);
      }
      else{
          lp.set_a(i, costraints, w);lp.set_a(j, costraints, w); lp.set_b(costraints, abs(toadd[j].first - toadd[i].first) * 2);
      }
      costraints++;
    }
    lp.set_c(i, -2*(h+w));
  }
  Solution s = CGAL::solve_linear_program(lp, ET());
  if(s.solves_linear_program(lp) && !s.is_infeasible()){
    long value = -floor(CGAL::to_double(s.objective_value()));
    cout << value<<"\n"; 
  }
  else{
    cout<<s<<"\n";
  }
  
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int t; cin>>t;
  while(t--) solve();
}