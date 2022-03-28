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
    vector<int> div;
    int carry=0;
    int tmp;
    int k=number1.size();
    int ll = number2.size();
    int x=0;
    // cout << l << " " << k << endl;
    for(int i=ll-1;i>=0;i--)
    {
        if(number2[i]>0)
        {
            x=i+1;
            break;
        }
    }
    for(int i=0;i<x;i++)
    {
        div.push_back(number2[i]);
    }
    int l = div.size();
    int d = k-l;
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
        q[i] = q[i]/div[l-1];

        if(q[i] >= Base)
        {
            q[i] = Base-1;
        }
        carry=0;
        // printf("%d %d\n",i,q[i]);
        for(int j=0;j<l;j++)
        {
            tmp = r[i+j] - (q[i]*div[j]) + carry;
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
                tmp=r[i+j]+div[j]+carry;
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
    vector <int> Base1;
    vector <int> decimal;
    vector<int> remBase;
    vector <int> quotient;
    vector<int> remainder = rem;
    int j;

    Base1.push_back(0);Base1.push_back(1);
     for(int i=0;i<260;i++)
     {
           remBase = Arithmetic::Mul(Base1,remainder);
    //     //for(int i=0;i<remBase.size();i++)
    //     //     cout<<remBase[i]<<" ";
    //     // cout<<endl;
           quotient = Arithmetic::Div(remBase,divisor).first;
           if(quotient.size()==0) decimal.push_back(0);
           else decimal.push_back(quotient[0]);
           remainder = Arithmetic::Div(remBase,divisor).second;
           for(j=0;j<remainder.size();j++)
           {
               if(remainder[j]!=0) break;
           }
           if(j==remainder.size()) return decimal;
     }
    return decimal;

}

pair<vector<int>,vector<int>>  Arithmetic:: squareroot(vector<int>R,vector<int>x0,vector<int>decimalR,vector<int>decimalx0)
{
    vector <int> x = x0;
    vector <int> x_decimal = decimalx0;
    vector<int> Rdec = decimalR;
    vector <int> Rnum = R;
    
   
    vector <int> none0,const2;

    const2.push_back(2);

    int power_of_x0,power_of_x0_sq,count=0;

    while(count<10)
    {
        vector<int> x_expanded,x_expanded_sq,x_expanded_sq_num,x_expanded_sq_dec,added_num,added_dec,mul_num,mul_dec,div_num,div_dec;
        power_of_x0_sq = -2*x_decimal.size();
        for(int i=x_decimal.size()-1;i>=0;i--)
        {
            x_expanded.push_back(x_decimal[i]);
        }
        for(int i=0;i<x.size();i++)
        {
            x_expanded.push_back(x[i]);
        }
        x_expanded_sq = Arithmetic::Mul(x_expanded,x_expanded);

        for(int i=(-1*power_of_x0_sq)-1;i>=0;i--)
        {
            x_expanded_sq_dec.push_back(x_expanded_sq[i]);
        }
        for(int i=-1*power_of_x0_sq;i<x_expanded_sq.size();i++)
        {
            x_expanded_sq_num.push_back(x_expanded_sq[i]);
        }

        added_num = Arithmetic::Add_with_dec(x_expanded_sq_num,x_expanded_sq_dec,Rnum,Rdec).first;  //xn^2 + R
        added_dec = Arithmetic::Add_with_dec(x_expanded_sq_num,x_expanded_sq_dec,Rnum,Rdec).second; //xn^2 + R

        // cout<<"Add"<<endl;
        // for(int i=0;i<added_num.size();i++) cout<<added_num[i]<<" ";
        // cout<<endl;
        // for(int i=0;i<added_dec.size();i++) cout<<added_dec[i]<<" ";
        // cout<<endl;

        mul_num = Arithmetic::Mul_with_dec(x,x_decimal,const2,none0).first;   //2*xn
        mul_dec = Arithmetic::Mul_with_dec(x,x_decimal,const2,none0).second;  //2*xn
        
        // cout<<"Mul"<<endl;
        // for(int i=0;i<mul_num.size();i++) cout<<mul_num[i]<<" ";
        // cout<<endl;
        // for(int i=0;i<mul_dec.size();i++) cout<<mul_dec[i]<<" ";
        // cout<<endl;

        div_num = Arithmetic::Div_with_dec(added_num,added_dec,mul_num,mul_dec).first;
        div_dec = Arithmetic::Div_with_dec(added_num,added_dec,mul_num,mul_dec).second;

        // cout<<"Div"<<endl;
        // for(int i=0;i<div_num.size();i++) cout<<div_num[i]<<" ";
        // cout<<endl;
        // for(int i=0;i<div_dec.size();i++) cout<<div_dec[i]<<" ";
        // cout<<endl;

        x = div_num;
        x_decimal = div_dec;
        
        count++;
    }

    return make_pair(x,x_decimal);
    

}

