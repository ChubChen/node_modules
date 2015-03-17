var esdb = require('easy_db');
var exports = {};
var target = 'dev';

var argv = process.argv;
var kvs = {};
for(var key in argv)
{
    if(key > 1)
    {
        var kv = argv[key].split("=");
        kvs[kv[0]] = kv[1];
    }
}
if(kvs.target)
{
    target = kvs.target;
}

//网关端口
if(kvs.gtPort)
{
    exports.gtPort = kvs.gtPort;
}
else
{
    exports.gtPort = 9090;
}

exports.platform = {};

//runtime target
exports.target = target;

//算奖的分块大小
exports.drawCount = 6;

//config db basic type
var dbs = {
    'devMg': {
        config: {'url': 'mongodb://192.168.0.20:27017/node_mcp'},
        type: esdb.prop.dbType.mongodb
    },
    'runMg': {
        config: {'url': 'mongodb://192.168.0.22:27017/node_mcp'},
        type: esdb.prop.dbType.mongodb
    },
    'devMain': {
        config: {
            'host': '192.168.0.20',
            'user': 'root',
            'password': '0okmnhy6zqc',
            'port': 3306,
            'database': 'node_mcp'
        },
        type: esdb.prop.dbType.mysql,
        dateToLong: true,
        poolSize:4
    },
    'runMain': {
        config: {
            'host': '192.168.0.23',
            'user': 'root',
            'password': '0okmnhy6zqc',
            'port': 3306,
            'database': 'node_mcp'
        },
        type: esdb.prop.dbType.mysql,
        dateToLong: true,
        poolSize:40
    },
    'devMsg': {
        config: {'url': 'mongodb://192.168.0.20:27017/node_mcp_msg'},
        type: esdb.prop.dbType.mongodb
    },'runMsg': {
        config: {'url': 'mongodb://192.168.0.22:27017/node_mcp_msg'},
        type: esdb.prop.dbType.mongodb
    },
    'testMain': {
        config: {
            'host': '192.168.0.20',
            'user': 'root',
            'password': '0okmnhy6zqc',
            'port': 3306,
            'database': 'node_mcp'
        },
        type: esdb.prop.dbType.mysql,
        dateToLong: true,
        poolSize:4
    }
}
if(target == 'dev')
{
    exports.main = dbs.devMain;
    exports.mg = dbs.devMg;
    exports.msg = dbs.devMsg;

    exports.platform.site = {
        hostname: '192.168.0.19',
        port: 9088,
        path: '/mcp-filter/main/interface.htm',
        method: 'POST'
    };

    exports.platform.gateways = [
        {host:'127.0.0.1', port:9090, method:'POST'},
        {host:'127.0.0.1', port:9091, method:'POST'}
    ];

    exports.filterPort = 9088;
}
else if(target == 'test')
{
    exports.main = dbs.testMain;
    exports.mg = dbs.devMg;
    exports.msg = dbs.devMsg;

    exports.platform.site = {
        hostname: '192.168.0.19',
        port: 9088,
        path: '/mcp-filter/main/interface.htm',
        method: 'POST'
    };


    exports.platform.gateways = [
        {host:'127.0.0.1', port:9090, method:'POST'},
        {host:'127.0.0.1', port:9091, method:'POST'},
        {host:'127.0.0.1', port:9092, method:'POST'},
        {host:'127.0.0.1', port:9093, method:'POST'},
        {host:'127.0.0.1', port:9094, method:'POST'}
    ];

    exports.filterPort = 9088;
}
else if(target == 'run')
{
    exports.main = dbs.runMain;
    exports.mg = dbs.runMg;
    exports.msg = dbs.runMsg;

    exports.platform.site = {
        hostname: '218.30.107.21',
        port: 80,
        path: '/mcp-filter/main/interface.htm',
        method: 'POST'
    };


    exports.platform.gateways = [
        {host:'192.168.0.21', port:9090, method:'POST'},
        {host:'192.168.0.21', port:9091, method:'POST'},
        {host:'192.168.0.21', port:9092, method:'POST'},
        {host:'192.168.0.21', port:9093, method:'POST'},
        {host:'192.168.0.21', port:9094, method:'POST'},
        {host:'192.168.0.23', port:9090, method:'POST'},
        {host:'192.168.0.23', port:9091, method:'POST'},
        {host:'192.168.0.23', port:9092, method:'POST'},
        {host:'192.168.0.23', port:9093, method:'POST'},
        {host:'192.168.0.23', port:9094, method:'POST'}
    ];

    exports.filterPort = 9088;
}


//暂时支持3种密钥来源
exports.digestFromType = {"NONE":0, "DB":1, "CACHE":2, "FIX":3};
exports.digestFromTypeArray = [
    {id:0, code:'NONE', des:"无"},
    {id:1, code:'DB', des:"数据库"},
    {id:2, code:'CACHE', des:"缓存"},
    {id:3, code:'FIX', des:"缓存固定"}
];

//if user hasn't operation in half a hour, the key will be expired.
exports.loginExpiredSeconds = 30*60;

module.exports = exports;



