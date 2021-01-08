REM must run elevated; open cmd.exe w/ "Run As Administrator"
set DUMP_DIR=.\dumps
mkdir %DUMP_DIR%

for /f "delims=, tokens=2" %%f in ('tasklist /fo csv') do (
	procdump -accepteula %%f %DUMP_DIR%
)

REM if running on command line, use:
REM   for /f "delims=, tokens=2" %f in ('tasklist /fo csv') do procdump %f	