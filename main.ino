// C++ code
//
#include <LiquidCrystal.h>

#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define REST      0

// Variáveis globais
int estado = 0;
int score = 0;
int alterado = 0;
int dificuldade = 0;
int musicaSelecionada = 0;

// Sequências musicais
int sequenciaMusica1[11] = {NOTE_FS3, NOTE_CS4, NOTE_CS4, NOTE_CS4, NOTE_GS3, NOTE_FS3, NOTE_A3, NOTE_FS3, NOTE_FS3, NOTE_CS4, NOTE_CS4};
int sequenciaMusica2[11] = {NOTE_A3, NOTE_A3, NOTE_GS3, NOTE_FS3, NOTE_CS4, NOTE_DS3, NOTE_CS4, NOTE_A3, NOTE_GS3, NOTE_FS3, NOTE_DS3};
int sequenciaMusica3[11] = {NOTE_GS3, NOTE_FS3, NOTE_CS4, NOTE_A3, NOTE_DS3, NOTE_CS4, NOTE_A3, NOTE_GS3, NOTE_FS3, NOTE_DS3, NOTE_CS4};
int sequenciaMusica4[11] = {NOTE_DS3, NOTE_CS4, NOTE_A3, NOTE_GS3, NOTE_FS3, NOTE_DS3, NOTE_CS4, NOTE_A3, NOTE_GS3, NOTE_FS3, NOTE_DS3};
int sequenciaMusica5[11] = {NOTE_CS4, NOTE_DS3, NOTE_A3, NOTE_GS3, NOTE_FS3, NOTE_DS3, NOTE_CS4, NOTE_A3, NOTE_GS3, NOTE_FS3, NOTE_DS3};
int sequencia[11] = {0};
LiquidCrystal lcd(13,12,11,10,9,8);

void setup() {
  lcd.begin(16,2);
  pinMode(7, OUTPUT);// buzzer
  pinMode(6, OUTPUT);// vermelho
  pinMode(5, OUTPUT);// verde
  pinMode(4,INPUT_PULLUP);
  pinMode(3,INPUT_PULLUP);
  pinMode(2,INPUT_PULLUP); 
  pinMode(1,INPUT_PULLUP); 
  pinMode(0,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2),blink,FALLING);
  attachInterrupt(digitalPinToInterrupt(1),hide,FALLING);
}

void musica1() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Inicio Musica 1");

  // Nota 1 - NOTE_FS3 (Botão 4)
  noTone(7);
  tone(7, NOTE_FS3);
  lcd.setCursor(0, 1);
  lcd.print("4");
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("   ");
  noTone(7);

  // Nota 2 - NOTE_CS4 (Botão 1)
  tone(7, NOTE_CS4);
  lcd.setCursor(0, 1);
  lcd.print("1");
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("   ");
  noTone(7);

  // Nota 3 - NOTE_CS4 (Botão 1)
  tone(7, NOTE_CS4);
  lcd.setCursor(0, 1);
  lcd.print("1");
  delay(1500);
  lcd.setCursor(0, 1);
  lcd.print("   ");
  noTone(7);

  // Nota 4 - NOTE_CS4 (Botão 1)
  tone(7, NOTE_CS4);
  lcd.setCursor(0, 1);
  lcd.print("1");
  delay(300);
  if (dificuldade % 3 == 0) {
    noTone(7);
    lcd.setCursor(0, 1);
    lcd.print("3");
    return;
  }
  lcd.setCursor(0, 1);
  lcd.print("   ");
  noTone(7);

  // Nota 5 - NOTE_GS3 (Botão 3)
  tone(7, NOTE_GS3);
  lcd.setCursor(0, 1);
  lcd.print("3");
  delay(1000);
  
  lcd.setCursor(0, 1);
  lcd.print("   ");
  noTone(7);

  // Nota 6 - NOTE_FS3 (Botão 4)
  tone(7, NOTE_FS3);
  lcd.setCursor(0, 1);
  lcd.print("4");
  delay(500);
  if (dificuldade % 3 == 1) {
    noTone(7);
    lcd.setCursor(0, 1);
    lcd.print("3");
    return;
  }
  lcd.setCursor(0, 1);
  lcd.print("   ");
  noTone(7);

  // Nota 7 - NOTE_A3 (Botão 2)
  tone(7, NOTE_A3);
  lcd.setCursor(0, 1);
  lcd.print("2");
  delay(1500);
  lcd.setCursor(0, 1);
  lcd.print("   ");
  noTone(7);

  // Nota 8 - NOTE_FS3 (Botão 4)
  tone(7, NOTE_FS3);
  lcd.setCursor(0, 1);
  lcd.print("4");
  delay(800);
  
  lcd.setCursor(0, 1);
  lcd.print("   ");
  noTone(7);

  // Nota 9 - NOTE_FS3 (Botão 4)
  tone(7, NOTE_FS3);
  lcd.setCursor(0, 1);
  lcd.print("4");
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("   ");
  noTone(7);

  // Nota 10 - NOTE_CS4 (Botão 1)
  tone(7, NOTE_CS4);
  lcd.setCursor(0, 1);
  lcd.print("1");
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("   ");
  noTone(7);

  // Nota 11 - NOTE_CS4 (Botão 1)
  tone(7, NOTE_CS4);
  lcd.setCursor(0, 1);
  lcd.print("1");
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("   ");
  noTone(7);
}



