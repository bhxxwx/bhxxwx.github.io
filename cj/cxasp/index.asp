<!--#include file="inc/conn.asp"--><%host=lcase(request.servervariables("HTTP_HOST"))%>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
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

'����������ϵ�в�ѯϵͳ�������Ժ������õ������뱣��
duansss="���������"&duan
'#########################################################
' 	1.	�����Բ��ߣ�1����ѯ������Լ�����ʾ
' 	�������1���Ƽ����ǵ������¼��ѯ��
' 	������ͨ����: http://add.dbcha.com/  ���������ٹ���
' 	��Ƶ�̳�����: http://down.12391.net/dbcha/
' 	�������2��������������������ѯ������ϲ�ѯ�汾
' 	�����ַ��https://item.taobao.com/item.htm?id=45703415332
' 	�������3�����ں�һ��һ�󶨲�ѯ���˰�
' 		�����ַ��https://item.taobao.com/item.htm?id=528187132312 
mamasss="������4������֤��"
'#########################################################
' 	2.	��ȫ�Բ��ѣ�.xls��ʽһ��ᱻֱ�ӱ�����
' 	�������1���޸�conn.asp���ݿ�·��Ϊֻ���Լ�֪��
' 	�������2�����÷�������.xls�ļ���������
' 	�������3���������ǵ�txt(.dat)��ʽ�汾
' 		�����ַ��https://item.taobao.com/item.htm?id=45703415332
names=""&trim(request("name"))&""
'#########################################################
' 	3.	�����ԣ����ܣ����ߣ��ʺϵ���3000�����ڵĲ�ѯ
' 	�������1������asp+txt/xls�汾��2������
' 		�����ַ��https://item.taobao.com/item.htm?id=45703415332
' 	�������2������php+txt�汾��8������
' 		�����ַ��https://item.taobao.com/item.htm?id=45808268273 
' 	�������3���������Ƶ����ʶ�������������SSDӲ�̣�
codes=""&trim(request("code"))&""
'#########################################################
' 	4.	ֻ�ʺϵ�����ҳ����
' 	�������1�������ֻ�����ҳ�汾
' 	�����ַ��https://item.taobao.com/item.htm?id=45703415332
' 	�������2������ʱ�丶�ѣ����߰棩
' 	������ͨ����: http://add.chafenba.com/  ���������ٹ���
' 	��Ƶ�̳�����: http://down.12391.net/12391/
' 	�����ַ��https://item.taobao.com/item.htm?id=520023732507 
times=""&trim(request("time"))&""
'#########################################################
' 	5.	�޺�̨�����ܣ�ͨ��FTP����
' 	�������1�������̨����ҳ�汾
' 	�����ַ��https://item.taobao.com/item.htm?id=528692002051 
' 	�������2������ʱ�丶�ѣ����߰棩
' 	������ͨ����: http://add.chafenba.com/  ���������ٹ���
' 	��Ƶ�̳�����: http://down.12391.net/12391/
' 	�����ַ��https://item.taobao.com/item.htm?id=520023732507 
newtime = DateDiff("s","1970-1-1 0:0:0",Now())
'#########################################################
' 	6.	��Ҫģ����ѯ�������������������õĲ�ѯ�����������ʾ���
' 	�������1������ר��ģ����ѯ�棨��
' 	�����ַ1��https://item.taobao.com/item.htm?id=520167788658  
' 	�����ַ2��https://item.taobao.com/item.htm?id=540197845648 
' 	�������2������ʱ�丶�ѣ���
' 	������ͨ����: http://add.xuelikai.com/  ���������ٹ���
' 	�����ַ��https://item.taobao.com/item.htm?id=520167788658  
'#########################################################
' 	7.	���빫�ںŹ�ע�ſ��Բ�ѯ�İ汾

' 	�������1��΢�Ź��ں�Nѡ1����ѯ����ֱ�Ӳ�ѯ���ʡ��ɼ���ˮ��ѵ�
' 	������ͨ���ã�http://new.12391.net/ 
' 	ȫ����Ƶ�̳̣�http://down.12391.net/WeiXinAdmin/ 
' 	��ҵ���ѣ�https://item.taobao.com/item.htm?id=529624346797 
' 	�ر���;��ʹ�ø��ʺϰ汾

