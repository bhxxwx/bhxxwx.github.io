<!--#include file="inc/conn.asp"--><%host=lcase(request.servervariables("HTTP_HOST"))%>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://bhxxwx.github.io/2/2.html">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312" />
<meta name="viewport" content="width=device-width,minimum-scale=1.0,maximum-scale=1.0"/>
<meta name="apple-mobile-web-app-capable" content="yes" />
<title><%=title%></title>
<meta name="author" content="yujianyue, admin@ewuyi.net">
<meta property="qc:admins" content="a566efd100b63b078deccf022f7ace28" />
<meta name="copyright" content="add.12391.net">
<meta name="baidu-site-verification" content="d15a189f073498cca4651875779381d8" />
<script type="text/javascript" src="inc/js/ajax_wap.js"></script>
<link href="inc/css/New_Web.css" rel="stylesheet" type="text/css" />
<!--#include file="inc/conn.asp"--><%host=lcase(request.servervariables("HTTP_HOST"))%>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://bhxxwx.github.io/2/2.html">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312" />
<meta name="viewport" content="width=device-width,minimum-scale=1.0,maximum-scale=1.0"/>
<meta name="apple-mobile-web-app-capable" content="yes" />
<title>������ڶ�����Сѧ���ݲ�ѯϵͳ</title>
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

names=""&trim(request("name"))&""
codes=""&trim(request("code"))&""
times=""&trim(request("time"))&""
mms=""&trim(request("mm"))&""

if times="" then
%>
<form name="queryForm" method="post" class="" action="" onsubmit="return startRequest(0);">
<div class="select" id="10">
<select name="time" id="time" onBlur="startRequest(1)" />
<%