void musica2() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Inicio Musica 2");
  
  // Nota 1 - NOTE_A3 (Botão 2)
  noTone(7);
  tone(7, NOTE_A3);
  lcd.setCursor(0, 1);
  lcd.print("2");
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("   ");
  noTone(7);

  // Nota 2 - NOTE_A3 (Botão 2)
  tone(7, NOTE_A3);
  lcd.setCursor(0, 1);
  lcd.print("2");
  delay(1500);
  lcd.setCursor(0, 1);
  lcd.print("   ");
  noTone(7);

  // Nota 3 - NOTE_GS3 (Botão 3)
  tone(7, NOTE_GS3);
  lcd.setCursor(0, 1);
  lcd.print("3");
  delay(300);
  lcd.setCursor(0, 1);
  lcd.print("   ");
  noTone(7);

  // Nota 4 - NOTE_FS3 (Botão 4)
  tone(7, NOTE_FS3);
  lcd.setCursor(0, 1);
  lcd.print("4");
  delay(1000);
  if (dificuldade % 3 == 0) {
    noTone(7);
    lcd.setCursor(0, 1);
    lcd.print("4");
    return;
  }
  lcd.setCursor(0, 1);
  lcd.print("   ");
  noTone(7);

  // Nota 5 - NOTE_CS4 (Botão 1)
  tone(7, NOTE_CS4);
  lcd.setCursor(0, 1);
  lcd.print("1");
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("   ");
  noTone(7);

  // Nota 6 - NOTE_DS3 (Botão 5)
  tone(7, NOTE_DS3);
  lcd.setCursor(0, 1);
  lcd.print("5");
  delay(800);
  if (dificuldade % 3 == 1) {
    noTone(7);
    lcd.setCursor(0, 1);
    lcd.print("5");
    return;
  }
  lcd.setCursor(0, 1);
  lcd.print("   ");
  noTone(7);

  // Nota 7 - NOTE_CS4 (Botão 1)
  tone(7, NOTE_CS4);
  lcd.setCursor(0, 1);
  lcd.print("1");
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("   ");
  noTone(7);

  // Nota 8 - NOTE_A3 (Botão 2)
  tone(7, NOTE_A3);
  lcd.setCursor(0, 1);
  lcd.print("2");
  delay(1500);
  lcd.setCursor(0, 1);
  lcd.print("   ");
  noTone(7);

  // Nota 9 - NOTE_GS3 (Botão 3)
  tone(7, NOTE_GS3);
  lcd.setCursor(0, 1);
  lcd.print("3");
  delay(300);
      
  
  lcd.setCursor(0, 1);
  lcd.print("   ");
  noTone(7);

  // Nota 10 - NOTE_FS3 (Botão 4)
  tone(7, NOTE_FS3);
  lcd.setCursor(0, 1);
  lcd.print("4");
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("   ");
  noTone(7);

  // Nota 11 - NOTE_DS3 (Botão 5)
  tone(7, NOTE_DS3);
  lcd.setCursor(0, 1);
  lcd.print("5");
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.print("   ");
  noTone(7);
}

