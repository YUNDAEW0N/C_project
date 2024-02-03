#include "rbtree.h"

//할아버지 노드 가져오는 함수
node_t *get_grandparent(rbtree *t,node_t *n)
{
  if ((n!=t->nil) && (n->parent!=t->nil))
    return n->parent->parent;
  else
    return t->nil;
}
//삼촌 노드 가져오는 함수
node_t *get_uncle(rbtree *t, node_t *n)
{
  node_t *g=get_grandparent(t,n);
  if(g==t->nil)
    return t->nil;
  if (n->parent==g->left)
    return g->right;
  else
    return g->left;
}

//로테이트 레프트
void rotate_left(rbtree *t, node_t *n)
{
    node_t *c=n->right;
    node_t *p=n->parent;

    if (c->left!=t->nil)
        c->left->parent=n;
    
    n->right = c->left;
    n->parent = c;
    c->left = n;
    c->parent = p;

    if (p!=t->nil){
        if(p->left == n)
            p->left = c;
        else
            p->right = c;
    }
}

void rotate_right(rbtree *t, node_t *n)
{
    node_t *c=n->left;
    node_t *p=n->parent;

    if (c->right != t->nil)
        c->right->parent = n;
    
    n->left = c->right;
    n->parent = c;
    c->right = n;
    c->parent = p;

    if (p != t->nil){
        if (p->right ==n)
            p->right = c;
        else
            p->left = c;
    }
}

void free_inorder_traversal(rbtree *t, node_t *root)
{
    if (root != t->nil){
        free_inorder_traversal(t,root->left);
        free(root);
        free_inorder_traversal(t,root->right);
    }
}

