/**
 * Created by CH on 15-2-13.
 */
var pls = require('./build/Release/qxc');
var vlidate = require("./Validate.js");


var gameGrades = [104000,24600,10,10,10,10,10];
var gl = pls.gl(gameGrades.length);
gl.setBonus(gameGrades);

var check = pls.check();
check.setDrawNum("7|3|9|2|4|5|7");
check.setGl(gl);

/*console.log(check.count0000({number:'7|3|9|2|5|5|7'}));
console.log(check.count0000({number:'7|5|9|2|4|5|7'}));
console.log(check.count0000({number:'1|3|9|2|4|5|7'}));
console.log(check.count0000({number:'7|3|9|2|4|5|7'}));
console.log(check.count0000({number:'7|2|2|4|3|4|0'}));
console.log(check.count0000({number:'1|2|9|2|4|5|5'}));*/

console.log(check.count0001({number:'7,1,3|5,2,3|9|4,6,2|1,2,3,4,5,6|4|3,4'}));
console.log(check.count0001({number:'1,7|3|9|2|4|5|7'}));



vlidate.validate0001(null, {number:'1,7|3|9|2|4|5|7'}, function(err, length){
    if(err){
        console.log(err);
    }else{
        console.log(length)
    }
});


vlidate.validate0001(null, {number:'1,3,7|2,3,4|9|2,4,6|1,2,3,4,5,6|4|3,4'}, function(err, length){
    if(err){
        console.log(err);
    }else{
        console.log(length)
    }
});



