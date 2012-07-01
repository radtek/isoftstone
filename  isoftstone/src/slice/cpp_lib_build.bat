cd /d %LSCADA%\src\sliceimpl
slice2cpp  -I ../slice/ -I %ICE_HOME%\slice --output-dir ./cppdll/ --dll-export ICEEXPORT ../slice/*.ice

slice2cpp  -I ../slice/ -I %ICE_HOME%\slice --output-dir ./cppdll/ --dll-export ICEEXPORT --stream ../slice/LcshUtil.ice