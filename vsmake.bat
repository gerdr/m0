@echo off
setlocal
set M0_VERSION=0x20120610
set M0_VALUE_TYPE=uint64_t
set M0_INT_TYPE=int64_t
set M0_UINT_TYPE=uint64_t
set M0_NUM_TYPE=double
set M0_OP_TYPE=uint32_t
set M0_ENDIANNESS=0
set M0_OPS_FILE=m0.ops
set M0_IPD_FILE=m0.ipd
set M0_CFG_FILE=m0.cfg
set M0_REG_FILE=m0.reg

@echo on
perl gen-m0.h.pl <src-m0.h >m0.h
perl gen-ops.c.pl <src-ops.c >ops.c
cl -c interp.c
cl -c mob.c
cl -c ops.c
cl -c platform.c
cl -c t-sanity.c
cl -c t-ops.c
cl -out:t-sanity.exe t-sanity.c interp.obj mob.obj ops.obj platform.obj
cl -out:t-ops.exe t-ops.c interp.obj mob.obj ops.obj platform.obj
t-sanity
t-ops

@echo off
endlocal
