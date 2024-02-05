#include "rbtree.h"
#include <stdlib.h>
#include <stdio.h>



rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  // TODO: initialize struct if needed
  p->nil=(node_t*)calloc(1,sizeof(node_t));
  p->nil->color=RBTREE_BLACK;
  p->root=p->nil;

  return p;
}

void delete_rbtree(rbtree *t) {
  // TODO: reclaim the tree nodes's memory
  // if (t->root != t->nil)
  //   free(t->root);
  // // t->root=NULL;

  //중위 순회 하면서 모든 노드 해제
  free_inorder_traversal(t,t->root);
  //nil 노드 해제
  free(t->nil);
  t->nil=NULL;
  //트리구조 해제
  free(t);
  t = NULL;
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
  // TODO: implement insert
  node_t *n=(node_t*)calloc(1,sizeof(node_t));
  if(!n)
    return NULL;
  //////노드 초기속성 설정//////
  n->color=RBTREE_RED;
  n->key=key;
  n->parent=t->nil;
  n->left=t->nil;
  n->right=t->nil;
  ////////////////////////////
  
  //이진탐색으로 노드삽입
  insert_binary(t,n);
  //삽입후 속성 재설정
  insert_fixed(t,n);


  return t->root;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  // TODO: implement find

  node_t *current = t->root;

    while (current != NULL && current != t->nil) {
        if (key == current->key) {
            // Key found
            return current;
        } else if (key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    // Key not found
    return NULL;
}

node_t *rbtree_min(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

node_t *rbtree_max(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

int rbtree_erase(rbtree *t, node_t *p) {
  // // TODO: implement erase
  node_t *y;
  erase_binary(t, p);
  
  if (y!=t->nil){
    delete_node(t, p);
    printf("delete_node 호출\n");
  }
  if(p==t->root)
  {
    t->root=t->nil;
  }

  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  return 0;
}
