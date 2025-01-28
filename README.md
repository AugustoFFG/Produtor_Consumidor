# Produtor-Consumidor com Arquivo de Buffer

Este projeto implementa uma solução simples para o problema clássico de Produtor-Consumidor utilizando arquivos para armazenar e acessar os dados de forma segura com bloqueios. O código é escrito em C e utiliza funções de sincronização para garantir que apenas um processo (produtor ou consumidor) tenha acesso ao arquivo de buffer por vez.

## Descrição

O programa simula dois processos: **produtor** e **consumidor**. O **produtor** gera números aleatórios e os escreve em um arquivo de texto (`buffer.txt`), enquanto o **consumidor** lê esses números, imprime-os e os remove do arquivo. O arquivo de bloqueio (`buffer.txt.lock`) é usado para garantir que o acesso ao arquivo de buffer seja feito de forma exclusiva entre os processos.

## Arquitetura

O código implementa o comportamento dos processos de forma simples:
1. **Produtor**:
   - Gera números aleatórios.
   - Bloqueia o acesso ao arquivo `buffer.txt`.
   - Adiciona o número gerado ao arquivo.
   - Libera o bloqueio.
2. **Consumidor**:
   - Lê os números do arquivo.
   - Imprime o número lido.
   - Remove o número lido do arquivo.
   - Libera o bloqueio.

Ambos os processos alternam entre escrita e leitura com bloqueios para evitar condições de corrida e garantir a integridade dos dados.

## Como Funciona

- O programa cria dois processos utilizando `fork()`. O processo pai será o **produtor** e o processo filho será o **consumidor**.
- Ambos os processos usam uma trava (`buffer.txt.lock`) para garantir acesso exclusivo ao arquivo de buffer.
- O **produtor** gera números aleatórios e os adiciona ao arquivo.
- O **consumidor** lê e remove um número do arquivo por vez.

## Compilação e Execução

1. **Compilar** o código:
   ```bash
   gcc produtor_consumidor.c -o produtor_consumidor
