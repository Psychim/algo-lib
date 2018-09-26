#include<bits/stdc++.h>
using namespace std;
struct Node{
    int v,sz=0;
    Node *ch[2];
    void update(){
        siz=ch[0]->sz+ch[1]->sz+1;
    }
    int cmp(int k){
        int ord=ch[0]->sz+1;
        if(ord==k) return -1;
        return k<ord?0:1;
    }
};
Node*null=new Node();
Node*root=null;

void rotate(Node*&u,int d){
    Node* tmp=u->ch[d];
    if(tmp==null) return;
    u->ch[d]=tmp->ch[d^1];
    tmp->ch[d^1]=u;
    u->update();
    tmp->update();
    u=tmp;
}
void insert(Node*&u,int val){
    if(u==null){
        u=new Node();
        u->v=val;
        u->sz=1;
        ch[0]=ch[1]=null;
    }
    int d=val>u->v?1:0;
    insert(u->ch[d],val);
    u->update();
    if(u->ch[d]->k>u->k)
        rotate(u,d);
}
void splay(Node*&u,int k){
    int d=u->cmp(k);
    if(d==1) k-=u->ch[0]->sz+1;
    if(d!=1){
        Node* p=u->ch[d];
        int d2=p->cmp(k);
        int k2=(d2==0?k:k-p->ch[0]->sz-1);
        if(d2!=-1){
            splay(p->ch[d2],k2);
            if(d==d2) rotate(u,d);
            else rotate(u->ch[d],d^1);
        }
        rotate(u,d);
    }
}
Node* merge(Node* left,Node* right){
    splay(left,left->s);
    left->ch[1]=right;
    left->update();
    return left;
}
void split(Node* u,int k,Node* &left,Node*&right){
    splay(u,k);
    left=u;
    right=u->ch[1];
    u->ch[1]=null;
    left->maintain();
}
void remove(Node*&u,int val){
    if(val==u->v){
        if(u->ch[0]==null)u=u->ch[1];
        else if(u->ch[1]==null)u=u->ch[0];
        else{
            int d=u->ch[0]->k<u->ch[1]->k?1:0;
            rotate(u,d);
            remove(u->ch[d^1]);
            u->update();
        }
    }
    else if(val<u->v) remove(u->ch[0],val);
    else remove(u->ch[1],val);
    u->update();
}
bool find(Node*u,int val){
    while(u!=null){
        if(u->v==val) return true;
        if(val<u->v) u=u->ch[0];
        else u=u->ch[1];
    }
    return false;
}

