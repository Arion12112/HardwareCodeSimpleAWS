var awsIot = require('aws-iot-device-sdk');
var mysql = require('mysql');
var Database_URL = 'localhost';
var Topic = 'simpleaws'; 
var device = awsIot.device({
 keyPath: 'cert/private.pem.key',
 certPath: 'cert/cer.pem.crt',
 caPath: 'cert/root.pem',
 host: 'ab7s064o15lu-ats.iot.us-east-1.amazonaws.com',
 clientId: 'server',
 });

 device.on('connect', function() {
 console.log('connected');
 device.subscribe(Topic,mqtt_subscribe);
 });
 device.on('message',  mqtt_messsageReceived);


function mqtt_subscribe(err, granted) {
    console.log("Subscribed to " + Topic);
    if (err) {console.log(err);}
};
 function mqtt_messsageReceived(topic, message, packet) {
	var message_str = message.toString(); //convert byte array to string
	message_str = message_str.replace(/\n$/, ''); //remove new line
	//payload syntax: clientID,topic,message
	if (countInstances(message_str) != 7) {
		console.log("Invalid payload");
		} else {	
		insert_message(topic, message_str, packet);
		//console.log(message_arr);
	}
};

var connection = mysql.createConnection({
	host: Database_URL,
	port : 3306,
	user: "root",
	password: "",
	database: "simple_aws"
});

connection.connect(function(err) {
	if (err) throw err;
	console.log("Database Connected!");
});

//insert a row into the tbl_messages table
function insert_message(topic, message_str, packet) {
	var message_arr = extract_string(message_str); //split a string into an array
	var suhu = Number(message_arr[0]);
	var tekanan = Number(message_arr[1]);
	var ketinggian = Number(message_arr[2]);
	var cahaya = Number(message_arr[3]);
	var kondisi = message_arr[4];
	var udara = message_arr[5];
	var kelembaban = Number(message_arr[6]);
	var tanggal = new Date(message_arr[7]);


	var sql = "INSERT INTO ?? (??,??) VALUES (?,?)";
	var params = ['suhu','nilai','tanggal', suhu, tanggal];
	sql = mysql.format(sql, params);
	
	var sql2 = "INSERT INTO ?? (??,??) VALUES (?,?)";
	var params2 = ['tekanan_udara','nilai','tanggal', tekanan, tanggal];
	sql2 = mysql.format(sql2, params2);
	
	var sql3 = "INSERT INTO ?? (??,??) VALUES (?,?)";
	var params3 = ['ketinggian','nilai','tanggal', ketinggian, tanggal];
	sql3 = mysql.format(sql3, params3);
	
	var sql4 = "INSERT INTO ?? (??,??) VALUES (?,?)";
	var params4 = ['intensitas_cahaya','nilai','tanggal', cahaya, tanggal];
	sql4 = mysql.format(sql4, params4);
	
	var sql5 = "INSERT INTO ?? (??,??) VALUES (?,?)";
	var params5 = ['kondisi_cuaca','nilai','tanggal', kondisi, tanggal];
	sql5 = mysql.format(sql5, params5);
	
	var sql6 = "INSERT INTO ?? (??,??) VALUES (?,?)";
	var params6 = ['kualitas_udara','nilai','tanggal', udara, tanggal];
	sql6 = mysql.format(sql6, params6);
	
	var sql7 = "INSERT INTO ?? (??,??) VALUES (?,?)";
	var params7 = ['kelembaban','nilai','tanggal', kelembaban, tanggal];
	sql7 = mysql.format(sql7, params7);
	
	connection.query(sql, function (error, results) {
		if (error) throw error;
		console.log("Success");
	}); 
		connection.query(sql2, function (error, results) {
		if (error) throw error;
	}); 
		connection.query(sql3, function (error, results) {
		if (error) throw error;
	}); 
		connection.query(sql4, function (error, results) {
		if (error) throw error;
	}); 
		connection.query(sql5, function (error, results) {
		if (error) throw error;
	}); 
		connection.query(sql6, function (error, results) {
		if (error) throw error;
	}); 
		connection.query(sql7, function (error, results) {
		if (error) throw error;
	});
};	

//split a string into an array of substrings
function extract_string(message_str) {
	var message_arr = message_str.split(","); //convert to array	
	return message_arr;
};	

//count number of delimiters in a string
var delimiter = ",";
function countInstances(message_str) {
	var substrings = message_str.split(delimiter);
	return substrings.length - 1;
};