void musica3() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Inicio Musica 3");

  // Nota 1 - NOTE_GS3 (Botão 3)
  noTone(7);
  tone(7, NOTE_GS3);
  lcd.setCursor(0, 1);
  lcd.print("3");
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("   ");
  noTone(7);

  // Nota 2 - NOTE_FS3 (Botão 4)
  tone(7, NOTE_FS3);
  lcd.setCursor(0, 1);
  lcd.print("4");
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("   ");
  noTone(7);

  // Nota 3 - NOTE_CS4 (Botão 1)
  tone(7, NOTE_CS4);
  lcd.setCursor(0, 1);
  lcd.print("1");
  delay(1500);
  lcd.setCursor(0, 1);
  lcd.print("   ");
  noTone(7);

  // Nota 4 - NOTE_A3 (Botão 2)
  tone(7, NOTE_A3);
  lcd.setCursor(0, 1);
  lcd.print("2");
  delay(1000);
  if (dificuldade % 3 == 0) {
    noTone(7);
    lcd.setCursor(0, 1);
    lcd.print("2");
    return;
  }
  lcd.setCursor(0, 1);
  lcd.print("   ");
  noTone(7);

  // Nota 5 - NOTE_DS3 (Botão 5)
  tone(7, NOTE_DS3);
  lcd.setCursor(0, 1);
  lcd.print("5");
  delay(800);
  lcd.setCursor(0, 1);
  lcd.print("   ");
  noTone(7);

  // Nota 6 - NOTE_CS4 (Botão 1)
  tone(7, NOTE_CS4);
  lcd.setCursor(0, 1);
  lcd.print("1");
  delay(500);
  if (dificuldade % 3 == 1) {
    noTone(7);
    lcd.setCursor(0, 1);
    lcd.print("1");
    return;
  }
  lcd.setCursor(0, 1);
  lcd.print("   ");
  noTone(7);

  // Nota 7 - NOTE_A3 (Botão 2)
  tone(7, NOTE_A3);
  lcd.setCursor(0, 1);
  lcd.print("2");
  delay(300);
  lcd.setCursor(0, 1);
  lcd.print("   ");
  noTone(7);

  // Nota 8 - NOTE_GS3 (Botão 3)
  tone(7, NOTE_GS3);
  lcd.setCursor(0, 1);
  lcd.print("3");
  delay(1500);
  lcd.setCursor(0, 1);
  lcd.print("   ");
  noTone(7);

  // Nota 9 - NOTE_FS3 (Botão 4)
  tone(7, NOTE_FS3);
  lcd.setCursor(0, 1);
  lcd.print("4");
  delay(500);
  

  // Nota 10 - NOTE_DS3 (Botão 5)
  tone(7, NOTE_DS3);
  lcd.setCursor(0, 1);
  lcd.print("5");
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.print("   ");
  noTone(7);

  // Nota 11 - NOTE_CS4 (Botão 1)
  tone(7, NOTE_CS4);
  lcd.setCursor(0, 1);
  lcd.print("1");
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("   ");
  noTone(7);
}

