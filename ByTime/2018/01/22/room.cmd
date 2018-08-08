@echo off
:be
room_make.exe
room.exe
room1.exe
fc room.out room1.out
if not errorlevel == 1 goto :be
pause
