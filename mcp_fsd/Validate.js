var async = require('async');

var config = require('mcp_config');
var ec = config.ec;
var game = config.game;

var esut = require('easy_util');
var log = esut.log;

var util = require('mcp_util');
var mathUtil = util.mathUtil;

var Validate = function(){
    var self = this;
    //直选和值最大值
    self.ZHIXUAN_HEZHI_MAX = 27;
    //直选和值最小值
    self.ZHIXUAN_HEZHI_MIN = 0;
    //组选和值最大值
    self.ZUXUAN_HEZHI_MAX = 26;
    //组选和值最小值
    self.ZUXUAN_HEZHI_MIN = 1;
    //pls组选和值，注数对照表，索引为和值的大小，值为注数
    self.ZUXUAN_HEZHI_COUNT = [0, 1, 2, 2, 4, 5, 6, 8, 10, 11, 13, 14, 14, 15, 15, 14, 14, 13, 11, 10, 8, 6, 5, 4, 2, 2, 1];
    //pls直选和值，注数对照表，索引为和值的大小，值为注数
    self.ZHIXUAN_HEZHI_COUNT = [1, 3, 6, 10, 15, 21, 28, 36, 45, 55, 63, 69, 73, 75, 75, 73, 69, 63, 55, 45, 36, 28, 21, 15, 10, 6, 3, 1];

};

Validate.prototype.validate = function(order, ticket, cb)
{
    var self = this;
    var tickets = order.tickets;
    var name = "validate" + ticket.pType + ticket.bType;
    if(self[name])
    {
        var number = ticket.number;
        if(!number)
        {
            cb(ec.E2066);
            return;
        }
        self[name](order, ticket, function(err, count){
            if(err)
            {
                cb(err);
            }
            else
            {
                var price = game.getInfo(ticket.gameCode, ticket.pType).price;
                //校验注数
                if(count*ticket.multiple*price != ticket.amount)
                {
                    cb(ec.E2061);
                }
                else
                {
                    cb(null);
                }
            }
        });
    }
    else
    {
        cb(ec.E2062);
    }
}

/**
 * 直选单式
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate0100 = function(order, ticket, cb)
{
    var self = this;
    var number = ticket.number;
    var items = number.split(";");
    if(items.length > 5 ){
        cb(ec.E2071);
        return;
    }
    for(var key in items)
    {
        var item = items[key];
        var reg = /^[0-9]{1}(\|[0-9]){2}$/;
        if(!reg.test(item))
        {
            cb(ec.E2066);
            return;
        }
    }
    cb(null, items.length);
}

/**
 * 直选复式
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate0101 = function(order, ticket, cb)
{
    var self = this;
    var number = ticket.number;
    var reg = /^[0-9]{1}(,[0-9]){0,9}(\|[0-9]{1}(,[0-9]){0,9}){2}$/;
    if(!reg.test(number))
    {
        cb(ec.E2066);
        return;
    }
    var posStrArray = number.split("|");
    var count = 1;
    for(var i = 0; i < posStrArray.length; i++)
    {
        var posIntArray = mathUtil.getIntArrayFromStrArray(posStrArray[i].split(","));
        if(!mathUtil.isFromMinToMax(posIntArray))
        {
            cb(ec.E2066);
            return;
        }
        count = count*posIntArray.length;
    }
    cb(null, count);
}

/**
 * 直选和值
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate0103 = function(order, ticket, cb)
{
    var self = this;
    var number = ticket.number;
    var reg = /^[0-9]{1,2}(,[0-9]{1,2}){0,}$/;
    if(!reg.test(number))
    {
        cb(ec.E2066);
        return;
    }
    var intArray = mathUtil.getIntArrayFromStrArray(number.split(","));
    if(!mathUtil.isFromMinToMax(intArray))
    {
        cb(ec.E2066);
        return;
    }
    if(intArray[0] < 0 || intArray[intArray.length - 1] > self.ZHIXUAN_HEZHI_MAX)
    {
        cb(ec.E2066);
        return;
    }
    var count = 0;
    for(var i = 0; i < intArray.length; i++)
    {
        count += self.ZHIXUAN_HEZHI_COUNT[intArray[i]];
    }
    cb(null, count);
}

/**
 * 组三复式
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate0201 = function(order, ticket, cb)
{
    var self = this;
    var number = ticket.number;
    var reg = /^[0-9]{1}(,[0-9]){1,9}$/;
    if(!reg.test(number))
    {
        cb(ec.E2066);
        return;
    }
    var intArray = mathUtil.getIntArrayFromStrArray(number.split(","));
    if(!mathUtil.isFromMinToMax(intArray))
    {
        cb(ec.E2066);
        return;
    }
    var count = mathUtil.getC(intArray.length, 2)*2;
    cb(null, count);
}

/**
 * 组六复式
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate0301 = function(order, ticket, cb)
{
    var self = this;
    var number = ticket.number;
    var reg = /^[0-9]{1}(,[0-9]){3,9}$/;
    if(!reg.test(number))
    {
        cb(ec.E2066);
        return;
    }
    var intArray = mathUtil.getIntArrayFromStrArray(number.split(","));
    if(!mathUtil.isFromMinToMax(intArray))
    {
        cb(ec.E2066);
        return;
    }
    var count = mathUtil.getC(intArray.length, 3);
    cb(null, count);
}

/**
 * 组选和值
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate0403 = function(order, ticket, cb)
{
    var self = this;
    var number = ticket.number;
    var reg = /^[0-9]{1,2}(,[0-9]{1,2}){0,}$/;
    if(!reg.test(number))
    {
        cb(ec.E2066);
        return;
    }
    var intArray = mathUtil.getIntArrayFromStrArray(number.split(","));
    if(!mathUtil.isFromMinToMax(intArray))
    {
        cb(ec.E2066);
        return;
    }
    if(intArray[0] < self.ZUXUAN_HEZHI_MIN || intArray[intArray.length - 1] > self.ZUXUAN_HEZHI_MAX)
    {
        cb(ec.E2066);
        return;
    }
    var count = 0;
    for(var i = 0; i < intArray.length; i++)
    {
        count += self.ZUXUAN_HEZHI_COUNT[intArray[i]];
    }
    cb(null, count);
}

module.exports = new Validate();