pair<vector<int>,vector<int>> Arithmetic::Add_with_dec(vector<int> number1,vector<int>dec1,vector<int> number2,vector<int>dec2)
{
    vector <int> num,dec,result;

    vector <int> extended_num1,extended_num2,added_zeroes_num1,added_zeroes_num2;
    int power_num1,power_num2;
    power_num1 = -1*dec1.size();
    power_num2 = -1*dec2.size();

    for(int i=dec1.size()-1;i>=0;i--)
    {
        extended_num1.push_back(dec1[i]);
    }
    for(int i=0;i<number1.size();i++)
    {
        extended_num1.push_back(number1[i]);
    }

    for(int i=dec2.size()-1;i>=0;i--)
    {
        extended_num2.push_back(dec2[i]);
    }
    for(int i=0;i<number2.size();i++)
    {
        extended_num2.push_back(number2[i]);
    }

    if((-1*power_num1)> (-1*power_num2)) 
    {
        for(int i=0;i<abs(power_num1-power_num2);i++)
        {
            added_zeroes_num2.push_back(0);
        }
        for(int i=0;i<extended_num2.size();i++)
        {
            added_zeroes_num2.push_back(extended_num2[i]);
        }
        result = Arithmetic::Add(extended_num1,added_zeroes_num2);

        for(int i=(-1*power_num1)-1;i>=0;i--)
        {
            dec.push_back(result[i]);
        }

        for(int i=-1*power_num1;i<result.size();i++)
        {
            num.push_back(result[i]);
        }
    }
    else
    {
        for(int i=0;i<abs(power_num1-power_num2);i++)
        {
            added_zeroes_num1.push_back(0);
        }
        for(int i=0;i<extended_num1.size();i++)
        {
            added_zeroes_num1.push_back(extended_num1[i]);
        }
        result = Arithmetic::Add(extended_num2,added_zeroes_num1);

        for(int i=(-1*power_num2)-1;i>=0;i--)
        {
            dec.push_back(result[i]);
        }

        for(int i=-1*power_num2;i<result.size();i++)
        {
            num.push_back(result[i]);
        }
    }

    

    vector<int> n1;
    vector<int> d1;
    int x=0,y=0;
    int p = num.size();
    int q = dec.size();
    for(int i=p-1;i>=0;i--)
    {
        if(num[i]>0)
        {
            x=i+1;
            break;
        }
    }
    for(int i=0;i<x;i++)
    {
        n1.push_back(num[i]);
    }

    for(int i=q-1;i>=0;i--)
    {
        if(dec[i]>0)
        {
            y=i+1;
            break;
        }
    }
    for(int i=0;i<y;i++)
    {
        d1.push_back(dec[i]);
    }
   

    return make_pair(n1,d1);
}

