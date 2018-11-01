/** Reference: https://www.cnblogs.com/yjiyjige/p/3263858.html **/
#include<bits/stdc++.h>
using namespace std;
struct KMP{
    static const int maxn=1e5;
    string p;
    int nxt[maxn];
    KMP(string pattern){
        p=pattern;
        nxt[0]=-1;
        int j=-1;
        int i=1;
        while(i<p.size()){
            if(j!=-1&&p[i]!=p[j+1])
                j=nxt[j];
            else if(p[i]==p[j+1])
                nxt[i++]=++j;
            else nxt[i++]=j;
        }
        for(i=0;i<p.size();++i) printf("%d > %d\n",i,nxt[i]);
    }
    int match(string s){
        int j=-1;
        int i=0;
        while(i<s.size()){
            if(j!=-1&&s[i]!=p[j+1])
                j=nxt[j];
            else if(s[i++]==p[j+1]&&++j==p.size()-1)
                    return i-1-j;

        }
        return -1;
    }
};
int main(){
    string p;
    while(cin>>p){
        KMP kmp(p);
        string s;
        cin>>s;
        cout<<kmp.match(s)<<endl;
    }
}
