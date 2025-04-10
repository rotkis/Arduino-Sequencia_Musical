# **Projeto Arduino**

## Objetivo 

O objetivo do projeto apresentado nas imagens é desenvolver um jogo de memória musical utilizando um sistema de computação embarcada. O jogo desafia o jogador a memorizar e reproduzir sequências musicais tocadas pelo sistema, usando botões correspondentes às notas.

## Principais funcionalidades:

* **Sequências Musicais:** O Arduino toca sequências pré-definidas de notas.
* **Interação do Jogador:** O jogador utiliza 5 botões para repetir a sequência ou navegar nos menus.
* **Feedback Visual:**
    * Um display LCD 16x2 mostra menus, instruções, o botão a ser pressionado durante a demonstração, mensagens de acerto/erro, pontuação e vidas.
    * Um LED verde acende ao acertar uma nota.
    * Um LED vermelho acende ao errar uma nota.
* **Feedback Sonoro:** Um buzzer toca as notas musicais da sequência e quando o jogador pressiona os botões.
* **Múltiplas Músicas:** O jogo oferece 5 sequências musicais diferentes para escolher.
* **Níveis de Dificuldade:**
    * Fácil: Sequências mais curtas.
    * Médio: Sequências de comprimento intermediário.
    * Difícil: Sequências completas.
* **Sistema de Vidas:** O jogador começa com 3 vidas e perde uma a cada erro.
* **Pontuação:** O jogador ganha pontos ao acertar as notas.
* **Game Over:** O jogo termina se o jogador perder todas as vidas.

   ## Hardware Necessário

* 1x Placa Arduino (Uno)
* 1x Display LCD 16x2 (com pinagem paralela)
* 1x Potenciômetro de 10k (para ajuste de contraste do LCD)
* 1x Buzzer passivo
* 5x Botões de pressão (Push buttons)
* 1x LED Verde
* 1x LED Vermelho
* 2x Resistores ( 330Ω, para os LEDs)
* 1x Protoboard (Placa de ensaio)
* Fios Jumper

## Software Necessário

* [Arduino IDE](https://www.arduino.cc/en/software)
* Biblioteca `LiquidCrystal.h` (geralmente já incluída na Arduino IDE)

## Montagem / Conexões

Siga as conexões abaixo para montar o circuito:

**Display LCD 16x2 (Paralelo):**

* LCD RS -> Arduino Pino 13
* LCD E (Enable) -> Arduino Pino 12
* LCD D4 -> Arduino Pino 11
* LCD D5 -> Arduino Pino 10
* LCD D6 -> Arduino Pino 9
* LCD D7 -> Arduino Pino 8
* LCD VSS -> Arduino GND
* LCD VDD -> Arduino 5V
* LCD VO -> Pino central do Potenciômetro 10k
* Extremos do Potenciômetro -> Arduino 5V e GND (respectivamente)
* LCD A  -> Arduino 5V (ou via resistor 220Ω)
* LCD K  -> Arduino GND

**Componentes de Feedback:**

* Buzzer (+) -> Arduino Pino 7
* Buzzer (-) -> Arduino GND
* LED Verde  -> Resistor -> Arduino Pino 5
* LED Verde  -> Arduino GND
* LED Vermelho -> Resistor -> Arduino Pino 6
* LED Vermelho  -> Arduino GND

**Botões (Usando INPUT_PULLUP):**

* Botão 1 (Nota 1) -> Arduino Pino 0 e Arduino GND
* Botão 2 (Navegação / Nota 2) -> Arduino Pino 1 e Arduino GND
* Botão 3 (Confirmação / Nota 3) -> Arduino Pino 2 e Arduino GND
* Botão 4 (Nota 4) -> Arduino Pino 3 e Arduino GND
* Botão 5 (Nota 5) -> Arduino Pino 4 e Arduino GND
    *(Nota: Ao usar `INPUT_PULLUP`, o botão apenas conecta o pino ao GND quando pressionado. Não são necessários resistores externos para os botões).*

## Como Jogar

1.  **Ligar:** Conecte o Arduino ao computador ou a uma fonte de energia.
2.  **Tela Inicial:** O LCD exibirá uma mensagem de boas-vindas e pedirá para pressionar o Botão 3.
3.  **Selecionar Música:** Pressione o **Botão 3** (Confirmar/Avançar - Pino 2). A tela de seleção de música aparecerá. Use o **Botão 2** (Navegar - Pino 1) para ciclar entre as "Musica 1" a "Musica 5". Pressione o **Botão 3** para confirmar a escolha.
4.  **Selecionar Dificuldade:** A tela de seleção de dificuldade aparecerá. Use o **Botão 2** para ciclar entre "Facil", "Medio" e "Dificil". Pressione o **Botão 3** para confirmar.
5.  **Ouvir a Sequência:** O Arduino tocará a sequência musical escolhida, mostrando no LCD o número do botão correspondente (1 a 5) para cada nota. A duração da sequência depende da dificuldade.
6.  **Repetir a Sequência:** O LCD mostrará "Sua vez!". Use os **Botões 1 a 5** (Pinos 0 a 4) para repetir a sequência na ordem correta.
7.  **Feedback:**
    * Ao acertar: O LED verde pisca, o LCD mostra "Acertou!", e você ganha um ponto.
    * Ao errar: O LED vermelho pisca, o LCD mostra "Errou!", e você perde uma vida.
8.  **Fim da Rodada / Jogo:**
    * Se completar a sequência corretamente (de acordo com a dificuldade), o LCD mostra "Parabens!" e a sua pontuação.
    * Se errar e perder todas as vidas, o LCD mostra "GAMEOVER".
    * Após alguns segundos, o jogo retorna automaticamente à tela inicial.

## Estrutura do Código (Visão Geral)

* **`setup()`:** Inicializa o LCD, configura os pinos (LEDs, buzzer, botões) e as interrupções dos botões 2 e 3.
* **`loop()`:** Funciona como uma máquina de estados controlada pela variável `estado`. Gerencia as telas de menu, chama as funções de demonstração e a função de jogo do usuário.
* **`musicaX()` (1 a 5):** Funções responsáveis por tocar a sequência de demonstração de cada música, mostrando o botão correspondente no LCD. A duração é ajustada pela variável `dificuldade`.
* **`res()`:** Função principal da jogabilidade do usuário. Lê os botões pressionados, compara com a sequência correta, atualiza score/vidas e fornece feedback.
* **`menuDificuldade()`:** Exibe e gerencia a interação no menu de seleção de dificuldade.
* **`blink()` e `hide()`:** Funções de Interrupção (ISRs) chamadas pelos botões 3 e 2, respectivamente, para avançar estados ou navegar nos menus.

