#include "game.h"
#include <bits/stdc++.h>

using namespace std;

#define dbg(x) cout << "[" << #x << ": " << x << "] ";
/*
struct SegmentTree{
    struct Node{
        int64_t val;
        Node *lc, *rc;
 
        Node() : lc(0), rc(0) {
            val = 0LL;
        }
    };
    
    deque<Node> tree;
 
    Node* new_node(){
        tree.emplace_back();
        return &tree.back();
    }

    Node *root;
    int L, R;

    void init(int _L, int _R){
        this->L = _L;
        this->R = _R;
        root = new_node();
    }
 
    void update(int idx, int64_t val, Node* &node, int l, int r){
        if(!node) node = new_node();
        if(r - l == 1){
            node->val = val;
            return;
        }
 
        int mid = (l + r) >> 1;
 
        if(idx < mid) update(idx, val, node->lc, l, mid);
        else update(idx, val, node->rc, mid, r);
 
        node->val = gcd((node->lc ? node->lc->val : 0), (node->rc ? node->rc->val : 0));
    }
 
    int64_t query(int l, int r, Node* &node, int lx, int rx){
        if(r <= lx || l >= rx || !node)
            return 0;
        if(lx >= l && rx <= r)
            return node->val;
 
        int mid = (lx + rx) >> 1;
        
        return gcd(query(l, r, node->lc, lx, mid), query(l, r, node->rc, mid, rx));
    }
 
    void update(int idx, int64_t val){
        update(idx, val, root, L, R);
    }
 
    int64_t query(int l, int r){
        return query(l, r, root, L, R);
    }
};
*/

struct QuadTree{
    struct Node{
        int64_t val;
        Node *top_left, *top_right, *bottom_left, *bottom_right;
        
        Node() : top_left(0), top_right(0), bottom_left(0), bottom_right(0) {
            val = 0;
        }
    }; 

    deque<Node> tree;
    Node *root;

    Node* new_node(){
        tree.emplace_back();
        return &tree.back();
    }

    int R, C;

    void init(int _R, int _C){
        root = new_node();
        this->R = _R;
        this->C = _C;
    }

    void update(int P, int Q, int64_t val, Node* &node, int left, int right, int top, int bottom){
        if(!node) node = new_node();
        if(bottom - top == 1 && right - left == 1){
            node->val = val;
            return;
        }

        int midR = (top + bottom) >> 1, midC = (left + right) >> 1;

        if(P < midR){
            if(Q < midC)
                update(P, Q, val, node->top_left, left, midC, top, midR);
            else update(P, Q, val, node->top_right, midC, right, top, midR);
        }
        else{
            if(Q < midC)
                update(P, Q, val, node->bottom_left, left, midC, midR, bottom);
            else update(P, Q, val, node->bottom_right, midC, right, midR, bottom);
        }
        
        node->val = 0;
        if(node->top_left) node->val = gcd(node->val, node->top_left->val);
        if(node->top_right) node->val = gcd(node->val, node->top_right->val);
        if(node->bottom_right) node->val = gcd(node->val, node->bottom_right->val);
        if(node->bottom_left) node->val = gcd(node->val, node->bottom_left->val);
    }

    int64_t query(int P, int Q, int U, int V, Node* &node, int left, int right, int top, int bottom){
        if(P >= bottom || U <= top || Q >= right || V <= left || !node)
            return 0;
        if(P <= top && U >= bottom && Q <= left && V >= right)
            return node->val;

        int midR = (top + bottom) >> 1, midC = (left + right) >> 1;

        return gcd(gcd(query(P, Q, U, V, node->top_left, left, midC, top, midR), 
                   query(P, Q, U, V, node->top_right, midC, right, top, midR)),
                   gcd(query(P, Q, U, V, node->bottom_left, left, midC, midR, bottom),
                   query(P, Q, U, V, node->bottom_right, midC, right, midR, bottom)));
    }

    void update(int P, int Q, int64_t val){
        update(P, Q, val, root, 0, C, 0, R);
    }

    int64_t query(int P, int Q, int U, int V){
        return query(P, Q, U, V, root, 0, C, 0, R);
    }
};

QuadTree T;
void init(int R, int C) {
    T.init(R, C);
}

void update(int P, int Q, long long K) {
    T.update(P, Q, K);
}

long long calculate(int P, int Q, int U, int V) {
    return T.query(P, Q, U+1, V+1);
}