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

void moverFrente();
void desligaMotores();
void controlaServo();
void virarDireita();
void virarEsquerda();
void decisao();

float medirDistancia();
float distanciaCM;

void setup()
{
  // Define a velocidade maxima para os motores
  motorEsquerdo1.setSpeed(255); 
  motorEsquerdo2.setSpeed(255); 
  motorDireito1.setSpeed(255); 
  motorDireito2.setSpeed(255);
  myservo.attach(servo);
}
 
void loop()
{
  moverFrente();
  distanciaCM = medirDistancia();
  if(distanciaCM < 20)
  {
    decisao();
  }
  delay(100); 
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

void decisao()
{  
  myservo.write(80);
   desligaMotores();
   delay(500);
   myservo.write(0);
   delay(500);
   distanciaDireita = medirDistancia();
   delay(2000);       
   myservo.write(180);
   delay(500);
   distanciaEsquerda = medirDistancia();
   delay(2000);
   myservo.write(80);
   delay(500);
   
   if(distanciaDireita > distanciaEsquerda)
   {
     moverTras();
     delay(600);
     virarDireita();
     delay(2000);
     moverFrente();
   }
   else
   {
     moverTras();
     delay(600);
     virarEsquerda();
     delay(2000);
     moverFrente(); 
   }
}

void moverFrente(){
  motorEsquerdo1.run(FORWARD); //sentido horario
  motorEsquerdo2.run(FORWARD); //sentido horario
  motorDireito1.run(FORWARD); //sentido  horario
  motorDireito2.run(FORWARD); //sentido horario
}

void moverTras(){
  motorEsquerdo1.run(BACKWARD); //sentido anti-horario
  motorEsquerdo2.run(BACKWARD); //sentido anti-horario
  motorDireito1.run(BACKWARD); //sentido  anti-horario
  motorDireito2.run(BACKWARD); //sentido anti-horario  
}

void virarDireita(){
  motorEsquerdo1.run(FORWARD);
  motorEsquerdo2.run(FORWARD);
  motorDireito1.run(BACKWARD);
  motorDireito2.run(BACKWARD);
  delay(1500);
  motorEsquerdo1.run(FORWARD);
  motorEsquerdo2.run(FORWARD);
  motorDireito1.run(BACKWARD);
  motorDireito2.run(BACKWARD);
}

void virarEsquerda(){
  motorEsquerdo1.run(BACKWARD);
  motorEsquerdo2.run(BACKWARD);
  motorDireito1.run(FORWARD);
  motorDireito2.run(FORWARD);
  delay(1500);
  motorEsquerdo1.run(FORWARD);
  motorEsquerdo2.run(FORWARD);
  motorDireito1.run(FORWARD);
  motorDireito2.run(FORWARD);
  
}

void desligaMotores(){
  motorEsquerdo1.run(RELEASE); //desligando motor esquerdo 1
  motorEsquerdo2.run(RELEASE); //desligando motor esquerdo 2 
  motorDireito1.run(RELEASE); //desligando motor direito 1
  motorDireito2.run(RELEASE); //desligando motor esquerdo 2
}

