@setlocal

set LCSHSVNURL=svn://localhost/isoftstone

REM 检查必要的环境变量是否设置
for %%V in (STONEDIR) do (
	if not defined %%V (
	@echo %%V 环境变量未设置！
	goto end
	)
)


REM 解析传入的调用参数，并设置相应的变量
set ForWin=1
set CleanOld=0
set SccLabel=

:parseparam

if "%1"=="" goto endparam

REM 如果参数中有"windows"，则取Windows所需的版本，即文件以回车换行结束。
if "%1"=="windows" (
set ForWin=1
goto nextparam
)

REM 如果参数中有"unix"，则取UNIX版本，文件以换行符结束，默认为取UNIX版本。
if "%1"=="unix" (
set ForWin=0
goto nextparam
)

REM 如果参数中有"cleanold"，则删除原来的文件重新获取，否则只更新文件
if "%1"=="cleanold" (
set CleanOld=1
goto nextparam
)

REM 如果有 -L 参数，则获取特定的版本(SccLabel)，否则获取最新版本
if "%1"=="-L" (
set SccLabel=%2
shift
goto nextparam
)

REM 以上参数都不是，则为无效参数，报错
@echo 调用参数错误！
@echo 用法：
@echo %0 [unix^|windows] [cleanold] [-L SccLabel]
@echo 参数：
@echo unix        文本文件以unix格式获取（即以换行符结束每行），这是默认的方式
@echo windows     文本文件以windows格式获取（即以回车换行符结束每行）
@echo cleanold    获取文件时先清空本地目录，否则只替换。（默认为替换）
@echo -L SccLabel 获取以SccLabel标注的版本。如果不提供则获取最新版本
goto end

:nextparam
shift
goto parseparam

:endparam
@echo ForWin=%ForWin%
@echo CleanOld=%CleanOld%
@echo SccLabel=%SccLabel%

REM 获取项目源程序

REM 设置获取选项
set LocalFold="%STONEDIR%/../STONE_SVN"
if "%SVNCOMMONOPTION%"=="" (
set SVNCOMMONOPTION=--username sys --password sys --non-interactive
)


set REPOURL=%LCSHSVNURL%


set CommonOptions=%SVNCOMMONOPTION% --force

if %ForWin%==1 (
REM Windows文件以回车换行结束
set CommonOptions=--native-eol CRLF %CommonOptions%
) else (
REM unix文本文件以换行结束
set CommonOptions=--native-eol LF %CommonOptions%
)

@echo CommonOptions=%CommonOptions%

REM 如果需要，先删除本地文件夹中的内容
if %CleanOld%==1 (
	if exist %LocalFold% rmdir %LocalFold% /s /q
)

REM 创建本地目录
if not exist %LocalFold% md %LocalFold%
cd %LocalFold%

@echo Getting source files ...
for %%P in (src proj config) do (
	svn export %COMMONOPTIONS% %REPOURL%/%%P %LocalFold%\%%P
)

REM 产生BuildNo
cd /D %LocalFold%/build
if exist setbuildno.bat del /F setbuildno.bat 
cscript //Nologo genbuildno.vbs > setbuildno.bat
call setbuildno.bat
set BuildLabel=%BUILDNo%

REM 打包Windows版源程序
cd /D %LocalFold%
if exist iSoftStone.7z del iSoftStone.7z /F
7z a -t7z iSoftStone.7z .


REM 将Windows源程序压缩包加上编译号后放入Build库中
if exist %LocalFold%\iSoftStone.7z (
	move /Y %LocalFold%\iSoftStone.7z ..\iSoftStone.%BuildLabel%.7z
)

echo 下载日志文件......

cd /d %STONEDIR%

svn log .\src --limit 10 --non-interactive > c:\svntmplog.log

cscript %STONEDIR%\build\svnlog.vbs


echo 开始发送邮件......

call %STONEDIR%\build\sendmail.bat %STONEDIR%\..\iSoftStone.%BuildLabel%.7z

rem 删除打包目录和压缩文件

rd /s /q %LocalFold%
del /f /s /q %STONEDIR%\..\iSoftStone.%BuildLabel%.7z


:end
endlocal
