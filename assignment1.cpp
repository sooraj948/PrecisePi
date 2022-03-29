#include <vector>
#include <string>
#include <iostream>
// #include <pair>
#include <utility>
using namespace std;

#define B 10
#define precision 50

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
    // cout <<"size of vector in print pair "<< d.first.size()<<endl;

    // cout <<"0";
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
    // cout << "Printing answer: " << endl;
    // print_number(c);

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
vector<int> removeXZeroes(vector<int> a, int num)
{
    // cout <<"num is " << num <<endl;
    // print_number(a);

    for (auto it = a.end() - 1; it != a.begin(); --it)
    {
        if (num == 1)
        {
            // cout<<"Removed the zeroes"<<endl;
            // print_number(a);
            break;
        }
        num--;
        if (*it == 0)
        {
            a.erase(it);
        }
        else
        {
            //    cout <<"inside Xzeroes and breaking"<< endl;
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
    // cout<<"Printing a"<<endl;
    // print_number(a);
    // cout<<"Printing b"<<endl;
    // print_number(b);
    // cout << l << " " << k << endl;

    for (int i = d; i >= 0; i--)
    {
        // printf("%d\n",i);
        q.push_back(0);
    }
    r = a;

    r.push_back(0);
    // cout << r.size() << endl;
    // finding first non zero

    int denom = 1;
    // for (int i=l-1;i>-1;i--)
    // {
    //     if (b[i])
    //     {
    //         denom = b[i];
    //         break;
    //     }

    // }
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
    static int count = 0;
    count++;
    // if (a.size()<precision)
    // {

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
            // cout<<"Zero is be
            // ing removed"<<endl;
            a.erase(it);
        }
        else
        {
            //    cout<<"Breaking"<<endl;
            break;
        }
    }
    // cout<<"Trailing zeroes have been removed"<<endl;
    // print_number(a);
    return a;
}

pair<vector<int>, int> division_real(vector<int> a, int power_a, vector<int> b, int power_b)
{
    vector<int> c = pad_zeroes_at_end(a);
    static int count = 0;
    count++;
    // power_a-=precision;
    // print_number(c);
    // cout <<" c is "<<endl;
    // print_number(c);
    b = removeXZeroes(b, b.size() + power_b);
    // b = removeTrailingZeroes(b);

    c = division(c, b);
    //********the power is the problem*********
    return make_pair(c, power_a - power_b - count * precision);
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
    static int count = 0;
    count++;
    cout << "count is " << count << endl;
    pair<vector<int>, int> x;

    vector<int> half;
    cout << "Pushing" << endl;
    half.push_back(B / 2); //*10**-1
    half.push_back(0);

    pair<vector<int>, int> temp; // inside ()

    pair<vector<int>, int> R_by_x = division_real(R, power_R, x0, power_x0);

    // R_by_x.push_back(0);

    cout << "R by x is " << endl;
    // R_by_x is empty ??? check this
    //  print_number(R_by_x.first);
    print_pair_number(R_by_x);

    temp = addition_real(x0, power_x0, R_by_x.first, R_by_x.second);
    cout << "temp ";
    print_pair_number(temp);

    x = multiplication_real(half, -1, temp.first, temp.second);

    cout << "intermediate x is " << endl;

    // print_number(x.first);
    // cout <<x.second<<endl;
    print_pair_number(x);

    if (count < 12) // some arbitrary precision
        return sq_root(R, power_R, x.first, x.second);
    else
        return x;
}

pair<vector<int>, int> roundoff(pair<vector<int>, int> a, int n)
{
    pair<vector<int>, int> ans;

    for (int i = a.first.size() - n; i < a.first.size(); i++)
        ans.first.push_back(a.first[i]);
    ans.second = a.first.size() - n + a.second;
    return ans;
}

