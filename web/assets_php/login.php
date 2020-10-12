<?php
	$connection = mysqli_connect("localhost", "root", "", "test_php");
	if (!$connection) {
		die('Could not connect: ');
	}
	
	$user = $_POST["username"];
	$pw = $_POST["password"];
	$result = mysqli_query($connection, "select * from users where username = '" . $user . "' and password = '" . $pw . "'");
	$row = mysqli_fetch_array($result);
	
	if ($row) {
		session_start();
		$_SESSION['userid'] = $row['id'];
		$_SESSION['username'] = $row['username'];
		header("Location: main.php");
	}
	mysqli_close($connection);
?>

<html>
	<head>
		<meta charset="UTF-8">
	</head>
</html>