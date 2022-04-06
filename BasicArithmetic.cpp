#include "BasicArithmetic.hpp"
using namespace std;
BasicArithmetic::BasicArithmetic(int B, int precision, int roundoffValue)

{
    this->B = B;
    this->roundoffValue = roundoffValue;
    this->precision = precision;
}
void BasicArithmetic::print_number(vector<int> d)
{
    for (int i = d.size() - 1; i > -1; i--)
    {
        cout << d[i] << "";
    }

    cout << endl;
}

void BasicArithmetic::print_pair_number(pair<vector<int>, int> d)
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
vector<int> BasicArithmetic::addition(vector<int> a, vector<int> b)
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

vector<int> BasicArithmetic::pad_zeroes(vector<int> a, int n)
{
    vector<int> c;

    for (int i = 0; i < n; i++)
        c.push_back(0);

    for (int i = 0; i < a.size(); i++)
        c.push_back(a[i]);

    return c;
}

pair<vector<int>, int> BasicArithmetic::addition_real(vector<int> a, int power_a, vector<int> b, int power_b)
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

    c = addition(a, b);

    return make_pair(c, power_a);
}
int BasicArithmetic::comparator(vector<int> a, vector<int> b) // returns 1 if a is greater than b else 0
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

vector<int> BasicArithmetic::adjustCarry(vector<int> a, int index) // returns a vector after adjusting the carry
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
vector<int> BasicArithmetic::adjustSign(vector<int> a)
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
vector<int> BasicArithmetic::adjustNegativeSign(vector<int> a)
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
vector<int> BasicArithmetic::removeXZeroes(vector<int> a, int num)
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
vector<int> BasicArithmetic::subtraction(vector<int> a, vector<int> b) // b-a

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

                b = adjustCarry(b, i);
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
    print_number(c);
    return c;
}
vector<int> BasicArithmetic::checkAndSubtract(vector<int> a, vector<int> b)
{
    vector<int> d;
    if (comparator(a, b)) // a is greater than b
    {
        d = subtraction(b, a); // d=a-b
        d = adjustSign(d);
    }
    else
    {

        d = subtraction(a, b); // d=b-a
        d = adjustNegativeSign(d);
    }
    print_number(d);
    return d;
}
pair<vector<int>, int> BasicArithmetic::subtraction_real(vector<int> a, int power_a, vector<int> b, int power_b)
{

    int l1 = a.size();
    int l2 = b.size();
    vector<int> c; // answer
    int carry = 0;
    print_number(a);
    print_number(b);
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

    c = checkAndSubtract(a, b);

    return make_pair(c, power_a);
}
vector<int> BasicArithmetic::multiplication(vector<int> a, vector<int> b)
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

pair<vector<int>, int> BasicArithmetic::multiplication_real(vector<int> a, int power_a, vector<int> b, int power_b)
{
    vector<int> c = multiplication(a, b);
    return make_pair(c, power_a + power_b);
}

void BasicArithmetic::checkAndAdd(vector<int> a, vector<int> b)
{
    vector<int> c = addition(a, b);
    c = adjustSign(c);
    print_number(c);
}
vector<int> BasicArithmetic::checkAndMultiply(vector<int> a, vector<int> b)
{
    vector<int> e = multiplication(a, b);
    e = adjustSign(e);
    print_number(e);
    return e;
}
vector<int> pad_zeros_at_end_withparameter(vector<int> a, int n)
{
    for (int i = 0; i < n; i++)
    {
        a.push_back(0);
    }

    return a;
}
vector<int> BasicArithmetic::karatsuba(vector<int> a, vector<int> b)
{
    int l = a.size();
    int k = b.size();
    if (l < k)
    {
        a = pad_zeros_at_end_withparameter(a, k - l);
    }
    else
    {
        b = pad_zeros_at_end_withparameter(b, l - k);
    }

    if (l == 1 || k == 1) // Base case
        return multiplication(a, b);

    vector<int> a1, a0, b1, b0;

    for (int i = l / 2; i < l; i++)
        a1.push_back(a[i]);

    for (int i = 0; i < l / 2; i++)
        a0.push_back(a[i]);

    for (int i = k / 2; i < k; i++)
        b1.push_back(b[i]);

    for (int i = 0; i < k / 2; i++)
        b0.push_back(b[i]);

    vector<int> z1 = karatsuba(a1, b1);
    cout << "a1*b1" << endl;
    print_number(z1);
    vector<int> z2 = karatsuba(a0, b0);

    cout << "a0*b0" << endl;

    vector<int> z3 = karatsuba(addition(a1, a0), addition(b1, b0));

    vector<int> z4 = subtraction(z3, addition(z1, z2));
    cout << "z3";
    print_number(z3);
    cout << "z1";
    print_number(z1);
    cout << "z2";
    print_number(z2);
    cout << "z4 = ";
    print_number(z4);
    return z4;
}

