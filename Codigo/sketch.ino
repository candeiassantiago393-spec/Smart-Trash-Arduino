#include <Servo.h> 

Servo servo_9;  
int pos = 0;

#define pinoTrigger 3
#define pinoEcho 5
#define botaoFechar 12   

float lerDistanciaEmCms(int triggerP, int echoP) {
  digitalWrite(triggerP, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerP, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerP, LOW);
  
  long duracao = pulseIn(echoP, HIGH, 30000); 
  return 0.01723 * duracao;
}

void fecharTampa() {
  for (pos = 90; pos >= 0; pos--) { 
    servo_9.write(pos);
    delay(15); 
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(pinoTrigger, OUTPUT); 
  pinMode(pinoEcho, INPUT);

  pinMode(botaoFechar, INPUT_PULLUP); 
  
  servo_9.attach(9, 500, 2500);
  servo_9.write(0); 
  delay(1000); 
}

void loop() {

  if (digitalRead(botaoFechar) == LOW) {
    fecharTampa();
    return; 
  }

  float distanciaEmCms = lerDistanciaEmCms(pinoTrigger, pinoEcho);

  if (distanciaEmCms <= 10 && distanciaEmCms > 1) {
    // ABRIR
    for (pos = 0; pos <= 90; pos++) { 
      servo_9.write(pos);
      delay(15);

      // verifica botão DURANTE abertura
      if (digitalRead(botaoFechar) == LOW) {
        fecharTampa();
        return;
      }
    }
    
    // ESPERA ATIVA
    unsigned long tempoInicial = millis();
    while (millis() - tempoInicial < 12000) {

      // verifica botão DURANTE espera
      if (digitalRead(botaoFechar) == LOW) {
        fecharTampa();
        return;
      }

      float novaDistancia = lerDistanciaEmCms(pinoTrigger, pinoEcho);
      
      if (novaDistancia <= 10 && novaDistancia > 1) {
        tempoInicial = millis(); 
      }

      delay(100);
    }
    
    // FECHAR
    fecharTampa();
  }

  delay(100); 
}