void musica4() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Inicio Musica 4");

  // Nota 1 - NOTE_DS3 (Botão 5)
  noTone(7);
  tone(7, NOTE_DS3);
  lcd.setCursor(0, 1);
  lcd.print("5");
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("   ");
  noTone(7);

  // Nota 2 - NOTE_CS4 (Botão 1)
  tone(7, NOTE_CS4);
  lcd.setCursor(0, 1);
  lcd.print("1");
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("   ");
  noTone(7);

  // Nota 3 - NOTE_A3 (Botão 2)
  tone(7, NOTE_A3);
  lcd.setCursor(0, 1);
  lcd.print("2");
  delay(1500);
  
  lcd.setCursor(0, 1);
  lcd.print("   ");
  noTone(7);

  // Nota 4 - NOTE_GS3 (Botão 3)
  tone(7, NOTE_GS3);
  lcd.setCursor(0, 1);
  lcd.print("3");
  delay(1000);
  if (dificuldade % 3 == 0) {
    noTone(7);
    lcd.setCursor(0, 1);
    lcd.print("   ");
    return;
  }
  lcd.setCursor(0, 1);
  lcd.print("   ");
  noTone(7);

  // Nota 5 - NOTE_FS3 (Botão 4)
  tone(7, NOTE_FS3);
  lcd.setCursor(0, 1);
  lcd.print("4");
  delay(800);
  
  lcd.setCursor(0, 1);
  lcd.print("   ");
  noTone(7);

  // Nota 6 - NOTE_DS3 (Botão 5)
  tone(7, NOTE_DS3);
  lcd.setCursor(0, 1);
  lcd.print("5");
  delay(500);
  if (dificuldade % 3 == 1) {
    noTone(7);
    lcd.setCursor(0, 1);
    lcd.print("  ");
    return;
  }
  lcd.setCursor(0, 1);
  lcd.print("   ");
  noTone(7);

  // Nota 7 - NOTE_CS4 (Botão 1)
  tone(7, NOTE_CS4);
  lcd.setCursor(0, 1);
  lcd.print("1");
  delay(300);
  lcd.setCursor(0, 1);
  lcd.print("   ");
  noTone(7);

  // Nota 8 - NOTE_A3 (Botão 2)
  tone(7, NOTE_A3);
  lcd.setCursor(0, 1);
  lcd.print("2");
  delay(1500);
  lcd.setCursor(0, 1);
  lcd.print("   ");
  noTone(7);

  // Nota 9 - NOTE_GS3 (Botão 3)
  tone(7, NOTE_GS3);
  lcd.setCursor(0, 1);
  lcd.print("3");
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("   ");
  noTone(7);

  // Nota 10 - NOTE_FS3 (Botão 4)
  tone(7, NOTE_FS3);
  lcd.setCursor(0, 1);
  lcd.print("4");
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.print("   ");
  noTone(7);

  // Nota 11 - NOTE_DS3 (Botão 5)
  tone(7, NOTE_DS3);
  lcd.setCursor(0, 1);
  lcd.print("5");
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("   ");
  noTone(7);
}

