
#include <iostream>
using namespace std;

int main()
{
    int check,prec,base_digits;
    
    
    cin >> check >> prec >> base_digits;


    int base  = 1<<base_digits;//2**Base_digits
    cout << base << endl;
    if (check==1)
    {
        //pi
        pair<vector<int>, int> PI = pi(base);
        PI.first = roundoff(PI.first,prec+1);

        print_pair_number(PI);

    }

    else
    {
        //root 2
        vector<int> two ;
        two.push_back(2);
        vector<int> x0 ;
        x0.push_back(1);

        pair<vector<int>, int> root2 = squareroot(two,0,x0,0,base);
        root2.first = roundoff(root2.first,prec+1);

        print_pair_number(root2);

    }
}