var jc = require('./build/Release/jc');

var exports = {};

exports.validate = require("./Validate.js");
exports.jc = jc;

module.exports = exports;