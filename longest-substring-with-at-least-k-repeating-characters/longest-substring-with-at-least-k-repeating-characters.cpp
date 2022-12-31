// https://leetcode.com/problems/longest-substring-with-at-least-k-repeating-characters/description/

#include <limits>
#include <string>
#include <unordered_set>
#include <vector>
#include <algorithm>
using std::max;
using std::vector;
using std::string;
using std::unordered_set;

class Solution {
public:
  int longestSubstring(string s, int num_aparicao) {
    int tam = s.size();
    if (num_aparicao < 1 || tam < num_aparicao) return 0;
    else if (num_aparicao == 1) return tam;
    vector<vector<int>> indices_char(26, vector<int>());
    vector<int> intervalo_valido(tam, std::numeric_limits<int>::max());
    for (int i = 0; i < tam; ++i) indices_char[s[i] - 'a'].push_back(i);
    for (auto& array: indices_char) {
      int array_tam = array.size();
      for (int i = 0, j = i + num_aparicao - 1; j < array_tam; ++i, ++j)
        intervalo_valido[array[i]] = array[j];
    }
    return calculaSubstringMaisLonga(s, num_aparicao, 0, tam, intervalo_valido);
  }
private:
  int calculaSubstringMaisLonga(const string& s, int num_aparicao, int inicio, int fim,
                       const vector<int>& intervalo) {
    if (inicio + num_aparicao > fim) return 0;
    int anterior = inicio;
    int resultado = 0;
    unordered_set<char> caracteres;
    bool split_flag = false;
    for (int i = inicio; i < fim; ++i) {
      if (caracteres.count(s[i]) == 0) {
        if (intervalo[i] >= fim) {
          split_flag = true;
          resultado = max(resultado, calculaSubstringMaisLonga(s, num_aparicao, anterior, i, intervalo));
          anterior = i + 1;
          caracteres.clear();
        } else {
          caracteres.insert(s[i]);
        }
      }
    }
    if (split_flag)
      return max(resultado, calculaSubstringMaisLonga(s, num_aparicao, anterior, fim, intervalo));
    return max(resultado, fim - inicio);
  }
};