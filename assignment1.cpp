#include <vector>
#include <string>
#include <iostream>
// #include <pair>
#include <utility>
using namespace std;

#define B 10
#define precision 100

void print_number(vector<int> d)
{
    for (int i = d.size() - 1; i > -1; i--)
    {
        cout << d[i] << "";
    }

    cout << endl;
}

void print_pair_number(pair<vector<int>,int> d)
{
    cout <<"0";
    int i;
    for ( i= d.first.size() - 1; i > -d.second-1 ; i--)
    {
        cout << d.first[i] << "";
    }
    cout<<".";
    for(;i>-1;i--)
    {
        cout << d.first[i] << "";

    }


    cout << endl;

}
vector<int> addition(vector<int> a, vector<int> b)
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
            // cout << "inside";
            // cout << "carry is " << carry << endl;
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
            // cout << "carry is " << carry << endl;
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
// assuming only positive numbers are passed

vector<int> pad_zeroes(vector<int> a, int n)
{
    vector<int> c;

    for (int i = 0; i < n; i++)
        c.push_back(0);

    for (int i = 0; i < a.size(); i++)
        c.push_back(a[i]);

    return c;
}
pair<vector<int>, int> addition_real(vector<int> a, int power_a, vector<int> b, int power_b)
{
    // power_a and b are the exponents of 10. always negative

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

    // print_number(a);
    // print_number(b);

    c = addition(a, b);

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

vector<int> adjustCarry(vector<int> a, int index) // returns a vector after adjusting the carry
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
    // cout << "adjusted vector is" << endl;

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
vector<int> subtraction(vector<int> a, vector<int> b) // b-a

{
    int l1 = a.size(); // always less than l2
    int l2 = b.size();
    vector<int> c;
    // cout << "size of a is =" << l1 << endl;
    // cout << "size of b is =" << l2 << endl;
    cout << "Subtraction of " << endl;
    print_number(b);
    print_number(a);
    int carry = 0;
    if (l1 == l2)
    {
        for (int i = 0; i < l1; i++)
        {

            c.push_back((-a[i] + b[i] + carry) % B);
            // cout << "i =" << i << " and c[i] = " << c[i] << endl;
            carry = (-a[i] + b[i] + carry) / B;
            // cout << b[i] << "-" << a[i] << endl;
            // cout << "carry is " << carry << endl;
        }

        for (int i = l1; i < l2; i++)
        {

            // cout << "doing from l1 to l2" << endl;
            c.push_back((b[i] + carry) % B);
            // cout << "i =" << i << " and c[i] = " << c[i] << endl;
            carry = (b[i] + carry) / B;

            // cout << "carry is " << carry << endl;
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
                // cout << "INSIDEEE" << endl;
                c.push_back((-a[i] + b[i] + carry) % B);
                // cout << "i =" << i << " and c[i] = " << c[i] << endl;
                carry = (-a[i] + b[i] + carry) / B;
                // cout << b[i] << "-" << a[i] << endl;
                // cout << "carry is " << carry << endl;
            }
            else
            {

                // cout << "i is less than l1-1" << endl;
                b = adjustCarry(b, i);
                // b[i + 1] -= 1;
                // b[i] += B;
                c.push_back((-a[i] + b[i] + carry) % B);
                // cout << "i =" << i << " and c[i] = " << c[i] << endl;
                carry = (-a[i] + b[i] + carry) / B;
                // cout << b[i] << "-" << a[i] << endl;
                // cout << "carry is " << carry << endl;
            }
        }
        for (int i = l1; i < l2; i++)
        {

            // cout << "doing from l1 to l2" << endl;
            c.push_back((b[i] + carry) % B);
            // cout << "i =" << i << " and c[i] = " << c[i] << endl;
            carry = (b[i] + carry) / B;

            // cout << "carry is " << carry << endl;
        }

        if (carry)
            c.push_back(carry);
    }
    cout << "b-a = " << endl;
    print_number(c);
    return c;
}
vector<int> checkAndSubtract(vector<int> a, vector<int> b)
{
    cout << "Subtract" << endl;
    vector<int> d;
    if (comparator(a, b)) // a is greater than b
    {
        // cout << "a-b" << endl;
        d = subtraction(b, a); // d=a-b
        d = adjustSign(d);
    }
    else
    {
        // cout << "b-a" << endl;
        d = subtraction(a, b); // d=b-a
        d = adjustNegativeSign(d);
        // d[d.size() - 1] *= -1;
    }
    print_number(d);
    return d;
}
pair<vector<int>, int> subtraction_real(vector<int> a, int power_a, vector<int> b, int power_b)
{ // here b>a .. has to be
    // power_a and b are the exponents of 10. always negative

    int l1 = a.size();
    int l2 = b.size();
    vector<int> c; // answer
    int carry = 0;
    cout << "number a =";
    print_number(a);
    cout << "number b =";
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
vector<int> multiplication(vector<int> a, vector<int> b)
{
    //     fori←0 to k+l−1 do ci ←0
    // for i ← 0 to k − 1 do
    // carry ← 0
    // for j ← 0 to l − 1 do
    // tmp ← aibj + ci+j + carry
    // (carry, ci+j ) ← QuoRem(tmp, B) ci+l ← carry

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
            // print_number(c);
            // cout << "carry is " << carry << endl;
        }

        c[i + l] = carry;
    }

    return c;
}

pair<vector<int>, int> multiplication_real(vector<int> a, int power_a, vector<int> b, int power_b)
{
    vector<int> c = multiplication(a, b);
    return make_pair(c, power_a + power_b);
}

