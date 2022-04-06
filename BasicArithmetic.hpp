

#include <bits/stdc++.h>
using namespace std;
class BasicArithmetic
{
private:
    int B, precision, roundoffValue;

public:
    BasicArithmetic(int B, int precision, int roundoffValue);
    void print_number(vector<int> d);
    void print_pair_number(pair<vector<int>, int> d);
    vector<int> addition(vector<int> a, vector<int> b);
    vector<int> pad_zeroes(vector<int> a, int n);
    pair<vector<int>, int> addition_real(vector<int> a, int power_a, vector<int> b, int power_b);
    int comparator(vector<int> a, vector<int> b); // returns 1 if a is greater than b else 0
    int comparator(vector<int> a, vector<int> b); // returns 1 if a is greater than b else 0
    vector<int> adjustCarry(vector<int> a, int index);
    vector<int> adjustSign(vector<int> a);
    vector<int> adjustNegativeSign(vector<int> a);
    vector<int> removeXZeroes(vector<int> a, int num);
    vector<int> subtraction(vector<int> a, vector<int> b); // b-a
    vector<int> checkAndSubtract(vector<int> a, vector<int> b);
    pair<vector<int>, int> subtraction_real(vector<int> a, int power_a, vector<int> b, int power_b);
    vector<int> multiplication(vector<int> a, vector<int> b);
    pair<vector<int>, int> multiplication_real(vector<int> a, int power_a, vector<int> b, int power_b);
    void checkAndAdd(vector<int> a, vector<int> b);
    vector<int> checkAndMultiply(vector<int> a, vector<int> b);
    vector<int> karatsuba(vector<int> a, vector<int> b);
    vector<int> division_one_digit(vector<int> a, int d);
    vector<int> division(vector<int> a, vector<int> b);
    vector<int> pad_zeroes_at_end(vector<int> a);
    vector<int> removeTrailingZeroes(vector<int> a);
    pair<vector<int>, int> division_real(vector<int> a, int power_a, vector<int> b, int power_b);
    pair<vector<int>, int> roundoff(pair<vector<int>, int> a, int n);
    pair<vector<int>, int> squareroot(vector<int> R, int power_R, vector<int> x0, int power_x0);
    vector<int> removeLeadingZereos(vector<int> a);
    pair<vector<int>, int> pi();
};