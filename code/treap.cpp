#include <bits/stdc++.h>

using namespace std;

typedef int T;
typedef char T1;

struct Treap {
    T key, priority, size;
    Treap *lc, *rc;

    T1 value;
    bool reverse;
    Treap(T key, T1 value): key(key), priority(rand()), 
        size(1), lc(NULL), rc(NULL), value(value), reverse(false) {}
};

inline int size(Treap *target) {
    if (!target) return 0;
    return target->size;
}

inline void pull(Treap *target) {
    target->size = size(target->lc) + size(target->rc) + 1;
}

void reverseIt(Treap *target) {
    if (!(target->reverse)) return;
    Treap *lc = target->lc;
    target->lc = target->rc;
    target->rc = lc;
    target->reverse = false;
    if (target->lc) (target->lc->reverse) ^= true;
    if (target->rc) (target->rc->reverse) ^= true;
}

Treap* merge(Treap *lhs, Treap *rhs) {
    if (!lhs || !rhs) return lhs? lhs: rhs;
    if (lhs->priority > rhs->priority) {
        reverseIt(lhs);
        lhs->rc = merge(lhs->rc, rhs);
        pull(lhs);
        return lhs;
    }
    else {
        reverseIt(rhs);
        rhs->lc = merge(lhs, rhs->lc);
        pull(rhs);
        return rhs;
    }
}

void split(Treap *target, Treap *&lhs, Treap *&rhs, int k) {
    if (!target) lhs = rhs = NULL;
    else if (k > target->key) {
        lhs = target;
        split(target->rc, lhs->rc, rhs, k);
        pull(lhs);
    }
    else {
        rhs = target;
        split(target->lc, lhs, rhs->lc, k);
        pull(rhs);
    }
}

Treap* insert(Treap *target, int key, int value) {
    Treap *lhs, *rhs;  
    split(target, lhs, rhs, key);
    return merge(merge(lhs, new Treap(key, value)), rhs);
}

/* split by size */
void splitSize(Treap *target, Treap *&lhs, Treap *& rhs, int k) {
    if (!target) lhs = rhs = NULL;
    else {
        reverseIt(target);
        if (size(target->lc) < k) {
            lhs = target;
            splitSize(target->rc, lhs->rc, rhs, k-size(target->lc)-1);
            pull(lhs);
        }
        else {
            rhs = target;
            splitSize(target->lc, lhs, rhs->lc, k);
            pull(rhs);
        }
    }
}

/* do lazy tag */
Treap* reverseIt(Treap *target, int lp, int rp) {
    Treap *A, *B, *C, *D;
    splitSize(target, A, B, lp-1);
    splitSize(B, C, D, rp-lp+1);
    C->reverse ^= true;
    return merge( merge(A, C), D);
}

/* delete singal key */
Treap* del(Treap *target, int key) {
    if (target->key == key) return merge(target->lc, target->rc);
    else if (target->key > key) target->lc = del(target->lc, key);
    else target->rc = del(target->rc, key);
    pull(target);
    return target;
}

T findK(Treap *target, int k) {
    if (size(target->lc)+1 == k) return target->key;
    else if (size(target->lc) < k) return findK(target->rc, k-size(target->lc)-1);
    else return findK(target->lc, k);
}

/* find the kth's value */
T1 findK(Treap *target, int k) {
    reverseIt(target);
    if (size(target->lc)+1 == k) return target->value;
    else if (size(target->lc) < k) return findK(target->rc, k-size(target->lc)-1);
    else return findK(target->lc, k);
}

int main () {
    return 0;
}

/* pass POJ2761, CF gym 100488 pL */
