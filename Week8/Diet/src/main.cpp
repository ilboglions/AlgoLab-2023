#include <iostream>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
typedef int IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;
void solve(const int);

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

void solve(const int n){
    int m;
    std::cin>>m;
    int min,max;
    int price, tmp;
    Program lp (CGAL::SMALLER, true, 0, false, 0);
    for(int i=0; i< n; i++){
        std::cin>>min>>max;
        lp.set_b(i, max);
        lp.set_b(n+i, -min);
    }
    for(int i=0; i < m; i++){
        std::cin>>price;
        lp.set_c(i, price);
        for(int j=0; j < n; j++){
            std::cin>>tmp;
            lp.set_a(i,j, tmp);
            lp.set_a(i,n+j , -tmp);
        }
    }
    Solution s = CGAL::solve_linear_program(lp, ET());
    if(!s.solves_linear_program(lp) || !s.is_optimal())
        std::cout<<"No such diet.\n";
    else{
        CGAL::Quotient<ET> res = s.objective_value();
        int result = (int)std::floor(-CGAL::to_double((res.numerator()/res.denominator())));
        std::cout<<result<<"\n";
    }
}