#include<bits/stdc++.h>
using namespace std;
int n,x,t;
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>x;
        t+=x;
    }
    if(t%2==0)
    cout<<"Bob";
    else
    cout<<"Alice";
}