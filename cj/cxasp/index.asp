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
 <!---div class="back" id="pageback"><a href="index.asp" class="d">返回</a></div---> 
 <!---<div class="menu" id="topmenus"><a href="http://add.dbcha.com/" class="d">后台</a></div>--->
</div><div class="main">
<%
startime=timer()

'以下内容是系列查询系统导航，以后总能用到，敬请保留
duansss="请输入你的"&duan
'#########################################################
' 	1.	保密性不高：1个查询条件输对即可显示
' 	解决方案1：推荐我们的密码登录查询版
' 	自助开通试用: http://add.dbcha.com/  （先试用再购买）
' 	视频教程下载: http://down.12391.net/dbcha/
' 	解决方案2：购买两个或者三个查询条件组合查询版本
' 	购买地址：https://item.taobao.com/item.htm?id=45703415332
' 	解决方案3：公众号一对一绑定查询本人版
' 		购买地址：https://item.taobao.com/item.htm?id=528187132312 
mamasss="请输入4数字验证码"
'#########################################################
' 	2.	安全性不佳：.xls格式一般会被直接被下载
' 	解决方案1：修改conn.asp数据库路径为只有自己知道
' 	解决方案2：配置服务器让.xls文件不被下载
' 	解决方案3：购买我们的txt(.dat)格式版本
' 		购买地址：https://item.taobao.com/item.htm?id=45703415332
names=""&trim(request("name"))&""
'#########################################################
' 	3.	并发性（性能）不高：适合单库3000条以内的查询
' 	解决方案1：购买asp+txt/xls版本（2万条）
' 		购买地址：https://item.taobao.com/item.htm?id=45703415332
' 	解决方案2：购买php+txt版本（8万条）
' 		购买地址：https://item.taobao.com/item.htm?id=45808268273 
' 	解决方案3：购买阿里云等优质独立服务器（配SSD硬盘）
codes=""&trim(request("code"))&""
'#########################################################
' 	4.	只适合电脑网页访问
' 	解决方案1：购买手机版网页版本
' 	购买地址：https://item.taobao.com/item.htm?id=45703415332
' 	解决方案2：购买按时间付费（在线版）
' 	自助开通试用: http://add.chafenba.com/  （先试用再购买）
' 	视频教程下载: http://down.12391.net/12391/
' 	购买地址：https://item.taobao.com/item.htm?id=520023732507 
times=""&trim(request("time"))&""
'#########################################################
' 	5.	无后台管理功能：通过FTP管理
' 	解决方案1：购买后台版网页版本
' 	购买地址：https://item.taobao.com/item.htm?id=528692002051 
' 	解决方案2：购买按时间付费（在线版）
' 	自助开通试用: http://add.chafenba.com/  （先试用再购买）
' 	视频教程下载: http://down.12391.net/12391/
' 	购买地址：https://item.taobao.com/item.htm?id=520023732507 
newtime = DateDiff("s","1970-1-1 0:0:0",Now())
'#########################################################
' 	6.	需要模糊查询：这是输入内容与设置的查询条件列相等显示结果
' 	解决方案1：购买专用模糊查询版（多款）
' 	购买地址1：https://item.taobao.com/item.htm?id=520167788658  
' 	购买地址2：https://item.taobao.com/item.htm?id=540197845648 
' 	解决方案2：购买按时间付费（多款）
' 	自助开通试用: http://add.xuelikai.com/  （先试用再购买）
' 	购买地址：https://item.taobao.com/item.htm?id=520167788658  
'#########################################################
' 	7.	必须公众号关注才可以查询的版本

' 	解决方案1：微信公众号N选1个查询条件直接查询工资、成绩、水电费等
' 	自助开通试用：http://new.12391.net/ 
' 	全程视频教程：http://down.12391.net/WeiXinAdmin/ 
' 	商业付费：https://item.taobao.com/item.htm?id=529624346797 
' 	特别用途：使用更适合版本

' 	网店发货查询系统后台导入通用版网页版加微信自动回复机器人查询
' 	即时开通试用:http://add.mabida.cn:1111/ 
' 	整体服务:https://item.taobao.com/item.htm?id=528166721835 
' 	源码购买:https://item.taobao.com/item.htm?id=44194950836 

' 	农产品质量溯源查询系统二维码防伪查询微信防伪查询
' 	即时开通试用:http://add.mabida.cn/ 
' 	整体服务:https://item.taobao.com/item.htm?id=43525422046 
' 	源码购买:https://item.taobao.com/item.htm?id=43525422046 

