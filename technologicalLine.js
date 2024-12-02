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

class LaborPayment extends Workshop {
    constructor(lines, hourlyRate, bonusRate, extraBonusRate, costPerUnit) {
        super(lines);
        this.hourlyRate = hourlyRate; // почасовая оплата в рублях
        this.bonusRate = bonusRate; // бонус за выполнение плана
        this.extraBonusRate = extraBonusRate; // доплата за перевыполнение плана
        this.costPerUnit = costPerUnit; // себестоимость одной покрышки в рублях
    }

    // Метод для расчета оплаты труда за смену
    calculateLaborPayment(shiftDurationMinutes, targetOutput) {
        const totalOutput = this.calculateTotalShiftOutput();
        const hoursWorked = shiftDurationMinutes / 60;
        let paymentPerWorker = this.hourlyRate * hoursWorked;

        if (totalOutput >= targetOutput) {
            // Выполнение плана
            paymentPerWorker += paymentPerWorker * this.bonusRate;

            if (totalOutput > targetOutput) {
                // Перевыполнение плана
                const extraProduction = totalOutput - targetOutput;
                const extraPayment = extraProduction * this.costPerUnit * this.extraBonusRate;
                paymentPerWorker += extraPayment / this.lines.length / this.lines[0].numberOfWorkers;
            }
        }

        return paymentPerWorker;
    }

    // Метод для вывода информации об оплате труда
    printLaborPayment(shiftDurationMinutes, targetOutput) {
        const payment = this.calculateLaborPayment(shiftDurationMinutes, targetOutput);
        console.log(`Начисленная оплата труда за смену на одного рабочего: ${payment.toFixed(2)} руб.`);
    }

    // Новый метод для расчета общей зарплаты всех рабочих в цехе
    calculateTotalLaborPayment(shiftDurationMinutes, targetOutput) {
        const paymentPerWorker = this.calculateLaborPayment(shiftDurationMinutes, targetOutput);
        let totalWorkers = 0;

        this.lines.forEach(line => {
            totalWorkers += line.numberOfWorkers;
        });

        return paymentPerWorker * totalWorkers;
    }

    // Метод для вывода информации о зарплате всех рабочих
    printTotalLaborPayment(shiftDurationMinutes, targetOutput) {
        const totalPayment = this.calculateTotalLaborPayment(shiftDurationMinutes, targetOutput);
        console.log(`Общая начисленная оплата труда за смену для всех рабочих: ${totalPayment.toFixed(2)} руб.`);
    }
}

module.exports = {
    TechnologicalLine,
    Workshop,
    LaborPayment
};