const { TechnologicalLine, Workshop, LaborPayment } = require('./technologicalLine');

// Пример использования
const workersPerLine = 2;// количество людей на линии
const shiftDurationMinutes = 8 * 60; // 8 часов в минутах
const targetOutput = 2880; // план на смену

const lines = [
    new TechnologicalLine(2, 3, workersPerLine, shiftDurationMinutes),
    new TechnologicalLine(2, 3, workersPerLine, shiftDurationMinutes),
    new TechnologicalLine(2, 3, workersPerLine, shiftDurationMinutes),
    new TechnologicalLine(2, 3, workersPerLine, shiftDurationMinutes)
];
const workshop = new Workshop(lines);

// Вывода информации о выполнении плана
workshop.checkProductionPlan(targetOutput, shiftDurationMinutes);
// Вывода информации о выпуске
workshop.printTotalShiftOutput(shiftDurationMinutes);
// Вывода информации о цехе
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