void musica5() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Inicio Musica 5");

  // Nota 1 - NOTE_CS4 (Botão 1)
  noTone(7);
  tone(7, NOTE_CS4);
  lcd.setCursor(0, 1);
  lcd.print("1");
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("   ");
  noTone(7);

  // Nota 2 - NOTE_DS3 (Botão 5)
  tone(7, NOTE_DS3);
  lcd.setCursor(0, 1);
  lcd.print("5");
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("   ");
  noTone(7);

  // Nota 3 - NOTE_A3 (Botão 2)
  tone(7, NOTE_A3);
  lcd.setCursor(0, 1);
  lcd.print("2");
  delay(1500);
  lcd.setCursor(0, 1);
  lcd.print("   ");
  noTone(7);

  // Nota 4 - NOTE_GS3 (Botão 3)
  tone(7, NOTE_GS3);
  lcd.setCursor(0, 1);
  lcd.print("3");
  delay(1000);
  if (dificuldade % 3 == 0) {
    noTone(7);
    lcd.setCursor(0, 1);
    lcd.print("3");
    return;
  }
  lcd.setCursor(0, 1);
  lcd.print("   ");
  noTone(7);

  // Nota 5 - NOTE_FS3 (Botão 4)
  tone(7, NOTE_FS3);
  lcd.setCursor(0, 1);
  lcd.print("4");
  delay(800);
  lcd.setCursor(0, 1);
  lcd.print("   ");
  noTone(7);

  // Nota 6 - NOTE_DS3 (Botão 5)
  tone(7, NOTE_DS3);
  lcd.setCursor(0, 1);
  lcd.print("5");
  delay(500);
  if (dificuldade % 3 == 1) {
    noTone(7);
    lcd.setCursor(0, 1);
    lcd.print("5");
    return;
  }
  lcd.setCursor(0, 1);
  lcd.print("   ");
  noTone(7);

  // Nota 7 - NOTE_CS4 (Botão 1)
  tone(7, NOTE_CS4);
  lcd.setCursor(0, 1);
  lcd.print("1");
  delay(300);
  lcd.setCursor(0, 1);
  lcd.print("   ");
  noTone(7);

  // Nota 8 - NOTE_A3 (Botão 2)
  tone(7, NOTE_A3);
  lcd.setCursor(0, 1);
  lcd.print("2");
  delay(1500);
  lcd.setCursor(0, 1);
  lcd.print("   ");
  noTone(7);

  // Nota 9 - NOTE_GS3 (Botão 3)
  tone(7, NOTE_GS3);
  lcd.setCursor(0, 1);
  lcd.print("3");
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("   ");
  noTone(7);

  // Nota 10 - NOTE_FS3 (Botão 4)
  tone(7, NOTE_FS3);
  lcd.setCursor(0, 1);
  lcd.print("4");
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.print("   ");
  noTone(7);

  // Nota 11 - NOTE_DS3 (Botão 5)
  tone(7, NOTE_DS3);
  lcd.setCursor(0, 1);
  lcd.print("5");
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("   ");
  noTone(7);
}

