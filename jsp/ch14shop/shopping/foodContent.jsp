<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ page import = "master.ShopFoodDBBean" %>
<%@ page import = "master.ShopFoodDataBean" %>
<%@ page import = "java.text.NumberFormat" %>

<%@ include file="../etc/color.jspf"%> 
 
<%
 String food_kind = request.getParameter("food_kind");
 String food_id = request.getParameter("food_id");
 String id = "";
 int buy_price=0;
 try{
   if(session.getAttribute("id")==null)
     id="not";
   else
     id= (String)session.getAttribute("id");    
}catch(Exception e){}
%>

<html>
<head>
<title>food Shopping Mall</title>
<link href="../etc/style.css" rel="stylesheet" type="text/css">
<style>
table{
	margin : auto;
    width : 50%;
}
</style>
</head>
<body bgcolor="<%=bodyback_c%>">
<header>
<jsp:include page="../module/top.jsp" flush="false" /> 
</header>
<%
ShopFoodDataBean foodList = null;
String food_kindName="";
  
ShopFoodDBBean foodProcess = ShopFoodDBBean.getInstance();
 
foodList = foodProcess.getFood(Integer.parseInt(food_id));
     
if(food_kind.equals("100"))
	food_kindName="한식";
else if(food_kind.equals("200"))
	food_kindName="일식";  
else if(food_kind.equals("300"))
	food_kindName="중식";
else if(food_kind.equals("400"))
	food_kindName="양식";
else if(food_kind.equals("500"))
	food_kindName="치킨";
else if(food_kind.equals("600"))
	food_kindName="면";
else if(food_kind.equals("700"))
	food_kindName="만두";

%>
<form name="inform" method="post" action="cartInsert.jsp">
<table> 
   <tr height="30"> 
     <td rowspan="6"  width="150">
        <img src="../../imageFile/<%=foodList.getFood_image()%>" 
             border="0" width="150" height="200"></td> 
     <td width="500"><font size="+1">
       <b><%=foodList.getFood_name() %></b></font></td>
   </tr>
   <tr><td width="500">정가 : <%=NumberFormat.getInstance().format(foodList.getFood_price())%>원<br>
   <%buy_price = (int)(foodList.getFood_price()) ;%>
   </td>
   <tr><td width="500">수량 : <input type="text" size="5"name="buy_count" value="1"> 개
 <%
   if(id.equals("not")){
     if(foodList.getFood_count()==0){
 %>
        <b>일시품절</b>
<%  
     }           
  }else{ 
     if(foodList.getFood_count()==0){
%>
         <b>일시품절</b>
                           
<%   }else{ %>	 
       <input type="hidden" name="food_id" value="<%=food_id %>">
       <input type="hidden" name="food_image" value="<%=foodList.getFood_image()%>">
       <input type="hidden" name="food_name" value="<%=foodList.getFood_name() %>">
       <input type="hidden" name="buy_price" value="<%=buy_price %>">
       <input type="hidden" name="food_kind" value="<%=food_kind %>">              
       <input type="submit" value="장바구니에 담기">
<%}}%>
   <input type="button" value="목록으로" 
     onclick="javascript:window.location='list.jsp?food_kind=<%=food_kind%>'">
   <input type="button" value="메인으로" 
     onclick="javascript:window.location='shopMain.jsp'">
   </td>
  </tr> 
</table>
</form>
</body>
</html>