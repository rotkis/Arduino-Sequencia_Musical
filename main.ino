void setup() {
  lcd.begin(16, 2);
  pinMode(bot1, INPUT);
  lcd.setCursor(0, 0);
  lcd.print("Seja bem vindo");
  lcd.setCursor(0, 1);
  lcd.print("Pressione p/ iniciar");
}

void loop() {
  int estadoBotao = digitalRead(bot1);

  if (estadoBotao == HIGH && !jogoIniciado) {
    jogoIniciado = true;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Iniciando o jogo");
    lcd.setCursor(0, 1);
    lcd.print("Escolha a musica");
    delay(2000);
}
