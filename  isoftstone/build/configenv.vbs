strComputer = "."
Dim WshShell, bKey
Set WshShell = WScript.CreateObject("WScript.Shell")
Set objWMIService = GetObject("winmgmts:" _
    & "{impersonationLevel=impersonate}!\\" & strComputer & "\root\cimv2")
Set objVariable = objWMIService.Get("Win32_Environment").SpawnInstance_


rem QTDIR ��������
objVariable.Name = "QTDIR"
objVariable.VariableValue = "d:\Qt\4.7.3"
objVariable.SystemVariable = True
objVariable.UserName = "<SYSTEM>"
objVariable.Status = "OK"
objVariable.Put_

rem VISDIR ��������
objVariable.Name = "VISDIR"
objVariable.VariableValue = "d:\vis"
objVariable.SystemVariable = True
objVariable.UserName = "<SYSTEM>"
objVariable.Status = "OK"
objVariable.Put_

rem VISDATAPATH ��������
objVariable.Name = "VISDATAPATH"
objVariable.VariableValue = "D:\Vis\data2\graph_client"
objVariable.SystemVariable = True
objVariable.UserName = "<SYSTEM>"
objVariable.Status = "OK"
objVariable.Put_

rem qmakespec ��������
objVariable.Name = "qmakespec"
objVariable.VariableValue = "win32-msvc2008"
objVariable.SystemVariable = True
objVariable.UserName = "<SYSTEM>"
objVariable.Status = "OK"
objVariable.Put_


rem PATH ��������
bKey=WshShell.RegRead("HKLM\SYSTEM\CurrentControlSet\Control\Session Manager\Environment\PATH")
objVariable.Name = "PATH"
objVariable.VariableValue = bKey&";%QTDIR%\bin"&";%QTDIR%\lib"
objVariable.SystemVariable = True
objVariable.UserName = "<SYSTEM>"
objVariable.Status = "OK"
objVariable.Put_

MsgBox "�����������óɹ�������ģ�", 65, "��ʾ��Ϣ!"