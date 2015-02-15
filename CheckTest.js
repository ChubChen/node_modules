/**
 * Created by CH on 15-2-13.
 */
var pls = require('mcp_pl3').pl3;


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

