#ifndef STRUCT_H
#define STRUCT_H
#define BUFFER_SIZE 100000
typedef struct node
{
	char country[3];
	char grade[4];
	int score;
	int rate;
	int key;
}node;

typedef struct BTreeNode 
{
    
    	node *keys;
    	int t;
    	struct BTreeNode **children;
    	int n;
    	int leaf;
    
} BTreeNode;


typedef struct BTree 
{
    
    	BTreeNode *root;
    	int t;
    
} BTree;

BTreeNode* allocateNode(int t, node leaf);
void BTreeCreate(BTree *T, int t);
void BTreeSplitChild(BTreeNode *x, int i);
void BTreeInsertNonFull(BTreeNode *x, node k); 
void BTreeInsert(BTree *T, node k);
void BTreeTraverseRecurse(BTreeNode *x); 
void BTreeTraverse(BTreeNode *x);
node* search(BTreeNode *x, int k);

#endif
