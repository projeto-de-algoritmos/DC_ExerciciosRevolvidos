// https://leetcode.com/problems/maximum-sum-circular-subarray/description/

#include <iostream>
#include <numeric>
#include <algorithm>
using namespace std;

class Solution {
public:
    // Funçcao para achar subarray contínuo com a maior soma
    // em um dado array de inteiros
    int kadane(int arr[], int n)
    {
        // armazena a soma do maximo subarray encontrado até então
        int maximo_encontrado = 0;
    
        // armazena a soma maxima do subarray que termina na posicao atual
        int maximo_final_atual = 0;
    
        // traverse the given array
        for (int i = 0; i < n; i++)
        {
            // atualiza a soma maxima do subarray "terminando" no índice `i` (adicionando o
            // elemento atual para a soma máxima terminando no índice anterior `i-1`)
            maximo_final_atual = maximo_final_atual + arr[i];
    
            // se a soma máxima for negativa, defina-a como 0 (que representa
            // um subarray vazio)
            maximo_final_atual = max(maximo_final_atual, 0);
    
            // atualiza o resultado se a soma do subarray atual for maior
            maximo_encontrado = max(maximo_encontrado, maximo_final_atual);
        }
    
        return maximo_encontrado;
    }
    
    // Funcao para encontrar a submatriz circular de soma máxima em uma determinado array
    int maxSubarraySumCircular(vector<int>& vector)
    {
        int n = vector.size();
        int* arr = &vector[0];

        // matriz vazia tem soma de 0
        if (n == 0) {
            return 0;
        }
    
        // encontre o elemento máximo presente em uma determinada matriz
        int num_maximo = *max_element(arr, arr + n);
    
        // se a matriz contiver todos os valores negativos, retorne o elemento máximo
        if (num_maximo < 0) {
            return num_maximo;
        }
    
        // nega todos os elementos do array
        for (int i = 0; i < n; i++) {
            arr[i] = -arr[i];
        }
    
        // execute o algoritmo de Kadane no array modificado
        int soma_num_neg_maximo = kadane(arr, n);
    
        // restaura a matriz
        for (int i = 0; i < n; i++) {
            arr[i] = -arr[i];
        }
    
        /* Retorna o máximo do seguinte:
            1. Soma retornada pelo algoritmo de Kadane no array original.
            2. Soma retornada pelo algoritmo de Kadane na array modificada +
            a soma de todos os elementos do array.
        */
    
        return max(kadane(arr, n), accumulate(arr, arr + n, 0) + soma_num_neg_maximo);
    }
};