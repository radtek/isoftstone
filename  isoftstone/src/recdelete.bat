@echo off
setlocal enabledelayedexpansion

for /r %%a in (*.user *.ncb *.pdb *.lib *.dll *.exp *.ilk *.idb *.Debug *.Release *.old) do (
set file=%%a
echo !file!
del /f /s /q !file!
)

echo ɾ��_UpgradeReport_FilesĿ¼
for /r %%a in (.) do (
set file=%%a
echo "!file:~0,-2!"

if "!file:~-22,20!"=="_UpgradeReport_Files"  rd /q /s "!file:~0,-2!"
)

echo ɾ��debugĿ¼
for /r %%a in (.) do (
set file=%%a
echo "!file:~0,-2!"

if "!file:~-7,5!"=="Debug"  rd /q /s "!file:~0,-2!"
if "!file:~-9,7!"=="Release"  rd /q /s "!file:~0,-2!"
if "!file:~-7,5!"=="debug"  rd /q /s "!file:~0,-2!"
if "!file:~-9,7!"=="release"  rd /q /s "!file:~0,-2!"
if "!file:~-5,3!"=="tmp"  rd /q /s "!file:~0,-2!"
if "!file:~-5,3!"=="x64"  rd /q /s "!file:~0,-2!"
if "!file:~-5,3!"=="svn"  rd /q /s "!file:~0,-2!"
)

pause