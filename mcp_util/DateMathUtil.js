var moment = require('moment');


var DateUtil = function () {
};


//---------------------------------------------------
// 日期格式化
// 格式 YYYY/yyyy/YY/yy 表示年份
// MM/M 月份
// W/w 星期
// dd/DD/d/D 日期
// hh/HH/h/H 时间
// mm/m 分钟
// ss/SS/s/S 秒
//---------------------------------------------------
DateUtil.prototype.format = function format(formatStr) {
    var str = formatStr;
    var Week = ['日', '一', '二', '三', '四', '五', '六'];
    var dataSet = new Date();
    str = str.replace(/yyyy|YYYY/, dataSet.getFullYear());
    str = str.replace(/yy|YY/, (dataSet.getYear() % 100) > 9 ? (dataSet.getYear() % 100).toString() : '0' + (dataSet.getYear() % 100));

    str = str.replace(/MM/, dataSet.getMonth() > 9 ? (dataSet.getMonth() + 1).toString() : '0' + (dataSet.getMonth() + 1));
    str = str.replace(/M/g, dataSet.getMonth());

    str = str.replace(/w|W/g, Week[dataSet.getDay()]);

    str = str.replace(/dd|DD/, dataSet.getDate() > 9 ? dataSet.getDate().toString() : '0' + dataSet.getDate());
    str = str.replace(/d|D/g, dataSet.getDate());

    str = str.replace(/hh|HH/, dataSet.getHours() > 9 ? dataSet.getHours().toString() : '0' + dataSet.getHours());
    str = str.replace(/h|H/g, dataSet.getHours());
    str = str.replace(/mm/, dataSet.getMinutes() > 9 ? dataSet.getMinutes().toString() : '0' + dataSet.getMinutes());
    str = str.replace(/m/g, dataSet.getMinutes());

    str = str.replace(/ss|SS/, dataSet.getSeconds() > 9 ? dataSet.getSeconds().toString() : '0' + dataSet.getSeconds());
    str = str.replace(/s|S/g, dataSet.getSeconds());

    return str;
}

//+---------------------------------------------------
//| 求两个时间的天数差 日期格式为 YYYY-MM-dd
//+---------------------------------------------------
DateUtil.prototype.daysBetween = function daysBetween(DateOne, DateTwo) {
    var OneMonth = DateOne.substring(5, DateOne.lastIndexOf('-'));
    var OneDay = DateOne.substring(DateOne.length, DateOne.lastIndexOf('-') + 1);
    var OneYear = DateOne.substring(0, DateOne.indexOf('-'));

    var TwoMonth = DateTwo.substring(5, DateTwo.lastIndexOf('-'));
    var TwoDay = DateTwo.substring(DateTwo.length, DateTwo.lastIndexOf('-') + 1);
    var TwoYear = DateTwo.substring(0, DateTwo.indexOf('-'));

    var cha = ((Date.parse(OneMonth + '/' + OneDay + '/' + OneYear) - Date.parse(TwoMonth + '/' + TwoDay + '/' + TwoYear)) / 86400000);
    return Math.abs(cha);
}


//+---------------------------------------------------
//| 日期计算
//+---------------------------------------------------
DateUtil.prototype.dateAdd = function dateAdd(strInterval, Number) {
    var dtTmp = new Date();
    switch (strInterval) {
        case 's' :
            return new Date(Date.parse(dtTmp) + (1000 * Number));
        case 'n' :
            return new Date(Date.parse(dtTmp) + (60000 * Number));
        case 'h' :
            return new Date(Date.parse(dtTmp) + (3600000 * Number));
        case 'd' :
            return new Date(Date.parse(dtTmp) + (86400000 * Number));
        case 'w' :
            return new Date(Date.parse(dtTmp) + ((86400000 * 7) * Number));
        case 'q' :
            return new Date(dtTmp.getFullYear(), (dtTmp.getMonth()) + Number * 3, dtTmp.getDate(), dtTmp.getHours(), dtTmp.getMinutes(), dtTmp.getSeconds());
        case 'm' :
            return new Date(dtTmp.getFullYear(), (dtTmp.getMonth()) + Number, dtTmp.getDate(), dtTmp.getHours(), dtTmp.getMinutes(), dtTmp.getSeconds());
        case 'y' :
            return new Date((dtTmp.getFullYear() + Number), dtTmp.getMonth(), dtTmp.getDate(), dtTmp.getHours(), dtTmp.getMinutes(), dtTmp.getSeconds());
    }
}

