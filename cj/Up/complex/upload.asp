<!--#include file="UpLoad_Class.asp"-->
<%
dim upload
set upload = new AnUpLoad
upload.Exe = "*"
upload.MaxSize = 2 * 1024 * 1024 '2M
upload.GetData()
if upload.ErrorID>0 then 
	response.Write upload.Description
else
	response.Write "�ı���:" & upload.forms("text1") & "<br />"
	response.Write "�ı���:" & upload.forms("textarea1") & "<br />"
	dim file,savpath
	savepath = "upload"
	set file = upload.files("file1")
	if file.isfile then
		result = file.saveToFile(savepath,0,true)
		if result then
			response.Write "�ļ�'" & file.LocalName & "'�ϴ��ɹ�������λ��'" & server.MapPath(savepath & "/" & file.filename) & "',�ļ���С" & file.size & "�ֽ�"
		else
			response.Write file.Exception
		end if
	end if
end if
set upload = nothing
%>