pair<vector<int>,vector<int>> Arithmetic::Mul_with_dec(vector<int> number1,vector<int>dec1,vector<int> number2,vector<int>dec2)
{
    vector <int> expanded_num1,expanded_num2,num,dec;
    vector<int> mul_exp;
    for(int i=dec1.size()-1;i>=0;i--)
    {
        expanded_num1.push_back(dec1[i]);
    }
    for(int i=0;i<number1.size();i++)
    {
        expanded_num1.push_back(number1[i]);
    }

    for(int i=dec2.size()-1;i>=0;i--)
    {
        expanded_num2.push_back(dec2[i]);
    }
    for(int i=0;i<number2.size();i++)
    {
        expanded_num2.push_back(number2[i]);
    }

    mul_exp = Arithmetic::Mul(expanded_num1,expanded_num2);

    for(int i=(dec1.size()+dec2.size())-1;i>=0;i--)
    {
        dec.push_back(mul_exp[i]);
    }

    for(int i=dec1.size()+dec2.size();i<mul_exp.size();i++)
    {
        num.push_back(mul_exp[i]);
    }

    vector<int> n1;
    vector<int> d1;
    int x=0,y=0;
    int p = num.size();
    int q = dec.size();
    for(int i=p-1;i>=0;i--)
    {
        if(num[i]>0)
        {
            x=i+1;
            break;
        }
    }
    for(int i=0;i<x;i++)
    {
        n1.push_back(num[i]);
    }

    for(int i=q-1;i>=0;i--)
    {
        if(dec[i]>0)
        {
            y=i+1;
            break;
        }
    }
    for(int i=0;i<y;i++)
    {
        d1.push_back(dec[i]);
    }
   

    return make_pair(n1,d1);

}

pair<vector<int>,vector<int>> Arithmetic::Div_with_dec(vector<int> number1,vector<int>dec1,vector<int> number2,vector<int>dec2)
{
    vector <int> exp_num1,exp_num2,expanded_num1,expanded_num2,num,dec,quo,rem,decimal;
    

    for(int i=dec1.size()-1;i>=0;i--)
    {
        expanded_num1.push_back(dec1[i]);
    }
    for(int i=0;i<number1.size();i++)
    {
        expanded_num1.push_back(number1[i]);
    }

    for(int i=dec2.size()-1;i>=0;i--)
    {
        expanded_num2.push_back(dec2[i]);
    }
    for(int i=0;i<number2.size();i++)
    {
        expanded_num2.push_back(number2[i]);
    }
   

    //int power_num1 = -1*dec1.size();
    //int power_num2 = -1*dec2.size();
    if(dec2.size()>dec1.size())
    {
        for(int i=0;i<dec2.size()-dec1.size();i++)
        {
            exp_num1.push_back(0);
        }
        for(int i=0;i<expanded_num1.size();i++)
        {
            exp_num1.push_back(expanded_num1[i]);
        }

        num = Arithmetic::Div(exp_num1,expanded_num2).first;
        rem = Arithmetic::Div(exp_num1,expanded_num2).second;

        dec = Arithmetic::decimal_after_division(rem,expanded_num2);
    }
    else
    {
        for(int i=0;i<dec1.size()-dec2.size();i++)
        {
            exp_num2.push_back(0);
        }
        for(int i=0;i<expanded_num2.size();i++)
        {
            exp_num2.push_back(expanded_num2[i]);
        }
        //for(int i=0;i<exp_num2.size();i++) cout<<exp_num2[i]<<" ";
        

        num = Arithmetic::Div(expanded_num1,exp_num2).first;
        rem = Arithmetic::Div(expanded_num1,exp_num2).second;

        dec = Arithmetic::decimal_after_division(rem,exp_num2);
    }

    

    
    // // if(dec1.size()<dec2.size()) 
    // // {
    // //     for(int i=dec2.size()-dec1.size()-1;i>=0;i--)
    // //     {
    // //         num.push_back(decimal[i]);
    // //     }
    // //     for(int i=0;i<quo.size();i++) 
    // //     {
    // //         num.push_back(quo[i]);
    // //     }
    // //     for(int i=dec2.size()-dec1.size();i<decimal.size();i++)
    // //     {
    // //         dec.push_back(decimal[i]);
    // //     }
    // // }
    // // else
    // // {
    // //     for(int i=dec1.size()-dec2.size();i<quo.size();i++)
    // //     {
    // //         num.push_back(quo[i]);
    // //     }
    // //     for(int i=dec1.size()-dec2.size()-1;i>=0;i--)
    // //     {
    // //         dec.push_back(quo[i]);
    // //     }
    // //     for(int i=0;i<decimal.size();i++)
    // //     {
    // //         dec.push_back(decimal[i]);
    // //     }
    // // }

    vector<int> n1;
    vector<int> d1;
    int x=0,y=0;
    int p = num.size();
    int q = dec.size();
    for(int i=p-1;i>=0;i--)
    {
        if(num[i]>0)
        {
            x=i+1;
            break;
        }
    }
    for(int i=0;i<x;i++)
    {
        n1.push_back(num[i]);
    }

    for(int i=q-1;i>=0;i--)
    {
        if(dec[i]>0)
        {
            y=i+1;
            break;
        }
    }
    for(int i=0;i<y;i++)
    {
        d1.push_back(dec[i]);
    }
   

    return make_pair(n1,d1);
    //return make_pair(exp_num1,exp_num2);

}

