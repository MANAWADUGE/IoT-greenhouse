<!DOCTYPE html>
<html><body>
<?php

$servername = "localhost";

$dbname = "green_house";
$username = "root";
$password = "";


$conn = new mysqli($servername, $username, $password, $dbname);

if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 

$sql = "SELECT * FROM sensordatahistory ORDER BY id DESC";

echo '<table cellspacing="5" cellpadding="5">
      <tr> 
        <td>Date Time</td> 
        <td>Pressure</td> 
        <td>Water_Temperature</td> 
        <td>Humidity</td> 
        <td>Temperature</td> 
        <td>Soil</td> 
        <td>Pump_status</td> 
        <td>Mist_status</td> 
        <td>Door_status</td> 
      </tr>';
 
if ($result = $conn->query($sql)) {
    while ($row = $result->fetch_assoc()) {
        $row_id = $row["reading_time"];
        $row_id1 = $row["Pressure"];
        $row_id2 = $row["Water_Temperature"];
        $row_id3 = $row["Humidity"];
        $row_id4 = $row["Temperature"];
        $row_id5 = $row["Soil"];
        $row_id6 = $row["Pump_status"];
        $row_id7 = $row["Mist_status"];
        $row_id8 = $row["Door_status"];
     
        echo '<tr> 
                <td>' . $row_id . '</td> 
                <td>' . $row_id1 . '</td> 
                <td>' . $row_id2 . '</td> 
                <td>' . $row_id3 . '</td> 
                <td>' . $row_id4 . '</td> 
                <td>' . $row_id5 . '</td> 
                <td>' . $row_id6 . '</td> 
                <td>' . $row_id7 . '</td> 
                <td>' . $row_id8 . '</td> 
              </tr>';
    }
    $result->free();
}

$conn->close();
?> 
</table>
</body>
</html>