pair<vector<int>, int> squareroot(vector<int> R, int power_R, vector<int> x0, int power_x0)
{

    vector<int> two;
    two.push_back(2);
    int count = 0;

    vector<int> half;
    half.push_back(B / 2);

    pair<vector<int>, int> answer;
    while (count < precision)
    {
        // if(count==12)
        // {
        //     break;
        // }
        // x0 =removeTrailingZeroes(x0);

        pair<vector<int>, int> R_by_Xn;
        // cout << "R = "; // 2
        // print_number(R);
        // cout << "x0 = "; // 1.41428
        // print_number(x0);
        // cout << "Power of x = " << power_x0 << endl; //-5
        // cout << "Power of R = " << power_R << endl;  // 0
        R_by_Xn = division_real(R, power_R, x0, power_x0);
        // cout << "R_by_Xn = "; // 1
        // print_number(R_by_Xn.first);
        // cout << "Power of R/Xn = " << R_by_Xn.second << endl; // 0
        pair<vector<int>, int> numerator = addition_real(x0, power_x0, R_by_Xn.first, R_by_Xn.second);
        // cout << "Numerator = ";
        // print_number(numerator.first);
        // cout << "Power of numerator = " << numerator.second << endl;
        // answer = division_real(numerator.first, numerator.second, two, 0);
        answer = multiplication_real(numerator.first, numerator.second, half, -1);
        // cout << "Answer = ";
        // print_number(answer.first);
        // cout << "Power of answer = " << answer.second << endl;
        x0 = answer.first;
        power_x0 = answer.second;

        // x0 = roundoff(x0,50);

        count++;
    }
    return answer;
}

pair<vector<int>, int> pi()
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
    // vector<int> one; // 1
    // one.push_back(1);

    // vector<int> half; // 5
    // half.push_back(B / 2);

    // initializing a0,b0,p0
    pair<vector<int>, int> a0 = squareroot(two, 0, b, -1); // 2**0.5
    // print_pair_number(a0);
    pair<vector<int>, int> b0;
    b0.first = {0};
    b0.second = 0;
    pair<vector<int>, int> five;
    five.first = {5};
    five.second = -1;

    pair<vector<int>, int> p0 = addition_real(two, 0, a0.first, a0.second);
    // cout << "Printing p0" << endl;
    // print_pair_number(p0);
    int count = 0;

    while (count < 3)
    {
        // bn-> an->pn

        pair<vector<int>, int> one_plus_bn = addition_real(b0.first, b0.second, one.first, one.second); // 1+b
        // print_pair_number(one_plus_bn);
        pair<vector<int>, int> root_an = squareroot(a0.first, a0.second, b, -1);
        // print_pair_number(root_an);
        pair<vector<int>, int> an_plus_bn = addition_real(b0.first, b0.second, a0.first, a0.second);
        // print_pair_number(an_plus_bn);
        pair<vector<int>, int> numerator_bn1 = multiplication_real(one_plus_bn.first, one_plus_bn.second, root_an.first, root_an.second);
        // print_pair_number(numerator_bn1);
        b0 = division_real(numerator_bn1.first, numerator_bn1.second, an_plus_bn.first, an_plus_bn.second);
        // print_pair_number(b0);
        pair<vector<int>, int> one_by_root_an = division_real(one.first, one.second, root_an.first, root_an.second);
        // print_pair_number(one_by_root_an);
        pair<vector<int>, int> numerator_an1 = addition_real(root_an.first, root_an.second, one_by_root_an.first, one_by_root_an.second);
        // print_pair_number(numerator_an1);
        a0 = multiplication_real(five.first, five.second, numerator_an1.first, numerator_an1.second);
        // print_pair_number(a0);
        pair<vector<int>, int> one_plus_an1 = addition_real(one.first, one.second, a0.first, a0.second);
        // print_pair_number(one_plus_an1);
        pair<vector<int>, int> pn_times_bn1 = multiplication_real(p0.first, p0.second, b0.first, b0.second);
        // cout << "************************" << endl;
        // print_pair_number(pn_times_bn1);
        pair<vector<int>, int> numerator_pn1 = multiplication_real(one_plus_an1.first, one_plus_an1.second, pn_times_bn1.first, pn_times_bn1.second);
        // print_pair_number(numerator_pn1);
        pair<vector<int>, int> one_plus_bn1 = addition_real(one.first, one.second, b0.first, b0.second);
        // print_pair_number(one_plus_bn1);
        p0 = division_real(numerator_pn1.first, numerator_pn1.second, one_plus_bn1.first, one_plus_bn1.second);
        p0 = roundoff(p0, 256);
        print_pair_number(p0);
        count++;
    }

    return p0;
}