void checkAndAdd(vector<int> a, vector<int> b)
{
    cout << "Adding" << endl;
    vector<int> c = addition(a, b);
    c = adjustSign(c);
    print_number(c);
}
vector<int> checkAndMultiply(vector<int> a, vector<int> b)
{
    cout << "Multiplication" << endl;
    vector<int> e = multiplication(a, b);
    e = adjustSign(e);
    print_number(e);
    return e;
}
vector<int> karatsuba(vector<int> a, vector<int> b)
{
    int l = a.size();
    int k = b.size();

    if (l == 1 || k == 1) // B case
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
    vector<int> z2 = karatsuba(a0, b0);

    vector<int> z3 = karatsuba(addition(a1, a0), addition(b1, b0));

    vector<int> z4 = subtraction(z3, addition(z1, z2));

    return z4;
}

vector<int> division_one_digit(vector<int> a, int d)
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
    // print_number(q);
    return q;
}
vector<int> division(vector<int> a, vector<int> b)
{
    vector<int> r;
    vector<int> q;
    int carry = 0;
    int temp;
    int k = a.size();
    int l = b.size();
    int d = k - l;
    // cout << l << " " << k << endl;

    for (int i = d; i >= 0; i--)
    {
        // printf("%d\n",i);
        q.push_back(0);
    }
    r = a;

    r.push_back(0);
    // cout << r.size() << endl;

    for (int i = k - l; i >= 0; i--)
    {
        q[i] = ((r[i + l] * B) + r[i + l - 1]) / b[l - 1];
        // q[i] += r[i + l - 1];
        // q[i] = q[i] / b[l - 1];

        if (q[i] >= B)
        {
            q[i] = B - 1;
        }
        carry = 0;
        // printf("%d %d\n",i,q[i]);
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
    if (a.size()<precision)
    {

        for (int i = 0; i < precision; i++)
        {
            result.push_back(0);
        }
    }
    for (int i = 0; i < a.size(); i++)
    {
        result.push_back(a[i]);
    }
    return result;
}
pair<vector<int>, int> division_real(vector<int> a, int power_a, vector<int> b, int power_b)
{
    vector<int> c = pad_zeroes_at_end(a);
    // print_number(c);
    cout <<" c is "<<endl;
    print_number(c);
    c = division(c, b);
    return make_pair(c, power_a - power_b - precision);
}
// pair<vector<int>, vector<int>> squareroot(vector<int> R, int power_R, vector<int> x0, int power_x0)
// {

//     vector<int> none0, const2;

//     const2.push_back(2);

//     int power_of_x0, power_of_x0_sq, count = 0;

//     while (count < precision)
//     {
//         pair<vector<int>, int> R_by_Xn;
//         R_by_Xn = division_real(R, power_R, x0, power_x0);

//         count++;
//     }
// }
pair<vector<int>, int> sq_root(vector<int> R, int power_R, vector<int> x0, int power_x0)
{
    static int count=0;
    count++;
    cout << "count is "<<count<<endl;
    pair<vector<int>, int> x;

    vector<int> half;
    half.push_back(5); //*10**-1
    half.push_back(0);

    pair<vector<int>, int> temp; // inside ()

    pair<vector<int>, int> R_by_x = division_real(R, power_R, x0, power_x0);

    cout << "R by x is "<<endl;
    //R_by_x is empty ??? check this
    // print_number(R_by_x.first);
    print_pair_number(R_by_x);


    temp = addition_real(x0, power_x0, R_by_x.first, R_by_x.second);
    cout <<"temp ";
    print_pair_number(temp);

    x = multiplication_real(half, -1, temp.first, temp.second);

    cout <<"intermediate x is "<<endl;

    // print_number(x.first);
    // cout <<x.second<<endl;
    print_pair_number(x);


    if (count<12) // some arbitrary precision
        return sq_root(R, power_R, x.first, x.second);
    else
        return x;
}

int main()
{

    vector<int> a;

    // a.push_back(2);
    // a.push_back(9);
    // a.push_back(9);
    // a.push_back(9);
    // a.push_back(1);
    a.push_back(2);
    // a.push_back(7);
    // a.push_back(7);
    // a.push_back(9);
    // a.push_back(9);

    vector<int> b;
    b.push_back(8);
    b.push_back(2);
    b.push_back(4);
    b.push_back(1);
    b.push_back(4);
    b.push_back(1);
    // b.push_back(0);
    // b.push_back(0);

    // b.push_back(1);
    print_number(a);
    print_number(b);

    checkAndAdd(a, b);
    checkAndSubtract(a, b);
    checkAndMultiply(a, b);
    vector<int> q = division(a, b);
    printf("Normal division quotient\n");
    print_number(q);
    division_one_digit(a, 8);
    // vector <int> Q = divTrial(a, b);
    // print_number(Q);
    // trialSubtraction(a, b);
    // trialAddition(a, b);

    printf("Addition real \n");
    pair<vector<int>, int> c = addition_real(a, 0, b, -2);
    print_number(c.first);
    printf("%d\n", c.second);

    printf("Subtraction real \n");
    pair<vector<int>, int> c1 = subtraction_real(a, 0, b, -2); // 2-0.01=1.99
    cout << "answer = ";
    print_number(c1.first);
    cout << "power =";
    printf("%d\n", c1.second);

    printf("Multiplication real \n");
    pair<vector<int>, int> c2 = multiplication_real(a, -1, b, -2);
    print_number(c2.first);
    printf("%d\n", c2.second);

    printf("Division real \n");
    pair<vector<int>, int> c3 = division_real(a, 0, b, -5);
    print_number(c3.first);
    
    printf("%d\n", c3.second);

    print_pair_number(c3);

    printf("Sq root  \n");
    pair<vector<int>, int> c4 = sq_root(a, 0, b, -5);
    print_number(c4.first);
    printf("%d\n", c4.second);

    return 0;
}