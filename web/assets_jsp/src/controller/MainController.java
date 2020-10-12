package controller;

import adapter.DatabaseAdapter;
import model.Asset;
import org.json.JSONArray;
import org.json.JSONObject;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import javax.xml.crypto.Data;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.List;

public class MainController extends HttpServlet {
    private JSONArray retrieveAllAssets(int userid) {
        DatabaseAdapter databaseAdapter = new DatabaseAdapter();
        List<Asset> assets = databaseAdapter.getAll(userid);
        JSONArray jsonArray = new JSONArray();
        assets.stream()
                .forEach(asset -> {
                    JSONObject jsonObject = new JSONObject();
                    jsonObject.put( "id", asset.getId());
                    jsonObject.put( "name", asset.getName());
                    jsonObject.put( "description", asset.getDescription());
                    jsonObject.put( "value", asset.getValue());
                    jsonArray.put(jsonObject);
                });
        return jsonArray;
    }

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = req.getSession();
        Integer userid = Integer.parseInt(session.getAttribute("userid").toString());
        JSONArray array = retrieveAllAssets(userid);
        response.setContentType("application/json");
        PrintWriter out = new PrintWriter(response.getOutputStream());
        out.println(array.toString());
        out.flush();
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        HttpSession session = req.getSession();
        Integer userid = Integer.parseInt(session.getAttribute("userid").toString());
        String[] names = req.getParameter("names").split(",");
        String[] descriptions = req.getParameter("descriptions").split(",");
        String[] values = req.getParameter("values").split(",");
        DatabaseAdapter databaseAdapter = new DatabaseAdapter();
        databaseAdapter.insertAssets(userid, Arrays.asList(names), Arrays.asList(descriptions), Arrays.asList(values));
    }
}
