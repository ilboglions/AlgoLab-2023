#include <iostream>
#include <vector>
#include <utility>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
using std::vector;
using std::pair;
typedef long IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;
void solve(){
    int n,m;
    long budget;
    long x,y;
    std::cin>>n>>m>>budget;
    int totalhouses = n+m;
    vector< pair<long, long> > houses(totalhouses);
    const int b=0;
    const int c=1;
    const int c2=2;
    const int dmax = 3;
    Program lp (CGAL::SMALLER, false, 0, false, 0);
    for(int i=0; i < n; i++){
        std::cin>>x>>y;
        houses[i]= std::make_pair(x,y);
        lp.set_a(b,i, y);
        lp.set_a(c,i, 1);
        lp.set_b(i, -x); 
    }
    for(int i=0; i < m; i++){
        std::cin>>x>>y;
        houses[i+n] = std::make_pair(x,y);
        lp.set_a(b, i+n, -y);
        lp.set_a(c, i+n, -1);
        lp.set_b(i+n, x);
    }
    Solution s = CGAL::solve_linear_program(lp, ET());
    if (s.is_infeasible()){
        std::cout<<"Yuck!\n"; return;
    }
    if(budget != -1){
        long sum_y=0, sum_x=0, sum_c=0;
        for(int i=0; i < n; i++){
            sum_y += houses[i].second;
            sum_x += houses[i].first;
            sum_c += 1;
        }
        for(int i=0; i < m; i++){
            sum_y -= houses[n+i].second;
            sum_x -= houses[n+i].first;
            sum_c -= 1;
        }
        lp.set_a(b, totalhouses, -sum_y);
        lp.set_a(c, totalhouses, -sum_c);
        lp.set_b(totalhouses, budget + sum_x);
        s = CGAL::solve_linear_program(lp, ET());
        if(s.is_infeasible()){
            std::cout<<"Bankrupt!\n"; return;
        }
    }
    int costraint = totalhouses+1;
    for(int i=0; i < totalhouses; i++){
        lp.set_a(dmax, costraint, -1);
        lp.set_a(b, costraint, -houses[i].first);
        lp.set_a(c2, costraint, 1);
        lp.set_b(costraint, -houses[i].second);
        costraint++;
        lp.set_a(dmax, costraint, -1);
        lp.set_a(b, costraint, houses[i].first);
        lp.set_a(c2, costraint, -1);
        lp.set_b(costraint, houses[i].second);
        costraint++;
    }
    lp.set_c(dmax, 1);
    s = CGAL::solve_linear_program(lp, ET());
    if(s.is_optimal()){
        CGAL::Quotient<ET> res = s.objective_value();
        std::cout<<std::setprecision(0)<<std::fixed<<std::ceil(CGAL::to_double(res))<<"\n";
    }
}
int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int t;
    std::cin>>t;
    while(t--){
        solve();
    }
}