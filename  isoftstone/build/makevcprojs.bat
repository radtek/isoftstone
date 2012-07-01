@setlocal
@echo off

if not defined CMD_V_ON (
    set CMD_V_ON=true
    REM 注意：本脚本使用了CMD的延缓扩展特性，因此使用下面的方式在一个新的CMD环境
    REM 中执行本脚本
    cmd /E:ON /V:ON /C "%0 %*"
    pause
    goto :eof
)

REM 检查命令行参数是否正确
if "%1"=="" (
	echo 对不起，您输入的命令行参数不正确！
	echo 请在命令行参数中输入要递归生成vcproj文件的起始目录，可以是相对/绝对路径。即：
	echo %0 PATH
	echo 如果起始目录为当前目录，可输入'.'（不包含单引号），即：
	echo %0 .
	echo.
	goto :eof
)

if not exist %1\nul (
	echo 对不起，您输入的起始目录不存在，请重新输入。
	echo.
	goto :eof
)

REM 检查设置的构建类型参数是否正确
if "%2"=="" goto okay
if "%2"=="debug" goto okay
if "%2"=="release" goto okay
echo 对不起，您输入的构建类型不正确，应当为"debug"或"release"或为空
echo.
goto :eof
	
:okay
pushd %1
for /R %%f in (*.pro) do (
    REM 进入该pro所在的路径
    cd /D %%~dpf
    echo Dir: %%~dpf
    REM 取得pro文件名
    set ProFile=%%~nxf
    echo ProFile: !ProFile!
    REM 下面的for语句从pro中取出TEMPLATE行，并取得=号后的值
    for /F "tokens=2 delims==" %%T in ('findstr /I "TEMPLATE.*=" !ProFile!') do (
        REM 下面的for语句将%%T中的空白符除去
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
