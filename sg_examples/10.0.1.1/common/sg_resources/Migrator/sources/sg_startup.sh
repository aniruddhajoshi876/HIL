#!/bin/sh
echo "Speedgoat startup callback"

$(sg_translateEthernetInterfaces)

sleep 5
targetAuthentication="invalid"
/usr/speedgoat/bin/./sg_checkTargetAuthentication /usr/speedgoat/config /usr/speedgoat/config

if [ "$?" == "0" ]; then
    targetAuthentication="valid"
else
    targetAuthentication="invalid"
fi

if [ "$targetAuthentication" == "valid" ]; then
    echo "Successfully authenticated this target machine"
else
    echo "ERROR: Can not verify the genuineness of your target machine."
    echo "       Please execute \"speedgoat.getTargetAuthentication\" on your host,"
    echo "       otherwise it can not be used with MATLAB R2020b and later"
fi
