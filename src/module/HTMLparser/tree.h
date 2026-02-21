#ifndef TREE_WEB_H
#define TREE_WEB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct Attribute {
    char* name;
    char* value;
    struct Attribute* next;
} Attribute;

typedef struct TreeNode {
    char* tag_name;
    Attribute* attributes;
    char* text;
    struct TreeNode* first_child;
    struct TreeNode* next_sibling;
    struct TreeNode* parent;
} TreeNode;

void free_tree(TreeNode* node);
void print_tree(TreeNode* node, int depth);
TreeNode* parse_to_tree(const char* file_path);

#endif
