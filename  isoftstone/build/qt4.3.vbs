strComputer = "."
Dim WshShell, bKey
Set WshShell = WScript.CreateObject("WScript.Shell")
Set objWMIService = GetObject("winmgmts:" _
    & "{impersonationLevel=impersonate}!\\" & strComputer & "\root\cimv2")
Set objVariable = objWMIService.Get("Win32_Environment").SpawnInstance_


rem QTDIR 环境变量
objVariable.Name = "QTDIR"
objVariable.VariableValue = "d:\Qt\4.3.2"
objVariable.SystemVariable = True
objVariable.UserName = "<SYSTEM>"
objVariable.Status = "OK"
objVariable.Put_
