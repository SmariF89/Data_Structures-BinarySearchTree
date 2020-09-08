#include "StringContactMap.h"

using namespace std;

StringContactMap::StringContactMap ()
{
    root = NULL;
    treeSize = 0;
}

StringContactMap::StringContactMap (int test)
{
    Contact A;
    A.name  = "A";
    A.address = "";
    A.email = "";
    A.phone = "";

    Contact B;
    B.name  = "B";
    B.address = "";
    B.email = "";
    B.phone = "";

    Contact C;
    C.name  = "C";
    C.address = "";
    C.email = "";
    C.phone = "";

    Contact D;
    D.name  = "D";
    D.address = "";
    D.email = "";
    D.phone = "";

    Contact E;
    E.name  = "E";
    E.address = "";
    E.email = "";
    E.phone = "";

    Contact F;
    F.name  = "F";
    F.address = "";
    F.email = "";
    F.phone = "";

    Contact G;
    G.name  = "G";
    G.address = "";
    G.email = "";
    G.phone = "";

    Contact H;
    H.name  = "H";
    H.address = "";
    H.email = "";
    H.phone = "";

    Contact I;
    I.name  = "I";
    I.address = "";
    I.email = "";
    I.phone = "";

    Contact J;
    J.name  = "J";
    J.address = "";
    J.email = "";
    J.phone = "";

    root = new ContactNode(A.name, A, NULL, NULL);
    root->right = new ContactNode(B.name, B, NULL, NULL);
    root->right->left = new ContactNode(C.name, C, NULL, NULL);
    root->right->left->left = new ContactNode(D.name, D, NULL, NULL);
    root->right->left->right = new ContactNode(E.name, E, NULL, NULL);
    root->right->left->right->left = new ContactNode(G.name, G, NULL, NULL);
    root->right->left->right->right = new ContactNode(H.name, H, NULL, NULL);
    root->right->left->left->left = new ContactNode(F.name, F, NULL, NULL);
    root->right->left->left->left->left = new ContactNode(I.name, I, NULL, NULL);
    root->right->left->left->left->right = new ContactNode(J.name, J, NULL, NULL);

    treeSize = test;

    cout << "PREFIX: ";
    printPreFix(root);
    cout << endl << endl;
    cout << "INFIX: ";
    printInFix(root);
    cout << endl << endl;
    cout << "POSTFIX: ";
    printPostFix(root);
    cout << endl << endl;
}

StringContactMap::~StringContactMap()
{
    free_memory(root);
}

int StringContactMap::size() const
{
    return treeSize;
}

bool StringContactMap::empty() const
{
    return root == NULL;
}

vector<Contact> StringContactMap::all_contacts()
{
    vector<Contact> contacts;
    contacts = all_contacts_Recursive(root, contacts);

    return contacts;
}

//A recursive help-function for all_contacts
vector<Contact> StringContactMap::all_contacts_Recursive(NodePtr node, vector<Contact>& contacts)
{
    if(node != NULL)
    {
        all_contacts_Recursive(node->left, contacts);
        contacts.push_back(node->value);
        all_contacts_Recursive(node->right, contacts);
    }

    return contacts;
}

void StringContactMap::add(string key, Contact value)
{
    if(empty())                                         //Ef tréð er tómt þá hlýtur fyrsta nóðan að vera rótin.
    {
        root = new ContactNode(key, value, NULL, NULL);
        treeSize++;
    }

    NodePtr &newNode = find(root, key);

    if(contains(key))                                   //Uppfærir value ef lykill er þegar til.
    {                                                   //Tré stækkar ekki.
        newNode->value = value;
    }
    else if(newNode == NULL)                            //Hengir á nýja nóðu á tréð þar sem er lauf.
    {
        newNode = new ContactNode(key, value, NULL, NULL);
        treeSize++;
    }
}

void StringContactMap::remove(string key)
{
    if(!contains(key))
    {
        return;
    }

    NodePtr &nodeToRemove = find(root, key);

    remove_recursive(nodeToRemove);

    treeSize--;
}

