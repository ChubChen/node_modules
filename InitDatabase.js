var dc = require('./DbCenter.js');
var async = require('async');

async.waterfall([
    function(cb){
        dc.init(function(err){
            cb(err);
        });
    },
    function(cb){
        dc.main.drop(function(err){
            cb(err);
        });
    },
    function(cb){
        dc.main.create(function(err){
            cb(err);
        });
    },
    function(cb){
        dc.mg.create(function(err){
            cb(err);
        });
    },
    function(cb){
        dc.check(function(err){
           cb(err);
        });
    }
], function (err, result) {
    console.log("end...........");
});