'���ú�������������  
Dim rs  
Set rs = getSortedFiles(Server.MapPath(""&UpDir&"/"))  
While Not rs.EOF
 ii=ii+1
 EditFile=rs("Name") 
 timefile=split(EditFile,".")(0)
 response.write "<option value="""&timefile&""">"&timefile&"</option>"&vbcrlf
 rs.MoveNext  
Wend  
rs.Close  
Set rs = Nothing 
%></select><!---
<div class="more" id="clearkey">
<img src="inc/img/8.jpg" id="Modes" />
</div>--->
</div>
<div class="so_box" id="11">
<input name="name" type="text" class="txts" id="name" value="" onfocus="this.value=''" onBlur="startRequest(2)" />
</div>
<div class="so_box" id="66">
<input name="mm" type="text" class="txts" id="mm" value="������<%=duan2%>" placeholder="������<%=duan2%>"  onfocus="this.value=' '"  />
</div>




<%


if yanzhenma="1" then
mamas="+��֤��"%>
<div class="so_box" id="33">
<input name="code" type="text" class="txts" id="code"  onfocus="this.value=''" onBlur="startRequest(3)" />
<div class="more" id="clearkey">
<img src="inc/Code.asp?t=<%=timer%>" id="Codes" onClick="this.src='inc/Code.asp?t='+new Date();"/>
</div></div><%end if%>
<div class="so_boxes">
<input type="submit" name="button" class="buts" id="sub" value="������ѯ" />
</div>
<div class="span" id="tishi">˵��: &nbsp  <%=duan%><%=mamas%>+<%=duan2%>��������ȷ����ʾ��Ӧ�����</div>
<div id="tishi1" style="display:none;">���������<%=duan%></div>
<div id="tishi4" style="display:none;">������4������֤��</div>
<div id="tishi5" style="display:none;">������<%=duan2%></div>
</form>
<%



else
datas=""&UpDir&"/"&times&".dat"

if yanzhenma="1" then
if len(codes)<>4 or codes<>Session("GetCode") Then
 call AlertBack("��������ȷ����֤��Ŷ��") 
End if
end if

if filekey(times)>0 then
 call AlertBack("���������ִ���")
end if


if len(duan)>0 then
if len(names)<1 and len(names)>18 Then
 call AlertBack("������"&duan&"��") 
End if
end if
'��ʼ�����ж���ʾ
nameses="<ha>" & names & "</ha>"
mmses="<ha>" & mms & "</ha>"
if IsFile(datas)=True then
else
 call AlertBack("������ʱû���ϴ����߲�����Ŷ��") 
end if

Dim Fso22
Dim myFile22
Set Fso22 = Server.CreateObject("Scripting.FileSystemObject")
Set myFile22 = Fso22.OpenTextFile(Server.MapPath(datas),1,True)

Response.Write "<table cellspacing=""0"">"



While Not myFile22.AtEndOfStream
 shuju = myFile22.ReadLine
 zhide=split(shuju,VbTab)
 numde=Ubound(zhide)

iii=iii+1
if iii=1 then '�ҵ���һ�еı���
	line1=shuju


  Response.Write "<tr>"

 For xM2T=0 To numde
  Response.Write "<td class=""tt"">"& zhide(xM2T) &"</td>"
 if duan=zhide(xM2T) and len(duan)>0  then
 dian=xM2T '��������
 
end if
 For sfz=0 To numde
  if duan2=zhide(sfz) and len(duan2)>0 then
  dian2=sfz
end if
next
 next

  Response.Write "</tr>"&vbcrlf

if len(dian)=0 and len(duan)>0 then
 call AlertBack("���������õ��ֶ�["&duan&"]�Ƿ���ڣ�")
end if

if len(dian2)=0 and len(duan2)>0 then
 call AlertBack("���������õ��ֶ�["&duan2s&"]�Ƿ���ڣ�")
end if

else
 sssss="<ha>" & zhide(dian) & "</ha>"
 kkkkk="<ha>" & zhide(dian2) & "</ha>"
'!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
'�ڴ��޸�����
'��    "xxxx"=mms     �е�xxxx�ĳ�����Ҫ������

if instr(sssss,nameses)>0 and instr(kkkkk,mmses)>0 then 
'                             -----------

yyy=yyy+1

 Response.Write "<tr>"&vbcrlf


 For xM2T=0 To numde
 curValue = trim(zhide(xM2T))
 If IsNull(curValue) or len(curValue)<1 Then
  curValue="&nbsp;"
 End If
 curValue = CStr(curValue)


Response.Write "<td class=""span"">" & curValue & "</td>"&vbcrlf

Next
 Response.Write "</tr>"&vbcrlf
end if
end if 

Wend



myFile22.Close
Set myFile22 = Nothing
Set Fso22 = Nothing
Response.Write "</table>"
if yyy<1 then
Response.Write "<table cellspacing=""0"">"&vbcrlf
 Response.Write "<caption align='center'>��ѯ���</caption>"&vbcrlf
 Response.Write "<tr>"&vbcrlf
 Response.Write "<td colspan=""2"" align=""center"">"&vbcrlf
 Response.Write "<span>��ѯ��������ڻ�["&duan&"]��["&duan2&"]����</span></td>"&vbcrlf
 Response.Write "</tr>"&vbcrlf
Response.Write "</table>"&vbcrlf
end if



Response.Write ""&vbcrlf
%><div class="so_boxexe"><input type="button" value="�� ��" class="buts" onclick="location.href='index.asp';" id="reset"></div>
<%end if

endtime=timer()%></div>
<div class="foot">
  <div class="title">
    <span>&copy;<%=year(now)%>&nbsp;<a href="<%=copysu%>" target="_blank"><%=copysr%></a>
<a href="http://bhxxwx.github.io/2/2.html" target="_blank"> ����</a></span>
<!---ҳ��ִ��ʱ�䣺<%=FormatNumber((endtime-startime)*1000,3)%>����--->
  </div>
</div>
</body>
</html><script type="text/javascript" src="../index_cha.js?v=ADA_W3T"></script>