pair<vector<int>,vector<int>> Arithmetic::PI()
{
   vector<int> num1, num2, dec1, dec2;
    num1.push_back(2);
    num2.push_back(1);
    dec2.push_back(5);
    pair<vector<int>,vector<int>> a = Arithmetic::squareroot(num1,num2,dec1,dec2);
    vector<int> a1;

    // for(int i=0;i<a.first.size();i++) cout<<a.first[i]<<" ";
    // cout<<endl;
    // for(int i=0;i<a.second.size();i++) cout<<a.second[i]<<" ";
    // cout<<endl;

    

    pair<vector<int>,vector<int>> b;
    pair<vector<int>,vector<int>> p = Arithmetic::Add_with_dec(a.first, a.second, num1, dec1);

    // for(int i=0;i<p.first.size();i++) cout<<p.first[i]<<" ";
    // cout<<endl;
    // for(int i=0;i<p.second.size();i++) cout<<p.second[i]<<" ";
    // cout<<endl;
    
    int j=0;
    while(j<8)
    {
        j++;
        
        pair<vector<int>,vector<int>> tempa=a;
        pair<vector<int>,vector<int>> ra; 
        pair<vector<int>,vector<int>> ra1;

        // for(int i=0;i<40;i++) a1.push_back(tempa.second[i]);
        ra = Arithmetic::squareroot(a.first,num1,a.second,dec1);

        // for(int i=0;i<ra.first.size();i++) cout<<ra.first[i]<<" ";
        // cout<<endl;
        // for(int i=0;i<ra.second.size();i++) cout<<ra.second[i]<<" ";
        // cout<<endl;
        // cout<<endl;

        // vector<int> tra;
        // for(int i=0;i<20;i++)
        // {
        //     tra.push_back(ra.second[i]);
        // }
        ra1 = Arithmetic::Div_with_dec(num2, dec1, ra.first,ra.second);

        // for(int i=0;i<ra1.first.size();i++) cout<<ra1.first[i]<<" ";
        // cout<<endl;
        // for(int i=0;i<ra1.second.size();i++) cout<<ra1.second[i]<<" ";
        // cout<<endl;
        // cout<<endl;

        a = Arithmetic::Add_with_dec(ra.first,ra.second,ra1.first,ra1.second);
        a = Arithmetic::Div_with_dec(a.first,a.second,num1,dec1);
        // for(int i=0;i<a.first.size();i++) cout<<a.first[i]<<" ";
        // cout<<endl;
        // for(int i=0;i<a.second.size();i++) cout<<a.second[i]<<" ";
        // cout<<endl;
        // cout<<endl;



        pair<vector<int>,vector<int>> tempb=b;
        pair<vector<int>,vector<int>> b1; 
        pair<vector<int>,vector<int>> addab;
        pair<vector<int>,vector<int>> b1rta;

        b1 = Arithmetic::Add_with_dec(b.first, b.second, num2, dec1);
        
        // for(int i=0;i<b1.first.size();i++) cout<<b1.first[i]<<" ";
        // cout<<endl;
        // for(int i=0;i<b1.second.size();i++) cout<<b1.second[i]<<" ";
        // cout<<endl;

        addab = Arithmetic::Add_with_dec(tempb.first, tempb.second, tempa.first, tempa.second);
        
        // for(int i=0;i<addab.first.size();i++) cout<<addab.first[i]<<" ";
        // cout<<endl;
        // for(int i=0;i<addab.second.size();i++) cout<<addab.second[i]<<" ";
        // cout<<endl;

        b1rta = Arithmetic::Mul_with_dec(b1.first, b1.second, ra.first, ra.second);

        // for(int i=0;i<b1rta.first.size();i++) cout<<b1rta.first[i]<<" ";
        // cout<<endl;
        // for(int i=0;i<b1rta.second.size();i++) cout<<b1rta.second[i]<<" ";
        // cout<<endl;
        // cout << endl;

        b = Arithmetic::Div_with_dec(b1rta.first,b1rta.second,addab.first,addab.second);
        // cout << "b"<<endl;
        // for(int i=0;i<b.first.size();i++) cout<<b.first[i]<<" ";
        // cout<<endl;
        // for(int i=0;i<b.second.size();i++) cout<<b.second[i]<<" ";
        // cout<<endl;
        // cout<<endl;

        pair<vector<int>,vector<int>> tempp = p;
        pair<vector<int>,vector<int>> a11;
        pair<vector<int>,vector<int>> b11;
        pair<vector<int>,vector<int>> a11p;
        pair<vector<int>,vector<int>> a11pb;

        b11 = Arithmetic::Add_with_dec(b.first,b.second,num2,dec1);
    //     // for(int i=0;i<b11.first.size();i++) cout<<b11.first[i]<<" ";
    //     // cout<<endl;
    //     // for(int i=0;i<b11.second.size();i++) cout<<b11.second[i]<<" ";
    //     // cout<<endl;

        a11 = Arithmetic::Add_with_dec(a.first,a.second,num2,dec1);
    //     // for(int i=0;i<a11.first.size();i++) cout<<a11.first[i]<<" ";
    //     // cout<<endl;
    //     // for(int i=0;i<a11.second.size();i++) cout<<a11.second[i]<<" ";
    //     // cout<<endl;

        a11p = Arithmetic::Mul_with_dec(a11.first,a11.second,tempp.first,tempp.second);
    //     // for(int i=0;i<a11p.first.size();i++) cout<<a11p.first[i]<<" ";
    //     // cout<<endl;
    //     // for(int i=0;i<a11p.second.size();i++) cout<<a11p.second[i]<<" ";
    //     // cout<<endl;

        a11pb = Arithmetic::Mul_with_dec(a11p.first,a11p.second,b.first,b.second);
    //     // for(int i=0;i<a11pb.first.size();i++) cout<<a11pb.first[i]<<" ";
    //     // cout<<endl;
    //     // for(int i=0;i<a11pb.second.size();i++) cout<<a11pb.second[i]<<" ";
    //     // cout<<endl;

        // vector<int> tb11;
        // for(int i=0;i<20;i++)
        // {
        //     tb11.push_back(b11.second[i]);
        // }
        p =Arithmetic::Div_with_dec(a11pb.first,a11pb.second,b11.first,b11.second);
        
    }
    for(int i=0;i<p.first.size();i++) cout<<p.first[i]<<" ";
        cout<<endl;
        for(int i=0;i<p.second.size();i++) cout<<p.second[i]<<" ";
        cout<<endl;
    return a;
}






































































    

