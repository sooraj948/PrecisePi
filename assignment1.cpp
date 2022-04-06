#include <vector>
#include <string>
#include <iostream>
#include <math.h>
// #include <pair>
#include <algorithm>

#include <utility>
using namespace std;

// #define B 10
#define precision 75
#define roundoffValue 500

void print_number(vector<int> d)
{
    for (int i = d.size() - 1; i > -1; i--)
    {
        cout << d[i] << "";
    }

    cout << endl;
}

void print_pair_number(pair<vector<int>, int> d)
{

    int i;
    for (i = d.first.size() - 1; i > -d.second - 1; i--)
    {
        cout << d.first[i] << "";
    }
    cout << ".";
    for (; i > -1; i--)
    {
        cout << d.first[i] << "";
    }

    cout << endl;
}
vector<int> addition(vector<int> a, vector<int> b, int B)
{
    int l1 = a.size();
    int l2 = b.size();

    vector<int> c;

    int carry = 0;
    if (l1 < l2)
    {
        for (int i = 0; i < l1; i++)
        {
            c.push_back((a[i] + b[i] + carry) % B);
            carry = (a[i] + b[i] + carry) / B;
        }

        for (int i = l1; i < l2; i++)
        {

            c.push_back((b[i] + carry) % B);
            carry = (b[i] + carry) / B;
        }
    }

    else
    {
        for (int i = 0; i < l2; i++)
        {
            c.push_back((a[i] + b[i] + carry) % B);
            carry = (a[i] + b[i] + carry) / B;
        }

        for (int i = l2; i < l1; i++)
        {
            c.push_back((a[i] + carry) % B);
            carry = (a[i] + carry) / B;
        }
    }

    if (carry)
        c.push_back(carry);

    return c;
}

vector<int> pad_zeroes(vector<int> a, int n)
{
    vector<int> c;

    for (int i = 0; i < n; i++)
        c.push_back(0);

    for (int i = 0; i < a.size(); i++)
        c.push_back(a[i]);

    return c;
}
pair<vector<int>, int> addition_real(vector<int> a, int power_a, vector<int> b, int power_b, int B)
{

    int l1 = a.size();
    int l2 = b.size();
    vector<int> c; // answer
    int carry = 0;

    if (power_a < power_b)
    {
        b = pad_zeroes(b, power_b - power_a);
        power_b = power_a;
    }
    else
    {
        a = pad_zeroes(a, -power_b + power_a);
        power_a = power_b;
    }

    c = addition(a, b, B);

    return make_pair(c, power_a);
}
int comparator(vector<int> a, vector<int> b) // returns 1 if a is greater than b else 0
{
    if (a.size() > b.size())
        return 1;
    else if (a.size() < b.size())
        return 0;
    else
    {
        for (int i = a.size() - 1; i >= 0; i--)
        {
            if (a[i] > b[i])
                return 1;
            else if (a[i] < b[i])
                return 0;
        }
    }
    return 0;
}

vector<int> adjustCarry(vector<int> a, int index, int B) // returns a vector after adjusting the carry
{
    for (int i = index + 1; i < a.size(); i++)
    {
        if (a[i] != 0)
        {
            a[i] -= 1;
            for (int j = index + 1; j < i; j++)
            {
                a[j] += B - 1;
            }
            a[index] += B;
        }
    }

    return a;
}
vector<int> adjustSign(vector<int> a)
{
    for (auto it = a.end() - 1; it != a.begin(); --it)
    {
        if (*it == 0)
        {
            a.erase(it);
        }
        else
        {
            break;
        }
    }
    return a;
}
vector<int> adjustNegativeSign(vector<int> a)
{
    for (auto it = a.end() - 1; it != a.begin(); --it)
    {
        if (*it == 0)
        {
            a.erase(it);
        }
        else
        {
            (*it) *= -1;
            break;
        }
    }
    return a;
}
vector<int> removeXZeroes(vector<int> a, int num)
{

    for (auto it = a.end() - 1; it != a.begin(); --it)
    {
        if (num == 1)
        {

            break;
        }
        num--;
        if (*it == 0)
        {
            a.erase(it);
        }
        else
        {
            break;
        }
    }
    return a;
}
vector<int> subtraction(vector<int> a, vector<int> b, int B) // b-a

