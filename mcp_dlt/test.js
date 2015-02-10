var dlt = require('./build/Release/dlt');

var gameGrades = [1, 1, 1, 20000, 1000, 500, 1, 1, 1, 10000, 500];
var gl = dlt.gl(gameGrades.length);
gl.setBonus(gameGrades);

var check = dlt.check();
check.setDrawNum("09,14,17,18,21|01,03");
check.setGl(gl);

for(var i = 0; i < 1; i++)
{
    console.log(check.count0000({number:'09,14,17,18,21|01,04;09,14,17,18,21|01,03;09,14,17,18,21|02,04;09,14,17,18,21|02,04;09,14,17,18,22|02,04'}));
    console.log(check.count0001({number:'09,14,17,18,21,22|01,04'}));

    console.log(check.count0002({number:'09,14,17,18$21,22,23|01$03,04'}));
    console.log(check.count0502({number:'09,14,17,18$21,22,23|01$03,04'}));
}

