var esf = require('./build/Release/esf');

var exports = {};

exports.validate = require("./Validate.js");
exports.esf = esf;

module.exports = exports;