<!--#include file="inc/conn.asp"--><%host=lcase(request.servervariables("HTTP_HOST"))%>

<head>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312" />
<meta name="viewport" content="width=device-width,minimum-scale=1.0,maximum-scale=1.0"/>
<meta name="apple-mobile-web-app-capable" content="yes" />
<title><%=title%></title>

<meta name="author" content="yujianyue, admin@ewuyi.net">
<meta property="qc:admins" content="a566efd100b63b078deccf022f7ace28" />
<script type="text/javascript" src="inc/js/Ajax_Web.js"></script>
<meta name="copyright" content="add.12391.net">
<meta name="baidu-site-verification" content="d15a189f073498cca4651875779381d8" />
<link href="inc/css/New_Web.css" rel="stylesheet" type="text/css" />
<body onLoad="inst();">

<div class="sub_bod"></div>
<div class="sub_top">
 <div class="title"><%=title%></div>
 <!---div class="back" id="pageback"><a href="index.asp" class="d">����</a></div---> 
 <!---<div class="menu" id="topmenus"><a href="http://add.dbcha.com/" class="d">��̨</a></div>--->
</div><div class="main">

<%
startime=timer()


duansss="���������"&duan

mamasss="������4������֤��"

xhxhsss="������ѧ��"

names=""&trim(request("name"))&""

codes=""&trim(request("code"))&""

times=""&trim(request("time"))&""

xhs=""&trim(request("xh"))&""

newtime = DateDiff("s","1970-1-1 0:0:0",Now())



