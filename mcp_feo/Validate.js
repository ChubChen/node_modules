var async = require('async');

var config = require('mcp_config');
var ec = config.ec;
var game = config.game;

var esut = require('easy_util');
var log = esut.log;

var util = require('mcp_util');
var mathUtil = util.mathUtil;

var NumType = require('./NumType.js');

var Validate = function(){
    var self = this;
    self.rtHeZhiCountList = [];
    self.rtHeZhiCountList[0] = 0;
    self.rtHeZhiCountList[1] = 0;
    self.rtHeZhiCountList[2] = 1;
    self.rtHeZhiCountList[3] = 2;
    self.rtHeZhiCountList[4] = 3;
    self.rtHeZhiCountList[5] = 4;
    self.rtHeZhiCountList[6] = 5;
    self.rtHeZhiCountList[7] = 6;
    self.rtHeZhiCountList[8] = 7;
    self.rtHeZhiCountList[9] = 8;
    self.rtHeZhiCountList[10] = 7;
    self.rtHeZhiCountList[11] = 6;
    self.rtHeZhiCountList[12] = 5;
    self.rtHeZhiCountList[13] = 4;
    self.rtHeZhiCountList[14] = 3;
    self.rtHeZhiCountList[15] = 2;
    self.rtHeZhiCountList[16] = 1;

    var kuaDuCountList = [];
    kuaDuCountList[0] = 8;
    kuaDuCountList[1] = 14;
    kuaDuCountList[2] = 12;
    kuaDuCountList[3] = 10;
    kuaDuCountList[4] = 8;
    kuaDuCountList[5] = 6;
    kuaDuCountList[6] = 4;
    kuaDuCountList[7] = 2;
    self.kuaDuCountList = kuaDuCountList;
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
        //按游戏先做倍数验证
        if(ticket.multiple > 99){
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
 * 组选，单式
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate0000 = function(order, ticket, cb)
{
    var self = this;
    var number = ticket.number;
    var items = number.split(";");
    for(var key in items)
    {
        var item = items[key];
        var reg = /^[0-9]{1}(,[0-9]){3}$/;
        if(!reg.test(item))
        {
            cb(ec.E2066);
            return;
        }
        var intArray = mathUtil.getIntArrayFromStrArray(item.split(","));
        if(!mathUtil.isFromMinToMaxCanEqual(intArray))
        {
            cb(ec.E2066);
            return;
        }
        if(intArray[0] < 1 || intArray[intArray.length - 1] > 8)
        {
            cb(ec.E2066);
            return;
        }
        var nt = new NumType(item);
        if(nt.isZ1())   //校验4个号码是否都相同
        {
            cb(ec.E2066);
            return;
        }
    }
    if(items.length > 5 ){
        cb(ec.E2071);
        return;
    }
    cb(null, items.length);
}

/**
 * 组24，单式
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate0100 = function(order, ticket, cb)
{
    var self = this;
    var number = ticket.number;
    var items = number.split(";");
    for(var key in items)
    {
        var item = items[key];
        var reg = /^[0-9]{1}(,[0-9]){3}$/;
        if(!reg.test(item))
        {
            cb(ec.E2066);
            return;
        }
        var intArray = mathUtil.getIntArrayFromStrArray(item.split(","));
        if(!mathUtil.isFromMinToMax(intArray))
        {
            cb(ec.E2066);
            return;
        }
        if(intArray[0] < 1 || intArray[intArray.length - 1] > 8)
        {
            cb(ec.E2066);
            return;
        }
    }
    if(items.length > 5 ){
        cb(ec.E2071);
        return;
    }
    cb(null, items.length);
}

/**
 * 组24，复式
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate0101 = function(order, ticket, cb)
{
    var self = this;
    var item = ticket.number;
    var reg = /^[0-9]{1}(,[0-9]){4,7}$/;
    if(!reg.test(item))
    {
        cb(ec.E2066);
        return;
    }
    var intArray = mathUtil.getIntArrayFromStrArray(item.split(","));
    if(!mathUtil.isFromMinToMax(intArray))
    {
        cb(ec.E2066);
        return;
    }
    if(intArray[0] < 1 || intArray[intArray.length - 1] > 8)
    {
        cb(ec.E2066);
        return;
    }
    cb(null, mathUtil.getC(intArray.length, 4));
}

/**
 * 组24，胆拖
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate0102 = function(order, ticket, cb)
{
    var self = this;
    var item = ticket.number;
    var reg = /^[0-9]{1}(,[0-9]){0,2}\$[0-9]{1}(,[0-9]){1,6}$/;
    if(!reg.test(item))
    {
        cb(ec.E2066);
        return;
    }
    var numStrArray = item.split("$");
    var danStr = numStrArray[0];
    var tuoStr = numStrArray[1];

    var danIntArray = mathUtil.getIntArrayFromStrArray(danStr.split(","));
    if(!mathUtil.isFromMinToMax(danIntArray))
    {
        cb(ec.E2066);
        return;
    }
    if(danIntArray[0] < 1 || danIntArray[danIntArray.length - 1] > 8)
    {
        cb(ec.E2066);
        return;
    }

    var tuoIntArray = mathUtil.getIntArrayFromStrArray(tuoStr.split(","));
    if(!mathUtil.isFromMinToMax(tuoIntArray))
    {
        cb(ec.E2066);
        return;
    }
    if(tuoIntArray[0] < 1 || tuoIntArray[tuoIntArray.length - 1] > 8)
    {
        cb(ec.E2066);
        return;
    }

    var hitCount = mathUtil.getHitCount(danIntArray, tuoIntArray);
    if(hitCount > 0)
    {
        cb(ec.E2066);
        return;
    }

    var m = tuoIntArray.length, n = 4 - danIntArray.length;
    cb(null, mathUtil.getC(m, n));
}

/**
 * 组12，单式
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate0200 = function(order, ticket, cb)
{
    var self = this;
    var number = ticket.number;
    var items = number.split(";");
    for(var key in items)
    {
        var item = items[key];
        var reg = /^[0-9]{1}(,[0-9]){3}$/;
        if(!reg.test(item))
        {
            cb(ec.E2066);
            return;
        }
        var intArray = mathUtil.getIntArrayFromStrArray(item.split(","));
        if(!mathUtil.isFromMinToMaxCanEqual(intArray))
        {
            cb(ec.E2066);
            return;
        }
        if(intArray[0] < 1 || intArray[intArray.length - 1] > 8)
        {
            cb(ec.E2066);
            return;
        }
        var nt = new NumType(item);
        if(!nt.isZ12())
        {
            cb(ec.E2066);
            return;
        }
    }
    if(items.length > 5 ){
        cb(ec.E2071);
        return;
    }
    cb(null, items.length);
}


/**
 * 组12，复式
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate0201 = function(order, ticket, cb)
{
    var self = this;
    var item = ticket.number;
    var reg = /^[0-9]{1}(,[0-9]){2,7}$/;
    if(!reg.test(item))
    {
        cb(ec.E2066);
        return;
    }
    var intArray = mathUtil.getIntArrayFromStrArray(item.split(","));
    if(!mathUtil.isFromMinToMax(intArray))
    {
        cb(ec.E2066);
        return;
    }
    if(intArray[0] < 1 || intArray[intArray.length - 1] > 8)
    {
        cb(ec.E2066);
        return;
    }
    cb(null, mathUtil.getC(intArray.length, 3)*3);
}

/**
 * 组12，胆拖
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate0202 = function(order, ticket, cb)
{
    var self = this;
    var item = ticket.number;
    var reg = /^[0-9]{1}(,[0-9]){0,1}\$[0-9]{1}(,[0-9]){1,6}$/;
    if(!reg.test(item))
    {
        cb(ec.E2066);
        return;
    }
    var numStrArray = item.split("$");
    var danStr = numStrArray[0];
    var tuoStr = numStrArray[1];

    var danIntArray = mathUtil.getIntArrayFromStrArray(danStr.split(","));
    if(!mathUtil.isFromMinToMax(danIntArray))
    {
        cb(ec.E2066);
        return;
    }
    if(danIntArray[0] < 1 || danIntArray[danIntArray.length - 1] > 8)
    {
        cb(ec.E2066);
        return;
    }

    var tuoIntArray = mathUtil.getIntArrayFromStrArray(tuoStr.split(","));
    if(!mathUtil.isFromMinToMax(tuoIntArray))
    {
        cb(ec.E2066);
        return;
    }
    if(tuoIntArray[0] < 1 || tuoIntArray[tuoIntArray.length - 1] > 8)
    {
        cb(ec.E2066);
        return;
    }

    var hitCount = mathUtil.getHitCount(danIntArray, tuoIntArray);
    if(hitCount > 0)
    {
        cb(ec.E2066);
        return;
    }

    var m = tuoIntArray.length, n = 3 - danIntArray.length;
    cb(null, mathUtil.getC(m, n)*3);
}

/**
 * 组12，重胆拖
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate0208 = function(order, ticket, cb)
{
    var self = this;
    var item = ticket.number;
    var reg = /^[0-9]{1}\$[0-9]{1}(,[0-9]){2,6}$/;
    if(!reg.test(item))
    {
        cb(ec.E2066);
        return;
    }
    var numStrArray = item.split("$");
    var danStr = numStrArray[0];
    var tuoStr = numStrArray[1];

    var danIntArray = mathUtil.getIntArrayFromStrArray(danStr.split(","));
    if(!mathUtil.isFromMinToMax(danIntArray))
    {
        cb(ec.E2066);
        return;
    }
    if(danIntArray[0] < 1 || danIntArray[danIntArray.length - 1] > 8)
    {
        cb(ec.E2066);
        return;
    }

    var tuoIntArray = mathUtil.getIntArrayFromStrArray(tuoStr.split(","));
    if(!mathUtil.isFromMinToMax(tuoIntArray))
    {
        cb(ec.E2066);
        return;
    }
    if(tuoIntArray[0] < 1 || tuoIntArray[tuoIntArray.length - 1] > 8)
    {
        cb(ec.E2066);
        return;
    }

    var hitCount = mathUtil.getHitCount(danIntArray, tuoIntArray);
    if(hitCount > 0)
    {
        cb(ec.E2066);
        return;
    }

    var m = tuoIntArray.length, n = 3 - danIntArray.length;
    cb(null, mathUtil.getC(m, n));
}

/**
 * 组6，单式
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate0300 = function(order, ticket, cb)
{
    var self = this;
    var number = ticket.number;
    var items = number.split(";");
    for(var key in items)
    {
        var item = items[key];
        var reg = /^[0-9]{1}(,[0-9]){3}$/;
        if(!reg.test(item))
        {
            cb(ec.E2066);
            return;
        }
        var intArray = mathUtil.getIntArrayFromStrArray(item.split(","));
        if(!mathUtil.isFromMinToMaxCanEqual(intArray))
        {
            cb(ec.E2066);
            return;
        }
        if(intArray[0] < 1 || intArray[intArray.length - 1] > 8)
        {
            cb(ec.E2066);
            return;
        }
        var nt = new NumType(item);
        if(!nt.isZ6())
        {
            cb(ec.E2066);
            return;
        }
    }
    if(items.length > 5 ){
        cb(ec.E2071);
        return;
    }
    cb(null, items.length);
}

/**
 * 组6，复式
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate0301 = function(order, ticket, cb)
{
    var self = this;
    var number = ticket.number;
    var items = number.split(";");
    for(var key in items)
    {
        var item = items[key];
        var reg = /^[0-9]{1}(,[0-9]){2,7}$/;
        if(!reg.test(item))
        {
            cb(ec.E2066);
            return;
        }
        var intArray = mathUtil.getIntArrayFromStrArray(item.split(","));
        if(!mathUtil.isFromMinToMax(intArray))
        {
            cb(ec.E2066);
            return;
        }
        if(intArray[0] < 1 || intArray[intArray.length - 1] > 8)
        {
            cb(ec.E2066);
            return;
        }
    }
    cb(null, mathUtil.getC(intArray.length, 2));
}

/**
 * 组6，胆拖
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate0302 = function(order, ticket, cb)
{
    var self = this;
    var item = ticket.number;
    var reg = /^[0-9]{1}\$[0-9]{1}(,[0-9]){1,6}$/;
    if(!reg.test(item))
    {
        cb(ec.E2066);
        return;
    }
    var numStrArray = item.split("$");
    var danStr = numStrArray[0];
    var tuoStr = numStrArray[1];

    var danIntArray = mathUtil.getIntArrayFromStrArray(danStr.split(","));
    if(!mathUtil.isFromMinToMax(danIntArray))
    {
        cb(ec.E2066);
        return;
    }
    if(danIntArray[0] < 1 || danIntArray[danIntArray.length - 1] > 8)
    {
        cb(ec.E2066);
        return;
    }

    var tuoIntArray = mathUtil.getIntArrayFromStrArray(tuoStr.split(","));
    if(!mathUtil.isFromMinToMax(tuoIntArray))
    {
        cb(ec.E2066);
        return;
    }
    if(tuoIntArray[0] < 1 || tuoIntArray[tuoIntArray.length - 1] > 8)
    {
        cb(ec.E2066);
        return;
    }

    var hitCount = mathUtil.getHitCount(danIntArray, tuoIntArray);
    if(hitCount > 0)
    {
        cb(ec.E2066);
        return;
    }

    var m = tuoIntArray.length, n = 2 - danIntArray.length;
    cb(null, mathUtil.getC(m, n));
}

/**
 * 组4，单式
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate0400 = function(order, ticket, cb)
{
    var self = this;
    var number = ticket.number;
    var items = number.split(";");
    for(var key in items)
    {
        var item = items[key];
        var reg = /^[0-9]{1}(,[0-9]){3}$/;
        if(!reg.test(item))
        {
            cb(ec.E2066);
            return;
        }
        var intArray = mathUtil.getIntArrayFromStrArray(item.split(","));
        if(!mathUtil.isFromMinToMaxCanEqual(intArray))
        {
            cb(ec.E2066);
            return;
        }
        if(intArray[0] < 1 || intArray[intArray.length - 1] > 8)
        {
            cb(ec.E2066);
            return;
        }
        var nt = new NumType(item);
        if(!nt.isZ4())
        {
            cb(ec.E2066);
            return;
        }
    }
    if(items.length > 5 ){
        cb(ec.E2071);
        return;
    }
    cb(null, items.length);
}

/**
 * 组4，复式
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate0401 = function(order, ticket, cb)
{
    var self = this;
    var number = ticket.number;
    var items = number.split(";");
    for(var key in items)
    {
        var item = items[key];
        var reg = /^[0-9]{1}(,[0-9]){1,7}$/;
        if(!reg.test(item))
        {
            cb(ec.E2066);
            return;
        }
        var intArray = mathUtil.getIntArrayFromStrArray(item.split(","));
        if(!mathUtil.isFromMinToMax(intArray))
        {
            cb(ec.E2066);
            return;
        }
        if(intArray[0] < 1 || intArray[intArray.length - 1] > 8)
        {
            cb(ec.E2066);
            return;
        }
    }
    cb(null, mathUtil.getC(intArray.length, 2)*2);
}

/**
 * 组4，胆拖
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate0402 = function(order, ticket, cb)
{
    var self = this;
    var item = ticket.number;
    var reg = /^[0-9]{1}\$[0-9]{1}(,[0-9]){1,6}$/;
    if(!reg.test(item))
    {
        cb(ec.E2066);
        return;
    }
    var numStrArray = item.split("$");
    var danStr = numStrArray[0];
    var tuoStr = numStrArray[1];

    var danIntArray = mathUtil.getIntArrayFromStrArray(danStr.split(","));
    if(!mathUtil.isFromMinToMax(danIntArray))
    {
        cb(ec.E2066);
        return;
    }
    if(danIntArray[0] < 1 || danIntArray[danIntArray.length - 1] > 8)
    {
        cb(ec.E2066);
        return;
    }

    var tuoIntArray = mathUtil.getIntArrayFromStrArray(tuoStr.split(","));
    if(!mathUtil.isFromMinToMax(tuoIntArray))
    {
        cb(ec.E2066);
        return;
    }
    if(tuoIntArray[0] < 1 || tuoIntArray[tuoIntArray.length - 1] > 8)
    {
        cb(ec.E2066);
        return;
    }

    var hitCount = mathUtil.getHitCount(danIntArray, tuoIntArray);
    if(hitCount > 0)
    {
        cb(ec.E2066);
        return;
    }

    var m = tuoIntArray.length, n = 2 - danIntArray.length;
    cb(null, mathUtil.getC(m, n)*2);
}

/**
 * 组4，重胆拖
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate0408 = function(order, ticket, cb)
{
    var self = this;
    var item = ticket.number;
    var reg = /^[0-9]{1}\$[0-9]{1}(,[0-9]){1,6}$/;
    if(!reg.test(item))
    {
        cb(ec.E2066);
        return;
    }
    var numStrArray = item.split("$");
    var danStr = numStrArray[0];
    var tuoStr = numStrArray[1];

    var danIntArray = mathUtil.getIntArrayFromStrArray(danStr.split(","));
    if(!mathUtil.isFromMinToMax(danIntArray))
    {
        cb(ec.E2066);
        return;
    }
    if(danIntArray[0] < 1 || danIntArray[danIntArray.length - 1] > 8)
    {
        cb(ec.E2066);
        return;
    }

    var tuoIntArray = mathUtil.getIntArrayFromStrArray(tuoStr.split(","));
    if(!mathUtil.isFromMinToMax(tuoIntArray))
    {
        cb(ec.E2066);
        return;
    }
    if(tuoIntArray[0] < 1 || tuoIntArray[tuoIntArray.length - 1] > 8)
    {
        cb(ec.E2066);
        return;
    }

    var hitCount = mathUtil.getHitCount(danIntArray, tuoIntArray);
    if(hitCount > 0)
    {
        cb(ec.E2066);
        return;
    }

    var m = tuoIntArray.length, n = 2 - danIntArray.length;
    cb(null, mathUtil.getC(m, n));
}

/**
 * 任1，单式
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate0500 = function(order, ticket, cb)
{
    var self = this;
    var number = ticket.number;
    var items = number.split(";");
    for(var key in items)
    {
        var item = items[key];
        var reg = /^[0-9|_]{1}(\|[0-9|_]){3}$/;
        if(!reg.test(item))
        {
            cb(ec.E2066);
            return;
        }
        var count = 0;
        var posStrArray = item.split("|");
        for(var posKey in posStrArray)
        {
            if(posStrArray[posKey] != "_")
            {
                var intArray = mathUtil.getIntArrayFromStrArray(posStrArray[posKey].split(","));
                if(!mathUtil.isFromMinToMax(intArray))
                {
                    cb(ec.E2066);
                    return;
                }
                if(intArray[0] < 1 || intArray[intArray.length - 1] > 8)
                {
                    cb(ec.E2066);
                    return;
                }
                count++;
            }
        }
        if(count != 1)
        {
            cb(ec.E2066);
            return;
        }
    }
    if(items.length > 5 ){
        cb(ec.E2071);
        return;
    }
    cb(null, items.length);
}

/**
 * 任1，复式
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate0501 = function(order, ticket, cb)
{
    var self = this;
    var item = ticket.number;
    log.info(item);
    var reg = /^([0-9,]{1,}|_){1}(\|([0-9,]{1,}|_)){3}$/;
    if(!reg.test(item))
    {
        cb(ec.E2066);
        return;
    }
    var count = 0;
    var posStrArray = item.split("|");
    for(var posKey in posStrArray)
    {
        if(posStrArray[posKey] != "_")
        {
            var intArray = mathUtil.getIntArrayFromStrArray(posStrArray[posKey].split(","));
            if(!mathUtil.isFromMinToMax(intArray))
            {
                cb(ec.E2066);
                return;
            }
            if(intArray[0] < 1 || intArray[intArray.length - 1] > 8)
            {
                cb(ec.E2066);
                return;
            }
            count += intArray.length;
        }
    }
    if(count <= 1)
    {
        cb(ec.E2066);
        return;
    }
    cb(null, count);
}

/**
 * 任2，单式
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate0600 = function(order, ticket, cb)
{
    var self = this;
    var number = ticket.number;
    var items = number.split(";");
    if(items.length > 5 ){
        cb(ec.E2071);
        return;
    }
    async.each(items, function(item, callback) {
        self.validateRn(order, {number:item}, 2, function(err, count){
            if(err)
            {
                callback(err);
            }
            else
            {
                if(count != 1)
                {
                    callback(ec.E2066);
                }
                else
                {
                    callback();
                }
            }
        });
    }, function(err){
        cb(null, items.length);
    });
}

/**
 * 任2，复式
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate0601 = function(order, ticket, cb)
{
    var self = this;
    self.validateRn(order, ticket, 2, function(err, count){
        if(err)
        {
            cb(err);
        }
        else
        {
            if(count < 2)
            {
                cb(ec.E2066);
            }
            else
            {
                cb(null, count);
            }
        }
    });
}

/**
 * 任2，和值
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate0603 = function(order, ticket, cb)
{
    var self = this;
    var item = ticket.number;
    var reg = /^[0-9]{1}(,[0-9]){1}\|[0-9]{2}(,[0-9]{2}){0,14}$/;
    if(!reg.test(item))
    {
        cb(ec.E2066);
        return;
    }
    var posStrArray = item.split('|');

    //先校验位置是否合法
    var posIntArray = mathUtil.getIntArrayFromStrArray(posStrArray[0].split(","));
    if(!mathUtil.isFromMinToMax(posIntArray))
    {
        cb(ec.E2066);
        return;
    }
    if(posIntArray[0] < 1 || posIntArray[posIntArray.length - 1] > 4)
    {
        cb(ec.E2066);
        return;
    }

    var heIntArray = mathUtil.getIntArrayFromStrArray(posStrArray[1].split(","));
    if(!mathUtil.isFromMinToMax(heIntArray))
    {
        cb(ec.E2066);
        return;
    }
    if(heIntArray[0] < 2 || heIntArray[heIntArray.length - 1] > 16)
    {
        cb(ec.E2066);
        return;
    }

    var count = 0;
    for(var i = 0; i < heIntArray.length; i++)
    {
        count += self.rtHeZhiCountList[heIntArray[i]];
    }
    cb(null, count);
}

/**
 * 任2，跨度
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate0606 = function(order, ticket, cb)
{
    var self = this;
    var item = ticket.number;
    var reg = /^[0-9]{1}(,[0-9]){1}\|[0-9]{1}(,[0-9]{1}){0,7}$/;
    if(!reg.test(item))
    {
        cb(ec.E2066);
        return;
    }
    var posStrArray = item.split('|');
    //先校验位置是否合法
    var posIntArray = mathUtil.getIntArrayFromStrArray(posStrArray[0].split(","));
    if(!mathUtil.isFromMinToMax(posIntArray))
    {
        cb(ec.E2066);
        return;
    }
    if(posIntArray[0] < 1 || posIntArray[posIntArray.length - 1] > 4)
    {
        cb(ec.E2066);
        return;
    }

    var duIntArray = mathUtil.getIntArrayFromStrArray(posStrArray[1].split(","));
    if(!mathUtil.isFromMinToMax(duIntArray))
    {
        cb(ec.E2066);
        return;
    }
    if(duIntArray[0] < 0 || duIntArray[duIntArray.length - 1] > 7)
    {
        cb(ec.E2066);
        return;
    }

    var count = 0;
    for(var i = 0; i < duIntArray.length; i++)
    {
        count += self.kuaDuCountList[duIntArray[i]];
    }
    cb(null, count);
}

/**
 * 任2，全包
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate0609 = function(order, ticket, cb)
{
    var self = this;
    var item = ticket.number;
    var reg = /^[0-9]{1}(,[0-9]){1}$/;
    if(!reg.test(item))
    {
        cb(ec.E2066);
        return;
    }
    var intArray = mathUtil.getIntArrayFromStrArray(item.split(","));
    if(!mathUtil.isFromMinToMaxCanEqual(intArray))
    {
        cb(ec.E2066);
        return;
    }
    if(intArray[0] < 1 || intArray[intArray.length - 1] > 8)
    {
        cb(ec.E2066);
        return;
    }
    var count = 12;
    if(intArray[0] == intArray[1])
    {
        count = 6;
    }
    cb(null, count);
}

/**
 * 任3，单式
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate0700 = function(order, ticket, cb)
{
    var self = this;
    var number = ticket.number;
    var items = number.split(";");
    if(items.length > 5 ){
        cb(ec.E2071);
        return;
    }
    async.each(items, function(item, callback) {
        self.validateRn(order, {number:item}, 3, function(err, count){
            if(err)
            {
                callback(err);
            }
            else
            {
                if(count != 1)
                {
                    callback(ec.E2066);
                }
                else
                {
                    callback();
                }
            }
        });
    }, function(err){
        cb(null, items.length);
    });
}

/**
 * 任3，复式
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate0701 = function(order, ticket, cb)
{
    var self = this;
    self.validateRn(order, ticket, 3, function(err, count){
        if(err)
        {
            cb(err);
        }
        else
        {
            if(count < 2)
            {
                cb(ec.E2066);
            }
            else
            {
                cb(null, count);
            }
        }
    });
}

/**
 * 任3，全包
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate0709 = function(order, ticket, cb)
{
    var self = this;
    var item = ticket.number;
    var reg = /^[0-9]{1}(,[0-9]){2}$/;
    if(!reg.test(item))
    {
        cb(ec.E2066);
        return;
    }
    var intArray = mathUtil.getIntArrayFromStrArray(item.split(","));
    if(!mathUtil.isFromMinToMaxCanEqual(intArray))
    {
        cb(ec.E2066);
        return;
    }
    if(intArray[0] < 1 || intArray[intArray.length - 1] > 8)
    {
        cb(ec.E2066);
        return;
    }
    var count = 0;
    var virtualNum = item + ",9";
    var nt = new NumType(virtualNum);
    if(nt.isZ24())
    {
        count = 24;
    }
    else if(nt.isZ12())
    {
        count = 12;
    }
    else if(nt.isZ4())
    {
        count = 4;
    }
    cb(null, count);
}

/**
 * 任4，单式
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate0800 = function(order, ticket, cb)
{
    var self = this;
    var number = ticket.number;
    var items = number.split(";");
    if(items.length > 5 ){
        cb(ec.E2071);
        return;
    }
    async.each(items, function(item, callback) {
        self.validateRn(order, {number:item}, 4, function(err, count){
            if(err)
            {
                callback(err);
            }
            else
            {
                if(count != 1)
                {
                    callback(ec.E2066);
                }
                else
                {
                    callback();
                }
            }
        });
    }, function(err){
        cb(null, items.length);
    });
}

/**
 * 任4，复式
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate0801 = function(order, ticket, cb)
{
    var self = this;
    self.validateRn(order, ticket, 4, function(err, count){
        if(err)
        {
            cb(err);
        }
        else
        {
            if(count < 2)
            {
                cb(ec.E2066);
            }
            else
            {
                cb(null, count);
            }
        }
    });
}

/**
 * 任选，单式
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate0900 = function(order, ticket, cb)
{
    var self = this;
    var number = ticket.number;
    var items = number.split(";");
    if(items.length > 5 ){
        cb(ec.E2071);
        return;
    }
    async.eachSeries(items, function(item, callback) {
        self.validateRn(order, {number:item}, -1, function(err, count){
            if(err)
            {
                callback(err);
            }
            else
            {
                if(count != 1)
                {
                    callback(ec.E2066);
                }
                else
                {
                    callback();
                }
            }
        });
    }, function(err){
        cb(err, items.length);
    });
}

/**
 * 任选，复式
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate0901 = function(order, ticket, cb)
{
    var self = this;
    self.validateRn(order, ticket, -1, function(err, count){
        if(err)
        {
            cb(err);
        }
        else
        {
            if(count < 2)
            {
                cb(ec.E2066);
            }
            else
            {
                cb(null, count);
            }
        }
    });
}

/**
 * 任选，组合
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate0902 = function(order, ticket, cb)
{
    var self = this;
    var item = ticket.number;
    var posLenAray = [];
    var posStrArray = item.split("|");
    var rn = 0;
    for(var posKey in posStrArray)
    {
        if(posStrArray[posKey] != "_")
        {
            rn++;
            var intArray = mathUtil.getIntArrayFromStrArray(posStrArray[posKey].split(","));
            if(!mathUtil.isFromMinToMax(intArray))
            {
                cb(ec.E2066);
                return;
            }
            if(intArray[0] < 1 || intArray[intArray.length - 1] > 8)
            {
                cb(ec.E2066);
                return;
            }
            posLenAray[posLenAray.length] = intArray.length;
        }
    }
    var count = 0;
    for(var i = 1; i < rn + 1; i++)
    {
        var dc = mathUtil.getDetailC(posLenAray.length, i);
        count += self.getRCountByDc(posLenAray, dc, i);
    }
    log.info("任选，组合---------------------------");
    log.info(count);
    cb(null, count);
}

Validate.prototype.validateRn = function(order, ticket, n, cb)
{
    var self = this;
    var item = ticket.number;
    log.info(item);
    var reg = /^([0-9,]{1,}|_){1}(\|([0-9,]{1,}|_)){3}$/;
    if(!reg.test(item))
    {
        cb(ec.E2066);
        return;
    }
    var posLenAray = [];
    var posStrArray = item.split("|");
    var rn = 0;
    for(var posKey in posStrArray)
    {

        if(posStrArray[posKey] != "_")
        {
            rn++;
            var intArray = mathUtil.getIntArrayFromStrArray(posStrArray[posKey].split(","));
            if(!mathUtil.isFromMinToMax(intArray))
            {
                cb(ec.E2066);
                return;
            }
            if(intArray[0] < 1 || intArray[intArray.length - 1] > 8)
            {
                cb(ec.E2066);
                return;
            }
            posLenAray[posLenAray.length] = intArray.length;
        }
    }
    if(n < 0)
    {
        n = rn;
    }
    var dc = mathUtil.getDetailC(posLenAray.length, n);
    var count = self.getRCountByDc(posLenAray, dc, n);
    cb(null, count);
}

/**
 * 获得任选号码注数，
 * @param lenAray   号码的长度数组
 * @param dc    记录集序号详情
 * @param n     任n
 * @returns {number}
 */
Validate.prototype.getRCountByDc = function(lenAray, dc, n)
{
    var self = this;
    var count = 0;
    for(var i = 0; i < dc.length; i++)
    {
        var set = dc[i];
        var setCount = 1;
        for(var j = 0; j < n; j++)
        {
            setCount = setCount*lenAray[set[j]];
        }
        count += setCount;
    }
    return count;
}

module.exports = new Validate();