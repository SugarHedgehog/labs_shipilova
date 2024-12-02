class TechnologicalLine {
    constructor(minProductionRate, maxProductionRate, numberOfWorkers) {
        this.productionRate = this.getRandomProductionRate(minProductionRate, maxProductionRate);
        this.numberOfWorkers = numberOfWorkers; // количество человек на линии
    }

    // Метод для получения информации о линии
    getLineInfo() {
        return `Производительность линии: ${this.productionRate}, Количество человек на линии: ${this.numberOfWorkers}`;
    }

    // Метод для расчета общего выпуска за смену (в минутах)
    calculateShiftOutput(shiftDurationMinutes) {
        return this.productionRate * shiftDurationMinutes;
    }

    // Метод для генерации случайной производительности в заданном диапазоне
    getRandomProductionRate(min, max) {
        return Math.floor(Math.random() * (max - min + 1)) + min;
    }
}

class Workshop {
    constructor(lines) {
        this.lines = lines; // массив технологических линий
    }

    // Метод для расчета общего выпуска цеха за смену
    calculateTotalShiftOutput(shiftDurationMinutes) {
        let totalOutput = 0;
        this.lines.forEach(line => {
            totalOutput += line.calculateShiftOutput(shiftDurationMinutes);
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

        if (difference > 0) {
            console.log(`План выпуска перевыполнен на ${difference} шт.`);
        } else if (difference < 0) {
            console.log(`План выпуска недовыполнен на ${Math.abs(difference)} шт.`);
        } else {
            console.log('План выпуска выполнен точно.');
        }
    }
}

// Пример использования
const workersPerLine = 2;//количество людей на линии
const shiftDurationMinutes = 8 * 60; // 8 часов в минутах
const targetOutput = 2880;

const lines = [
    new TechnologicalLine(2, 3, workersPerLine),
    new TechnologicalLine(2, 3, workersPerLine),
    new TechnologicalLine(2, 3, workersPerLine),
    new TechnologicalLine(2, 3, workersPerLine)
];

const workshop = new Workshop(lines);

// Используем метод для вывода информации о выпуске
workshop.printTotalShiftOutput(shiftDurationMinutes);
// Используем метод для проверки выполнения плана
workshop.checkProductionPlan(targetOutput, shiftDurationMinutes);
