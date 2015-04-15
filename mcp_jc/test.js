var async = require('async');

var jc = require('./build/Release/jc');
var check = jc.check();

var drawNumber = {};

var getDrawNumber = function(matchCode, cb)
{
    if(matchCode == "201503275006")
    {
        cb(null, "3:0,3:0,-2");
    }
    else if(matchCode == "201503275008")
    {
        cb(null, "2:0,4:0,-2");
    } else if(matchCode == "201503275009")
    {
        cb(null, "1:0,0:6,-4");
    }else if(matchCode == "201503275010")
    {
        cb(null, "2:0,3:0,-1");
    }else if(matchCode == "201503227030")
    {
        cb(null, "0:0,1:0,-1");
    }else if(matchCode == "201503227032")
    {
        cb(null, "2:2,2:3,+1");
    }else if(matchCode == "201503227034")
    {
        cb(null, "0:2,1:3,+1");
    }else if(matchCode == "201503227052")
    {
        cb(null, "1:1,2:1,-1");
    }else if(matchCode == "201503227039")
    {
        cb(null, "1:1,3:1,-1");
    }else if(matchCode == "201503227048")
    {
        cb(null, "2:0,2:0,-1");
    }
    else
    {
        cb(null, "*");
    }
}

var start = new Date().getTime();
for(var i = 0; i < 1; i++)
{
    //411 var number = '03|201503275006|30@5.600,40@8.000,50@15.00;03|201503275008|30@5.000,31@11.50,40@6.600;03|201503275009|50@5.700,09@2.650;03|201503275010|20@4.500,30@5.600,31@11.00';
    //33  var number = '02|201503227030|3@1.340;02|201503227039|3@1.480;02|201503227048|3@1.280';
    var number = '05|201503275013|00@2.950'; //45
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

