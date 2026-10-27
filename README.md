# Gerenciador de Manutenção de Equipamentos de Laboratório

Projeto 2 da disciplina **Estrutura de Dados (Prática)** do curso de Engenharia de Computação da Escola Politécnica da PUC-Campinas, 2º semestre de 2026.

Sistema em linguagem C para registrar equipamentos de laboratório (placas de desenvolvimento, microcontroladores, computadores), controlar os incidentes (falhas) que ocorrem com eles e permitir consultas aos dados em memória. Toda a solução usa estruturas de dados dinâmicas implementadas pelo próprio time: uma **Árvore Binária de Busca** e uma **Tabela Hash** com encadeamento separado.

---

## Time

| Nome | RA |
|------|----|
| Guilherme Carvalho Mais | 25009646 |
| Luigi de Lima Miranda | 25005899 |

---

## Dados do sistema

### Equipamento

| Campo | Tipo | Regra |
|-------|------|-------|
| Código | `int` | 4 dígitos, de 1000 a 9999, único |
| Nome (apelido) | `char[11]` | até 10 caracteres (ex.: `Placa-01`, `PC-Lab08`) |
| Incidentes | lista simplesmente encadeada | IDs dos incidentes associados |

### Incidente

| Campo | Tipo | Regra |
|-------|------|-------|
| Identificador | `int` | 2 dígitos, único |
| Código do equipamento | `int` | 1000 a 9999, deve existir na tabela hash |
| Gravidade | `int` | 1 = Baixa, 2 = Média, 3 = Alta |

---

## Estruturas de dados

### Árvore Binária de Busca (incidentes)

Organiza os incidentes pelo identificador. Cada nó guarda os dados de um incidente.

- **Inserção** seguindo a regra de formação definida pelo time
- **Busca** pelo identificador, exibindo os dados do incidente e do equipamento
- **Listagem** em ordem crescente (percurso in-ordem)
- **Remoção** tratando os três casos: nó folha, nó com um filho e nó com dois filhos

> Regra de inserção/busca/remoção adotada: _a definir e apresentar à professora_.

### Tabela Hash (equipamentos)

Localiza equipamentos diretamente pelo código.

- **Função hash:** _a definir e apresentar à professora_ (ex.: método da divisão, `codigo % TAMANHO`)
- **Tamanho da tabela:** _a definir com a professora_
- **Colisões:** encadeamento separado, com listas ligadas próprias (vetor de ponteiros)
- Cada elemento guarda os dados do equipamento e a lista de IDs dos incidentes associados

### Integração entre as estruturas

- **Registrar incidente:** verifica na hash se o equipamento existe; se existir, insere o incidente na árvore e adiciona o ID à lista do equipamento.
- **Consultar incidentes de um equipamento:** localiza o equipamento na hash e, a partir dos IDs da lista, busca os dados na árvore.
- **Exclusões:** mantêm a consistência entre hash e árvore. Excluir um equipamento remove antes todos os seus incidentes da árvore; excluir um incidente remove também o ID da lista do equipamento.

---

## Menu

```
1 - Cadastrar Equipamento
2 - Registrar Incidente
3 - Consultar Equipamento e Incidentes
4 - Listar todos os Incidentes
5 - Excluir um Incidente
6 - Excluir um Equipamento
7 - Encerrar Programa
```

---

## Regras de funcionamento

- Não pode haver dois equipamentos com o mesmo código.
- Não pode haver dois incidentes com o mesmo identificador.
- Todo incidente deve estar associado a um equipamento já cadastrado.
- A remoção de incidentes deve manter as propriedades da árvore binária de busca.
- Colisões na hash não podem causar perda ou sobreposição de dados.
- Toda a memória alocada (nós da árvore, nós das listas e posições da hash) é liberada ao encerrar.
- Entradas inválidas (códigos inexistentes, duplicados, fora do intervalo) geram mensagens informativas sem interromper o programa.

### Restrições do projeto

- **Proibido:** variáveis globais, vetores para armazenar os dados, e funções ou bibliotecas prontas de ordenação. Projetos que usarem esses recursos não serão corrigidos.

---

## Estrutura de arquivos (sugerida)

```
PROJETO_ESTRUTURA_DE_DADOS_2/
├── main.c        # menu e fluxo principal
├── arvore.h      # declarações da árvore binária de busca
├── arvore.c      # implementação da árvore
├── hash.h        # declarações da tabela hash e das listas
├── hash.c        # implementação da tabela hash e das listas
└── README.md
```

---

## Como compilar e executar

### Code::Blocks

Crie um projeto do tipo *Console application* em C, adicione todos os arquivos `.c` e `.h` e use **Build and Run** (F9).

### Terminal (GCC)

```bash
gcc main.c arvore.c hash.c -o gerenciador -Wall
./gerenciador
```

No Windows, execute `gerenciador.exe`.

---

## Fluxo de trabalho com Git

| Branch | Uso |
|--------|-----|
| `main` | versão estável, que compila e funciona |
| `apoio` | desenvolvimento e testes |

```bash
git checkout apoio            # trabalhar na branch de apoio
git add .
git commit -m "Feat: descrição da mudança"
git push

git checkout main             # quando estiver estável, juntar na main
git merge apoio
git push
```

---

## Entregas

- **Relatório (.pdf):** capa com nome e RA em ordem alfabética, introdução, desenvolvimento (regras da árvore, função hash, tamanho da tabela, tratamento de colisões, integração) e referências bibliográficas (com data de acesso para sites).
- **Código-fonte (.c e bibliotecas):** compatível com o Code::Blocks.
- **Prazo:** 30/11, até 23h59, via Canvas.
