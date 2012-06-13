@echo off

:LOOP
if "%1"=="" goto EXIT
del %1 2>NUL
shift
goto LOOP

:EXIT
