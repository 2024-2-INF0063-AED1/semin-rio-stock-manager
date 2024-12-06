# Gerenciador de Estoque
## Algoritmo para otimização de entregas em centros de distribuição

### Autores
- **Matheus Sousa Marinho (202206132)**  
  Escola de Engenharia Elétrica, Mecânica e de Computação  
  Universidade Federal de Goiás, Goiânia, Brasil  
  *E-mail*: matheusmarinho@discente.ufg.br

- **Gabriel Sales Gerardo (202201623)**  
  Escola de Engenharia Elétrica, Mecânica e de Computação  
  Universidade Federal de Goiás, Goiânia, Brasil  
  *E-mail*: gabriel.gerardo@discente.ufg.br

- **João Pedro da Costa Reis (202206124)**  
  Escola de Engenharia Elétrica, Mecânica e de Computação  
  Universidade Federal de Goiás, Goiânia, Brasil  
  *E-mail*: joaoreis2@discente.ufg.br

### Resumo
Com o aumento da demanda por serviços de transporte, especialmente após a pandemia de 2020, as entregas online ganharam destaque. Este relatório descreve um gerenciador de estoque que organiza produtos com base em uma lista encadeada, levando em conta prazos e distâncias, aprimorando o processo de logística. A ferramenta possibilita a inclusão, exclusão, listagem e ordenação de produtos através do algoritmo Merge Sort, que prioriza determinadas entregas. O projeto apresenta uma estratégia eficaz e modular, com capacidade para aprimoramentos futuros. Esta aplicação ilustra o papel crucial dos sistemas inteligentes na administração logística, auxiliando em operações mais rápidas e estratégicas.

**Palavras-chave**: Logística, Otimização, Prioridade, Ordenação, Gestão de Estoque.

## 1. Introdução

O problema a ser estudado envolve o desenvolvimento de um gerenciador de estoque utilizando listas encadeadas e o algoritmo Merge Sort para otimizar o processo de organização e consulta de produtos. Este sistema visa fornecer uma solução eficiente para empresas ou lojas que necessitam gerenciar grandes volumes de itens, permitindo a inserção, remoção, e busca de produtos de forma dinâmica e eficiente, além de otimizar o tempo de organização do estoque. A lista encadeada é particularmente útil para esse tipo de aplicação, pois permite a alocação dinâmica de memória, sem a necessidade de pré-definir a quantidade de itens a serem armazenados, facilitando o ajuste conforme as mudanças na quantidade de produtos em estoque.

Este problema pode ser utilizado em várias situações, como em empresas de pequeno a grande porte, que necessitam de um método eficiente para administrar produtos, prevenindo o desperdício de recursos ao tentar alocar grandes quantidades de memória ou executar buscas ineficazes. Ademais, a aplicação do Merge Sort assegura a otimização do processo de organização do inventário, simplificando a procura e a consulta de dados sobre os produtos.

A bibliografia pertinente a este projeto abrange várias fontes que debatem os benefícios e a aplicação de listas encadeadas, e métodos de ordenação como o Merge Sort. Abdala (2011) afirma que "listas encadeadas são a estrutura de dados mais simples concebível, excetuando-se naturalmente os arrays".  Esta definição oferece uma fundamentação robusta para compreender a estrutura básica do gerenciador de estoque sugerido. Abdala destaca as vantagens das listas encadeadas sobre os arrays, enfatizando a flexibilidade na alocação dinâmica de memória, crucial para administrar um inventário de produtos que pode mudar ao longo do tempo.

Complementando o entendimento sobre a ordenação dos dados, o artigo de freeCodeCamp sobre algoritmos de ordenação esclarece que "o Merge Sort é um algoritmo eficiente para ordenar grandes volumes de dados, com uma complexidade O(n log n), o que o torna ideal para organizar grandes conjuntos de informações”, como os encontrados em sistemas de inventário. Esse algoritmo será fundamental para otimizar o processo de organização do estoque, garantindo que a busca e a consulta de produtos sejam realizadas rapidamente, mesmo com o aumento do número de itens.

