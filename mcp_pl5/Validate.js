
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
                var gameConfig = game.getInfo(ticket.gameCode, ticket.pType);
                if(gameConfig == undefined || gameConfig == null){
                    cb(ec.E2062);
                    return;
                }
                var price = gameConfig.price;
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
 * 排列五 标准单式
 * @param order
 * @param ticket
 * @param cb
 */

Validate.prototype.validate0000 = function(order, ticket, cb)
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
        if(item.length <=0)
            continue;
        var reg = /^[0-9](\|[0-9]){4}$/;
        if(!reg.test(item))
        {
            cb(ec.E2066);
            return;
        }
    }
    cb(null, items.length);
}


/**
 * 排列三  标准复式
 * @param order
 * @param ticket
 * @param cb
 */

Validate.prototype.validate0001 = function(order, ticket, cb)
{
    var self = this;
    var number = ticket.number;
    var reg = /^[0-9](,[0-9]){0,9}(\|[0-9](,[0-9]){0,9}){4}$/;
    if (!reg.test(number)){
        cb(ec.E2066);
        return;
    }
    var funshiArray  = number.split('|');
    var count = 1;
    for(var i =0 ; i < funshiArray.length ; i++){
        var intArray = funshiArray[i].split(',');
        if(!mathUtil.isFromMinToMax(intArray)){
            cb(ec.E2066);
            return;
        }
        count *= mathUtil.getC(intArray.length, 1);
    }
    if (count == 1){
        cb(ec.E2066);
        return;
    }
    cb(null, count);
}

module.exports = new Validate();
