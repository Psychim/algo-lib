#include<bits/stdc++.h>
using namespace std;
struct Node{
    int v,k;
    Node *ch[2];
};
Node*null=new Node();
void rotate(Node*&u,int d){
    Node* tmp=u->ch[d];
    if(tmp==null) return;
    u->ch[d]=tmp->ch[d^1];
    tmp->ch[d^1]=u;
    u=tmp;
}
void insert(Node*&u,int val){
    if(u==null){
        u=new Node();
        u->v=val;
        u->k=rand();
        ch[0]=ch[1]=null;
    }
    int d=val>u->v;
    insert(u->ch[d],val);
    if(u->ch[d]->k>u->k)
        rotate(u,d);
}
void remove(Node*&u,int val){
    if(val==u->v){
        if(u->ch[0]==null)u=u->ch[1];
        else if(u->ch[1]==null)u=u->ch[0];
        else{
            int d=u->ch[0]->k<u->ch[1]->k?1:0;
            rotate(u,d);
            remove(u->ch[d^1]);
        }
    }
    else if(val<u->v) remove(u->ch[0],val);
    else remove(u->ch[1],val);
}
bool find(Node*u,int val){
    while(u!=null){
        if(u->v==val) return true;
        if(val<u->v) u=u->ch[0];
        else u=u->ch[1];
    }
    return false;
}
