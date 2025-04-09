// Inclui a biblioteca para interagir com displays de Cristal Líquido (LCD)
#include <LiquidCrystal.h>

// --- Definições das Notas Musicais ---
// Define constantes (usando #define) para representar as frequências (em Hertz)
// das notas musicais. Isso torna o código mais legível do que usar os números diretamente.
// Ex: NOTE_C3 é a nota Dó da terceira oitava. CS é C sustenido, DS é D sustenido, etc.
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
#define REST      0 // Define uma constante para silêncio (sem som)

// --- Variáveis Globais ---
// Variáveis declaradas fora de qualquer função, acessíveis por todo o código.
int estado = 0;            // Controla o estado atual da aplicação (ex: menu, jogando, etc.)
int score = 0;             // Armazena a pontuação do jogador.
int alterado = 0;          // Variável auxiliar para controlar etapas dentro de um estado (flag).
int dificuldade = 0;       // Armazena o nível de dificuldade escolhido (0=Fácil, 1=Médio, 2=Difícil).
int musicaSelecionada = 0; // Guarda o índice da música que o jogador selecionou (0 a 4).

// --- Sequências Musicais ---
// Arrays (vetores) que armazenam a sequência de notas (frequências definidas acima) para cada música.
// Cada array tem tamanho 11, significando que as músicas têm no máximo 11 notas.
int sequenciaMusica1[11] = {NOTE_FS3, NOTE_CS4, NOTE_CS4, NOTE_CS4, NOTE_GS3, NOTE_FS3, NOTE_A3, NOTE_FS3, NOTE_FS3, NOTE_CS4, NOTE_CS4};
int sequenciaMusica2[11] = {NOTE_A3, NOTE_A3, NOTE_GS3, NOTE_FS3, NOTE_CS4, NOTE_DS3, NOTE_CS4, NOTE_A3, NOTE_GS3, NOTE_FS3, NOTE_DS3};
int sequenciaMusica3[11] = {NOTE_GS3, NOTE_FS3, NOTE_CS4, NOTE_A3, NOTE_DS3, NOTE_CS4, NOTE_A3, NOTE_GS3, NOTE_FS3, NOTE_DS3, NOTE_CS4};
int sequenciaMusica4[11] = {NOTE_DS3, NOTE_CS4, NOTE_A3, NOTE_GS3, NOTE_FS3, NOTE_DS3, NOTE_CS4, NOTE_A3, NOTE_GS3, NOTE_FS3, NOTE_DS3};
int sequenciaMusica5[11] = {NOTE_CS4, NOTE_DS3, NOTE_A3, NOTE_GS3, NOTE_FS3, NOTE_DS3, NOTE_CS4, NOTE_A3, NOTE_GS3, NOTE_FS3, NOTE_DS3};

// Array para armazenar a sequência de notas que o jogador insere.
// É inicializado com zeros.
int sequencia[11] = {0};

// --- Inicialização do LCD ---
// Cria um objeto chamado 'lcd' da classe LiquidCrystal.
// Os números (13, 12, 11, 10, 9, 8) são os pinos do Arduino conectados, respectivamente,
// aos pinos RS, E, D4, D5, D6, D7 do display LCD.
LiquidCrystal lcd(13,12,11,10,9,8);

// --- Função setup() ---
// Esta função é executada apenas uma vez quando o Arduino liga ou é resetado.
void setup() {
  // Inicializa o display LCD com 16 colunas e 2 linhas.
  lcd.begin(16,2);

  // --- Configuração dos Pinos ---
  pinMode(7, OUTPUT); // Pino 7 configurado como SAÍDA (para controlar o buzzer).
  pinMode(6, OUTPUT); // Pino 6 configurado como SAÍDA (para o LED vermelho - erro).
  pinMode(5, OUTPUT); // Pino 5 configurado como SAÍDA (para o LED verde - acerto).
  pinMode(4, INPUT_PULLUP); // Pino 4 como ENTRADA com resistor PULL-UP interno (Botão 5).
  pinMode(3, INPUT_PULLUP); // Pino 3 como ENTRADA com resistor PULL-UP interno (Botão 4).
  pinMode(2, INPUT_PULLUP); // Pino 2 como ENTRADA com resistor PULL-UP interno (Botão 3).
  pinMode(1, INPUT_PULLUP); // Pino 1 como ENTRADA com resistor PULL-UP interno (Botão 2).
  pinMode(0, INPUT_PULLUP); // Pino 0 como ENTRADA com resistor PULL-UP interno (Botão 1).
  // INPUT_PULLUP significa que o pino lê HIGH por padrão; quando o botão é pressionado (ligando ao GND), ele lê LOW.

  // --- Configuração das Interrupções ---
  // Associa funções (ISRs) a eventos de mudança nos pinos 2 e 1.
  // digitalPinToInterrupt(pino) converte o número do pino para o número da interrupção correspondente.
  // blink: função a ser chamada quando a interrupção ocorrer.
  // FALLING: A interrupção é disparada quando o pino muda de HIGH para LOW (quando o botão é pressionado).
  attachInterrupt(digitalPinToInterrupt(2), blink, FALLING); // Pino 2 (Botão 3) chama a função blink.
  attachInterrupt(digitalPinToInterrupt(1), hide, FALLING);  // Pino 1 (Botão 2) chama a função hide.
}

