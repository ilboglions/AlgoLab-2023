#include <iostream>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
typedef int IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;
void solve(const int & );
int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int t;
    std::cin>>t;
    while(t){
        solve(t);
        std::cin>>t;
    }
}
void solve(const int & p){
    int a,b;
    int coeff;
    int coeffz;
    std::cin>>a>>b;
    Program lp (CGAL::SMALLER, false, 0, false, 0);
    const int x = 0;
    const int y = 1;
    const int z = 2;
    if(p == 1){
        coeff=-1;
        coeffz=0;
    }
    else{
        coeff=1;
        coeffz=1;
    }
    lp.set_a(x, 0, coeff);
    lp.set_a(y, 1, coeff);
    lp.set_a(z, 2, coeff);
    lp.set_a(x, 3, -coeff);
    lp.set_a(y, 3, -coeff);
    lp.set_b(3,4);
    lp.set_a(x, 4, -4*coeff);
    lp.set_a(y, 4, -2*coeff);
    lp.set_a(z, 4, -coeff);
    lp.set_b(4,a*b);
    lp.set_a(x, 5, coeff);
    lp.set_a(y, 5, -coeff);
    lp.set_b(5, 1);
    lp.set_c(y, b*coeff);
    lp.set_c(x, a);
    lp.set_c(z,coeffz);
    Solution s = CGAL::solve_linear_program(lp, ET());
    if(!s.solves_linear_program(lp) || !s.is_optimal())
        std::cout<<"no\n";
    else{
        CGAL::Quotient<ET> res = s.objective_value();
        int result = (int)std::ceil(CGAL::to_double((res.numerator()/res.denominator())));
        std::cout<<coeff*result<<"\n";

    }
}