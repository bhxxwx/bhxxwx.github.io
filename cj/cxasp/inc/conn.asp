<%
'修改以下几项后 无需修改其他内容


title="某某da中学成绩查询系统"			'设置查询标题,相信你懂的。

copysr="某某da中学"				'设置底部版权简短的文字,相信你懂的。
copysu="http://www.96448.cn/"			'设置底部版权连接完整网址,相信你懂的。

'设置查询条件
tiaojian1="姓名"				'汉字是列标题，跟excel一致

yanzhenma="0"					'是否使用验证码。填1使用0不用
UpDir="shujukufangzheli"			'设置数据库所在目录(文件夹名称),修改后相应更名对于文件夹。

'#########################################################
'修改以上几项后 无需修改以下内容
'#########################################################

'以下内容是系列查询系统导航，以后总能用到，敬请保留
'#########################################################
' 	1.	保密性不高：1个查询条件输对即可显示
' 	解决方案1：推荐我们的密码登录查询版
' 	自助开通试用: http://add.dbcha.com/  （先试用再购买）
' 	视频教程下载: http://down.12391.net/dbcha/
' 	解决方案2：购买两个或者三个查询条件组合查询版本
' 	购买地址：https://item.taobao.com/item.htm?id=45703415332
' 	解决方案3：公众号一对一绑定查询本人版
' 		购买地址：https://item.taobao.com/item.htm?id=528187132312 
'#########################################################
' 	2.	安全性不佳：.xls格式一般会被直接被下载
' 	解决方案1：修改conn.asp数据库路径为只有自己知道
' 	解决方案2：配置服务器让.xls文件不被下载
' 	解决方案3：购买我们的txt(.dat)格式版本
' 		购买地址：https://item.taobao.com/item.htm?id=45703415332
'#########################################################
' 	3.	并发性（性能）不高：适合单库3000条以内的查询
' 	解决方案1：购买asp+txt/xls版本（2万条）
' 		购买地址：https://item.taobao.com/item.htm?id=45703415332
' 	解决方案2：购买php+txt版本（8万条）
' 		购买地址：https://item.taobao.com/item.htm?id=45808268273 
' 	解决方案3：购买阿里云等优质独立服务器（配SSD硬盘）
'#########################################################
' 	4.	只适合电脑网页访问
' 	解决方案1：购买手机版网页版本
' 	购买地址：https://item.taobao.com/item.htm?id=45703415332
' 	解决方案2：购买按时间付费（在线版）
' 	自助开通试用: http://add.chafenba.com/  （先试用再购买）
' 	视频教程下载: http://down.12391.net/12391/
' 	购买地址：https://item.taobao.com/item.htm?id=520023732507 
'#########################################################
' 	5.	无后台管理功能：通过FTP管理
' 	解决方案1：购买后台版网页版本
' 	购买地址：https://item.taobao.com/item.htm?id=528692002051 
' 	解决方案2：购买按时间付费（在线版）
' 	自助开通试用: http://add.chafenba.com/  （先试用再购买）
' 	视频教程下载: http://down.12391.net/12391/
' 	购买地址：https://item.taobao.com/item.htm?id=520023732507 
'#########################################################
mdbtype=".xls" '只能是xls格式文件哦不要修改
' 	6.	需要模糊查询：这是输入内容与设置的查询条件列相等显示结果
' 	解决方案1：购买专用模糊查询版（多款）
' 	购买地址1：https://item.taobao.com/item.htm?id=520167788658  
' 	购买地址2：https://item.taobao.com/item.htm?id=540197845648 
' 	解决方案2：购买按时间付费（多款）
' 	自助开通试用: http://add.xuelikai.com/  （先试用再购买）
' 	购买地址：https://item.taobao.com/item.htm?id=520167788658  
'#########################################################
duan=tiaojian1
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
'#########################################################
' 	8.	不支持图片、网址、多表联查，当然都可以付费定制
' 	付费联系：https://aiyaha.taobao.com/ 电话(微信)：15058593138 admin@ewuyi.net
'#########################################################
if len(tiaojian1)=2 then
 qianmian1=left(tiaojian1,1)&"&nbsp;&nbsp;"&right(tiaojian1,1)
else
 qianmian1=tiaojian1
end if
' 	课表查询系统：https://item.taobao.com/item.htm?id=537645721513 
Function IsFile(FilePath)
 Set Fso=Server.CreateObject("Scri"&"pting.File"&"Sys"&"temObject")
 If (Fso.FileExists(Server.MapPath(FilePath))) Then
 IsFile=True
 Else
 IsFile=False
 End If
 Set Fso=Nothing
End Function
' 	推荐我们的密码登录查询版
' 	自助开通试用: http://add.dbcha.com/
' 	视频教程下载: http://down.12391.net/dbcha/
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
' 	微信公众号N选1个查询条件直接查询工资、成绩、水电费等
' 	自助开通试用：http://new.12391.net/ 
' 	全程视频教程：http://down.12391.net/WeiXinAdmin/ 
Function getSortedFiles(folderPath) 
' 	课表查询系统：https://item.taobao.com/item.htm?id=537645721513 
' 	多级联动版：https://item.taobao.com/item.htm?id=43263796985 
' 	发码、领码、随机抽奖、随机分班等: https://item.taobao.com/item.htm?id=525228396981 
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