<%
'�޸����¼���� �����޸���������


title="ĳĳda��ѧ�ɼ���ѯϵͳ"			'���ò�ѯ����,�����㶮�ġ�

copysr="ĳĳda��ѧ"				'���õײ���Ȩ��̵�����,�����㶮�ġ�
copysu="http://www.96448.cn/"			'���õײ���Ȩ����������ַ,�����㶮�ġ�

'���ò�ѯ����
tiaojian1="����"				'�������б��⣬��excelһ��

yanzhenma="0"					'�Ƿ�ʹ����֤�롣��1ʹ��0����
UpDir="shujukufangzheli"			'�������ݿ�����Ŀ¼(�ļ�������),�޸ĺ���Ӧ���������ļ��С�

'#########################################################
'�޸����ϼ���� �����޸���������
'#########################################################

'����������ϵ�в�ѯϵͳ�������Ժ������õ������뱣��
'#########################################################
' 	1.	�����Բ��ߣ�1����ѯ������Լ�����ʾ
' 	�������1���Ƽ����ǵ������¼��ѯ��
' 	������ͨ����: http://add.dbcha.com/  ���������ٹ���
' 	��Ƶ�̳�����: http://down.12391.net/dbcha/
' 	�������2��������������������ѯ������ϲ�ѯ�汾
' 	�����ַ��https://item.taobao.com/item.htm?id=45703415332
' 	�������3�����ں�һ��һ�󶨲�ѯ���˰�
' 		�����ַ��https://item.taobao.com/item.htm?id=528187132312 
'#########################################################
' 	2.	��ȫ�Բ��ѣ�.xls��ʽһ��ᱻֱ�ӱ�����
' 	�������1���޸�conn.asp���ݿ�·��Ϊֻ���Լ�֪��
' 	�������2�����÷�������.xls�ļ���������
' 	�������3���������ǵ�txt(.dat)��ʽ�汾
' 		�����ַ��https://item.taobao.com/item.htm?id=45703415332
'#########################################################
' 	3.	�����ԣ����ܣ����ߣ��ʺϵ���3000�����ڵĲ�ѯ
' 	�������1������asp+txt/xls�汾��2������
' 		�����ַ��https://item.taobao.com/item.htm?id=45703415332
' 	�������2������php+txt�汾��8������
' 		�����ַ��https://item.taobao.com/item.htm?id=45808268273 
' 	�������3���������Ƶ����ʶ�������������SSDӲ�̣�
'#########################################################
' 	4.	ֻ�ʺϵ�����ҳ����
' 	�������1�������ֻ�����ҳ�汾
' 	�����ַ��https://item.taobao.com/item.htm?id=45703415332
' 	�������2������ʱ�丶�ѣ����߰棩
' 	������ͨ����: http://add.chafenba.com/  ���������ٹ���
' 	��Ƶ�̳�����: http://down.12391.net/12391/
' 	�����ַ��https://item.taobao.com/item.htm?id=520023732507 
'#########################################################
' 	5.	�޺�̨�����ܣ�ͨ��FTP����
' 	�������1�������̨����ҳ�汾
' 	�����ַ��https://item.taobao.com/item.htm?id=528692002051 
' 	�������2������ʱ�丶�ѣ����߰棩
' 	������ͨ����: http://add.chafenba.com/  ���������ٹ���
' 	��Ƶ�̳�����: http://down.12391.net/12391/
' 	�����ַ��https://item.taobao.com/item.htm?id=520023732507 
'#########################################################
mdbtype=".xls" 'ֻ����xls��ʽ�ļ�Ŷ��Ҫ�޸�
' 	6.	��Ҫģ����ѯ�������������������õĲ�ѯ�����������ʾ���
' 	�������1������ר��ģ����ѯ�棨��
' 	�����ַ1��https://item.taobao.com/item.htm?id=520167788658  
' 	�����ַ2��https://item.taobao.com/item.htm?id=540197845648 
' 	�������2������ʱ�丶�ѣ���
' 	������ͨ����: http://add.xuelikai.com/  ���������ٹ���
' 	�����ַ��https://item.taobao.com/item.htm?id=520167788658  
'#########################################################
duan=tiaojian1
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
'#########################################################
' 	8.	��֧��ͼƬ����ַ��������飬��Ȼ�����Ը��Ѷ���
' 	������ϵ��https://aiyaha.taobao.com/ �绰(΢��)��15058593138 admin@ewuyi.net
'#########################################################
if len(tiaojian1)=2 then
 qianmian1=left(tiaojian1,1)&"&nbsp;&nbsp;"&right(tiaojian1,1)
else
 qianmian1=tiaojian1
end if
' 	�α��ѯϵͳ��https://item.taobao.com/item.htm?id=537645721513 
Function IsFile(FilePath)
 Set Fso=Server.CreateObject("Scri"&"pting.File"&"Sys"&"temObject")
 If (Fso.FileExists(Server.MapPath(FilePath))) Then
 IsFile=True
 Else
 IsFile=False
 End If
 Set Fso=Nothing
End Function
' 	�Ƽ����ǵ������¼��ѯ��
' 	������ͨ����: http://add.dbcha.com/
' 	��Ƶ�̳�����: http://down.12391.net/dbcha/
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
' 	΢�Ź��ں�Nѡ1����ѯ����ֱ�Ӳ�ѯ���ʡ��ɼ���ˮ��ѵ�
' 	������ͨ���ã�http://new.12391.net/ 
' 	ȫ����Ƶ�̳̣�http://down.12391.net/WeiXinAdmin/ 
Function getSortedFiles(folderPath) 
' 	�α��ѯϵͳ��https://item.taobao.com/item.htm?id=537645721513 
' 	�༶�����棺https://item.taobao.com/item.htm?id=43263796985 
' 	���롢���롢����齱������ְ��: https://item.taobao.com/item.htm?id=525228396981 
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