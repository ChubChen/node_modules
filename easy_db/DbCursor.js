var dbPool = require('./DbPool.js');
var dateUtil = require('./DateUtil.js');
var log = require('./McpLog.js');

var prop = require('./Prop.js');

var DbCurser = function(table, options, baseSql, conditionStr){
    var self = this;
    self.table = table;
    self.baseSql = baseSql;
    self.conditionStr = conditionStr;
    self.options = options;
    self.parseDate = false;
    if(self.conditionStr)
    {
        self.baseSql += " where " + self.conditionStr;
    }
};

DbCurser.prototype.limit = function(start, size)
{
    var self = this;
    if(self.table.db.type == prop.dbType.oracle)
    {
        var sql = "SELECT * FROM (SELECT A.*, ROWNUM RN FROM (";
        sql += self.baseSql;
        sql += ") A WHERE ROWNUM <= " + (start + size) + ") WHERE RN > " + start;
        self.baseSql = sql;
    }
    else
    {
        var sql = " limit " + start + "," + size;
        self.baseSql += sql;
    }
    return self;
};

DbCurser.prototype.dateToString = function()
{
    var self = this;
    self.parseDate = true;
};

DbCurser.prototype.sort = function(data)
{
    var self = this;
    var count = 0;
    var sql = " order by ";
    for(var key in data)
    {
        if(count > 0)
        {
            sql += ",";
        }
        if(data[key] > 0)
        {
            sql += key;
        }
        else
        {
            sql += key + " desc";
        }
        count++;
    }
    if(count > 0)
    {
        self.baseSql += sql;
    }
    return self;
};

DbCurser.prototype.toArray = function(cb)
{
    var self = this;
    var sql = self.baseSql;
    log.info(sql);
    var conn = self.table.db.pool.getConn();
    conn.execute(sql, self.options, function(err, data){
        if(err)
        {
            log.info(err);
        }
        var backSet = [];
        if(data)
        {
            if(self.table.db.type == prop.dbType.oracle)
            {
                for(var key in data)
                {
                    var newSet = {};
                    var set = data[key];
                    for(var setKey in set)
                    {
                        newSet[self.table.nameRelation[setKey]] = set[setKey];
                    }
                    backSet[backSet.length] = newSet;
                }
            }
            else
            {
                backSet = data;
            }
        }
        if(backSet.length > 0 && self.parseDate)
        {
            for(var key in backSet)
            {
                dateUtil.objDateToString(self.table, backSet[key]);
            }
        }
        cb(err, backSet);
    });
};

DbCurser.prototype.count = function(cb)
{
    var self = this;
    var sql = "select count(*) as num from " + self.table.name;
    if(self.conditionStr)
    {
        sql += " where " + self.conditionStr;
    }
    log.info(sql);
    var conn = self.table.db.pool.getConn();
    conn.execute(sql, self.options, function(err, data){
        if(data && data.length > 0)
        {
            if(self.table.db.type == prop.dbType.oracle)
            {
                cb(null, data[0].NUM);
            }
            else
            {
                cb(null, data[0].num);
            }
        }
        else
        {
            cb(err, data);
        }
    });
};

module.exports = DbCurser;