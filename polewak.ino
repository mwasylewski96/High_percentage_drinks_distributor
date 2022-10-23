
//______________________________________________________WYŚWIETLACZ BIBIBLIOTEKI ORAZ ZROBIENIE ZNAKÓW_____________________________________________________________________________________________________________________________
#include <Wire.h>
#include <LiquidCrystal_I2C.h> // include LiquidCrystal_I2C library.
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); // Set the LCD I2C address
byte lewasciana[8] = {//nazwa znaku
//wejdz na strone i stworz znak, (zielone lampki beda zgaszone a ciemne zapalone  http://omerk.github.io/lcdchargen/
//przekopiuj te liczby
//__________________________________________________ZROBIENIE WSZYSTKICH ZNAKÓW DLA NAPEŁNIAJĄCEGO SIĘ KIELISZKA____________________________________________
0b10000,
  0b10000,
  0b10000,
  0b10000,
  0b10000,
  0b10000,
  0b10000,
  0b10000
};
byte lewadolnasciana[8] = {
0b01000,
  0b01000,
  0b01000,
  0b01000,
  0b01000,
  0b01000,
  0b01000,
  0b01111
};
byte dol[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b11111
};
byte prawadolnasciana[8] = {
  0b00010,
  0b00010,
  0b00010,
  0b00010,
  0b00010,
  0b00010,
  0b00010,
  0b11110
};
byte prawasciana[8] = {
  0b00001,
  0b00001,
  0b00001,
  0b00001,
  0b00001,
  0b00001,
  0b00001,
  0b00001
};
byte zalane[8]{
0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111
};
byte zalanezlewej[8] = {
  0b01111,
  0b01111,
  0b01111,
  0b01111,
  0b01111,
  0b01111,
  0b01111,
  0b01111
};
byte zalanezprawej[8] = {
  0b11110,
  0b11110,
  0b11110,
  0b11110,
  0b11110,
  0b11110,
  0b11110,
  0b11110
};

//____________________________________________________________________PRZYCISKI ITD__________________________________________________________________________________
//inicjuję kolumny
int kol1=3;
int kol2=6;
int kol3=5;
//inicjuję wiersze
int wier1=2;
int wier2=4;
//żaden przycisk nie jest domyślnie wciśnięty
int push1 = 0;
int push2 = 0;
int push3 = 0;
int push4 = 0;
int push5 = 0;

// inicjuję piny do ustawiania stanu niskiego na przekaźnikach
int przekaznik1 = 7;
int przekaznik2 = 8;
int przekaznik3 = 9;
int przekaznik4 = 10;
int przekaznik5 = 11;

int buttons = 12;



//ZMIENNA DELAY I ZMIENNA safe (dodana aby pozbyć się błędów związanych z zasilaniem układu i samoczynnym włączaniem się przekazników)
int DELAY1 = 6000;
int DELAY2 = 3000;
int DELAY5 = 1000;
int DELAY3 = 50;
int DELAY4 = 500;

int safe =500;


void setup(){
  
 Serial.begin(9600); 
 //____________________________________________________ZAINICJOWANIE ORAZ TO CO WYŚWIETLACZ WYŚWIETLA NA POCZĄTKU______________________________________________________________________________
 //__________________________________________URUCHOMIENIE WYŚWIETLACZA, CZYSZCZENIE ORAZ WGRANIE DO WYŚWIETLACZA TYCH ZNAKÓW____________________________ 
 lcd.begin(20,4);
 lcd.clear();
 lcd.createChar (0, lewasciana);
 lcd.createChar (1, lewadolnasciana);
 lcd.createChar (2, dol);
 lcd.createChar (3, prawadolnasciana);
 lcd.createChar (4, prawasciana);
 lcd.createChar (5, zalane);
 lcd.createChar (6, zalanezlewej);
 lcd.createChar (7, zalanezprawej);
//_____________________________________________________________________________________________________________________

//piny wierszy ustawiam jako output
pinMode(2, OUTPUT);
pinMode(4, OUTPUT);
//piny kolumn ustawiam jako input pullup
pinMode(3, INPUT_PULLUP);
pinMode(5, INPUT_PULLUP);
pinMode(6, INPUT_PULLUP);

//ustawiam wszystkie piny przekaznikow jako OUTPUT http://www.arduino.cc/en/Guide/Troubleshooting#upload
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT); //PODŚWIETLENIE PRZYCISKOW

  
  //ustawiam piny przekaznikow na stan wysoki
  digitalWrite(przekaznik1, HIGH);
  digitalWrite(przekaznik2, HIGH);
  digitalWrite(przekaznik3, HIGH);
  digitalWrite(przekaznik4, HIGH);
  digitalWrite(przekaznik5, HIGH);
  
  digitalWrite(buttons, LOW); //PRZYCISKI



  
}

