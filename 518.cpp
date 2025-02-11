class Solution {
public:
    // Função para calcular o número de maneiras de formar um valor com um conjunto de moedas.
    int change(int valor, vector<int>& moedas) {
        int n = moedas.size(); // Obtém o número de tipos de moedas disponíveis.
        
        // Vetor de DP onde dp[i] representa o número de formas de obter a quantia 'i'.
        vector<uint64_t> dp(valor + 1, 0);
        dp[0] = 1; // Há exatamente uma maneira de fazer 0: não usar nenhuma moeda.

        // Percorre as moedas começando da última para a primeira.
        for(int moeda = n - 1; moeda >= 0; moeda--) {
            // Para cada valor alvo de 0 até 'valor', tentamos formar esse valor com a moeda atual.
            for(int alvo = 0; alvo <= valor; alvo++) {
                // Só atualizamos dp[alvo] se for possível subtrair o valor da moeda do alvo.
                if(alvo >= moedas[moeda]) {
                    dp[alvo] += dp[alvo - moedas[moeda]];
                }
            }
        }
        
        // Retorna o número total de formas de formar 'valor' usando as moedas dadas.
        return dp[valor];
    }
};
