

#include<bits/stdc++.h>
using namespace std;

struct Node
{
    int x;
    int balance;
    int height;
    struct Node *left ;
    struct Node *right;
};


class AVL
{
    struct Node *start;

    public:
    AVL(): start(0)
    {
    }
    
    Node* rotateL(Node* node) //for LL
    {
        cout<<"left rotating "<<node->x<<endl;
        Node* left = node->left; 
        Node* leftright = left->right;
        left->right = node;
        node->left = leftright;
        computeheight(node);
        computeheight(left);
        return left;
    }

    Node* rotateR(Node* node) //for RR
    {
        cout<<"right rotating"<<node->x<<endl;
        Node* right= node->right; 
        Node* rightleft = right->left;
        right->left = node;
        node->right = rightleft;
        computeheight(node);
        computeheight(right);
        return right;
    }

    
    Node* balance(Node *node)
    {
        int b = getbalance(node);
        if(b > 1)
        {
            Node* left = node->left;
            if(getbalance(left) > 0)//LL
            {
                return rotateL(node);
            }
            else //LR
            {
                node->left = rotateR(node->left);
                return rotateL(node);
            }
        }
        else if(b < -1)
        {
            Node* right = node->right;
            if(getbalance(right) < 0)//RR
            {
                return rotateR(node);
            }
            else //RL
            {
                node->right = rotateL(node->right);
                return rotateR(node);
            }
        }
    }

    void insert(int x)
    {
        if(start == NULL)
        {
            start = new Node();
            start->x = x;
            start->left = NULL;
            start->right = NULL;
            start->height = 1;
        }
        else
        {
            print();
            cout<<endl;
            start = insertAndBalance(x, start);
            cout<<"returned start: "<<start->x<<endl;
        }
    }

    int getheight(Node* node)
    {
        if(node == NULL) return 0;
        else return node->height;
    }
    
    void computeheight(Node* node)
    {
        if(node != NULL) node->height = max(getheight(node->left),
                getheight(node->right)) + 1;
    }

    int getbalance(Node *node)
    {
        if(node == NULL) return 0;
        int l = getheight(node->left);
        int r = getheight(node->right);
        int b = l-r;
        return b;
    }
    /* Working */
    Node* insertAndBalance(int x, Node *node)
    {
        if(x < node-> x)
        {
            Node* left = node->left;
            if(left == NULL)
            {
               cout<<"Inserting at left of "<<node->x<<endl;
               node->left = new Node(); 
               node->left->x = x;
               node->left->left = NULL;
               node->left->right = NULL;
               node->left->height = 1;

               node->height = max(getheight(node->left),getheight(node->right)) + 1;
               return node;
            }
            else
            {
                node->left = insertAndBalance(x, node->left);
                node->height = max(getheight(node->left),getheight(node->right)) + 1;
                node = balance(node);
                return node;
            }
        }
        else if(x > node->x)
        {
            Node* right = node->right;
            if(right == NULL)
            {
                cout<<"Inserting at right of "<<node->x<<endl;
               node->right = new Node(); 
               node->right->x = x;
               node->right->left = NULL;
               node->right->right = NULL;
               node->right->height = 1;

               node->height = max(getheight(node->left),getheight(node->right)) + 1;
               return node;
            }
            else
            {
                node->right = insertAndBalance(x, node->right);
                node->height = max(getheight(node->left),getheight(node->right)) + 1;
                node = balance(node);
                return node;
            }
        }
        else if(x == node->x)
        {
            throw std::invalid_argument("value already present in tree");
        }
    }

    void print()
    {
        printUtil(start);
    }

    void printUtil(Node *node)
    {
        if(node != NULL)
        {
            printUtil(node->left);
            cout<<node->x<<":"<<node->height<<" ";
            printUtil(node->right);
        }
    }
};
int main()
{
    AVL avl;

    avl.insert(1);
    avl.insert(2);
    avl.insert(3);
    avl.insert(4);
    avl.print();
    
}





