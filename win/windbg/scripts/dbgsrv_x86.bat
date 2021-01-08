@echo off
SET PORT_NUM=5000
SET ARCH=x86
SET DBGSRV_DIR="C:\\Program Files (x86)\\Windows Kits\\10\\Debuggers\\%ARCH%\\"

echo Killing any running dbgsrv...
TASKKILL /IM dbgsrv.exe /F

echo dbgsrv (%ARCH%) listening on port %PORT_NUM%...
%DBGSRV_DIR%dbgsrv.exe -t tcp:port=%PORT_NUM%

