#include <Servo.h> // inclui a biblioteca do servo

// 180 MÁXIMO horizontal
Servo horizontal; // servo na horizontal 
int servoh = 180;   // 90;     // mantém o servo na horizontal

int servohLimitHigh = 180;
int servohLimitLow = 0;

// 65 graus MÁXIMO
Servo vertical;   // vertical servo 
int servov = 45;    //   90;     // mantém o servo na vertical

int servovLimitHigh = 100;
int servovLimitLow = 10;


// conecções pin do LDR
//  nome = analogpin;
int ldrlt = 1; //LDR em cima / esquerda - INFERIOR ESQUERDA   
int ldrrt = 0; //LDR em cima / direita - INFERIOR DIREITA 
int ldrld = 3; //LDR em baixo / esquerda - SUPERIOR ESQUERDA
int ldrrd = 2; //LDR em baixo / direita - SUPERIOR DIREITA

void setup()
{
  Serial.begin(9600);
// coneccções do servo
// nome.attacht(pin);
  horizontal.attach(9); 
  vertical.attach(10);
  horizontal.write(180);
  vertical.write(45);
  delay(3000);
}

void loop() 
{
  int lt = analogRead(ldrlt); //LDR em cima / esquerda
  int rt = analogRead(ldrrt); //LDR em cima / direita
  int ld = analogRead(ldrld); //LDR em baixo / esquerda
  int rd = analogRead(ldrrd); //LDR em baixo / direita
  
  //int dtime = analogRead(4)/20; // ler potenciometros  
  //int tol = analogRead(5)/4;
  int dtime = 10;
  int tol = 75;
  
  int avt = (lt + rt) / 2; // valor médio de cima
  int avd = (ld + rd) / 2; // valor médio de baixo
  int avl = (lt + ld) / 2; // valor médio da esquerda
  int avr = (rt + rd) / 2; // valor médio da direita

  int dvert = avt - avd; // checa a diferença do de cima com o de baixo
  int dhoriz = avl - avr;// checa a diferença do da esquerda com o da direita
  
  
 /* Serial.print(avt);
  Serial.print(" ");
  Serial.print(avd);
  Serial.print(" ");
  Serial.print(avl);
  Serial.print(" ");
  Serial.print(avr);
  Serial.print("   ");
  Serial.print(dtime);
  Serial.print("   ");
  Serial.print(tol);
  Serial.println(" ");*/
  
    
  if (-1*tol > dvert || dvert > tol) // verifica se a diferença está na tolerância senão muda o ângulo vertical
  {
  if (avt > avd)
  {
    servov = ++servov;
     if (servov > servovLimitHigh) 
     { 
      servov = servovLimitHigh;
     }
  }
  else if (avt < avd)
  {
    servov= --servov;
    if (servov < servovLimitLow)
  {
    servov = servovLimitLow;
  }
  }
  vertical.write(servov);
  }
  
  if (-1*tol > dhoriz || dhoriz > tol) // verifica se a diferença está na tolerância senão muda o ângulo horizontal
  {
  if (avl > avr)
  {
    servoh = --servoh;
    if (servoh < servohLimitLow)
    {
    servoh = servohLimitLow;
    }
  }
  else if (avl < avr)
  {
    servoh = ++servoh;
     if (servoh > servohLimitHigh)
     {
     servoh = servohLimitHigh;
     }
  }
  else if (avl = avr)
  {
    // nada
  }
  horizontal.write(servoh);
  }
   delay(dtime);
Serial.print(servoh);
Serial.print(" ");
Serial.print(servov);
Serial.println("-------------");
}
