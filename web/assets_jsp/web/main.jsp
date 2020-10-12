<html>
<head>
    <meta charset="UTF-8">
    <script src="jquery-2.0.3.js"></script>
    <script>
        $(document).ready(function() {
            $.get(
                "MainController",
                function (data) {
                    tableString = "<table border='1'><tr><th>ID</th><th>Name</th><th>Description</th><th>Value</th></tr>"
                    for (var i in data) {
                        var id = data[i].id;
                        var name = data[i].name;
                        var description = data[i].description;
                        var value = data[i].value;
                        if (parseInt(value) > 10)
                            tableString += "<tr style='background-color: red'>";
                        else
                            tableString += "<tr>";
                        tableString += "<td>" + id + "</td>";
                        tableString += "<td>" + name + "</td>";
                        tableString += "<td>" + description + "</td>";
                        tableString += "<td>" + value + "</td>";
                        tableString += "</tr>";
                    }
                    tableString += "</table>";
                    $("#assetData").html(tableString);
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
            var namesString = "";
            var descriptionsString = "";
            var valuesString = "";
            for (var i = 0; i < names.length; ++i) {
                if (i > 0) {
                    namesString += ",";
                    descriptionsString += ",";
                    valuesString += ",";
                }
                namesString += names[i];
                valuesString += values[i];
                descriptionsString += descriptions[i];
            }
            $.post(
                "MainController",
                {
                    names: namesString,
                    descriptions: descriptionsString,
                    values: valuesString
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
