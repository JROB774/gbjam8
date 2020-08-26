@echo off
setlocal

call buildvars.bat

pushd ..

if not exist binary mkdir binary
pushd source

..\.gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -c -o %Object% %Source%
..\.gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG    -o %Output% %Object%

del *.lst *.map *.o *.sym

popd
popd

endlocal
