package adapter;

import model.Asset;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class DatabaseAdapter {
    private Statement statement;

    public DatabaseAdapter() {
        connectToDatabase();
    }

    private void connectToDatabase() {
        try {
            Class.forName("com.mysql.jdbc.Driver");
            Connection connection = DriverManager.getConnection("jdbc:mysql://localhost/test_php", "root", "");
            statement = connection.createStatement();
        }
        catch (Exception e) {
            System.out.println("connect error " + e.getMessage());
            e.printStackTrace();
        }
    }

    public int authenticate(String username, String password) {
        ResultSet resultSet;
        int id = -1;
        try {
            resultSet = statement.executeQuery("select * from users where username = '" + username + "' and password = '" + password + "'");
            if (resultSet.next()) {
                id = resultSet.getInt("id");
            }
            resultSet.close();
        }
        catch (SQLException e) {
            e.printStackTrace();
        }

        return id;
    }

    public List<Asset> getAll(int uid) {
        List<Asset> assets = new ArrayList<>();
        ResultSet resultSet;
        try {
            resultSet = statement.executeQuery("select * from assets where userid = " + uid);

            while (resultSet.next()) {
                assets.add(new Asset(
                        resultSet.getInt("id"),
                        resultSet.getInt("userid"),
                        resultSet.getString("name"),
                        resultSet.getString("description"),
                        resultSet.getInt("value")
                ));
            }
            resultSet.close();
        } catch (SQLException throwables) {
            throwables.printStackTrace();
        }
        return assets;
    }

    public void insertAssets(int uid, List<String> names, List<String> descriptions, List<String> values) {
        int n = names.size();
        for (int i = 0; i < n; ++i) {
            try {
                statement.executeUpdate("insert into assets(userid, name, description, value) values(" + uid + ",'" + names.get(i) + "','" + descriptions.get(i) + "','" + values.get(i) + "')");
            } catch (SQLException throwables) {
                throwables.printStackTrace();
            }
        }
    }
}
