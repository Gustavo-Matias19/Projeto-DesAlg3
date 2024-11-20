Banco exchange

Responsáveis pelo projeto:
Gustavo Matias Félix, RA: 22.124.007-0.
Lucas Galvano de Paula, RA: 22.124.015-3.


# Exchange de Criptomoedas - Fork e Implementação de Funcionalidades Adicionais

Este repositório contém o código de uma Exchange de Criptomoedas desenvolvida em C. O projeto foi inicialmente criado como **Projeto 1** para a construção de uma plataforma de compra e venda de criptomoedas com funcionalidades para investidores. Em seguida, realizamos um **fork** deste projeto e implementamos a **segunda parte** (**Projeto 3**) que adiciona funcionalidades para o **administrador** da exchange.

## Objetivo do Projeto

O objetivo do projeto é criar uma plataforma de exchange de criptomoedas onde investidores podem realizar operações de compra, venda e consulta de saldos de criptomoedas (Bitcoin, Ethereum e Ripple), além de registrar transações. Após o fork, adicionamos um módulo para o administrador, permitindo o gerenciamento de investidores e criptomoedas.

## Funcionalidades Implementadas

### Projeto 1 - Módulo do Investidor

O módulo de investidor contém as seguintes funcionalidades:
- **Efetuar login** usando CPF e senha.
- **Consultar saldo** de reais, Bitcoin, Ethereum e Ripple.
- **Consultar extrato de operações** da carteira de investimentos.
- **Depositar reais** na carteira de investimento.
- **Sacar reais** da carteira de investimento.
- **Comprar criptomoedas** (Bitcoin, Ethereum, Ripple), com taxa de compra.
- **Vender criptomoedas**, com taxa de venda.
- **Atualizar cotação das criptomoedas** com variações aleatórias.

### Projeto 3 - Módulo do Administrador (parte 2)

Após o fork, implementamos o módulo do administrador com as seguintes funcionalidades:
- **Efetuar login** usando CPF e senha.
- **Cadastro de novo investidor** (nome, CPF, senha).
- **Excluir investidor** (confirmar a exclusão após exibir dados).
- **Cadastro de criptomoeda** (nome, cotação inicial, taxas de compra e venda).
- **Excluir criptomoeda** (confirmar a exclusão após exibir dados).
- **Consultar saldo de um investidor** (informar CPF e exibir saldo).
- **Consultar extrato de um investidor** (informar CPF e exibir extrato).
- **Atualizar cotação de criptomoedas** (mesma lógica do investidor).

## Como Compilar e Executar

### Para o Investidor:

1. **Compilar o programa do investidor**:
   ```bash
   gcc inv_main.c funcoes.c cadastro.c adm_trade.c 

2. **Compilar o programa do Administrador**:
   ```bash
    gcc adm_main.c adm_trade.c funcoes.c cadastro.c inv_trade.c

