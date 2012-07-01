rem 配置邮件服务器

set BackupDir=%STONEDIR%\backup
set BuildDirSvn=%BackupDir%

set MailFile=%BackupDir%\mailw.txt
if exist %MailFile% del /F %MailFile%

REM 产生BuildNo
cd /D %STONEDIR%/build
if exist setbuildno.bat del /F setbuildno.bat 
cscript //Nologo genbuildno.vbs > setbuildno.bat

call %STONEDIR%\build\setbuildno.bat
set BuildLabel=%BUILDNo%
echo %BuildLabel%
set attachfile1 = d:\iSoftStone.%BuildLabel%.7z
echo %attachfile1%
REM 获取本机名
for /F %%H in ('hostname') do set HostName=%%H

@echo Windows机每日编译已结束，请检查>%MailFile%

@echo.>>%MailFile%
@echo 剩余磁盘空间：>>%MailFile%
cd /D %BuildDirSvn%
cd \
@echo BuildDir: >>%MailFile%
@dir | findstr /C:"可用字节">>%MailFile%
cd /D %BackupDir%
cd \
@echo BackupDir: >>%MailFile%
@dir | findstr /C:"可用字节">>%MailFile%
@echo.>>%MailFile%
@echo 如果没有错误，测试员可以开始测试工作。>>%MailFile%
@echo.>>%MailFile%
@echo 当前编译号：%BUILDNo%>>%MailFile%
@echo.>>%MailFile%
@echo Daily Builder>>%MailFile%
@echo %DATE% %TIME%>>%MailFile%
REM =================================================================

blat %STONEDIR%\svnlog.log -tf %BackupDir%\..\build\rcvmail.lst -subject "STONEDIR NEW VERSION" -server smtp.163.com -u liuruigong_lrg@163.com -pw liuruigong1985 -charset GBK -attach %1