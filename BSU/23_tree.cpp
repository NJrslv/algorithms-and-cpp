#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <set>

/*
Найти все вершины, через которые проходят полупути длины K между висячими вершинами.
Выбрать те, которые находятся на наименьшей глубине, и удалить (левым удалением) 
из них среднюю по значению, если она существует.
Input:
Входной файл содержит в первой строке число K (2 ≤ K ≤ 109),
а в последующих строках — последовательность чисел — ключи вершин в порядке добавления в дерево.
Output:
Выходной файл должен содержать последовательность ключей вершин,
 полученную прямым левым обходом итогового дерева.
*/

class BinaryTree {
public:
    using setHeights = std::set<int>;
    
    struct Node {
        Node(int _key)
            : key(_key)
            , r(nullptr)
            , l(nullptr)
            , isIn(false)
            , h(0)
            , depth(0)
        {
        }
        int   key;
        Node* r;
        Node* l;
        bool  isIn;
        setHeights setH;
        int h;
        int depth;
    };

    BinaryTree(int _k)
        : root(0)
        , k(_k)
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
        while(p) {
            if(x < p->key) {
                pp = &p->l;
                p = p->l;
            } else if(x > p->key) {
                pp = &p->r;
                p = p->r;
            } else {
                break;
            }
        }
        if(!p) {
            return false;
        } else if(!HasTwoSons(p)) {
            DeleteLE1Sons(pp, p);
        } else {
            pp = &p->l;
            Node* pmin = p->l;
            while (pmin->r) {
                pp = &pmin->r; 
                pmin = pmin->r; 
            }
            p->key = pmin->key;
            DeleteLE1Sons(pp, pmin);
        }
        return true;
    }

    void solve() {
        CheckNodes(root);
        FillDepth(root, 0);
        BFS();
        if(nodesIn.empty() || nodesIn.size() % 2 == 0)
            return;
        std::sort(nodesIn.begin(), nodesIn.end());
        Delete(nodesIn[nodesIn.size() / 2]);
    } 

private:
    Node* root;
    int k;
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

    void FillDepth(Node* node, int depth) {
        if (!node) 
            return;
        node->depth = depth;
        FillDepth(node->l, depth + 1);
        FillDepth(node->r, depth + 1);
    }

    void CheckNodes(Node* node) {
        if(!node)
            return;
        CheckNodes(node->l);
        CheckNodes(node->r);

        if(IsLeaf(node)) {
            node->h = 0;
            node->setH.insert(0);
        } else if(node->l && node->r) {
            node->h = std::max(node->l->h, node->r->h) + 1;
            for(auto &fH: node->l->setH)
                node->setH.insert(fH + 1);
            for(auto &sH: node->r->setH)
                node->setH.insert(sH + 1);

            for(auto &fH: node->l->setH) {
                if(node->r->setH.find(k - fH - 2) != node->r->setH.end()) {
                    node->isIn = true;
                    break;
                }
            }
            //auto itL = node->l->setH.begin();
            //auto itR = node->r->setH.rbegin();
            //while(itL != node->l->setH.end() && itR != node->r->setH.rend()) {
                //if(*itL + *itR + 2 == k) {
                    //node->isIn = true;
                    //break;
                //} else if(*itL + *itR < k) {
                    //++itR;
                //} else {
                    //++itL;
                //}
            //}
        } else if(node->r) {
            node->h = node->r->h + 1;
            for(auto &h: node->r->setH)
                node->setH.insert(h + 1);
        } else {
            node->h = node->l->h + 1;
            for(auto &h: node->l->setH)
                node->setH.insert(h + 1);
        }
    }

    void BFS() {
        if (root == nullptr)
            return;

        int global_depth = 0;
        bool first_time = true;
        std::queue<Node*> q;

        q.push(root);
        while (!q.empty()) {
            Node* node = q.front();

            if(node->isIn) {
                if(!first_time && (node->depth != global_depth))
                    break;
                global_depth = node->depth;
                nodesIn.push_back(node->key);
                first_time = false;
            }

            q.pop();
            if (node->l)
                q.push(node->l);
            if (node->r)
                q.push(node->r);
        }
    }
};

int main() {
    std::ios_base::sync_with_stdio(0);
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    std::cin.tie(0);
    std::cout.tie(0);
    int k;
    std::cin >> k;
    BinaryTree tree(k);
    for(int data; std::cin >> data;)
        tree.Insert(data);
    tree.solve();
    tree.PrintPreO(std::cout);
}


