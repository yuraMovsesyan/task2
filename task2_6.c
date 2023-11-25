#include <stdio.h>
#include <stdlib.h>
#include <graphviz/cgraph.h>

struct Node
{
    int val;
    struct Node* left;
    struct Node* right;

    struct Node* parent;

    Agnode_t *node;
};

Agraph_t *graph;

struct Node* create(int value, struct Node* parent)
{
    struct Node* res = (struct Node*)malloc(sizeof(struct Node));
    res->val = value;
    res->left = res->right = NULL;
    char buff[20];
    sprintf(buff, "%d", value);
    res->node = agnode(graph, buff, 1);
    
    if (parent != NULL)
    {
        res->parent = parent;
        agedge(graph, parent->node, res->node, NULL, 1);
    }
    else
    {
        res->parent = NULL;
    }

    return res;
}

struct Node* insert(struct Node* node, int value, struct Node* parent)
{
    if (node == NULL)
    {
        return create(value, parent);
    }

    if (value < node->val)
    {
        node->left = insert(node->left, value, node);
    } else if (value > node->val)
    {
        node->right = insert(node->right, value, node);
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
            agdelnode(graph, node->node);
            free(node);
            return temp;
        } else if (node->right == NULL)
        {
            struct Node* temp = node->left;
            agdelnode(graph, node->node);
            free(node);
            return temp;
        }

        struct Node* temp = find_min(node->right);

        node->val = temp->val;

        agdelnode(graph, node->node);
        node->right = del(node->right, temp->val);

        char buff[20];
        sprintf(buff, "%d", node->val);

        node->node = agnode(graph, buff, 1);

        if (node->parent != NULL)
        {
            agedge(graph, node->parent->node, node->node, NULL, 1);
        }

        if (node->left != NULL)
        {
            agedge(graph, node->node, node->left->node, NULL, 1);
        }

        if (node->right != NULL)
        {
            agedge(graph, node->node, node->right->node, NULL, 1);
        }

        
    }

    return node;
}

void graph_to_png()
{
    FILE *file = fopen("graph.dot", "w");

    agwrite(graph, file);

    fclose(file);

    system("dot -Tpng -O graph.dot");
}

int main()
{
    graph = agopen("MyGraph", Agdirected, NULL);

    struct Node* root = NULL;

    graph_to_png();
    char opr;
    int key;

    while (scanf(" %c%d", &opr, &key) != EOF)
    {
        switch (opr)
        {
            case '+':   root = insert(root, key, root); break;
            case '-':   root = del(root, key); break;
            case '?':   if (find(root, key) != NULL) printf("%d yes\n", key); 
                        else printf("%d no\n", key); break;

        }

        graph_to_png();
    }

    agclose(graph);

    return 0;
}