//----------------------------------------------------PETLA NIESKONCZONA
void loop(){

  pocz();
  //pierwszy wiersz low, każdy pozostały high (ja używam tylko dwóch)
  digitalWrite(wier1, LOW);
  digitalWrite(wier2, HIGH);
  
  //....:::PIERWSZY PRZYCISK:::...
   int buttonState1 = digitalRead(kol1);
 
 
 if(buttonState1 == LOW && push1 == 0){
 Serial.print(1);
 
 digitalWrite(buttons, HIGH);
 kiel1();
 blinks();
 push1 = 1;
 }
 else if (buttonState1 == LOW && push1 == 1){
 push1 = 1;
 }
 else{
   push1 = 0; 
 }

//....:::DRUGI PRZYCISK:::...
  int buttonState2 = digitalRead(kol2);
 
 
 if(buttonState2 == LOW && push2 == 0){
 Serial.print(2);

     digitalWrite(buttons, HIGH); 
     kiel2();
 blinks();
 push2 = 1;
 }
 else if (buttonState2 == LOW && push2 == 1){
 push2 = 1;
 }
 else{
   push2 = 0; 
 }
  
 //....:::TRZECI PRZYCISK:::...
 int buttonState3 = digitalRead(kol3);
 
 
 if(buttonState3 == LOW && push3 == 0){
 Serial.print(3);

     digitalWrite(buttons, HIGH);   
     kiel3();
 blinks();
 push3 = 1;
 }
 else if (buttonState3 == LOW && push3 == 1){
 push3 = 1;
 }
 else{
   push3 = 0; 
 }
  //TERAZ DRUGI WIERSZ NA LOW A WSZYSTKIE POZOSTAŁE NA HIGH (ja używam tylko dwóch pierwszych wierszy)
  digitalWrite(wier1, HIGH);
  digitalWrite(wier2, LOW);
  
 //....:::CZWARTY PRZYCISK:::...
 int buttonState4 = digitalRead(kol1);
 
 
 if(buttonState4 == LOW && push4 == 0){
 Serial.print(4);
   
     digitalWrite(buttons, HIGH);
     kiel4();
 blinks();
 push4 = 1;
 }
 else if (buttonState4 == LOW && push4 == 1){
 push4 = 1;
 }
 else{
   push4 = 0; 
 }
  //....:::PIATY PRZYCISK:::...
  int buttonState5 = digitalRead(kol2);
 
 
 if(buttonState5 == LOW && push5 == 0){
 Serial.print(5);

     digitalWrite(buttons, HIGH);  
     kiel5();
 blinks();
 push5 = 1;
 }
 else if (buttonState5 == LOW && push5 == 1){
 push5 = 1;
 }
 else{
   push5 = 0; 
 }
  
}
//---------------------------------------------------KONIEC PETLI NIESKONCZONEJ

//----------------MOJE FUNKCJE--------------------------------------------------

//-JEDEN KIELISZEK-
void kiel1(){
  kieliszek1napisy();
  emptyone();
  digitalWrite(przekaznik1, LOW);
  delay(2000);
  oneone();
   delay(2000);
  onetwo();
   delay(1000);
  onethree();
  delay(1000);
  digitalWrite(przekaznik1, HIGH);
  gotowe();
  delay(safe);
}

//-DWA KIELISZKI
void kiel2(){
  kieliszek2napisy();
  emptytwo();
  digitalWrite(przekaznik1, LOW);
  digitalWrite(przekaznik2, LOW);
  delay(3000);
  twoone();
  delay(3000);
  twotwo();
  digitalWrite(przekaznik1, HIGH);
  delay(2000);
  twothree();
   delay(5000);
  digitalWrite(przekaznik2, HIGH);
  gotowe();
  delay(safe);
}