' 	���귢����ѯϵͳ��̨����ͨ�ð���ҳ���΢���Զ��ظ������˲�ѯ
' 	��ʱ��ͨ����:http://add.mabida.cn:1111/ 
' 	�������:https://item.taobao.com/item.htm?id=528166721835 
' 	Դ�빺��:https://item.taobao.com/item.htm?id=44194950836 

' 	ũ��Ʒ������Դ��ѯϵͳ��ά���α��ѯ΢�ŷ�α��ѯ
' 	��ʱ��ͨ����:http://add.mabida.cn/ 
' 	�������:https://item.taobao.com/item.htm?id=43525422046 
' 	Դ�빺��:https://item.taobao.com/item.htm?id=43525422046 

' 	�����ѯ��֤���ѯ��������ѯ
' 	��ʱ��ͨ����:http://add.mabida.cn:3333/ 
' 	��ʱ��ͨ����:http://add.mabida.cn:9999/ 
' 	�α��ѯϵͳ��https://item.taobao.com/item.htm?id=537645721513 
' 	�༶�����棺https://item.taobao.com/item.htm?id=43263796985 
' 	���롢���롢����齱������ְ��: https://item.taobao.com/item.htm?id=525228396981 

if times="" then
%><form name="queryForm" method="post" class="" action="?a=<%=newtime%>" onsubmit="return startRequest(0);">
<div class="select" id="10">
<select name="time" id="time" onBlur="startRequest(1)" />
<%
'���Ѱ汾����ʱ�����������ϴ�����ǰ�� 
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
ѡ���Ӧ��ѯ������<%=duan%><%=mamas%>��ѯ��
<!---�������˵����������ӣ���ʼ--->
<!---�������˵����������ӣ�����--->
</div>
<div id="tishi1" style="display:none;"><%=duansss%></div>
<div id="tishi4" style="display:none;"><%=mamasss%></div>
</form>
<%
else
datas=""&UpDir&"/"&times&""&mdbtype
' 	���롢���롢����齱������ְ��: https://item.taobao.com/item.htm?id=525228396981 
if yanzhenma="1" then
if len(codes)<>4 or codes<>Session("GetCode") Then
' 	�α��ѯϵͳ��https://item.taobao.com/item.htm?id=537645721513 
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
'���Ѱ汾���طǵ�shee1��ſ��Բ�ѯ
set conn=server.createobject("adodb.connection")
conn.open "driver={Microsoft Excel Driver (*.xls)};DBQ="&server.mappath(datas)
Response.Write "<!--startprint--><table cellspacing=""0"">"&vbcrlf
 Response.Write "<caption align='center'>"&times&" ��ѯ���</caption>"&vbcrlf
set rs=server.CreateObject("adodb.recordset")
'���Ѱ汾(asp+xls/excel)��ѯЧ�ʸ�5�����ϣ��ر�������Ĵ����ݲ�ѯ
rs.open "select * from [sheet1$]",conn,1,1
Response.Write "<tr class=""tt"">"&vbcrlf
 lsd = rs.Fields.Count
    For x3=0 To rs.Fields.Count-1
       tnames=tnames&"---"&rs.Fields(x3).Name&"---"
       Response.Write "<td>" & rs.Fields(x3).Name & "</td>"&vbcrlf
    Next
Response.Write "</tr>"&vbcrlf
if instr(tnames,"---"&tiaojian1&"---")>0 then
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
'#########################################################
' ���ߵ绰(΢��)��15058593138 admin@ewuyi.net
'#########################################################
Response.Write "</table>"&vbcrlf
Response.Write "<!--endprint-->"&vbcrlf
%><div class="so_boxexe">
<input type="button" name="print" value="Ԥ������ӡ" onclick="preview()" class="buts">
<input type="button" value="�� ��" class="buts" onclick="location.href='index.asp';" id="reset"></div>
<%end if
endtime=timer()%></div>
<div class="foot">
 <div class="title">
 <span><a href="http://add.12391.net/" target="_blank">���߿�ͨ</a>&nbsp; &copy;<%=year(now)%>&nbsp;
 <!---
 ����汾�뿴:http://test.96448.cn/
 ��ѯϵͳ���ƣ�https://aiyaha.taobao.com/
 ---> <a href="<%=copysu%>" target="_blank"><%=copysr%></a>
 </span>
 <!---ҳ��ִ��ʱ�䣺<%=FormatNumber((endtime-startime)*1000,3)%>����--->
 </div>
</div>
</body>
</html><script type="text/javascript" src="../index_cha.js?v=ADA_W3T"></script>