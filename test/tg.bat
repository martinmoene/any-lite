@setlocal
@set std=%1
@if "%std%"=="" set std=c++11
g++ -std=%std% -O2 -Wall -Wextra -Wno-unused-parameter -o any-lite.t.exe -I../include/nonstd any-main.t.cpp any.t.cpp && any-lite.t.exe
@endlocal

