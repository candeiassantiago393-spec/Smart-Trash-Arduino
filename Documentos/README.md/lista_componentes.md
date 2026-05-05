# Documentos — Smart Trash Arduino

Esta pasta contém a documentação técnica mais detalhada do projeto **Smart Trash Arduino**.

Aqui estão reunidas informações sobre o funcionamento do sistema, os componentes utilizados, as ligações elétricas, as entradas e saídas do Arduino, a explicação do código, os estados de funcionamento e as condições de segurança do projeto.

---

## Conteúdo da pasta

| Ficheiro | Descrição |
|---|---|
| `Smart_Trash_Especificacao.docx` | Documento de especificação técnica completo do projeto |
| `lista_componentes.md` | Lista dos componentes utilizados, respetivas funções e ligações principais |

---

## O que pode ser consultado nesta pasta

Nesta pasta é possível consultar informação mais detalhada sobre:

- Objetivo do projeto;
- Funcionamento geral do Smart Trash;
- Componentes utilizados;
- Ligações elétricas;
- Entradas e saídas do sistema;
- Pinagem do Arduino;
- Funcionamento do sensor ultrassónico HC-SR04;
- Funcionamento do servomotor;
- Botão de reset/fecho manual;
- Estados de funcionamento;
- Condições de funcionamento;
- Segurança e fiabilidade;
- Possíveis melhorias futuras.

---

## Resumo do projeto

O **Smart Trash Arduino** é um sistema automático de abertura e fecho da tampa de um caixote do lixo.

O sistema utiliza um sensor ultrassónico **HC-SR04** para detetar a aproximação da mão do utilizador. Quando a distância medida é igual ou inferior a **10 cm**, o Arduino aciona um servomotor que abre a tampa até aos **90 graus**.

Depois de aberta, a tampa permanece nessa posição durante **12 segundos**. Se durante esse tempo houver uma nova deteção da mão, a contagem dos 12 segundos é reiniciada, permitindo que a tampa continue aberta por mais tempo.

O sistema inclui também um botão de **reset/fecho manual**, que permite fechar imediatamente a tampa, colocando o servomotor novamente na posição de **0 graus**.

---

## Ligações principais

| Elemento | Pino Arduino | Função |
|---|---:|---|
| Trigger do HC-SR04 | D3 | Envia o impulso ultrassónico |
| Echo do HC-SR04 | D5 | Recebe o sinal refletido |
| Servomotor | D9 | Controla a abertura e o fecho da tampa |
| Botão de fecho/reset | D12 | Fecha manualmente a tampa |

---

## Observação

Esta pasta deve ser utilizada para guardar os documentos explicativos e técnicos do projeto.

O código principal encontra-se na raiz do repositório, no ficheiro:

```text
smart_trash.ino
