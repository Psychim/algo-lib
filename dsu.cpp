#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5;
int father[maxn];
void initdsu(int n){
    for(int i=0;i<n;i++){
        father[i]=i;
    }
}
int findset(int u){
    if(father[u]==u)return u;
    return father[u]=findset(father[u]);
}
int unionset(int u,int v){
    u=findset(u);
    v=findset(v);
    father[v]=u;
    return u;
}
