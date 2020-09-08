#ifndef CONTACTNODE_H
#define CONTACTNODE_H

#include <iostream>
#include <string>
#include <vector>
#include "Contact.h"

struct ContactNode
{
    ContactNode(string key, Contact value, ContactNode* left = NULL, ContactNode* right = NULL);
    bool is_leaf();

    string key;
    Contact value;
    ContactNode *left;
    ContactNode *right;
};

typedef ContactNode* NodePtr;

#endif
