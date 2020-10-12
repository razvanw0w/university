<?php
	session_start();
	if (!isset($_SESSION['userid'])) {
		header("Location: login.html");
	}
?>

<html>
	<head>
		<meta charset="UTF-8">
		<script src="jquery-2.0.3.js"></script>
		<script>
			$(document).ready(function() {
				$.get(
					"getAll.php",
					function (data) {
						$("#assetData").html(data);
					}
				);
				$("#addList").click(function() {
					addAssetToList();
					updateHistory();
				});
				$("#sendList").click(function() {
					submitAdd();
				});
			});
			
			names = [];
			descriptions = [];
			values = [];
			
			function clearInputs() {
				$("#name").val("");
				$("#description").val("");
				$("#value").val("");
			}
			function updateHistory() {
				tableString = "<table border='1'><tr><th>Name to add</th><th>Description to add</th><th>Value to add</th></tr>"
				for (var i = 0; i < names.length; ++i) {
					var name = names[i];
					var description = descriptions[i];
					var value = values[i];
					tableString += "<tr>";
					tableString += "<td>" + name + "</td>";
					tableString += "<td>" + description + "</td>";
					tableString += "<td>" + value + "</td>";
					tableString += "</tr>";
				}
				tableString += "</table>";
				$("#history").html(tableString);
			}
			function clearHistory() {
				$("#history").html("");
			}
			function addAssetToList() {
				var name = $("#name").val();
				var description = $("#description").val();
				var value = $("#value").val();
				console.log(name, description, value);
				clearInputs();
				names.push(name);
				descriptions.push(description);
				values.push(value);
			}
			function submitAdd() {
				$.post(
					"add.php",
					{
						names: names,
						descriptions: descriptions,
						values: values
					},
					function (data) {
						console.log("success submit");
					}
				);
			}
		</script>
	</head>
	<body>
		<section id="assetData">
		</section>
		<br>
		<input placeholder="name" id="name"/>
		<br>
		<input placeholder="description" id="description"/>
		<br>
		<input placeholder="value" id="value"/>
		<br>
		<button id="addList">Add to list</button>
		<br>
		<button id="sendList">Submit all added assets</button>
		<br>
		<br>
		History <br>
		<section id="history">
			
		</section>
	</body>
</html>