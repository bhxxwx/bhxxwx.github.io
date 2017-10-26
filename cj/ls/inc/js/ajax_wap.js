var $=function(node){
return document.getElementById(node);
}
function $(objId){
return document.getElementById(objId);
}
document.onkeydown = function(e){
 if(!e) e = window.event;
 if((e.keyCode || e.which) == 13){
 document.getElementById("sub").click();
}
}
function inst() {
if ($("name")!=null) $("name").value = $("tishi1").innerHTML;
if ($("code")!=null) $("code").value = $("tishi4").innerHTML;
}
function startRequest(Num) {
var queryString;
if(Num == 1 || Num == 0){
if($("time")!=null){
if($("time").value == ""){
$('time').style.borderColor='red';
return false;
}else{
$('time').style.borderColor='green';
}
}
}
if(Num == 2 || Num == 0){
if($("name")!=null){
if($("name").value == "" || $("name").value == $("tishi1").innerHTML){
$("name").value = $("tishi1").innerHTML;
$('11').style.borderColor='red';
return false;
}else{
$('11').style.borderColor='green';
}
}
}
if(Num == 3 || Num == 0){
if($("code")!=null){
if (!$("code").value.match(/^[0-9]{4}$/)){
$("code").value = $("tishi4").innerHTML;
$('33').style.borderColor='red';
return false;
}else{
$('33').style.borderColor='green';
}
}
}
if(Num == 4 || Num == 0){
    if ($("mm").value.match(/^[0-9]{4}$/)){
    $("mm").value = $("tishi5").innerHTML;
    $('66').style.borderColor='red';
    return false;
    }else{
    $('66').style.borderColor='green';
    }
    }
if(Num == "0"){
}
}