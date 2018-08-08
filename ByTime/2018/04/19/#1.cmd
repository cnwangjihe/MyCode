:s
bag_make.exe
bag.exe
#1.exe
fc #1.out bag.out
if not errorlevel == 1 goto :s
pause