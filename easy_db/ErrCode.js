var ErrCode = function()
{
    var self = this;
    self.E0000 = {repCode:"0000", description:"系统处理成功"};
    self.E9999 = {repCode:"9999", description:"系统内部错误"};
};
module.exports = new ErrCode();