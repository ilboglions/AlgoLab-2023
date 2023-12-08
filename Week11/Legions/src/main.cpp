#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
#include <math.h>
using std::sqrt;

typedef long IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

void solve(){
    Program lp (CGAL::SMALLER, false, 0, false, 0);
    long xs,ys;
    int n;
    std::cin>>xs>>ys>>n; 
    long a,b,c,v; 
    long coeff;  
    const int X = 0; 
    const int Y = 1;
    const int T = 2;
    lp.set_l(T, true, 0);
    for(int i=0; i < n; i++){
        std::cin>>a>>b>>c>>v;
        if( a*xs + b*ys + c >= 0)
            coeff = 1;
        else coeff = -1;
        lp.set_a(X,i, -coeff * a); lp.set_a(Y, i,  -coeff * b); lp.set_a(T, i , v*((long)sqrt(a*a + b*b))); lp.set_b(i, coeff*c);
    }
    lp.set_c(T, -1);                                     
    Solution s = CGAL::solve_linear_program(lp, ET());
    if(s.solves_linear_program(lp) && s.is_optimal()){
        CGAL::Quotient<ET> res = s.objective_value();
        long result = (long)std::floor(-CGAL::to_double((res.numerator()/res.denominator())));
        std::cout<<result<<"\n";
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