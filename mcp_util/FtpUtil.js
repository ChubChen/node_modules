/**
 * Created by CH on 15-4-24.
 */
var Client = require('ftp');
var path = require('path');
var c = new Client();
c.on('ready', function() {

    c.mkdir("html/1/2/3/4", true, function(err){
        if(err){
            console.log(err);
            throw err;
        }else{

        }
    })

});
c.connect({host:"218.30.107.22",port:21, user:"chenpeng",password:"123456"});