{
    int l1 = a.size(); // always less than l2
    int l2 = b.size();
    vector<int> c;

    int carry = 0;
    if (l1 == l2)
    {
        for (int i = 0; i < l1; i++)
        {

            c.push_back((-a[i] + b[i] + carry) % B);
            carry = (-a[i] + b[i] + carry) / B;
        }

        for (int i = l1; i < l2; i++)
        {

            c.push_back((b[i] + carry) % B);

            carry = (b[i] + carry) / B;
        }

        if (carry)
            c.push_back(carry);
    }
    else
    {
        for (int i = 0; i < l1; i++)
        {
            if (a[i] < b[i])
            {
                c.push_back((-a[i] + b[i] + carry) % B);
                carry = (-a[i] + b[i] + carry) / B;
            }
            else
            {

                b = adjustCarry(b, i, B);
                c.push_back((-a[i] + b[i] + carry) % B);
                carry = (-a[i] + b[i] + carry) / B;
            }
        }
        for (int i = l1; i < l2; i++)
        {

            c.push_back((b[i] + carry) % B);
            carry = (b[i] + carry) / B;
        }

        if (carry)
            c.push_back(carry);
    }

    return c;
}
vector<int> checkAndSubtract(vector<int> a, vector<int> b, int B)
{
    vector<int> d;
    if (comparator(a, b)) // a is greater than b
    {
        d = subtraction(b, a, B); // d=a-b
        d = adjustSign(d);
    }
    else
    {

        d = subtraction(a, b, B); // d=b-a
        d = adjustNegativeSign(d);
    }
    return d;
}
pair<vector<int>, int> subtraction_real(vector<int> a, int power_a, vector<int> b, int power_b, int B)
{

    int l1 = a.size();
    int l2 = b.size();
    vector<int> c; // answer
    int carry = 0;

    if (power_a < power_b)
    {
        b = pad_zeroes(b, power_b - power_a);
        power_b = power_a;
    }
    else
    {
        a = pad_zeroes(a, -power_b + power_a);
        power_a = power_b;
    }

    c = checkAndSubtract(a, b, B);

    return make_pair(c, power_a);
}
vector<int> multiplication(vector<int> a, vector<int> b, int B)
{

    int l = a.size();
    int k = b.size();
    vector<int> c;

    for (int i = 0; i < k + l; i++)
        c.push_back(0);

    int carry = 0;
    for (int i = 0; i < k; i++)
    {
        carry = 0;
        for (int j = 0; j < l; j++)
        {
            int temp = a[j] * b[i] + c[i + j] + carry;

            c[i + j] = temp % B;
            carry = temp / B;
        }

        c[i + l] = carry;
    }

    return c;
}

pair<vector<int>, int> multiplication_real(vector<int> a, int power_a, vector<int> b, int power_b, int B)
{
    vector<int> c = multiplication(a, b, B);
    return make_pair(c, power_a + power_b);
}

void checkAndAdd(vector<int> a, vector<int> b, int B)
{
    vector<int> c = addition(a, b, B);
    c = adjustSign(c);
}
vector<int> checkAndMultiply(vector<int> a, vector<int> b, int B)
{
    vector<int> e = multiplication(a, b, B);
    e = adjustSign(e);
    return e;
}
vector<int> karatsuba(vector<int> a, vector<int> b, int B)
{
    int l = a.size();
    int k = b.size();

    if (l == 1 || k == 1) // B case
        return multiplication(a, b, B);

    vector<int> a1, a0, b1, b0;

    for (int i = l / 2; i < l; i++)
        a1.push_back(a[i]);

    for (int i = 0; i < l / 2; i++)
        a0.push_back(a[i]);

    for (int i = k / 2; i < k; i++)
        b1.push_back(b[i]);

    for (int i = 0; i < k / 2; i++)
        b0.push_back(b[i]);

    vector<int> z1 = karatsuba(a1, b1, B);
    vector<int> z2 = karatsuba(a0, b0, B);

    vector<int> z3 = karatsuba(addition(a1, a0, B), addition(b1, b0, B), B);

    vector<int> z4 = checkAndSubtract(addition(z1, z2, B), z3, B);

    return z4;
}

