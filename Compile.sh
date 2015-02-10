#!/bin/sh
# Compile.sh
export node_modules=`pwd`
cd "$node_modules"
which node-gyp > /dev/null 2>&1
if [ $? -eq 0 ]; then
    for i in `ls -l |grep mcp_ | awk '/^d/{print $9}'`
    do
        cd "$node_modules"/"$i"
        tempFile=`ls -l | grep .gyp |awk '{print $9}'`
        echo "$tempFile"
        if [ -f "$tempFile"  ]; then
            echo "Compile" "$i"
            node-gyp configure build
        fi
    done
else
  echo "Node is not installed  or Not found node-gyp"
fi