// pair<vector<int>, vector<int>> PI()
// {
//     vector<int> num1, num2, dec1, dec2;
//     num1.push_back(2);
//     num2.push_back(1);
//     dec2.push_back(5);
//     pair<vector<int>, vector<int>> a = squareroot(num1, num2, dec1, dec2);
//     vector<int> a1;

//     // for(int i=0;i<a.first.size();i++) cout<<a.first[i]<<" ";
//     // cout<<endl;
//     // for(int i=0;i<a.second.size();i++) cout<<a.second[i]<<" ";
//     // cout<<endl;

//     pair<vector<int>, vector<int>> b;
//     pair<vector<int>, vector<int>> p = Add_with_dec(a.first, a.second, num1, dec1);

//     // for(int i=0;i<p.first.size();i++) cout<<p.first[i]<<" ";
//     // cout<<endl;
//     // for(int i=0;i<p.second.size();i++) cout<<p.second[i]<<" ";
//     // cout<<endl;

//     int j = 0;
//     while (j < 8)
//     {
//         j++;

//         pair<vector<int>, vector<int>> tempa = a;
//         pair<vector<int>, vector<int>> ra;
//         pair<vector<int>, vector<int>> ra1;

//         // for(int i=0;i<40;i++) a1.push_back(tempa.second[i]);
//         ra = squareroot(a.first, num1, a.second, dec1);

//         // for(int i=0;i<ra.first.size();i++) cout<<ra.first[i]<<" ";
//         // cout<<endl;
//         // for(int i=0;i<ra.second.size();i++) cout<<ra.second[i]<<" ";
//         // cout<<endl;
//         // cout<<endl;

//         // vector<int> tra;
//         // for(int i=0;i<20;i++)
//         // {
//         //     tra.push_back(ra.second[i]);
//         // }
//         ra1 = Div_with_dec(num2, dec1, ra.first, ra.second);

//         // for(int i=0;i<ra1.first.size();i++) cout<<ra1.first[i]<<" ";
//         // cout<<endl;
//         // for(int i=0;i<ra1.second.size();i++) cout<<ra1.second[i]<<" ";
//         // cout<<endl;
//         // cout<<endl;

//         a = Add_with_dec(ra.first, ra.second, ra1.first, ra1.second);
//         a = Div_with_dec(a.first, a.second, num1, dec1);
//         // for(int i=0;i<a.first.size();i++) cout<<a.first[i]<<" ";
//         // cout<<endl;
//         // for(int i=0;i<a.second.size();i++) cout<<a.second[i]<<" ";
//         // cout<<endl;
//         // cout<<endl;

//         pair<vector<int>, vector<int>> tempb = b;
//         pair<vector<int>, vector<int>> b1;
//         pair<vector<int>, vector<int>> addab;
//         pair<vector<int>, vector<int>> b1rta;

//         b1 = Add_with_dec(b.first, b.second, num2, dec1);

//         // for(int i=0;i<b1.first.size();i++) cout<<b1.first[i]<<" ";
//         // cout<<endl;
//         // for(int i=0;i<b1.second.size();i++) cout<<b1.second[i]<<" ";
//         // cout<<endl;

//         addab = Add_with_dec(tempb.first, tempb.second, tempa.first, tempa.second);

//         // for(int i=0;i<addab.first.size();i++) cout<<addab.first[i]<<" ";
//         // cout<<endl;
//         // for(int i=0;i<addab.second.size();i++) cout<<addab.second[i]<<" ";
//         // cout<<endl;

//         b1rta = Mul_with_dec(b1.first, b1.second, ra.first, ra.second);

//         // for(int i=0;i<b1rta.first.size();i++) cout<<b1rta.first[i]<<" ";
//         // cout<<endl;
//         // for(int i=0;i<b1rta.second.size();i++) cout<<b1rta.second[i]<<" ";
//         // cout<<endl;
//         // cout << endl;

//         b = Div_with_dec(b1rta.first, b1rta.second, addab.first, addab.second);
//         // cout << "b"<<endl;
//         // for(int i=0;i<b.first.size();i++) cout<<b.first[i]<<" ";
//         // cout<<endl;
//         // for(int i=0;i<b.second.size();i++) cout<<b.second[i]<<" ";
//         // cout<<endl;
//         // cout<<endl;

//         pair<vector<int>, vector<int>> tempp = p;
//         pair<vector<int>, vector<int>> a11;
//         pair<vector<int>, vector<int>> b11;
//         pair<vector<int>, vector<int>> a11p;
//         pair<vector<int>, vector<int>> a11pb;

