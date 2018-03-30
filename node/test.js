// var debounce = require('debounce');
var serialport = require('serialport');
var readline = require('readline');
var request = require('request');
var gamenumber = 2053;
var idPlayer = "";
var http = require("http");
const fs = require('fs');


var express = require('express');
var xbox = require('xbox-controller-node');
var path = require("path");





var buttonPressed;

const hostname = '172.31.11.90';
const port = 3000;


//var playerId = "daae8fcc-146b-4618-a917-c070b6f6582d";
//var gameId = "58";

var playerId;
var gameId;

var name = "PietjePek";
var ammo;
var health;





var portname = process.argv[2];

var myPort = new serialport(portname, {
	bauttRate: 9600,
	//parser:serialport.parsers.readline("\r\n")
})

let playerID;

var rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout
});


myPort.on('open', onOpen);
myPort.on('data', onrecieveData);
myPort.on('error', showError);

rl.on('line', sendDataBluetooth);

function onOpen()
{
	console.log("Connection to Droid!");
}



function onrecieveData(data)
{
	console.log("Received data: " + data);
	if(data == 'h')
	{
    hit();	
  }
}

function sendDataBluetooth(data)
{
	console.log("Sending to Droid: " + data);
	myPort.write(data + "\n");
}

function sendDataServer(data, method)
{
	var url = iphost + data;
	// Set the headers
	var headers = {
		'User-Agent':       'Super Agent/0.0.1',
		'Content-Type':     'application/x-www-form-urlencoded'
	}

	// Configure the request
	var options = {
		url: url,
		method: method,
		headers: headers,
	}

	console.log(url);
	// Start the request
	/*request(options, function (error, response, body) {
		if (!error && response.statusCode == 200) {
			// Print out the response body
			var obj = JSON.parse(body);

			if(obj.action == 'identifyPlayer')
			{
				playerID = obj.result.id;
			}
		}
	});*/
}

function showError(error)
{
   console.log('Serial port error: ' + error);
}



xbox.on('start', function () {
  console.log('Start');
  if (buttonPressed !== "start" )
	logIn(769);
	buttonPressed = "start";

});

xbox.on('back', function () {
  console.log('back');
  if (buttonPressed !== "back" )
      getInfo();
	buttonPressed = "back";
});

xbox.on('rb', function () {
  console.log('rb');
  if (buttonPressed !== "rb" )
      fire();
	buttonPressed = "rb";
	myPort.write("f");
});
 
 
 xbox.on('lb', function () {
  console.log('lb');
  if (buttonPressed !== "lb" )
      getAmmo();
	buttonPressed = "lb";

});

 



 
//Manage sticks events 
 
xbox.on('leftstickLeft', function () {
  console.log('Moving [LEFTSTICK] LEFT');
  if (buttonPressed !== "left" )
  myPort.write("l");
  buttonPressed = "left";
  
});
 
xbox.on('leftstickLeft:release', function () {
    console.log('Released [LEFTSTICK] LEFT');
    if (buttonPressed !== "leftRelease" )
    myPort.write("s");
	buttonPressed = "leftRelease";
  });






xbox.on('leftstickRight', function () {
  console.log('Moving [LEFTSTICK] RIGHT');

  if (buttonPressed !== "right" )
  myPort.write("r");
  buttonPressed = "right";

});

xbox.on('leftstickRight:release', function () {
    console.log('Released [LEFTSTICK] LEFT');
    if (buttonPressed !== "rightRelease" )
    myPort.write("s");
	buttonPressed = "rightRelease";
    
  });
 



 
xbox.on('leftstickDown', function () {
  console.log('Moving [LEFTSTICK] DOWN');
  if (buttonPressed !== "down" )
  myPort.write("d");
  buttonPressed = "down";

});

