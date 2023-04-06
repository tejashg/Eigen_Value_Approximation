const express = require('express');
const bodyParser = require('body-parser');
const cors = require("cors");
const { spawn } = require('child_process');

const app = express();
app.use(cors());
app.use(bodyParser.json());

const output = (input, res) => {
  let method = input.pop();
  let executablePath = '';
  if (method[0] == 'power') {
    executablePath = '../computation/Power_Method.exe';
  }
  else {
    executablePath = '../computation/QR_Algorithm.exe';
  }

  // Arguments to pass to the executable file
  const args = ['arg1', 'arg2', 'arg3'];

  // Spawn the child process
  const childProcess = spawn(executablePath, args);

  // Send input to the child process
  const inputString = input.map(row => row.join(' ')).join('\n');
  childProcess.stdin.write(inputString);

  // End the input stream
  childProcess.stdin.end();

  // Receive output from the child process
  childProcess.stdout.on('data', (data) => {
    const outpt = data.toString('utf8')

    res.json({ message: 'Matrix received successfully', output: outpt });
  });

  // Handle errors
  childProcess.on('error', (error) => {
    console.error(`Error: ${error}`);
  });
}

app.post('/api/matrix', async (req, res) => {
  const { size, data, maxIterations, precision, algorithm } = req.body;

  const input = [[size], ...data, [precision], [maxIterations], [algorithm]]

  output(input, res)
});

const PORT = process.env.PORT;
app.listen(PORT, () => {
  console.log(`Server listening on port ${PORT}`);
});
