#include <fstream>
#include <iostream>
#include <vector>
#include <stack>
#include <tuple>
#include <algorithm>

/*
Необходимо найти наибольший полупуть между вершинами разной высоты с минимальной суммой ключей крайних вершин.

Если таких полупутей несколько, то выбрать из них тот, у которого корневая вершина имеет наименьшее ключевое значение.

Удалить (правым удалением), если существует, среднюю по значению вершину этого полупути.

Если у вершины отсутствует некоторое поддерево, то его высоту полагаем равной −1.

Note
В случае неоднозначности выбора удаляемой вершины 
(например, несколько наибольших полупутей между вершинами разной высоты 
и с минимальной суммой ключей крайних вершин имеют один и тот же корень, 
но средние по значению вершины этих полупутей не совпадают) 
ничего из дерева удалять не нужно.

Input
Входной файл содержит последовательность чисел — ключи вершин в порядке добавления в дерево.
Output
Выходной файл должен содержать последовательность ключей вершин, полученную прямым левым обходом итогового дерева.

*/

#define TWOSUBTREES 0
#define ONESUBTREE 1
#define LEAF 1
#define RIGHT 1
#define LEFT 0
#define BOTH 2
#define START std::get<0>
#define ROOT  std::get<1>
#define END   std::get<2>

class BinaryTree {
public:
    struct Node;
    using path = std::tuple<Node*, Node*, Node*>;

    struct Node {
        Node(int _key)
            : key(_key)
            , r(nullptr)
            , l(nullptr)
            , h(0)
            , last(nullptr)
            , prev(nullptr)
            , parent(nullptr)
        {
        }
        int   key;
        Node* r;
        Node* l;
        int   h;
        Node* last;
        Node* prev;
        Node* parent;
    };

    BinaryTree()
        : root(0)
        , lpathRoot(nullptr)
        , maxLength(0)
        , minSum(0)
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
        Node* parent = nullptr;
        while (*curr) {
            Node& node = **curr;
            parent = *curr;
            if (info > node.key) {
                curr = &node.r;
            } else if (info < node.key) {
                curr = &node.l;
            } else {
                return;
            }
        }
        *curr = new Node(info);
        (*curr)->parent = parent;
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
        GetPaths(root);
        if(maxLength % 2 != 0)
            return;
        int deletable = GetMedianNode(START(paths.top()), ROOT(paths.top()), END(paths.top()));
        paths.pop();
        while(!paths.empty()) {
            if(GetMedianNode(START(paths.top()), ROOT(paths.top()), END(paths.top())) != deletable)
                return;
            paths.pop();
        }
        Delete(deletable);
    }

