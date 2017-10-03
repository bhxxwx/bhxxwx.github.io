<%
'修改以下几项后 无需修改其他内容


title="滨淮中心小学成绩查询系统"			'设置查询标题,相信你懂的。

copysr="滨淮中心小学"				'设置底部版权简短的文字,相信你懂的。
copysu="http://www.96448.cn/"			'设置底部版权连接完整网址,相信你懂的。

'设置查询条件
tiaojian1="姓名"				'汉字是列标题，跟excel一致
tiaojian2="学号"
yanzhenma="1"					'是否使用验证码。填1使用0不用
UpDir="shujukufangzheli"			'设置数据库所在目录(文件夹名称),修改后相应更名对于文件夹。

mdbtype=".xls" '只能是xls格式文件哦不要修改

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