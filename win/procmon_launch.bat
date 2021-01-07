set PROG_BASENAME=notepad
set EXT=exe
set PROG=%PROG_BASENAME%.%EXT%

REM File that has the ProcMon configuration file
set CONFIG_FILE_DIR=.\
set CONFIG_FILE=%PROG_BASENAME%.pmc
set CONFIG_FILEPATH=%CONFIG_FILE_DIR%\%CONFIG_FILE%

REM Filename with ProcMon output
set OUTPUT_FILEPATH= .\%PROG_BASENAME%.pml

set PMExe=Procmon.exe
set PMHide= /AcceptEula /Quiet
set PMCfg= /LoadConfig %CONFIG_FILEPATH%
set PMFile= /BackingFile %OUTPUT_FILEPATH%
start "" %PMExe% %PMHide% %PMCfg% %PMFile%
%PMExe% /WaitForIdle

REM Launch program to monitor
%PROG%

%PMExe% /Terminate
start "" %PMExe% /NoConnect /Minimized /Quiet
%PMExe% /WaitForIdle
%PMExe% /Terminate