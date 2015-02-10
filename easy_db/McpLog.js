var dateUtil = require('./DateUtil.js');
var async = require('async');

var McpLog = function(){
    var self = this;
    self.showLog = false;
};

McpLog.prototype.info = function(data)
{
    var self = this;
    if(self.showLog)
    {
        console.log(data);
    }
};

McpLog.prototype.setShowLog = function(showLog)
{
    var self = this;
    self.showLog = showLog;
};

module.exports = new McpLog();