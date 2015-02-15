/**
 * Created by CH on 15-2-13.
 */
var pls = require('./build/Release/pl3');
var vlidate = require("./Validate.js");


var gameGrades = [104000,24600];
var gl = pls.gl(gameGrades.length);
gl.setBonus(gameGrades);

var check = pls.check();
check.setDrawNum("7|5|1");
check.setGl(gl);

console.log(check.count0100({number:'5|7|1'}));
console.log(check.count0101({number:'5,6|5|1,2'}));
console.log(check.count0103({number:'01,03,05,13'}));
console.log(check.count0104({number:'1,7,4,8,5'}));
console.log(check.count0104({number:'1,3,4,8,5'}));
//console.log(check.count0105({number:'1,3$4,8,5'}));
//console.log(check.count0105({number:'1,7$4,8,5'}));
console.log(check.count0105({number:'1,7$3,1,5,9'}));
console.log(check.count0106({number:'1,2,3,4,8'}));
console.log(check.count0106({number:'1,2,3,4,5,6,9'}));


vlidate.validate0100(null, {number:"1|2|3;2|3|4;4|5|6;5|6|7;3|6|7|;6|5|6"}, function(err, length){
    if(err){
        console.log(err);
    }else{
        console.log(length)
    }
});

vlidate.validate0100(null, {number: "1|2|3;2|3|4;4|4|4"}, function(err, length){
    if(err){
        console.log(err);
    }else{
        console.log(length)
    }
});

vlidate.validate0101(null, {number: "1,2,3,4,5|5,6|9"}, function(err, length){
    if(err){
        console.log(err);
    }else{
        console.log(length)
    }
});


vlidate.validate0103(null, {number: "01"}, function(err, length){
    if(err){
        console.log(err);
    }else{
        console.log(length)
    }
});

vlidate.validate0104(null, {number: "1,2,3"}, function(err, length){
    if(err){
        console.log(err);
    }else{
        console.log(length)
    }
});


vlidate.validate0105(null, {number: "1,2$3,4,5"}, function(err, length){
    if(err){
        console.log(err);
    }else{
        console.log(length)
    }
});



vlidate.validate0106(null, {number: "1"}, function(err, length){
    if(err){
        console.log(err);
    }else{
        console.log(length)
    }
});
