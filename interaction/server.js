const express = require('express');
const socket = require('socket.io');
const oscTransmitter = require('./oscTransmitter.js')

let app = express();
let server = app.listen(55123) 

app.use(express.static('public'));

let io = socket(server);

io.sockets.on('connection', newConnection);

function newConnection(socket) {
    console.log("new connection: " + socket.id);

    socket.on('centroidAndPalmMiddleFinger', dataReceived)

    function dataReceived(data) {
        //console.log(data);
        oscTransmitter.sendData(data);
    }
}



