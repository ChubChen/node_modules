var ssq = require('./build/Release/ssq');

var gameGrades = [400000000, 100000000, 300000, 20000, 1000, 500];
var gl = ssq.gl(gameGrades.length);
gl.setBonus(gameGrades);

var check = ssq.check();
check.setDrawNum("09,14,17,18,21,25|15");
check.setGl(gl);

for(var i = 0; i < 2; i++)
{
    console.log(check.count0000({number:'09,14,17,18,21,25|15;09,15,16,19,22,26|15;09,15,17,19,22,26|15;09,14,17,18,21,25|10;09,14,17,18,21,25|10'}))
    console.log(check.count0000({number:'09,14,17,18,21,25|10'}))
    console.log(check.count0000({number:'08,14,17,18,21,25|15'}))

    console.log(check.count0001({number:'08,09,14,17,18,21,25|15'}))

    console.log(check.count0002({number:'08,09,14,17,18$21,25|15,16'}))

    console.log(check.count0002({number:'08,09,14,17,18$21,25,26|15,16,17'}))
}

