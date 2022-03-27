@echo off
CD /d "%~dp0"
echo selected file: [%1]
echo please write new filename (without extension) and press enter
SET /P NAME=
BinMerger.exe "%1" "%NAME%"
Pause
