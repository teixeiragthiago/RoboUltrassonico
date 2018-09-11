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
float distanciaDireita, distanciaEsquerda, distanciaFrontal;
float microsec;
float distanciaCm = 0;

void moverFrente();
void desligaMotores();
void virarDireita();
void virarEsquerda();
void decisao();
void virarAoRedor();

float medirDistancia();
float distanciaCM;

void setup()
{
  //Definindo pinos echo e trigger
  pinMode(echo, INPUT); //echo como entrada
  pinMode(trig, OUTPUT); //trig como saida
  // Define a velocidade para os motores
  motorEsquerdo1.setSpeed(110); 
  motorEsquerdo2.setSpeed(110); 
  motorDireito1.setSpeed(110); 
  motorDireito2.setSpeed(110);
  myservo.attach(servo);
  digitalWrite(trig, LOW);
  myservo.write(80);
  delay(500);
}
 
void loop()
{
  moverFrente();
  distanciaCM = medirDistancia();
  if(distanciaCM < 15)
  {
    decisao();
  }
  delay(100);
   
}

float medirDistancia(){
  
  microsec = ultrasonic.timing();
  distanciaCm = ultrasonic.convert(microsec, Ultrasonic::CM);
  
  return distanciaCm;
  
}

void decisao()
{  
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
     delay(500);
     virarDireita();
     delay(1000);
     moverFrente();
   }
   else
   {
     moverTras();
     delay(500);
     virarEsquerda();
     delay(1000);
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
  delay(1000);
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
  delay(1000);
  motorEsquerdo1.run(FORWARD);
  motorEsquerdo2.run(FORWARD);
  motorDireito1.run(FORWARD);
  motorDireito2.run(FORWARD);
  
}

void virarAoRedor()
{
  motorEsquerdo1.run(FORWARD);
  motorEsquerdo2.run(FORWARD);
  motorDireito1.run(BACKWARD);
  motorDireito2.run(BACKWARD);
  delay(1700);
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



