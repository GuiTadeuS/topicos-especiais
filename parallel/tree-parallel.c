#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

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
#pragma omp parallel sections
        {
#pragma omp section
            {
                node->left = gen(depth, height + 1, 2 * val);
            }
#pragma omp section
            {
                node->right = gen(depth, height + 1, 2 * val + 1);
            }
        }
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
        long long sum = node->val;
        long long left_sum = 0;
        long long right_sum = 0;
#pragma omp parallel sections reduction(+ : sum)
        {
#pragma omp section
            {
                left_sum = sum_tree(node->left);
            }
#pragma omp section
            {
                right_sum = sum_tree(node->right);
            }
        }
        return sum + left_sum + right_sum;
    }
}

int main()
{
    clock_t begin = clock();
    Node *tree = gen(20, 0, 1);
    printf("Result(C): %lld\n", sum_tree(tree));
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("- TIME(C): %.2fs\n", time_spent);
    return 0;
}