Adicionalmente, Jim Hearson, em seu artigo sobre gerenciamento de estoque, destaca que "um sistema de gerenciamento de estoque eficiente deve ser capaz de lidar com dados em constante mudança, otimizando a alocação e a organização dos produtos para evitar perdas e garantir que a operação da empresa seja fluida" (Hearson, 2024). Essa citação apoia a necessidade de um sistema dinâmico, como o proposto com listas encadeadas, e a importância de algoritmos de ordenação para manter o estoque sempre organizado e acessível.

O dataset a ser explorado no projeto consiste em uma série de dados fictícios de um estoque de produtos. Cada item do estoque será representado como um nó de uma lista encadeada, contendo as informações essenciais do produto, como N° do Pedido, distância de entrega e data de entrega. Este dataset simula um cenário realista de uma empresa que precisa organizar e consultar rapidamente seu inventário, garantindo que as operações de inserção, remoção e busca sejam realizadas de forma eficiente. Na construção do mesmo, utilizamos a implementação em python em `dataframe.py` utilizando a biblioteca `pandas`. Assim, pudemos realizar simulações com números variados de dados de input.

Para o desenvolvimento deste projeto de gerenciamento de estoque, serão revisados dois métodos principais: 
1. **Listas Encadeadas**: Uma estrutura de dados dinâmica que permite a inserção e remoção eficientes de itens em tempo de execução. Esse método será utilizado para armazenar e organizar os produtos no estoque, garantindo que a memória seja alocada conforme necessário e sem a restrição de alocação contígua, como nos arrays. 

2. **Merge Sort**: Um algoritmo de ordenação com complexidade O(n log n), que será implementado para organizar os itens no estoque de maneira eficiente. A utilização do Merge Sort será crucial para garantir que a busca e a consulta aos produtos sejam feitas rapidamente, independentemente do número de itens no estoque.

Além disso, para simplificar a implementação e melhorar a modularidade do código, foi criada a biblioteca `libtools.h`, que reúne funções auxiliares e ferramentas necessárias para a leitura de inputs do usuário e a exibição do menu do programa.

A avaliação dos resultados será baseada em duas métricas que buscam medir tanto a eficiência do sistema quanto a precisão do gerenciamento de estoque, que são: precisão e consistência dos dados, benchmarking comparando a implementação do Merge Sort em listas encadeadas desordenadas com o uso do Bubble Sort na mesma situação.

## 2. Fundamentos Teóricos
O projeto, como dito anteriormente, faz o uso da biblioteca auxiliar `libtools.h`. A descrição das funções que a biblioteca oferece está presente no Apêndice C do relatório.

O arquivo principal do projeto, gerenciador.c, contém a lógica central da execução do sistema, reunindo as operações principais do programa. A estrutura Produto define os dados de um produto, como o número do pedido (NP), a distância a percorrer, a data de entrega e um ponteiro para o próximo produto. Já a estrutura Lista representa a lista de produtos, com dois ponteiros: um para o primeiro produto ("inicio") e outro para o último ("fim"). A lista encadeada é gerenciada por esses ponteiros, permitindo manipular os dados de forma eficiente. As funções do gerenciador de estoque são descritas a seguir:

1.**criarLista**: Cria uma nova lista encadeada, alocando dinamicamente memória para um objeto do tipo *Lista* e inicializando os ponteiros "inicio" e "fim" como "NULL", indicando que a lista está vazia.

2.**verificarNP**: Verifica se um número de pedido já existe na lista. A função percorre todos os produtos cadastrados, comparando o número de pedido de cada um com o valor fornecido. 

3.**adicionarProduto**: Adiciona um novo produto à lista encadeada. A função aloca memória para o novo produto e valida as entradas de número do pedido, distância e data de entrega. Se as entradas forem válidas, o produto é inserido ao final da lista. Caso a lista esteja vazia, o produto será o primeiro e o último da lista. Caso contrário, ele será adicionado ao final.

4.**removerProduto**: Remove um produto da lista encadeada com base no número do pedido. A função verifica se a lista está vazia e, se estiver, exibe uma mensagem informando que nenhum produto foi cadastrado. Solicita-se então o número do pedido a ser removido, e a função percorre a lista para encontrar o produto. Se encontrado, ele é removido da lista; se não, uma mensagem de erro é exibida.

5.**lerCSV**: Lê dados de um arquivo CSV e insere os produtos na lista encadeada. A função tenta abrir o arquivo fornecido e, caso não consiga, exibe uma mensagem de erro. Ela ignora a primeira linha do arquivo (cabeçalho) e, para cada linha subsequente, faz o parsing dos dados dos produtos. Se encontrar um número de pedido já existente, o produto não é adicionado e uma mensagem informando a duplicidade é exibida.

