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
        pair<vector<int>,vector<int>>  squareroot(vector<int>R,vector<int>x0,vector<int>decimalR,vector<int>decimalx0);
        pair<vector<int>,vector<int>> Add_with_dec(vector<int> number1,vector<int>dec1,vector<int> number2,vector<int>dec2);
        pair<vector<int>,vector<int>> Mul_with_dec(vector<int> number1,vector<int>dec1,vector<int> number2,vector<int>dec2);
        pair<vector<int>,vector<int>> Div_with_dec(vector<int> number1,vector<int>dec1,vector<int> number2,vector<int>dec2);

        pair<vector<int>,vector<int>> PI();
};