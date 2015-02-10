var http = require('http');
var querystring = require('querystring');

var config = require('mcp_config');
var prop = config.prop;

var esut = require('easy_util');
var digestUtil = esut.digestUtil;
var dateUtil = esut.dateUtil;
var log = esut.log;

var NotifyUtil = function(){};

NotifyUtil.prototype.send = function(options, digestType, userKey, cmd, body, cb)
{
    log.info(options);
    body.uniqueId = digestUtil.createUUID();
    var bodyStr = JSON.stringify(body);
    var head = {digest:"", digestType:digestType, cmd:cmd};
    head.timestamp = dateUtil.getCurTime();
    var encodedBody = bodyStr;
    if(head.digestType.length > 0)
    {
        encodedBody = digestUtil.generate(head, userKey, bodyStr);
    }
    var msgJson = {head:head, body:encodedBody};
    var msgToSend = JSON.stringify(msgJson);
    var post_data  = querystring.stringify({
        message:msgToSend
    });
    var headers = {
        'Content-Type': 'application/x-www-form-urlencoded',
        'Content-Length':post_data.length
    };
    options.headers = headers;
    var backCalled = false;
    var req = http.request(options, function(res) {
        res.setEncoding('utf8');
        var data = '';
        res.on('data', function (chunk) {
            data += chunk;
        });

        res.on('end', function(){
            var backNode;
            try {
                log.info(data);
                backNode = JSON.parse(data);
            }
            catch(err)
            {
                backNode = {};
            }
            if(!backCalled)
            {
                cb(null, backNode);
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
    req.write(post_data, "utf8");
    req.end();
};

var notifyUtil = new NotifyUtil();
module.exports = notifyUtil;