private:
    Node*            root;
    Node*            lpathRoot;           
    int              maxLength;
    int              minSum;
    std::stack<path> paths;
    std::vector<int> chunk;

    void GetPaths(Node* node) {
        if(!node)
            return;

        GetPaths(node->l);
        GetPaths(node->r);

        if(IsLeaf(node)) {
            node->prev = node->parent;
            node->last = node;
            node->h = 0;
        } else {
            if(node->r && node->l) {
                node->h = std::max(node->l->h, node->r->h) + 1;
                if(node->r->h > node->l->h) {
                    node->last = node->r->last;
                    node->prev = node->r->prev;
                } else if(node->r->h < node->l->h) {
                    node->last = node->l->last;
                    node->prev = node->l->prev;
                } else {
                    node->last = (node->r->last->key < node->l->last->key) ? node->r->last : node->l->last;
                    node->prev = (node->r->prev->key < node->l->prev->key) ? node->r->prev : node->l->prev;
                } 
                CalcPath(node, TWOSUBTREES, BOTH, !LEAF);
            } else if(node->r) {
                node->h = node->r->h + 1;
                node->last = node->r->last;
                node->prev = node->r->prev;
                CalcPath(node, ONESUBTREE, RIGHT, !LEAF);
            } else {
                node->h = node->l->h + 1;
                node->last = node->l->last;
                node->prev = node->l->prev;
                CalcPath(node, ONESUBTREE, LEFT, !LEAF);
            }
        }
    }

    void ClearStackPaths() {
        std::stack<path>().swap(paths);
    }

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
        os << node->key << '\n';
        PrintPreO(os, node->l);
        PrintPreO(os, node->r);
    }
    
    void CalcPath(Node* node, bool isOneSubTree, bool isRight, bool isLeaf) {
        Node* start(nullptr);
        Node* end(nullptr);
        Node* sec_start(nullptr);
        Node* sec_end(nullptr);
        int lengthCurr = 0, minSumCurr = 0;
        bool isTwoPaths = false;

        if(isLeaf) {
            lengthCurr = 0; 
        } else if(isOneSubTree) {
            start = node;
            if(isRight) {
                lengthCurr = node->r->h + 1;
                end = node->r->last;
            } else {
                lengthCurr = node->l->h + 1;
                end = node->l->last;
            }
        } else {
            lengthCurr = node->l->h + node->r->h + 1;
            if(node->r->prev->key + node->l->last->key < node->r->last->key + node->l->prev->key) {
                start = node->l->last; 
                end = node->r->prev;
            } else if(node->r->prev->key + node->l->last->key > node->r->last->key + node->l->prev->key) {
                start = node->l->prev;
                end = node->r->last; 
            } else {
                isTwoPaths = 1;
                start = node->l->prev;
                end = node->r->last;
                sec_start = node->l->last;
                sec_end = node->r->prev;
            }
        }

        minSumCurr = start->key + end->key;
        if(lengthCurr > maxLength) {
            maxLength = lengthCurr;
            minSum = minSumCurr;
            lpathRoot = node;
            ClearStackPaths();
            if(isTwoPaths) {
                paths.push({start, lpathRoot, end});
                paths.push({sec_start, lpathRoot, sec_end});
            } else {
                paths.push({start, lpathRoot, end});
            }
        } else if(lengthCurr == maxLength) {
            if(minSum > minSumCurr) {
                minSum = minSumCurr;
                lpathRoot = node;
                ClearStackPaths();
                if(isTwoPaths) {
                    paths.push({start, lpathRoot, end});
                    paths.push({sec_start, lpathRoot, sec_end});
                } else {
                    paths.push({start, lpathRoot, end});
                } 
            } else if(minSum == minSumCurr) {
                if(lpathRoot->key > node->key) {
                    lpathRoot = node;
                    ClearStackPaths();
                    if(isTwoPaths) {
                        paths.push({start, lpathRoot, end});
                        paths.push({sec_start, lpathRoot, sec_end});
                    } else {
                        paths.push({start, lpathRoot, end});
                    }  
                } else if(lpathRoot->key == node->key) {
                    if(isTwoPaths) {
                        paths.push({start, lpathRoot, end});
                        paths.push({sec_start, lpathRoot, sec_end});
                    } else {
                        paths.push({start, lpathRoot, end});
                    } 
                }
            }
        }
    }

    int GetMedianNode(Node* start, Node* root, Node* end) {
        Node* tmp_start = start;
        Node* tmp_end = end;
        chunk.clear();
        while(tmp_start != root) {
            chunk.push_back(tmp_start->key);
            tmp_start = tmp_start->parent;
        }
        chunk.push_back(root->key);
        while (tmp_end != root) {
            chunk.push_back(tmp_end->key);
            tmp_end = tmp_end->parent;
        }
        std::sort(chunk.begin(), chunk.end());
        //std::nth_element(chunk.begin(), chunk.begin() + chunk.size() / 2, chunk.end());
        return chunk[chunk.size() / 2];
    }
};

int main() {
    std::fstream fin("tst.in");
    std::ofstream fout("tst.out");
    BinaryTree tree;
    size_t c = 0;
    for(int data; fin >> data;) {
        tree.Insert(data);
        ++c;
    }
    if(c > 1)
        tree.solve();
    tree.PrintPreO(fout);
}