// --- Funções das Músicas (musica1 a musica5) ---
// Estas funções tocam a sequência de notas da música correspondente no buzzer (pino 7)
// e mostram no LCD qual botão (1 a 5) o jogador deveria pressionar para aquela nota.
// A duração da demonstração depende da variável 'dificuldade'.

void musica1() {
  lcd.clear(); // Limpa o conteúdo do LCD.
  lcd.setCursor(0, 0); // Posiciona o cursor na coluna 0, linha 0.
  lcd.print("Inicio Musica 1"); // Escreve o título da música.

  // --- Bloco de cada Nota ---
  // Nota 1: NOTE_FS3 (associada ao Botão 4 no comentário, mas o código mostra "4")
  noTone(7); // Garante que o buzzer está desligado antes de tocar.
  tone(7, NOTE_FS3); // Toca a frequência NOTE_FS3 no pino 7.
  lcd.setCursor(0, 1); // Posiciona o cursor na coluna 0, linha 1.
  lcd.print("4"); // Mostra "4" no LCD.
  delay(500); // Mantém a nota e o número por 500 milissegundos.
  lcd.setCursor(0, 1); // Reposiciona o cursor (embora já esteja lá).
  lcd.print("  "); // Apaga o "4" escrevendo espaços em cima.
  noTone(7); // Para de tocar a nota.

  // Nota 2: NOTE_CS4 (associada ao Botão 1)
  tone(7, NOTE_CS4);
  lcd.setCursor(0, 1);
  lcd.print("1");
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("  ");
  noTone(7);

  // Nota 3: NOTE_CS4 (associada ao Botão 1)
  tone(7, NOTE_CS4);
  lcd.setCursor(0, 1);
  lcd.print("1");
  delay(1500); // Nota mais longa.
  lcd.setCursor(0, 1);
  lcd.print("  ");
  noTone(7);

  // Nota 4: NOTE_CS4 (associada ao Botão 1)
  tone(7, NOTE_CS4);
  lcd.setCursor(0, 1);
  lcd.print("1");
  delay(300);
  // Verifica a dificuldade: Se for Fácil (dificuldade % 3 == 0), para a demonstração aqui.
  if (dificuldade % 3 == 0) {
    noTone(7); // Para o som.
    lcd.setCursor(0, 1); // Posiciona cursor.
    // lcd.print("3"); // Originalmente mostrava "3" aqui antes de retornar, talvez um erro?
    // Na verdade, o código não mostra nada, apenas apaga e retorna. Vamos manter como está.
    lcd.print(" "); // Apaga o último número mostrado.
    return; // Sai da função musica1 prematuramente.
  }
  lcd.setCursor(0, 1);
  lcd.print("  ");
  noTone(7);

  // Nota 5: NOTE_GS3 (associada ao Botão 3)
  tone(7, NOTE_GS3);
  lcd.setCursor(0, 1);
  lcd.print("3");
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.print("  ");
  noTone(7);

  // Nota 6: NOTE_FS3 (associada ao Botão 4)
  tone(7, NOTE_FS3);
  lcd.setCursor(0, 1);
  lcd.print("4");
  delay(500);
  // Verifica a dificuldade: Se for Médio (dificuldade % 3 == 1), para a demonstração aqui.
  if (dificuldade % 3 == 1) {
    noTone(7);
    lcd.setCursor(0, 1);
    // lcd.print("3"); // Originalmente mostrava "3" aqui antes de retornar.
    lcd.print(" "); // Apaga o último número.
    return; // Sai da função musica1 prematuramente.
  }
  lcd.setCursor(0, 1);
  lcd.print("  ");
  noTone(7);

  // Nota 7: NOTE_A3 (associada ao Botão 2)
  tone(7, NOTE_A3);
  lcd.setCursor(0, 1);
  lcd.print("2");
  delay(1500);
  lcd.setCursor(0, 1);
  lcd.print("  ");
  noTone(7);

  // Nota 8: NOTE_FS3 (associada ao Botão 4)
  tone(7, NOTE_FS3);
  lcd.setCursor(0, 1);
  lcd.print("4");
  delay(800);
  lcd.setCursor(0, 1);
  lcd.print("  ");
  noTone(7);

  // Nota 9: NOTE_FS3 (associada ao Botão 4)
  tone(7, NOTE_FS3);
  lcd.setCursor(0, 1);
  lcd.print("4");
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("  ");
  noTone(7);

  // Nota 10: NOTE_CS4 (associada ao Botão 1)
  tone(7, NOTE_CS4);
  lcd.setCursor(0, 1);
  lcd.print("1");
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("  ");
  noTone(7);

  // Nota 11: NOTE_CS4 (associada ao Botão 1)
  tone(7, NOTE_CS4);
  lcd.setCursor(0, 1);
  lcd.print("1");
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("  ");
  noTone(7);
  // Se chegou até aqui, a dificuldade era Difícil (dificuldade % 3 == 2) e tocou todas as notas.
}

