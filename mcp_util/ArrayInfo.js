var ArrayInfo = function (row, col) {
    if(row != undefined && col != undefined ){
        if(row > 0 && col > 0){
            var tempArray = new Array(row);
            for(var i = 0; i < tempArray.length; i++){
                var colArray = new Array();
                colArray.length = col;
                tempArray[i] = colArray;
            }
            return tempArray;
        }
    }else if(row != undefined){
        if(row > 0){
            var tempArray = new Array(row);
            return tempArray;
        }
    }
}
module.exports = ArrayInfo;