vector<int> BasicArithmetic::division_one_digit(vector<int> a, int d)
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

vector<int> BasicArithmetic::division(vector<int> a, vector<int> b)
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

vector<int> BasicArithmetic::pad_zeroes_at_end(vector<int> a)
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
vector<int> BasicArithmetic::removeTrailingZeroes(vector<int> a)
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

pair<vector<int>, int> BasicArithmetic::division_real(vector<int> a, int power_a, vector<int> b, int power_b)
{
    vector<int> c = pad_zeroes_at_end(a);
    static int count = 0;
    count++;
    b = removeXZeroes(b, b.size() + power_b);
    c = division(c, b);
    return make_pair(c, power_a - power_b - count * precision);
}

pair<vector<int>, int> BasicArithmetic::roundoff(pair<vector<int>, int> a, int n)
{
    pair<vector<int>, int> ans;

    for (int i = a.first.size() - n; i < a.first.size(); i++)
        ans.first.push_back(a.first[i]);
    ans.second = a.first.size() - n + a.second;
    return ans;
}

pair<vector<int>, int> BasicArithmetic::squareroot(vector<int> R, int power_R, vector<int> x0, int power_x0)
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
        R_by_Xn = division_real(R, power_R, x0, power_x0);

        pair<vector<int>, int> numerator = addition_real(x0, power_x0, R_by_Xn.first, R_by_Xn.second);

        answer = multiplication_real(numerator.first, numerator.second, half, -1);

        x0 = answer.first;
        power_x0 = answer.second;
        count++;
    }
    return answer;
}

vector<int> BasicArithmetic::removeLeadingZereos(vector<int> a)

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
pair<vector<int>, int> BasicArithmetic::pi()
{
    // Constants
    vector<int> two; // 2
    two.push_back(2);

    vector<int> b;
    b.push_back(4); // 1.4
    b.push_back(1);
    pair<vector<int>, int> one;
    one.first = {1};
    one.second = 0;

    pair<vector<int>, int> a0 = squareroot(two, 0, b, -1); // 2**0.5
    pair<vector<int>, int> b0;
    b0.first = {0};
    b0.second = 0;
    pair<vector<int>, int> five;
    five.first = {5};
    five.second = -1;

    pair<vector<int>, int> p0 = addition_real(two, 0, a0.first, a0.second);

    int count = 0;

    while (count < 9)
    {

        pair<vector<int>, int> one_plus_bn = addition_real(b0.first, b0.second, one.first, one.second); // 1+b

        pair<vector<int>, int> root_an = squareroot(a0.first, a0.second, b, -1); // root a

        pair<vector<int>, int> an_plus_bn = addition_real(b0.first, b0.second, a0.first, a0.second); // a+b

        pair<vector<int>, int> numerator_bn1 = multiplication_real(one_plus_bn.first, one_plus_bn.second, root_an.first, root_an.second); //(1+b)rootA
        b0 = division_real(numerator_bn1.first, numerator_bn1.second, an_plus_bn.first, an_plus_bn.second);                               // b

        b0 = roundoff(b0, roundoffValue);

        pair<vector<int>, int> one_by_root_an = division_real(one.first, one.second, root_an.first, root_an.second); // 1/rootA

        pair<vector<int>, int> numerator_an1 = addition_real(root_an.first, root_an.second, one_by_root_an.first, one_by_root_an.second); // rootA+1/rootA

        a0 = multiplication_real(five.first, five.second, numerator_an1.first, numerator_an1.second); // divide by 2
        a0 = roundoff(a0, roundoffValue);

        pair<vector<int>, int> one_plus_an1 = addition_real(one.first, one.second, a0.first, a0.second); // 1+a

        pair<vector<int>, int> pn_times_bn1 = multiplication_real(p0.first, p0.second, b0.first, b0.second); // p*b

        pair<vector<int>, int> numerator_pn1 = multiplication_real(one_plus_an1.first, one_plus_an1.second, pn_times_bn1.first, pn_times_bn1.second);

        pair<vector<int>, int> one_plus_bn1 = addition_real(one.first, one.second, b0.first, b0.second);

        p0 = division_real(numerator_pn1.first, numerator_pn1.second, one_plus_bn1.first, one_plus_bn1.second);
        p0.first = removeLeadingZereos(p0.first);
        p0 = roundoff(p0, roundoffValue);
        count++;
    }

    return p0;
}
