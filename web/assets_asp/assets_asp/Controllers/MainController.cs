using assets_asp.Communcation_Layer;
using assets_asp.Models;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace assets_asp.Controllers {
    public class MainController : Controller {
        // GET: Main
        public ActionResult Index() {
            return View("Main");
        }

        public ActionResult GetAll() {
            DataAccessLayer dal = new DataAccessLayer();
            int id = Int32.Parse(Session["userid"].ToString());
            List<Asset> assets = dal.getAll(id);
            string result = "<table border='1'><tr><th>ID</th><th>Name</th><th>Description</th><th>Value</th></tr>";
            foreach (Asset asset in assets) {
                if (asset.Value > 10) {
                    result += "<tr style='background-color: red;'>";
                }
                else {
                    result += "<tr>";
                }
                result += "<td>" + asset.Id + "</td>";
                result += "<td>" + asset.Name + "</td>";
                result += "<td>" + asset.Description + "</td>";
                result += "<td>" + asset.Value + "</td>";
            }
            result += "</table>";
            return Json(result, JsonRequestBehavior.AllowGet);
        }

        public ActionResult Add() {
            DataAccessLayer dal = new DataAccessLayer();
            int id = Int32.Parse(Session["userid"].ToString());
            String[] names = Request.Params["names"].Split(',');
            String[] descriptions = Request.Params["descriptions"].Split(',');
            String[] values = Request.Params["values"].Split(',');
            dal.add(id, names, descriptions, values);
            return Json(true);
        }
    }
}