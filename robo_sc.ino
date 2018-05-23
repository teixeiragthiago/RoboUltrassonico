#include <AFMotor.h>
#include <Servo.h>
#include <Ultrasonic.h>

AF_DCMotor motorEsquerdo1(1); 
AF_DCMotor motorEsquerdo2(2); 
AF_DCMotor motorDireito1(3);
AF_DCMotor motorDireito2(4);

#define servo 10
Servo myservo;
int val = 0;

//Definindo portas do sensor ultrassonico
#define trig A1 //definindo trigger na entrada analogica 0
#define echo A0 //definindo echo na entrada analogica 1

//Instanciando objeto do tipo Ultrasonic
Ultrasonic ultrasonic(trig,echo);

//Variaveis globais
float distanciaDireita, distanciaEsquerda;

void ligaMotores();
void desligaMotores();
void controlaServo();
float medirDistancia();
float distanciaCM;

void setup()
{
  // Define a velocidade maxima para os motores 1 e 2
  
  motorEsquerdo1.setSpeed(255); 
  motorEsquerdo2.setSpeed(255); 
  motorDireito1.setSpeed(255); 
  motorDireito2.setSpeed(255);
    
  myservo.attach(servo);
  Serial.begin(9600);
}
 
void loop()
{
  distanciaCM = medirDistancia();
  Serial.begin(9600);
  Serial.print(distanciaCM);
  Serial.println(" Centimetros");
  delay(1000);
}


void controlaServo(){
  myservo.write(160); //virando servo para a esquerda
  delay(2000);
  myservo.write(80);
  delay(2000);    
  myservo.write(0); //virando servo para a direita
  delay(2000);  
  myservo.write(80);
  delay(2000);
}

void ligaMotores(){
  motorEsquerdo1.run(FORWARD); //sentido horario
  motorEsquerdo2.run(FORWARD); //sentido horario
  motorDireito1.run(FORWARD); //sentido anti-horario
  motorDireito2.run(FORWARD); //sentido horario
    
}

void desligaMotores(){
  motorEsquerdo1.run(RELEASE); //desligando motor esquerdo 1
  motorEsquerdo2.run(RELEASE); //desligando motor esquerdo 2 
  motorDireito1.run(RELEASE); //desligando motor direito 1
  motorDireito2.run(RELEASE); //desligando motor esquerdo 2
}

float medirDistancia(){
  float pulso;
  triggerPulso();
  
  pulso = pulseIn(echo, HIGH);

  return (pulso/58.82);
}

void triggerPulso() //gerando o pulso de trigger/gatilho do sensor ultrassonico
{
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW); 
}

