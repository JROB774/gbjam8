@echo off
setlocal

call buildvars.bat

pushd ..

if not exist binary mkdir binary
pushd binary

..\.gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -o %Output% %Source%

del *.lst *.map *.o *.sym

popd
popd

endlocal