6.**exibirProdutos**: Exibe todos os produtos cadastrados na lista, apresentando suas informações de forma organizada na tela.

O Merge Sort foi escolhido devido à sua complexidade de tempo estável de O(n log n), independentemente da ordem inicial dos dados, o que é crucial quando se lida com um grande número de pedidos desordenados. Comparado ao Bubble Sort, que possui complexidade de O(n²), o Merge Sort é muito mais eficiente em grandes listas, já que o Bubble Sort tende a ser muito lento em casos com muitos elementos. Por outro lado, o Quick Sort, embora também tenha complexidade O(n log n) em média, pode apresentar um desempenho pior de O(n²) em casos específicos, como quando a lista está quase ordenada. O Merge Sort, portanto, garante uma performance mais previsível e confiável para grandes volumes de dados, sendo mais adequado para o contexto do gerenciador de estoque.

## 3. Metodologia
O desenvolvimento do gerenciador de estoque seguiu uma metodologia estruturada, integrando o uso de listas encadeadas como estrutura de dados, o algoritmo Merge Sort para ordenação eficiente e uma biblioteca auxiliar, denominada `libtools.h`, que simplifica operações como leitura de entradas do usuário e limpeza do buffer de entrada, garantindo robustez contra entradas inválidas ou inesperadas.

O processo foi conduzido com base em um fluxo lógico de escolhas e operações que fundamentaram a concepção do algoritmo. A Tabela 1 apresenta um resumo das funcionalidades básicas do sistema, enquanto o Apêndice A detalha o passo a passo seguido para o concebimento do programa.

| Função | Descrição |
|--------|-----------|
| Inserir Produto | Recebe dados do produto do usuário e insere na lista encadeada |
| Remover Produto | Localiza e remove o produto da lista através do N° do Pedido |
| Ordenar Lista | Aplica o Merge Sort para ordenar os produtos |
| Exibir Lista | Exibe os produtos do estoque |
| Ler Arquivo | Realiza a leitura e parsing de um arquivo CSV |
| Sair | Encerra a execução do programa |

*Tabela 1. Resumo das principais operações do sistema*

As operações do gerenciador de estoque são baseadas em manipulações de uma lista encadeada, permitindo o gerenciamento dinâmico dos produtos. A inserção de produtos adiciona um novo item no final da lista. Durante esse processo, os dados do produto, como N° do Pedido (NP), distância e data de entrega, são coletados, e um novo nó é alocado e conectado à estrutura existente. Essa abordagem é eficiente para manter a organização da lista e facilita futuras operações. 

A remoção de produtos permite excluir itens específicos com base no NP. O algoritmo percorre a lista, localiza o nó correspondente e ajusta os ponteiros para preservar a integridade da estrutura após a exclusão. Caso o produto a ser removido esteja no início ou no final da lista, ajustes adicionais são realizados. 

A operação de exibição de produtos percorre a lista do início ao fim, imprimindo as informações armazenadas em cada nó. Isso proporciona uma visão clara e organizada do estoque atual, auxiliando na tomada de decisões gerenciais.

A operação de ordenar produtos no programa utiliza o algoritmo Merge Sort. O processo começa ao comparar os produtos com base em critérios hierárquicos: data de entrega, distância e NP. Esses critérios são avaliados sequencialmente para determinar a ordem. A lista é dividida em partes menores, utilizando ponteiros rápidos e lentos para localizar o ponto médio. Cada segmento é ordenado recursivamente e, em seguida, as sublistas são mescladas. Durante a mesclagem, o programa escolhe os produtos com base no critério de prioridade, ajustando os ponteiros para reconstruir a lista de forma ordenada. A função principal, “ordenarLista”, inicia o processo verificando se a lista contém elementos. Caso positivo, o Merge Sort é chamado para ordenar a lista desde o início. Após a conclusão, a lista é reorganizada de acordo com os critérios definidos, sendo ideal para priorizar entregas no estoque.