// As funções musica2, musica3, musica4, musica5 seguem exatamente a mesma estrutura
// da musica1, apenas mudando as notas, durações e os pontos onde a demonstração
// é interrompida com base na 'dificuldade'. Os comentários seriam redundantes.
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
  lcd.print("  ");
  noTone(7);

  // Nota 2 - NOTE_A3 (Botão 2)
  tone(7, NOTE_A3);
  lcd.setCursor(0, 1);
  lcd.print("2");
  delay(1500);
  lcd.setCursor(0, 1);
  lcd.print("  ");
  noTone(7);

  // Nota 3 - NOTE_GS3 (Botão 3)
  tone(7, NOTE_GS3);
  lcd.setCursor(0, 1);
  lcd.print("3");
  delay(300);
  lcd.setCursor(0, 1);
  lcd.print("  ");
  noTone(7);

  // Nota 4 - NOTE_FS3 (Botão 4)
  tone(7, NOTE_FS3);
  lcd.setCursor(0, 1);
  lcd.print("4");
  delay(1000);
  if (dificuldade % 3 == 0) { // Corte para Dificuldade Fácil
    noTone(7);
    lcd.setCursor(0, 1);
    // lcd.print("4"); // Código original mostrava "4" aqui.
    lcd.print(" ");
    return;
  }
  lcd.setCursor(0, 1);
  lcd.print("  ");
  noTone(7);

  // Nota 5 - NOTE_CS4 (Botão 1)
  tone(7, NOTE_CS4);
  lcd.setCursor(0, 1);
  lcd.print("1");
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("  ");
  noTone(7);

  // Nota 6 - NOTE_DS3 (Botão 5)
  tone(7, NOTE_DS3);
  lcd.setCursor(0, 1);
  lcd.print("5");
  delay(800);
  if (dificuldade % 3 == 1) { // Corte para Dificuldade Média
    noTone(7);
    lcd.setCursor(0, 1);
    // lcd.print("5"); // Código original mostrava "5" aqui.
    lcd.print(" ");
    return;
  }
  lcd.setCursor(0, 1);
  lcd.print("  ");
  noTone(7);

  // Nota 7 - NOTE_CS4 (Botão 1)
  tone(7, NOTE_CS4);
  lcd.setCursor(0, 1);
  lcd.print("1");
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("  ");
  noTone(7);

  // Nota 8 - NOTE_A3 (Botão 2)
  tone(7, NOTE_A3);
  lcd.setCursor(0, 1);
  lcd.print("2");
  delay(1500);
  lcd.setCursor(0, 1);
  lcd.print("  ");
  noTone(7);

  // Nota 9 - NOTE_GS3 (Botão 3)
  tone(7, NOTE_GS3);
  lcd.setCursor(0, 1);
  lcd.print("3");
  delay(300);
  lcd.setCursor(0, 1);
  lcd.print("  ");
  noTone(7);

  // Nota 10 - NOTE_FS3 (Botão 4)
  tone(7, NOTE_FS3);
  lcd.setCursor(0, 1);
  lcd.print("4");
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("  ");
  noTone(7);

  // Nota 11 - NOTE_DS3 (Botão 5)
  tone(7, NOTE_DS3);
  lcd.setCursor(0, 1);
  lcd.print("5");
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.print("  ");
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
  lcd.print("  ");
  noTone(7);

  // Nota 2 - NOTE_FS3 (Botão 4)
  tone(7, NOTE_FS3);
  lcd.setCursor(0, 1);
  lcd.print("4");
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("  ");
  noTone(7);

  // Nota 3 - NOTE_CS4 (Botão 1)
  tone(7, NOTE_CS4);
  lcd.setCursor(0, 1);
  lcd.print("1");
  delay(1500);
  lcd.setCursor(0, 1);
  lcd.print("  ");
  noTone(7);

  // Nota 4 - NOTE_A3 (Botão 2)
  tone(7, NOTE_A3);
  lcd.setCursor(0, 1);
  lcd.print("2");
  delay(1000);
  if (dificuldade % 3 == 0) { // Corte Fácil
    noTone(7);
    lcd.setCursor(0, 1);
    // lcd.print("2"); // Originalmente mostrava 2
    lcd.print(" ");
    return;
  }
  lcd.setCursor(0, 1);
  lcd.print("  ");
  noTone(7);

  // Nota 5 - NOTE_DS3 (Botão 5)
  tone(7, NOTE_DS3);
  lcd.setCursor(0, 1);
  lcd.print("5");
  delay(800);
  lcd.setCursor(0, 1);
  lcd.print("  ");
  noTone(7);

  // Nota 6 - NOTE_CS4 (Botão 1)
  tone(7, NOTE_CS4);
  lcd.setCursor(0, 1);
  lcd.print("1");
  delay(500);
  if (dificuldade % 3 == 1) { // Corte Médio
    noTone(7);
    lcd.setCursor(0, 1);
    // lcd.print("1"); // Originalmente mostrava 1
    lcd.print(" ");
    return;
  }
  lcd.setCursor(0, 1);
  lcd.print("  ");
  noTone(7);

  // Nota 7 - NOTE_A3 (Botão 2)
  tone(7, NOTE_A3);
  lcd.setCursor(0, 1);
  lcd.print("2");
  delay(300);
  lcd.setCursor(0, 1);
  lcd.print("  ");
  noTone(7);

  // Nota 8 - NOTE_GS3 (Botão 3)
  tone(7, NOTE_GS3);
  lcd.setCursor(0, 1);
  lcd.print("3");
  delay(1500);
  lcd.setCursor(0, 1);
  lcd.print("  ");
  noTone(7);

  // Nota 9 - NOTE_FS3 (Botão 4)
  tone(7, NOTE_FS3);
  lcd.setCursor(0, 1);
  lcd.print("4");
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("  "); // Apagava aqui no original
  noTone(7); // Parava o tom aqui no original

  // Nota 10 - NOTE_DS3 (Botão 5)
  tone(7, NOTE_DS3); // Começa a tocar a nota 10
  lcd.setCursor(0, 1);
  lcd.print("5");
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.print("  ");
  noTone(7);

  // Nota 11 - NOTE_CS4 (Botão 1)
  tone(7, NOTE_CS4);
  lcd.setCursor(0, 1);
  lcd.print("1");
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("  ");
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
  lcd.print("  ");
  noTone(7);

  // Nota 2 - NOTE_CS4 (Botão 1)
  tone(7, NOTE_CS4);
  lcd.setCursor(0, 1);
  lcd.print("1");
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("  ");
  noTone(7);

  // Nota 3 - NOTE_A3 (Botão 2)
  tone(7, NOTE_A3);
  lcd.setCursor(0, 1);
  lcd.print("2");
  delay(1500);
  lcd.setCursor(0, 1);
  lcd.print("  ");
  noTone(7);

  // Nota 4 - NOTE_GS3 (Botão 3)
  tone(7, NOTE_GS3);
  lcd.setCursor(0, 1);
  lcd.print("3");
  delay(1000);
  if (dificuldade % 3 == 0) { // Corte Fácil
    noTone(7);
    lcd.setCursor(0, 1);
    lcd.print("  "); // Originalmente apagava aqui
    return;
  }
  lcd.setCursor(0, 1);
  lcd.print("  ");
  noTone(7);

  // Nota 5 - NOTE_FS3 (Botão 4)
  tone(7, NOTE_FS3);
  lcd.setCursor(0, 1);
  lcd.print("4");
  delay(800);
  lcd.setCursor(0, 1);
  lcd.print("  ");
  noTone(7);

  // Nota 6 - NOTE_DS3 (Botão 5)
  tone(7, NOTE_DS3);
  lcd.setCursor(0, 1);
  lcd.print("5");
  delay(500);
  if (dificuldade % 3 == 1) { // Corte Médio
    noTone(7);
    lcd.setCursor(0, 1);
    // lcd.print(" "); // Originalmente tinha só um espaço aqui
    lcd.print("  "); // Deixando consistente com os outros
    return;
  }
  lcd.setCursor(0, 1);
  lcd.print("  ");
  noTone(7);

  // Nota 7 - NOTE_CS4 (Botão 1)
  tone(7, NOTE_CS4);
  lcd.setCursor(0, 1);
  lcd.print("1");
  delay(300);
  lcd.setCursor(0, 1);
  lcd.print("  ");
  noTone(7);

  // Nota 8 - NOTE_A3 (Botão 2)
  tone(7, NOTE_A3);
  lcd.setCursor(0, 1);
  lcd.print("2");
  delay(1500);
  lcd.setCursor(0, 1);
  lcd.print("  ");
  noTone(7);

  // Nota 9 - NOTE_GS3 (Botão 3)
  tone(7, NOTE_GS3);
  lcd.setCursor(0, 1);
  lcd.print("3");
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("  ");
  noTone(7);

  // Nota 10 - NOTE_FS3 (Botão 4)
  tone(7, NOTE_FS3);
  lcd.setCursor(0, 1);
  lcd.print("4");
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.print("  ");
  noTone(7);

  // Nota 11 - NOTE_DS3 (Botão 5)
  tone(7, NOTE_DS3);
  lcd.setCursor(0, 1);
  lcd.print("5");
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("  ");
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
  lcd.print("  ");
  noTone(7);

  // Nota 2 - NOTE_DS3 (Botão 5)
  tone(7, NOTE_DS3);
  lcd.setCursor(0, 1);
  lcd.print("5");
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("  ");
  noTone(7);

  // Nota 3 - NOTE_A3 (Botão 2)
  tone(7, NOTE_A3);
  lcd.setCursor(0, 1);
  lcd.print("2");
  delay(1500);
  lcd.setCursor(0, 1);
  lcd.print("  ");
  noTone(7);

  // Nota 4 - NOTE_GS3 (Botão 3)
  tone(7, NOTE_GS3);
  lcd.setCursor(0, 1);
  lcd.print("3");
  delay(1000);
  if (dificuldade % 3 == 0) { // Corte Fácil
    noTone(7);
    lcd.setCursor(0, 1);
    // lcd.print("3"); // Originalmente mostrava 3
    lcd.print(" ");
    return;
  }
  lcd.setCursor(0, 1);
  lcd.print("  ");
  noTone(7);

  // Nota 5 - NOTE_FS3 (Botão 4)
  tone(7, NOTE_FS3);
  lcd.setCursor(0, 1);
  lcd.print("4");
  delay(800);
  lcd.setCursor(0, 1);
  lcd.print("  ");
  noTone(7);

  // Nota 6 - NOTE_DS3 (Botão 5)
  tone(7, NOTE_DS3);
  lcd.setCursor(0, 1);
  lcd.print("5");
  delay(500);
  if (dificuldade % 3 == 1) { // Corte Médio
    noTone(7);
    lcd.setCursor(0, 1);
    // lcd.print("5"); // Originalmente mostrava 5
    lcd.print(" ");
    return;
  }
  lcd.setCursor(0, 1);
  lcd.print("  ");
  noTone(7);

  // Nota 7 - NOTE_CS4 (Botão 1)
  tone(7, NOTE_CS4);
  lcd.setCursor(0, 1);
  lcd.print("1");
  delay(300);
  lcd.setCursor(0, 1);
  lcd.print("  ");
  noTone(7);

  // Nota 8 - NOTE_A3 (Botão 2)
  tone(7, NOTE_A3);
  lcd.setCursor(0, 1);
  lcd.print("2");
  delay(1500);
  lcd.setCursor(0, 1);
  lcd.print("  ");
  noTone(7);

  // Nota 9 - NOTE_GS3 (Botão 3)
  tone(7, NOTE_GS3);
  lcd.setCursor(0, 1);
  lcd.print("3");
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("  ");
  noTone(7);

  // Nota 10 - NOTE_FS3 (Botão 4)
  tone(7, NOTE_FS3);
  lcd.setCursor(0, 1);
  lcd.print("4");
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.print("  ");
  noTone(7);

  // Nota 11 - NOTE_DS3 (Botão 5)
  tone(7, NOTE_DS3);
  lcd.setCursor(0, 1);
  lcd.print("5");
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("  ");
  noTone(7);
}