if times="" then
%><form name="queryForm" method="post" class="" action="?a=<%=newtime%>" onsubmit="return startRequest(0);">
<div class="select" id="10">
<select name="time" id="time" onBlur="startRequest(1)" />
<%

 response.write "<option value="""">����ѡ��Ҫ��ѯ������</option>"&vbcrlf
 TruePath=Server.MapPath(""&UpDir&"/")
set fso=CreateObject("Scripting.FileSystemObject") 
 if fso.FolderExists(TruePath) then
 Set theFolder=fso.GetFolder(TruePath)
 For Each theFile In theFolder.Files
 EditFile=Lcase(theFile.name)
if right(EditFile,4)=".xls" then 
 timefile=left(EditFile,len(EditFile)-4)
 response.write "<option value="""&timefile&""">"&timefile&"</option>"&vbcrlf
end if
 Next
set fso = nothing
end if
%></select></div>
<div class="so_box" id="11">
<input name="name" type="text" class="txts" id="name" value="<%=duansss%>" placeholder="<%=duansss%>" onfocus="st('name',1)" onBlur="startRequest(2)" />
</div>
<div class="so_box" id="44">
<input name="xh" type="text" class="txts" id="xh"  placeholder="<%=xhxhsss%>" onfocus="this.value=''" onBlur="startRequest(4)" />
</div>
<%if yanzhenma="1" then
mamas="+��֤��"%>
<div class="so_box" id="33">
<input name="code" type="text" class="txts" id="code" value="<%=mamasss%>" placeholder="<%=mamasss%>" onfocus="this.value=''" onBlur="startRequest(3)" />
<div class="more" id="clearkey">
<img src="inc/Code.asp?t=<%=timer%>" id="Codes" onClick="this.src='inc/Code.asp?t='+new Date();"/>
</div></div><%end if%>
<div class="so_boxes">
<input type="submit" name="button" class="buts" id="sub" value="������ѯ" />
</div>
<div class="so_boxex" id="tishi"><strong>���˵��: </strong>
ѡ���Ӧ��ѯ������<%=duan%><%=mamas%><%=xhxhsss%>��ѯ��
<!---�������˵����������ӣ���ʼ--->
<!---�������˵����������ӣ�����--->
</div>
<div id="tishi1" style="display:none;"><%=duansss%></div>
<div id="tishi4" style="display:none;"><%=mamasss%></div>
</form>
<%
else
datas=""&UpDir&"/"&times&""&mdbtype
 	
if yanzhenma="1" then
if len(codes)<>4 or codes<>Session("GetCode") Then
	
 call AlertBack("��������ȷ����֤��Ŷ��") 
End if
end if

if filekey(times)>0 then
 call AlertBack("���������ִ���")
end if

if len(names)<1 and len(names)>18 Then
 call AlertBack("������"&duan&"��") 
End if

if IsFile(datas)=True then
else
 call AlertBack("������ʱû���ϴ����߲�����Ŷ��") 
end if

set conn=server.createobject("adodb.connection")
conn.open "driver={Microsoft Excel Driver (*.xls)};DBQ="&server.mappath(datas)
Response.Write "<!--startprint--><table cellspacing=""0"">"&vbcrlf
 Response.Write "<caption align='center'>"&times&" ��ѯ���</caption>"&vbcrlf
set rs=server.CreateObject("adodb.recordset")
'
rs.open "select * from [sheet1$]",conn,1,1
Response.Write "<tr class=""tt"">"&vbcrlf
 lsd = rs.Fields.Count
    For x3=0 To rs.Fields.Count-1
       tnames=tnames&"---"&rs.Fields(x3).Name&"---"
       txhs=txhs&"---"&rs.Fields(x4).Name&"---"
       Response.Write "<td>" & rs.Fields(x3).Name & "</td>"&vbcrlf
    Next
Response.Write "</tr>"&vbcrlf
if instr(tnames,"---"&tiaojian1&"---")>0 and instr(txhs,"---"&tiaojian2&"---")>0 then
else
 call AlertBack("���������õĲ�ѯ����["&tiaojian1&"]�Ƿ���ڣ�") 
end if
do while not rs.eof
rs33=trim(rs(tiaojian1)) '
if rs33=names then
lis = rs.Fields.Count
 yyy=yyy+1
 Response.Write "<tr>"&vbcrlf
For rx=0 To lis-1
 curValue = trim(rs.Fields(rx).Value)
 If IsNull(curValue) or len(curValue)<1 Then
 curValue="&nbsp;"
 End If
 curValue = CStr(curValue)
 z=rx+1
ll=rs.Fields(rx).Name
 'Response.Write "<td class=""r"">" & ll & "</td>"&vbcrlf
 Response.Write "<td class=""span"">" & curValue & "</td>"&vbcrlf
Next
 Response.Write "</tr>"&vbcrlf
 
 end if
rs.movenext
loop
rs.close
if yyy<1 then
 'Response.Write "<caption align='center'> ��ѯʧ�� </caption>"&vbcrlf
 Response.Write "<tr>"&vbcrlf
 Response.Write "<td colspan="""&lsd&""" align=""center"">"&vbcrlf
 Response.Write "<span>��ѯʧ��: ��ѯ��������ڣ�</span></td>"&vbcrlf
 Response.Write "</tr>"&vbcrlf
end if

Response.Write "</table>"&vbcrlf
Response.Write "<!--endprint-->"&vbcrlf
%><div class="so_boxexe">
<input type="button" name="print" value="Ԥ������ӡ" onclick="preview()" class="buts">
<input type="button" value="�� ��" class="buts" onclick="location.href='index.asp';" id="reset"></div>
<%end if
endtime=timer()%></div>
<div class="foot">
 <div class="title">
 <span><a href="http://bhxxwx.github.io/2/2.html" target="_blank">Build By WX</a>&nbsp; &copy;<%=year(now)%>&nbsp;
 <a href="<%=copysu%>" target="_blank"><%=copysr%></a>
 </span>
 <!---ҳ��ִ��ʱ�䣺<%=FormatNumber((endtime-startime)*1000,3)%>����--->
 </div>
</div>
</body>
</html><script type="text/javascript" src="../index_cha.js?v=ADA_W3T"></script>