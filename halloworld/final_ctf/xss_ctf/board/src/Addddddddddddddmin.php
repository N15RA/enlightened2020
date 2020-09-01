<?php
setcookie('USERSESSID', "GuvfvfnqzvapbbxvrGuvfvfnqzvapbbxvr");
require_once('db_connection.php');

$stmt = $conn->prepare('select id, content, user from comment where `isread`=0 limit 1');
$check = $stmt->execute();
if ( $check===false ) {
    die('execute() failed: ' . htmlspecialchars($stmt->error));
}
else {
    $stmt->bind_result($id,$content,$user);
    $stmt->fetch();
}
$stmt->close();

$tmp = $id;
echo $id.": ".$content;

$stmt2 = $conn->prepare('UPDATE `comment` SET `isread` = 1  WHERE `id` = ?');
$stmt2->bind_param('i', $tmp);
$stmt2->execute();
$stmt2->close(); 