void StringContactMap::remove_recursive(NodePtr &nodeToRemove)                     //FOUR CASES//
{
    if(nodeToRemove->is_leaf())                                                 //      .O.
    {
        delete nodeToRemove;
        nodeToRemove = NULL;
    }
    else if(nodeToRemove->left != NULL && nodeToRemove->right == NULL)
    {
                                                                               //        O.
        NodePtr tmp = nodeToRemove;                                            //       /
        nodeToRemove = nodeToRemove->left;
        delete tmp;
    }
    else if(nodeToRemove->left == NULL && nodeToRemove->right != NULL)
    {
                                                                               //       .O
        NodePtr tmp = nodeToRemove;                                            //         \         //
        nodeToRemove = nodeToRemove->right;
        delete tmp;
    }
    else if(nodeToRemove->left != NULL && nodeToRemove->right != NULL)         //        O
    {                                                                          //       / \         //

        NodePtr &tmp  = find_rightmost(nodeToRemove->left);
        nodeToRemove->value = tmp->value;
        nodeToRemove->key = tmp->key;
        remove_recursive(tmp);
    }
}

NodePtr &StringContactMap::find_rightmost(NodePtr &node)
{
    if(node->right == NULL)
    {
        return node;
    }
    else
    {
        return find_rightmost(node->right);
    }
}

bool StringContactMap::contains(string key)
{
    NodePtr &nodeToFind = find(root, key);

    if(nodeToFind == NULL)                                  //Koma í veg fyrir villu.
    {
        return false;
    }
    else
    {
        return (nodeToFind->key == key);
    }
}

Contact StringContactMap::get(string key)
{
    if(!contains(key))                                   //Villu meðhöndlun.
    {
        throw KeyException();
    }

    NodePtr &theNode = find(root, key);
    Contact theContact = theNode->value;

    return theContact;
}

vector<Contact> StringContactMap::prefix_search(string prefix) const
{
    vector<Contact> contacts;

    prefix_search(root, prefix, contacts);

    return contacts;
}

//Recurses poster-order through tree and deletes node after
//traversing through its left and right children respectively
//having already deleted its children, grandchildren etc.
void StringContactMap::free_memory(NodePtr node)
{
    if(node != NULL)
    {
        free_memory(node->left);
        free_memory(node->right);
        delete node;
    }

    treeSize = 0;
}

void StringContactMap::prefix_search(NodePtr node, string prefix, vector<Contact>& v) const
{
    if(node != NULL)
    {
        if(node->key[0] == prefix[0])                               //Ef fyrstu stafir eru eins.
        {
            bool match = true;

            for(size_t i = 0; i < prefix.size(); i++)               //Kannar hvort að
            {                                                       //fyrstu stafir lykils
                if(node->key[i] != prefix[i])                       //stemmi við Prefix.
                {
                    match = false;
                    break;
                }
            }

            prefix_search(node->left, prefix, v);                   //Kannar hvort það
                                                                    //séu fleiri, hægra
                                                                    //og og vinstra megin.
            if(match)                                               //Add-ar in-fix fyrir
            {                                                       //stafrófsröð.
                v.push_back(node->value);
            }
            prefix_search(node->right, prefix, v);
        }

        else if (prefix[0] < node->key[0])                  //Ef prefix er á undan key
        {                                                   //í stafrófinu, förum við til vinstri.
            prefix_search(node->left, prefix, v);
        }
        else if (prefix[0] > node->key[0])                  //Ef prefix er á eftir key
        {                                                   //í stafrófinu, förum við til hægri.
            prefix_search(node->right, prefix, v);
        }
    }
}

ostream& operator <<(ostream& out, StringContactMap& map)
{
    vector<Contact> contacts = map.all_contacts();

    for(size_t i = 0; i < contacts.size(); i++)
    {
        out << contacts[i] << endl;
    }
    return out;
}

NodePtr &StringContactMap::find(NodePtr &node, string key)
{
    if(node == NULL)                        //Key not found
    {
        return node;
    }
    else if(node->key == key)               //Key found
    {
        return node;
    }
    else if(key < node->key)                //Search left
    {
        return find(node->left, key);
    }
    else                                    //Search right
    {
        return find(node->right, key);
    }
}

void StringContactMap::printPreFix(NodePtr node)
{
    if(node == NULL)
    {
        return;
    }
    cout << node->value.name << " ";
    printPreFix(node->left);
    printPreFix(node->right);
}

void StringContactMap::printInFix(NodePtr node)
{
    if(node == NULL)
    {
        return;
    }
    printInFix(node->left);
    cout << node->value.name << " ";
    printInFix(node->right);
}

void StringContactMap::printPostFix(NodePtr node)
{
    if(node == NULL)
    {
        return;
    }
    printPostFix(node->left);
    printPostFix(node->right);
    cout << node->value.name << " ";
}
