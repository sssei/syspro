#define _REENTRANT
#include "btree.h"
#include <stdlib.h>
#include <stdio.h>

tnode *btree_create(){
    return NULL;
};

void btree_insert(int v, tnode **t){
    if(*t == NULL){
	if((*t = malloc(sizeof(tnode))) == NULL){
	    perror("malloc error");
	    exit(1);
	}
	(*t)->value = v;
	(*t)->left = NULL;
	(*t)->right = NULL;
	return;
    }
    if(v <= (*t)->value){
	btree_insert(v, &(*t)->left);
    }else{
	btree_insert(v, &(*t)->right);
    }
    return;
};

void btree_destroy(tnode **t){
    if(*t == NULL) return;
    btree_destroy(&(*t)->right);
    btree_destroy(&(*t)->left);
    free(*t);
    return;
};

void btree_dump(tnode *t){
    if(t == NULL) return;
    btree_dump(t->left);
    printf("%d\n", t->value);    
    btree_dump(t->right);
    return;
};



