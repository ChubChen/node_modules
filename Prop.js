var esdb = require('./easy_db');

var exports = {};

exports.userType = {"CUSTOMER":0, "ADMIN":1};
exports.userTypeArray = [{id:0, code:'CUSTOMER', des:"普通用户"},
    {id:1, code:'ADMIN', des:"系统管理员"}];

//config db basic type
var dbs = [{
    config:{'url':'mongodb://127.0.0.1:27017/football'},
    type:esdb.prop.dbType.mongodb
},{
    config:{
        'host':'localhost',
        'user':'root',
        'password':'123456',
        'port':3306,
        'database':'football'
    },
    type:esdb.prop.dbType.mysql
}];
exports.dbs = dbs;

module.exports = exports;


