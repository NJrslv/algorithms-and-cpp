#include <iostream>
#include <vector>
#include <unordered_map>
#include <cmath>

std::string get_word(std::vector<int32_t>& w, std::unordered_map<size_t,char>& alphabet);
size_t get_diff_bit(int32_t l, int32_t r);
void fill_alphabet(std::unordered_map<size_t,char>& alphabet);

int main(){
    size_t n;
    std::cin>>n;
    std::vector<int32_t> in(n);
    for(auto &w: in) std::cin>>w;

    std::unordered_map<size_t,char> alphabet;
    fill_alphabet(alphabet);

    std::cout<<get_word(in, alphabet);
}


std::string get_word(std::vector<int32_t>& w, std::unordered_map<size_t,char>& alphabet){
    std::string word;
    int32_t prev = 0;
    int32_t next;
    for(size_t i = 0; i < w.size(); ++i){
        next= w[i];
        word.push_back(alphabet[get_diff_bit(prev,next)]);
        prev = next;
    }   
    return word; 
}


void fill_alphabet(std::unordered_map<size_t,char>& alphabet){
    for(int bit = 0; bit <= 25; ++bit){
        alphabet[bit] = char(bit + 97);
    }
    alphabet[26] = ' ';
}

size_t get_diff_bit(int32_t l, int32_t r){
    return std::log2(l ^ r);
}
