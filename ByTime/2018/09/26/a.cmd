:s
a_make.exe
a.exe
#1.exe
fc #1.out a.out
if not errorlevel == 1 goto :s
pause