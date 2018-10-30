/** Reference: codeforces.com/blog/entry/20861 **/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
struct SuffixAutomaton{
    vector<map<char,int>> edges;
    vector<int> link;
    vector<int> length;
    vector<bool> isTerminal;
    vector<vector<int>> children;
    int last;
    SuffixAutomaton(string s){
        edges.push_back(map<char,int>());
        link.push_back(-1)
        length.push_back(0);
        last=0;
        for(int i=0;i<s.size();i++){
            edges.push_back(map<char,int>());
            length.push_back(i+1);
            link.push_back(0);
            int r=edges.size()-1;
            int p=last;
            while(p>=0&&edges[p].find(s[i])==edges[p].end()){
                edges[p][s[i]]=r;
                p=link[p];
            }
            if(p!=-1){
                int q = edges[p][s[i]];
                if(length[p]+1==length[q]){
                    link[r]=q;
                }
                else{
                    edges.push_back(edges[q]);
                    length.push_back(length[p]+1);
                    link.push_back(link[q]);
                    int qq=edges.size()-1;
                    link[q]=qq;
                    link[r]=qq;
                    while(p>=0&&edges[p][s[i]]==q){
                        edges[p][s[i]]=qq;
                        p=link[p];
                    }
                }
            }
            last=r;
        }
        findTerminals();
        findChildren();
    }
    void findTerminals(){
        isTerminal=vector<bool>(link.size(),false);
        int p=last;
        while(p>0){
            isTerminal[p]=true;
            p=link[p];
        }
    }
    void findChildren(){
        children=vector<vector<int>>(link.size());
        for(int i=0;i<link.size();i++){
            if(link[i]>=0) children[link[i]].push_back(i);
        }
    }
    int findNode(string w){
        int n=0;
        for(int i=0;i<w.size();i++){
            if(edges[n].find(w[i])==edges[n].end())
                return -1;
            n=edges[n][w[i]];
        }
        return n;
    }
    bool isSubstr(string w){
        return findNode(w)!=-1;
    }
    bool isSuffix(string w){
        int n=findNode(w);
        return n!=-1&&isTerminal[n];
    }
    void countDistinctSubstr(int n,vector<ll>&dp){
        map<char,int>::iterator ite;
        ll ans=1;
        for(ite=edges[n].begin();ite!=edges[n].end();ite++){
            if(dp[ite.second]==0)
                countDistinctSubstr(ite.second,dp);
            ans+=dp[ite.second];
        }
        dp[n]=ans;
    }
    ll countDistinctSubstr(){
        vector<ll> dp(link.size(),0);
        countDistinctSubstr(0,dp);
        return dp[0]-1;
    }
    void countStrOccurs(int n,vector<ll>&dp){
        map<char,int>::iterator ite;
        ll ans=isTerminal[n]?1:0;
        for(ite=edges[n].begin();ite!=edges[n].end();ite++){
            if(dp[ite.second]==-1)
                countStrOccurs(ite.second,dp);
            ans+=dp[ite.second];
        }
        dp[n]=ans;
    }
    ll countStrOccurs(string w){
        vector<ll> dp(link.size(),-1);
        int n=findPosition(w);
        if(n==-1)return 0;
        countStrOccurs(n,dp);
        return dp[n];
    }
};

