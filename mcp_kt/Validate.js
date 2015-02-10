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
 * 三不同 单选
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate0100 = function(order, ticket, cb)
{
    var self = this;
    var number = ticket.number;
    var items = number.split(";");
    for(var i = 0 ; i < items.length; i++){
        var reg = /^\d(,\d){2}$/;
        if(!reg.test(items[i]))
        {
            cb(ec.E2066);
            return;
        }
        var intArray = mathUtil.getIntArrayFromStrArray(items[i].split(','));
        if(!mathUtil.isFromMinToMax(intArray)){
            cb(ec.E2066);
            return;
        }
        if(!mathUtil.isMinAndMaxBetween(intArray,1, 6)){
            cb(ec.E2066);
            return;
        }
    }
    if(items.length >5){
        cb(ec.E2071);
        return;
    }
    cb(null, items.length);
}

/**
 * 二同单选
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate0200 = function(order, ticket, cb)
{
    var self = this;
    var number = ticket.number;
    var items = number.split(";");
    var array = [112,113,114,115,116,122,223,224,225,226,133,233,334,335,336,144,244,344,445,446,155,255,355,455,556,166,266,366,466,566];
    var count = 0;
    for(var i = 0 ; i < items.length; i++){
        var reg = /^\d(,\d){2}$/;
        if(!reg.test(items[i]))
        {
            cb(ec.E2066);
            return;
        }
        var intArray = mathUtil.getIntArrayFromStrArray(items[i].split(','));
        if(!mathUtil.isFromMinToMaxCanEqual(intArray)){
            cb(ec.E2066);
            return;
        }
        mathUtil.selectSort(intArray);
        var temp = intArray[0]*100 + intArray[1]*10 + intArray[2];
        for(var j = 0; j < array.length; j++ ){
            if(temp == array[j]){
                count ++;
                break;
            }
        }
    }
    if(count != items.length){
        cb(ec.E2066);
        return;
    }
    if(items.length >5){
        cb(ec.E2071);
        return;
    }
    cb(null, items.length);
}


/**
 * 三同单选
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate0300 = function(order, ticket, cb)
{
    var self = this;
    var number = ticket.number;
    var items = number.split(";");
    var array = [111,222,333,444,555,666];
    var count = 0;
    for(var i = 0 ; i < items.length; i++){
        var reg = /^\d(,\d){2}$/;
        if(!reg.test(items[i]))
        {
            cb(ec.E2066);
            return;
        }
        var intArray = mathUtil.getIntArrayFromStrArray(items[i].split(','));
        var temp = intArray[0]*100 + intArray[1]*10 + intArray[2];
        for(var j = 0; j < array.length; j++ ){
            if(temp == array[j]){
                count ++;
                break;
            }
        }
    }
    if(count != items.length){
        cb(ec.E2066);
        return;
    }
    if(items.length >5){
        cb(ec.E2071);
        return;
    }
    cb(null, items.length);
}

/**
 * 合值
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate0401 = function(order, ticket, cb)
{
    var self = this;
    var number = ticket.number;
    var items = number.split(",");
    for(var i = 0 ; i < items.length; i++){
        var reg = /^\d{1,2}$/;
        if(!reg.test(items[i]))
        {
            cb(ec.E2066);
            return;
        }
        var value = parseInt(items[i]);
        if(value < 4 || value> 17 ) {
            cb(ec.E2066);
            return;
        }
    }
    if(!mathUtil.isFromMinToMax(mathUtil.getIntArrayFromStrArray(items))){
        cb(ec.E2066);
        return;
    }
    cb(null, items.length);
}


/**
 * 二不同
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate0501 = function(order, ticket, cb)
{
    var self = this;
    var number = ticket.number;
    var items = number.split(";");
    var array = [12,13,14,15,16,23,24,25,26,34,35,36,45,46,56];
    var count = 0;
    for(var i = 0 ; i < items.length; i++){
        var reg = /^\d{2}$/;
        if(!reg.test(items[i]))
        {
            cb(ec.E2066);
            return;
        }
        var value = parseInt(items[i]);
        for(var j = 0; j < array.length; j++){
            if(array[j] == value){
                count++
                break;
            }
        }
    }
    if(count != items.length){
        cb(ec.E2066);
        return;
    }
    if(items.length >5){
        cb(ec.E2071);
        return;
    }
    cb(null, items.length);
}

/**
 * 二同
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate0601 = function(order, ticket, cb)
{
    var self = this;
    var number = ticket.number;
    var items = number.split(";");
    var array = [11,22,33,44,55,66];
    var count = 0;
    for(var i = 0 ; i < items.length; i++){
        var reg = /^\d{2}$/;
        if(!reg.test(items[i]))
        {
            cb(ec.E2066);
            return;
        }
        var value = parseInt(items[i]);
        for(var j = 0; j < array.length; j++){
            if(array[j] == value){
                count++
                break;
            }
        }
    }
    if(count != items.length){
        cb(ec.E2066);
        return;
    }
    cb(null, items.length);
}

/**
 * 三同通选
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate0700 = function(order, ticket, cb)
{
    var self = this;
    var number = ticket.number;
    if(number != '111,222,333,444,555,666'){
        cb(ec.E2066);
        return;
    }
    cb(null, 1);
}

/**
 * 三连号通选
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate0800 = function(order, ticket, cb)
{
    var self = this;
    var number = ticket.number;
    if(number != '123,234,345,456'){
        cb(ec.E2066);
        return;
    }
    cb(null, 1);
}

module.exports = new Validate();