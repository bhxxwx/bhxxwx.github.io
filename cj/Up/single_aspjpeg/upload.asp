<!--#include file="UpLoad_Class.asp"-->
<%
dim upload
set upload = new AnUpLoad
upload.Exe = "jpg|bmp|jpeg|gif|png"
upload.MaxSize = 2 * 1024 * 1024 '2M
upload.GetData()
if upload.ErrorID>0 then 
	response.Write upload.Description
else
	dim file,savpath
	savepath = "upload"
	set file = upload.files("file1")
	if file.isfile then
		jo_Canvas file.getbytes(),server.MapPath("upload/" & file.newname)
		response.Write "ˮӡ��ӳɹ�"
	end if
end if
set upload = nothing

function jo_Canvas(data,savepath)
	'����ԭʼͼƬ
	Set jpeg = Server.CreateObject("Persits.Jpeg")
	jpeg.RegKey="48958-77556-02411"
	jpeg.OpenBinary data
	width = jpeg.width
	height= jpeg.height
	jpeg.Quality=100

	'����ˮӡͼƬ
	set jpeg1 = Server.CreateObject("Persits.Jpeg")
	jpeg1.RegKey="48958-77556-02411"
	jpeg1.open server.MapPath("cloud1.jpg")  'ˮӡͼƬ
	jpeg1.Quality=100
	w1 = jpeg1.width
	h1 = jpeg1.height
	jpeg.DrawImage (width-w1-20),(height-h1-20),jpeg1,0.5,&Hff0000   '����20Ϊ�ұ߾���±߾�
	jpeg1.close
	set jpeg1 = nothing
	
	'ˮӡ����
	jpeg.Canvas.font.color=&HFFFFFF   '������ɫ
	jpeg.Canvas.font.Family = "����"   '����
	jpeg.Canvas.font.ShadowColor = &H000000   '��Ӱ��ɫ
	jpeg.Canvas.font.ShadowXoffset = 1   '��Ӱƫ��
	jpeg.Canvas.font.ShadowYoffset = 1   '��Ӱƫ��
	jpeg.Canvas.font.Bold = false    '�Ƿ����
	jpeg.Canvas.font.size= 14   '�����С
	text = "http://www.eb.com.cn/" 'ˮӡ����
	jpeg.Canvas.Printtext (width-152-20),(height-fontsize-20),text   '152Ϊˮӡ���ֵĿ�ȣ�20�ұ߾���±߾�

	jpeg.save savepath '���浽�ļ���
	jpeg.close
	set jpeg=nothing
end function
%>