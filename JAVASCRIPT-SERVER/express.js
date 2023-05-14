const express = require('express');
const app = express();

import('random').then((module) => {
  const random = module.default;

  
const IP_ADDRESS = '192.168.0.100';

let traffic_response = '';

app.get('/CHECK/:param', (req, res) => {
  console.log('SUCCESS');
  res.send('SUCCESS');
});

app.get('/ACCIDENT/:param', (req, res) => {
  if (req.params.param === 'XXXXX') {
    const response = random.int(0, 1) === 0 ? 'A1' : 'A2';
    console.log(response);
    res.send(response);
  } else {
    res.send('FAILED');
  }
});

app.get('/HOSPITAL/:param', (req, res) => {
  if (req.params.param === 'XXXXX') {
    const response = random.int(0, 1) === 0 ? 'H1' : 'H2';
    if (response === 'H1') {
      traffic_response = random.int(0, 1) === 0 ? 'V11' : 'V12';
    } else {
      traffic_response = random.int(0, 1) === 0 ? 'V21' : 'V22';
    }
    console.log(response);
    res.send(response);
  } else {
    res.send('FAILED');
  }
});

app.get('/LIGHT/:param', (req, res) => {
  if (req.params.param === 'XXXXX') {
    const response = random.int(0, 1) === 0 ? 'RED' : 'GREEN';
    console.log(response);
    res.send(response);
  } else {
    res.send('FAILED');
  }
});

app.get('/TRAFFIC/:param', (req, res) => {
  if (req.params.param === 'XXXXX') {
    const response = traffic_response;
    console.log(response);
    res.send(response);
  } else {
    res.send('FAILED');
  }
});

app.get('/GREEN/:param', (req, res) => {
  if (req.params.param === 'XXXXX') {
    const response = 'CHANGED';
    console.log(response);
    res.send(response);
  } else {
    res.send('FAILED');
  }
});

app.listen(5000, '0.0.0.0', () => {
  console.log('Server running on port 5000');
});

}).catch((error) => {
 console.error(error);
});
