@echo off

gcc .\main.c .\my_queue.c -o main.exe

if %errorlevel% equ 0 (
    .\main.exe
)