A operação de leitura de arquivo permite o carregamento automático dos produtos no sistema a partir de um arquivo no formato CSV. Este arquivo deve conter os atributos de cada produto organizados em linhas, com os valores separados por vírgulas. Durante a leitura, o programa utiliza funções específicas para abrir o arquivo, processar cada linha, dividir os valores com base no delimitador (vírgula) e convertê-los nos atributos correspondentes de um novo nó da lista encadeada. Este nó é então inserido dinamicamente na lista, garantindo que os dados sejam integrados à lista de entrega. O formato do arquivo CSV está exemplificado no apêndice D.

A funcionalidade de saída finaliza a execução do programa de forma segura. Antes de encerrar, o sistema libera toda a memória alocada dinamicamente para os nós da lista encadeada, prevenindo vazamentos de memória e garantindo o encerramento adequado do processo.

Portanto, a metodologia adotada foca na modularidade e na eficiência do sistema, utilizando o Merge Sort para ordenar grandes listas de produtos e a biblioteca `libtools.h` para garantir a flexibilidade e simplificação do código. O funcionamento geral do programa está ilustrado no Apêndice B.

## 4. Resultados e Conclusões
O desenvolvimento do sistema de gerenciamento de estoque demonstrou a eficácia de utilizar listas encadeadas em conjunto com o algoritmo Merge Sort para manipular e ordenar dados estruturados. A escolha dessas ferramentas foi fundamentada pela necessidade de lidar com uma estrutura de dados dinâmica e adaptável, onde elementos representam pedidos compostos por múltiplos atributos (data de entrega, distância e número do pedido), exigindo critérios hierárquicos para ordenação.

A opção por listas encadeadas revelou-se vantajosa no contexto do projeto, especialmente devido à flexibilidade que oferecem para manipulação de dados. Diferentemente dos arrays, as listas encadeadas não exigem alocação de memória contínua, permitindo que o programa lide de forma eficiente com um número variável de elementos. Além disso, a remoção e a inserção de elementos são operações realizadas diretamente com ponteiros, evitando o custo de deslocamento de elementos típico de arrays. Essa característica foi particularmente importante ao gerenciar pedidos em que modificações frequentes na estrutura eram necessárias. A escolha das listas também simplificou a implementação de critérios múltiplos de comparação durante a ordenação, uma vez que os dados de cada pedido foram armazenados como structs, facilitando o acesso e a manipulação das informações.

O Merge Sort foi escolhido como o algoritmo de ordenação devido à sua complexidade temporal constante de O(n log ⁡n), independentemente da ordem inicial dos dados. Essa estabilidade mostrou-se crucial no contexto de uma lista encadeada, onde não há acesso direto a índices como nos arrays. Além disso, o Merge Sort é mais adequado para listas encadeadas porque evita a necessidade de acesso repetido aos elementos intermediários, ao contrário do Quick Sort, que requer particionamento e pode atingir um desempenho de O(n²) em seu pior caso. Comparado ao Bubble Sort, cuja complexidade é O(n²) mesmo nos cenários intermediários, o Merge Sort apresentou maior eficiência e constância, especialmente ao lidar com grandes volumes de dados e múltiplos critérios de comparação. É possível observar como as estruturas de ordenação se comportam com o aumento de elementos a serem ordenados, intensificando o número de operações necessárias para a organização da lista, através da figura 1.

![Gráfico Merge](/assets/Gráfico%20Merge.png)

Figura 1. Gráfico mostrando a complexidade das estruturas de ordenação

Durante o projeto, várias lições importantes foram assimiladas. A implementação de listas encadeadas destacou a importância de gerenciar cuidadosamente a memória alocada dinamicamente, evitando vazamentos ou acessos inválidos. Adicionalmente, a modularização do código por meio da biblioteca `libtools.h` demonstrou ser uma prática essencial para tornar o sistema mais legível e fácil de manter.

A escolha do Merge Sort proporcionou uma compreensão mais profunda dos fatores que influenciam o desempenho de algoritmos de ordenação, especialmente em cenários específicos como o uso de listas encadeadas. Este aprendizado reforçou a importância de alinhar a escolha do algoritmo às características da estrutura de dados utilizada.
 
Por fim, o projeto mostrou como a priorização de critérios de ordenação pode impactar diretamente a eficiência do gerenciamento de estoques. A adoção de um método eficiente e robusto, aliado a uma estrutura de dados dinâmica, resultou em um sistema funcional e escalável, apto a lidar com os desafios práticos de gestão de pedidos. Esse aprendizado é aplicável em contextos reais, oferecendo insights valiosos para a resolução de problemas em sistemas mais complexos.

