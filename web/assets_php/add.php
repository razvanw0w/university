<?php
	$connection = mysqli_connect("localhost", "root", "", "test_php");
	if (!$connection) {
		die('Could not connect: ');
	}
	
	session_start();
	$id = $_SESSION['userid'];
	$names = $_POST['names'];
	$descriptions = $_POST['descriptions'];
	$values = $_POST['values'];
	
	$n = sizeof($names);
	for ($i = 0; $i < $n; ++$i) {
		$name = $names[$i];
		$description = $descriptions[$i];
		$value = $values[$i];
		$query = "insert into assets(userid, name, description, value)"
			. "values(" . $id . ", '"
			. $name . "', '"
			. $description . "', "
			. $value . ")";
		mysqli_query($connection, $query);
	}
	mysqli_close($connection);
?>