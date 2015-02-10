var ErrCode = function()
{
    var self = this;
    self.E0000 = {repCode:"0000", description:"系统处理成功"};
    self.E0001 = {repCode:"0001", description:"校验签名失败"};
    self.E0002 = {repCode:"0002", description:"用户不存在"};
    self.E0003 = {repCode:"0003", description:"用户名或在密码错误"};
    self.E0004 = {repCode:"0004", description:"消息已经过期"};
    self.E0005 = {repCode:"0005", description:"用户未登录"};
    self.E0006 = {repCode:"0006", description:"消息格式错误"};

    self.E1007 = {repCode:"1007", description:'账户余额不足'};

    self.E2003 = {repCode:'2003', description:'期次不存在'};
    self.E2005 = {repCode:'2005', description:'订单不存在'};
    self.E2008 = {repCode:'2008', description:'不是当前期'};
    self.E2035 = {repCode:"2035", description:"渠道不存在"};
    self.E2057 = {repCode:"2057", description:"处于不允许的状态"};
    self.E2058 = {repCode:'2058', description:'JSON格式转换出错'};
    self.E2059 = {repCode:'2059', description:'系统繁忙'};
    self.E2060 = {repCode:"2060", description:"不支持的cmd"};
    self.E2061 = {repCode:"2061", description:"金额错误"};
    self.E2062 = {repCode:"2062", description:"不支持的玩法或者投注方式"};
    self.E2063 = {repCode:"2063", description:"不支持的游戏"};
    self.E2064 = {repCode:"2064", description:"外部id不能为空"};
    self.E2065 = {repCode:"2065", description:"期次不存在"};
    self.E2066 = {repCode:"2066", description:"号码格式错误"};
    self.E2067 = {repCode:"2067", description:"账户异常,或者余额不足"};
    self.E2068 = {repCode:"2068", description:"游戏不可用"};
    self.E2069 = {repCode:"2069", description:"订单成功金额0"};
    self.E2070 = {repCode:"2070", description:"参数错误"};
    self.E2071 = {repCode:"2071", description:"单式不能超过5注"};


    self.E0999 = {repCode:"0999", description:"系统内部错误"};
    self.E9000 = {repCode:"9000", description:"不支持的数据库类型"};
    self.E9002 = {repCode:"9002", description:'密钥来源错误'};
    self.E9003 = {repCode:"9003", description:'密钥错误'};
    self.E9004 = {repCode:"9004", description:'登录超时'};
    self.E9005 = {repCode:"9005", description:'不支持的用户类型'};
    self.E9006 = {repCode:"9006", description:'会话结束'};
    self.E9999 = {repCode:"9999", description:"处理失败"};



    self.E3001 = {repCode:'3001', description:'票据不存在'};
    self.E3002 = {repCode:'3002', description:'票据已经失效'};
    self.E3003 = {repCode:'3003', description:'机构不支持的游戏'};
    self.E3004 = {repCode:'3004', description:'票据状态错误'};

    self.E4001 = {repCode:'4001', description:'页面不存在'};
    self.E4002 = {repCode:'4002', description:'缺少通知配置'};
};
module.exports = new ErrCode();