#include <iostream>
#include <vector>
#include <queue>
#include <limits>

const int64_t INF = std::numeric_limits<int64_t>::max();

class Dinic {
public:
    explicit Dinic(int n) : n_(n), graph_(n), level_(n), was_(n) {}

    void add_edge(int from, int to, int64_t capacity) {
        graph_[from].emplace_back(to, capacity, graph_[to].size());
        graph_[to].emplace_back(from, 0, graph_[from].size() - 1);
    }

    int64_t max_flow(int source, int sink) {

        //      ***
        // Explanation max_flow
        // Кратко:
        // 1. Строим остаточную сеть
        // 2. Стром по остаточной слоистую сеть
        // 3. Ищем путь у которого каждое ребро насыщено потоком (блокирующий)
        // 4. Пока находится блокирующий путь (delta > 0) мы можем увеличить поток
        // 
        // Описание кода:
        // Пока есть путь от истока в сток в остаточной сети 
        // (Почему так - check prove теоремы Форда-Фалкерсона)
        // Ищем блокирующий поток и прибавляем к 'глобальному потоку' (flow)
        //      ***

        int64_t flow = 0;
        while (bfs(source, sink)) {
            std::fill(was_.begin(), was_.end(), 0);
            while (auto delta = dfs(source, sink, INF)) {
                 flow += delta;
            }
        }
        return flow;
    }

private:
    struct Edge {
        int to;
        int64_t capacity;
        int rev;
        Edge(int to, int64_t capacity, int rev) : to(to), capacity(capacity), rev(rev) {}
    };

    int n_;
    std::vector<std::vector<Edge>> graph_;
    std::vector<int> level_;
    std::vector<size_t> was_;

    bool bfs(int source, int sink) {

        //      ***
        // Explanation bfs:
        // 1) Устанавливаем уровень исходной вершины равным 0
        // 2) Для каждой вершины в порядке bfs делаем следующее:
        //    2.1) Проходим по всем ребрам, исходящим из текущей вершины
        //    2.2) Если вершина, в которую ведет ребро, еще не была рассмотрена (её уровень -1),
        //         и её пропускная способность положительна, 
        //         иначе ребро блокировано и по нему не может протекать ЖИЖА, то делаем след.:
        //         + Устанавливаем уровень текущей вершины равным уровню предыдущей вершины + 1
        //         + добавляем ее в очередь для дальнейшего рассмотрения
        // 3) Если мы добрались до последней вершины то понятно что мы дошли до нее bfs-ом
        //    тогда мы вернем true если мы дошли до нее
        //      ***

        std::fill(level_.begin(), level_.end(), -1);
        std::queue<int> q;
        level_[source] = 0;
        q.push(source);
        while (!q.empty()) {
            auto u = q.front();
            q.pop();
            for (const auto& edge : graph_[u]) {
                if (level_[edge.to] < 0 && edge.capacity > 0) {
                    level_[edge.to] = level_[u] + 1;
                    q.push(edge.to);
                }
            }
        }
        return level_[sink] >= 0;
    }

    int64_t dfs(int u, int sink, int64_t flow) {

        //      ***
        // Explanation dfs:
        // Замечание 1. (По вектору was_)
        // Этот массив необходим для того, чтобы при каждом запуске функции dfs()
        // мы начинали просмотр рёбер графа с того места, где остановились в предыдущий раз.
        // => Берем по ссылке.
        //
        // 1) Будем итерироваться по ребрам исходящим из текущей вершины u
        // 2) Найдем такое ребро, которое ведет в вершину, уровень которой на единицу больше, 
        //    чем уровень текущей вершины u, 
        //    и что у этого ребра положительная остаточная пропускная способность.
        // 3) Запустимся рекурсивно из найденной вершины и на выхоже из рекурсии запомним значание delta
        //    Далее увеличиваем на delta поток и уменьшаем на delta обратное ребро
        //      ***

        if (u == sink) return flow;
        for (auto& i = was_[u]; i < graph_[u].size(); ++i) {
            Edge& edge = graph_[u][i];
            if (level_[edge.to] == level_[u] + 1 && edge.capacity > 0) {
                auto delta = dfs(edge.to, sink, std::min(flow, edge.capacity));
                if (delta > 0) {
                    // При выполнении операции увеличения потока по ребру u->v 
                    // мы уменьшаем его оставшуюся пропускную способность на значение delta
                    // и увеличиваем пропускную способность обратного ребра v->u, соответствующего ребру u->v
                    edge.capacity -= delta;
                    graph_[edge.to][edge.rev].capacity += delta;
                    return delta;
                }
            }
        }
        return 0;
    }
};


int main() {
    int n, m;
    std::cin >> n >> m;
    Dinic dinic(n);
    for (int i = 0; i < m; ++i) {
        int from, to, capacity;
        std::cin >> from >> to >> capacity;
        dinic.add_edge(from - 1, to - 1, capacity);
    }
    int max_flow = dinic.max_flow(0, n - 1);
    std::cout << max_flow << '\n';
    return 0;
}