vector<int> division_one_digit(vector<int> a, int d, int B)
{
    int hi = 0;
    int k = a.size();
    vector<int> q;
    for (int i = k - 1; i > -1; i--)
        q.push_back(0);

    for (int i = k - 1; i > -1; i--)
    {
        int temp = hi * B + a[i];
        q[i] = temp / d;
        hi = temp % d;
    }
    return q;
}
pair<vector<int>, vector<int>> divisionWithRemainder(vector<int> a, vector<int> b, int B)
{
    vector<int> r;
    vector<int> q;
    int carry = 0;
    int temp;
    int k = a.size();
    int l = b.size();
    int d = k - l;

    for (int i = d; i >= 0; i--)
    {
        q.push_back(0);
    }
    r = a;

    r.push_back(0);

    int denom = 1;

    for (int i = k - l; i >= 0; i--)
    {
        q[i] = ((r[i + l] * B) + r[i + l - 1]) / b[l - 1];

        if (q[i] >= B)
        {
            q[i] = B - 1;
        }
        carry = 0;
        for (int j = 0; j < l; j++)
        {
            temp = r[i + j] - (q[i] * b[j]) + carry;
            carry = temp / B;
            r[i + j] = temp % B;
            if (r[i + j] < 0)
            {
                carry -= 1;
                r[i + j] += B;
            }
        }
        r[i + l] = r[i + l] + carry;
        while (r[i + l] < 0)
        {
            carry = 0;
            for (int j = 0; j < l; j++)
            {
                temp = r[i + j] + b[j] + carry;
                carry = temp / B;
                r[i + j] = temp % B;
                if (r[i + j] < 0)
                {
                    carry -= 1;
                    r[i + j] += B;
                }
            }
            r[i + l] += carry;
            q[i] -= 1;
        }
    }

    return make_pair(q, r);
}

vector<int> division(vector<int> a, vector<int> b, int B)
{
    vector<int> r;
    vector<int> q;
    int carry = 0;
    int temp;
    int k = a.size();
    int l = b.size();
    int d = k - l;

    for (int i = d; i >= 0; i--)
    {
        q.push_back(0);
    }
    r = a;

    r.push_back(0);

    int denom = 1;

    for (int i = k - l; i >= 0; i--)
    {
        q[i] = ((r[i + l] * B) + r[i + l - 1]) / b[l - 1];

        if (q[i] >= B)
        {
            q[i] = B - 1;
        }
        carry = 0;
        for (int j = 0; j < l; j++)
        {
            temp = r[i + j] - (q[i] * b[j]) + carry;
            carry = temp / B;
            r[i + j] = temp % B;
            if (r[i + j] < 0)
            {
                carry -= 1;
                r[i + j] += B;
            }
        }
        r[i + l] = r[i + l] + carry;
        while (r[i + l] < 0)
        {
            carry = 0;
            for (int j = 0; j < l; j++)
            {
                temp = r[i + j] + b[j] + carry;
                carry = temp / B;
                r[i + j] = temp % B;
                if (r[i + j] < 0)
                {
                    carry -= 1;
                    r[i + j] += B;
                }
            }
            r[i + l] += carry;
            q[i] -= 1;
        }
    }

    return q;
}

vector<int> pad_zeroes_at_end(vector<int> a)
{
    vector<int> result;
    static int count = 0;
    count++;

    for (int i = 0; i < count * precision; i++)
    {
        result.push_back(0);
    }
    // }
    for (int i = 0; i < a.size(); i++)
    {
        result.push_back(a[i]);
    }
    return result;
}
vector<int> removeTrailingZeroes(vector<int> a)
{
    for (auto it = a.begin(); it != a.end(); ++it)
    {
        if (*it == 0)
        {
            a.erase(it);
        }
        else
        {
            break;
        }
    }

    return a;
}

