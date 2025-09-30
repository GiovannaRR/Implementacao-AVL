# 🌳 Implementação de Árvore AVL em C++

## 📜 Descrição

Este repositório contém uma implementação educacional de uma **Árvore AVL**, uma estrutura de dados de árvore de busca binária auto-balanceada. O objetivo principal deste projeto é demonstrar as operações fundamentais de inserção e remoção, garantindo que a árvore mantenha suas propriedades de balanceamento para otimizar o tempo de busca.

Uma Árvore AVL mantém a complexidade de tempo para busca, inserção e remoção em $O(\log n)$ no pior caso, tornando-a muito mais eficiente que uma árvore de busca binária comum, que pode degenerar para $O(n)$.

## ✨ Funcionalidades

-   **➕ Inserção de Nós**: Adiciona novos elementos à árvore, realizando rotações quando necessário para manter o balanceamento.
-   **➖ Remoção de Nós**: Remove elementos da árvore, tratando todos os casos e rebalanceando a árvore após a remoção.
-   **🔍 Busca de Valores**: Verifica de forma eficiente se um valor existe na árvore.
-   **🔄 Rotações Automáticas**: Implementação das rotações Simples (à Direita e à Esquerda) e Duplas (Direita-Esquerda e Esquerda-Direita) para manter o fator de balanceamento de cada nó entre -1, 0 e 1.
-   **📊 Percursos**: Métodos para exibir os elementos da árvore (Em-Ordem, Pré-Ordem, Pós-Ordem).

## 💡 O que é uma Árvore AVL?

Uma Árvore AVL é uma Árvore de Busca Binária (ABB) com uma propriedade de balanceamento adicional. Para cada nó na árvore, a diferença de altura entre suas sub-árvores esquerda e direita (conhecida como **Fator de Balanceamento**) não pode ser maior que 1.

> **Fator de Balanceamento = altura(subárvore_direita) - altura(subárvore_esquerda)**

Sempre que uma operação de inserção ou remoção viola essa propriedade, a árvore executa uma ou mais **rotações** para restaurar o balanceamento.

## 📂 Estrutura do Projeto
```
  .
  ├── AVL.cpp                  # Arquivo principal com a implementação da árvore
  ├── output/
  │   └── AVL.exe              # Arquivo executável (gerado após compilação)
  └── README.md                # Este arquivo :)
```
