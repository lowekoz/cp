#include <iostream>

using namespace std;

template<typename T>
struct node
{
    T data;
    node* left;
    node* right;
    //node<T>* parent;
};

template<typename T>
class Tree: public node<T>
{
private:
    node<T>* root = nullptr;

public:
    Tree(): root{nullptr}{};
    ~Tree(){
        destroyTree(root);
    };

    void destroyTree(node<T>* leaf)
    {
        if(leaf != nullptr)
        {
            destroyTree(leaf->left);
            destroyTree(leaf->right);
            delete leaf;
        }
    }

    void insertRec(node<T>* leaf, T data)
    {
        if(data < leaf->data)
        {
            if(leaf->left != nullptr)
            {
                insertRec(leaf->left, data);
            }else
            {
                leaf->left = new node<T>;
                leaf->left->data = data;
                leaf->left->left = nullptr;
                leaf->left->right = nullptr;
            }
        }else if(data >= leaf->data)
        {
            if(leaf->right != nullptr)
            {
                insertRec(leaf->right, data);
            }else
            {
                leaf->right = new node<T>;
                leaf->right->data = data;
                leaf->right->left = nullptr;
                leaf->right->right = nullptr;
            }
        }
    }

    void insertnode(T data)
    {
        if(root != nullptr)
        {
            insertRec(root, data);
        }else
        {
            node<T>* temp = new node<T>;
            root = temp;
            root->data = data;
            root->left = nullptr;
            root->right = nullptr;
        }
    }

    void printTree(node<T>* leaf)
    {
        if(leaf == nullptr)
        {
            return;
        }else
        {
            printTree(leaf->left);
            cout << leaf->data << " ";
            printTree(leaf->right);
        }
    }

    void printTree()
    {
        printTree(root);
    }

    node<T>* search(node<T>* leaf, T key)
    {
        if(leaf != nullptr)
        {
            if(key == leaf->data)
            {
                cout <<"node<T> found: " << leaf->data << endl;
                return leaf;
            }else if(key < leaf->data)
            {
                search(leaf->left, key);
            }else
            {
                search(leaf->right, key);
            }
        }else
        {
            cout << "node<T> not found." << endl;
            return nullptr;
        }
    }

    node<T>* search(T key)
    {
        return search(root, key);
    }


};

int main()
{

    Tree<int> tree; // OBS - declare correct type

    tree.insertnode(10);
    tree.insertnode(9);
    tree.insertnode(5);
    tree.insertnode(7);
    tree.insertnode(20);
    tree.insertnode(1);
    tree.insertnode(19);
    tree.insertnode(21);


    tree.printTree();
    tree.search(5);
    tree.search(100);

}