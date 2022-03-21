#include <bits/stdc++.h>
using namespace std;
class Arithmetic
{
    private:
        int Base;
    public:
        Arithmetic(int base);

        vector<int> Add(vector <int> number1, vector <int> number2);  //this returns a vector in which 0th index is lsb and nth index is msb.
        vector<int> Sub(vector <int> number1, vector <int> number2);
        vector <int> Mul(vector<int> number1, vector<int> number2);
        pair<vector<int>,vector<int>> Div(vector<int> number1, vector<int> number2);
        vector<int> decimal_after_division(vector<int>rem,vector<int>divisor);

};