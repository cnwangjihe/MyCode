@echo off
:be
gift_make.exe
gift.exe
gift4.exe
fc gift.out gift4.out
if not errorlevel == 1 goto :be
pause

exit

