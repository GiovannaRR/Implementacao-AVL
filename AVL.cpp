#include<iostream>
#include <algorithm>

using namespace std;

struct Vertice {
    int valor;
    int altura;
    // fb (fator de balanceamento) não é estritamente necessário armazenar, 
    // pois pode ser calculado a partir da altura dos filhos. 
    // Mas vamos mantê-lo para seguir a estrutura.
    int fb; 
    Vertice *esq;
    Vertice *dir;
    
    // Construtor
    Vertice(int v): esq{nullptr}, dir{nullptr}, valor{v}, altura{0}, fb{0} {}
};

class Avl {

    public:

        Avl(): raiz{nullptr}{}

        ~Avl() {
            destruir(raiz);
        }

        void insere(int valor) {
            raiz = insere(raiz, valor);
        }
        
        void remove(int valor) {
            raiz = remove(raiz, valor);
        }

        bool busca(int valor) {
            Vertice* atual = raiz;
            while (atual != nullptr) {
                if (valor == atual->valor) {
                    return true;
                }
                if (valor < atual->valor) {
                    atual = atual->esq;
                } else {
                    atual = atual->dir;
                }
            }
            return false;
        }

        void imprime() {
            cout << "--- Arvore AVL (pre-ordem) ---" << endl;
            imprime(raiz);
            cout << "-----------------------------" << endl;
        }


    private:
        Vertice *raiz;

        // Função para destruir a árvore e liberar memória
        void destruir(Vertice* v) {
            if (v == nullptr) return;
            destruir(v->esq);
            destruir(v->dir);
            delete v;
        }

        // Retorna a altura de um vértice (seguro para ponteiros nulos)
        int altura(Vertice *v) {
            if (v == nullptr) {
                return -1;
            }
            return v->altura;
        }

        // Calcula e retorna o fator de balanceamento de um vértice
        int fator_bal(Vertice *v) {
            if (v == nullptr) {
                return 0;
            }
            return altura(v->esq) - altura(v->dir);
        }

        int profundidade(Vertice *v) {
            return 0;
        }

        // Encontra o vértice com o menor valor na sub-árvore
        Vertice* min(Vertice *v) {
            if (v == nullptr) return nullptr;
            Vertice* atual = v;
            while (atual->esq != nullptr) {
                atual = atual->esq;
            }
            return atual;
        }
        
        // Rotação Simples à Direita
        Vertice *rot_dir(Vertice *y) {
            Vertice *x = y->esq;
            Vertice *T2 = x->dir;

            // Realiza a rotação
            x->dir = y;
            y->esq = T2;

            // Atualiza as alturas (a ordem importa: primeiro o filho, depois o novo pai)
            y->altura = max(altura(y->esq), altura(y->dir)) + 1;
            x->altura = max(altura(x->esq), altura(x->dir)) + 1;

            return x; 
        }

        // Rotação Simples à Esquerda
        Vertice *rot_esq(Vertice *x) {
            Vertice *y = x->dir;
            Vertice *T2 = y->esq;

            // Realiza a rotação
            y->esq = x;
            x->dir = T2;

            // Atualiza as alturas
            x->altura = max(altura(x->esq), altura(x->dir)) + 1;
            y->altura = max(altura(y->esq), altura(y->dir)) + 1;

            return y; 
        }

