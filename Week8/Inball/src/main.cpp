#include <iostream>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
#include <vector>
#include <cmath>
using std::sqrt;
using std::vector;
typedef int IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;
void solve(int);
int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int t;
    std::cin>>t;
    while(t){
        solve(t);
        std::cin>>t;
    }
}
void solve(int n){
    int d;
    std::cin>>d;
    int ai, bi;
    Solution s;
    Program lp (CGAL::SMALLER, false, 0, false, 0);
    int denominator;
    lp.set_l(d,true,0);
    
    for(int i=0; i < n; i++){
        denominator=0;
        for(int j=0; j < d; j++){
            std::cin>>ai;
            lp.set_a(j, i, ai);
            denominator += ai*ai;
        }
        denominator = sqrt(denominator);
        lp.set_a(d, i, denominator);
        std::cin>>bi;
        lp.set_b(i, bi);
    }
    lp.set_c(d, -1);
    s = CGAL::solve_linear_program(lp, ET());
    if (s.is_optimal()) { 
        CGAL::Quotient<ET> res = s.objective_value();
        int result = -std::ceil(CGAL::to_double(res));
        std::cout<<result<<"\n";
    }
    else if (s.is_unbounded())
        std::cout<<"inf\n";
    else
        std::cout<<"none\n";
}