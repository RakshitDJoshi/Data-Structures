#include<iostream>
#include<vector>
#include<cmath>
using namespace std;
typedef vector<int> vi;
void build_seg(vi &t, vi &A, int vertex, int L, int R)
{
    if(L==R)
    {
        t[vertex]=L;
        return;
    }
    int nL=vertex*2; int nR=vertex*2+1;
    build_seg(t, A, nL, L, (L+R)/2);
    build_seg(t, A, nR, (L+R)/2 +1, R);
    int lcontent=t[nL], rcontent=t[nR];
    int lvalue=A[lcontent], rvalue=A[rcontent];
    t[vertex]=(lvalue<rvalue)? lcontent:rcontent;
}
void st_create(vi &t, vi &A)
{
    int len=(int)(2*pow(2.0,floor(log((double)A.size()/log(2))+1)));
    t.assign(len,0);
    build_seg(t, A, 1, 0, (int)A.size()-1);
}
int rmq(vi &t, vi &A, int vertex, int L, int R, int i,int j)
{
    if(i>R || j<L)
        return -1;
    if(i<=L && j>=R)
        return t[vertex];
    int p1= rmq(t, A, vertex*2,             L, (L+R)/2, i, j);
    int p2= rmq(t, A, vertex*2 +1, (L+R)/2 +1,       R, i, j);
    if(p1==-1) return p2;
    if(p2==-1) return p1;
    return (( A[p1]<A[p2] )? p1 : p2);
}
int rmq(vi &t, vi &A, int i, int j)
{
    return rmq(t, A, 1, 0, (int)A.size()-1, i, j);
}
int main()
{
    int arr[7] = { 8, 7, 3, 9, 5, 1, 10 }; // the original array
    vi A(arr, arr + 7);
    vi st; st_create(st, A);
    printf("RMQ(1, 3) = %d\n", rmq(st, A, 1, 3)); // answer is index 2
    printf("RMQ(4, 6) = %d\n", rmq(st, A, 4, 6));
    return 0;
}
