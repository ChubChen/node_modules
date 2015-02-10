var async = require('async');
var CronJob = require("cron").CronJob;

var mysql = require('mysql');
var oracle = require('oracle');
var MongoClient = require('mongodb').MongoClient;
var prop = require('./Prop.js');
var DbConnection = require('./DbConnection.js');
var log = require('./McpLog.js');
var ec = require('./ErrCode.js');

var DbPool = function(db){
    var self = this;
    self.db = db;
    if(db.poolSize == undefined)
    {
        self.size = 1
    }
    else
    {
        self.size = db.poolSize;
    }
    self.conns = [];
};

DbPool.prototype.connect = function(cb)
{
    var self = this;
    async.waterfall([
        function(cb)
        {
            var array = [];
            for(var i = 0; i < self.size; i++)
            {
                array[array.length] = i;
            }
            cb(null, array);
        },
        //第一步，创建连接
        function(array, cb)
        {
            if(self.db.type == prop.dbType.mysql || self.db.type == prop.dbType.oracle)
            {
                async.eachSeries(array, function(obj, callback) {
                    if(self.db.type == prop.dbType.mysql)
                    {
                        var index = self.conns.length;
                        var conn = mysql.createConnection(self.db.config);
                        conn.connect(function(err){
                            self.conns[index] = new DbConnection(self.db, self, conn);
                            callback(err);
                        });

                        conn.on("error", function(err) {
                            console.log(err);
                        });
                    }
                    else if(self.db.type == prop.dbType.oracle)
                    {
                        oracle.connect(self.db.config, function(err, connection) {
                            self.conns[self.conns.length] = new DbConnection(self.db, self, connection);
                            callback(err);
                        });
                    }
                }, function(err){
                    cb(err);
                });
            }
            else if(self.db.type == prop.dbType.mongodb)
            {
                MongoClient.connect(self.db.config.url, function(err, db) {
                    if (err) throw err;
                    self.conns[self.conns.length] = new DbConnection(self.db, self, db);
                    cb(err);
                });
            }
            else
            {
                cb("unsurpted database type.");
            }
        },
        //开始定期检查连接的可用性
        function(cb)
        {
            self.checkAvailable();
            cb(null);
        }
    ], function (err) {
        cb(err);
    });
};

DbPool.prototype.getConn = function(index)
{
    var self = this;
    if(index == undefined)
    {
        var ran = Math.round(Math.random()*100);
        var index = ran%self.size;
    }
    return self.conns[index];
};

/**
 * 校验所有连接的可用性
 */
DbPool.prototype.checkAvailable = function()
{
    var self = this;
    self.checkJob = new CronJob('0 */20 * * * *', function () {
        if(self.db.type == prop.dbType.mysql)
        {
            var sql = "select now() as time";
            for(var key in self.conns)
            {
                var conn = self.conns[key];
                conn.execute(sql, {}, function(err, data){
                    log.info("校验连接的可用性..............");
                    log.info(err);
                    log.info(data);
                });
            }
        }
    });
    self.checkJob.start();
}

/*DbPool.prototype.reCreate = function(index)
{
    var self = this;
    if(self.db.type == prop.dbType.mysql)
    {
        var conn = mysql.createConnection(self.db.config);
        conn.connect(function(err){
            cb(err, null);
        });
    }
}*/

module.exports = DbPool;
