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
    } else if(matchCode == "201503227028")
    {
        cb(null, "1:0,2:0,-1");
    }else if(matchCode == "201503227030")
    {
        cb(null, "0:0,1:0,-1");
    }else if(matchCode == "201503227032")
    {
        cb(null, "2:2,2:3,+1");
    }else if(matchCode == "201503227034")
    {
        cb(null, "0:2,1:3,+1");
    }else if(matchCode == "201503227038")
    {
        cb(null, "0:1,0:2,-2");
    }else if(matchCode == "201503227039")
    {
        cb(null, "1:1,3:1,-1");
    }else if(matchCode == "201503227040")
    {
        cb(null, "3:0,4:1,-1");
    }else if(matchCode == "201503227043")
    {
        cb(null, "0:2,2:3,+1");
    }
    else
    {
        cb(null, "0:0,1:1,-1");
    }
}

var start = new Date().getTime();
for(var i = 0; i < 1; i++)
{
    var number = '01|201503227028|3@3.250,1@3.400;01|201503227030|3@2.100,1@3.600;01|201503227032|1@3.250,0@2.330;01|201503227034|1@3.400,0@3.900;01|201503227038|1@4.000,0@2.300;01|201503227039|3@2.670,1@3.200;01|201503227040|3@1.980,1@3.550;01|201503227043|1@3.250,0@2.470';
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
            bType:'21'
        }));
    });
}
var end = new Date().getTime();
console.log("执行耗时:" + (end - start) + "ms.");

