#include "rbtree.h"
#include <stdio.h>
#include <stdlib.h>

static int pow_2(int x) {
  // 2**x 계산 함수
  return 1 << x;
}

static void record_keys(rbtree *t, node_t *p, node_t **node_arr, int *node_idx_list, int cur_depth, int render_depth) {
  // visualize_tree에서 사용하기위한 배열을 재귀적으로 기록
  if (cur_depth > render_depth) {
    return;
  }
  
  node_arr[cur_depth * pow_2(render_depth) + node_idx_list[cur_depth]] = p;
  node_idx_list[cur_depth] += 1;
  if (p == t->nil) {
    record_keys(t, t->nil, node_arr, node_idx_list, cur_depth +1, render_depth);
    record_keys(t, t->nil, node_arr, node_idx_list, cur_depth +1, render_depth);
  } else {
    record_keys(t, p->left, node_arr, node_idx_list, cur_depth +1, render_depth);
    record_keys(t, p->right, node_arr, node_idx_list, cur_depth +1, render_depth);
  }
}

static void visualize_tree(rbtree *t, int render_depth) {
  // 트리 시각화 함수
  // depth는 루트를 0으로 계산
  // key_arr[i][j]: 깊이가 i인 (j+1)번째 원소의 키 **2차원 배열 접근이 불가능해 1차원 배열로 구현
    node_t **node_arr = calloc( (render_depth +1) * pow_2(render_depth), sizeof(node_t *));

  // key_idx_list[i]: key_arr[i]의 현재 인덱스
  int *node_idx_list = (int *) calloc(render_depth +1, sizeof(int));

  char *filler = "  ";

  // 키를 배열에 기록
  record_keys(t, t->root, node_arr, node_idx_list, 0, render_depth);

  // 기록된 키를 출력
  for (int i = 0; i < render_depth +1; i++) {
    for (int j = 0; j < pow_2(i); j++) {
      for (int k = 0; k < pow_2(render_depth - i); k++) { // front buffer
        printf("%s", filler);
      }
      if (node_arr[i * pow_2(render_depth) + j] == t->nil) {
        printf("\x1b[0m" "%2s", ".");
      } else if (node_arr[i * pow_2(render_depth) + j]->color == RBTREE_BLACK) {
        // 검정 노드는 흰색으로 출력
        printf("\x1b[0m" "%2d", node_arr[i * pow_2(render_depth) + j]->key);
      } else {
        // 빨강 노드는 빨간색으로 출력
        printf("\x1b[31m" "%2d", node_arr[i * pow_2(render_depth) + j]->key);
      }
      
      for (int k = 0; k < pow_2(render_depth - i) -1; k++) { // back buffer
        printf("%s", filler);
      }
    }
    printf("\n");
  }
  printf("\n");

  free(node_arr);
  free(node_idx_list);
}


void replace_node(rbtree *t, node_t *n, node_t *child)
{
   child->parent = n->parent;
    if (n->parent != t->nil) {
        if (n->parent->left == n)
            n->parent->left = child;
        else if (n->parent->right == n)
            n->parent->right = child;
    } else {
        // n이 루트 노드인 경우
        t->root = child; // 트리의 루트를 child로 업데이트
    }
}


void *erase_binary(rbtree *t, node_t *n)
{
    node_t *y;

    if (n->left == t->nil)
        replace_node(t, n, n->right);
    else if (n->right == t->nil)
        replace_node(t, n, n->left);
    else
    {
        y = tree_minimum(t, n->right);
        if (y->parent != n)
        {
            replace_node(t, y, y->right);
            y->right = n->right;
            y->right->parent = y;
        }
        replace_node(t, n, y);
        y->left = n->left;
        y->left->parent = y;
    }
    // if (y!=t->nil){
    //     free(n);
    //     printf("n해제");
    // }
}

void delete_node(rbtree *t, node_t *n)
{
    node_t *child = (n->right == t->nil) ? n->left : n->right;
    if (n == t->root)
        return;
    replace_node(t, n, child);
    
    // Debugging messages
    printf("n->color: %d, child->color: %d\n", n->color, child->color);
    if (n->color == RBTREE_BLACK)
    {
        printf("if 문 들어오나 ?\n");
        if (child->color == RBTREE_RED)
        {
            child->color = RBTREE_BLACK;
            printf("child->color set to RBTREE_BLACK\n");
        }
        else
        { // case 1:
            printf("fixed 호출\n");
            erase_fixed(t, child);
            printf("fixed 호출\n");
            //visualize_tree(t,4);
            
        }
    }
    free(n);
}


void erase_fixed(rbtree *t, node_t *n)
{

   if (n->parent == t->nil){
        return;
    }
    node_t *s = get_sibling(t, n);

    // case 2:
    if (s->color == RBTREE_RED)
    {
        printf("erase_fixed: case 2 들어오니?\n");
        n->parent->color = RBTREE_RED;
        s->color = RBTREE_BLACK;

        if (n == n->parent->left)
            rotate_left(t, n->parent);
        else
            rotate_right(t, n->parent);
    }
    // case 3:
    else if ((n->parent->color == RBTREE_BLACK) &&
             (s->color == RBTREE_BLACK) &&
             (s->left->color == RBTREE_BLACK) &&
             (s->right->color == RBTREE_BLACK))
    {
        printf("erase_fixed: case 3 들어오니?\n");
        s->color = RBTREE_RED;
        erase_fixed(t, n->parent);
    }
    // case 4:
    else if ((n->parent->color == RBTREE_RED) &&
             (s->color == RBTREE_BLACK) &&
             (s->left->color == RBTREE_BLACK) &&
             (s->right->color == RBTREE_BLACK))
    {
        printf("erase_fixed: case 4 들어오니?\n");
        s->color = RBTREE_RED;
        n->parent->color = RBTREE_BLACK;
    }
    // case 5:
    else if (s->color == RBTREE_BLACK)
    {
        if ((n == n->parent->left) &&
            (s->right->color == RBTREE_BLACK) &&
            (s->left->color == RBTREE_RED))
        {
            printf("erase_fixed: case 5 들어오니?\n");
            s->color = RBTREE_RED;
            s->left->color = RBTREE_BLACK;
            rotate_right(t, s);
        }
        else if ((n == n->parent->right) &&
                 (s->left->color == RBTREE_BLACK) &&
                 (s->right->color == RBTREE_RED))
        {
            s->color = RBTREE_RED;
            s->right->color = RBTREE_BLACK;
            rotate_left(t, s);
        }
    }
    // case 6:
    else
    {
        printf("erase_fixed: case 6 들어오니?\n");
        s->color = n->parent->color;
        n->parent->color = RBTREE_BLACK;

        if (n == n->parent->left)
        {
            s->right->color = RBTREE_BLACK;
            rotate_left(t, n->parent);
        }
        else
        {
            s->left->color = RBTREE_BLACK;
            rotate_right(t, n->parent);
        }
    }
}

node_t *tree_minimum(rbtree *t, node_t *x)
{
    while (x->left != t->nil)
        x = x->left;

    return x;
}