//TRZY KIELISZKI
void kiel3(){
  kieliszek3napisy();
  emptythree();
  digitalWrite(przekaznik1, LOW);
  digitalWrite(przekaznik2, LOW);
  digitalWrite(przekaznik3, LOW);
  delay(1000);
  threeone();
  delay(5000);
  threetwo();
  digitalWrite(przekaznik1, HIGH);
  delay(3000);
  threethree();
  delay(1500);
  
  delay(900); 
  digitalWrite(przekaznik3, HIGH);
  delay(6000);
  digitalWrite(przekaznik2, HIGH);
  threethree();
  delay(1000);
  gotowe();
  delay(safe);
  }

//CZTERY KIELISZKI
void kiel4(){
  kieliszek4napisy();
  emptyfour();
  digitalWrite(przekaznik1, LOW);
  digitalWrite(przekaznik2, LOW);
  digitalWrite(przekaznik3, LOW);
  digitalWrite(przekaznik4, LOW);
  delay(3100);
  fourone();
  delay(3000);
  digitalWrite(przekaznik1, HIGH);
  fourtwo();
  delay(4000);
  
  delay(1660);
  digitalWrite(przekaznik3, HIGH);
  fourthree();
  delay(3000);
  digitalWrite(przekaznik4, HIGH);
  delay(4000);
  digitalWrite(przekaznik2, HIGH);
  gotowe();
  delay(safe);
  }

//PIĘĆ KIELISZKÓW
void kiel5(){
  kieliszek5napisy();
  emptyfive();
  digitalWrite(przekaznik1, LOW);
  digitalWrite(przekaznik2, LOW);
  digitalWrite(przekaznik3, LOW);
  digitalWrite(przekaznik4, LOW);
  digitalWrite(przekaznik5, LOW);
  delay(3000);
  fiveone();
  delay(4000);
  digitalWrite(przekaznik1, HIGH);
  fivetwo();
  delay(4400);
  
  delay(1000);
  digitalWrite(przekaznik5, HIGH);
  fivethree();
  delay(1000);
  digitalWrite(przekaznik3, HIGH);
  delay(3500);
  digitalWrite(przekaznik4, HIGH);
  digitalWrite(przekaznik2, HIGH);
  gotowe();
  delay(safe);
}

  //MRUGNIĘCIA
void blinks(){
  digitalWrite(buttons, HIGH);
  delay(400);

  digitalWrite(buttons, LOW);
  delay(400);

  digitalWrite(buttons, HIGH);
  delay(400);

  digitalWrite(buttons, LOW);
   delay(400);
  digitalWrite(buttons, HIGH);
 
  delay(400);
  digitalWrite(buttons, LOW);
}

//POCZĄTEK
void pocz()
{
  
  lcd.setCursor(2,0);
  lcd.print("WASYLGARAGE WITA");
  
  lcd.setCursor(0,2);
  lcd.print("Wybierz liczbe");
  
  lcd.setCursor(14,3);
  lcd.print("SHOTOW");
 
}

void gotowe()
{
  lcd.clear();
  lcd.setCursor(6,1);
  lcd.print("GOTOWE!!!");
  delay(2000);
  lcd.clear();
}


//_________________________________________________________________________________FUNKCJE WYSWIETLACZ KIELISZKI NAPISY___PODFUNKCJE___
//--------------------------------------------WSZYSTKO DO 1 Kieliszka---------------POCZĄTEK_______________

//...::::PIERWSZY KIELISZEK::::....
void emptyone()
{
  //----------------------Rysuje pustego shota-POCZĄTEK--------------------------
 //-----Rysuje lewą ścianę-POCZĄTEK----
lcd.clear();
for(int i=0; i<=2; i=i+1)
{
lcd.setCursor(8,i);
lcd.print(char(0));
}
//-----KONIEC Rysowania lewej ściany---

//-----Rysuje dolną ścianę-POCZĄTEK----
lcd.setCursor(8,3);
lcd.print(char(1));
lcd.print(char(2));
lcd.print(char(2));
lcd.print(char(3));
//-----KONIEC Rysowania dolnej ściany--

//-----Rysuje prawą ścianę-POCZĄTEK----
for(int i=0; i<=2; i=i+1)
{
lcd.setCursor(11,i);
lcd.print(char(4));
}
//-----KONIEC Rysowania prawej ściany--

//----------------------KONIEC Rysowania pustego shota------------------------
  }
 void oneone()
 {
lcd.setCursor(8,3);
lcd.print(char(6));
lcd.print(char(5));
lcd.print(char(5));
lcd.print(char(7));}
 void onetwo()
 {
lcd.setCursor(8,2);
for(int i=0; i<=3; i++)
{
lcd.print(char(5));
}
 }
 void onethree()
 {
lcd.setCursor(8,1);
 for(int i=0; i<=3; i++)
{
lcd.print(char(5));
}}

