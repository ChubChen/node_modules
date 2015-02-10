var prop = require('./Prop.js');

var moment = require("moment");

var DateUtil = function(){
    var self = this;
    self.default_fmt = 'YYYY-MM-DD HH:mm:ss';
};

DateUtil.prototype.toString = function(date)
{
    var self = this;
    return moment(date).format("YYYY-MM-DD HH:mm:ss");
};

DateUtil.prototype.oracleToString = function(date)
{
    var self = this;
    return moment(date).format("YYYY-MM-DD HH:mm:ss");
};

DateUtil.prototype.toDate = function(str)
{
    var self = this;
    return moment(str, self.default_fmt);
};

DateUtil.prototype.oracleObj = function(table, obj)
{
    var self = this;
    var newObj = {};
    for(var key in obj)
    {
        var col = table.colList[key];
        if(col.type == 'date')
        {
            newObj[col.name] = moment(obj[key]).subtract("8", "h").format("YYYY-MM-DD HH:mm:ss");
        }
        else
        {
            newObj[col.name] = obj[key];
        }
    }
    return newObj;
};

/**
 * 把表table对应的数据的日期转换成字符串
 * @param table
 * @param obj
 */
DateUtil.prototype.objDateToString = function(table, obj)
{
    var self = this;
    for(var key in obj)
    {
        var col = table.colList[key];
        if(col)
        {
            if(col.type == 'date')
            {
                if(table.db.type == prop.dbType.oracle)
                {
                    obj[col.name] = moment(obj[key]).subtract("8", "h").format("YYYY-MM-DD HH:mm:ss");
                }
                else
                {
                    obj[col.name] = moment(obj[key]).format("YYYY-MM-DD HH:mm:ss");
                }
            }
        }
    }
};

DateUtil.prototype.getCurTime = function()
{
    var self = this;
    return moment(new Date()).format("YYYY-MM-DD HH:mm:ss");
};

DateUtil.prototype.getLogTime = function()
{
    var self = this;
    return moment(new Date()).format("YYYY-MM-DD HH:mm:ss") + ",";
};


module.exports = new DateUtil();