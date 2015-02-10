var MathUtil = function(){};

/**
 * 把字符串数组转换成int数组
 * @param strArray
 * @returns {Int32Array}
 */
MathUtil.prototype.getIntArrayFromStrArray = function(strArray)
{
    var self = this;
    var rst = [];
    for(var key in strArray)
    {
        rst[rst.length] = parseInt(strArray[key]);
    }
    return rst;
}

/**
 * 将值转换为Int
 */
MathUtil.prototype.getIntValue = function(str){
    if(isNaN(str)){
        return 0;
    }else{
        return parseInt(str);
    }
}

/**
 * 查看整数数组是否按从小到大排列，不能相等
 * @param intArray
 * @returns {boolean}
 */
MathUtil.prototype.isFromMinToMax = function(intArray)
{
    var self = this;
    if(intArray.length == 1)
    {
        return true;
    }
    var rst = true;
    for(var i = 0; i < intArray.length - 1; i++)
    {
        if(intArray[i] >= intArray[i + 1])
        {
            rst = false;
            break;
        }
    }
    return rst;
}
/**
 * 判断数组到最小值和最大值是否符合要求
 */
MathUtil.prototype.isMinAndMaxBetween = function(intArray, min , max){
    var self = this;
    if(intArray.length >= 2)
    {
        if(intArray[0] < min || intArray[intArray.length - 1] > max){
            return false;
        }else{
            return true;
        }
    }else if(intArray.length == 1){
        if(intArray[0] < min || intArray[0] > max){
            return false;
        }
    }
    return true;
}

/**
 * 查看整数数组是否按从小到大排列，可以相等
 * @param intArray
 * @returns {boolean}
 */
MathUtil.prototype.isFromMinToMaxCanEqual = function(intArray)
{
    var self = this;
    if(intArray.length == 1)
    {
        return true;
    }
    var rst = true;
    for(var i = 0; i < intArray.length - 1; i++)
    {
        if(intArray[i] > intArray[i + 1])
        {
            rst = false;
            break;
        }
    }
    return rst;
}

/**
 * 获得A(m,n)的值
 * @param m
 * @param n
 */
MathUtil.prototype.getA = function(m, n)
{
    var self = this;
    var value = 1;
    for (var i = 0; i < n; i++) {
        value = value * (m - i);
    }
    return value;
}

/**
 * 获得C(m,n)的值
 * @param m
 * @param n
 * @returns {number}
 */
MathUtil.prototype.getC = function(m, n)
{
    var self = this;
    if ((m < n) || (n < 0)) {
        return 0;
    }
    return self.getA(m, n) / self.getA(n, n);
}

/**
 * 获得两个整数数组中重复号码的个数
 * @param arrayOne
 * @param arrayTwo
 * @returns {number}
 */
MathUtil.prototype.getHitCount = function(arrayOne, arrayTwo)
{
    var self = this;
    var hitCount = 0;
    for(var i = 0; i < arrayOne.length; i++)
    {
        for(var j = 0; j < arrayTwo.length; j++)
        {
            if(arrayOne[i] == arrayTwo[j])
            {
                hitCount++;
            }
        }
    }
    return hitCount;
}

var DetailC = function(recordCount, n){
    var self = this;
    self.data = [];
    for(var i = 0; i < recordCount; i++)
    {
        self.data[i] = new Int32Array(n);
    }
    self.index = 0;

};

DetailC.prototype.put = function(set)
{
    var self = this;
    var dSet = self.data[self.index];
    for(var i = 0; i < dSet.length; i++)
    {
        dSet[i] = set[i];
    }
    self.index++;
}

DetailC.prototype.get = function()
{
    var self = this;
    return self.data;
}

/**
 * 获得c(m,n)所有记录集的详情
 * @param m
 * @param n
 */
MathUtil.prototype.getDetailC = function(m, n)
{
    var self = this;
    var recordCount = self.getC(m, n);
    var dc = new DetailC(recordCount, n);
    var data = new Int32Array(n);
    self.getDetailCRec(dc, data, m, n, 0);
    return dc.get();
}

MathUtil.prototype.getDetailCRec = function(dc, data, m, n, level)
{
    var self = this;
    if(n == 0)
    {
        dc.put(data);
        return;
    }
    var startIndex = 0;	//第一层从第一个记录开始
    if(level > 0)
    {
        startIndex = data[level - 1] + 1;	//非第一层，则要从上一层的下一个记录开始
    }
    for(var i = startIndex; i < m; i++)
    {
        data[level] = i;	//记录当层的序号
        self.getDetailCRec(dc, data, m, n - 1, level + 1);
    }
}

MathUtil.prototype.selectSort = function(intArray){
    var self = this;
    for(var i = 0 ; i < intArray.length-1; i++){
        var index = i;
        for(var j = i + 1; j < intArray.length; j++){
            if(intArray[j] < intArray[index]){
                index = j;
            }
        }
        if(index != i){
            var temp = intArray[i];
            intArray[i] = intArray[index];
            intArray[index] = temp;
        }
    }
}

module.exports = new MathUtil();