int res(int i ,int nota1, int nota2, int nota3, int nota4, int nota5, int sequenciaCerta[]) {
  int vida = 3;
  int j = 0;
  if (dificuldade % 3 == 0){
    j = 3;
  }
  if (dificuldade % 3 ==  1){
    j = 5;
  }
  if (dificuldade %3 == 2 ){
    j = 10;
  }

  while (sequencia[j] == 0) {
        int primeiro = digitalRead(0);
        int segundo = digitalRead(1);
        int terceiro = digitalRead(2);
        int quarto = digitalRead(3);
        int quinto = digitalRead(4);
        if (primeiro == LOW){
           sequencia[i] = nota1;
           tone(7,nota1);
           delay(500);
           lcd.setCursor(0,1);
  	       lcd.print("1");
           noTone(7);
           if (sequencia[i] == sequenciaCerta[i]){
              digitalWrite(5, HIGH);
              digitalWrite(6, LOW);
              lcd.setCursor(0,0);
  	          lcd.print("Acertou!");
              delay(500);
              digitalWrite(5, LOW);
              score++;
           } else{
              digitalWrite(5, LOW);
              digitalWrite(6, HIGH);
              lcd.setCursor(0,0);
  	          lcd.print("Errou!  ");
              delay(500);
              digitalWrite(6, LOW);
              vida--;
           }
           i++;
        } else if (segundo == LOW){
           sequencia[i] = nota2;
           tone(7,nota2);
           delay(500);
           lcd.setCursor(0,1);
  	       lcd.print("2");
           noTone(7);
           if (sequencia[i] == sequenciaCerta[i]){
              digitalWrite(5, HIGH);
              digitalWrite(6, LOW);
              lcd.setCursor(0,0);
  	          lcd.print("Acertou!");
              delay(500);
              digitalWrite(5, LOW);
              score++;
           } else{
              digitalWrite(5, LOW);
              digitalWrite(6, HIGH);
              lcd.setCursor(0,0);
  	          lcd.print("Errou!  ");
              delay(500);
              digitalWrite(6, LOW);
              vida--;
           }
           i++;
        } else if (terceiro == LOW){
           sequencia[i] = nota3;
           tone(7,nota3);
           delay(500);
           lcd.setCursor(0,1);
           lcd.print("3");
           noTone(7);
           if (sequencia[i] == sequenciaCerta[i]){
              digitalWrite(5, HIGH);
              digitalWrite(6, LOW);
              lcd.setCursor(0,0);
  	          lcd.print("Acertou!");
              delay(500);
              digitalWrite(5, LOW);
              score++;
           } else{
              digitalWrite(5, LOW);
              digitalWrite(6, HIGH);
              lcd.setCursor(0,0);
  	          lcd.print("Errou!  ");
              delay(500);
              digitalWrite(6, LOW);
              vida--;
           }
           i++;
        } else if (quarto == LOW){
           sequencia[i] = nota4;
           tone(7,nota4);
           delay(500);
           lcd.setCursor(0,1);
           lcd.print("4");
           noTone(7);
           if (sequencia[i] == sequenciaCerta[i]){
              digitalWrite(5, HIGH);
              digitalWrite(6, LOW);
              lcd.setCursor(0,0);
  	          lcd.print("Acertou!");
              delay(500);
              digitalWrite(5, LOW);
              score++;
           } else{
              digitalWrite(5, LOW);
              digitalWrite(6, HIGH);
              lcd.setCursor(0,0);
  	          lcd.print("Errou!  ");
              delay(500);
              digitalWrite(6, LOW);
              vida--;
           }
           i++;
        } else if (quinto == LOW){
           sequencia[i] = nota5;
           tone(7,nota5);
           delay(500);
           lcd.setCursor(0,1);
           lcd.print("5");
           noTone(7);
           if (sequencia[i] == sequenciaCerta[i]){
              digitalWrite(5, HIGH);
              digitalWrite(6, LOW);
              lcd.setCursor(0,0);
  	          lcd.print("Acertou!");
              delay(500);
              digitalWrite(5, LOW);
              score++;

           } else{
              digitalWrite(5, LOW);
              digitalWrite(6, HIGH);
              lcd.setCursor(0,0);
  	          lcd.print("Errou!  ");
              delay(500);
              digitalWrite(6, LOW);
              vida--;
           }
           i++;
        }
        lcd.setCursor(9, 1);
        lcd.print("Vida: ");
        lcd.setCursor(15, 1);
        lcd.print(vida);
        if (vida == 0){
          delay(1000);
          lcd.clear();
          lcd.setCursor(8, 1);
          lcd.print("GAMEOVER");
          break;
        }
      }
  vida = 3;
  for(int k = 0; k < 11; k++) sequencia[k] = 0;
  return j;
}

void menuDificuldade(){
  while (true){
    lcd.setCursor(0,0);
    lcd.print("Escolha a dificuldade");
    lcd.setCursor(0,1);
    if (digitalRead(1) == LOW) dificuldade++;
    switch (dificuldade % 3) {
    case 0:
      lcd.print("> Facil  ");
      if (estado == 3){
        return;
      }
      break;
    case 1:
      lcd.print("> Medio  ");
      if (estado == 3){
        return;
      }
      break;
    case 2:
      lcd.print("> Dificil");
      if (estado == 3){
        return;
      }
      break;
    default:
      estado =0;
      break;
    } 
  }
}




