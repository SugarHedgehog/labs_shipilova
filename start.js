const readline = require('readline');
const { TechnologicalLine, Workshop, LaborPayment } = require('./technologicalLine');

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout
});

function askQuestion(query, defaultValue, validate) {
  return new Promise((resolve) => {
    const ask = () => {
      rl.question(`${query} (по умолчанию: ${defaultValue}): `, (input) => {
        const value = input || defaultValue;
        if (validate(value)) {
          resolve(value);
        } else {
          console.log('Неверный ввод. Пожалуйста, попробуйте снова.');
          ask();
        }
      });
    };
    ask();
  });
}

async function main() {
  const workersPerLine = parseInt(await askQuestion(
    'Введите количество людей на линии', 
    2, 
    (value) => !isNaN(value) && Number.isInteger(parseFloat(value)) && value > 0
  ));

  const shiftDurationMinutes = parseInt(await askQuestion(
    'Введите длительность смены в минутах', 
    8 * 60, 
    (value) => !isNaN(value) && Number.isInteger(parseFloat(value)) && value > 0
  ));

  const targetOutput = parseInt(await askQuestion(
    'Введите план на смену', 
    2880, 
    (value) => !isNaN(value) && Number.isInteger(parseFloat(value)) && value > 0
  ));

  const hourlyRate = parseFloat(await askQuestion(
    'Введите почасовую оплату в рублях', 
    335, 
    (value) => !isNaN(value) && value > 0
  ));
  
  const bonusRate = parseFloat(await askQuestion(
    'Введите бонус за выполнение плана (в долях)', 
    0.17, 
    (value) => !isNaN(value) && value >= 0 && value <= 1
  ));
  
  const extraBonusRate = parseFloat(await askQuestion(
    'Введите доплату за перевыполнение плана (в долях)', 
    0.215, 
    (value) => !isNaN(value) && value >= 0 && value <= 1
  ));
  
  const costPerUnit = parseFloat(await askQuestion(
    'Введите себестоимость одной покрышки в рублях', 
    726, 
    (value) => !isNaN(value) && value > 0
  ));

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