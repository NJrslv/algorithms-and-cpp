#include <fstream>

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
private:
    Node* root;
};

int main() {
    std::fstream fin("input.txt");
    std::ofstream fout("output.txt");
    BinaryTree tree;
    for(int data; fin >> data;)
        tree.Insert(data);
    tree.PrintPreO(fout);
}