<?php
//echo getenv('HOST').":".getenv('PORT');
$servername = getenv('HOST').":".getenv('PORT');
$username = "root";
$password = "donttouchme";
$dbname = "testdb";
$conn = mysqli_connect($servername, $username, $password, $dbname);
?>
