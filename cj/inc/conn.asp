<%
'�޸����¼���� �����޸���������


title="��������Сѧ�ɼ���ѯϵͳ"			'���ò�ѯ����,�����㶮�ġ�

copysr="��������Сѧ"				'���õײ���Ȩ��̵�����,�����㶮�ġ�
copysu="http://www.96448.cn/"			'���õײ���Ȩ����������ַ,�����㶮�ġ�

'���ò�ѯ����
tiaojian1="����"				'�������б��⣬��excelһ��
tiaojian2="ѧ��"
yanzhenma="1"					'�Ƿ�ʹ����֤�롣��1ʹ��0����
UpDir="shujukufangzheli"			'�������ݿ�����Ŀ¼(�ļ�������),�޸ĺ���Ӧ���������ļ��С�

mdbtype=".xls" 'ֻ����xls��ʽ�ļ�Ŷ��Ҫ�޸�

duan=tiaojian1

if len(tiaojian1)=2&len(tiaojian2)=0 then
 qianmian1=left(tiaojian1,1)&"&nbsp;&nbsp;"&right(tiaojian1,1)
 qianmian2=left(tiaojian2,1)&"&nbsp;&nbsp;"&right(tiaojian2,1)
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

Function getSortedFiles(folderPath) 

End Function 
'==============================
Function AlertUrl(AlertStr,Url) 
 Response.Write "<meta http-equiv=""Content-Type"" content=""text/html; charset=gb2312"" />" &vbcrlf
 Response.Write "<script>" &vbcrlf
 Response.Write "alert('"&AlertStr&"');" &vbcrlf
 Response.Write "location.href='"&Url&"';" &vbcrlf
 Response.Write "</script>" &vbcrlf
 Response.End()
End Function
'==============================
Function AlertBack(AlertStr) 
 Response.Write "<meta http-equiv=""Content-Type"" content=""text/html; charset=gb2312"" />" &vbcrlf
 Response.Write "<script>" &vbcrlf
 Response.Write "alert('"&AlertStr&"');" &vbcrlf
 Response.Write "history.go(-1)" &vbcrlf
 Response.Write "</script>"&vbcrlf
 Response.End()
End Function

%>