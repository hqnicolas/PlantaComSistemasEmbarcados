# PlantaComSistemasEmbarcados

## Sistema de Irrigação Automatizada por Umidade do Solo

Sistema desenvolvido para Arduino Uno.

### Situação-problema

Uma horta automatizada pode desperdiçar água ao irrigar quando o solo já possui umidade suficiente ou tentar ligar a bomba com o reservatório vazio. O sistema deve evitar essas situações e realizar a rega em ciclos temporizados.

### Entradas e saídas digitais

- **Entradas:** botão de irrigação manual, configurado com pull-up interno, e chave boia para detectar o nível mínimo do reservatório.
- **Saídas:** relé da eletrobomba e LED de alerta de falta d'água.

### Sensor de umidade do solo

O sistema utiliza um sensor higrômetro capacitivo, com leitura analógica calibrada para medir a umidade do solo.

### Display

LCD de 20 caracteres × 4 linhas, controlado com a biblioteca `LiquidCrystal` e os métodos demonstrados nos [Exemplos](Exemplos/). Para este display, a inicialização usa `lcd.begin(20, 4)`; a posição e o conteúdo são definidos com `lcd.setCursor` e `lcd.print`.

- **Construção:** LCD, moldura (bezel), Zebra e PCB, com backlight LED amarelo-verde de +5 V.
- **Tipo:** STN, modo amarelo-verde, transflectivo, posição 6 horas.
- **Alimentação:** entrada única de +5 V. Para acionamento em 3,3 V, há uma versão especial com conversor DC/DC integrado.
- **Controlador:** ST7066U-0A.

### Implementação

O projeto pode ser montado em hardware físico ou simulado no [Wokwi](https://wokwi.com/). Na simulação, o sensor higrômetro pode ser substituído por um potenciômetro.

#### Circuito no Wokwi

Em um projeto Arduino Uno no Wokwi, use o [diagrama do projeto](diagram.json) e carregue o firmware de [teste do display](sketch.ino) na aba `sketch.ino`. O programa segue a pinagem do Exercício 05 da Aula 07, inicializa o LCD com `lcd.begin(20, 4)`, mostra os caracteres nas 20 colunas, atualiza um contador na segunda linha e pisca o LED integrado da placa (pino 13) a cada 500 ms. Durante este teste, o relé e o LED de alerta permanecem desligados.

O firmware compilado para Arduino Uno está disponível em [DisplayTest.ino.hex](build/uno/DisplayTest.ino.hex).

| Componente | Pino no Arduino Uno | Comportamento esperado no firmware |
| --- | --- | --- |
| LCD paralelo | D8 (RS), D9 (E), D4 a D7 (dados) | Modo de 4 bits, com RW ligado ao GND |
| Botão de rega manual | D10 | `INPUT_PULLUP`, pressionado em `LOW` |
| Chave boia simulada | D11 | `INPUT_PULLUP`, esquerda em `LOW` (nível OK) e direita em `HIGH` (nível baixo, posição inicial) |
| Potenciômetro de umidade | A0 | `analogRead(A0)`, com valores de 0 a 1023 |
| LED vermelho de alerta | D12 | Acende em `HIGH` |
| LED integrado do Uno | D13 (`LED_BUILTIN`) | Pisca a cada 500 ms |
| Módulo relé | D3 | O contato COM–NO alimenta o LED verde que representa a bomba |

Este firmware verifica o display. A lógica de leitura dos sensores, bloqueio por nível baixo e temporização da rega ainda precisa ser adicionada para operar o sistema de irrigação.
