using assets_asp.Communcation_Layer;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace assets_asp.Views
{
    public class LoginController : Controller
    {
        // GET: Login
        public ActionResult Index()
        {
            return View("Login");
        }

        public ActionResult Login()
        {
            string user = Request.Params["username"];
            string password = Request.Params["password"];
            DataAccessLayer dal = new DataAccessLayer();
            int id = dal.login(user, password);
            Session["userid"] = id;
            if (id > 0)
                return Redirect("/Main");
            return Redirect("/Login");
        }
    }
}