pair<vector<int>, int> division_real(vector<int> a, int power_a, vector<int> b, int power_b, int B)
{
    vector<int> c = pad_zeroes_at_end(a);
    static int count = 0;
    count++;
    b = removeXZeroes(b, b.size() + power_b);
    c = division(c, b, B);
    return make_pair(c, power_a - power_b - count * precision);
}

pair<vector<int>, int> roundoff(pair<vector<int>, int> a, int n)
{
    pair<vector<int>, int> ans;

    for (int i = a.first.size() - n; i < a.first.size(); i++)
        ans.first.push_back(a.first[i]);
    ans.second = a.first.size() - n + a.second;
    return ans;
}

pair<vector<int>, int> squareroot(vector<int> R, int power_R, vector<int> x0, int power_x0, int B)
{

    vector<int> two;
    two.push_back(2);
    int count = 0;

    vector<int> half;
    half.push_back(B / 2);

    pair<vector<int>, int> answer;
    while (count < precision / 5)
    {
        pair<vector<int>, int> R_by_Xn;
        R_by_Xn = division_real(R, power_R, x0, power_x0, B);

        pair<vector<int>, int> numerator = addition_real(x0, power_x0, R_by_Xn.first, R_by_Xn.second, B);

        answer = multiplication_real(numerator.first, numerator.second, half, -1, B);

        x0 = answer.first;
        power_x0 = answer.second;
        count++;
    }
    return answer;
}
vector<int> removeLeadingZereos(vector<int> a)
{
    for (auto it = a.end() - 1; it != a.begin(); --it)
    {
        if (*it == 0)
        {
            a.erase(it);
        }
        else
        {
            break;
        }
    }
    return a;
}
bool isZero(vector<int> a)
{
    for (int i = 0; i < a.size(); i++)
    {
        if (a[i] != 0)
        {
            return false;
        }
    }
    return true;
}

vector<int> DecimalToBaseB(vector<int> a, int b, int B) //
{
    pair<vector<int>, vector<int>> divide;
    vector<int> answer;
    vector<int> quotient, remainder;
    vector<int> base;
    base.push_back(b);
    while (!isZero(a))
    {
        divide = divisionWithRemainder(a, base, B);
        divide.second = removeLeadingZereos(divide.second);
        divide.first = removeLeadingZereos(divide.first);

        int number = 0;

        for (int i = divide.second.size() - 1; i >= 0; i--)
        {

            cout << "The current digit is = " << divide.second[i] << endl;
            number += divide.second[i] * (int)(pow(10, i));
            cout << "The value of number = " << number << endl;
        }
        answer.push_back(number);
        a = divide.first;
    }
    vector<int> result;
    for (int i = 0; i < answer.size(); i++)
    {
        result.push_back(answer[i]);
    }
    return result;
}
vector<int> getInteger(vector<int> a, int power_a)
{
    vector<int> integer;
    for (int i = power_a; i < a.size(); i++)
    {
        integer.push_back(a[i]);
    }
    return integer;
}
vector<int> getDecimal(vector<int> a, int power_a)
{

    vector<int> decimal;
    for (int i = 0; i < power_a; i++)
    {
        decimal.push_back(a[i]);
    }
    return decimal;
}
pair<vector<int>, int> DecimalToBaseBReal(vector<int> a, int p, int b, int B) // 29.125 =  5 2 1 9 2 , -3
{
    vector<int> base;
    base.push_back(b);
    vector<int> integer, decimal;
    int power_a = p * -1;
    decimal = getDecimal(a, power_a);
    integer = getInteger(a, power_a);

    vector<int> result_integer = DecimalToBaseB(integer, b, B); // 1 1 0 1

    pair<vector<int>, int> product;
    vector<int> beforeDecimal, afterDecimal;
    vector<int> answer;

    vector<int> result;
    for (int i = answer.size() - 1; i >= 0; i--)
    {
        result.push_back(answer[i]);
    }
    for (int i = 0; i < result_integer.size(); i++)
    {
        result.push_back(result_integer[i]);
    }

    return make_pair(result, answer.size() * -1);
}
vector<int> TenToBaseB(int b, int B)
{
    vector<int> ten;
    ten.push_back(0);
    ten.push_back(1);
    pair<vector<int>, vector<int>> divide;
    vector<int> answer;
    vector<int> quotient, remainder;
    vector<int> base;
    base.push_back(b);
    while (!isZero(ten))
    {
        divide = divisionWithRemainder(ten, base, 10);
        divide.second = removeLeadingZereos(divide.second);
        divide.first = removeLeadingZereos(divide.first);

        int number = 0;

        for (int i = divide.second.size() - 1; i >= 0; i--)
        {

            number += divide.second[i] * (int)(pow(10, i));
        }

        answer.push_back(number);
        ten = divide.first;
    }

    vector<int> result;
    for (int i = 0; i < answer.size(); i++)
    {
        result.push_back(answer[i]);
    }
    return result;
}

