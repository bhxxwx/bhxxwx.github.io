<%
UpDir="�ɼ�"			'�������ݿ�����Ŀ¼(�ļ�������)��
title="��������Сѧ�ɼ���ѯϵͳ"	'���ò�ѯ����,�����㶮�ġ�
copysr="��������Сѧ"	'���õײ���Ȩ����,�����㶮�ġ�
copysu="http://bhxxwx.github.io/2/2.html"	'���õײ���Ȩ����,�����㶮�ġ�

'���ò�ѯ����
tiaojian1="����"  		'�������б��⣬��excelһ��
yanzhenma="1"  		'�Ƿ�ʹ����֤�롣��1ʹ��0����

usename="admin@wuyi.net"			'��̨�û���(�����ʽ)
usepass="2532525454"				'��̨����

'���ò�ѯ���������޸���������
duan=tiaojian1


if len(tiaojian1)=2 then
 qianmian1=left(tiaojian1,1)&"&nbsp;&nbsp;"&right(tiaojian1,1)
else
 qianmian1=tiaojian1
end if

Function IsFile(FilePath)
	Set Fso=Server.CreateObject("Scri"&"pting.File"&"Sys"&"temObject")
	If (Fso.FileExists(Server.MapPath(FilePath))) Then
	IsFile=True
	Else
	IsFile=False
	End If
	Set Fso=Nothing
End Function

Function filekey(texts)
filekey=0
rekey="-/-\-%-@-.-"
keyes=split(rekey,"-")
nnnnn=Ubound(keyes)
For m=1 To Ubound(keyes)-1
rekeys=keyes(m)
rekeys=trim(rekeys)
if instr(texts,rekeys)>0 and len(rekeys)>0 then
filekey=filekey+1
end if
next
End Function

'�����ȡ�����ļ��б�ĺ���  
Function getSortedFiles(folderPath)  
    Dim rs, fso, folder, File  
    Const adInteger = 3  
    Const adDate = 7  
    Const adVarChar = 200  
    Set rs = Server.CreateObject("ADODB.Recordset")  
    Set fso = Server.CreateObject("Scripting.FileSystemObject")  
    Set folder = fso.GetFolder(folderPath)  
    Set fso = Nothing  
    With rs.Fields  
        .Append "Name", adVarChar, 200  
        .Append "Type", adVarChar, 200  
        .Append "DateCreated", adDate  
        .Append "DateLastAccessed", adDate  
        .Append "DateLastModified", adDate  
        .Append "Size", adInteger  
        .Append "TotalFileCount", adInteger  
    End With  
    rs.Open  
    For Each File In folder.Files  
        rs.AddNew  
        rs("Name") = File.Name  
        rs("Type") = File.Type  
        rs("DateCreated") = File.DateCreated  
        rs("DateLastAccessed") = File.DateLastAccessed  
        rs("DateLastModified") = File.DateLastModified  
        rs("Size") = File.Size  
        rs.Update  
    Next  
    '����������򣺰���������  
    rs.Sort = "DateLastModified DESC"  
    '��������������ΰ��ļ���С���򣬰��޸����ڵ���  
    'rs.Sort = "Size DESC, DateLastModified DESC"  
    rs.MoveFirst  
    Set folder = Nothing  
    Set getSortedFiles = rs  
End Function   
'==============================
'�� �� ���� AlertUrl(AlertStr,Url) 
'��    �ã������ת��ָ��ҳ��
'==============================
Function AlertUrl(AlertStr,Url) 
 Response.Write "<script>" &vbcrlf
 Response.Write "alert('"&AlertStr&"');" &vbcrlf
 Response.Write "location.href='"&Url&"';" &vbcrlf
 Response.Write "</script>" &vbcrlf
 Response.End()
End Function
'==============================
'�� �� ���� AlertBack(AlertStr)
'��    �ã�����󷵻���һҳ��
'==============================
Function AlertBack(AlertStr) 
 Response.Write "<script>" &vbcrlf
 Response.Write "alert('"&AlertStr&"');" &vbcrlf
 Response.Write "history.go(-1)" &vbcrlf
 Response.Write "</script>"&vbcrlf
 Response.End()
End Function

%>