const readline = require('readline');

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout
});

function showMenu() {
  console.log('\nВыберите опцию:');
  console.log('1. Показать время');
  console.log('2. Показать дату');
  console.log('3. Показать время и дату');
  console.log('4. Выход');
  rl.question('Введите номер опции: ', handleUserInput);
}

function handleUserInput(option) {
  const now = new Date();
  switch (option.trim()) {
    case '1':
      console.log(`Время: ${now.toLocaleTimeString()}`);
      break;
    case '2':
      console.log(`Дата: ${now.toLocaleDateString()}`);
      break;
    case '3':
      console.log(`Дата и время: ${now.toLocaleString()}`);
      break;
    case '4':
      console.log('Выход...');
      rl.close();
      return;
    default:
      console.log('Неверный ввод. Пожалуйста, выберите опцию от 1 до 4.');
  }
  showMenu();
}

showMenu();