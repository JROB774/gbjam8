@echo off
setlocal

call buildvars.bat

pushd ..
.emulator\bgb64.exe binary\%Output%
popd

endlocal
