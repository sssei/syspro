#ifndef _BTREE_H_
#define _BTREE_H_

typedef struct tnode{
    int value;
    struct tnode *left;
    struct tnode *right;
}tnode;

tnode *btree_create();

void btree_insert(int v, tnode **t);

void btree_destroy(tnode **t);

void btree_dump(tnode *t);

#endif 