//--NAPISY
void kieliszek1napisy()
{
 lcd.clear();
 lcd.setCursor(3,0);
 lcd.print("Dlaczego tylko");
 delay(1000);
 lcd.setCursor(5,2);
 lcd.print("JEDEN?? :(");
 delay(1000);
 lcd.clear();
  
}

//--------------------------------------------WSZYSTKO DO 1 Kieliszka---------------KONIEC----------------- 



//--------------------------------------------WSZYSTKO DO 2 Kieliszków---------------POCZĄTEK__________________________________________________________

void emptytwo() {
 //---------------------------------------------------Rysuje puste shoty-POCZĄTEK--------------------------
 //-----Rysuje lewą ścianę każdego shota-POCZĄTEK----
lcd.clear();
for (int i=0; i<=2; i++)
{
lcd.setCursor(5,i);
lcd.print(char(0));
lcd.setCursor(11,i);
lcd.print(char(0));
}
//-----Rysuje lewą ścianę każdego shota-KONIEC----

//-----Rysuje dolną ścianę każdego shota-POCZĄTEK----
for(int i=5; i<=11; i=i+6)
{
lcd.setCursor(i,3);
lcd.print(char(1));
lcd.print(char(2));
lcd.print(char(2));
lcd.print(char(3));
}
//-----Rysuje dolną ścianę każdego shota-KONIEC----


//-----Rysuje prawą ścianę każdego shota-POCZĄTEK----
for (int i=0; i<=2; i++)
{
lcd.setCursor(8,i);
lcd.print(char(4));
lcd.setCursor(14,i);
lcd.print(char(4));
}
//-----Rysuje prawą ścianę każdego shota-KONIEC----

//----------------------KONIEC Rysowania pustych shotów---------------------------------------------------
}

void twoone() {
  //teraz pierwsze wypelnienie-Początek
for(int i=5; i<=11; i=i+6)
{
lcd.setCursor(i,3);
lcd.print(char(6));
lcd.print(char(5));
lcd.print(char(5));
lcd.print(char(7));
}
//teraz pierwsze wypelnienie-KONIEC
}
void twotwo() {
  //teraz drugie wypelnienie-Początek
for(int i=5; i<=11; i=i+6)
{
lcd.setCursor(i,2);
for(int j=0; j<=3; j++)
{
lcd.print(char(5));
}}
}
void twothree() {
  //teraz trzecie wypelnienie-Początek
for(int i=5; i<=11; i=i+6)
{
lcd.setCursor(i,1);
for(int j=0; j<=3; j++)
{
lcd.print(char(5));
}}
//teraz trzecie wypelnienie-Koniec  
}
//--NAPISY
void kieliszek2napisy()
{
 lcd.clear();
 lcd.setCursor(3,0);
 lcd.print("Troche lepiej");
 delay(500);
 lcd.setCursor(4,2);
 lcd.print("ale i tak");
 delay(500);
 lcd.setCursor(14,3);
 lcd.print("MALO");
 delay(1500);
  
}

//--------------------------------------------WSZYSTKO DO 2 Kieliszków---------------KONIEC__________________________________________________________

//--------------------------------------------WSZYSTKO DO 3 Kieliszków---------------POCZĄTEK__________________________________________________________
void emptythree() {
 //---------------------------------------------------Rysuje puste shoty-POCZĄTEK--------------------------
 //-----Rysuje lewą ścianę każdego shota-POCZĄTEK----
lcd.clear();
for(int i=0; i<=2; i++)
{
lcd.setCursor(2,i);
lcd.print(char(0));
lcd.setCursor(8,i);
lcd.print(char(0));
lcd.setCursor(14,i);
lcd.print(char(0));
}
//-----Rysuje lewą ścianę każdego shota-KONIEC----

//-----Rysuje dolną ścianę każdego shota-POCZĄTEK----
for(int i=2; i<=14; i=i+6)
{
lcd.setCursor(i,3);
lcd.print(char(1));
lcd.print(char(2));
lcd.print(char(2));
lcd.print(char(3));
}
//-----Rysuje dolną ścianę każdego shota-KONIEC----


//-----Rysuje prawą ścianę każdego shota-POCZĄTEK----
for(int i=0; i<=2; i++)
{
lcd.setCursor(5,i);
lcd.print(char(4));
lcd.setCursor(11,i);
lcd.print(char(4));
lcd.setCursor(17,i);
lcd.print(char(4));
}
//-----Rysuje prawą ścianę każdego shota-KONIEC----

//----------------------KONIEC Rysowania pustych shotów---------------------------------------------------
}