vector<int> getIntegerPart(vector<int> a, vector<int> base, int B)
{
    pair<vector<int>, vector<int>> divide;
    vector<int> answer;
    vector<int> quotient, remainder;
    while (!isZero(a))
    {
        divide = divisionWithRemainder(a, base, B);
        divide.second = removeLeadingZereos(divide.second);
        if (!isZero(divide.first))
        {
            divide.first = removeLeadingZereos(divide.first);
        }
        if (divide.first.size() == 0)
        {
            divide.first.push_back(0);
        }

        int number = 0;

        for (int i = divide.second.size() - 1; i >= 0; i--)
        {

            number += divide.second[i] * (int)(pow(B, i));
        }
        answer.push_back(number);
        a = divide.first;
    }
    vector<int> result;
    for (int i = 0; i < answer.size(); i++)
    {
        result.push_back(answer[i]);
    }
    return result;
}
pair<vector<int>, int> BaseBToDecimal(vector<int> a, int p, int b, int B)
{
    vector<int> base = TenToBaseB(b, B); // ten in base b format

    vector<int> integer, decimal;
    int power_a = p * -1;
    decimal = getDecimal(a, power_a); // gets the decimal portion of the number
    integer = getInteger(a, power_a);

    vector<int> result_integer = getIntegerPart(integer, base, B); // 1 1 0 1

    pair<vector<int>, int> product;
    vector<int> beforeDecimal, afterDecimal;
    vector<int> answer;

    do
    {
        product = multiplication_real(decimal, p, base, 0, B); // 0.1875*2 = 0.3750
        beforeDecimal = getInteger(product.first, product.second * -1);
        afterDecimal = getDecimal(product.first, product.second * -1); // product.first = removeLeadingZereos(product.first);
        int number = 0;
        for (int i = 0; i <= beforeDecimal.size() - 1; i++)
        {

            number += beforeDecimal[i] * (int)(pow(B, i));
        }
        answer.push_back(number);

        decimal = afterDecimal;

        p = afterDecimal.size() * -1;

        if (answer.size() == a.size())
        {
            cout << "Breaking" << endl;
            break;
        }
    } while (!isZero(afterDecimal));

    vector<int> result;
    for (int i = answer.size() - 1; i >= 0; i--)
    {
        result.push_back(answer[i]);
    }
    for (int i = 0; i < result_integer.size(); i++)
    {
        result.push_back(result_integer[i]);
    }

    return make_pair(result, answer.size() * -1);
}
pair<vector<int>, int> pi(int B)
{
    // Constants
    vector<int> two; // 2
    two.push_back(2);

    vector<int> b;
    b.push_back(4); // 1.4
    b.push_back(1);
    pair<vector<int>, int> one;
    one.first.push_back(1);
    one.second = 0;

    pair<vector<int>, int> a0 = squareroot(two, 0, b, -1, B); // 2**0.5
    pair<vector<int>, int> b0;
    b0.first.push_back(0);
    b0.second = 0;
    pair<vector<int>, int> five;
    five.first.push_back(B / 2);
    five.second = -1;

    pair<vector<int>, int> p0 = addition_real(two, 0, a0.first, a0.second, B);

    int count = 0;

    while (count < 9)
    {

        pair<vector<int>, int> one_plus_bn = addition_real(b0.first, b0.second, one.first, one.second, B); // 1+b

        pair<vector<int>, int> root_an = squareroot(a0.first, a0.second, b, -1, B); // root a

        pair<vector<int>, int> an_plus_bn = addition_real(b0.first, b0.second, a0.first, a0.second, B); // a+b

        pair<vector<int>, int> numerator_bn1 = multiplication_real(one_plus_bn.first, one_plus_bn.second, root_an.first, root_an.second, B); //(1+b)rootA
        b0 = division_real(numerator_bn1.first, numerator_bn1.second, an_plus_bn.first, an_plus_bn.second, B);                               // b

        b0 = roundoff(b0, roundoffValue);

        pair<vector<int>, int> one_by_root_an = division_real(one.first, one.second, root_an.first, root_an.second, B); // 1/rootA

        pair<vector<int>, int> numerator_an1 = addition_real(root_an.first, root_an.second, one_by_root_an.first, one_by_root_an.second, B); // rootA+1/rootA

        a0 = multiplication_real(five.first, five.second, numerator_an1.first, numerator_an1.second, B); // divide by 2
        a0 = roundoff(a0, roundoffValue);

        pair<vector<int>, int> one_plus_an1 = addition_real(one.first, one.second, a0.first, a0.second, B); // 1+a

        pair<vector<int>, int> pn_times_bn1 = multiplication_real(p0.first, p0.second, b0.first, b0.second, B); // p*b

        pair<vector<int>, int> numerator_pn1 = multiplication_real(one_plus_an1.first, one_plus_an1.second, pn_times_bn1.first, pn_times_bn1.second, B);

        pair<vector<int>, int> one_plus_bn1 = addition_real(one.first, one.second, b0.first, b0.second, B);

        p0 = division_real(numerator_pn1.first, numerator_pn1.second, one_plus_bn1.first, one_plus_bn1.second, B);
        p0.first = removeLeadingZereos(p0.first);
        p0 = roundoff(p0, roundoffValue);
        count++;
    }

    return p0;
}