## Referências
1. DELGADO, Maria Betania Darcie Pessoa; DOS SANTOS BARBOSA, Amanda. A logística de entrega como um diferencial competitivo no comércio eletrônico. Congresso de Tecnologia-Fatec Mococa, 2023.
2. ABDALA, Daniel Duarte. *Listas encadeadas*. Disponível em: https://www.facom.ufu.br/~abdala/DAS5102/TEO_ListasEncadeadas.pdf
3. FREECODECAMP. *Algoritmos de ordenação explicados*. Disponível em: https://www.freecodecamp.org/portuguese/news/algoritmos-de-ordenacao-explicados-com-exemplos-em-python-java-e-c/
4. DIETZ, Paul F. *Maintaining order in a linked list. In: Proceedings of the fourteenth annual ACM symposium on Theory of computing*. 1982. p. 122-127.
5. HEARSON, Jim. *O que é gerenciamento de estoque? Disponível em: https://www.oracle.com/br/scm/inventory-management/what-is-inventory-management/*. Acesso em: 19 nov. 2024.

## Apresentação
https://docs.google.com/presentation/d/13OgVZOCVku7zqfG5pzkPP247VS97e92B8tZFC5QbBHg/edit?usp=sharing

## Apêndices
### Apêndice A - Diagrama dos passos seguidos e escolhas feitas para o algoritmo
![Diagrama JPG](/assets/DiagramaJPG.jpg)


### Apêndice B - Diagrama de Blocos que Ilustra o Funcionamento do Programa
![Diagrama V3](/assets/Diagrama_V3.png)

### Apêndice C - Descrição das funções oferecidas pela biblioteca `libtools.h`
A biblioteca oferece funções de leitura de dados do tipo “int”, “float” e “strings”, além de garantir que o buffer de entrada seja limpo para evitar a leitura errônea de dados. O uso dessa biblioteca permite que a lógica de negócios do sistema de gerenciamento de estoque seja isolada das complexidades da implementação das estruturas de dados e algoritmos, facilitando a integração e garantindo um código mais organizado e eficiente.Ambos os métodos serão integrados de forma a otimizar a manipulação e a organização do estoque, permitindo uma gestão eficiente dos produtos armazenados. Entre as funções oferecidas pela biblioteca, estão: 

1.**clear_input_buffer**: Limpa o buffer de entrada padrão, garantindo que caracteres residuais deixados no buffer, como o caractere de nova linha (\n), sejam descartados após a leitura de dados. Isso é importante para evitar que dados incorretos sejam processados nas próximas leituras de entrada.

2.**get_int**: Solicita ao usuário um valor inteiro e, após a leitura, limpa o buffer de entrada. Ela assegura que o valor inserido seja corretamente processado antes de prosseguir para outras interações.

3.**get_float**: Similar à get_int, mas essa função solicita a entrada de um número do tipo float.

4.**get_string**: Permite a leitura de uma linha de texto fornecida pelo usuário, armazenando-a em um buffer de string cujo tamanho máximo é especificado pelo parâmetro length. Após a leitura, a função remove o caractere de nova linha (\n) no final da string, quando presente, garantindo que a string armazenada esteja corretamente formatada e sem caracteres desnecessários. Essa função é útil para capturar entradas de texto livre e tratar corretamente o que é inserido pelo usuário.

5.**exibirMenu**: Mostra o menu principal do sistema de gerenciamento de estoques. Ela apresenta ao usuário uma série de opções, como adicionar ou remover produtos, exibir a lista de produtos, ordenar os itens conforme a data de entrega, ou carregar dados de um arquivo.

### Apêndice D - Exemplo do formato do arquivo CSV suportado pelo programa
![Apêndice D](/assets/apêndice%20D.jpg)


<!-- SETUP -->
## Setup
### 1. Clone the repository:
```bash 
git clone git@github.com:m9tzin/stock-manager.git
cd stock-manager/src
```
### 2. Compile:
```bash 
gcc -o nome-do-seu-executavel gererenciador.c
```
### 3. Run file:
```bash 
./nome-do-seu-executavel
```

## License
Distributed under the MIT License. See `LICENSE.txt` for more information.