void threeone(){
  //teraz pierwsze wypelnienie-Początek
for(int i=2; i<=14; i=i+6)
{
lcd.setCursor(i,3);
lcd.print(char(6));
lcd.print(char(5));
lcd.print(char(5));
lcd.print(char(7));
}
//teraz pierwsze wypelnienie-KONIEC
  }
 void threetwo(){
 //teraz drugie wypelnienie-Początek
for(int i=2; i<=14; i=i+6)
{
lcd.setCursor(i,2);
for(int i=0; i<=3; i++)
{
lcd.print(char(5));
}}
//teraz drugie wypelnienie-KONIEC
  }
void threethree(){
//teraz trzecie wypelnienie-Początek
for(int i=2; i<=14; i=i+6)
{
lcd.setCursor(i,1);
for(int i=0; i<=3; i++)
{
lcd.print(char(5));
}}
}
//teraz trzecie wypelnienie-Koniec
void kieliszek3napisy()
{
 lcd.clear();
 lcd.setCursor(2,0);
 lcd.print("Nadal jestes");
 delay(1000);
 lcd.setCursor(11,1);
 lcd.print("SLABIUTKI");
 delay(1000);
 lcd.setCursor(2,2);
 lcd.print("ale niech ci");
 delay(500);
 lcd.setCursor(14,3);
 lcd.print("bedzie");
 delay(500);  
}
//--------------------------------------------WSZYSTKO DO 3 Kieliszków---------------KONIEC__________________________________________________________
//--------------------------------------------WSZYSTKO DO 4 Kieliszków---------------POCZĄTEK__________________________________________________________
void emptyfour() {
 //---------------------------------------------------Rysuje puste shoty-POCZĄTEK--------------------------
 //-----Rysuje lewą ścianę każdego shota-POCZĄTEK----
lcd.clear();
for(int i=0; i<=2; i++)
{
lcd.setCursor(0,i);
lcd.print(char(0));
lcd.setCursor(5,i);
lcd.print(char(0));
lcd.setCursor(11,i);
lcd.print(char(0));
lcd.setCursor(16,i);
lcd.print(char(0));
}
//-----Rysuje lewą ścianę każdego shota-KONIEC----

//-----Rysuje dolną ścianę każdego shota-POCZĄTEK----
for(int i=0; i<=16; i=i+11)
{
lcd.setCursor(i,3);
lcd.print(char(1));
lcd.print(char(2));
lcd.print(char(2));
lcd.print(char(3));
lcd.setCursor(i+5,3);
lcd.print(char(1));
lcd.print(char(2));
lcd.print(char(2));
lcd.print(char(3));
}
//-----Rysuje dolną ścianę każdego shota-KONIEC----


//-----Rysuje prawą ścianę każdego shota-POCZĄTEK----
for(int i=0; i<=2; i++)
{
lcd.setCursor(3,i);
lcd.print(char(4));
lcd.setCursor(8,i);
lcd.print(char(4));
lcd.setCursor(14,i);
lcd.print(char(4));
lcd.setCursor(19,i);
lcd.print(char(4));
}
//-----Rysuje prawą ścianę każdego shota-KONIEC----

//----------------------KONIEC Rysowania pustych shotów---------------------------------------------------
}
void fourone(){
//teraz pierwsze wypelnienie-Początek
for(int i=0; i<=16; i=i+11)
{
lcd.setCursor(i,3);
lcd.print(char(6));
lcd.print(char(5));
lcd.print(char(5));
lcd.print(char(7));
lcd.setCursor(i+5,3);
lcd.print(char(6));
lcd.print(char(5));
lcd.print(char(5));
lcd.print(char(7));
}
//teraz pierwsze wypelnienie-KONIEC
}

void fourtwo() {
  //teraz drugie wypelnienie-Początek
for(int i=0; i<=16; i=i+11)
{
lcd.setCursor(i,2);
for(int i=0; i<=3; i++)
{
lcd.print(char(5));
}
lcd.setCursor(i+5,2);
for(int i=0; i<=3; i++)
{
lcd.print(char(5));
}
}
//teraz drugie wypelnienie-KONIEC
}

