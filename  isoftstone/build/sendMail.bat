rem �����ʼ�������

set BackupDir=%STONEDIR%\backup
set BuildDirSvn=%BackupDir%

set MailFile=%BackupDir%\mailw.txt
if exist %MailFile% del /F %MailFile%

REM ����BuildNo
cd /D %STONEDIR%/build
if exist setbuildno.bat del /F setbuildno.bat 
cscript //Nologo genbuildno.vbs > setbuildno.bat

call %STONEDIR%\build\setbuildno.bat
set BuildLabel=%BUILDNo%
echo %BuildLabel%
set attachfile1 = d:\iSoftStone.%BuildLabel%.7z
echo %attachfile1%
REM ��ȡ������
for /F %%H in ('hostname') do set HostName=%%H

@echo Windows��ÿ�ձ����ѽ���������>%MailFile%

@echo.>>%MailFile%
@echo ʣ����̿ռ䣺>>%MailFile%
cd /D %BuildDirSvn%
cd \
@echo BuildDir: >>%MailFile%
@dir | findstr /C:"�����ֽ�">>%MailFile%
cd /D %BackupDir%
cd \
@echo BackupDir: >>%MailFile%
@dir | findstr /C:"�����ֽ�">>%MailFile%
@echo.>>%MailFile%
@echo ���û�д��󣬲���Ա���Կ�ʼ���Թ�����>>%MailFile%
@echo.>>%MailFile%
@echo ��ǰ����ţ�%BUILDNo%>>%MailFile%
@echo.>>%MailFile%
@echo Daily Builder>>%MailFile%
@echo %DATE% %TIME%>>%MailFile%
REM =================================================================

blat %STONEDIR%\svnlog.log -tf %BackupDir%\..\build\rcvmail.lst -subject "STONEDIR NEW VERSION" -server smtp.163.com -u liuruigong_lrg@163.com -pw liuruigong1985 -charset GBK -attach %1