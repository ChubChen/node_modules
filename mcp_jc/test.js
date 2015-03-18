var async = require('async');

var jc = require('./build/Release/jc');
var check = jc.check();

var drawNumber = {};

var getDrawNumber = function(matchCode, cb)
{
    if(matchCode == "201406135006")
    {
        cb(null, "0:0,1:2,-1");
    }
    else if(matchCode == "201406135003")
    {
        cb(null, "*");
    }
    else
    {
        cb(null, "0:0,1:1,-1");
    }
}

var start = new Date().getTime();
for(var i = 0; i < 10000; i++)
{
    var number = '05|201406135006|3@1.9,2@2.0';
    //var number = '03|201406135006|12@1.30;03|201406135005|11@1.30;03|201406135003|11@3.0';
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
            bType:'11'
        }));
    });
}
var end = new Date().getTime();
console.log("执行耗时:" + (end - start) + "ms.");

