var async = require('async');

var jc = require('./build/Release/jc');
var check = jc.check();

var drawNumber = {};

var getDrawNumber = function(matchCode, cb)
{
    if(matchCode == "201503264301")
    {
        cb(null, "105:120");
    }else if(matchCode == "201503264302" ){
        cb(null, "100:210");
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
    var number = '02|201503264301|1@2.50,2@2.50;02|201503264302|2@2.00;03|201503264303|11@4.00';
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
            bType:'23'
        }));
    });
}
var end = new Date().getTime();
console.log("执行耗时:" + (end - start) + "ms.");