//         b11 = Add_with_dec(b.first, b.second, num2, dec1);
//         //     // for(int i=0;i<b11.first.size();i++) cout<<b11.first[i]<<" ";
//         //     // cout<<endl;
//         //     // for(int i=0;i<b11.second.size();i++) cout<<b11.second[i]<<" ";
//         //     // cout<<endl;

//         a11 = Add_with_dec(a.first, a.second, num2, dec1);
//         //     // for(int i=0;i<a11.first.size();i++) cout<<a11.first[i]<<" ";
//         //     // cout<<endl;
//         //     // for(int i=0;i<a11.second.size();i++) cout<<a11.second[i]<<" ";
//         //     // cout<<endl;

//         a11p = Mul_with_dec(a11.first, a11.second, tempp.first, tempp.second);
//         //     // for(int i=0;i<a11p.first.size();i++) cout<<a11p.first[i]<<" ";
//         //     // cout<<endl;
//         //     // for(int i=0;i<a11p.second.size();i++) cout<<a11p.second[i]<<" ";
//         //     // cout<<endl;

//         a11pb = Mul_with_dec(a11p.first, a11p.second, b.first, b.second);
//         //     // for(int i=0;i<a11pb.first.size();i++) cout<<a11pb.first[i]<<" ";
//         //     // cout<<endl;
//         //     // for(int i=0;i<a11pb.second.size();i++) cout<<a11pb.second[i]<<" ";
//         //     // cout<<endl;

//         // vector<int> tb11;
//         // for(int i=0;i<20;i++)
//         // {
//         //     tb11.push_back(b11.second[i]);
//         // }
//         p = Div_with_dec(a11pb.first, a11pb.second, b11.first, b11.second);
//     }
//     for (int i = 0; i < p.first.size(); i++)
//         cout << p.first[i] << " ";
//     cout << endl;
//     for (int i = 0; i < p.second.size(); i++)
//         cout << p.second[i] << " ";
//     cout << endl;
//     return a;
// }

int main()
{
    vector<int> one;
    one.push_back(1);

    vector<int> a;

    a = {4, 1, 4, 1};
    // a.push_back(5);

    vector<int> b;

    b.push_back(4);
    b.push_back(1);

    print_number(a);
    print_number(b);

    checkAndAdd({0}, {1});
    // checkAndSubtract(a, b);
    // checkAndMultiply(a, b);
    // vector<int> q = division(a, b);
    // printf("Normal division quotient\n");
    // print_number(q);
    // division_one_digit(a, 8);
    // // vector <int> Q = divTrial(a, b);
    // // print_number(Q);
    // // trialSubtraction(a, b);
    // // trialAddition(a, b);

    printf("Addition real \n");
    pair<vector<int>, int> c = addition_real({0}, 0, {1}, 0);
    print_number(c.first);
    printf("%d\n", c.second);

    // printf("Subtraction real \n");
    // pair<vector<int>, int> c1 = subtraction_real(a, 0, b, -2); // 2-0.01=1.99
    // cout << "answer = ";
    // print_number(c1.first);
    // cout << "power =";
    // printf("%d\n", c1.second);

    // printf("Multiplication real \n");
    // pair<vector<int>, int> c2 = multiplication_real(a, -1, b, -2);
    // print_number(c2.first);
    // printf("%d\n", c2.second);

    // printf("Division real \n");
    // pair<vector<int>, int> c3 = division_real(a, 0, b, -5);cout<<"Answer = "<<endl;
    // print_number(c3.first);

    // printf("%d\n", c3.second);

    // print_pair_number(c3);

    // printf("Sq root  \n");
    // pair<vector<int>, int> c4 = squareroot(a, -3, b, -1);
    // // print_number(c4.first);
    // // printf("%d\n", c4.second);

    // print_pair_number(c4);
    // pair<vector<int>, int> reciprocal = division_real(one, 0, c4.first, c4.second);
    // // pair<vector<int>, int> c5 = squareroot(reciprocal.first, reciprocal.second, b, -1);
    // print_pair_number(reciprocal);

    cout << "PI:" << endl;
    pair<vector<int>, int> PI = pi();
    print_pair_number(PI);

    return 0;
}
