#include <Servo.h>

#define TRIG 10
#define ECHO 11
#define BUZZER 8
#define VelM_DIR 2
#define M_DirA 4
#define M_DirB 3
#define VelM_ESQ 5
#define M_EsqA 6
#define M_EsqB 7


float duracao;
float distancia, distaux; 
int pos = 90;
int vel = 255;

Servo myservo;

void setup()
{
  myservo.attach(9);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(VelM_DIR, OUTPUT);
  pinMode(VelM_ESQ, OUTPUT);
  pinMode(M_DirA, OUTPUT);
  pinMode(M_DirB, OUTPUT);
  pinMode(M_EsqA, OUTPUT);
  pinMode(M_EsqB, OUTPUT);

  analogWrite(VelM_DIR, 0);
  digitalWrite(M_DirA, LOW);
  digitalWrite(M_DirB, LOW);

  analogWrite(VelM_ESQ, 0);
  digitalWrite(M_EsqA, LOW);
  digitalWrite(M_EsqB, LOW);
  
  Serial.begin(9600);
  
}

void andar_reto(void){
  analogWrite(VelM_DIR, vel);
  digitalWrite(M_DirA, LOW);
  digitalWrite(M_DirB, HIGH);

  analogWrite(VelM_ESQ, vel);
  digitalWrite(M_EsqA, HIGH);
  digitalWrite(M_EsqB, LOW);
}

void parar(void){
  analogWrite(VelM_DIR, 0);
  digitalWrite(M_DirA, LOW);
  digitalWrite(M_DirB, LOW);

  analogWrite(VelM_ESQ, 0);
  digitalWrite(M_EsqA, LOW);
  digitalWrite(M_EsqB, LOW);
}

void girar_direita(void){
  parar();
  delay(100);
  analogWrite(VelM_DIR, vel);
  digitalWrite(M_DirA, LOW);
  digitalWrite(M_DirB, LOW);

  analogWrite(VelM_ESQ, vel);
  digitalWrite(M_EsqA, HIGH);
  digitalWrite(M_EsqB, LOW);
}

void girar_esquerda(void){
  parar();
  delay(100);
  analogWrite(VelM_DIR, vel);
  digitalWrite(M_DirA, LOW);
  digitalWrite(M_DirB, HIGH);

  analogWrite(VelM_ESQ, vel);
  digitalWrite(M_EsqA, LOW);
  digitalWrite(M_EsqB, LOW);
}

float guardar_dist(int tmp){
  digitalWrite(TRIG, LOW);
  delay(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10); 
  digitalWrite(TRIG, LOW);
  
  duracao = pulseIn(ECHO, HIGH);
  
  distaux = duracao/58;
  
  Serial.print("cm: ");
  Serial.println(distaux);
  
  delay(tmp);
    
  return distaux;

}
float procurar(int tmp){
  digitalWrite(TRIG, LOW);
  delay(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10); 
  digitalWrite(TRIG, LOW);
  
  duracao = pulseIn(ECHO, HIGH);
  
  distancia = duracao/58;
  
  Serial.print("cm: ");
  Serial.println(distancia);
  
  delay(tmp);
    
  return distancia;
  
}
void olharesquerda()
{
  for (pos = 90; pos <= 180; pos += 1) { 
    myservo.write(pos);             
    delay(15);
  }
  while(1){
    guardar_dist(0);
    delay(200);
    break;
  }
  for (pos = 180; pos >= 90; pos -= 1) { 
    myservo.write(pos);
  }
}
void olhardireita()
{
  for (pos = 90; pos >= 0; pos -= 1) { 
    myservo.write(pos);              
    delay(15);
  }
  while(1){
    guardar_dist(0);
    delay(200);
    break;
  }
  for (pos = 0; pos <= 90; pos += 1) { 
    myservo.write(pos);
  }
}

void piscar_buz2(){
  digitalWrite(BUZZER, HIGH);
  delay(350);
  
  digitalWrite(BUZZER, LOW);
  delay(200);
  
  
  digitalWrite(BUZZER, HIGH);
  delay(350);
  
  digitalWrite(BUZZER, LOW);
}
void piscar_buz3(){
  digitalWrite(BUZZER, HIGH);
  delay(350);
  
  digitalWrite(BUZZER, LOW);
  delay(150);
  
  digitalWrite(BUZZER, HIGH);
  delay(350);
  
  digitalWrite(BUZZER, LOW);
  delay(150);
  
  digitalWrite(BUZZER, HIGH);
  delay(350);
  
  digitalWrite(BUZZER, LOW);
}
void loop()
{
  andar_reto();
  procurar(0);
  if(distancia < 60 && distancia > 0){
    
    parar();
    
    delay(500);
    
    digitalWrite(BUZZER, HIGH);
    delay(1000);
    digitalWrite(BUZZER, LOW);
    
    Serial.println("Parou" );
    
    olharesquerda();
      if(distaux > 60 || distaux < 0){
        piscar_buz2();
        delay(500);
        
        Serial.println("Ta andando esquerda Sinba" );
        girar_esquerda();
        delay(160);
      
      }else{
        olhardireita();
        if(distaux > 60 || distaux < 0){
          piscar_buz3();
          delay(500);
          
          Serial.println("Ta andando direita Sinba" );
          girar_direita();
          delay(250);
          
        }else{
          Serial.println("so de costa");
          girar_direita();
          delay(530);
             }
          } 
  }
}
