Dim WshShell, bKey
Set WshShell = WScript.CreateObject("WScript.Shell")
bKey=WshShell.RegRead("HKLM\SYSTEM\CurrentControlSet\Control\Session Manager\Environment\STONEDIR")

svnbat = bKey&"\build\exportsvnlog.bat"

rem WshShell.Run(svnbat)

set fs =createobject("scripting.filesystemobject")
set ins=fs.opentextfile("c:\svntmplog.log",1,true)

logfile = bKey & "\svnlog.log"
set outs=fs.opentextfile(logfile,2,true)
do while ins.atendofstream <> true
line=ins.readline
outs.writeline line
loop
ins.close()
outs.close()

if (fs.fileexists("c:\svntmplog.log")) Then
fs.deleteFile "c:\svntmplog.log"
End if
