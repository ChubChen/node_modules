var async = require('async');

var config = require('mcp_config');
var ec = config.ec;
var game = config.game;

var esut = require('easy_util');
var log = esut.log;

var util = require('mcp_util');
var mathUtil = util.mathUtil;

var Validate = function(){};

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
 * 大乐透单式
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate0000 = function(order, ticket, cb){
    var self = this;
    var number = ticket.number;
    var items = number.split(";");
    for(var key in items)
    {
        var item = items[key];
        log.info(item);
        var reg = /^\d{2}(,\d{2}){4}\|\d{2},\d{2}$/;
        if(!reg.test(item))
        {
            cb(ec.E2066);
            log.info("正则表达式校验错误");
            return;
        }
        var intRedArray = mathUtil.getIntArrayFromStrArray(item.split("|")[0].split(","));
        var intBlueArray = mathUtil.getIntArrayFromStrArray(item.split("|")[1].split(","));
        if(!mathUtil.isFromMinToMax(intRedArray))
        {
            cb(ec.E2066);
            return;
        }
        if(!mathUtil.isMinAndMaxBetween(intRedArray, 0, 35)){
            cb(ec.E2066);
            log.info("红球数值范围错误");
            return;
        }
        if(!mathUtil.isFromMinToMax(intBlueArray))
        {
            cb(ec.E2066);
            return;
        }
        if(!mathUtil.isMinAndMaxBetween(intBlueArray, 0, 12)){
            cb(ec.E2066);
            log.info("篮球数值范围错误");
            return;
        }
    }
    if(items.length > 5 ){
        cb(ec.E2071);
        log.info("篮球数值范围错误");
        return;
    }
    cb(null, items.length);
}


