<?php

require_once('db_connection.php');

 //開啟緩衝區
if(!isset($_COOKIE["USERSESSID"])){
    setcookie('USERSESSID', md5(uniqid(rand(), true)));
    header("Location: /");
}

echo "<!-- Only xss, no command injection or sql injection la....... -->";
?>

<form method="POST">
  <label for="fname">寫下你想留的話:</label><br>
  <input type="text" id="content" name="content">
  <input type="submit" value="提交">
</form>


<?php

$user = $_COOKIE['USERSESSID'];
// check the admin's cookie
if($user === "GuvfvfnqzvapbbxvrGuvfvfnqzvapbbxvr") {
    echo "您是管理員，歡迎回來<br>";
    echo "NISRA{You_CAN_use_thhhhhhhhhhhhhhhhhhhe_xssssssss_la}<br>";
    echo "-------------------------------------------------<br>";
}
else {
    echo "你是一般的使用者，只有留言功能<br>";
}


if(isset($_POST['content']) && !empty($_POST['content']))
{
    $user = $_COOKIE['USERSESSID'];
    $message = $_POST['content'];
    // echo $user." ".$message."<br>";
    
    $stmt = $conn->prepare('insert into comment(user, content) values (?, ?)');
    $stmt->bind_param('ss',$user,$message);
    $check = $stmt->execute();
    if ( $check===false ) {
        die('execute() failed: ' . htmlspecialchars($stmt->error));
    }
}

$user = $_COOKIE['USERSESSID'];

$stmt = $conn->prepare('select id, content, isread from comment where user=?');
$stmt->bind_param('s',$user);
$stmt->execute();
$stmt->bind_result($id,$content,$isread);


//show all of comments
while($stmt->fetch())
{
    echo "userid: ".$user."<br>";
    echo "content: ".htmlentities($content)."<br>";
    echo "admin_read: ";
    if($isread === 1)
        echo "True<br>";
    else
        echo "False<br>";
    echo "-------------------------------------------------<br>";
}

$stmt->close();
$conn->close();

?>