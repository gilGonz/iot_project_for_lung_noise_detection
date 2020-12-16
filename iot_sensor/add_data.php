<?php
	$temp_data = $_GET['data'];
	$sound_data = (int)$temp_data;
	
	define('DB_HOST', '127.0.0.1');
	define('DB_USERNAME', 'iot');
	define('DB_PASSWORD', 'iotpass');
	define('DB_NAME', 'arduino_db');

	//get connection
	$iot_connect = new mysqli(DB_HOST, DB_USERNAME, DB_PASSWORD, DB_NAME);

	if($iot_connect->connect_error){
	  echo "die";
	  die("Connection failed: " . $iot_connect->connect_error);
	}
	
	$timestamp = gmdate("l jS \of F Y h:i:s A");
	
	$stmt = $iot_connect->prepare("INSERT INTO sound_sensor VALUES (?, ?)");
	$stmt->bind_param("si", $timestamp, $sound_data);

	$stmt->execute();
	$stmt->close();
	$iot_connect->close();

?> 
