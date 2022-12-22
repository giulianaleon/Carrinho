#include <Ultrasonic.h>
#include <Servo.h>

  const int motorA1 = 9;     //ESQUERDA
  const int motorA2 = 3;
  const int motorB1 = 11;    //DIREITA
  const int motorB2 = 10;
  const int trig = 41;      //SENSOR
  const int echo = 43;     //SENSOR

  Ultrasonic ultrasonic(trig,echo);
  Servo servoSensor;   //Objeto criado para controlar o servo motor

  int distanciaD;
  int distanciaE;
  float distancia;

int Obstaculo(void){        //Função para procurar obstaculo
  float cm = 0;
  float duracao = 0;

  digitalWrite(trig, LOW);           //não vai enviar som
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);         //envia som  
  delayMicroseconds(10);
  digitalWrite(trig, LOW);         //espera o som enviado volta
  duracao = pulseIn(echo, HIGH);   //duração em tempo do retorno do som
  cm = (duracao / 58.8);
  return cm;
}

void setup() {
  Serial.begin(9600);    //Inicia a comunicação serial em 9600 bits

  servoSensor.attach(6); 
  pinMode(trig, OUTPUT);  //Saída
  pinMode(echo, INPUT);   //Entrada
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);
}

void loop() {
  distancia = Obstaculo();    //Mede a distancia
  delay(10);
  Serial.print(distancia);
  if(distancia > 15){        //Se a distancia for maior que 15
    frente();
  }else{                     //Se a distancia for menor que 15
    direcao();
  }
}

void direcao(){
  parar();
  servoSensor.write(180);           //Gira o servo em 180
  delay(1000);
  distanciaE = Obstaculo();         //Distancia Esquerda
  delay(500);
  servoSensor.write(0);             //Gira em 0
  delay(500);
  distanciaD = Obstaculo();
  delay(500);
  servoSensor.write(90);            //Volta o sensor para 90
  delay(500);
  compararDistancias();
}

void compararDistancias(){
  if(distanciaD > distanciaE){        //Se a distancia D é maior
    direita();
  }else if(distanciaE > distanciaD){   //Se a distancia E é maior
    esquerda();
  }
}

void frente(){
  digitalWrite(motorA1, LOW); 
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, HIGH);
}

void esquerda(){
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2,LOW);
  delay(1000);
}

void direita(){
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2,LOW);
  delay(1000);
}

void parar(){
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, LOW);
  delay(1000);
}
