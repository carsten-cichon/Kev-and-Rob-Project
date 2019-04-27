const mongoDB = require("mongodb").MongoClient;

let database, 
    dbName = "keystokesDB";

const keyLoggerRepo = {
    connectDatabase = () => {
        MongoClient.connect('mongodb://localhost:27017/animals', (err, client) => {
            if (err) {
                throw new Error(err);
            } else {
                database = client.db(dbName);
                client.close();
            }
        });
    }, saveStrokes = strokes => {
        const collection = db.collection("keystokes")
    }
};