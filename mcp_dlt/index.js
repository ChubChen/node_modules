var dlt = require('./build/Release/dlt');

var exports = {};

exports.validate = require("./Validate.js");
exports.dlt = dlt;

module.exports = exports;