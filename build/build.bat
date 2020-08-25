@echo off
setlocal

set Source=..\source\main.c
set Object=main.o
set Output=GBJAM.gb

pushd ..

if not exist binary mkdir binary
pushd binary

..\.gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -c -o %Object% %Source%
..\.gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -o    %Output% %Object%

del *.lst *.map *.o *.sym

popd
popd

endlocal
