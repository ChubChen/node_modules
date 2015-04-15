var async = require('async');

var jc = require('./build/Release/jc');
var check = jc.check();

var drawNumber = {};

var getDrawNumber = function(matchCode, cb)
{
    if(matchCode == "201504024303")
    {
        cb(null, "66:68");
    }else if(matchCode == "201504024302" ){
        cb(null, "81:72");
    }else if(matchCode == "201504024305" ){
        cb(null, "93:76");
    }else if(matchCode == "201504024304" ){
        cb(null, "85:80");
    }else if(matchCode == "201504024301" ){
        cb(null, "75:94");
    }else if(matchCode == "201504024308" ){
        cb(null, "107:106");
    }else if(matchCode == "201504024306" ){
        cb(null, "114:88");
    }else if(matchCode == "201504024307" ){
        cb(null, "101:108");
    }else
    {
        cb(null, "*");
    }
}

var start = new Date().getTime();
for(var i = 0; i < 1; i++)
{
    var number = '01|201504024301|1(-4.5)@1.700;01|201504024302|2(-14.5)@1.700';
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

