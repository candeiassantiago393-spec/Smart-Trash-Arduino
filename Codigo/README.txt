# Smart Trash — Explicação do Código

Este projeto utiliza um Arduino UNO, um sensor ultrassónico HC-SR04, um servomotor e um botão de fecho manual para controlar automaticamente a tampa de um caixote do lixo inteligente.

O código permite que a tampa abra automaticamente quando é detetada uma mão a uma distância igual ou inferior a 10 cm. A tampa abre até aos 90 graus, permanece aberta durante 12 segundos e depois fecha automaticamente. Se durante esse tempo a mão voltar a ser detetada, o contador dos 12 segundos é reiniciado. O botão de fecho permite cancelar o tempo de espera e fechar imediatamente a tampa.

---

## Código principal

O ficheiro principal do projeto é:

```text
sketch.ino
