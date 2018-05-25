@echo off & setlocal
set std=%1
if "%std%"=="" set std=c++14

::set stdany=-Dany_CONFIG_SELECT_STD_ANY=1 -Dany_CONFIG_SELECT_NONSTD_ANY=1

set any_config=

set     clang=C:\Program Files\LLVM\bin\clang
set  optflags=-O2
set warnflags= -Wall -Wextra -Wpedantic -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-padded -Wno-missing-noreturn -Wno-documentation-unknown-command -Wno-documentation-deprecated-sync -Wno-documentation -Wno-weak-vtables -Wno-missing-prototypes -Wno-missing-variable-declarations -Wno-exit-time-destructors -Wno-global-constructors

"%clang%" -std=%std% %optflags% %warnflags% %stdany% %any_config% -fms-compatibility-version=19.00 -isystem "%VCInstallDir%include" -isystem "%WindowsSdkDir_71A%include" -I../include/nonstd -o any-main.t.exe any-main.t.cpp any.t.cpp && any-main.t.exe
endlocal
