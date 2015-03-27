var async = require('async');

var config = require('mcp_config');
var ec = config.ec;
var game = config.game;

var esut = require('easy_util');
var log = esut.log;

var util = require('mcp_util');
var mathUtil = util.mathUtil;
var jcUtil = require("./JcUtil.js")


var Validate = function(){
    var self = this;
};


Validate.prototype.validate = function(order, ticket, cb)
{
    var self = this;
    var tickets = order.tickets;
    var name = "validate0000";
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
 * 三不同 单选
 * @param order
 * @param ticket
 * @param cb
 */
Validate.prototype.validate0000 = function(order, ticket, cb)
{
    var split = "\\d{2}(,\\d{2}){0,}\\|\\d{12}\\|\\d{1,}(@\\d{1,}\\.\\d{1,}){0,1}(,\\d{1,}(@\\d{1,}\\.d{1,}){0,1}){0,7}";
    var match = "(\\${0,1}" + split + "(&" + split +"){0,}){1}";
    var reg = new RegExp("^" + match + "(;" + match + "){0,}$");
    if(!reg.test(ticket.number)){
        cb(ec.E2066);
        return;
    }
    var betType = ticket.bType;
    var m = betType.substr(0,1);
    var n = betType.substr(1);
    var number = ticket.number;
    var count = jcUtil.getJcCount(number, m, n );
    if(count < 0){
        cb(ec.E2066);
        return;
    }
    if(count > 10000){
        cb(ec.E2072);
        return;
    }
    cb(null, count);
};

var reg = new RegExp('^\\d{1,}$');
module.exports = new Validate();