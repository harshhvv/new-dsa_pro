//avl tree project
//self balancing tree for a grocery store with items and rates
//searching by price i suppose
//sorts salaries according to bst

// NAME: Harsh Vardhan
// REGISTARTION NUMBER: 20BCE2266
// CSE-2011

#include <iostream>

struct node
{
    int code;    //serial code of product
    int val;     //rate of the product
    int balance; //height balance variable
    node *left;
    node *right;
    std::string item; //name of the item
    //  __________________________________________
    //  |         |      |      |      |         |
    //  | pointer | item | rate | code | pointer |
    //  |         |      |      |      |         |
    //  ------------------------------------------
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
    node *aptr;
    node *bptr;
    if (ptr == NULL)
    {
        ptr = new node;
        ptr->val = data;
        ptr->item = name;
        ptr->code = code;
        ptr->left = NULL;
        ptr->right = NULL;
        ptr->balance = 0;
        *ht_inc = true;
        return ptr;
    }

    if (data < ptr->val)
    {
        ptr->left = insert(name, code, data, ptr->left, ht_inc);
        if (*ht_inc == true)
        {
            switch (ptr->balance)
            {

            case -1: //right heavy
                ptr->balance = 0;
                *ht_inc = false;
                break;

            case 0: // balancedy
                ptr->balance = 0;
                break;

            case 1: //left heavy
                aptr = ptr->left;
                if (aptr->balance == 1)
                {
                    std::cout << "left to left rotation\n";
                    ptr->left = aptr->right;
                    aptr->right = ptr;
                    ptr->balance = 0;
                    aptr->balance = 0;
                    ptr = aptr;
                }
                else
                {
                    std::cout << "left to right rotation\n";
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
                *ht_inc = false;
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
                    std::cout << "right to roght rotation \n";
                    ptr->right = aptr->left;
                    aptr->left = ptr;
                    ptr->balance = 0;
                    aptr->balance = 0;
                    ptr = aptr;
                }
                else
                {
                    std::cout << "right to left rotation\n";
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
                    //end of else
                }
                *ht_inc = false;
            }
        }
    }
    return ptr;
}

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

//function to print
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
    bool ht_inc;
    int code;
    int data;
    std::string name;
    int option;
    node *root = new node;
    root = NULL;
    while (true)
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
        case 1:
            std::cout << "Enter name of new item: ";
            std::cin >> name;
            std::cout << "enter rate of " << name << ": ";
            std::cin >> data;
            std::cout << "enter serial code of " << name << ": ";
            std::cin >> code;
            if (search(root, code) == NULL)
            {
                root = insert(name, code, data, root, &ht_inc);
            }
            else
                std::cout << "iteam with serial code " << code << " already exists\n";
            break;

        case 2:
            if (root == NULL)
            {
                std::cout << "No items at the moment. Sorry \n";
                continue;
            }
            std::cout << "Items filtered from high to low are:: \n";
            display(root, 1);
            std::cout << "\n\n";
            //std::cout << "inorder traversal is as dollows: \n";
            std::cout << "Items filtered from low to high are:\n";
            inorder(root);
            std::cout << "\n";
            break;

        case 3:
            exit(1);

        default:
            std::cout << "Please enter a valid option\n\n";
        }
    }
}