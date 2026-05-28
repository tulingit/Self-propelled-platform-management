#include <IRremote.h>

IRrecv irrecv(13);
decode_results results;

#define FORWARD_CODE      0xFF18E7
#define BACKWARD_CODE     0xFF4AB5
#define LEFT_CODE         0xFF10EF
#define RIGHT_CODE        0xFF5AA5
#define STOP_CODE         0xFF38C7

#define FORWARD 1
#define BACKWARD -1
#define STOP     0

const int motor1SpeedPin = 5;
const int motor1Direction1Pin = A0;
const int motor1Direction2Pin = A1;

const int motor2SpeedPin = 6;
const int motor2Direction1Pin = A2;
const int motor2Direction2Pin = A3;

int motor1Speed = 0;
int motor2Speed = 0;

// Переменная для хранения последнего запомненного кода кнопки
unsigned long lastButtonCode = 0;

// Переменная для хранения времени последнего срабатывания кнопки
unsigned long lastButtonTime = 0;

// Переменная для задания времени задержки перед повторным выводом последнего кода
const unsigned long repeatDelay = 500;

void setup() {
  irrecv.enableIRIn();
  pinMode(motor1SpeedPin, OUTPUT);
  pinMode(motor1Direction1Pin, OUTPUT);
  pinMode(motor1Direction2Pin, OUTPUT);

  pinMode(motor2SpeedPin, OUTPUT);
  pinMode(motor2Direction1Pin, OUTPUT);
  pinMode(motor2Direction2Pin, OUTPUT);

  Serial.begin(9600); // Инициализация монитора порта
}

// Функция для управления двигателем 1
void controlMotor1(int speed, int direction) {
  if (speed >= 0) {
    digitalWrite(motor1Direction1Pin, HIGH);
    digitalWrite(motor1Direction2Pin, LOW);
  } else {
    digitalWrite(motor1Direction1Pin, LOW);
    digitalWrite(motor1Direction2Pin, HIGH);
    speed = -speed;
  }
  analogWrite(motor1SpeedPin, speed);
}

// Функция для управления двигателем 2
void controlMotor2(int speed, int direction) {
  if (speed >= 0) {
    digitalWrite(motor2Direction1Pin, HIGH);
    digitalWrite(motor2Direction2Pin, LOW);
  } else {
    digitalWrite(motor2Direction1Pin, LOW);
    digitalWrite(motor2Direction2Pin, HIGH);
    speed = -speed;
  }
  analogWrite(motor2SpeedPin, speed);
}

void loop() {
  if (irrecv.decode(&results)) {
    // Получаем значение кода
    unsigned long currentCode = results.value;

    // Если текущее значение кода отличается от последнего запомненного,
    // сбрасываем таймер времени последнего срабатывания кнопки
    if (currentCode != lastButtonCode) {
      lastButtonTime = millis();
    }

    // Если прошло достаточно времени после последнего срабатывания кнопки
    // и текущее значение кода не равно 0xFFFFFFFF (FFFFFFF), выводим его
    if (millis() - lastButtonTime >= repeatDelay && currentCode != 0xFFFFFFFF) {
      lastButtonCode = currentCode;
    }

    // Если значения отличаются, то это уникальный сигнал кнопки,
    // и мы можем его обработать
    switch (currentCode) {
      case FORWARD_CODE:
        // Увеличиваем скорость вперед
        motor1Speed = constrain(motor1Speed + 20, 0, 255);
        motor2Speed = constrain(motor2Speed + 20, 0, 255);
        break;
      case BACKWARD_CODE:
        // Увеличиваем скорость назад
        motor1Speed = constrain(motor1Speed - 20, -255, 0);
        motor2Speed = constrain(motor2Speed - 20, -255, 0);
        break;
      case RIGHT_CODE:
        // Поворот направо
        motor1Speed = constrain(motor1Speed + 20, 0, 255);
        motor2Speed = constrain(motor2Speed - 20, -255, 0);
        break;
      case LEFT_CODE:
        // Поворот налево
        motor1Speed = constrain(motor1Speed - 20, -255, 0);
        motor2Speed = constrain(motor2Speed + 20, 0, 255);
        break;
      case STOP_CODE:
        // Остановка
        motor1Speed = 0;
        motor2Speed = 0;
        break;
      // Другие кейсы для других кнопок пульта (если необходимо)
    }

    irrecv.resume(); // Продолжаем прослушивание ИК сигналов
  }

  // Устанавливаем скорость моторов
  controlMotor1(motor1Speed, motor1Speed >= 0 ? FORWARD : BACKWARD);
  controlMotor2(motor2Speed, motor2Speed >= 0 ? FORWARD : BACKWARD);

  // Выводим последнее запомненное значение кода кнопки в монитор порта
  Serial.println(lastButtonCode);
}
