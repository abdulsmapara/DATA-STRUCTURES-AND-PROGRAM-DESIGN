/*
  Problem: https://www.hackerearth.com/problem/algorithm/rahuls-lucky-id-number/
  Contest: Code_War VNIT
*/
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define req st
//#define int long long
unordered_set<int> st;
void precompute(int N)
{
    for(int i=1;i<=N;i=i*2)
    {
        for(int j=i*2;j<=N;j=j*2)
        {
            st.insert(i+j);
        }
    }
}
int process(int block[],int arr[],int n)
{
    int sz=(sqrt(n));
    int index=-1;
    for(int i=0;i<n;i++)
    {
        if(i%sz==0)
        {
            index++;
            block[index]=0;
        }
        if(st.find(arr[i]) != st.end())
        {
            block[index]++;
        }
    }
    return index+1;
}
void update(int block[],int arr[],int p,int q,int sz)
{
    int block_nm = ((p)/sz);
    if((req.find(arr[p]) != req.end() and req.find(q) != req.end()))
    {
        ;
    }
    else if((req.find(arr[p]) == req.end() and req.find(q) == req.end()))
    {
        ;
    }
    else if((req.find(arr[p]) != req.end() and req.find(q) == req.end()))
    {
        block[block_nm]+=(-1);
        arr[p] = q;
    }
    else
    {
        block[block_nm] +=1;
        arr[p] = q;
    }
    
}
int query(int block[],int arr[],int p,int q,int sz)
{
    int sum=0;
    while(p<q and p%sz!=0)
    {
        sum += req.find(arr[p])!=req.end();
        p++;
    }
    while(p+sz <= q)
    {
        int it=(p/sz);
        sum += block[it];
        p+=sz;
    }
    while(p<=q)
    {
        sum += req.find(arr[p])!=req.end();
        p++;
    }
    return sum;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    precompute(1000000001);
    int t;
    cin >> t;
    while(t--)
    {
        int n;
        cin >> n;
        int arr[n];
        int sz=(sqrt(n));
        int block[sz*sz];
        for(int i=0;i<n;i++)
        {
            cin>>arr[i];
        }
       int actual=process(block,arr,n);
        int q;
        cin >> q;
        while(q--)
        {
            int m,p,q;
            cin >> m >> p >> q;
            if(m==1){
                p--;
                update(block,arr,p,q,sz);
            }else{//if m==2
            p--;q--;
                if(p > q)
                {
                    printf("0\n");
                }
                else
                {
                    printf("%d\n",query(block,arr,p,q,sz));
                }
            }
        }
    }
    return 0;
    
}