// --- Função res() ---
// Esta função gerencia a vez do jogador de inserir a sequência.
// Recebe a entrada dos botões, compara com a sequência correta, dá feedback (LEDs, LCD),
// atualiza score e vidas, e verifica game over.
// Parâmetros:
//   i: O índice inicial no array 'sequencia' onde a entrada do jogador será salva (geralmente 0).
//   nota1 a nota5: As frequências das notas que serão tocadas quando os botões 1 a 5 forem pressionados PELO JOGADOR.
//                  (Note que são fixas, passadas do loop, não necessariamente as notas da música original).
//   sequenciaCerta[]: O array que contém a sequência correta que o jogador deve imitar.
// Retorna:
//   j: O número de notas que o jogador precisava acertar para a dificuldade atual.
int res(int i ,int nota1, int nota2, int nota3, int nota4, int nota5, int sequenciaCerta[]) {
  int vida = 3; // O jogador começa com 3 vidas.
  int j = 0;    // Variável para guardar o número de notas a verificar.

  // Define quantas notas ('j') o jogador precisa acertar com base na dificuldade.
  // A lógica original era:
  if (dificuldade % 3 == 0){ // Fácil
     j = 3; // Precisa acertar 3 notas (índices 0, 1, 2).
  } else if (dificuldade % 3 ==  1){ // Médio
     j = 5; // Precisa acertar 5 notas (índices 0 a 4).
  } else if (dificuldade %3 == 2 ){ // Difícil
     j = 10;// Precisa acertar 10 notas (índices 0 a 9).
  }
  // ATENÇÃO: Os valores de 'j' (3, 5, 10) aqui podem não corresponder exatamente ao número
  // de notas tocadas nas funções musicaX() para cada dificuldade (que pareciam ser 4, 6, 11).
  // Isso pode ser uma inconsistência intencional ou não no código original.

  // Loop principal da vez do jogador: continua enquanto a j-ésima posição da sequência do jogador for 0
  // (ou seja, enquanto o jogador não tiver inserido 'j' notas).
  while (sequencia[j] == 0) {
        // Lê o estado atual de cada um dos 5 botões (conectados aos pinos 0 a 4).
        // LOW significa que o botão está pressionado (por causa do INPUT_PULLUP).
        int primeiro = digitalRead(0);  // Botão 1
        int segundo = digitalRead(1);   // Botão 2
        int terceiro = digitalRead(2);  // Botão 3
        int quarto = digitalRead(3);    // Botão 4
        int quinto = digitalRead(4);    // Botão 5

        // Verifica qual botão (se algum) foi pressionado.
        if (primeiro == LOW){ // Se o botão 1 (pino 0) foi pressionado
            sequencia[i] = nota1; // Armazena a nota associada (passada como parâmetro) na sequência do jogador.
            tone(7,nota1);        // Toca o som correspondente ao botão 1.
            delay(500);           // Espera 500ms (mantém o som e dá tempo de ver).
            lcd.setCursor(0,1);   // Posiciona o cursor na linha 1.
            lcd.print("1");       // Mostra "1" no LCD.
            noTone(7);            // Para o som.

            // Compara a nota inserida pelo jogador (sequencia[i]) com a nota esperada (sequenciaCerta[i]).
            if (sequencia[i] == sequenciaCerta[i]){ // Se acertou
                digitalWrite(5, HIGH); // Acende o LED verde (pino 5).
                digitalWrite(6, LOW);  // Garante que o LED vermelho (pino 6) está apagado.
                lcd.setCursor(0,0);    // Posiciona o cursor na linha 0.
                lcd.print("Acertou!"); // Mostra "Acertou!".
                delay(500);            // Mostra a mensagem por 500ms.
                digitalWrite(5, LOW);  // Apaga o LED verde.
                score++;               // Incrementa a pontuação.
            } else{ // Se errou
                digitalWrite(5, LOW);  // Garante que o LED verde está apagado.
                digitalWrite(6, HIGH); // Acende o LED vermelho.
                lcd.setCursor(0,0);    // Posiciona o cursor na linha 0.
                lcd.print("Errou!  "); // Mostra "Errou!".
                delay(500);            // Mostra a mensagem por 500ms.
                digitalWrite(6, LOW);  // Apaga o LED vermelho.
                vida--;                // Decrementa uma vida.
            }
            i++; // Incrementa o índice para a próxima nota a ser inserida.

        } else if (segundo == LOW){ // Se o botão 2 (pino 1) foi pressionado
            sequencia[i] = nota2;
            tone(7,nota2);
            delay(500);
            lcd.setCursor(0,1);
            lcd.print("2");
            noTone(7);
            if (sequencia[i] == sequenciaCerta[i]){ // Acertou
                digitalWrite(5, HIGH);
                digitalWrite(6, LOW);
                lcd.setCursor(0,0);
                lcd.print("Acertou!");
                delay(500);
                digitalWrite(5, LOW);
                score++;
            } else{ // Errou
                digitalWrite(5, LOW);
                digitalWrite(6, HIGH);
                lcd.setCursor(0,0);
                lcd.print("Errou!  ");
                delay(500);
                digitalWrite(6, LOW);
                vida--;
            }
            i++;

        } else if (terceiro == LOW){ // Se o botão 3 (pino 2) foi pressionado
            sequencia[i] = nota3;
            tone(7,nota3);
            delay(500);
            lcd.setCursor(0,1);
            lcd.print("3");
            noTone(7);
            if (sequencia[i] == sequenciaCerta[i]){ // Acertou
                digitalWrite(5, HIGH);
                digitalWrite(6, LOW);
                lcd.setCursor(0,0);
                lcd.print("Acertou!");
                delay(500);
                digitalWrite(5, LOW);
                score++;
            } else{ // Errou
                digitalWrite(5, LOW);
                digitalWrite(6, HIGH);
                lcd.setCursor(0,0);
                lcd.print("Errou!  ");
                delay(500);
                digitalWrite(6, LOW);
                vida--;
            }
            i++;

        } else if (quarto == LOW){ // Se o botão 4 (pino 3) foi pressionado
            sequencia[i] = nota4;
            tone(7,nota4);
            delay(500);
            lcd.setCursor(0,1);
            lcd.print("4");
            noTone(7);
            if (sequencia[i] == sequenciaCerta[i]){ // Acertou
                digitalWrite(5, HIGH);
                digitalWrite(6, LOW);
                lcd.setCursor(0,0);
                lcd.print("Acertou!");
                delay(500);
                digitalWrite(5, LOW);
                score++;
            } else{ // Errou
                digitalWrite(5, LOW);
                digitalWrite(6, HIGH);
                lcd.setCursor(0,0);
                lcd.print("Errou!  ");
                delay(500);
                digitalWrite(6, LOW);
                vida--;
            }
            i++;

        } else if (quinto == LOW){ // Se o botão 5 (pino 4) foi pressionado
            sequencia[i] = nota5;
            tone(7,nota5);
            delay(500);
            lcd.setCursor(0,1);
            lcd.print("5");
            noTone(7);
            if (sequencia[i] == sequenciaCerta[i]){ // Acertou
                digitalWrite(5, HIGH);
                digitalWrite(6, LOW);
                lcd.setCursor(0,0);
                lcd.print("Acertou!");
                delay(500);
                digitalWrite(5, LOW);
                score++;

            } else{ // Errou
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

        // Após verificar cada botão, atualiza a exibição de vidas no LCD.
        lcd.setCursor(9, 1); // Coluna 9, linha 1.
        lcd.print("Vida: ");
        lcd.setCursor(15, 1); // Coluna 15, linha 1.
        lcd.print(vida);      // Mostra o número atual de vidas.

        // Verifica se o jogador perdeu todas as vidas.
        if (vida == 0){
            delay(1000);        // Espera 1 segundo.
            lcd.clear();        // Limpa o LCD.
            lcd.setCursor(4, 0); // Posiciona para a mensagem de Game Over (original era 8,1 ?)
            lcd.print("GAMEOVER");
            // A exibição do score final não estava aqui originalmente, é feita no loop principal.
            break; // Sai do loop 'while', terminando a vez do jogador.
        }
   } // Fim do loop while

 // --- Fim da função res ---
 vida = 3; // Reseta a variável vida para 3 (embora não seja usada após sair da função).
 // Limpa o array 'sequencia' preenchendo-o com zeros para a próxima rodada.
 for(int k = 0; k < 11; k++) sequencia[k] = 0;
 return j; // Retorna o número de notas que deveriam ter sido acertadas (3, 5 ou 10).
}

// --- Função menuDificuldade() ---
// Gerencia a tela onde o jogador escolhe a dificuldade.
void menuDificuldade(){
  // Loop infinito. A saída é controlada pela mudança da variável global 'estado'.
  while (true){
    lcd.setCursor(0,0); // Linha 0
    lcd.print("Escolha a dificuldade"); // Título do menu

    lcd.setCursor(0,1); // Linha 1
    // Verifica se o botão 1 (pino 1) foi pressionado (LOW).
    // Este botão é usado para navegar/mudar a opção.
    // A função 'hide()' chamada pela interrupção no pino 1 também faz isso.
    // Ter a leitura aqui E na interrupção pode causar incrementos duplos.
    // O ideal seria depender apenas da interrupção 'hide()'.
    // Comentando esta linha para evitar possível comportamento inesperado:
    // if (digitalRead(1) == LOW) dificuldade++;

    // Usa a variável 'dificuldade' (modificada pela interrupção 'hide') para mostrar a opção atual.
    // O operador % 3 garante que o valor fique entre 0, 1 e 2.
    switch (dificuldade % 3) {
      case 0:
        lcd.print("> Facil  "); // Mostra ">" para indicar seleção. Espaços limpam texto anterior.
        break;
      case 1:
        lcd.print("> Medio  ");
        break;
      case 2:
        lcd.print("> Dificil");
        break;
      // O default não é estritamente necessário aqui, mas incluído no original.
      default:
        // estado = 0; // Esta linha no default parece incorreta, pois forçaria a volta ao menu inicial.
                    // Comentando-a, pois o switch já cobre todos os casos de % 3.
        break;
    }
    // Verifica se a variável 'estado' foi alterada para 3 (pela interrupção 'blink' no pino 2).
    // Isso significa que o jogador pressionou o botão 3 para confirmar a seleção.
     if (estado == 3){
        return; // Sai da função menuDificuldade.
     }
     // Não há delay aqui no original, o que pode levar a flickering se a interrupção não tiver debounce.
  }
}

// --- Função loop() ---
// Esta função é o coração do programa, executada repetidamente após o setup().
// Funciona como uma máquina de estados, usando a variável 'estado'.
void loop() {
  // Verifica o valor de 'estado' para decidir o que fazer.
  if(estado == 0){ // Estado 0: Tela de Boas-Vindas
    lcd.setCursor(0, 0); // Linha 0
    lcd.print("Seja bem vindo");
    lcd.setCursor(0, 1); // Linha 1
    lcd.print("Pressione botao 3 p/ iniciar"); // Instrução para o jogador (Botão 3 = Pino 2)
    musicaSelecionada = 0; // Reseta a seleção de música para a próxima vez.
    // Score e dificuldade também poderiam ser resetados aqui para garantir.
    // A variável 'alterado' é resetada aqui implicitamente ou no final do ciclo anterior.
    // O jogo espera aqui até que o botão 3 (pino 2) seja pressionado,
    // o que chama a ISR 'blink()', incrementando 'estado' para 1.

  } else if (estado == 1){ // Estado 1: Seleção de Música
    // Verifica se o botão 1 (pino 1) foi pressionado para mudar a música.
    // Assim como no menuDificuldade, isso pode conflitar com a ISR 'hide()'.
    // Comentando para depender da ISR:
    // if (digitalRead(1) == LOW) musicaSelecionada++;

    lcd.setCursor(0,0); // Linha 0
    lcd.print("Escolha a musica            "); // Título, com espaços para limpar a linha.
    lcd.setCursor(0,1); // Linha 1

    // Mostra a música selecionada com base em 'musicaSelecionada' (modificada pela ISR 'hide').
    // Usa % 5 para ciclar entre as 5 músicas (0 a 4).
    switch (musicaSelecionada % 5) {
      case 0:
        lcd.print("> Musica 1              "); // Mostra ">" e espaços para limpar.
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
      // O default do código original levava de volta ao estado 1, o que é redundante.
      default:
        // estado = 1; // Comentando esta linha.
        break;
    }
    // Espera o botão 3 (pino 2) ser pressionado, chamando 'blink()' e mudando 'estado' para 2.

  } else if (estado == 2){ // Estado 2: Seleção de Dificuldade
    lcd.clear(); // Limpa a tela antes de mostrar o menu.
    menuDificuldade(); // Chama a função que cuida do menu de dificuldade.
    // A função menuDificuldade só retorna quando o botão 3 é pressionado,
    // o que também incrementa 'estado' para 3 (via ISR 'blink').

  } else if (estado == 3) { // Estado 3: Tocar a Sequência de Demonstração
    // A variável 'alterado' é usada como flag para garantir que a música toque só uma vez.
    if (alterado == 0){ // Se for a primeira vez neste estado desde a última rodada.
      score = 0; // Zera o score no início da rodada.
      // Chama a função da música selecionada. A função interna ajustará o comprimento
      // da demonstração com base na variável global 'dificuldade'.
      switch (musicaSelecionada % 5) {
        case 0: musica1(); break;
        case 1: musica2(); break;
        case 2: musica3(); break;
        case 3: musica4(); break;
        case 4: musica5(); break;
      }
      alterado++; // Incrementa 'alterado' para 1, sinalizando que a música já tocou.
      estado++;   // Avança para o estado 4 (vez do jogador).
    }

  // O código original tinha um `else if (alterado == 1)` aqui, que corresponde ao estado 4.
  // Vamos seguir a estrutura original.
  } else if (alterado == 1 ){ // Corresponde ao Estado 4: Vez do Jogador
    // Entra aqui APÓS o estado 3 ter tocado a música e incrementado 'alterado' e 'estado'.
    int notasDaRodada = 0; // Variável para armazenar o retorno de res().

    // Chama a função 'res()' para que o jogador insira a sequência.
    // Passa o índice inicial (0), as notas FIXAS para os botões do jogador,
    // e o array da sequência correta da música selecionada.
    switch (musicaSelecionada % 5) {
      case 0:
        lcd.clear(); // Limpa a tela.
        lcd.setCursor(0,0); // Linha 0.
        lcd.print("Sua vez"); // Avisa o jogador.
        // Chama res() para a música 1.
        notasDaRodada = res( 0, NOTE_CS4, NOTE_A3, NOTE_GS3 ,NOTE_FS3 , NOTE_DS3, sequenciaMusica1);
        // Após res() retornar (jogador terminou ou deu game over):
        // Verifica se o jogador acertou todas as notas necessárias para aquela dificuldade.
        // A lógica original compara `score == res(...) + 1`. O +1 é peculiar.
        // Pode ser para compensar algo ou um pequeno erro. Mantendo como está.
        if (score == notasDaRodada + 1){ // Se a pontuação for igual ao esperado + 1
          lcd.setCursor(0,0); // Linha 0
          lcd.print("Parabens!    "); // Mensagem de sucesso.
          delay(2000); // Mostra por 2 segundos.
          lcd.clear(); // Limpa a tela.
        }
        // Mostra o score final da rodada, independentemente de ter ganhado ou perdido (desde que não seja game over dentro de res).
        lcd.setCursor(0,0);
        lcd.print("Score: ");
        lcd.setCursor(8,0);
        lcd.print(score);
        musicaSelecionada = 0; // Reseta a seleção de música (poderia ser feito no estado 0).
        alterado++; // Incrementa 'alterado' para 2, sinalizando fim da vez do jogador.
        break;

      case 1:
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Sua vez");
        notasDaRodada = res( 0, NOTE_CS4, NOTE_A3, NOTE_GS3 ,NOTE_FS3 , NOTE_DS3, sequenciaMusica2);
        // Para as outras músicas, a comparação original é `score == res(...)`.
        if (score == notasDaRodada){ // Se acertou todas as notas da dificuldade.
          lcd.setCursor(0,0);
          lcd.print("Parabens!    ");
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
        notasDaRodada = res( 0, NOTE_CS4, NOTE_A3, NOTE_GS3 ,NOTE_FS3 , NOTE_DS3, sequenciaMusica3);
        if (score == notasDaRodada){
          lcd.setCursor(0,0);
          lcd.print("Parabens!    ");
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
        notasDaRodada = res( 0, NOTE_CS4, NOTE_A3, NOTE_GS3 ,NOTE_FS3 , NOTE_DS3, sequenciaMusica4);
        if (score == notasDaRodada){
          lcd.setCursor(0,0);
          lcd.print("Parabens!    ");
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
        notasDaRodada = res( 0, NOTE_CS4, NOTE_A3, NOTE_GS3 ,NOTE_FS3 , NOTE_DS3, sequenciaMusica5);
        if (score == notasDaRodada){
          lcd.setCursor(0,0);
          lcd.print("Parabens!    ");
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

      // O default original levava ao estado 0, o que parece um fallback razoável.
      default:
        estado =0;
        break;
    } // Fim do switch (musicaSelecionada % 5) dentro de alterado == 1

  } else if (alterado > 1){ // Estado de Finalização/Reset da Rodada
    // Entra aqui após a vez do jogador terminar (alterado foi para 2).
    estado = 0;     // Define o próximo estado como 0 (volta para a tela inicial).
    alterado = 0;   // Reseta a flag 'alterado'.
    delay(3000);    // Espera 3 segundos (mostrando o score final que foi exibido antes).
    lcd.clear();    // Limpa a tela para preparar a volta ao estado 0.
  }
} // Fim da função loop()

// --- Funções de Interrupção (ISRs) ---

// ISR chamada quando o pino 2 (Botão 3) é pressionado (FALLING edge).
void blink() {
  // Simplesmente incrementa a variável 'estado'.
  // A condição original `if (estado <= 3)` limitava o incremento até o estado 4.
  if (estado <= 3){ // Impede que 'estado' passe de 4 indefinidamente.
    estado ++;
  }
  
}

// ISR chamada quando o pino 1 (Botão 2) é pressionado (FALLING edge).
void hide(){
  // Verifica o estado atual para decidir qual variável incrementar.
  if (estado == 1){ // Se está na seleção de música
    musicaSelecionada++; // Incrementa para mudar a opção de música.
  }
  if (estado == 2) { // Se está na seleção de dificuldade
    dificuldade++;   // Incrementa para mudar a opção de dificuldade.
  }
}
