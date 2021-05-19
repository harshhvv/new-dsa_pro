//avl tree project
//self balancing tree for a grocery store with items and rates

// NAME: Harsh Vardhan
// REGISTARTION NUMBER: 20BCE2266
// CSE-2011

#include <iostream>
#include <string>

struct node
{
    int code;         //serial code of product
    int val;          //rate of the product
    int balance;      //height balance variable
    node *left;       //pointing to left sub-tree
    node *right;      //pointing to right sub-tree
    std::string item; //name of the item

    //rough diagram of structure of the node
    //  __________________________________________
    //  |         |      |      |      |         |
    //  | pointer | item | rate | code | pointer |
    //  |         |      |      |      |         |
    //  ------------------------------------------
    //
};

//recursive function to search for data (product code in this case)
node *search(node *ptr, int data)
{
    if (ptr != NULL)
    {
        if (data < ptr->val)
            ptr = search(ptr->left, data);
        else if (data > ptr->val)
            ptr = search(ptr->right, data);
    }
    return ptr;
}

node *insert(std::string name, int code, int data, node *ptr, bool *ht_inc)
{
    //two temporary variables
    node *aptr;
    node *bptr;
    if (ptr == NULL)
    {
        ptr = new node;
        ptr->left = NULL;
        ptr->item = name;
        ptr->val = data;
        ptr->code = code;
        ptr->right = NULL;

        ptr->balance = 0;
        *ht_inc = true; //height of tree will increase since we're adding a new node
        return ptr;
    }

    // when data is less than the value of data in the left node
    if (data < ptr->val)
    {
        //inserts new node in left leaf
        ptr->left = insert(name, code, data, ptr->left, ht_inc);
        if (*ht_inc == true)
        {
            switch (ptr->balance)
            {
            //value may be -1, 1 or 0 depending if it's right heavy, left heavy or balanced avl tree
            case -1: //right heavy
                ptr->balance = 0;
                *ht_inc = false;
                break;

            case 0: // balanced
                ptr->balance = 0;
                break;

            case 1: //left heavy
                aptr = ptr->left;
                if (aptr->balance == 1)
                {
                    //piece will perform LL rotation of sub-tree
                    ptr->left = aptr->right;
                    aptr->right = ptr;
                    ptr->balance = 0;
                    aptr->balance = 0;
                    ptr = aptr;
                }
                else
                {
                    //piece will perform LR rotation of sub-tree
                    bptr = aptr->right;
                    aptr->right = bptr->left;
                    bptr->left = aptr;
                    ptr->left = bptr->right;
                    bptr->right = ptr;
                    if (bptr->balance == 1)
                        ptr->balance = -1;
                    else
                        ptr->balance = 0;

                    if (bptr->balance == -1)
                        aptr->balance = 1;
                    else
                        aptr->balance = 0;
                    bptr->balance = 0;
                    ptr = bptr;
                }
                *ht_inc = false; //false after we have finished adding the node
            }
        }
    }

    if (data > ptr->val)
    {
        ptr->right = insert(name, code, data, ptr->right, ht_inc);
        if (*ht_inc == true)
        {
            switch (ptr->balance)
            {
            case 1: //left heavy
                ptr->balance = 0;
                *ht_inc = false;
                break;

            case 0: //balanced
                ptr->balance = -1;
                break;

            case -1: //right heavy
                aptr = ptr->right;
                if (aptr->balance == -1)
                {
                    //this piece will perform RR rotation of tree
                    ptr->right = aptr->left;
                    aptr->left = ptr;
                    ptr->balance = 0;
                    aptr->balance = 0;
                    ptr = aptr;
                }
                else
                {
                    //this piece will perform right to left rotation
                    bptr = aptr->left;
                    aptr->left = bptr->right;
                    bptr->right = aptr;
                    ptr->right = bptr->left;
                    bptr->left = ptr;
                    if (bptr->balance == -1)
                        ptr->balance = 1;
                    else
                        ptr->balance = 0;

                    if (bptr->balance == 1)
                        aptr->balance = -1;
                    else
                        aptr->balance = 0;
                    bptr->balance = 0;
                    ptr = bptr;
                }
                *ht_inc = false; //false after we have finished adding the node
            }
        }
    }
    return ptr;
}

//function to display the items in avl tree
//Items displayed from high to low are:
void display(node *ptr, int level)
{
    if (ptr != NULL)
    {
        display(ptr->right, level + 1);
        std::cout << std::endl;
        for (int i = 0; i < level; i++)
            std::cout << " ";
        std::cout << "Item: " << ptr->item << ", Rate: " << ptr->val << ", Code: " << ptr->code << std::endl;
        std::cout << " ";
        display(ptr->left, level + 1);
    }
}

//Items are printed from low to high
void inorder(node *ptr)
{
    if (ptr != NULL)
    {
        inorder(ptr->left);
        std::cout << "  ";
        std::cout << "Item: " << ptr->item << ", Rate: " << ptr->val << ", Code: " << ptr->code << std::endl;
        inorder(ptr->right);
    }
}

int main()
{
    bool ht_inc;           //to keep track if height increase is true or not
    int code;              //serial code of node
    int data;              //the rate/value of node
    std::string name;      //name of the node(item)
    int option;            //keeps track of choice entered by user while running the program
    node *root = new node; //variable of type node
    root = NULL;           //initial value is given as NULL

    while (true) //always executed
    {
        std::cout << std::endl;
        std::cout << "1. Insert\n";
        std::cout << "2. Display\n";
        std::cout << "3. Quit\n";
        std::cout << "Enter your option pls: ";
        std::cin >> option;
        std::cout << std::endl;
        switch (option)
        {
        case 1: //insertion of new node
            std::cout << "Enter name of new item: ";
            std::cin >> name;
            std::cout << "enter rate of " << name << ": ";
            std::cin >> data;
            std::cout << "enter serial code of " << name << ": ";
            std::cin >> code;

            //first searches if a node with same serial code already exists or not and if not then you can insert a new node
            if (search(root, code) == NULL)
            {
                root = insert(name, code, data, root, &ht_inc);
            }
            else
                std::cout << "item with serial code " << code << " already exists\n";
            break;

        case 2: //displaying of all nodes
            if (root == NULL)
            {
                std::cout << "No items at the moment. Sorry \n";
                continue;
            }

            std::cout << "Items filtered from high to low are:: \n";
            display(root, 1);
            std::cout << "\n\n";

            std::cout << "Items filtered from low to high are:\n";
            inorder(root);
            std::cout << "\n";
            break;

        case 3: //exiting from program
            exit(1);

        default:
            std::cout << "Please enter a valid option\n\n";
        }
    }
}
