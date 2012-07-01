@setlocal
@echo off

if not defined CMD_V_ON (
    set CMD_V_ON=true
    REM ע�⣺���ű�ʹ����CMD���ӻ���չ���ԣ����ʹ������ķ�ʽ��һ���µ�CMD����
    REM ��ִ�б��ű�
    cmd /E:ON /V:ON /C "%0 %*"
    pause
    goto :eof
)

REM ��������в����Ƿ���ȷ
if "%1"=="" (
	echo �Բ���������������в�������ȷ��
	echo ���������в���������Ҫ�ݹ�����vcproj�ļ�����ʼĿ¼�����������/����·��������
	echo %0 PATH
	echo �����ʼĿ¼Ϊ��ǰĿ¼��������'.'�������������ţ�������
	echo %0 .
	echo.
	goto :eof
)

if not exist %1\nul (
	echo �Բ������������ʼĿ¼�����ڣ����������롣
	echo.
	goto :eof
)

REM ������õĹ������Ͳ����Ƿ���ȷ
if "%2"=="" goto okay
if "%2"=="debug" goto okay
if "%2"=="release" goto okay
echo �Բ���������Ĺ������Ͳ���ȷ��Ӧ��Ϊ"debug"��"release"��Ϊ��
echo.
goto :eof
	
:okay
pushd %1
for /R %%f in (*.pro) do (
    REM �����pro���ڵ�·��
    cd /D %%~dpf
    echo Dir: %%~dpf
    REM ȡ��pro�ļ���
    set ProFile=%%~nxf
    echo ProFile: !ProFile!
    REM �����for����pro��ȡ��TEMPLATE�У���ȡ��=�ź��ֵ
    for /F "tokens=2 delims==" %%T in ('findstr /I "TEMPLATE.*=" !ProFile!') do (
        REM �����for��佫%%T�еĿհ׷���ȥ
        for /F %%t in ("%%T") do (
            echo TEMPLATE: %%t
            set ProjType=
            if "%%t"=="app" set ProjType=vcapp
            if "%%t"=="lib" set ProjType=vclib
	    if "%%t"=="subdirs" set ProjType=vcsubdirs
        )
    )
    echo ProjType: !ProjType!
    if not "!ProjType!"=="" (
    	if "%2"=="" (
        	set ICCSBUILDTYPE=release
        	qmake -t !ProjType! !ProFile!
	        set ICCSBUILDTYPE=debug
    	    qmake -t !ProjType! !ProFile!
		) else (
        	set ICCSBUILDTYPE=%2
        	qmake -t !ProjType! !ProFile!
        )
    )
    echo.
)
popd

endlocal
