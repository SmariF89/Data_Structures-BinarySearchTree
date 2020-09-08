# Data_Structures-BinarySearchTree
This is a contact book which is implemented using a binary search tree to keep track of the contacts.

The binary search tree (BST) allows for a quick retrieval of data using keys and binary recursive search. The implementation of the BST is located in the StringContactMap class, it uses the ContactNode struct for its nodes and the ContactNode struct uses the Contact struct as its value (data). 
The BST implements basic methods such as size, add, get, contains and remove. It also has a function which allows for a prefix search and it overloads the << operator.

The ContactManager class uses two instances of the StringContactMap to keep track of its contacts. One keyed by phone number and another keyed by name.
The InteractivePhoneBook class has an instance of the ContactManager class. It offers a console user interface which allows the user to interact with the ContactManager and, thus, the StringContactMap BST implementation.

The CSV files can be read into the ContactManager using the InteractivePhoneBook UI.