        Vertice* remove(Vertice *v, int valor) {
            if (v == nullptr) return v;

            // Navega até o vértice a ser removido
            if (valor < v->valor) {
                v->esq = remove(v->esq, valor);
            } else if (valor > v->valor) {
                v->dir = remove(v->dir, valor);
            } else { 

                // Caso 1: O vértice é uma folha ou tem apenas um filho
                if (v->esq == nullptr || v->dir == nullptr) {
                    Vertice *temp = v->esq ? v->esq : v->dir;

                    if (temp == nullptr) { 
                        temp = v;
                        v = nullptr;
                    } else { 
                        *v = *temp; 
                    }
                    delete temp;

                } else {
                    // Caso 3: O vértice tem 2 filhos
                    // Encontra o sucessor (menor da sub-árvore direita)
                    Vertice* sucessor = min(v->dir);
                    
                    // Copia o valor do sucessor para este vértice
                    v->valor = sucessor->valor;
                    
                    // Remove o sucessor da sub-árvore direita
                    v->dir = remove(v->dir, sucessor->valor);
                }
            }

            //Se a árvore ficou vazia após a remoção 
            if (v == nullptr) {
                return v;
            }

            v->altura = 1 + max(altura(v->esq), altura(v->dir));
            v->fb = fator_bal(v);

            //Se o vértice ficou desbalanceado, aplica as rotações
            //Esquerda-Esquerda
            if (v->fb > 1 && fator_bal(v->esq) >= 0) {
                return rot_dir(v);
            }
            //Esquerda-Direita
            if (v->fb > 1 && fator_bal(v->esq) < 0) {
                v->esq = rot_esq(v->esq);
                return rot_dir(v);
            }
            //Direita-Direita
            if (v->fb < -1 && fator_bal(v->dir) <= 0) {
                return rot_esq(v);
            }
            //Direita-Esquerda
            if (v->fb < -1 && fator_bal(v->dir) > 0) {
                v->dir = rot_dir(v->dir);
                return rot_esq(v);
            }

            return v;
        }

        void imprime(Vertice* v) {
            if (v == nullptr) return;
            cout << v->valor << " (H: " << v->altura << ", FB: " << v->fb << ")" << endl;
            imprime(v->esq);
            imprime(v->dir);
        }

        Vertice* insere(Vertice *v, int valor) {
            
            // Caso base: aloca memória e retorna o novo vértice
            if (v == nullptr) {
                return new Vertice(valor);
            }
            
            // IDA (encontrar a posição de inserção)
            if (valor < v->valor) {
                v->esq = insere(v->esq, valor);
            } else if (valor > v->valor) {
                v->dir = insere(v->dir, valor);
            } else {
                return v; //valores duplicados não são inseridos
            }

            // Atualiza a altura do vértice ancestral atual
            v->altura = 1 + max(altura(v->esq), altura(v->dir));

            //Calcula o fator de balanceamento
            v->fb = fator_bal(v);

            //Verifica o balanceamento e aplica as rotações se necessário

            //Esquerda-Esquerda (fb > 1)
            if (v->fb > 1 && valor < v->esq->valor) {
                return rot_dir(v);
            }

            //Direita-Direita (fb < -1)
            if (v->fb < -1 && valor > v->dir->valor) {
                return rot_esq(v);
            }

            //Esquerda-Direita (fb > 1)
            if (v->fb > 1 && valor > v->esq->valor) {
                v->esq = rot_esq(v->esq);
                return rot_dir(v);
            }

            //Direita-Esquerda (fb < -1)
            if (v->fb < -1 && valor < v->dir->valor) {
                v->dir = rot_dir(v->dir);
                return rot_esq(v);
            }
            
            //retorna o ponteiro 
            return v;
        }

};

int main() {

    Avl t;

    //inserção e rotações
    cout << "Inserindo elementos..." << endl;
    t.insere(100);
    t.insere(50);
    t.insere(200);
    t.insere(30);
    t.insere(60);
    t.insere(55); //rotação dupla (Direita-Esquerda)

    t.imprime();

    //busca
    cout << "\nBuscando 60: " << (t.busca(60) ? "Encontrado" : "Nao encontrado") << endl;
    cout << "Buscando 99: " << (t.busca(99) ? "Encontrado" : "Nao encontrado") << endl;

    cout << "\nRemovendo 55..." << endl;
    t.remove(55);
    t.imprime();

    cout << "\nRemovendo 50..." << endl;
    t.remove(50);
    t.imprime();
    
    cout << "\nRemovendo 200..." << endl;
    t.remove(200); //rotação para rebalancear
    t.imprime();

    return 0;
}