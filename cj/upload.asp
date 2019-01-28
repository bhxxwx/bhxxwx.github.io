<!--#include file="UpLoad_Class.asp"-->
<%
dim upload
set upload = new AnUpLoad
upload.Exe = "*"
upload.MaxSize = 20 * 1024 * 1024 '20M
upload.GetData()
if upload.ErrorID>0 then 
	response.Write upload.Description
else
	dim file,savpath
	savepath = "成绩"
	for each frm in upload.forms("-1")
		response.Write frm & "=" & upload.forms(frm) & "<br />"
	next
	
	set file = upload.Files("file1")
	if file.isfile then
		result = file.saveToFile(savepath,1,true)
		if result then
			response.Write "文件'" & file.LocalName & "'上传成功，保存位置'" & server.MapPath(savepath & "/" & file.filename) & "',文件大小" & file.size & "字节<br />"
		else
			response.Write file.Exception & "<br />"
		end if
	end if
	
	set file = upload.Files_Muti("file1",1)
	if file.isfile then
		result = file.saveToFile(savepath,1,true)
		if result then
			response.Write "文件'" & file.LocalName & "'上传成功，保存位置'" & server.MapPath(savepath & "/" & file.filename) & "',文件大小" & file.size & "字节<br />"
		else
			response.Write file.Exception & "<br />"
		end if
	end if
	
	Response.Write "成功保存文件！"
end if
set upload = nothing
%>