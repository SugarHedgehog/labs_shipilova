const { ChartJSNodeCanvas } = require('chartjs-node-canvas');

const width = 800; // Ширина изображения
const height = 600; // Высота изображения
const chartJSNodeCanvas = new ChartJSNodeCanvas({ width, height });

const configuration = {
  type: 'line',
  data: {
    labels: Array.from({ length: 100 }, (_, i) => (i / 10).toFixed(1)),
    datasets: [{
      label: 'y = cos(x)',
      data: Array.from({ length: 100 }, (_, i) => Math.cos(i / 10)),
      borderColor: 'rgba(75, 192, 192, 1)',
      borderWidth: 1
    }]
  },
  options: {
    scales: {
      x: { title: { display: true, text: 'x' } },
      y: { title: { display: true, text: 'y' } }
    }
  }
};

(async () => {
  const image = await chartJSNodeCanvas.renderToBuffer(configuration);
  require('fs').writeFileSync('cosx.png', image);
  console.log('График сохранен как cosx.png');
})();