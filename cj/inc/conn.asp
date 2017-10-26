<%
UpDir="成绩"			'设置数据库所在目录(文件夹名称)。
title="滨淮中心小学成绩查询系统"	'设置查询标题,相信你懂的。
copysr="滨淮中心小学"	'设置底部版权文字,相信你懂的。
copysu="http://bhxxwx.github.io/2/2.html"	'设置底部版权连接,相信你懂的。

'设置查询条件
tiaojian1="姓名"  		'汉字是列标题，跟excel一致
yanzhenma="1"  		'是否使用验证码。填1使用0不用

usename="admin@wuyi.net"			'后台用户名(邮箱格式)
usepass="2532525454"				'后台密码

'设置查询条件无需修改以下内容
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

'定义获取排序文件列表的函数  
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
    '设置排序规则：按名称排序  
    rs.Sort = "DateLastModified DESC"  
    '设置排序规则：依次按文件大小倒序，按修改日期倒序  
    'rs.Sort = "Size DESC, DateLastModified DESC"  
    rs.MoveFirst  
    Set folder = Nothing  
    Set getSortedFiles = rs  
End Function   
'==============================
'函 数 名： AlertUrl(AlertStr,Url) 
'作    用：警告后转入指定页面
'==============================
Function AlertUrl(AlertStr,Url) 
 Response.Write "<script>" &vbcrlf
 Response.Write "alert('"&AlertStr&"');" &vbcrlf
 Response.Write "location.href='"&Url&"';" &vbcrlf
 Response.Write "</script>" &vbcrlf
 Response.End()
End Function
'==============================
'函 数 名： AlertBack(AlertStr)
'作    用：警告后返回上一页面
'==============================
Function AlertBack(AlertStr) 
 Response.Write "<script>" &vbcrlf
 Response.Write "alert('"&AlertStr&"');" &vbcrlf
 Response.Write "history.go(-1)" &vbcrlf
 Response.Write "</script>"&vbcrlf
 Response.End()
End Function

%>