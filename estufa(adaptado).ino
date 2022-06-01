#include <Servo.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

//Declaração de variáveis
int TMP;
float VTMP;
Servo servo;
const int lamp = 9;
int sensorReading = 0;
int posicao = 0;
int sensor = A2;
int botao = 0;
#define BT1 6
#define temperatura A3

//Inicialçização LCD
void setup() {
  lcd.begin(16, 2);
  lcd.print("Grupo 8 - 2022/1");
  pinMode (9, OUTPUT);
  pinMode (8, OUTPUT);
  pinMode(sensor, INPUT);
  servo.attach(7);
  servo.write(95);
  pinMode(BT1, INPUT);
}

//
void loop() {
 lcd.setCursor(0, 1);
 temp ();
 LCD ();
 luz ();
 servom ();
 botao1 ();
}

//Funções
void temp() {  //Sensor de temperatura (conversão para leitura)
 VTMP = analogRead (temperatura)*5.0 / 1023;
 TMP = round ((VTMP - 0.5)*100);   
}

void LCD() {  //Funcionamento do LCD
  Serial.println(digitalRead(BT1));
  if (botao == 1) {
  lcd.setCursor (0,1);
  lcd.print ("SEM AGUA         ");
  tone(8, 300);
  } else if (TMP < 18 || TMP > 28){
  lcd.setCursor (0,1);
  lcd.print ("ERRO TEMPERATURA");
  tone(8, 440);
  } else if (posicao < 90){
  lcd.print("IRRIGANDO...     ");
  noTone (8);
  } else {
  lcd.setCursor (0,1);
  lcd.print("TUDO CERTO      ");
  noTone (8);
  }
}  
void luz() {  //Lâmpada
  digitalWrite(lamp, HIGH);
}

void servom() {  //Funcionamento do servo motor (torneira)
  if (analogRead(sensor) > 500){
  	posicao = 0;
  	servo.write(posicao);
  } else {
  	posicao = 95;
  	servo.write(posicao);
  }
} 

void botao1() {
 if (digitalRead(BT1) == HIGH && botao == 0) {
   botao = 1;
   delay(500);
 } else if (digitalRead(BT1) == HIGH && botao == 1) {
   botao = 0; 
   delay(500);
 }
}