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
    self.zxHeZhiList= new Array(0,0,0,1,1,2,2,3,3,4,4,5,5,5,4,4,3,3,2,2,1,1);
    self.zxKuaDuList = new Array(0,10,9,8,7,6,5,4,3,2,1);
    self.qszxHeZhiList = new Array(0, 0, 0, 0, 0, 0, 1, 1, 2, 3, 4, 5, 7, 8, 10, 11, 12, 12, 13, 12, 12, 11, 10, 8, 7, 5, 4, 3, 2, 1, 1);
    self.qszxKuaDuList = new Array(0, 0, 9, 16, 21, 24, 25, 24, 21, 16, 9);
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
 * 11选5 任选一单式
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate2100 = function(order, ticket, cb){
    var self = this;
    var number = ticket.number;
    var iterms = number.split(';');
    for(var i = 0 ; i < iterms.length; i++){
        var reg = /^\d{2}$/;
        if(!reg.test(iterms[i])){
            log.info("正则表达式校验不通过");
            cb(ec.E2066);
            return;
        }
        var intArray = mathUtil.getIntArrayFromStrArray(number.split(','));
        if(!mathUtil.isFromMinToMax(intArray)){
            cb(ec.E2066);
            return;
        }
        if(!mathUtil.isMinAndMaxBetween(intArray, 1 ,11)){
            cb(ec.E2066);
            return;
        }

    }
    if(iterms.length >5){
        cb(ec.E2071);
        return;
    }
    cb(null, iterms.length);
}
/**
 * 11选5 任选一复式
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate2101 = function(order, ticket, cb){
    var self = this;
    var number = ticket.number;
    var reg = /^\d{2}(,\d{2}){1,10}$/;
    if(!reg.test(number)){
        log.info("正则表达式校验不通过");
        cb(ec.E2066);
        return;
    }
    var intArray = mathUtil.getIntArrayFromStrArray(number.split(','));
    if(!mathUtil.isFromMinToMax(intArray)){
        cb(ec.E2066);
        return;
    }
    if(!mathUtil.isMinAndMaxBetween(intArray, 1 ,11)){
        cb(ec.E2066);
        return;
    }
    var count = mathUtil.getC(intArray.length , 1);
    if(count <= 1){
        cb(ec.E2066);
        return;
    }
    cb(null, count);
}

/**
 * 11选5 任选二单式
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate2200 = function(order, ticket, cb){
    var self = this;
    var number = ticket.number;
    var items = number.split(";");
    for (var key in items) {
        var item = items[key];
        var reg = /^\d{2}(,\d{2})$/;
        if (!reg.test(item)) {
            log.info("正则表达式校验不通过");
            cb(ec.E2066);
            return;
        }
        var intArray = mathUtil.getIntArrayFromStrArray(item.split(','));
        if (!mathUtil.isFromMinToMax(intArray)) {
            cb(ec.E2066);
            return;
        }
        if (!mathUtil.isMinAndMaxBetween(intArray, 1, 11)) {
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
 * 11选5 任选二复式
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate2201 = function(order, ticket, cb){
    var self = this;
    var number = ticket.number;
    var reg = /^\d{2}(,\d{2}){2,10}$/;
    if (!reg.test(number)) {
        log.info("正则表达式校验不通过");
        cb(ec.E2066);
        return;
    }
    var intArray = mathUtil.getIntArrayFromStrArray(number.split(','));
    if (!mathUtil.isFromMinToMax(intArray)) {
        cb(ec.E2066);
        return;
    }
    if (!mathUtil.isMinAndMaxBetween(intArray, 1, 11)) {
        cb(ec.E2066);
        return;
    }
    var count = mathUtil.getC(intArray.length, 2);
    if(count <= 1){
        cb(ec.E2066);
        return;
    }
    cb(null, count);
}


/**
 * 11选5 任选二胆拖
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate2202 = function(order, ticket, cb){
    var self = this;
    var number = ticket.number;
    var reg = /^\d{2}\$\d{2}(,\d{2}){1,9}$/;
    if (!reg.test(number)) {
        log.info("正则表达式校验不通过");
        cb(ec.E2066);
        return;
    }
    var numberArray = number.split('$');
    var danArray = mathUtil.getIntArrayFromStrArray(numberArray[0].split(','));
    var intArray = mathUtil.getIntArrayFromStrArray(numberArray[1].split(','));
    if (!mathUtil.isFromMinToMax(intArray)) {
        cb(ec.E2066);
        return;
    }
    if (!mathUtil.isFromMinToMax(danArray)) {
        cb(ec.E2066);
        return;
    }
    if (!mathUtil.isMinAndMaxBetween(intArray, 1, 11)) {
        cb(ec.E2066);
        return;
    }
    if(!mathUtil.isMinAndMaxBetween(danArray, 1, 11) ){
        cb(ec.E2066);
        return;
    }
    if(mathUtil.getHitCount(danArray, intArray) > 0){
        cb(ec.E2066);
        return;
    }
    var count = mathUtil.getC(intArray.length, 1);
    if(count <= 1){
        cb(ec.E2066);
        return;
    }
    cb(null, count);
}

/**
 * 11选5 任选三单式
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate2300 = function(order, ticket, cb){
    var self = this;
    var number = ticket.number;
    var items = number.split(';');
    for (var key in items) {
        var item = items[key];
        var reg = /^\d{2}(,\d{2}){2}$/;
        if (!reg.test(item)) {
            log.info("正则表达式校验不通过");
            cb(ec.E2066);
            return;
        }
        var intArray = mathUtil.getIntArrayFromStrArray(item.split(','));
        if (!mathUtil.isFromMinToMax(intArray)) {
            cb(ec.E2066);
            return;
        }
        if (!mathUtil.isMinAndMaxBetween(intArray, 1, 11)) {
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
 * 11选5 任选三复式
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate2301 = function(order, ticket, cb){
    var self = this;
    var number = ticket.number;
    var reg = /^\d{2}(,\d{2}){3,10}$/;
    if (!reg.test(number)) {
        log.info("正则表达式校验不通过");
        cb(ec.E2066);
        return;
    }
    var intArray = mathUtil.getIntArrayFromStrArray(number.split(','));
    if (!mathUtil.isFromMinToMax(intArray)) {
        cb(ec.E2066);
        return;
    }
    if (!mathUtil.isMinAndMaxBetween(intArray, 1, 11)) {
        cb(ec.E2066);
        return;
    }
    var count = mathUtil.getC(intArray.length, 3);
    if(count <= 1){
        cb(ec.E2066);
        return;
    }
    cb(null, count);
}


/**
 * 11选5 任选三胆拖
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate2302 = function(order, ticket, cb){
    var self = this;
    var number = ticket.number;
    var reg = /^\d{2}(,\d{2})?\$\d{2}(,\d{2}){1,9}$/;
    if (!reg.test(number)) {
        log.info("正则表达式校验不通过");
        cb(ec.E2066);
        return;
    }
    var numberArray = number.split('$');
    var danArray = mathUtil.getIntArrayFromStrArray(numberArray[0].split(','));
    var intArray = mathUtil.getIntArrayFromStrArray(numberArray[1].split(','));
    if (!mathUtil.isFromMinToMax(intArray)) {
        cb(ec.E2066);
        return;
    }
    if (!mathUtil.isMinAndMaxBetween(intArray, 1, 11)) {
        cb(ec.E2066);
        return;
    }
    if(!mathUtil.isMinAndMaxBetween(danArray, 1, 11)){
        cb(ec.E2066);
        return;
    }
    if(mathUtil.getHitCount(danArray , intArray) > 0){
        cb(ec.E2066);
        return;
    }
    var count = mathUtil.getC(intArray.length, 3 - danArray.length);
    if(count <= 1){
        cb(ec.E2066);
        return;
    }
    cb(null, count);
}


/**
 * 11选5 任选四单式
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate2400 = function(order, ticket, cb){
    var self = this;
    var number = ticket.number;
    var items = number.split(';');
    for (var key in items) {
        var item = items[key];
        var reg = /^\d{2}(,\d{2}){3}$/;
        if (!reg.test(item)) {
            log.info("正则表达式校验不通过");
            cb(ec.E2066);
            return;
        }
        var intArray = mathUtil.getIntArrayFromStrArray(item.split(','));
        if (!mathUtil.isFromMinToMax(intArray)) {
            cb(ec.E2066);
            return;
        }
        if (!mathUtil.isMinAndMaxBetween(intArray, 1, 11)) {
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
 * 11选5 任选四复式
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate2401 = function(order, ticket, cb){
    var self = this;
    var number = ticket.number;
    var reg = /^\d{2}(,\d{2}){4,10}$/;
    if (!reg.test(number)) {
        log.info("正则表达式校验不通过");
        cb(ec.E2066);
        return;
    }
    var intArray = mathUtil.getIntArrayFromStrArray(number.split(','));
    if (!mathUtil.isFromMinToMax(intArray)) {
        cb(ec.E2066);
        return;
    }
    if (!mathUtil.isMinAndMaxBetween(intArray, 1, 11)) {
        cb(ec.E2066);
        return;
    }
    var count = mathUtil.getC(intArray.length, 4);
    if(count <= 1){
        cb(ec.E2066);
        return;
    }
    cb(null, count);
}


/**
 * 11选5 任选四胆拖
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate2402 = function(order, ticket, cb){
    var self = this;
    var number = ticket.number;
    var reg = /^\d{2}(,\d{2}){0,2}\$\d{2}(,\d{2}){1,9}$/;
    if (!reg.test(number)) {
        log.info("正则表达式校验不通过");
        cb(ec.E2066);
        return;
    }
    var numberArray = number.split('$');
    var danArray = mathUtil.getIntArrayFromStrArray(numberArray[0].split(','));
    var intArray = mathUtil.getIntArrayFromStrArray(numberArray[1].split(','));
    if (!mathUtil.isFromMinToMax(intArray)) {
        cb(ec.E2066);
        return;
    }if (!mathUtil.isFromMinToMax(danArray)) {
        cb(ec.E2066);
        return;
    }
    if (!mathUtil.isMinAndMaxBetween(danArray, 1, 11)) {
        cb(ec.E2066);
        return;
    }
    if(!mathUtil.isMinAndMaxBetween(intArray,1,11)){
        cb(ec.E2066);
        return;
    }
    if(mathUtil.getHitCount(danArray , intArray) > 0){
        cb(ec.E2066);
        return;
    }
    var count = mathUtil.getC(intArray.length, 4 - danArray.length);
    if(count <= 1){
        cb(ec.E2066);
        return;
    }
    cb(null, count);
}

/**
 * 11选5 任选五单式
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate2500 = function(order, ticket, cb){
    var self = this;
    var number = ticket.number;
    var items = number.split(';');
    for (var key in items) {
        var item = items[key];
        var reg = /^\d{2}(,\d{2}){4}$/;
        if (!reg.test(item)) {
            log.info("正则表达式校验不通过");
            cb(ec.E2066);
            return;
        }
        var intArray = mathUtil.getIntArrayFromStrArray(item.split(','));
        if (!mathUtil.isFromMinToMax(intArray)) {
            cb(ec.E2066);
            return;
        }
        if (!mathUtil.isMinAndMaxBetween(intArray, 1, 11)) {
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
 * 11选5 任选五复式
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate2501 = function(order, ticket, cb){
    var self = this;
    var number = ticket.number;
    var reg = /^\d{2}(,\d{2}){5,10}$/;
    if (!reg.test(number)) {
        log.info("正则表达式校验不通过");
        cb(ec.E2066);
        return;
    }
    var intArray = mathUtil.getIntArrayFromStrArray(number.split(','));
    if (!mathUtil.isFromMinToMax(intArray)) {
        cb(ec.E2066);
        return;
    }
    if (!mathUtil.isMinAndMaxBetween(intArray, 1, 11)) {
        cb(ec.E2066);
        return;
    }
    var count = mathUtil.getC(intArray.length, 5);
    if(count <= 1){
        cb(ec.E2066);
        return;
    }
    cb(null, count);
}


/**
 * 11选5 任选五胆拖
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate2502 = function(order, ticket, cb){
    var self = this;
    var number = ticket.number;
    var reg = /^\d{2}(,\d{2}){0,3}\$\d{2}(,\d{2}){1,9}$/;
    if (!reg.test(number)) {
        log.info("正则表达式校验不通过");
        cb(ec.E2066);
        return;
    }
    var numberArray = number.split('$');
    var danArray = mathUtil.getIntArrayFromStrArray(numberArray[0].split(','));
    var intArray = mathUtil.getIntArrayFromStrArray(numberArray[1].split(','));
    if (!mathUtil.isFromMinToMax(intArray)) {
        cb(ec.E2066);
        return;
    }
    if (!mathUtil.isFromMinToMax(danArray)) {
        cb(ec.E2066);
        return;
    }
    if (!mathUtil.isMinAndMaxBetween(danArray, 1, 11)) {
        cb(ec.E2066);
        return;
    }
    if(!mathUtil.isMinAndMaxBetween(intArray,1,11)){
        cb(ec.E2066);
        return;
    }
    if(mathUtil.getHitCount(danArray , intArray) > 0){
        cb(ec.E2066);
        return;
    }
    var count = mathUtil.getC(intArray.length, 5 - danArray.length);
    if(count <= 1){
        cb(ec.E2066);
        return;
    }
    cb(null, count);
}

/**
 * 11选5 任选六单式
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate2600 = function(order, ticket, cb){
    var self = this;
    var number = ticket.number;
    var items = number.split(';');
    for (var key in items) {
        var item = items[key];
        var reg = /^\d{2}(,\d{2}){5}$/;
        if (!reg.test(item)) {
            log.info("正则表达式校验不通过");
            cb(ec.E2066);
            return;
        }
        var intArray = mathUtil.getIntArrayFromStrArray(item.split(','));
        if (!mathUtil.isFromMinToMax(intArray)) {
            cb(ec.E2066);
            return;
        }
        if (!mathUtil.isMinAndMaxBetween(intArray, 1, 11)) {
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
 * 11选5 任选六复式
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate2601 = function(order, ticket, cb){
    var self = this;
    var number = ticket.number;
    var reg = /^\d{2}(,\d{2}){5,10}$/;
    if (!reg.test(number)) {
        log.info("正则表达式校验不通过");
        cb(ec.E2066);
        return;
    }
    var intArray = mathUtil.getIntArrayFromStrArray(number.split(','));
    if (!mathUtil.isFromMinToMax(intArray)) {
        cb(ec.E2066);
        return;
    }
    if (!mathUtil.isMinAndMaxBetween(intArray, 1, 11)) {
        cb(ec.E2066);
        return;
    }
    var count = mathUtil.getC(intArray.length, 6);
    if(count <= 1){
        cb(ec.E2066);
        return;
    }
    cb(null, count);
}


/**
 * 11选5 任选六胆拖
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate2602 = function(order, ticket, cb){
    var self = this;
    var number = ticket.number;
    var reg = /^\d{2}(,\d{2}){0,4}\$\d{2}(,\d{2}){1,9}$/;
    if (!reg.test(number)) {
        log.info("正则表达式校验不通过");
        cb(ec.E2066);
        return;
    }
    var numberArray = number.split('$');
    var danArray = mathUtil.getIntArrayFromStrArray(numberArray[0].split(','));
    var intArray = mathUtil.getIntArrayFromStrArray(numberArray[1].split(','));
    if (!mathUtil.isFromMinToMax(intArray)) {
        cb(ec.E2066);
        return;
    }
    if (!mathUtil.isFromMinToMax(danArray)) {
        cb(ec.E2066);
        return;
    }
    if (!mathUtil.isMinAndMaxBetween(danArray, 1, 11)) {
        cb(ec.E2066);
        return;
    }
    if(!mathUtil.isMinAndMaxBetween(intArray,1,11)){
        cb(ec.E2066);
        return;
    }
    if(mathUtil.getHitCount(danArray , intArray) > 0){
        cb(ec.E2066);
        return;
    }
    var count = mathUtil.getC(intArray.length, 6 - danArray.length);
    if(count <= 1){
        cb(ec.E2066);
        return;
    }
    cb(null, count);
}

/**
 * 11选5 任选七单式
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate2700 = function(order, ticket, cb){
    var self = this;
    var number = ticket.number;
    var items = number.split(';');
    for (var key in items) {
        var item = items[key];
        var reg = /^\d{2}(,\d{2}){6}$/;
        if (!reg.test(item)) {
            log.info("正则表达式校验不通过");
            cb(ec.E2066);
            return;
        }
        var intArray = mathUtil.getIntArrayFromStrArray(item.split(','));
        if (!mathUtil.isFromMinToMax(intArray)) {
            cb(ec.E2066);
            return;
        }
        if (!mathUtil.isMinAndMaxBetween(intArray, 1, 11)) {
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
 * 11选5 任选六复式
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate2701 = function(order, ticket, cb){
    var self = this;
    var number = ticket.number;
    var reg = /^\d{2}(,\d{2}){6,10}$/;
    if (!reg.test(number)) {
        log.info("正则表达式校验不通过");
        cb(ec.E2066);
        return;
    }
    var intArray = mathUtil.getIntArrayFromStrArray(number.split(','));
    if (!mathUtil.isFromMinToMax(intArray)) {
        cb(ec.E2066);
        return;
    }
    if (!mathUtil.isMinAndMaxBetween(intArray, 1, 11)) {
        cb(ec.E2066);
        return;
    }
    var count = mathUtil.getC(intArray.length, 7);
    if(count <= 1){
        cb(ec.E2066);
        return;
    }
    cb(null, count);
}


/**
 * 11选5 任选七胆拖
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate2702 = function(order, ticket, cb){
    var self = this;
    var number = ticket.number;
    var reg = /^\d{2}(,\d{2}){0,5}\$\d{2}(,\d{2}){1,9}$/;
    if (!reg.test(number)) {
        log.info("正则表达式校验不通过");
        cb(ec.E2066);
        return;
    }
    var numberArray = number.split('$');
    var danArray = mathUtil.getIntArrayFromStrArray(numberArray[0].split(','));
    var intArray = mathUtil.getIntArrayFromStrArray(numberArray[1].split(','));
    if (!mathUtil.isFromMinToMax(intArray)) {
        cb(ec.E2066);
        return;
    }
    if (!mathUtil.isFromMinToMax(danArray)) {
        cb(ec.E2066);
        return;
    }
    if (!mathUtil.isMinAndMaxBetween(intArray, 1, 11)) {
        cb(ec.E2066);
        return;
    }
    if(!mathUtil.isMinAndMaxBetween(intArray,1,11)){
        cb(ec.E2066);
        return;
    }
    if(mathUtil.getHitCount(danArray , intArray) > 0){
        cb(ec.E2066);
        return;
    }
    var count = mathUtil.getC(intArray.length, 7 - danArray.length);
    if(count <= 1){
        cb(ec.E2066);
        return;
    }
    cb(null, count);
}


/**
 * 11选5 任选八单式
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate2800 = function(order, ticket, cb){
    var self = this;
    var number = ticket.number;
    var items = number.split(';');
    for (var key in items) {
        var item = items[key];
        var reg = /^\d{2}(,\d{2}){7}$/;
        if (!reg.test(item)) {
            log.info("正则表达式校验不通过");
            cb(ec.E2066);
            return;
        }
        var intArray = mathUtil.getIntArrayFromStrArray(item.split(','));
        if (!mathUtil.isFromMinToMax(intArray)) {
            cb(ec.E2066);
            return;
        }
        if (!mathUtil.isMinAndMaxBetween(intArray, 1, 11)) {
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
 * 11选5 前二组选单式
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate2900 = function(order, ticket, cb){
    var self = this;
    var number = ticket.number;
    var items = number.split(';');
    for (var key in items) {
        var item = items[key];
        var reg = /^\d{2}(,\d{2})$/;
        if (!reg.test(item)) {
            log.info("正则表达式校验不通过");
            cb(ec.E2066);
            return;
        }
        var intArray = mathUtil.getIntArrayFromStrArray(item.split(','));
        if (!mathUtil.isFromMinToMax(intArray)) {
            cb(ec.E2066);
            return;
        }
        if (!mathUtil.isMinAndMaxBetween(intArray, 1, 11)) {
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
 * 11选5 前二组选复式
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate2901 = function(order, ticket, cb){
    var self = this;
    var number = ticket.number;
    var reg = /^\d{2}(,\d{2}){1,10}$/;
    if (!reg.test(number)) {
        log.info("正则表达式校验不通过");
        cb(ec.E2066);
        return;
    }
    var intArray = mathUtil.getIntArrayFromStrArray(number.split(','));
    if (!mathUtil.isFromMinToMax(intArray)) {
        cb(ec.E2066);
        return;
    }
    if (!mathUtil.isMinAndMaxBetween(intArray, 1, 11)) {
        cb(ec.E2066);
        return;
    }
    var count = mathUtil.getC(intArray.length, 2);
    if(count <= 1){
        cb(ec.E2066);
        return;
    }
    cb(null, count);
}


/**
 * 11选5 前二组选胆拖
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate2902 = function(order, ticket, cb){
    var self = this;
    var number = ticket.number;
    var reg = /^\d{2}\$\d{2}(,\d{2}){1,9}$/;
    if (!reg.test(number)) {
        log.info("正则表达式校验不通过");
        cb(ec.E2066);
        return;
    }
    var numberArray = number.split('$');
    var danArray = mathUtil.getIntArrayFromStrArray(numberArray[0].split(','));
    var intArray = mathUtil.getIntArrayFromStrArray(numberArray[1].split(','));
    if (!mathUtil.isFromMinToMax(intArray)) {
        cb(ec.E2066);
        return;
    }
    if (!mathUtil.isFromMinToMax(danArray)) {
        cb(ec.E2066);
        return;
    }
    if (!mathUtil.isMinAndMaxBetween(intArray, 1, 11)) {
        cb(ec.E2066);
        return;
    }
    if(!mathUtil.isMinAndMaxBetween(danArray, 1, 11)){
        cb(ec.E2066);
        return;
    }
    if(mathUtil.getHitCount(intArray, danArray) > 0){
        cb(ec.E2066);
        return;
    }
    var count = mathUtil.getC(intArray.length, 1);
    if(count <= 1){
        cb(ec.E2066);
        return;
    }
    cb(null, count);
}

/**
 * 11选5 前二组选合值
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate2903 = function(order, ticket, cb){
    var self = this;
    var number = ticket.number;
    var reg = /^\d{2}(,\d{2}){0,19}$/;
    if (!reg.test(number)) {
        log.info("正则表达式校验不通过");
        cb(ec.E2066);
        return;
    }
    var intArray = mathUtil.getIntArrayFromStrArray(number.split(','));
    if (!mathUtil.isFromMinToMax(intArray)) {
        cb(ec.E2066);
        return;
    }
    if (!mathUtil.isMinAndMaxBetween(intArray, 3, 21)) {
        cb(ec.E2066);
        return;
    }
    var count = 0;
    for(var key =0 ; key< intArray.length; key++ ){
        count += self.zxHeZhiList[intArray[key]];
    }
    if(count < 1){
        cb(ec.E2066);
        return;
    }
    cb(null, count);
}

/**
 * 11选5 前二组选跨度
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate2906 = function(order, ticket, cb){
    var self = this;
    var number = ticket.number;
    var reg = /^\d{2}(,\d{2}){0,10}$/;
    if (!reg.test(number)) {
        log.info("正则表达式校验不通过");
        cb(ec.E2066);
        return;
    }
    var intArray = mathUtil.getIntArrayFromStrArray(number.split(','));
    if (!mathUtil.isFromMinToMax(intArray)) {
        cb(ec.E2066);
        return;
    }
    if (!mathUtil.isMinAndMaxBetween(intArray, 1, 10)) {
        cb(ec.E2066);
        return;
    }
    var count = 0;
    for(var key =0 ; key< intArray.length; key++ ){
        count += self.zxKuaDuList[intArray[key]];
    }
    if(count < 1){
        cb(ec.E2066);
        return;
    }
    cb(null, count);
}


/**
 * 11选5 前二直选单式
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate3000 = function(order, ticket, cb){
    var self = this;
    var number = ticket.number;
    var items = number.split(';');
    for (var key in items) {
        var item = items[key];
        var reg = /^\d{2}(\|\d{2})$/;
        if (!reg.test(item)) {
            log.info("正则表达式校验不通过");
            cb(ec.E2066);
            return;
        }
        var intArray = mathUtil.getIntArrayFromStrArray(item.split('|'));
        if (!mathUtil.isMinAndMaxBetween(intArray, 1, 11)) {
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
 * 11选5 前二直选复式
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate3001 = function(order, ticket, cb){
    var self = this;
    var number = ticket.number;
    var reg = /^\d{2}(,\d{2}){1,10}$/;
    if (!reg.test(number)) {
        log.info("正则表达式校验不通过");
        cb(ec.E2066);
        return;
    }
    var intArray = mathUtil.getIntArrayFromStrArray(number.split(','));
    if(!mathUtil.isFromMinToMax(intArray)){
        cb(ec.E2066);
        return;
    }
    if (!mathUtil.isMinAndMaxBetween(intArray, 1, 11)) {
        cb(ec.E2066);
        return;
    }
    var count = mathUtil.getA(intArray.length, 2);
    if(count <= 1){
        cb(ec.E2066);
        return;
    }
    cb(null, count);
}


/**
 * 11选5 前二直选合值
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate3003 = function(order, ticket, cb){
    var self = this;
    var number = ticket.number;
    var reg = /^\d{2}(,\d{2}){0,19}$/;
    if (!reg.test(number)) {
        log.info("正则表达式校验不通过");
        cb(ec.E2066);
        return;
    }
    var intArray = mathUtil.getIntArrayFromStrArray(number.split(','));
    if (!mathUtil.isFromMinToMax(intArray)) {
        cb(ec.E2066);
        return;
    }
    if (!mathUtil.isMinAndMaxBetween(intArray, 3, 21)) {
        cb(ec.E2066);
        return;
    }
    var count = 0;
    for(var key =0 ; key< intArray.length; key++ ){
        count += 2*self.zxHeZhiList[intArray[key]];
    }
    if(count < 1){
        cb(ec.E2066);
        return;
    }
    cb(null, count);
}

/**
 * 11选5 前二组选跨度
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate3006 = function(order, ticket, cb){
    var self = this;
    var number = ticket.number;
    var reg = /^\d{2}(,\d{2}){0,10}$/;
    if (!reg.test(number)) {
        log.info("正则表达式校验不通过");
        cb(ec.E2066);
        return;
    }
    var intArray = mathUtil.getIntArrayFromStrArray(number.split(','));
    if (!mathUtil.isFromMinToMax(intArray)) {
        cb(ec.E2066);
        return;
    }
    if (!mathUtil.isMinAndMaxBetween(intArray, 1, 10)) {
        cb(ec.E2066);
        return;
    }
    var count = 0;
    for(var key =0 ; key< intArray.length; key++ ){
        count += 2*self.zxKuaDuList[intArray[key]];
    }
    if(count < 1){
        cb(ec.E2066);
        return;
    }
    cb(null, count);
}

/**
 * 11选5 前二直选定位
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate3007 = function(order, ticket, cb) {
    var self = this;
    var number = ticket.number;
    var reg = /^\d{2}(,\d{2}){0,10}\|\d{2}(,\d{2}){0,10}$/;
    if(!reg.test(number)){
        log.info("正则表达式校验不通过");
        cb(ec.E2066);
        return;
    }
    var firstArray = mathUtil.getIntArrayFromStrArray(number.split('|')[0].split(','));
    var secondArray = mathUtil.getIntArrayFromStrArray(number.split('|')[1].split(','));
    if(!mathUtil.isFromMinToMax(firstArray)){
        cb(ec.E2066);
        return;
    }
    if(!mathUtil.isFromMinToMax(secondArray)){
        cb(ec.E2066);
        return;
    }
    if(!mathUtil.isMinAndMaxBetween(firstArray, 1, 11)){
        cb(ec.E2066);
        return;
    }
    if(!mathUtil.isMinAndMaxBetween(secondArray, 1, 11)){
        cb(ec.E2066);
        return;
    }
    var chongfuCount = mathUtil.getHitCount(firstArray,secondArray);
    var count = firstArray.length * secondArray.length - chongfuCount;
    if(count < 1){
        cb(ec.E2066);
        return;
    }
    cb(null, count);
}

/**
 * 11选5 前三组选单式
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate3100 = function(order, ticket, cb){
    var self = this;
    var number = ticket.number;
    var items = number.split(';');
    for (var key in items) {
        var item = items[key];
        var reg = /^\d{2}(,\d{2}){2}$/;
        if (!reg.test(item)) {
            log.info("正则表达式校验不通过");
            cb(ec.E2066);
            return;
        }
        var intArray = mathUtil.getIntArrayFromStrArray(item.split(','));
        if (!mathUtil.isFromMinToMax(intArray)) {
            cb(ec.E2066);
            return;
        }
        if (!mathUtil.isMinAndMaxBetween(intArray, 1, 11)) {
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
 * 11选5 前三组选复式
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate3101 = function(order, ticket, cb){
    var self = this;
    var number = ticket.number;
    var reg = /^\d{2}(,\d{2}){2,10}$/;
    if (!reg.test(number)) {
        log.info("正则表达式校验不通过");
        cb(ec.E2066);
        return;
    }
    var intArray = mathUtil.getIntArrayFromStrArray(number.split(','));
    if (!mathUtil.isFromMinToMax(intArray)) {
        cb(ec.E2066);
        return;
    }
    if (!mathUtil.isMinAndMaxBetween(intArray, 1, 11)) {
        cb(ec.E2066);
        return;
    }
    var count = mathUtil.getC(intArray.length, 3);
    if(count <= 1){
        cb(ec.E2066);
        return;
    }
    cb(null, count);
}


/**
 * 11选5 前三组选胆拖
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate3102 = function(order, ticket, cb){
    var self = this;
    var number = ticket.number;
    var reg = /^\d{2}(,\d{2}){0,1}\$\d{2}(,\d{2}){1,9}$/;
    if (!reg.test(number)) {
        log.info("正则表达式校验不通过");
        cb(ec.E2066);
        return;
    }
    var numberArray = number.split('$');
    var danArray = mathUtil.getIntArrayFromStrArray(numberArray[0].split(','));
    var tuoArray = mathUtil.getIntArrayFromStrArray(numberArray[1].split(','));
    if (!mathUtil.isFromMinToMax(tuoArray)) {
        cb(ec.E2066);
        return;
    }
    if (!mathUtil.isMinAndMaxBetween(tuoArray, 1, 11)) {
        cb(ec.E2066);
        return;
    }
    if (!mathUtil.isFromMinToMax(danArray)) {
        cb(ec.E2066);
        return;
    }
    if (!mathUtil.isMinAndMaxBetween(danArray, 1, 11)) {
        cb(ec.E2066);
        return;
    }
    if(mathUtil.getHitCount(danArray, tuoArray) > 0){
        cb(ec.E2066);
        return;
    }
    var count = mathUtil.getC(tuoArray.length, 3 - danArray.length);
    if(count <= 1){
        cb(ec.E2066);
        return;
    }
    cb(null, count);
}

/**
 * 11选5 前三组选合值
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate3103 = function(order, ticket, cb){
    var self = this;
    var number = ticket.number;
    var reg = /^\d{2}(,\d{2}){0,24}$/;
    if (!reg.test(number)) {
        log.info("正则表达式校验不通过");
        cb(ec.E2066);
        return;
    }
    var intArray = mathUtil.getIntArrayFromStrArray(number.split(','));
    if (!mathUtil.isFromMinToMax(intArray)) {
        cb(ec.E2066);
        return;
    }
    if (!mathUtil.isMinAndMaxBetween(intArray, 6, 30)) {
        cb(ec.E2066);
        return;
    }
    var count = 0;
    for(var key =0 ; key< intArray.length; key++ ){
        count += self.qszxHeZhiList[intArray[key]];
    }
    if(count < 1){
        cb(ec.E2066);
        return;
    }
    cb(null, count);
}

/**
 * 11选5 前三组选跨度
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate3106 = function(order, ticket, cb){
    var self = this;
    var number = ticket.number;
    var reg = /^\d{2}(,\d{2}){0,10}$/;
    if (!reg.test(number)) {
        log.info("正则表达式校验不通过");
        cb(ec.E2066);
        return;
    }
    var intArray = mathUtil.getIntArrayFromStrArray(number.split(','));
    if (!mathUtil.isFromMinToMax(intArray)) {
        cb(ec.E2066);
        return;
    }
    if (!mathUtil.isMinAndMaxBetween(intArray, 2, 10)) {
        cb(ec.E2066);
        return;
    }
    var count = 0;
    for(var key =0 ; key< intArray.length; key++ ){
        count += self.qszxKuaDuList[intArray[key]];
    }
    if(count < 1){
        cb(ec.E2066);
        return;
    }
    cb(null, count);
}


/**
 * 11选5 前三直选单式
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate3200 = function(order, ticket, cb){
    var self = this;
    var number = ticket.number;
    var items = number.split(';');
    for (var key in items) {
        var item = items[key];
        var reg = /^\d{2}(\|\d{2}){2}$/;
        if (!reg.test(item)) {
            log.info("正则表达式校验不通过");
            cb(ec.E2066);
            return;
        }
        var intArray = mathUtil.getIntArrayFromStrArray(item.split('|'));
        log.error(intArray);
        if (intArray[0] == intArray[1]){
            cb(ec.E2066);
            return;
        }
        if (intArray[1] == intArray[2]){
            cb(ec.E2066);
            return;
        }
        if (intArray[0] == intArray[2]){
            cb(ec.E2066);
            return;
        }
        if (!mathUtil.isMinAndMaxBetween(intArray, 1, 11)) {
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
 * 11选5 前三直选复式
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate3201 = function(order, ticket, cb){
    var self = this;
    var number = ticket.number;
    var reg = /^\d{2}(,\d{2}){3,10}$/;
    if (!reg.test(number)) {
        log.info("正则表达式校验不通过");
        cb(ec.E2066);
        return;
    }
    var intArray = mathUtil.getIntArrayFromStrArray(number.split(','));
    if(!mathUtil.isFromMinToMax(intArray)){
        cb(ec.E2066);
        return;
    }
    if (!mathUtil.isMinAndMaxBetween(intArray, 1, 11)) {
        cb(ec.E2066);
        return;
    }
    var count = mathUtil.getA(intArray.length, 3);
    if(count <= 1){
        cb(ec.E2066);
        return;
    }
    cb(null, count);
}


/**
 * 11选5 前三直选合值
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate3203 = function(order, ticket, cb){
    var self = this;
    var number = ticket.number;
    var reg = /^\d{2}(,\d{2}){0,24}$/;
    if (!reg.test(number)) {
        log.info("正则表达式校验不通过");
        cb(ec.E2066);
        return;
    }
    var intArray = mathUtil.getIntArrayFromStrArray(number.split(','));
    if (!mathUtil.isFromMinToMax(intArray)) {
        cb(ec.E2066);
        return;
    }
    if (!mathUtil.isMinAndMaxBetween(intArray, 6, 30)) {
        cb(ec.E2066);
        return;
    }
    var count = 0;
    for(var key =0 ; key< intArray.length; key++ ){
        count += 6*self.qszxHeZhiList[intArray[key]];
    }
    if(count < 1){
        cb(ec.E2066);
        return;
    }
    cb(null, count);
}

/**
 * 11选5 前三组选跨度
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate3206 = function(order, ticket, cb){
    var self = this;
    var number = ticket.number;
    var reg = /^\d{2}(,\d{2}){0,10}$/;
    if (!reg.test(number)) {
        log.info("正则表达式校验不通过");
        cb(ec.E2066);
        return;
    }
    var intArray = mathUtil.getIntArrayFromStrArray(number.split(','));
    if (!mathUtil.isFromMinToMax(intArray)) {
        cb(ec.E2066);
        return;
    }
    if (!mathUtil.isMinAndMaxBetween(intArray, 2, 10)) {
        cb(ec.E2066);
        return;
    }
    var count = 0;
    for(var key =0 ; key< intArray.length; key++ ){
        count += 6*self.qszxKuaDuList[intArray[key]];
    }
    if(count < 1){
        cb(ec.E2066);
        return;
    }
    cb(null, count);
}

/**
 * 11选5 前三直选定位
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate3207 = function(order, ticket, cb) {
    var self = this;
    var number = ticket.number;
    var reg = /^\d{2}(,\d{2}){0,9}(\|\d{2}(,\d{2}){0,9}){2}$/;
    if(!reg.test(number)){
        log.info("正则表达式校验不通过");
        cb(ec.E2066);
        return;
    }
    var firstArray = mathUtil.getIntArrayFromStrArray(number.split('|')[0].split(','));
    var secondArray = mathUtil.getIntArrayFromStrArray(number.split('|')[1].split(','));
    var threeArray = mathUtil.getIntArrayFromStrArray(number.split('|')[2].split(','));
    if(!mathUtil.isFromMinToMax(firstArray)){
        cb(ec.E2066);
        return;
    }
    if(!mathUtil.isFromMinToMax(secondArray)){
        cb(ec.E2066);
        return;
    }
    if(!mathUtil.isFromMinToMax(threeArray)){
        cb(ec.E2066);
        return;
    }
    if(!mathUtil.isMinAndMaxBetween(firstArray, 1 ,11)){
        cb(ec.E2066);
        return;
    }
    if(!mathUtil.isMinAndMaxBetween(secondArray, 1, 11)){
        cb(ec.E2066);
        return;
    }
    if(!mathUtil.isMinAndMaxBetween(threeArray, 1, 11)){
        cb(ec.E2066);
        return;
    }
    var numArray = new Array();
    numArray[0] = firstArray;
    numArray[1] = secondArray;
    numArray[2] = threeArray;
    var count = firstArray.length * secondArray.length * threeArray.length;
    var allNum = new Array();
    for(var i =0 ; i<count ; i++){
        allNum[i] = new Array();
    }
    //每一层的份数为当层的长度numIArray.length乘以上一层的份数，第一层的份数为第一层的长度
    var splitCount = 1;
    for(var i = 0; i < numArray.length; i++)
    {
        var numIArray = numArray[i];
        splitCount = splitCount*numIArray.length;

        var countPerNum = count/splitCount;
        var index = 0;	//当前要填的索引
        while(index < count)
        {
            for(var j = 0; j < numIArray.length; j++)
            {
                for(var k = 0; k < countPerNum; k++)
                {
                    allNum[index][i] = numIArray[j];
                    index++;
                }
            }
        }
    }
    var dumplicateCount = 0;	//包含重复号码的个数
    for(var i = 0; i < allNum.length; i++)
    {
        if(self.hasDumplicate(allNum[i], 11))
        {
            dumplicateCount++;
        }
    }
    count = count - dumplicateCount;
    if(count < 1){
        cb(ec.E2066);
        return;
    }
    cb(null, count);
}

Validate.prototype.hasDumplicate = function(number, max){
    var countArray = new Array();
    for(var i = 0; i < number.length; i++)
    {
        if(countArray[number[i]] == 1)
        {
            return true;
        }
        countArray[number[i]] = 1;
    }
    return false;
}

module.exports = new Validate();