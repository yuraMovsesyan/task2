#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int val;
    struct Node* left;
    struct Node* right;
};

struct Node* create(int value)
{
    struct Node* res = (struct Node*)malloc(sizeof(struct Node));
    res->val = value;
    res->left = res->right = NULL;
    return res;
}

struct Node* insert(struct Node* node, int value)
{
    if (node == NULL)
    {
        return create(value);
    }

    if (value < node->val)
    {
        node->left = insert(node->left, value);
    } else if (value > node->val)
    {
        node->right = insert(node->right, value);
    }

    return node;
}

void rec_print(struct Node* node)
{
    if (node != NULL)
    {
        rec_print(node->left);
        printf("%d ", node->val);
        rec_print(node->right);
    }
}

struct Node* find(struct Node* node, int value)
{

    if (node == NULL || node->val == value)
    {
        return node;
    }

    if (value < node->val)
    {
        return find(node->left, value);
    }

    return find(node->right, value);
}

struct Node* find_min(struct Node* node)
{
    if (node == NULL || node->left == NULL)
    {
        return node;
    }

    return find_min(node->left);
}

struct Node* del(struct Node* node, int value)
{
    if (node == NULL)
    {
        return node;
    }

    if (value < node->val)
    {
        node->left = del(node->left, value);
    } else if (value > node->val)
    {
        node->right = del(node->right, value);
    } else
    {
        if (node->left == NULL)
        {
            struct Node* temp = node->right;
            free(node);
            return temp;
        } else if (node->right == NULL)
        {
            struct Node* temp = node->left;
            free(node);
            return temp;
        }

        struct Node* temp = find_min(node->right);

        node->val = temp->val;

        node->right = del(node->right, temp->val);
    }

    return node;
}

int main()
{
    struct Node* root = NULL;

    char opr;
    int key;

    while (scanf(" %c%d", &opr, &key) != EOF)
    {
        switch (opr)
        {
            case '+':   root = insert(root, key); break;
            case '-':   root = del(root, key); break;
            case '?':   if (find(root, key) != NULL) printf("%d yes\n", key); 
                        else printf("%d no\n", key); break;
        }
    }


    return 0;
}
