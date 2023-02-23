#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>

int64_t levenshtein_distance(std::string &str1, std::string &str2,
                             int64_t del, int64_t ins, int64_t rep) {
    size_t len1 = str1.size();
    size_t len2 = str2.size();
    std::vector<std::vector<int64_t>> d(len1+1, std::vector<int64_t>(len2+1));
    for(int i = 0; i <= len1; ++i) d[i][0] = i * del;   
    for(int i = 0; i <= len2; ++i) d[0][i] = i * ins; 
    for(int i = 1; i <= len1; ++i){
        for(int j = 1; j <= len2; ++j){
            int64_t remove_cost = d[i-1][j] + del;
            int64_t insert_cost = d[i][j-1] + ins;
            int64_t replace_cost = d[i-1][j-1] + (!(str1[i-1] == str2[j-1]) * rep);
            d[i][j] = std::min(std::min(remove_cost,insert_cost),replace_cost);
        }
    }
    return d[str1.size()][str2.size()];                             
}

int main(void) {
    std::ifstream fin("in.txt");
    std::ofstream fout("out.txt");
    int64_t d, i, r;
    std::string str1;
    std::string str2;
    fin >> d >> i >> r >> str1 >> str2;  
    fout << levenshtein_distance(str1, str2, d, i, r);
}
