class Solution {
public:
    // Definição de um tipo chamado "Trabalho" que representa um trabalho com:
    // (horário de início, horário de término, lucro)
    using Trabalho = array<int, 3>; 

    vector<Trabalho> trabalhos; // Vetor para armazenar todos os trabalhos
    vector<int> dp; // Vetor para armazenar os resultados da Programação Dinâmica
    int n; // Número total de trabalhos
    vector<int> proximo; // Vetor para armazenar o próximo trabalho não conflitante

    // Função para encontrar o próximo trabalho que pode ser escolhido sem sobreposição
    void busca_binaria() {
        for (int i = 0; i < n; i++) {
            // Encontramos o primeiro trabalho que começa após o término do trabalho atual
            proximo[i] = upper_bound(trabalhos.begin() + i, trabalhos.end(),
                array<int, 3>{trabalhos[i][1], 0, 0}) - trabalhos.begin();
        }
    }
    
    // Função para calcular o máximo lucro utilizando Programação Dinâmica (PD)
    void iterar() {
        dp.assign(n + 1, 0); // Inicializa o vetor DP com zeros
        
        // Percorremos os trabalhos de trás para frente (abordagem bottom-up)
        for(int i = n - 1; i >= 0; i--) {
            // Escolher o trabalho i e adicionar o lucro do próximo trabalho não conflitante
            int lucro_com_i = trabalhos[i][2] + dp[proximo[i]];

            // Pular o trabalho i e considerar o lucro do próximo índice
            int lucro_sem_i = dp[i + 1];

            // Armazena o máximo lucro possível entre pegar ou não o trabalho
            dp[i] = max(lucro_com_i, lucro_sem_i);
        }
    }

    // Função principal para calcular o maior lucro possível ao agendar trabalhos sem sobreposição
    int jobScheduling(vector<int>& inicio, vector<int>& fim, vector<int>& lucro) {
        n = inicio.size(); // Obtém o número total de trabalhos
        
        // Inicializa o vetor 'trabalhos' com valores padrão
        trabalhos.assign(n, {-1, -1, -1});

        // Preenche o vetor 'trabalhos' com os dados fornecidos
        for (int i = 0; i < n; i++)
            trabalhos[i] = {inicio[i], fim[i], lucro[i]};

        // Ordena os trabalhos pelo horário de início para facilitar o processamento
        sort(trabalhos.begin(), trabalhos.end());

        // Inicializa o vetor 'proximo' para armazenar os índices dos próximos trabalhos possíveis
        proximo.assign(n, -1);

        // Preenche o vetor 'proximo' usando busca binária
        busca_binaria();

        // Aplica a programação dinâmica para encontrar o máximo lucro possível
        iterar();
        
        // Retorna o valor armazenado em dp[0], que representa a melhor escolha desde o início
        return dp[0];
    }
};
