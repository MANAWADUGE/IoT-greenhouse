<?php

$servername = "localhost";


$dbname = "green_house";
$username = "root";
$password = "";

$api_key_value = "tPmAT5Ab3j7F9";

$api_key= $Temperature = $Latitude = $Longitude = $accident = $Speed = "";

if ($_SERVER["REQUEST_METHOD"] == "GET") {
    $api_key = test_input($_GET["api_key"]);
    if($api_key == $api_key_value) {
        $Pressure = test_input($_GET["Pressure"]);
		$Water_Temperature = test_input($_GET["Water_Temperature"]);
		$Humidity = test_input($_GET["Humidity"]);
		$Temperature = test_input($_GET["Temperature"]);
		$Soil = test_input($_GET["Soil"]);
        $Pump_status = test_input($_GET["Pump_status"]);
        $Mist_status = test_input($_GET["Mist_status"]);
        $Door_status = test_input($_GET["Door_status"]);
        
        // Create connection
        $conn = new mysqli($servername, $username, $password, $dbname);
        // Check connection
        if ($conn->connect_error) {
            die("Connection failed: " . $conn->connect_error);
        } 
        
        $sql = "INSERT INTO sensordatahistory (Pressure,Water_Temperature,Humidity,Temperature,Soil,Pump_status,Mist_status,Door_status)
        VALUES ('" . $Pressure . "','" . $Water_Temperature . "','" . $Humidity . "','" . $Temperature . "','" . $Soil . "','" . $Pump_status . "','" . $Mist_status . "','" . $Door_status . "')";
        
        if ($conn->query($sql) === TRUE) {
            echo "New record created successfully";
        } 
        else {
            echo "Error: " . $sql . "<br>" . $conn->error;
        }
    
        $conn->close();
    }
    else {
        echo "Wrong API Key provided.";
    }

}
else {
    echo "No data posted with HTTP POST.";
}

function test_input($data) {
    $data = trim($data);
    $data = stripslashes($data);
    $data = htmlspecialchars($data);
    return $data;
}