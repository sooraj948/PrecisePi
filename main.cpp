#include <iostream>
#include <string>
#include <vector>
#include "Arithmetic.hpp"
using namespace std;
int main()
{
    vector <int> num1,num2,dec1,dec2,result;
    int size1,size2,size_dec1,size_dec2;
    // cin>>size1>>size2>>size_dec1>>size_dec2;
    // for(int i=0;i<size1;i++)
    // {
    //     int dig;
    //     cin>>dig;
    //     num1.push_back(dig);
    // }
    // for(int i=0;i<size2;i++)
    // {
    //     int dig;
    //     cin>>dig;
    //     num2.push_back(dig);
    // }
    // for(int i=0;i<size_dec1;i++)
    // {
    //     int dig;
    //     cin>>dig;
    //     dec1.push_back(dig);
    // }
    // for(int i=0;i<size_dec2;i++)
    // {
    //     int dig;
    //     cin>>dig;
    //     dec2.push_back(dig);
    // }
    Arithmetic a = Arithmetic(10);
    // result = a.Div();
    // vector<int> quo = a.Div(num1,num2).first;
    // vector<int> rem = a.Div(num1,num2).second;

    // for(int i=0;i<quo.size();i++)
    // {
    //     cout<<quo[i]<<" ";
    // }
    // cout<<endl;
    // for(int i=0;i<rem.size();i++)
    // {
    //     cout<<rem[i]<<" ";
    // }
    // cout<<endl;

    vector <int> x=a.PI().first;
    // for(int i=0;i<x.size();i++) cout<<x[i]<<" ";
    // cout<<endl;
    // vector <int> x_dec = a.squareroot(num1,num2,dec1,dec2).second;
   
    // for(int i=0;i<x_dec.size();i++) cout<<x_dec[i]<<" ";
    // cout<<endl;
    // result = a.decimal_after_division(num1,num2);
    // for(int i=0;i<result.size();i++)
    //  {
    //      cout<<result[i];
    //  }

}

