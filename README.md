
# README

## Обзор

Этот модуль предоставляет симуляцию производственной системы, включая классы для управления технологическими линиями, цехами и расчетами оплаты труда. Он позволяет вычислять производственные показатели, проверять выполнение производственного плана и рассчитывать оплату труда на основе производительности.

## Классы

### `TechnologicalLine`

Представляет собой одну производственную линию с следующими характеристиками:

- **Параметры конструктора:**
  - `minProductionRate`: Минимальная производительность в минуту.
  - `maxProductionRate`: Максимальная производительность в минуту.
  - `numberOfWorkers`: Количество работников на линии.
  - `shiftDurationMinutes`: Длительность смены в минутах.

- **Методы:**
  - `getLineInfo()`: Возвращает информацию о линии, включая среднюю производительность и количество работников.
  - `calculateShiftOutput()`: Рассчитывает общий выпуск за смену.
  - `generateProductionRates(min, max, duration)`: Генерирует массив производительности на каждую минуту смены.
  - `getRandomProductionRate(min, max)`: Генерирует случайную производительность в заданном диапазоне.
  - `calculateAverageProductionRate()`: Рассчитывает среднюю производительность за смену.

### `Workshop`

представляет собой цех с несколькими производственными линиями и предоставляет следующие функции:

- **Параметры конструктора:**
  - `lines`: Массив экземпляров `TechnologicalLine`.

- **Методы:**
  - `calculateTotalShiftOutput()`: Рассчитывает общий выпуск цеха за смену.
  - `isProductionPlanMet(targetOutput, shiftDurationMinutes)`: Проверяет выполнение производственного плана.
  - `printTotalShiftOutput(shiftDurationMinutes)`: Выводит общий выпуск за смену.
  - `checkProductionPlan(targetOutput, shiftDurationMinutes)`: Выводит информацию о статусе выполнения производственного плана.
  - `printAllLinesInfo()`: Выводит информацию о всех линиях в цехе.

### `LaborPayment`

Расширяет `Workshop` для включения расчетов оплаты труда:

- **Параметры конструктора:**
  - `lines`: Массив экземпляров `TechnologicalLine`.
  - `hourlyRate`: Почасовая оплата в рублях.
  - `bonusRate`: Бонус за выполнение плана.
  - `extraBonusRate`: Доплата за перевыполнение плана.
  - `costPerUnit`: Себестоимость одной единицы продукции в рублях.

- **Методы:**
  - `calculateLaborPayment(shiftDurationMinutes, targetOutput)`: Рассчитывает оплату труда за смену.
  - `printLaborPayment(shiftDurationMinutes, targetOutput)`: Выводит информацию об оплате труда за смену на одного рабочего.
  - `calculateTotalLaborPayment(shiftDurationMinutes, targetOutput)`: Рассчитывает общую зарплату всех рабочих в цехе.
  - `printTotalLaborPayment(shiftDurationMinutes, targetOutput)`: Выводит информацию о зарплате всех рабочих за смену.

## Пример использования

```javascript
const { TechnologicalLine, Workshop, LaborPayment } = require('./technologicalLine');

const workersPerLine = 2; // количество людей на линии
const shiftDurationMinutes = 8 * 60; // 8 часов в минутах
const targetOutput = 2880; // план на смену

const lines = [
    new TechnologicalLine(2, 3, workersPerLine, shiftDurationMinutes),
    new TechnologicalLine(2, 3, workersPerLine, shiftDurationMinutes),
    new TechnologicalLine(2, 3, workersPerLine, shiftDurationMinutes),
    new TechnologicalLine(2, 3, workersPerLine, shiftDurationMinutes)
];
const workshop = new Workshop(lines);

// Вывод информации о выполнении плана
workshop.checkProductionPlan(targetOutput, shiftDurationMinutes);
// Вывод информации о выпуске
workshop.printTotalShiftOutput(shiftDurationMinutes);
// Вывод информации о цехе
workshop.printAllLinesInfo();

const hourlyRate = 335; // почасовая оплата в рублях
const bonusRate = 0.17; // бонус за выполнение плана
const extraBonusRate = 0.215; // доплата за перевыполнение плана
const costPerUnit = 726; // себестоимость одной покрышки в рублях

const laborPaymentWorkshop = new LaborPayment(lines, hourlyRate, bonusRate, extraBonusRate, costPerUnit);

// Вывод информации об оплате труда
laborPaymentWorkshop.printLaborPayment(shiftDurationMinutes, targetOutput);
// Вывод информации о зарплате всех рабочих
laborPaymentWorkshop.printTotalLaborPayment(shiftDurationMinutes, targetOutput);
```

Этот пример демонстрирует создание нескольких технологических линий, расчет общего выпуска цеха, проверку выполнения производственного плана и расчет оплаты труда.
