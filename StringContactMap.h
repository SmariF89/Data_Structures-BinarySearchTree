#ifndef STRINGCONTACTMAP_H
#define STRINGCONTACTMAP_H

#include <iostream>
#include <string>
#include <vector>
#include "ContactNode.h"

class KeyException { };

class StringContactMap
{

public:
    // Creates an empty map.
    StringContactMap ();
    StringContactMap (int test);

    ~StringContactMap();

    // Returns the number of entries in this map.
    int size() const;

    // Returns true if and only if the map contains no entries.
    bool empty() const;

    // Returns a vector containing the contacts in this map, ordered by
    // their keys in increasing order.
    vector<Contact> all_contacts();

    // Adds the specified key to the map associated with the specified
    // contact.
    // If there exists an entry in the map with the specified key, it
    // should be replaced with the specified value.
    void add(string key, Contact value);

    // Returns true if and only if there exists an entry in the map with
    // the specified key.
    bool contains(string key);

    // Returns the contact associated with the specified key.
    // Throws KeyException if no such contact exists.
    Contact get(string key);

    // Removes the entry with the specified key from the map.
    // If no entry in the map has the specified key, this operation has no
    // effect.
    void remove(string key);

    // Returns a vector containing the contacts in this map, whose key is
    // prefixed by 'prefix'. The contacts are ordered by their
    // keys in increasing order,
    // NOTE: This is for part 3 of the assignment.
    vector<Contact> prefix_search(string prefix) const;



    friend ostream& operator <<(ostream& out, StringContactMap& map);

private:
    NodePtr root;

    // Deallocates all memory allocated for the specified tree.
    void free_memory(NodePtr node);

    // Optional helper function
    // Adds the the Contacts in the specified tree, whose key is prefixed
    // by 'prefix', to the vector v. The contacts are ordered by their keys
    // in increasing order.
    // NOTE: This is for part C of the assignment.
    void prefix_search(NodePtr node, string prefix, vector<Contact>& v) const;

    //A recursive find function the returns a pointer reference.
    ContactNode* &find(ContactNode* &node, string key);

    //Adds all contacts to a vector.
    vector<Contact> all_contacts_Recursive(NodePtr node, vector<Contact>& contacts);

    void remove_recursive(NodePtr &nodeToRemove);

    //Help function for removal.
    NodePtr &find_rightmost(NodePtr &node);

    //Number of nodes.
    int treeSize;

    void printPreFix(NodePtr node);
    void printInFix(NodePtr node);
    void printPostFix(NodePtr node);
};

#endif