void fourthree() {
//teraz trzecie wypelnienie-Początek
for(int i=0; i<=16; i=i+11)
{
lcd.setCursor(i,1);
for(int i=0; i<=3; i++)
{
lcd.print(char(5));
}
lcd.setCursor(i+5,1);
for(int i=0; i<=3; i++)
{
lcd.print(char(5));
}
}
}
//teraz trzecie wypelnienie-Koniec

void kieliszek4napisy()
{
 lcd.clear();
 lcd.setCursor(2,0);
 lcd.print("NARESZCZIE!!!");
 delay(1000);
 lcd.setCursor(11,1);
 lcd.print("jakis");
 delay(500);
 lcd.setCursor(2,2);
 lcd.print("dobry!!!");
 delay(500);
 lcd.setCursor(11,3);
 lcd.print("ZIOMECZEK");
 delay(1000);  
}
//--------------------------------------------WSZYSTKO DO 4 Kieliszków---------------KONIEC__________________________________________________________


//--------------------------------------------WSZYSTKO DO 5 Kieliszków---------------POCZĄTEK__________________________________________________________
void emptyfive() {
//---------------------------------------------------Rysuje puste shoty-POCZĄTEK--------------------------
 //-----Rysuje lewą ścianę każdego shota-POCZĄTEK----
lcd.clear();
for(int i=0; i<=2; i++)
{
lcd.setCursor(0,i);
lcd.print(char(0));
lcd.setCursor(4,i);
lcd.print(char(0));
lcd.setCursor(8,i);
lcd.print(char(0));
lcd.setCursor(12,i);
lcd.print(char(0));
lcd.setCursor(16,i);
lcd.print(char(0));
}
//-----Rysuje lewą ścianę każdego shota-KONIEC----

//-----Rysuje dolną ścianę każdego shota-POCZĄTEK----
for(int i=0; i<=16; i=i+4)
{
lcd.setCursor(i,3);
lcd.print(char(1));
lcd.print(char(2));
lcd.print(char(2));
lcd.print(char(3));
}
//-----Rysuje dolną ścianę każdego shota-KONIEC----


//-----Rysuje prawą ścianę każdego shota-POCZĄTEK----
for(int i=0; i<=2; i++)
{
lcd.setCursor(3,i);
lcd.print(char(4));
lcd.setCursor(7,i);
lcd.print(char(4));
lcd.setCursor(11,i);
lcd.print(char(4));
lcd.setCursor(15,i);
lcd.print(char(4));
lcd.setCursor(19,i);
lcd.print(char(4));
}
//-----Rysuje prawą ścianę każdego shota-KONIEC----

//----------------------KONIEC Rysowania pustych shotów---------------------------------------------------

}

void fiveone()
{
  //teraz pierwsze wypelnienie-Początek
for(int i=0; i<=16; i=i+4)
{
lcd.setCursor(i,3);
lcd.print(char(6));
lcd.print(char(5));
lcd.print(char(5));
lcd.print(char(7));
}

//teraz pierwsze wypelnienie-KONIEC
}

void fivetwo()
{
//teraz drugie wypelnienie-Początek
for(int i=0; i<=16; i=i+4)
{
lcd.setCursor(i,2);
for(int i=0; i<=3; i++)
{
lcd.print(char(5));
}}
//teraz drugie wypelnienie-KONIEC

}

void fivethree(){
  //teraz trzecie wypelnienie-Początek
for(int i=0; i<=16; i=i+4)
{
lcd.setCursor(i,1);
for(int i=0; i<=3; i++)
{
lcd.print(char(5));
}}
//teraz trzecie wypelnienie-Koniec
  }

void kieliszek5napisy()
{
 lcd.clear();
 lcd.setCursor(2,0);
 lcd.print("DOOBRZE!!");
 delay(1000);
 lcd.setCursor(6,1);
 lcd.print("Tak Trzymaj!!!");
 delay(1000);
 lcd.setCursor(2,2);
 lcd.print("Wasyl bedzie");
 delay(500);
 lcd.setCursor(10,3);
 lcd.print("zadowolony");
 delay(1000);  
}  
 //--------------------------------------------WSZYSTKO DO 5 Kieliszków---------------KONIEC__________________________________________________________
