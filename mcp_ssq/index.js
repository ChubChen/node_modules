var ssq = require('./build/Release/ssq');

var exports = {};

exports.validate = require("./Validate.js");
exports.ssq = ssq;

module.exports = exports;