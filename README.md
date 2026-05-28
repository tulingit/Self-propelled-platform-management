# Self-Propelled Platform Management 🤖

Система управления **самоходной платформой на Arduino** с поддержкой драйвера двигателя **L298N** и управлением через **ИК-пульт**.

[![Arduino](https://img.shields.io/badge/Arduino-1.8+-blue.svg)](https://www.arduino.cc/)
[![C++](https://img.shields.io/badge/C%2B%2B-11-orange.svg)](https://isocpp.org/)
[![L298N](https://img.shields.io/badge/Driver-L298N-green.svg)](https://www.infineon.com/)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

## 🎯 О проекте

Код предназначен для управления самоходной платформой на базе **Arduino**. Реализована поддержка драйвера двигателя **L298N** и других аналогичных драйверов, а также управление через **ИК-пульт дистанционного управления**.

### Основные возможности

- 🚀 Управление самоходной платформой через Arduino
- ⚙️ Поддержка драйвера **L298N** и совместимых драйверов
- 📡 Управление через **ИК-пульт** (можно заменить на любой другой способ)
- 🔄 Гибкая настройка значений кнопок для вашего пульта
- 🎮 Управление движением: вперёд, назад, влево, вправо, остановка

### Поддерживаемое оборудование

| Компонент | Описание |
|-----------|----------|
| **Arduino** |任意 Arduino-плата (UNO, Nano, Mega и др.) |
| **Драйвер двигателя** | L298N и совместимые (L293D, TB6612FNG и др.) |
| **ИК-пульт** | Любой ИК-пульт с NEC-протоколом |
| **ИК-приёмник** | TSOP38238, VS1838B или совместимые |
| **Двигатели** | 2× DC-мотора для колёсной базы |

## 📋 Комплектующие

### Необходимые компоненты
├── Arduino Board (UNO/Nano/Mega)
├── L298N Motor Driver (или аналог)
├── IR Remote Control (ИК-пульт)
├── IR Receiver Module (TSOP38238/VS1838B)
├── 2× DC Motors (для колёс)
├── Колёсная платформа (шасси)
├── Батарея (7.4V-12V)
└── Провода и макетная плата


## 🚀 Быстрый старт

### Установка

1. **Склонируйте репозиторий:**
```bash
git clone https://github.com/ваш-юзернейм/Self-propelled-platform-management.git
cd Self-propelled-platform-management
```

2. **Установите библиотеки в Arduino IDE:**
- [IRremote](https://github.com/IRremote/IRremote) — для работы с ИК-пультом
- Откройте `platform.ino` в Arduino IDE

3. **Настройте значения кнопок пульта:**
```cpp
// ВНИМАНИЕ: Замените значения на ваши!
#define BUTTON_UP     0xFFA25D    // Кнопка "вперёд"
#define BUTTON_DOWN   0xFFE21D    // Кнопка "назад"
#define BUTTON_LEFT   0xFF629D    // Кнопка "влево"
#define BUTTON_RIGHT  0xFFA857    // Кнопка "вправо"
#define BUTTON_STOP   0xFF6897    // Кнопка "стоп"
```

4. **Загрузите код в Arduino:**
- Выберите правильную плату и порт в Arduino IDE
- Нажмите **Upload** (Загрузить)

## ⚙️ Настройка ИК-пульта

### Определение кодов кнопок

Перед использованием необходимо определить коды кнопок вашего пульта:

```cpp
// Пример кода для определения кодов кнопок
#include <IRremote.hpp>

void setup() {
  Serial.begin(9600);
  IRrecv.begin(11);  // Пин ИК-приёмника
  IRrecv.enableIROut(38);
}

void loop() {
  decode_results results;
  if (IRrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    IRrecv.resume();
  }
  delay(100);
}
```

**Запустите этот код, нажмите кнопки на пульте и запишите значения из Serial Monitor.**

### Замена на другие коды кнопок

```cpp
// После определения замените в основном коде:
#define BUTTON_UP     <ВАШ_КОД_ВПЕРЁД>    // Например: 0xFFA25D
#define BUTTON_DOWN   <ВАШ_КОД_НАЗАД>     // Например: 0xFFE21D
#define BUTTON_LEFT   <ВАШ_КОД_ВЛЕВО>     // Например: 0xFF629D
#define BUTTON_RIGHT  <ВАШ_КОД_ВПРАВО>    // Например: 0xFFA857
#define BUTTON_STOP   <ВАШ_КОД_СТОП>      // Например: 0xFF6897
```
