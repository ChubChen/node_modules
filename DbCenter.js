var async = require('async');
var esdb = require('./easy_db');
var Database = esdb.Database;
var Table = esdb.Table;
var Column = esdb.Column;
var prop = require('./Prop.js');

var DbCenter = function(){
    var self = this;
};

DbCenter.prototype.init = function(cb)
{
    var self = this;
    esdb.log.setShowLog(true);
    async.waterfall([
        //the mysql
        function(cb){
            self._initMain(function(err){
                cb(err);
            });
        },
        //the mongodb
        function(cb){
            self._initMg(function(err){
                cb(err);
            });
        }
    ], function (err, result) {
        cb(err);
    });
};

DbCenter.prototype.check = function(cb)
{
    var self = this;
    async.waterfall([
        //check the mysql
        function(cb){
            self._checkMain(function(err){
                cb(err);
            });
        },
        //check the mongodb
        function(cb){
            self._checkMg(function(err){
                cb(err);
            });
        }
    ], function (err, result) {
        cb(err);
    });
};

DbCenter.prototype._initMg = function(cb)
{
    var self = this;
    var db = new Database(prop.dbs[0]);

    //add tables
    var uniqueIdTable = new Table(db, "uniqueId", [
        new Column(db, "_id", "varchar", 80, false, undefined, true, false)
    ]);
    db.put(uniqueIdTable);
    var stInfoTable = new Table(db, "stInfo", [
        new Column(db, "_id", "varchar", 80, false, undefined, true, false),
        new Column(db, "st", "varchar", 32, false, undefined),
        new Column(db, "lastActiveTime", "bigint", -1, false, undefined)
    ]);
    db.put(stInfoTable);
    self.mg = db;
    self.mg.init(cb);
};

DbCenter.prototype._checkMg = function(cb)
{
    var self = this;
    cb(null);
};

DbCenter.prototype._checkMain = function(cb)
{
    var self = this;
    var userTable = self.main.get("user");
    var admin = {id:"admin", password:"123456", type:prop.userType.ADMIN};
    userTable.findOne({id:admin.id}, {}, [], function(err, data){
        if(err)
        {
            cb(err);
        }
        else
        {
            if(!data)
            {
                userTable.save(admin, [], function(err, data){
                    cb(null);
                });
            }
            else
            {
                cb(null);
            }
        }
    });
};

DbCenter.prototype._initMain = function(cb)
{
    var self = this;
    var db = new Database(prop.dbs[1]);

    //add tables
    var area = new Table(db, "area", [
        new Column(db, "id", "varchar", 80, false, undefined, true, false),
        new Column(db, "name", "varchar", 20, false, undefined),
        new Column(db, "version", "int", 11, false, 0)
    ]);
    db.put(area);
    var league = new Table(db, "league", [
        new Column(db, "id", "varchar", 80, false, undefined, true, false),
        new Column(db, "name", "varchar", 20, false, undefined),
        new Column(db, "areaId", "varchar", 80, false, undefined),
        new Column(db, "version", "int", 11, false, 0)
    ]);
    db.put(league);
    var user = new Table(db, "user", [
        new Column(db, "id", "varchar", 80, false, undefined, true, false),
        new Column(db, "password", "varchar", 80, false, undefined),
        new Column(db, "type", "int", 11, false, undefined),
        new Column(db, "version", "int", 11, false, 0)
    ]);
    db.put(user);
    var operation = new Table(db, "operation", [
        new Column(db, "id", "varchar", 40, false, undefined),
        new Column(db, "userType", "int", 11, false, undefined),
        new Column(db, "hasChildren", "int", 11, false, 0),
        new Column(db, "name", "varchar", 20, false, undefined),
        new Column(db, "parent", "varchar", 40, false, ''),
        new Column(db, "url", "varchar", 80, false, undefined),
        new Column(db, "version", "int", 11, false, 0)
    ]);
    db.put(operation);
    self.main = db;
    self.main.init(cb);
};

module.exports = new DbCenter();