xbox.on('leftstickDown:release', function () {
    console.log('Released [LEFTSTICK] LEFT');
    if (buttonPressed !== "downRelease" )
    myPort.write("s");
	buttonPressed = "downRelease";
    
  });
 






xbox.on('leftstickUp', function () {
  console.log('Moving [LEFTSTICK] UP');
        if (buttonPressed !== "up" )
        myPort.write("u");
        buttonPressed = "up";

});

xbox.on('leftstickUp:release', function () {
    console.log('Released [LEFTSTICK] LEFT');
    if (buttonPressed !== "upRelease" )
    myPort.write("s");
	buttonPressed = "upRelease";
  });
 





function logIn(newGameId) {

    var options = {
        hostname: hostname,
        port: port,
        path: '/game/' + newGameId + '/player',
        method: 'POST',
        headers: {
            'Content-Type': 'application/x-www-form-urlencoded',
        }
    };
    var req = http.request(options, function(res) {
        res.on('data', function(body) {

            name = JSON.parse(body).result.name;
            playerIdNew = JSON.parse(body).result.id;
            ammo = JSON.parse(body).result.ammo;
            health = JSON.parse(body).result.health;

            playerId = playerIdNew;
            gameId = newGameId;

            console.log('POST login:');
            console.log('PlayerId: ' + playerId);
            console.log('GameId: ' + gameId);
            console.log('name: ' + name);
            console.log('ammo: ' + ammo);
            console.log('health: ' + health);

        });

    });
    req.write("name=" + name);
    req.on('error', function(e) {
        console.log('problem with request: ' + e.message);
    });
    req.end();
}




function getInfo() {

    var options = {
        hostname: hostname,
        port: port,
        path: '/game/' + gameId,
        method: 'GET',
        headers: {
            'Content-Type': 'application/json',
        }
    };
    var req = http.request(options, function(res) {
        res.on('data', function(body) {
            console.log('GET info game:');
            console.log('Body: ' + body);

            console.log('PlayerId: ' + playerId);
            console.log('GameId: ' + gameId);
            console.log('ammo: ' + ammo);
            console.log('health: ' + health);
        });
    });
    req.on('error', function(e) {
        console.log('problem with request: ' + e.message);
    });
    req.end();
}





function getAmmo() {

    var options = {
        hostname: hostname,
        port: port,
        path: '/game/' + gameId + '/player/' + playerId + '/ammo',
        method: 'GET',
        headers: {
            'Content-Type': 'application/json',
        }
    };
    var req = http.request(options, function(res) {
        res.on('data', function(body) {
            console.log('GET ammo:');
            console.log('Body: ' + body);
        });
    });
    req.on('error', function(e) {
        console.log('problem with request: ' + e.message);
    });
    req.end();

}


function fire() {

    var options = {
        hostname: hostname,
        port: port,
        path: '/game/' + gameId + '/player/' + playerId + '/ammo',
        method: 'POST',
        headers: {
            'Content-Type': 'application/json',
        }
    };
    var req = http.request(options, function(res) {
        res.on('data', function(body) {
            console.log('POST ammo // FIRE:');
            console.log('Body: ' + body);
        });
    });
    req.on('error', function(e) {
        console.log('problem with request: ' + e.message);
    });
    req.end();

}


function hit() {

    var options = {
        hostname: hostname,
        port: port,
        path: '/game/' + gameId + '/player/' + playerId + '/hit',
        method: 'POST',
        headers: {
            'Content-Type': 'application/json',
        }
    };
    var req = http.request(options, function(res) {
        res.on('data', function(body) {
            console.log('POST HIT:');
            console.log('Body: ' + body);
        });
    });
    req.on('error', function(e) {
        hit();
        console.log('problem with request: ' + e.message);
    });
    req.end();

}



// log in with gameId
//logIn(76);

//getInfo();
//getAmmo();
//fire();
//hit();



/* 

var server = app.listen(8081, function() {

    var host = server.address().address
    var port = server.address().port

});
*/
