var sxc = require('./build/Release/sxc');

var exports = {};

exports.validate = require("./Validate.js");
exports.sxc = sxc;

module.exports = exports;