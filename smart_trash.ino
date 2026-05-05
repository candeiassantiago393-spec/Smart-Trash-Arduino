#include <Servo.h> // Inclui a biblioteca necessária para controlar o servomotor

Servo servo_9;     // Cria um objeto Servo chamado servo_9
int pos = 0;       // Variável que guarda a posição atual do servomotor em graus

#define pinoTrigger 3     // Define o pino digital 3 como Trigger do sensor ultrassónico
#define pinoEcho 5        // Define o pino digital 5 como Echo do sensor ultrassónico
#define botaoFechar 12    // Define o pino digital 12 para o botão de fecho manual

// Função responsável por medir a distância em centímetros usando o sensor ultrassónico
float lerDistanciaEmCms(int triggerP, int echoP) {
  digitalWrite(triggerP, LOW);       // Garante que o pino Trigger começa em nível baixo
  delayMicroseconds(2);              // Aguarda 2 microssegundos para estabilizar o sinal

  digitalWrite(triggerP, HIGH);      // Envia um impulso ultrassónico pelo pino Trigger
  delayMicroseconds(10);             // Mantém o impulso ativo durante 10 microssegundos
  digitalWrite(triggerP, LOW);       // Desliga o impulso do Trigger

  long duracao = pulseIn(echoP, HIGH, 30000); // Mede o tempo que o sinal demora a regressar ao pino Echo, com limite de 30000 microssegundos

  return 0.01723 * duracao;          // Converte o tempo medido em distância aproximada em centímetros
}

// Função responsável por fechar a tampa
void fecharTampa() {
  for (pos = 90; pos >= 0; pos--) {  // Faz o servo mover-se gradualmente dos 90 graus até aos 0 graus
    servo_9.write(pos);              // Envia ao servo a posição atual
    delay(15);                       // Pequeno atraso para tornar o movimento mais suave
  }
}

void setup() {
  Serial.begin(9600);                // Inicia a comunicação série a 9600 bps

  pinMode(pinoTrigger, OUTPUT);      // Define o pino Trigger como saída
  pinMode(pinoEcho, INPUT);          // Define o pino Echo como entrada

  pinMode(botaoFechar, INPUT_PULLUP); // Define o botão como entrada com resistência interna pull-up ativada

  servo_9.attach(9, 500, 2500);      // Liga o servomotor ao pino digital 9 e define os limites do sinal PWM
  servo_9.write(0);                  // Coloca o servo na posição inicial de 0 graus, ou seja, tampa fechada

  delay(1000);                       // Aguarda 1 segundo antes de iniciar o funcionamento principal
}

void loop() {

  // Verifica se o botão de fecho foi pressionado
  if (digitalRead(botaoFechar) == LOW) { // Como o botão usa INPUT_PULLUP, LOW significa botão pressionado
    fecharTampa();                       // Fecha imediatamente a tampa
    return;                              // Interrompe o ciclo atual do loop
  }

  float distanciaEmCms = lerDistanciaEmCms(pinoTrigger, pinoEcho); // Lê a distância medida pelo sensor ultrassónico

  // Verifica se foi detetada uma mão ou objeto a 10 cm ou menos
  if (distanciaEmCms <= 10 && distanciaEmCms > 1) { // A condição > 1 evita leituras inválidas ou demasiado próximas

    // Abertura da tampa
    for (pos = 0; pos <= 90; pos++) {  // Faz o servo mover-se gradualmente dos 0 graus até aos 90 graus
      servo_9.write(pos);              // Envia ao servo a posição atual
      delay(15);                       // Pequeno atraso para suavizar o movimento

      // Verifica o botão durante o movimento de abertura
      if (digitalRead(botaoFechar) == LOW) { // Se o botão for pressionado durante a abertura
        fecharTampa();                       // Fecha imediatamente a tampa
        return;                              // Interrompe o ciclo atual do loop
      }
    }

    // Início da espera ativa com a tampa aberta
    unsigned long tempoInicial = millis();   // Guarda o instante em que a tampa terminou de abrir

    // Mantém a tampa aberta durante 12 segundos
    while (millis() - tempoInicial < 12000) { // Enquanto ainda não passaram 12000 ms, ou seja, 12 segundos

      // Verifica o botão durante o tempo de espera
      if (digitalRead(botaoFechar) == LOW) { // Se o botão for pressionado durante a espera
        fecharTampa();                       // Fecha imediatamente a tampa
        return;                              // Interrompe o ciclo atual do loop
      }

      float novaDistancia = lerDistanciaEmCms(pinoTrigger, pinoEcho); // Faz uma nova leitura da distância

      // Verifica se a mão voltou a ser detetada durante a espera
      if (novaDistancia <= 10 && novaDistancia > 1) { // Se houver nova deteção a 10 cm ou menos
        tempoInicial = millis();                      // Reinicia a contagem dos 12 segundos
      }

      delay(100);                         // Pequeno atraso entre leituras para evitar medições excessivas
    }

    // Fecho automático da tampa
    fecharTampa();                        // Fecha a tampa quando termina o tempo de espera
  }

  delay(100);                             // Pequeno atraso antes de repetir o ciclo principal
}
