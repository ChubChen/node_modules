var util = require('mcp_util');
var arrayInfo = util.arrayInfo;
var mathUtil = util.mathUtil;

var banchMap = require('./BanchMap.js');


var JcUtil = function () {
};

/**
 * 把订单的号码拆分为彩票，不考虑胆和混投同场次选多个玩法。
 * @param number 订单的号码，场次信息之间以分号分割
 * @param neededBalls 需要的场次数，比如用户玩的是4串N，则需要的场次数为4
 * @return
 */
JcUtil.prototype.getJcCount=function(number, m, n){
    var self = this;
    var numberArray = number.split(';');
    var ticketList = new Array();
    var countList = new Array();
    var danArray =  new Array();
    var dantuoCount = 0;
    if(n == 1){
        //记录场次的注数
        for(var i = 0; i< numberArray.length; i++){
            var tempNum = numberArray[i];
            if(tempNum.indexOf('$') == 0){
                dantuoCount ++;
                danArray[i] = i;
            }else{
                danArray[i] = -1;
            }
        }
    }
    var data = mathUtil.getDetailC(numberArray.length , m);
    for(var i = 0; i< data.length; i++){
        var setArray = data[i];
        if(dantuoCount > 0 ){//胆拖玩法
            var hitCount = mathUtil.getHitCount(danArray, setArray);
            if(hitCount == dantuoCount){
                var obj = self.mulitMxn(m, n, setArray, numberArray);
                countList = countList.concat(obj.countArray);
                ticketList = ticketList.concat(obj.countArray);
            }
        }else{//普通玩法
            var obj = self.mulitMxn(m, n, setArray, numberArray );
            countList = countList.concat(obj.countArray);
            ticketList = ticketList.concat(obj.countArray);
        }
    }
    var count = 0;
    for(var k =0  ; k < countList.length ; k++)
    {
        count += countList[k];
    }
    return count;
};

/**
 * 多个m串n，当混投的时候，选择了多个玩法
 * @return
 */
JcUtil.prototype.mulitMxn = function(m, n, setArray, matchArray ){
    var self = this;
    var obj = { "ticketArray": new Array(), "countArray": new Array()};

    var numberArray = new arrayInfo(setArray.length);
    for(var i = 0; i < setArray.length; i++)
    {
        numberArray[i] = matchArray[setArray[i]];
    }
    var playList = new Array();
    //记录玩法的注数列表
    var countArray = new arrayInfo(numberArray.length);
    var playCount = 1;	//记录所有的注数
    for(var i = 0; i < numberArray.length; i++)
    {
        var playTypeArray = numberArray[i].split("&");
        playList.push(playTypeArray);
        countArray[i] = playTypeArray.length;
        playCount = playCount*playTypeArray.length;
    }

    var data = mathUtil.getDetailMultiplier(countArray);

    var termCount = new arrayInfo(data.length, setArray.length);
    var orderList = new Array();
    for(var i = 0; i < playCount; i++)
    {
        var orderString = "";
        var tset = data[i];
        for(var j = 0; j < tset.length; j++)
        {
            if(j > 0)
            {
                orderString += ";";
            }
            var mString = playList[j][tset[j]];
            orderString += mString;
            termCount[i][j] = mString.split(",").length;
        }
        orderList.push(orderString);
    }

    for(var i = 0; i < orderList.length; i++)
    {
        obj.ticketArray.push(orderList[i]);
        obj.countArray.push(self.standardMxn(m, n, setArray, termCount[i]));
    }
    return obj
};
/**
 * m串n
 * @return
 */
JcUtil.prototype.standardMxn = function(m, n, set, termCount){
    var self = this;
    var mxn = m.toString()+ n.toString();
    var str = banchMap.getInfoById(mxn); //mxn为串关描述符号。5串26
    var total = 0;
    for (var i = 0; i < str.length; i++) {
        if (str.charAt(i) == '1') {
            var ct = self.mX1(m, i+1, set, termCount);
            total = total + ct;
        }
    }
    return total;
};

/**
 * 标准的多场串1算法。
 * @param m 票的总关数
 * @param n 要通过的关数
 * @param set 票的所有场次在订单所有场次中的序号列表
 * @param termCount 订单所有场次的注数列表
 * @return
 */
JcUtil.prototype.mX1=function(m,  n, setArray, termCount){
    var data = mathUtil.getDetailC(m, n);
    var count = 0;
    for(var i = 0; i < data.length; i++)
    {
        var record = data[i];
        var tCount = 1;
        for(var j = 0; j < record.length; j++)
        {
            tCount *= termCount[record[j]];
        }
        count += tCount;
    }
    return count;
};

//var betInfo="02|201312172001|1@1.0;02|201312172006|1@1.4,2,3;02|201312172006|1@1.5";
//console.log(new JcUtil().getJcCount(betInfo, 2, 1));
module.exports = new JcUtil();