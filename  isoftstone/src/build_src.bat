REM …Ë÷√VSª∑æ≥
if "%VSINSTALLDIR%"=="" (
	call "%VS90COMNTOOLS%"\vsvars32.bat
)

qmake
nmake clean
nmake
@pause

