<!--#include file="UpLoad_Class.asp"-->
<%
dim upload
set upload = new AnUpLoad
upload.Exe = "jpg|bmp|jpeg|gif|png|sql|txt"
upload.MaxSize = 2 * 1024 * 1024 '2M
upload.GetData()
if upload.ErrorID>0 then 
	response.Write upload.Description
else
	dim file,savpath
	savepath = "upload"
	response.Write "��ѡ��:" & upload.forms("c1") & "<br />"
	response.Write "��ѡ��:" & upload.forms("r1") & "<br />"
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