/**
 * 大乐透复式
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate0001 = function(order, ticket, cb){
    var self = this;
    var number = ticket.number;
    var reg = /^\d{2}(,\d{2}){4,34}\|\d{2}(,\d{2}){1,11}$/;
    if(!reg.test(number)){
        cb(ec.E2066);
        return;
    }
    var intRedArray = mathUtil.getIntArrayFromStrArray(number.split("|")[0].split(","));
    var intBlueArray = mathUtil.getIntArrayFromStrArray(number.split("|")[1].split(","));
    if(!mathUtil.isFromMinToMax(intRedArray))
    {
        cb(ec.E2066);
        return;
    }
    if(!mathUtil.isMinAndMaxBetween(intRedArray, 0, 35)){
        cb(ec.E2066);
        log.info("红球数值范围错误");
        return;
    }
    if(!mathUtil.isFromMinToMax(intBlueArray))
    {
        cb(ec.E2066);
        return;
    }
    if(!mathUtil.isMinAndMaxBetween(intBlueArray, 0, 12)){
        cb(ec.E2066);
        log.info("篮球数值范围错误");
        return;
    }
    var redLength = intRedArray.length;
    var blueLength = intBlueArray.length;
    var len = mathUtil.getC(redLength, 5) * mathUtil.getC(blueLength, 2);
    cb(null, len);
}

/**
 * 大乐透胆拖
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate0002 = function(order, ticket, cb){
    var self = this;
    var number = ticket.number;
    var numArray = number.split('$');
    if(numArray < 2 || numArray > 3){
        cb(ec.E2066);
        log.info("不包含$,或者包含$过多,不是胆脱投注");
        return;
    }
    var count = 0;
    //只有前胆或者后胆
    if( numArray.length == 2){
        log.info("houdan ________");
         //后胆
        if(numArray[0].indexOf('|') > -1){
            var reg = /^\d{2}(,\d{2}){4,34}\|\d{2}$/;
            var reg2 =/^\d{2}(,\d{2}){1,10}$/;
            if(!(reg.test(numArray[0]) && reg2.test(numArray[1]) )){
                cb(ec.E2066);
                log.info("后胆$前格式不正确");
                return
            }
            var fuhaoQian = numArray[0].split('|');
            var redArray = mathUtil.getIntArrayFromStrArray(fuhaoQian[0].split(','));
            var blueArray = mathUtil.getIntArrayFromStrArray(numArray[1].split(','));
            var houdan = mathUtil.getIntArrayFromStrArray(fuhaoQian[1].split(','));
            if(!mathUtil.isFromMinToMax(redArray)){
                cb(ec.E2066);
                return
            }
            if(!mathUtil.isMinAndMaxBetween(redArray, 0 , 35)){
                cb(ec.E2066);
                return
            }
            if(!mathUtil.isMinAndMaxBetween(houdan, 0 , 12)){
                cb(ec.E2066);
                return
            }
            if(!mathUtil.isFromMinToMax(blueArray)){
                cb(ec.E2066);
                return
            }
            if(!mathUtil.isMinAndMaxBetween(blueArray, 0, 12)){
                cb(ec.E2066);
                return
            }
            if( mathUtil.getHitCount(blueArray, houdan) > 0){
                cb(ec.E2066);
                return
            }
            count = mathUtil.getC(redArray.length, 5)*mathUtil.getC(blueArray.length, 1);
        }else{ //前胆
            var reg = /^\d{2}(,\d{2}){0,34}\|\d{2}(,\d{2}){1,11}$/;
            var reg2 = /^\d{2}(,\d{2}){0,3}$/;
            if(!(reg.test(numArray[1]) && reg2.test(numArray[0]) )){
                cb(ec.E2066);
                log.info("后胆$前格式不正确");
                return
            }
            var fuhaoQian = numArray[1].split('|');
            var redTuo = mathUtil.getIntArrayFromStrArray(fuhaoQian[0].split(','));
            var blueArray = mathUtil.getIntArrayFromStrArray(fuhaoQian[1].split(','));
            var redDan = mathUtil.getIntArrayFromStrArray(numArray[0].split(','));
            if(!(mathUtil.isFromMinToMax(redDan) && mathUtil.isFromMinToMax(redTuo))){
                cb(ec.E2066);
                return
            }
            if(!(mathUtil.isMinAndMaxBetween(redTuo, 0 , 35) && mathUtil.isMinAndMaxBetween(redDan, 0, 35))){
                cb(ec.E2066);
                return
            }
            if(!mathUtil.isFromMinToMax(blueArray)){
                cb(ec.E2066);
                return
            }
            if(!mathUtil.isMinAndMaxBetween(blueArray, 0, 12)){
                cb(ec.E2066);
                return
            }
            if(mathUtil.getHitCount(redDan,redTuo) > 0){
                cb(ec.E2066);
                log.info("胆码拖码有重复");
                return
            }
            count = mathUtil.getC(blueArray.length, 2)*mathUtil.getC(redTuo.length, 5 - redDan.length);
        }
    }else{
        var reg = /^\d{2}(,\d{2}){0,3}\$\d{2}(,\d{2}){0,34}\|\d{2}\$\d{2}(,\d{2}){1,11}$/;
        if(!reg.test(number)){
            cb(ec.E2066);
            return;
        }
        var redDan = mathUtil.getIntArrayFromStrArray(numArray[0].split(','));
        var redTuo = mathUtil.getIntArrayFromStrArray(numArray[1].split('|')[0].split(','));
        var blueDan = mathUtil.getIntArrayFromStrArray(numArray[1].split('|')[1].split(','));
        var blueTuo = mathUtil.getIntArrayFromStrArray(numArray[2].split(','));
        if(! (mathUtil.isFromMinToMax(redDan) && mathUtil.isFromMinToMax(redTuo))){
            cb(ec.E2066);
            return;
        }
        if(! (mathUtil.isMinAndMaxBetween(redDan, 0 ,35) && mathUtil.isFromMinToMax(redTuo))){
            cb(ec.E2066);
            return;
        }
        if(! (mathUtil.isFromMinToMax(blueDan) && mathUtil.isFromMinToMax(blueTuo))){
            cb(ec.E2066);
            return;
        }
        if(! (mathUtil.isFromMinToMax(blueDan) && mathUtil.isFromMinToMax(blueTuo))){
            cb(ec.E2066);
            return;
        }
        if(mathUtil.getHitCount(redDan,redTuo) > 0 || mathUtil.getHitCount(blueDan,blueTuo) > 0){
            cb(ec.E2066);
            log.info("拖码胆码不能重复");
            return;
        }
        count = mathUtil.getC(redTuo.length, 5 - redDan.length)*mathUtil.getC(blueTuo.length, 2 - blueDan.length)
    }
    if(count < 1){
        cb(ec.E2066);
        log.info("注数计算错误");
        return;
    }
    cb(null, count);
}

/**
 * 大乐透追加单式
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate0500 = function(order, ticket, cb){
    var self = this;
    var number = ticket.number;
    var items = number.split(";");
    for(var key in items)
    {
        var item = items[key];
        log.info(item);
        var reg = /^\d{2}(,\d{2}){4}\|\d{2},\d{2}$/;
        if(!reg.test(item))
        {
            cb(ec.E2066);
            log.info("正则表达式校验错误");
            return;
        }
        var intRedArray = mathUtil.getIntArrayFromStrArray(item.split("|")[0].split(","));
        var intBlueArray = mathUtil.getIntArrayFromStrArray(item.split("|")[1].split(","));
        if(!mathUtil.isFromMinToMax(intRedArray))
        {
            cb(ec.E2066);
            return;
        }
        if(!mathUtil.isMinAndMaxBetween(intRedArray, 0, 35)){
            cb(ec.E2066);
            log.info("红球数值范围错误");
            return;
        }
        if(!mathUtil.isFromMinToMax(intBlueArray))
        {
            cb(ec.E2066);
            return;
        }
        if(!mathUtil.isMinAndMaxBetween(intBlueArray, 0, 12)){
            cb(ec.E2066);
            log.info("篮球数值范围错误");
            return;
        }
    }
    if(items.length > 5 ){
        cb(ec.E2071);
        log.info("篮球数值范围错误");
        return;
    }
    cb(null, items.length);
}
/**
 * 大乐透追加复式
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate0501 = function(order, ticket, cb){
    var self = this;
    var number = ticket.number;
    var reg = /^\d{2}(,\d{2}){4,34}\|\d{2}(,\d{2}){1,11}$/;
    if(!reg.test(number)){
        cb(ec.E2066);
        return;
    }
    var intRedArray = mathUtil.getIntArrayFromStrArray(number.split("|")[0].split(","));
    var intBlueArray = mathUtil.getIntArrayFromStrArray(number.split("|")[1].split(","));
    if(!mathUtil.isFromMinToMax(intRedArray))
    {
        cb(ec.E2066);
        return;
    }
    if(!mathUtil.isMinAndMaxBetween(intRedArray, 0, 35)){
        cb(ec.E2066);
        log.info("红球数值范围错误");
        return;
    }
    if(!mathUtil.isFromMinToMax(intBlueArray))
    {
        cb(ec.E2066);
        return;
    }
    if(!mathUtil.isMinAndMaxBetween(intBlueArray, 0, 12)){
        cb(ec.E2066);
        log.info("篮球数值范围错误");
        return;
    }
    var redLength = intRedArray.length;
    var blueLength = intBlueArray.length;
    var len = mathUtil.getC(redLength, 5) * mathUtil.getC(blueLength, 2);
    cb(null, len);
}

/**
 * 大乐透追加胆拖
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate0502 = function(order, ticket, cb){
    var self = this;
    var number = ticket.number;
    var numArray = number.split('$');
    if(numArray < 2 || numArray > 3){
        cb(ec.E2066);
        log.info("不包含$,或者包含$过多,不是胆脱投注");
        return;
    }
    var count = 0;
    //只有前胆或者后胆
    if( numArray.length == 2){
        //后胆
        if(numArray[0].indexOf('|') > -1){
            var reg = /^\d{2}(,\d{2}){4,34}\|\d{2}$/;
            var reg2 =/^\d{2}(,\d{2}){1,10}$/;
            if(!(reg.test(numArray[0]) && reg2.test(numArray[1]) )){
                cb(ec.E2066);
                log.info("后胆$前格式不正确");
                return
            }
            var fuhaoQian = numArray[0].split('|');
            var redArray = mathUtil.getIntArrayFromStrArray(fuhaoQian[0].split(','));
            var blueArray = mathUtil.getIntArrayFromStrArray(numArray[1].split(','));
            var houdan = mathUtil.getIntArrayFromStrArray(fuhaoQian[1].split(','));
            if(!mathUtil.isFromMinToMax(redArray)){
                cb(ec.E2066);
                return
            }
            if(!mathUtil.isMinAndMaxBetween(redArray, 0 , 35)){
                cb(ec.E2066);
                return
            }
            if(!mathUtil.isMinAndMaxBetween(houdan, 0 , 12)){
                cb(ec.E2066);
                return
            }
            if(!mathUtil.isFromMinToMax(blueArray)){
                cb(ec.E2066);
                return
            }
            if(!mathUtil.isMinAndMaxBetween(blueArray, 0, 12)){
                cb(ec.E2066);
                return
            }
            if(mathUtil.getHitCount(blueArray, houdan) > 0 ){
                cb(ec.E2066);
                return
            }
            count = mathUtil.getC(redArray.length, 5)*mathUtil.getC(blueArray.length, 1);
        }else{ //前胆
            var reg = /^\d{2}(,\d{2}){0,34}\|\d{2}(,\d{2}){1,11}$/;
            var reg2 = /^\d{2}(,\d{2}){0,3}$/;
            if(!(reg.test(numArray[1]) && reg2.test(numArray[0]) )){
                cb(ec.E2066);
                log.info("后胆$前格式不正确");
                return
            }
            var fuhaoQian = numArray[1].split('|');
            var redTuo = mathUtil.getIntArrayFromStrArray(fuhaoQian[0].split(','));
            var blueArray = mathUtil.getIntArrayFromStrArray(fuhaoQian[1].split(','));
            var redDan = mathUtil.getIntArrayFromStrArray(numArray[0].split(','));
            if(!(mathUtil.isFromMinToMax(redDan) && mathUtil.isFromMinToMax(redTuo))){
                cb(ec.E2066);
                return
            }
            if(!(mathUtil.isMinAndMaxBetween(redTuo, 0 , 35) && mathUtil.isMinAndMaxBetween(redDan, 0, 35))){
                cb(ec.E2066);
                return
            }
            if(!mathUtil.isFromMinToMax(blueArray)){
                cb(ec.E2066);
                return
            }
            if(!mathUtil.isMinAndMaxBetween(blueArray, 0, 12)){
                cb(ec.E2066);
                return
            }
            if(mathUtil.getHitCount(redDan,redTuo) > 0){
                cb(ec.E2066);
                log.info("胆码拖码有重复");
                return
            }
            count = mathUtil.getC(blueArray.length, 2)*mathUtil.getC(redTuo.length, 5 - redDan.length);
        }
    }else{
        var reg = /^\d{2}(,\d{2}){0,3}\$\d{2}(,\d{2}){0,34}\|\d{2}\$\d{2}(,\d{2}){1,11}$/;
        if(!reg.test(number)){
            cb(ec.E2066);
            return;
        }
        var redDan = mathUtil.getIntArrayFromStrArray(numArray[0].split(','));
        var redTuo = mathUtil.getIntArrayFromStrArray(numArray[1].split('|')[0].split(','));
        var blueDan = mathUtil.getIntArrayFromStrArray(numArray[1].split('|')[1].split(','));
        var blueTuo = mathUtil.getIntArrayFromStrArray(numArray[2].split(','));
        if(! (mathUtil.isFromMinToMax(redDan) && mathUtil.isFromMinToMax(redTuo))){
            cb(ec.E2066);
            return;
        }
        if(! (mathUtil.isMinAndMaxBetween(redDan, 0 ,35) && mathUtil.isFromMinToMax(redTuo))){
            cb(ec.E2066);
            return;
        }
        if(! (mathUtil.isFromMinToMax(blueDan) && mathUtil.isFromMinToMax(blueTuo))){
            cb(ec.E2066);
            return;
        }
        if(! (mathUtil.isFromMinToMax(blueDan) && mathUtil.isFromMinToMax(blueTuo))){
            cb(ec.E2066);
            return;
        }
        if(mathUtil.getHitCount(redDan,redTuo) > 0 || mathUtil.getHitCount(blueDan,blueTuo) > 0){
            cb(ec.E2066);
            log.info("拖码胆码不能重复");
            return;
        }
        count = mathUtil.getC(redTuo.length, 5 - redDan.length)*mathUtil.getC(blueTuo.length, 2 - blueDan.length)
    }
    if(count < 1){
        cb(ec.E2066);
        log.info("注数计算错误");
        return;
    }
    cb(null, count);
}

module.exports = new Validate();