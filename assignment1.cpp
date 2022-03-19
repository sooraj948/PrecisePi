#include <vector>
#include <string>
#include <iostream>

using namespace std;

#define B 8

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
            cout << "inside";
            cout << "carry is " << carry << endl;
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
            cout << "carry is " << carry << endl;
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
    cout << "adjusted vector is" << endl;
    for (int i = a.size() - 1; i >= 0; i--)
    {

        cout << a[i];
    }
    cout << endl;
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
    cout << "size of a is =" << l1 << endl;
    cout << "size of b is =" << l2 << endl;

    int carry = 0;
    if (l1 == l2)
    {
        for (int i = 0; i < l1; i++)
        {

            c.push_back((-a[i] + b[i] + carry) % B);
            cout << "i =" << i << " and c[i] = " << c[i] << endl;
            carry = (-a[i] + b[i] + carry) / B;
            cout << b[i] << "-" << a[i] << endl;
            cout << "carry is " << carry << endl;
        }

        for (int i = l1; i < l2; i++)
        {

            cout << "doing from l1 to l2" << endl;
            c.push_back((b[i] + carry) % B);
            cout << "i =" << i << " and c[i] = " << c[i] << endl;
            carry = (b[i] + carry) / B;

            cout << "carry is " << carry << endl;
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
                cout << "INSIDEEE" << endl;
                c.push_back((-a[i] + b[i] + carry) % B);
                cout << "i =" << i << " and c[i] = " << c[i] << endl;
                carry = (-a[i] + b[i] + carry) / B;
                cout << b[i] << "-" << a[i] << endl;
                cout << "carry is " << carry << endl;
            }
            else
            {

                cout << "i is less than l1-1" << endl;
                b = adjustCarry(b, i);
                // b[i + 1] -= 1;
                // b[i] += B;
                c.push_back((-a[i] + b[i] + carry) % B);
                cout << "i =" << i << " and c[i] = " << c[i] << endl;
                carry = (-a[i] + b[i] + carry) / B;
                cout << b[i] << "-" << a[i] << endl;
                cout << "carry is " << carry << endl;
            }
        }
        for (int i = l1; i < l2; i++)
        {

            cout << "doing from l1 to l2" << endl;
            c.push_back((b[i] + carry) % B);
            cout << "i =" << i << " and c[i] = " << c[i] << endl;
            carry = (b[i] + carry) / B;

            cout << "carry is " << carry << endl;
        }

        if (carry)
            c.push_back(carry);
    }

    return c;
}
void print_number(vector<int> d)
{
    for (int i = d.size() - 1; i > -1; i--)
    {
        cout << d[i] << "";
    }

    cout << endl;
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
            print_number(c);
            cout << "carry is " << carry << endl;
        }

        c[i + l] = carry;
    }

    return c;
}

vector<int> karatsuba(vector<int> a, vector<int> b)
{
    int l = a.size();
    int k = b.size();

    if (l == 1 || k == 1) // base case
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

int main()
{
    // string input;
    // cin >> input;
    // char ch;

    // vector <int > input_vector;
    // for (int i=0;i<input.size();i++)
    // {
    //     ch = input[i];
    //     input_vector.push_back(atoi(&ch));
    // }

    // for(int i=0;i<input_vector.size();i++)
    // {
    //     cout<< input_vector.at(i);
    // }
    // cout <<endl;

    vector<int> a;

    // a.push_back(2);
    // a.push_back(0);
    // a.push_back(0);
    a.push_back(7);
    for (int i = a.size() - 1; i >= 0; i--)
    {
        cout << a[i];
    }
    cout << endl;
    vector<int> b;
    b.push_back(0);
    b.push_back(0);
    b.push_back(1);
    for (int i = b.size() - 1; i >= 0; i--)
    {
        cout << b[i];
    }
    cout << endl;
    cout << b.size() << endl;

    vector<int> c = addition(a, b);
    c = adjustSign(c);
    cout << c.size() << endl;

    for (int i = c.size() - 1; i > -1; i--)
    {
        cout << c[i] << "";
    }
    cout << endl;
    vector<int> d;
    if (comparator(a, b)) // a is greater than b
    {
        cout << "a-b" << endl;
        d = subtraction(b, a); // d=a-b
        d = adjustSign(d);
    }
    else
    {
        cout << "b-a" << endl;
        d = subtraction(a, b); // d=b-a
        d = adjustNegativeSign(d);
        // d[d.size() - 1] *= -1;
    }
    // vector<int> d = subtraction(b, a);
    cout << d.size() << endl;

    for (int i = d.size() - 1; i > -1; i--)
    {
        cout << d[i] << "";
    }
    cout << endl;

    cout << "Multiplication" << endl;
    vector<int> e = multiplication(a, b);
    e = adjustSign(e);
    for (int i = e.size() - 1; i > -1; i--)
    {
        cout << e[i] << "";
    }
    cout << endl;
    return 0;
}