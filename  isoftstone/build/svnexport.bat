@setlocal

set LCSHSVNURL=svn://localhost/isoftstone

REM ����Ҫ�Ļ��������Ƿ�����
for %%V in (STONEDIR) do (
	if not defined %%V (
	@echo %%V ��������δ���ã�
	goto end
	)
)


REM ��������ĵ��ò�������������Ӧ�ı���
set ForWin=1
set CleanOld=0
set SccLabel=

:parseparam

if "%1"=="" goto endparam

REM �����������"windows"����ȡWindows����İ汾�����ļ��Իس����н�����
if "%1"=="windows" (
set ForWin=1
goto nextparam
)

REM �����������"unix"����ȡUNIX�汾���ļ��Ի��з�������Ĭ��ΪȡUNIX�汾��
if "%1"=="unix" (
set ForWin=0
goto nextparam
)

REM �����������"cleanold"����ɾ��ԭ�����ļ����»�ȡ������ֻ�����ļ�
if "%1"=="cleanold" (
set CleanOld=1
goto nextparam
)

REM ����� -L ���������ȡ�ض��İ汾(SccLabel)�������ȡ���°汾
if "%1"=="-L" (
set SccLabel=%2
shift
goto nextparam
)

REM ���ϲ��������ǣ���Ϊ��Ч����������
@echo ���ò�������
@echo �÷���
@echo %0 [unix^|windows] [cleanold] [-L SccLabel]
@echo ������
@echo unix        �ı��ļ���unix��ʽ��ȡ�����Ի��з�����ÿ�У�������Ĭ�ϵķ�ʽ
@echo windows     �ı��ļ���windows��ʽ��ȡ�����Իس����з�����ÿ�У�
@echo cleanold    ��ȡ�ļ�ʱ����ձ���Ŀ¼������ֻ�滻����Ĭ��Ϊ�滻��
@echo -L SccLabel ��ȡ��SccLabel��ע�İ汾��������ṩ���ȡ���°汾
goto end

:nextparam
shift
goto parseparam

:endparam
@echo ForWin=%ForWin%
@echo CleanOld=%CleanOld%
@echo SccLabel=%SccLabel%

REM ��ȡ��ĿԴ����

REM ���û�ȡѡ��
set LocalFold="%STONEDIR%/../STONE_SVN"
if "%SVNCOMMONOPTION%"=="" (
set SVNCOMMONOPTION=--username sys --password sys --non-interactive
)


set REPOURL=%LCSHSVNURL%


set CommonOptions=%SVNCOMMONOPTION% --force

if %ForWin%==1 (
REM Windows�ļ��Իس����н���
set CommonOptions=--native-eol CRLF %CommonOptions%
) else (
REM unix�ı��ļ��Ի��н���
set CommonOptions=--native-eol LF %CommonOptions%
)

@echo CommonOptions=%CommonOptions%

REM �����Ҫ����ɾ�������ļ����е�����
if %CleanOld%==1 (
	if exist %LocalFold% rmdir %LocalFold% /s /q
)

REM ��������Ŀ¼
if not exist %LocalFold% md %LocalFold%
cd %LocalFold%

@echo Getting source files ...
for %%P in (src proj config) do (
	svn export %COMMONOPTIONS% %REPOURL%/%%P %LocalFold%\%%P
)

REM ����BuildNo
cd /D %LocalFold%/build
if exist setbuildno.bat del /F setbuildno.bat 
cscript //Nologo genbuildno.vbs > setbuildno.bat
call setbuildno.bat
set BuildLabel=%BUILDNo%

REM ���Windows��Դ����
cd /D %LocalFold%
if exist iSoftStone.7z del iSoftStone.7z /F
7z a -t7z iSoftStone.7z .


REM ��WindowsԴ����ѹ�������ϱ���ź����Build����
if exist %LocalFold%\iSoftStone.7z (
	move /Y %LocalFold%\iSoftStone.7z ..\iSoftStone.%BuildLabel%.7z
)

echo ������־�ļ�......

cd /d %STONEDIR%

svn log .\src --limit 10 --non-interactive > c:\svntmplog.log

cscript %STONEDIR%\build\svnlog.vbs


echo ��ʼ�����ʼ�......

call %STONEDIR%\build\sendmail.bat %STONEDIR%\..\iSoftStone.%BuildLabel%.7z

rem ɾ�����Ŀ¼��ѹ���ļ�

rd /s /q %LocalFold%
del /f /s /q %STONEDIR%\..\iSoftStone.%BuildLabel%.7z


:end
endlocal