void loop() {
  if(estado == 0){
    lcd.setCursor(0, 0);
  lcd.print("Seja bem vindo");
  lcd.setCursor(0, 1);
  lcd.print("Pressione botao 3 p/ iniciar");
  musicaSelecionada = 0;
  } else if (estado == 1){
  if (digitalRead(1) == LOW) musicaSelecionada++;
  lcd.setCursor(0,0);
  lcd.print("Escolha a musica              ");
  lcd.setCursor(0,1);
  switch (musicaSelecionada % 5) {
  case 0:
    lcd.print("> Musica 1              ");
    break;
  case 1:
    lcd.print("> Musica 2              ");
    break;
  case 2:
    lcd.print("> Musica 3              ");
    break;
  case 3:
    lcd.print("> Musica 4              ");
    break;
  case 4:
    lcd.print("> Musica 5              ");
    break;
  default:
    estado =1;
    break;
  }
  } else if (estado == 2){
    lcd.clear();
    menuDificuldade();
  } else if (estado == 3) {
    if (alterado== 0){
      switch (musicaSelecionada % 5) {
        case 0: musica1(); break;
        case 1: musica2(); break;
        case 2: musica3(); break;
        case 3: musica4(); break;
        case 4: musica5(); break;
      }
      alterado++;
      estado++;
    }
      } else if (alterado == 1 ){
      switch (musicaSelecionada % 5) {
      case 0:
        lcd.clear();
      lcd.setCursor(0,0);
  	  lcd.print("Sua vez");
      if (score == res( 0, NOTE_CS4, NOTE_A3, NOTE_GS3 ,NOTE_FS3 , NOTE_DS3, sequenciaMusica1)+1){
      	lcd.setCursor(0,0);
  	  lcd.print("Parabens!");
        delay(2000);
        lcd.clear();
      }
      lcd.setCursor(0,0);
  	  lcd.print("Score: ");
      lcd.setCursor(8,0);
      lcd.print(score);
      musicaSelecionada = 0;
      alterado++;
      break;
      case 1:
        lcd.clear();
      lcd.setCursor(0,0);
  	  lcd.print("Sua vez");
      if (score == res( 0, NOTE_CS4, NOTE_A3, NOTE_GS3 ,NOTE_FS3 , NOTE_DS3, sequenciaMusica2)){
      	lcd.setCursor(0,0);
  	  lcd.print("Parabens!");
        delay(2000);
        lcd.clear();
      }
      lcd.setCursor(0,0);
  	  lcd.print("Score: ");
      lcd.setCursor(8,0);
      lcd.print(score);
      musicaSelecionada = 0;
      alterado++; 
        break;
      case 2:
         lcd.clear();
      lcd.setCursor(0,0);
  	  lcd.print("Sua vez");
      if (score == res( 0, NOTE_CS4, NOTE_A3, NOTE_GS3 ,NOTE_FS3 , NOTE_DS3, sequenciaMusica3)){
      	lcd.setCursor(0,0);
  	  lcd.print("Parabens!");
        delay(2000);
        lcd.clear();
      }
      lcd.setCursor(0,0);
  	  lcd.print("Score: ");
      lcd.setCursor(8,0);
      lcd.print(score);
      musicaSelecionada = 0;
      alterado++;
        break;
      case 3:
        lcd.clear();
      lcd.setCursor(0,0);
  	  lcd.print("Sua vez");
      if (score == res( 0, NOTE_CS4, NOTE_A3, NOTE_GS3 ,NOTE_FS3 , NOTE_DS3, sequenciaMusica4)){
      	lcd.setCursor(0,0);
  	  lcd.print("Parabens!");
        delay(2000);
        lcd.clear();
      }
      lcd.setCursor(0,0);
  	  lcd.print("Score: ");
      lcd.setCursor(8,0);
      lcd.print(score);
      musicaSelecionada = 0;
      alterado++;
        break;
      case 4:
        lcd.clear();
      lcd.setCursor(0,0);
  	  lcd.print("Sua vez");
      if (score == res( 0, NOTE_CS4, NOTE_A3, NOTE_GS3 ,NOTE_FS3 , NOTE_DS3, sequenciaMusica5)){
      	lcd.setCursor(0,0);
  	  lcd.print("Parabens!");
        delay(2000);
        lcd.clear();
      }
      lcd.setCursor(0,0);
  	  lcd.print("Score: ");
      lcd.setCursor(8,0);
      lcd.print(score);
      musicaSelecionada = 0;
      alterado++;
        break;
      default:
        estado =0;
        break;
      }
      } else if (alterado > 1){
      estado = 0;
      alterado = 0;
      delay(3000);
      lcd.clear();
      }
}

void blink() {
  if (estado <= 3){
    estado ++;
  } 
 	
}

void hide(){
  if (estado == 1){
    musicaSelecionada++;
  }
  if (estado == 2) {
    dificuldade++;
  }
}


