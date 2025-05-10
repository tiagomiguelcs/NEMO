const express = require('express'); // Importing express
const app = express(); // Creating an express app
const python_backend = "../python/send.py";
nemo_bt_address = "";
// Create a route that sends a response when visiting the homepage
app.get('/', (req, res) => {
	res.send('<h1>Hello, Express.js Server!</h1>');
});

app.get('/forward', (req, res) => {
	const spawn = require('child_process').spawn;
    const args = ['f', nemo_bt_address]
	const cn = spawn('python3', [python_backend, ...args]);

	cn.stdout.on('data', (data) => {
		console.log(`${data}`);
		res.send({message: `${data}`});
	});

	cn.stderr.on('data', (data) => {
		console.log(`${data}`);
		res.send({message: `${data}`});
	});

	cn.on('close', (code) => {
		console.log(`Code sent to the device, exited with code ${code}`);
	});
});

app.get('/backward', (req, res) => {
	const spawn = require('child_process').spawn;
    const args = ['b', nemo_bt_address]
	const cn = spawn('python3', [python_backend, ...args]);

	cn.stdout.on('data', (data) => {
		console.log(`${data}`);
		res.send({message: `${data}`});
	});

	cn.stderr.on('data', (data) => {
		console.log(`${data}`);
		res.send({message: `${data}`});
	});

	cn.on('close', (code) => {
		console.log(`Code sent to the device, exited with code ${code}`);
	});
});

// Set up the server to listen on port 4000
const port = 4000;

console.log("Connecting to NEMO's bluetooth...");
const spawn = require('child_process').spawn;
const cn = spawn('python3', [python_backend, 'bt']);
cn.stdout.on('data', (data) => {
    nemo_bt_address = `${data}`;
    nemo_bt_address = nemo_bt_address.replace('\n', '');
    if (nemo_bt_address.length === 0){
        console.log("Unable to find BT address");
        return;
    }
    console.log(nemo_bt_address);
    app.listen(port, () => {
        console.log(`BT address retrieved, server is running on port ${port}`);
    });
});
