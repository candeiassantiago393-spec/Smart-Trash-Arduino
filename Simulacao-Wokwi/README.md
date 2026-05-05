# Simulação Wokwi — Smart Trash Arduino

## Descrição

Esta pasta contém os ficheiros necessários para simular o projeto **Smart Trash** na plataforma **Wokwi**.

A simulação representa o funcionamento de um caixote do lixo inteligente com:

- **Arduino UNO**
- **Sensor ultrassónico HC-SR04**
- **Servomotor**
- **Botão de fecho manual/reset**

O sistema abre automaticamente a tampa quando é detetada uma mão ou objeto a menos de **10 cm** do sensor. A tampa abre até aos **90 graus**, mantém-se aberta durante **12 segundos** e esse tempo pode ser renovado se houver nova deteção. O botão permite fechar imediatamente a tampa.

---

## Ficheiros desta pasta

| Ficheiro | Função |
|---|---|
| `diagram.json` | Define o circuito e as ligações da simulação |
| `libraries.txt` | Indica as bibliotecas utilizadas no projeto |
| `wokwi-project.txt` | Contém a referência ao projeto Wokwi |

---

## O que fazer no Wokwi

### 1. Abrir a simulação
Abrir o projeto no Wokwi através do link da simulação.

### 2. Verificar os componentes
Confirmar que a simulação contém os seguintes componentes:

- Arduino UNO
- Sensor ultrassónico HC-SR04
- Servomotor
- Botão de pressão

### 3. Carregar o código
No Wokwi, o código principal do projeto deve ser colocado no ficheiro `sketch.ino`.

Se o código estiver no repositório com outro nome, por exemplo:

```text
smart_trash.ino
