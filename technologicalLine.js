class TechnologicalLine {
    constructor(minProductionRate, maxProductionRate, numberOfWorkers, shiftDurationMinutes) {
        this.productionRates = this.generateProductionRates(minProductionRate, maxProductionRate, shiftDurationMinutes);
        this.numberOfWorkers = numberOfWorkers; // количество человек на линии
    }

    // Метод для получения информации о линии
    getLineInfo() {
        const averageProductionRate = this.calculateAverageProductionRate();
        return `Средняя производительность линии: ${parseFloat(averageProductionRate.toFixed(2))},\nКоличество человек на линии: ${this.numberOfWorkers}`;
    }

    // Метод для расчета общего выпуска за смену
    calculateShiftOutput() {
        return this.productionRates.reduce((total, rate) => total + rate, 0);
    }

    // Метод для генерации массива производительности на каждую минуту смены
    generateProductionRates(min, max, duration) {
        const rates = [];
        for (let i = 0; i < duration; i++) {
            rates.push(this.getRandomProductionRate(min, max));
        }
        return rates;
    }

    // Метод для генерации случайной производительности в заданном диапазоне
    getRandomProductionRate(min, max) {
        return Math.floor(Math.random() * (max - min + 1)) + min;
    }

    // Метод для расчета средней производительности
    calculateAverageProductionRate() {
        const totalProduction = this.calculateShiftOutput();
        return totalProduction / this.productionRates.length;
    }
}

class Workshop {
    constructor(lines) {
        this.lines = lines; // массив технологических линий
    }

    // Метод для расчета общего выпуска цеха за смену
    calculateTotalShiftOutput() {
        let totalOutput = 0;
        this.lines.forEach(line => {
            totalOutput += line.calculateShiftOutput();
        });
        return totalOutput;
    }

    // Метод для проверки выполнения плана выпуска
    isProductionPlanMet(targetOutput, shiftDurationMinutes) {
        const totalOutput = this.calculateTotalShiftOutput(shiftDurationMinutes);
        return totalOutput >= targetOutput;
    }

    // Новый метод для вывода информации о выпуске
    printTotalShiftOutput(shiftDurationMinutes) {
        const totalOutput = this.calculateTotalShiftOutput(shiftDurationMinutes);
        console.log(`Общий выпуск за смену: ${totalOutput} шт.`);
    }

    checkProductionPlan(targetOutput, shiftDurationMinutes) {
        const totalOutput = this.calculateTotalShiftOutput(shiftDurationMinutes);
        const difference = totalOutput - targetOutput;
        console.log(`План выпуска: ${targetOutput} шт.`);
        if (difference > 0) {
            console.log(`План выпуска перевыполнен на ${difference} шт.`);
        } else if (difference < 0) {
            console.log(`План выпуска недовыполнен на ${Math.abs(difference)} шт.`);
        } else {
            console.log('План выпуска выполнен точно.');
        }
    }

    // Новый метод для вывода информации о всех линиях
    printAllLinesInfo() {
        this.lines.forEach((line, index) => {
            console.log(`Линия ${index + 1}: ${line.getLineInfo()}`);
        });
    }
}

// Пример использования
const workersPerLine = 2;//количество людей на линии
const shiftDurationMinutes = 8 * 60; // 8 часов в минутах
const targetOutput = 2880;

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