//+---------------------------------------------------
//| 比较日期差 dtEnd 格式为日期型或者有效日期格式字符串
//+---------------------------------------------------
DateUtil.prototype.dateDiff = function dateDiff(strInterval, dtEnd) {
    var dtStart = new Date();
    if (typeof dtEnd == 'string')//如果是字符串转换为日期型
    {
        dtEnd = StringToDate(dtEnd);
    }
    switch (strInterval) {
        case 's' :
            return parseInt((dtEnd - dtStart) / 1000);
        case 'n' :
            return parseInt((dtEnd - dtStart) / 60000);
        case 'h' :
            return parseInt((dtEnd - dtStart) / 3600000);
        case 'd' :
            return parseInt((dtEnd - dtStart) / 86400000);
        case 'w' :
            return parseInt((dtEnd - dtStart) / (86400000 * 7));
        case 'm' :
            return (dtEnd.getMonth() + 1) + ((dtEnd.getFullYear() - dtStart.getFullYear()) * 12) - (dtStart.getMonth() + 1);
        case 'y' :
            return dtEnd.getFullYear() - dtStart.getFullYear();
    }
}


//+---------------------------------------------------
//| 日期合法性验证
//| 格式为：YYYY-MM-DD或YYYY/MM/DD
//+---------------------------------------------------
DateUtil.prototype.isValidDate = function isValidDate(DateStr) {
    var sDate = DateStr.replace(/(^\s+|\s+$)/g, ''); //去两边空格;
    if (sDate == '') return true;
    //如果格式满足YYYY-(/)MM-(/)DD或YYYY-(/)M-(/)DD或YYYY-(/)M-(/)D或YYYY-(/)MM-(/)D就替换为''
    //数据库中，合法日期可以是:YYYY-MM/DD(2003-3/21),数据库会自动转换为YYYY-MM-DD格式
    var s = sDate.replace(/[\d]{4,4}[-/]{1}[\d]{1,2}[-/]{1}[\d]{1,2}/g, '');
    if (s == '') //说明格式满足YYYY-MM-DD或YYYY-M-DD或YYYY-M-D或YYYY-MM-D
    {
        var t = new Date(sDate.replace(/-/g, '/'));
        var ar = sDate.split(/[-/:]/);
        if (ar[0] != t.getFullYear() || ar[1] != t.getMonth() + 1 || ar[2] != t.getDate()) {
            //alert('错误的日期格式！格式为：YYYY-MM-DD或YYYY/MM/DD。注意闰年。');
            return false;
        }
    }
    else {
        //alert('错误的日期格式！格式为：YYYY-MM-DD或YYYY/MM/DD。注意闰年。');
        return false;
    }
    return true;
}

//+---------------------------------------------------
//| 把日期分割成数组
//+---------------------------------------------------
DateUtil.prototype.toArray = function toArray() {
    var myDate = new Date();
    var myArray = new Array();
    myArray[0] = myDate.getFullYear();
    myArray[1] = myDate.getMonth();
    myArray[2] = myDate.getDate();
    myArray[3] = myDate.getHours();
    myArray[4] = myDate.getMinutes();
    myArray[5] = myDate.getSeconds();
    return myArray;
}

//+---------------------------------------------------
//| 取得日期数据信息
//| 参数 interval 表示数据类型
//| y 年 m月 d日 w星期 ww周 h时 n分 s秒
//+---------------------------------------------------
DateUtil.prototype.datePart = function datePart(interval) {
    var myDate = new Date();
    var partStr = '';
    var Week = ['日', '一', '二', '三', '四', '五', '六'];
    switch (interval) {
        case 'y' :
            partStr = myDate.getFullYear();
            break;
        case 'm' :
            partStr = myDate.getMonth() + 1;
            break;
        case 'd' :
            partStr = myDate.getDate();
            break;
        case 'w' :
            partStr = Week[myDate.getDay()];
            break;
        case 'ww' :
            partStr = myDate.WeekNumOfYear();
            break;
        case 'h' :
            partStr = myDate.getHours();
            break;
        case 'n' :
            partStr = myDate.getMinutes();
            break;
        case 's' :
            partStr = myDate.getSeconds();
            break;
    }
    return partStr;
}


