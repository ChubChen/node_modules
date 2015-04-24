/**
 * Created by CH on 15-4-24.
 */
var xml2js = require('xml2js');

var xmlUtil = function(){
}

xmlUtil.prototype.jsonToXml = function(JsonObj){
    //将JSon对象转换为xml
    var buildXml = new xml2js.Builder({'xmldec':{'encoding':"UTF8"}});
    var xml = buildXml.buildObject(JsonObj);
    return xml;
}

var xml = new xmlUtil();
module.exports = xml;