#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node
{
  long long val;
  struct Node *left;
  struct Node *right;
} Node;

Node *gen(long long depth, long long height, long long val)
{
  if (height < depth)
  {
    Node *node = malloc(sizeof(Node));
    node->val = val;
    node->left = gen(depth, height + 1, 2 * val);
    node->right = gen(depth, height + 1, 2 * val + 1);
    return node;
  }
  else
  {
    return NULL;
  }
}

long long sum_tree(Node *node)
{
  if (node == NULL)
  {
    return 0;
  }
  else
  {
    return node->val + sum_tree(node->left) + sum_tree(node->right);
  }
}

long long main()
{
  clock_t begin = clock();
  Node *tree = gen(20, 0, 1);
  printf("Result(C): %lld\n", sum_tree(tree));
  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("- TIME(C): %.2fs\n", time_spent);
  return 0;
}