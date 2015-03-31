var async = require('async');

var jc = require('./build/Release/jc');
var check = jc.check();

var drawNumber = {};

var getDrawNumber = function(matchCode, cb)
{
    if(matchCode == "201503312301")
    {
        cb(null, "53:50");
    }else if(matchCode == "201503312303" ){
        cb(null, "73:80");
    }else if(matchCode == "201503264303" ){
        cb(null, "100:105");
    }else
    {
        cb(null, "*");
    }
}

var start = new Date().getTime();
for(var i = 0; i < 1; i++)
{
    var number = '01|201503312301|1(-2.5)@1.790;01|201503312303|2(+6.5)@1.610';
    var numberArray = number.split(';');
    var matches = [];
    for(var j = 0; j < numberArray.length; j++)
    {
        var matchCode = numberArray[j].split('|')[1];
        matches.push(matchCode);
    }
    async.eachSeries(matches, function(matchCode, callback) {
        if(drawNumber[matchCode] == undefined)
        {
            getDrawNumber(matchCode, function(err, data){
                drawNumber[matchCode] = data;
                check.setDrawNumber({code:matchCode, number:data});
                callback(err);
            });
        }
        else
        {
            callback();
        }
    }, function(err){
        var te = 'count';
        console.log(check[te]({
            number:number,
            bType:'21'
        }));
    });
}
var end = new Date().getTime();
console.log("执行耗时:" + (end - start) + "ms.");

