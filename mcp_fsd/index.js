var fsd = require('./build/Release/fsd');

var exports = {};

exports.validate = require("./Validate.js");
exports.fsd = fsd;

module.exports = exports;