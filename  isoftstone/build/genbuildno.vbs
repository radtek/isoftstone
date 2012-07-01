Option Explicit

dim DateToday, BuildNo

Const cFirstBuildDate = 40202	'2010-01-25
Const cFirstBuildNo = 1

DateToday = CLng(Date())
BuildNo = DateToday - cFirstBuildDate + cFirstBuildNo

' 每天18:00以前都记入前一天，因为18:00以前编的都是前一天的版本（排除编译错误）
If Hour(Now()) < 18 Then
	BuildNo = BuildNo - 1
End If

WScript.Echo "set BUILDNo=" & BuildNo
rem WScript.Echo "BUILDNo=" & BuildNo
