@echo off
set THIS_FILE=%~n0
set DIR="C:\\Windows"

REM -e (executable files only)
REM -s (recurse in subdirectories)
set OPTIONS=-e -nobanner

ECHO [%THIS_FILE%]: Checking in %DIR% ...

sigcheck %OPTIONS% %DIR% 1> nul
IF ERRORLEVEL 1 GOTO SIG_CHECK_FAILED
ECHO [%THIS_FILE%]: All executable files are signed
GOTO :EOF
:SIG_CHECK_FAILED
ECHO [%THIS_FILE%]: Files with signature issues: %ERRORLEVEL% 
