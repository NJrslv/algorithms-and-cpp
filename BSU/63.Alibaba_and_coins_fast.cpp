#include <vector>
#include <iostream>
#include <cmath>
#include <fstream>

/*
На дороге в некоторых местах разбросаны золотые монеты. 
Для каждой монеты известно её местоположение, 
которое задается одним целым числом — расстоянием в метрах от начальной отметки. 
Все монеты расположены правее начальной отметки на различном расстоянии от начала. 
Али-баба бегает по дороге и собирает монеты, начиная делать это в момент времени 0. 
За одну секунду он пробегает ровно один метр. У каждой монеты есть крайний срок, 
до которого её нужно подобрать, иначе монета исчезнет. Али-баба должен собрать 
все монеты и сделать это за минимально возможное время. 
Он может стартовать в любой точке на прямой, собирать монеты в произвольном порядке, 
но обязательно должен успеть собрать все монеты и минимизировать затраченное на это время.

Input:
В первой строке которого задано целое число n монет (1 ≤ n ≤ 10 000). 
В каждой из последующих n строк содержатся по два целых числа d и t, 
первое из которых задаёт положение монеты (1 ≤ d ≤ 10 000), 
а второе — крайний срок в секундах (1 ≤ t ≤ 10 000), 
до которого нужно успеть собрать эту монету (в момент времени ровно t подобрать монету также возможно). 
Монеты перечислены в порядке возрастания расстояния от начала (слева направо).

Output:
Выведите единственное число — минимальное время, за которое Али-баба может собрать все монеты. 
Если Али-баба не может собрать все монеты — выведите строку No solution.
*/

#define dist first
#define time second
#define index(i, j, n) ((i) * (n) + (j))
#define add(a, b) ((a == INT_MAX || b == INT_MAX) ? INT_MAX : a + b)


using coin = std::pair<int, int>;

coin in[10000];


inline int dist(const coin& cstart, const coin& cend, int prev_time) {
    int d = std::abs(cend.dist - cstart.dist);
    return prev_time == INT_MAX ? INT_MAX
                           : cend.time - prev_time - d >= 0 ? d
                                                            : INT_MAX;
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");
    size_t n;
    fin >> n;
    for(size_t i = 0; i < n; ++i)
        fin >> in[i].dist >> in[i].time;
    std::vector<int> dp(n * n, 0);
    for (size_t i = n - 2; i != (size_t)-1; --i) {
        for (size_t j = i + 1; j < n; ++j) {
            dp[index(i, j, n)] = std::min(add(dp[index(i, j - 1, n)], dist(in[j - 1], in[j], dp[index(i, j - 1, n)])),
                                      add(dp[index(j - 1, i, n)], dist(in[i], in[j], dp[index(j - 1, i, n)])));
            dp[index(j, i, n)] = std::min(add(dp[index(i + 1, j, n)], dist(in[j], in[i], dp[index(i + 1, j, n)])),
                                      add(dp[index(j, i + 1, n)], dist(in[i + 1], in[i], dp[index(j, i + 1, n)])));
        }
    }
    int res = std::min(dp[index(0, n - 1, n)], dp[index(n - 1, 0, n)]);
    res == INT_MAX ? fout << "No solution" : fout << res;
}