/**
 * Created by CH on 15-3-3.
 */
var BanchMap = function(){
    var self = this;
    self.info = [{id:11, code:'10000000'},
        {id:21, code:'01000000'},
        {id:31, code:'00100000'},
        {id:41, code:'00010000'},
        {id:51, code:'00001000'},
        {id:61, code:'00000100'},
        {id:71, code:'00000010'},
        {id:81, code:'00000001'},
        {id:23, code:'11000000'},
        {id:36, code:'11000000'},
        {id:37, code:'11100000'},
        {id:410, code:'11000000'},
        {id:414, code:'11100000'},
        {id:415, code:'11110000'},
        {id:515, code:'11000000'},
        {id:525, code:'11100000'},
        {id:530, code:'11110000'},
        {id:531, code:'11111000'},
        {id:621, code:'11000000'},
        {id:641, code:'11100000'},
        {id:656, code:'11110000'},
        {id:662, code:'11111000'},
        {id:663, code:'11111100'},
        {id:7127, code:'11111110'},
        {id:8255, code:'11111111'},
        {id:33, code:'01000000'},
        {id:34, code:'01100000'},
        {id:46, code:'01000000'},
        {id:411, code:'01110000'},
        {id:510, code:'01100000'},
        {id:526, code:'01111000'},
        {id:615, code:'01000000'},
        {id:635, code:'01100000'},
        {id:650, code:'01110000'},
        {id:657, code:'01111100'},
        {id:7120, code:'01111110'},
        {id:8247, code:'01111111'},
        {id:44, code:'00100000'},
        {id:45, code:'00110000'},
        {id:516, code:'00111000'},
        {id:620, code:'00100000'},
        {id:642, code:'00111100'},
        {id:55, code:'00010000'},
        {id:56, code:'00011000'},
        {id:622, code:'00011100'},
        {id:735, code:'00010000'},
        {id:870, code:'00010000'},
        {id:66, code:'00001000'},
        {id:67, code:'00001100'},
        {id:721, code:'00001000'},
        {id:856, code:'00001000'},
        {id:77, code:'00000100'},
        {id:78, code:'00000110'},
        {id:828, code:'00000100'},
        {id:88, code:'00000010'},
        {id:89, code:'00000011'}]
    self.infoArray = {};
    self.init();
};

BanchMap.prototype.init = function()
{
    var self = this;
    for(var key in self.info)
    {
        var set = self.info[key];
        self.infoArray[set.id] = set.code;
    }
};

BanchMap.prototype.getInfoById = function(id)
{
    var self = this;
    var obj ;
    if(id != undefined)
    {
        obj = self.infoArray;
        obj = obj[id];
    }
    return obj;
};


module.exports = new BanchMap();
