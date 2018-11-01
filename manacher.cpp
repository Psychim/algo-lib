/** Reference: https://www.cnblogs.com/biyeymyhjob/archive/2012/10/04/2711527.html **/
#include<bits/stdc++.h>
using namespace std;
struct Manacher{
    static const int maxn=1e5;
    string s;
    int p[maxn*2+1];
    inline char get(int i){
        if(i<0) return '$';
        if(i%2) return s[i/2];
        return '#';
    }
    Manacher(string str){
        s=str;
        int mx=0,id=0;
        for(int i=0;i<2*s.size()+1;++i){
            if(mx>i) p[i]=min(p[2*id-i],mx-i);
            else p[i]=1;
            while(get(i-p[i])==get(i+p[i])) ++p[i];
            if(i+p[i]>mx){
                mx=i+p[i];
                id=i;
            }
        }
    }
};
int main(){
    string p;
    while(cin>>p){
        Manacher m(p);
        for(int i=0;i<2*p.size()+1;++i){
            printf("%c > %d\n",m.get(i),m.p[i]);
        }
    }
}
