Option Explicit

dim DateToday, BuildNo

Const cFirstBuildDate = 40202	'2010-01-25
Const cFirstBuildNo = 1

DateToday = CLng(Date())
BuildNo = DateToday - cFirstBuildDate + cFirstBuildNo

' ÿ��18:00��ǰ������ǰһ�죬��Ϊ18:00��ǰ��Ķ���ǰһ��İ汾���ų��������
If Hour(Now()) < 18 Then
	BuildNo = BuildNo - 1
End If

WScript.Echo "set BUILDNo=" & BuildNo
rem WScript.Echo "BUILDNo=" & BuildNo
