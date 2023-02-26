#include <fstream>
#include <iostream>

struct Node {
    Node(int _key)
        : key(_key)
        , right(nullptr)
        , left(nullptr)
    {
    }

    int   key;
    Node* right;
    Node* left;
};

class BinaryTree {
public:
    BinaryTree()
        : root(0)
    {
    }

    ~BinaryTree() {
        Erase(root);
    }

    void Erase(Node* node) {
        if(node) {
            Erase(node->left);
            Erase(node->right);
            delete node;
        }
    }

    void PrintPreO(std::ostream& os) const {
        PrintPreO(os, root);
    }

    void PrintPreO(std::ostream& os, Node* node) const {
        if(!node)
            return;
        os << node->key <<"\n";
        PrintPreO(os, node->left);
        PrintPreO(os, node->right);
    }

    void Insert(int info) {
        Node** curr = &root;
        while(*curr) {
            Node& node = **curr;
            if(info > node.key) {
                curr = &node.right;
            } else if(info < node.key) {
                curr = &node.left;
            } else {
                return;
            }
        }
        *curr = new Node(info);
    }

    bool IsLeaf(Node* node) {
        return (node && !node->left && !node->right) ? true : false;
    }

    bool HasTwoSons(Node* node) {
        return (node->left != nullptr && node->right != nullptr);
    }

    void DeleteLE1Sons(Node** parent, Node* deletable) {
        *parent = deletable->left ? deletable->left : deletable->right;
        delete deletable;
    }

    bool Delete(int x) {
        Node** pp = &root;
        Node* p = root;
        while(p) {
            if(x < p->key) {
                pp = &p->left;
                p = p->left;
            } else if(x > p->key) {
                pp = &p->right;
                p = p->right;
            } else {
                break;
            }
        }
        if(!p) {
            return false;
        } else if(!HasTwoSons(p)) {
            DeleteLE1Sons(pp, p);
        } else {
            pp = &p->right;
            Node* pmin = p->right;
            while (pmin->left) {
                pp = &pmin->left; 
                pmin = pmin->left; 
            }
            p->key = pmin->key;
            DeleteLE1Sons(pp, pmin);
        }
        return true;
    }
private:
    Node* root;
};

int main() {
    std::fstream fin("input.txt");
    std::ofstream fout("output.txt");
    BinaryTree tree;
    int val_to_delete;
    fin >> val_to_delete;
    for(int data; fin >> data;)
        tree.Insert(data);
    tree.Delete(val_to_delete);
    tree.PrintPreO(fout);
}