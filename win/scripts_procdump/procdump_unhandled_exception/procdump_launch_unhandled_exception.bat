set DUMP_DIR=.\dumps
SET TARGET_EXE=UnhandledException_x64.exe
mkdir %DUMP_DIR%

REM to display the debug output in Procmon - must enable "Profiling"
procdump -e 1 -f "" -x %DUMP_DIR% %TARGET_EXE%