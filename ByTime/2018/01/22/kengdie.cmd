@echo off
:be
kengdie_make.exe
kengdie.exe
kengdie1.exe
fc kengdie.out kengdie1.out
if not errorlevel == 1 goto :be
pause