int main()
{

    // cout << "karatsuba multiplication" << endl;

    // vector<int> a = {4, 2, 5, 5, 7, 3, 0, 1, 1, 3};
    // vector<int> b = {5, 2, 6, 0, 4, 1, 7, 3};
    // vector<int> d = checkAndSubtract(b, a);
    // print_number(d);
    // vector<int> c = karatsuba(a, b);
    // print_number(c);
    // print_pair_number(make_pair(a, -4));
    // cout << "PI:" << endl;
    // pair<vector<int>, int> PI = pi(10);
    // print_pair_number(PI);
    // cout << "Base conversion" << endl;
    // vector<int> answer;
    // answer = DecimalToBaseB(b, 64);
    // print_number(answer);
    // print_pair_number(DecimalToBaseBReal(b, -6, 8,8));
    // print_pair_number(make_pair(a, -9));
    // cout << "Base to decimal conversion" << endl;
    // answer = BaseBToDecimal(b, 64);

    // TenToBaseB(8, 2);
    int check, prec, base_digits;

    cin >> check >> prec >> base_digits;

    int base = 1 << base_digits; // 2**Base_digits
    cout << base << endl;
    if (check == 1)
    {
        // pi
        pair<vector<int>, int> PI = pi(base);

        print_pair_number(PI);

        PI = BaseBToDecimal(PI.first, PI.second, base, base);
        print_pair_number(PI);

        PI = roundoff(PI, prec + 1);

        print_pair_number(PI);
    }

    else
    {
        // root 2
        vector<int> two;
        two.push_back(2);
        vector<int> x0;
        x0 = {4,1,4,1};

        pair<vector<int>, int> root2 = squareroot(two, 0, x0, -3, base);
        root2 = BaseBToDecimal(root2.first, root2.second, base, base);
        root2 = roundoff(root2, prec + 1);

        print_pair_number(root2);
    }
    // pair<vector<int>, int> root2 = BaseBToDecimal(a, -9, 8, 8);
    // print_pair_number(root2);
    return 0;
}
