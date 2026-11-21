#include <LiquidCrystal.h>

const uint8_t LCD_RS = 8;
const uint8_t LCD_ENABLE = 9;
const uint8_t LCD_D4 = 4;
const uint8_t LCD_D5 = 5;
const uint8_t LCD_D6 = 6;
const uint8_t LCD_D7 = 7;

const uint8_t PIN_RELE = 3;
const uint8_t PIN_LED_ALERTA = 12;

const unsigned long INTERVALO_ATUALIZACAO_MS = 1000;
const unsigned long INTERVALO_PISCADA_MS = 500;

LiquidCrystal lcd(LCD_RS, LCD_ENABLE, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

unsigned long ultimaAtualizacao = 0;
unsigned long ultimaPiscada = 0;
unsigned int segundos = 0;
bool ledIntegradoLigado = false;

void atualizarContador() {
  char linha[21] = "SEGUNDOS: 0000 s    ";

  linha[10] = '0' + (segundos / 1000) % 10;
  linha[11] = '0' + (segundos / 100) % 10;
  linha[12] = '0' + (segundos / 10) % 10;
  linha[13] = '0' + segundos % 10;

  lcd.setCursor(0, 1);
  lcd.print(linha);
}

void setup() {
  pinMode(PIN_RELE, OUTPUT);
  digitalWrite(PIN_RELE, LOW);
  pinMode(PIN_LED_ALERTA, OUTPUT);
  digitalWrite(PIN_LED_ALERTA, LOW);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  lcd.begin(20, 4);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("TESTE LCD 20x4  OK");

  lcd.setCursor(0, 2);
  lcd.print("01234567890123456789");

  lcd.setCursor(0, 3);
  lcd.print("ABCDEFGHIJKLMNOPQRST");

  atualizarContador();
  ultimaAtualizacao = millis();
  ultimaPiscada = ultimaAtualizacao;
}

void loop() {
  const unsigned long agora = millis();

  if (agora - ultimaPiscada >= INTERVALO_PISCADA_MS) {
    ultimaPiscada += INTERVALO_PISCADA_MS;
    ledIntegradoLigado = !ledIntegradoLigado;
    digitalWrite(LED_BUILTIN, ledIntegradoLigado ? HIGH : LOW);
  }

  if (agora - ultimaAtualizacao >= INTERVALO_ATUALIZACAO_MS) {
    ultimaAtualizacao += INTERVALO_ATUALIZACAO_MS;
    segundos = (segundos + 1) % 10000;
    atualizarContador();
  }
}
