const readline = require('readline');
const { TechnologicalLine, Workshop, LaborPayment } = require('./technologicalLine');

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout
});

function askQuestion(query, defaultValue) {
  return new Promise((resolve) => {
    rl.question(`${query} (по умолчанию: ${defaultValue}): `, (input) => {
      resolve(input || defaultValue);
    });
  });
}

async function main() {
  const hourlyRate = parseFloat(await askQuestion('Введите почасовую оплату в рублях', 335));
  const bonusRate = parseFloat(await askQuestion('Введите бонус за выполнение плана (в долях)', 0.17));
  const extraBonusRate = parseFloat(await askQuestion('Введите доплату за перевыполнение плана (в долях)', 0.215));
  const costPerUnit = parseFloat(await askQuestion('Введите себестоимость одной покрышки в рублях', 726));

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

  const laborPaymentWorkshop = new LaborPayment(lines, hourlyRate, bonusRate, extraBonusRate, costPerUnit);

  // Вывод информации об оплате труда
  laborPaymentWorkshop.printLaborPayment(shiftDurationMinutes, targetOutput);
  // Вывод информации о зарплате всех рабочих
  laborPaymentWorkshop.printTotalLaborPayment(shiftDurationMinutes, targetOutput);

  rl.close();
}

main();