//+---------------------------------------------------
//| 字符串转成日期类型
//| 格式 MM/dd/YYYY MM-dd-YYYY YYYY/MM/dd YYYY-MM-dd
//+---------------------------------------------------
DateUtil.prototype.stringToDate = function stringToDate(DateStr) {

    var converted = Date.parse(DateStr);
    var myDate = new Date(converted);
    if (isNaN(myDate)) {
        //var delimCahar = DateStr.indexOf('/')!=-1?'/':'-';
        var arys = DateStr.split('-');
        myDate = new Date(arys[0], --arys[1], arys[2]);
    }
    return myDate;
}

//+---------------------------------------------------
//| 求时间距现在多长时间
//+---------------------------------------------------
DateUtil.prototype.secondBetween = function secondBetween(DateTwo)
{
    var  str=DateTwo.toString();
    str = str.replace(/-/g,"/");
    var date2 = new Date(str);
    var date3=new Date()-date2.getTime();  //时间差的毫秒数
    //计算出相差天数
    var days=Math.floor(date3/(24*3600*1000));
    //计算出小时数
    var leave1=date3%(24*3600*1000);    //计算天数后剩余的毫秒数
    var hours=Math.floor(leave1/(3600*1000));
    //计算相差分钟数
    var leave2=leave1%(3600*1000);        //计算小时数后剩余的毫秒数
    var minutes=Math.floor(leave2/(60*1000));
    //计算相差秒数
    var leave3=leave2%(60*1000);      //计算分钟数后剩余的毫秒数
    var seconds=Math.round(leave3/1000);
    var res="";
    if(days!=0){
        res+=days+"天 ";
    }
    if(hours!=0){
        res+=hours+"小时 ";
    }
    if(minutes!=0){
        res+=minutes+"分钟 ";
    }
    if(seconds!=0){
        res+=seconds+"秒";
    }
    return  res;
}


//+---------------------------------------------------
//| 获取一天00:00:00
//| 格式 YYYY-MM-dd
//+---------------------------------------------------
DateUtil.prototype.getEarlyTime = function getEarlyTime(DateStr) {
    if (DateStr == undefined) {
        var today = moment().format("YYYY-MM-DD");
        return  today + " 00:00:00";
    } else {
        return  DateStr + " 00:00:00";
    }
}

//+---------------------------------------------------
//| 获取一天23:59:59
//| 格式 YYYY-MM-dd
//+---------------------------------------------------
DateUtil.prototype.getLaterTime = function getLaterTime(DateStr) {
    if (DateStr == undefined) {
        var today = moment().format("YYYY-MM-DD");
        return  today + " 23:59:59";
    } else {
        return  DateStr + " 23:59:59";
    }
}


//+---------------------------------------------------
//| 转为时间戳
//+---------------------------------------------------
DateUtil.prototype.getTimestamp  = function getTimestamp (DateStr) {
    return moment(DateStr, "YYYY-MM-DD HH:mm:ss").valueOf();
}


//若要显示:当前日期加时间(如:2009-06-12 12:00)

DateUtil.prototype.curentTime = function curentTime(showWeek) {
    var now = new Date();

    var year = now.getFullYear();       //年
    var month = now.getMonth() + 1;     //月
    var day = now.getDate();            //日
    var hh = now.getHours();            //时
    var mm = now.getMinutes();          //分
    var ss = now.getSeconds();           //秒

    var clock = year + "-";

    if (month < 10)
        clock += "0";

    clock += month + "-";

    if (day < 10)
        clock += "0";

    clock += day + " ";

    if (hh < 10)
        clock += "0";

    clock += hh + ":";

    if (mm < 10)

        clock += '0';

    clock += mm + ":";

    if (ss < 10)

        clock += '0';

    clock += ss;


    if (showWeek) {
        var Week = ["日", "一", "二", "三", "四", "五", "六"];
        clock += ' 星期' + Week[now.getDay()];
    }

    return(clock);
}

module.exports = new DateUtil();