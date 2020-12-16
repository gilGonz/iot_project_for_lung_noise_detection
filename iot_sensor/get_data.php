<?php
	//setting header to json
	header('Content-Type: application/json');

	//database
	define('DB_HOST', 'localhost');
	define('DB_USERNAME', 'iot');
	define('DB_PASSWORD', 'iotpass');
	define('DB_NAME', 'arduino_db');

	//get connection
	$iot_connect = new mysqli(DB_HOST, DB_USERNAME, DB_PASSWORD, DB_NAME);

	if($iot_connect->connect_error){
	  die("Connection failed: " . $iot_connect->connect_error);
	}

	//query to get data from the table
	$query = sprintf("SELECT timestamp, lung_sound FROM sound_sensor");

	//execute query
	$result = $iot_connect->query($query);

	//loop through the returned data
	$data = array();
	foreach ($result as $row) {
	  $data[] = $row;
	}

	//free memory associated with result
	$result->close();

	//close connection
	$iot_connect->close();

	//now print the data
	//print json_encode($data);
	
	$fp = fopen('./iot_sensor/value_data.json', 'w');
	if ( $fp ) {
		fwrite($fp, json_encode($data));
		fclose($fp);
	}
?>
