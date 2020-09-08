#include "ContactNode.h"

ContactNode::ContactNode(string key, Contact value, ContactNode* left, ContactNode* right)
{
    this->key = key;
    this->value = value;
    this->left = NULL;
    this->right = NULL;
}

bool ContactNode::is_leaf()
{
    return (left == NULL && right == NULL);
}
