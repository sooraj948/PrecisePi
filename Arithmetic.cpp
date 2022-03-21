#include "Arithmetic.hpp"
using namespace std;
Arithmetic::Arithmetic(int base)
{
    this->Base = base;
}

vector<int> Arithmetic::Add(vector <int> number1,vector<int> number2)
{
    vector <int> result;
    int carry = 0,i=0;
    //printf("sizes = %ld %ld\n",sizeof(number1),sizeof(number2));
    for(i=0;i<min(number1.size(),number2.size());i++)
    {
        result.push_back((number1[i]+number2[i]+carry)%Base);
        carry = (number1[i]+number2[i]+carry)/Base;
    }

    for(int j=i;j<max(number1.size(),number2.size());j++) 
    {
        // printf("j=%d\n",j);
        if(max(number1.size(),number2.size())==number1.size())
        {
            result.push_back((number1[j]+carry)%Base);
            carry = (number1[j]+carry)/Base;
        }
        else
        {
            result.push_back((number2[j]+carry)%Base);
            carry = (number2[j]+carry)/Base;
        }
    }
    result.push_back(carry);
    return result;
}

vector <int> Arithmetic::Sub(vector<int>number1, vector<int>number2) 
{
    //Doing number1-number2
    vector<int> result;
    int carry=0;
    //padding zeroes
    if(number1.size()>number2.size())
    {
        while(number2.size()!=number1.size()) 
        {
            number2.push_back(0);
        }
    }
    else
    {
        while(number2.size()!=number1.size()) 
        {
            number1.push_back(0);
        }
    }

    for(int i=0;i<number1.size();i++)
    {
        
        if(number1[i]-number2[i]+carry<0) {
            result.push_back(Base + (number1[i]-number2[i]+carry));
            carry = -1;
        }
        else 
        {
            result.push_back(number1[i]-number2[i]+carry);
            carry = 0;
        }
    }
    result.push_back(carry);
    return result;

}

vector<int> Arithmetic::Mul(vector<int> number1, vector<int> number2)
{
    vector<int> result;
    int carry=0;
    int tmp;
    for(int i=0; i<=(number1.size()+number2.size()-1);i++)
    {
        result.push_back(0);
    }
    for(int i=0;i<number1.size();i++)
    {
        carry = 0;
        for(int j=0;j<number2.size();j++)
        {
            // printf("%d %d %d %d\n", i,j,carry,result[i+j]);
            tmp = number1[i]*number2[j]+carry+result[i+j];
            carry = tmp/Base;
            result[i+j] = tmp%Base;
            // printf("%d %d %d %d %d %d %d\n",number1[i], number2[j], i,j,tmp,carry,result[i+j]);
        }
        result[i+number2.size()] = carry;
    }
    return result;
}

pair<vector<int>,vector<int>> Arithmetic::Div(vector<int>number1, vector<int>number2)
{
    vector<int> r;
    vector<int> q;
    int carry=0;
    int tmp;
    int k=number1.size();
    int l = number2.size();
    int d = k-l;
    // cout << l << " " << k << endl;

    for(int i=d; i>=0;i--)
    {
        // printf("%d\n",i);
        q.push_back(0);
    }
    for(int i=0;i<k;i++)
    {
        r.push_back(number1[i]);
    }
    r.push_back(0);
    // cout << r.size() << endl;

    for(int i=(k-l);i>=0;i--)
    {
        q[i] = (r[i+l]*Base);
        q[i] += r[i+l-1];
        q[i] = q[i]/number2[l-1];

        if(q[i] >= Base)
        {
            q[i] = Base-1;
        }
        carry=0;
        // printf("%d %d\n",i,q[i]);
        for(int j=0;j<l;j++)
        {
            tmp = r[i+j] - (q[i]*number2[j]) + carry;
            carry = tmp/Base;
            r[i+j] = tmp%Base;
            if(r[i+j]<0)
            {
                carry-=1;
                r[i+j]+=Base;
            }
        }
        r[i+l] = r[i+l]+carry;
        while(r[i+l]<0)
        {
            carry=0;
            for(int j=0;j<l;j++)
            {
                tmp=r[i+j]+number2[j]+carry;
                carry = tmp/Base;
                r[i+j] = tmp%Base;
                if(r[i+j]<0)
                {
                    carry-=1;
                    r[i+j]+=Base;
                }
            }
            r[i+l]+=carry;
            q[i]-=1;

        }
    }
    // for(int i=0;i<r.size();i++)
    // {
    //     cout<<r[i]<<" ";
    // }
    // cout << endl;
    return make_pair(q,r);

}

vector<int> Arithmetic::decimal_after_division(vector<int>rem,vector<int>divisor)
{
    vector <int> Base;
    vector <int> decimal;
    vector<int> remBase;
    vector <int> quotient;
    vector<int> remainder = rem;
    int j;

    Base.push_back(0);Base.push_back(1);
    for(int i=0;i<1000;i++)
    {
        remBase = Arithmetic::Mul(Base,remainder);
        // for(int i=0;i<remBase.size();i++)
        //     cout<<remBase[i]<<" ";
        // cout<<endl;
        quotient = Div(remBase,divisor).first;
        decimal.push_back(quotient[0]);
        remainder = Div(remBase,divisor).second;
        for(j=0;j<remainder.size();j++)
        {
            if(remainder[j]!=0) break;
        }
        if(j==remainder.size()) return decimal;
    }
    return decimal;

}