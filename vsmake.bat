@echo off
setlocal
set CYGWIN=nodosfilewarnings
make SHELL=cmd .SHELLFLAGS=/c SEPARATOR=\ CC=cl I_FLAG=/I OBJ_FLAG=/Fo EXE_FLAG=/Fe C_FLAG=/c CFLAGS=/Tp RM=rm-f EXESUFFIX=.exe OBJSUFFIX=.obj %*
endlocal
