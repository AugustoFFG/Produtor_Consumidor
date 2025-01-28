# Descrição do Código: Produtor e Consumidor com Buffer em Arquivo

Este código implementa um modelo simples de **produtor-consumidor** usando arquivos como buffer para armazenar e manipular dados. O produtor gera números aleatórios e os grava no arquivo de buffer, enquanto o consumidor lê e remove o primeiro número do buffer, imprimindo-o na tela. O código utiliza mecanismos de **bloqueio de arquivo** para garantir que o produtor e o consumidor não acessem o arquivo simultaneamente, prevenindo condições de corrida.

## Estrutura do Código

O código está organizado em várias funções que tratam do comportamento do produtor e do consumidor, além de manipulação de arquivos e bloqueio de acesso.

### Funções

1. **`buffer()`**
    - Responsável por criar e preencher o arquivo de buffer (`buffer.txt`) com 10 números aleatórios entre 0 e 99.
    - A função é chamada no início do programa para inicializar o arquivo de buffer.
    - **Fluxo**:
      - Abre o arquivo `buffer.txt` em modo de escrita (`"w"`).
      - Preenche o arquivo com 10 números aleatórios gerados pela função `rand()`.
      - Fecha o arquivo após o preenchimento.

2. **`tranca()`**
    - Função responsável por **bloquear** o arquivo `buffer.txt` para garantir que apenas um processo (produtor ou consumidor) possa acessá-lo por vez.
    - **Fluxo**:
      - Verifica se o arquivo de bloqueio (`buffer.txt.lock`) já existe, o que indica que o arquivo de buffer está sendo acessado.
      - Caso o arquivo de bloqueio exista, a função aguarda 1 segundo (1.000.000 de microssegundos) e tenta novamente.
      - Quando não houver arquivo de bloqueio, cria o arquivo de bloqueio (`buffer.txt.lock`) para indicar que o processo está acessando o buffer.

3. **`destranca()`**
    - Função responsável por **remover o bloqueio** do arquivo de buffer, permitindo que outro processo acesse o arquivo.
    - **Fluxo**:
      - Remove o arquivo de bloqueio (`buffer.txt.lock`), permitindo que o próximo processo possa acessar o buffer.

4. **`produtor()`**
    - Função que simula o processo produtor, que gera números aleatórios e os adiciona ao buffer.
    - **Fluxo**:
      - Em um loop infinito, o produtor gera um número aleatório e o adiciona ao final do arquivo `buffer.txt` usando o modo de abertura `"a"` (apêndice).
      - O produtor imprime o número gerado no console e aguarda um tempo aleatório entre 1 e 3 segundos antes de gerar o próximo número.
      - Durante a operação, o acesso ao arquivo de buffer é protegido por bloqueio (via `tranca()` e `destranca()`).

5. **`consumidor()`**
    - Função que simula o processo consumidor, que lê e remove o primeiro número do buffer.
    - **Fluxo**:
      - Em um loop infinito, o consumidor abre o arquivo de buffer, lê o primeiro número e imprime no console.
      - O número lido é então removido do arquivo, e o restante do conteúdo do arquivo é copiado para um arquivo temporário (`temp.txt`).
      - Após a leitura e remoção, o arquivo temporário é renomeado para substituir o arquivo de buffer original.
      - O consumidor aguarda um tempo aleatório entre 1 e 3 segundos antes de consumir o próximo número.
      - O acesso ao arquivo de buffer é protegido por bloqueio (via `tranca()` e `destranca()`).

### Função Principal (`main`)

- Inicializa o gerador de números aleatórios com a semente obtida do tempo atual (`srand(time(NULL))`).
- Cria um processo filho usando `fork()`:
  - O processo filho executa a função `consumidor()`.
  - O processo pai executa a função `produtor()`.
- Ambos os processos (produtor e consumidor) operam simultaneamente e interagem com o arquivo de buffer de forma coordenada.

## Funcionamento do Programa

1. **Inicialização**: O programa começa criando o arquivo de buffer com 10 números aleatórios usando a função `buffer()`.
2. **Execução Paralela**:
   - O **produtor** gera números aleatórios e os adiciona ao final do arquivo `buffer.txt` em intervalos aleatórios.
   - O **consumidor** lê e remove os números do início do arquivo `buffer.txt` e os imprime na tela.
   - Ambos os processos (produtor e consumidor) utilizam o arquivo de bloqueio (`buffer.txt.lock`) para garantir que o acesso ao arquivo de buffer seja exclusivo em cada momento.
3. **Bloqueio de Acesso**: O produtor e o consumidor só podem acessar o arquivo de buffer quando o arquivo de bloqueio não existe. Isso evita que ambos acessem o arquivo simultaneamente, prevenindo problemas de concorrência.

## Considerações

- **Sincronização**: O uso de arquivos de bloqueio (`buffer.txt.lock`) garante que apenas um processo tenha acesso ao arquivo de buffer de cada vez, garantindo a integridade dos dados.
- **Desempenho**: O programa pode ser lento devido ao uso de arquivos e à necessidade de aguardar a liberação do bloqueio. A função `usleep()` é utilizada para fazer o programa aguardar antes de tentar novamente, o que pode aumentar o tempo de execução dependendo da disponibilidade do arquivo.
- **Escalabilidade**: Este código é adequado para um número limitado de produtores e consumidores. Se o número de processos for muito grande, pode haver impacto no desempenho devido ao uso de arquivos e bloqueios.

## Exemplo de Saída

A saída do programa pode ser semelhante a:

[Produtor] 43 
[Consumidor] 43 
[Produtor] 87 
[Consumidor] 87 
[Produtor] 22 
[Consumidor] 22 ...


Aqui, o **produtor** gera números aleatórios e o **consumidor** consome um número de cada vez.

## Requisitos

- Sistema operacional Unix-like (Linux ou macOS) com suporte à chamada de sistema `fork()`.
- Compilador C (como GCC).

## Como Compilar e Executar

1. Compile o código:

   ```bash
   gcc produtor_consumidor.c -o produtor_consumidor
2. Execute o programa:
   ```bash
   ./produtor_consumidor