' 	代理查询、证书查询等其他查询
' 	即时开通试用:http://add.mabida.cn:3333/ 
' 	即时开通试用:http://add.mabida.cn:9999/ 
' 	课表查询系统：https://item.taobao.com/item.htm?id=537645721513 
' 	多级联动版：https://item.taobao.com/item.htm?id=43263796985 
' 	发码、领码、随机抽奖、随机分班等: https://item.taobao.com/item.htm?id=525228396981 

if times="" then
%><form name="queryForm" method="post" class="" action="?a=<%=newtime%>" onsubmit="return startRequest(0);">
<div class="select" id="10">
<select name="time" id="time" onBlur="startRequest(1)" />
<%
'付费版本按照时间排序：最新上传排最前面 
 response.write "<option value="""">请先选择要查询的类型</option>"&vbcrlf
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
mamas="+验证码"%>
<div class="so_box" id="33">
<input name="code" type="text" class="txts" id="code" value="<%=mamasss%>" placeholder="<%=mamasss%>" onfocus="this.value=''" onBlur="startRequest(3)" />
<div class="more" id="clearkey">
<img src="inc/Code.asp?t=<%=timer%>" id="Codes" onClick="this.src='inc/Code.asp?t='+new Date();"/>
</div></div><%end if%>
<div class="so_boxes">
<input type="submit" name="button" class="buts" id="sub" value="立即查询" />
</div>
<div class="so_boxex" id="tishi"><strong>相关说明: </strong>
选择对应查询后输入<%=duan%><%=mamas%>查询。
<!---你的其他说明在这里添加：开始--->
<!---你的其他说明在这里添加：结束--->
</div>
<div id="tishi1" style="display:none;"><%=duansss%></div>
<div id="tishi4" style="display:none;"><%=mamasss%></div>
</form>
<%
else
datas=""&UpDir&"/"&times&""&mdbtype
' 	发码、领码、随机抽奖、随机分班等: https://item.taobao.com/item.htm?id=525228396981 
if yanzhenma="1" then
if len(codes)<>4 or codes<>Session("GetCode") Then
' 	课表查询系统：https://item.taobao.com/item.htm?id=537645721513 
 call AlertBack("请输入正确的验证码哦！") 
End if
end if

if filekey(times)>0 then
 call AlertBack("请检查连接字串！")
end if

if len(names)<1 and len(names)>18 Then
 call AlertBack("请输入"&duan&"！") 
End if

if IsFile(datas)=True then
else
 call AlertBack("数据暂时没有上传或者不存在哦！") 
end if
'付费版本不必非得shee1表才可以查询
set conn=server.createobject("adodb.connection")
conn.open "driver={Microsoft Excel Driver (*.xls)};DBQ="&server.mappath(datas)
Response.Write "<!--startprint--><table cellspacing=""0"">"&vbcrlf
 Response.Write "<caption align='center'>"&times&" 查询结果</caption>"&vbcrlf
set rs=server.CreateObject("adodb.recordset")
'付费版本(asp+xls/excel)查询效率高5倍以上，特别是上万的大数据查询
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
 call AlertBack("请检查你设置的查询条件["&tiaojian1&"]是否存在！") 
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
 'Response.Write "<caption align='center'> 查询失败 </caption>"&vbcrlf
 Response.Write "<tr>"&vbcrlf
 Response.Write "<td colspan="""&lsd&""" align=""center"">"&vbcrlf
 Response.Write "<span>查询失败: 查询结果不存在！</span></td>"&vbcrlf
 Response.Write "</tr>"&vbcrlf
end if
'#########################################################
' 作者电话(微信)：15058593138 admin@ewuyi.net
'#########################################################
Response.Write "</table>"&vbcrlf
Response.Write "<!--endprint-->"&vbcrlf
%><div class="so_boxexe">
<input type="button" name="print" value="预览并打印" onclick="preview()" class="buts">
<input type="button" value="返 回" class="buts" onclick="location.href='index.asp';" id="reset"></div>
<%end if
endtime=timer()%></div>
<div class="foot">
 <div class="title">
 <span><a href="http://add.12391.net/" target="_blank">在线开通</a>&nbsp; &copy;<%=year(now)%>&nbsp;
 <!---
 更多版本请看:http://test.96448.cn/
 查询系统定制：https://aiyaha.taobao.com/
 ---> <a href="<%=copysu%>" target="_blank"><%=copysr%></a>
 </span>
 <!---页面执行时间：<%=FormatNumber((endtime-startime)*1000,3)%>毫秒--->
 </div>
</div>
</body>
</html><script type="text/javascript" src="../index_cha.js?v=ADA_W3T"></script>