var pls = require('./build/Release/pls');

var exports = {};

exports.validate = require("./Validate.js");
exports.pls = pls;

module.exports = exports;