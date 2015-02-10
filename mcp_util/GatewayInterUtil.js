var http = require('http');
var querystring = require('querystring');

var config = require('mcp_config');
var prop = config.prop;
var gts = prop.platform.gateways;

var esut = require("easy_util");
var log = esut.log;

var GatewayInterUtil = function(){};

GatewayInterUtil.prototype.get= function(message, cb)
{
    var self = this;
    var post_data  = querystring.stringify({
        message:message
    });
    var headers = {
        'Content-Type': 'application/x-www-form-urlencoded',
        'Content-Length':post_data.length
    };

    var path = "/mcp-filter/main/interface.htm";

    var ran = Math.round(Math.random()*10);
    var gtIndex = ran%gts.length;
    var gt = gts[gtIndex];
    var options = {host:gt.host, port:gt.port, method:gt.method, path:path};
    options.headers = headers;

    self.send(post_data, options, function(err, data){
        if(err)     //如果发生错误，切换一个，再次发送
        {
            log.info(err);
            gtIndex = (gtIndex + 1)%gts.length;
            gt = gts[gtIndex];
            options = {host:gt.host, port:gt.port, method:gt.method, path:path};
            options.headers = headers;

            self.send(post_data, options, function(err, data){
                cb(err, data);
            });
        }
        else
        {
            cb(err, data);
        }
    });
};

GatewayInterUtil.prototype.send = function(data, options, cb)
{
    var self = this;
    var backCalled = false; //是否已经调用过回调函数
    var req = http.request(options, function(res) {
        res.setEncoding('utf8');
        var backData = '';
        res.on('data', function (chunk) {
            backData += chunk;
        });
        res.on('end', function(){
            if(!backCalled)
            {
                cb(null, backData);
                backCalled = true;
            }
        });
    });
    req.setTimeout(20000);
    req.on('error', function(e) {
        if(!backCalled)
        {
            cb(e, null);
            backCalled = true;
        }
    });
    req.write(data, "utf8");
    req.end();
};

var gatewayInterUtil = new GatewayInterUtil();
module.exports = gatewayInterUtil;



