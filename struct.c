/*
	Algorithm Implemented from "Introduction to Algorithms by Thomas H. Cormen" text book ..!!!!  
*/
#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include <string.h>

BTreeNode* allocateNode(int t, node leaf) 
{
    
    	BTreeNode *x = (BTreeNode*)malloc(sizeof(BTreeNode));
    
    	x->t = t;
    	x->leaf = leaf.key;
    	x->keys = (node*)malloc((2*t-1)*sizeof(node));
    	x->children = (BTreeNode**)malloc((2*t)*sizeof(BTreeNode));
    	x->n = 0;
    
    	return x;
}

void BTreeCreate(BTree *T, int t) 
{
    
    	T->t = t;
	node k;
	k.key = 1;
    	BTreeNode *x = allocateNode(t,k);
    	x->leaf = 1;
    	x->n = 0;
    	T->root = x;
}

void BTreeSplitChild(BTreeNode *x, int i) 
{
    
    	int t = x->t;
    
    	BTreeNode *y = x->children[i];
	node k;
	k.key = y->leaf;
    	BTreeNode *z = allocateNode(t, k);
    	z->n = t - 1;
    
    	int j;
    
    	for(j = 0; j < t-1; j++) 
	{
    	    	z->keys[j] = y->keys[j+t];
    	}

    	if(y->leaf == 0) 
	{
        	for(j = 0; j < t; j++) 
		{
            		z->children[j] = y->children[j+t];
        	}
    	}
    
    	y->n = t-1;
    
    	for(j = x->n; j >= i+1; j--) 
	{
        	x->children[j+1] = x->children[j];
    	}
    
    	x->children[i+1] = z;
    
    	for(j = x->n - 1; j >= i; j--) 
	{
        	x->keys[j+1] = x->keys[j];
    	}	
    
    	x->keys[i] = y->keys[t-1];
    
    	x->n += 1;
    
}

void BTreeInsertNonFull(BTreeNode *x, node k) 
{
    
    	int i = x->n - 1;
    
    	if(x->leaf == 1) 
	{
        	while(i >= 0 && x->keys[i].key > k.key) 
		{
            		x->keys[i+1].key = x->keys[i].key;
            		i--;
        	}
        	x->keys[i+1].key = k.key;
		strcpy(x->keys[i+1].country,k.country);
		strcpy(x->keys[i+1].grade , k.grade);
		x->keys[i+1].score = k.score;
		x->keys[i+1].rate = k.rate;
        	x->n += 1;
    	}
    	else 
	{
        	while(i >= 0 && x->keys[i].key > k.key) i--;
        	if(x->children[i+1]->n == 2*x->t-1) 
		{
            		BTreeSplitChild(x, i+1);
            			if(k.key > x->keys[i+1].key) i++;
        	}
        	BTreeInsertNonFull(x->children[i+1], k);
    	}
}

void BTreeInsert(BTree *T, node k) 
{
    
    	int t = T->t;
    
    	BTreeNode *r = T->root;
    
    	if(r->n == 2*t-1) 
	{
		k.key = 0;
		BTreeNode *s = allocateNode(t, k);
		T->root = s;
		
		s->children[0] = r;
		
		BTreeSplitChild(s, 0);
		
		int i = 0;
		if (s->keys[0].key < k.key) i++;
			BTreeInsertNonFull(s->children[i], k);
    	}
    	else 
	{
        	BTreeInsertNonFull(r, k);
    	}
}

void BTreeTraverseRecurse(BTreeNode *x) 
{
    	int i;
    
    	for(i = 0; i < x->n; i++) 
	{
        	if(x->leaf == 0) 
			BTreeTraverseRecurse(x->children[i]);
		printf("Key : %d \n", x->keys[i].key);
		printf("Country : %s \n",x->keys[i].country);	
    	}
    
    	if(x->leaf == 0) BTreeTraverseRecurse(x->children[i]);
}

void BTreeTraverse(BTreeNode *x) 
{
    
    	BTreeTraverseRecurse(x);
    	printf("\n");
}

node* search(BTreeNode *x, int k)
{
	int i = 0;
	while(i < x->n && k > x->keys[i].key)
		++i;
	if(i < x->n && k == x->keys[i].key)
		return &x->keys[i];
	else if(x->leaf)
		return NULL;
	else 
		return search(x->children[i],k);	
}
