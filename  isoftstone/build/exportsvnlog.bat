cd /d %LSCADA%

svn log .\src --limit 10 --non-interactive > c:\svntmplog.log

cscript %LSCADA%\build\svnlog.vbs

rem del /f /s /q c:\svntmplog.log