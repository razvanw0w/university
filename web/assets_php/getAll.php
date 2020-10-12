<?php
	$connection = mysqli_connect("localhost", "root", "", "test_php");
	if (!$connection) {
		die('Could not connect: ');
	}
	
	session_start();
	$id = $_SESSION['userid'];
	$result = mysqli_query($connection, "select * from assets where userid = " . $id);
	
	if ($result) {
		echo "<table border='1'><tr><th>ID</th><th>Name</th><th>Description</th><th>Value</th></tr>";
		while ($row = mysqli_fetch_array($result)) {
			$assetid = $row['id'];
			$name = $row['name'];
			$description = $row['description'];
			$value = $row['value'];
			if ($value > 10) {
				echo "<tr style='background-color: red;'>";
			}
			else {
				echo "<tr>";
			}
			echo "<td>" . $assetid . "</td>";
			echo "<td>" . $name . "</td>";
			echo "<td>" . $description . "</td>";
			echo "<td>" . $value . "</td>";
			echo "</tr>";
		}
		echo "</table>";
	}
	mysqli_close($connection);
?>