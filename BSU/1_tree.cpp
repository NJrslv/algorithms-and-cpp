#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <set>

class BinaryTree {
public:
    struct Node {
        Node(int _key)
            : key(_key)
            , r(nullptr)
            , l(nullptr)
            , count(0)
        {
        }
        int   key;
        Node* r;
        Node* l;
        int count;
    };

    BinaryTree()
        : root(0)
    {
    }

    ~BinaryTree() {
        Erase(root);
    }

    void Erase(Node* node) {
        if(node) {
            Erase(node->l);
            Erase(node->r);
            delete node;
        }
    }

    void PrintPreO(std::ostream& os) const {
        PrintPreO(os, root);
    }

    void Insert(int info) {
        Node** curr = &root;
        while(*curr) {
            Node& node = **curr;
            if(info > node.key) {
                curr = &node.r;
            } else if(info < node.key) {
                curr = &node.l;
            } else {
                return;
            }
        }
        *curr = new Node(info);
    }

    bool Delete(int x) {
        Node** pp = &root;
        Node* p = root;
        while (p) {
            if (x < p->key) {
                pp = &p->l;
                p = p->l;
            } else if (x > p->key) {
                pp = &p->r;
                p = p->r;
            } else {
                break;
            }
        }
        if (!p) {
            return false;
        } else if (!HasTwoSons(p)) {
            DeleteLE1Sons(pp, p);
        } else {
            Node** ppmin = &p->r;
            Node* pmin = p->r;
            while (pmin->l) {
                ppmin = &pmin->l;
                pmin = pmin->l;
            }
            p->key = pmin->key;
            DeleteLE1Sons(ppmin, pmin);
        }
        return true;
    }

    void solve() {
        CheckNodes(root);
        if(nodesIn.empty() || nodesIn.size() % 2 == 0)
            return;
        std::sort(nodesIn.begin(), nodesIn.end());
        Delete(nodesIn[nodesIn.size() / 2]);
    } 

private:
    Node* root;
    std::vector<int> nodesIn;

    bool IsPreLeaf(Node* node) {
        return  (IsLeaf(node->r) || IsLeaf(node->l)); 
    }

    bool HasTwoSons(Node* node) {
        return (node->l != nullptr && node->r != nullptr);
    }

    void DeleteLE1Sons(Node** parent, Node* deletable) {
        *parent = deletable->l ? deletable->l : deletable->r;
        delete deletable;
    }

    bool IsLeaf(Node* node) {
        return (node && !node->l && !node->r) ? true : false;
    }

    void PrintPreO(std::ostream& os, Node* node) const {
        if(!node)
            return;
        os << node->key << "\n";
        PrintPreO(os, node->l);
        PrintPreO(os, node->r);
    }

    void CheckNodes(Node* node) {
        if(!node)
            return;
        CheckNodes(node->l);
        CheckNodes(node->r);

        if(IsLeaf(node)) {
            node->count = 1;
        } else if(node->l && node->r) {
            node->count = node->l->count + node->r->count + 1;
            if(node->l->count != node->r->count) nodesIn.push_back(node->key);
        } else if(node->r) {
            node->count = node->r->count + 1;
            nodesIn.push_back(node->key);
        } else {
            node->count = node->l->count + 1;
            nodesIn.push_back(node->key);
        }
    }
};

int main() {
    std::ios_base::sync_with_stdio(0);
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    std::cin.tie(0);
    std::cout.tie(0);
    BinaryTree tree;
    for(int data; std::cin >> data;)
        tree.Insert(data);
    tree.solve();
    tree.PrintPreO(std::cout);
}


