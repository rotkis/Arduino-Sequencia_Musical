// C++ code
//
#include <LiquidCrystal.h>
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
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
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST      0
int estado = 0;
int score = 0;
int alterado = 0;
int dificuldade = 0;
int musicaSelecionada = 0;
int sequenciaMusica1[11] = {NOTE_FS3, NOTE_CS4, NOTE_CS4, NOTE_CS4, NOTE_GS3, NOTE_FS3, NOTE_A3, NOTE_FS3, NOTE_FS3, NOTE_CS4, NOTE_CS4};
int sequenciaMusica2[11] = {NOTE_FS3, NOTE_CS4, NOTE_CS4, NOTE_CS4, NOTE_GS3, NOTE_FS3, NOTE_A3, NOTE_FS3, NOTE_FS3, NOTE_CS4, NOTE_CS4};
int sequenciaMusica3[11] = {NOTE_FS3, NOTE_CS4, NOTE_CS4, NOTE_CS4, NOTE_GS3, NOTE_FS3, NOTE_A3, NOTE_FS3, NOTE_FS3, NOTE_CS4, NOTE_CS4};
int sequenciaMusica4[11] = {NOTE_FS3, NOTE_CS4, NOTE_CS4, NOTE_CS4, NOTE_GS3, NOTE_FS3, NOTE_A3, NOTE_FS3, NOTE_FS3, NOTE_CS4, NOTE_CS4};
int sequenciaMusica5[11] = {NOTE_FS3, NOTE_CS4, NOTE_CS4, NOTE_CS4, NOTE_GS3, NOTE_FS3, NOTE_A3, NOTE_FS3, NOTE_FS3, NOTE_CS4, NOTE_CS4};
int sequencia[11] = {0, 0, 0, 0, 0, 0 , 0, 0, 0 , 0 , 0};
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

void musica1(){
    lcd.clear();
 	  lcd.setCursor(0,0);
  	lcd.print("Inicio");
    noTone(7);
    tone(7,NOTE_FS3);
    lcd.setCursor(0,1);
  	lcd.print("4");
    delay(500);
    lcd.setCursor(0,1);
    lcd.print("   ");
    noTone(7);
    tone(7,NOTE_CS4);
    lcd.setCursor(0,1);
  	lcd.print("1");
    delay(500);
    lcd.setCursor(0,1);
    lcd.print("   ");
    noTone(7);
    tone(7,NOTE_CS4);
    lcd.setCursor(0,1);
  	lcd.print("1");
    delay(1500);
    lcd.setCursor(0,1);
    lcd.print("   ");
    noTone(7);
    tone(7,NOTE_CS4);
    lcd.setCursor(0,1);
  	lcd.print("1");
    delay(300);
    lcd.setCursor(0,1);
    lcd.print("   ");
    noTone(7);
    tone(7,NOTE_GS3);
    lcd.setCursor(0,1);
  	lcd.print("3");
    delay(1000);
    if (dificuldade % 3 == 0){
      noTone(7);
      lcd.setCursor(0,1);
  	  lcd.print("3");
      return;
    }
    lcd.setCursor(0,1);
    lcd.print("   ");
    noTone(7);
    tone(7,NOTE_FS3);
    lcd.setCursor(0,1);
  	lcd.print("4");
    delay(500);
    lcd.setCursor(0,1);
    lcd.print("   ");
    noTone(7);
    tone(7,NOTE_A3);
    lcd.setCursor(0,1);
  	lcd.print("2");
    delay(1500);
    lcd.setCursor(0,1);
    lcd.print("   ");
    noTone(7);
    tone(7,NOTE_FS3);
    lcd.setCursor(0,1);
  	lcd.print("4");
    delay(800);  
    if (dificuldade% 3 == 1){
      noTone(7);
      lcd.setCursor(0,1);
  	  lcd.print("3");
      return;
    }
    tone(7,NOTE_FS3);
    lcd.setCursor(0,1);
  	lcd.print("4");
    delay(500);
    lcd.setCursor(0,1);
    lcd.print("   ");
    noTone(7);
    tone(7,NOTE_CS4);
    lcd.setCursor(0,1);
  	lcd.print("1");
    delay(500);
    lcd.setCursor(0,1);
    lcd.print("   ");
    noTone(7);
    tone(7,NOTE_CS4);
    lcd.setCursor(0,1);
  	lcd.print("1");
    lcd.print("   ");
    noTone(7);
    
}

int res(int i ,int nota1, int nota2, int nota3, int nota4, int nota5, int sequenciaCerta[]) {
  int vida = 3;
  int j = 0
  if (dificuldade % 3 == 0){
    j = 5;
  }
  if (dificuldade % 3 ==  1){
    j = 8;
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
          lcd.setCursor();
          lcd.print("GAMEOVER");
          break;
        }
      }
  vida = 3;
  sequencia[11] = {0, 0, 0, 0, 0, 0 , 0, 0, 0 , 0 , 0};
  return j - 1;
}

void menuDificuldade(){
  while (true){
    lcd.setCursor(0,0);
    lcd.print("Escolha a dificuldade");
    lcd.setCursor(0,1);

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

void menuMusica() {
  lcd.setCursor(0,0);
  lcd.print("Escolha a musica");
  lcd.setCursor(0,1);

  switch (musicaSelecionada % 5) {
  case 0:
    lcd.print("> Musica 1");
    break;
  case 1:
    lcd.print("> Musica 2");
    break;
  case 2:
    lcd.print("> Musica 3");
    break;
  case 3:
    lcd.print("> Musica 4");
    break;
  case 4:
    lcd.print("> Musica 5");
    break;
  default:
    estado =0;
    break;
  }
}


void loop() {
  if(estado == 0){
    lcd.setCursor(0, 0);
  lcd.print("Seja bem vindo");
  lcd.setCursor(0, 1);
  lcd.print("Pressione botao 3 p/ iniciar");
  } else if (estado == 1){
    menuMusica();
  } else if (estado == 2) {
    if (alterado== 0){
      switch (musicaSelecionada % 5) {
      case 0:
        musica1();
        menuDificuldade();
        alterado++;
        break;
      case 1:
        lcd.print("> Musica 2");
        menuDificuldade();
        alterado++;
        break;
      case 2:
        lcd.print("> Musica 3");
        menuDificuldade();
        alterado++;
        break;
      case 3:
        lcd.print("> Musica 4");
        menuDificuldade();
        alterado++;
        break;
      case 4:
        lcd.print("> Musica 5");
        menuDificuldade();
        alterado++;
        break;
      default:
        estado =0;
        break;
      }
      musicaSelecionada = 0;
      // todo escolha de dificuldade
      } else if (alterado == 1 ){
      lcd.clear();
      lcd.setCursor(0,0);
  	  lcd.print("Sua vez");
      if (score == res( 0, NOTE_CS4, NOTE_A3, NOTE_GS3 ,NOTE_FS3 , NOTE_DS3)){
      	lcd.setCursor(0,0);
  	  lcd.print("Parabens!");
        delay(2000);
        lcd.clear();
      }
      lcd.setCursor(0,0);
  	  lcd.print("Score: ");
      lcd.setCursor(8,0);
      lcd.print(score);
      alterado++;
    } else if (alterado > 1){
      estado = 0;
      alterado = 0;
      delay(3000);
      lcd.clear();
    }
      
  }
}

void blink() {
  if (estado <= 2){
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

