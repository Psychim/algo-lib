#include<bits/stdc++.h>
using namespace std;
struct Node{
    int val,pri,siz;
    Node* ch[2];
    Node(int v):val(v),pri(rand()),siz(1){
        ch[0]=ch[1]=NULL;
    }
    void update(){
        siz=(ch[0]?ch[0]->siz:0)+(ch[1]?ch[1]->siz:0)+1;
    }
};
typedef pair<Node*,Node*> ptt;
inline int siz(Node* u){
    return u?u->siz:0;
}
Node* merge(Node* a,Node* b){
    if(!a) return b;
    if(!b) return a;
    if(a->pri<b->pri){
        a->ch[1]=merge(a->ch[1],b);
        a->update();
        return a;
    }
    else{
        b->ch[0]=merge(a,b->ch[0]);
        b->update();
        return b;
    }
}
ptt split(Node*u,int k){
    if(!u) return ptt(NULL,NULL);
    ptt res;
    if(siz(u->ch[0])>=k){
        res=split(u->ch[0],k);
        u->ch[0]=res.second;
        u->update();
        res.second=u;
    }
    else{
        res=split(u->ch[1],k-1-siz(u->ch[0]));
        u->ch[1]=res.first;
        u->update();
        res.first=u;
    }
    return res;
}
//x可能不在treap中
int getrank(Node*u,int x){
    if(u==NULL) return 0;
    else return x<=u->val?getrank(u->ch[0],x):getrank(u->ch[1],x)+1+siz(u->ch[0])
}
int getkth(Node* rt,int k){
    ptt x=split(rt,k-1);
    ptt y=split(x.second,1);
    Node* u=y.first;
    root=merge(x.first,merge(pos,y.second));
    return u==NULL?0:u->val;
}
void insert(Node*& rt,int v){
    int k=getrank(rt,v);
    ptt x=split(rt,k);
    Node* u=new Node(v);
    rt=merge(x.first,merge(u,x.second));
}
//要先find(v)
void remove(Node*&rt,int v){
    int k=getrank(rt,v);
    ptt x=split(rt,k);
    ptt y=split(x.second,1);
    rt=merge(x.first,y.second);
}
