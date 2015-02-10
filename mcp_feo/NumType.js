var esut = require("easy_util");
var log = esut.log;

var NumType = function(number){
    var self = this;
    self.Z24 = 0;
    self.Z12 = 1;
    self.Z6 = 2;
    self.Z4 = 3;

    self.info = self._getInfo(number);
};

/**
 * 获得号码出现的重复次数信息
 * @param number
 */
NumType.prototype._getInfo = function(number)
{
    var self = this;
    var info = {};
    var numStrArray = number.split(",");
    info.count = numStrArray.length;    //号码的个数
    info.keyCount = 0;
    var data = {};
    for(var key in numStrArray)
    {
        var c = numStrArray[key];
        if(data[c])
        {
            data[c]++;
        }
        else
        {
            info.keyCount++;
            data[c] = 1;
        }
    }
    info.data = data;
    return info;
}

/**
 * 是否是组24号
 */
NumType.prototype.isZ24 = function()
{
    var self = this;
    if(self.info.count != 4)
    {
        return false;
    }
    if(self.info.keyCount != 4)
    {
        return false;
    }
    return true;
}

/**
 * 是否是组12号
 */
NumType.prototype.isZ12 = function()
{
    var self = this;
    if(self.info.count != 4)
    {
        return false;
    }
    if(self.info.keyCount != 3)
    {
        return false;
    }
    return true;
}

/**
 * 是否是组6号
 */
NumType.prototype.isZ6 = function()
{
    var self = this;
    if(self.info.count != 4)
    {
        return false;
    }
    if(self.info.keyCount != 2)
    {
        return false;
    }
    var data = self.info.data;
    for(var key in data)
    {
        var count = data[key];
        if(count != 2)
        {
            return false;
        }
    }
    return true;
}

/**
 * 是否是组4号
 */
NumType.prototype.isZ4 = function()
{
    var self = this;
    if(self.info.count != 4)
    {
        return false;
    }
    if(self.info.keyCount != 2)
    {
        return false;
    }
    var data = self.info.data;
    var hasThree = false;   //是否有号码出现3次
    for(var key in data)
    {
        var count = data[key];
        if(count == 3)
        {
            hasThree = true;
        }
    }
    if(!hasThree)
    {
        return false;
    }
    return true;
}

/**
 * 是否是豹子号
 */
NumType.prototype.isZ1 = function()
{
    var self = this;
    if(self.info.count != 4)
    {
        return false;
    }
    if(self.info.keyCount != 1)
    {
        return false;
    }
    return true;
}

module.exports = NumType;

