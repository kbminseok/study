<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ page import = "shopping.CartDBBean" %>

<%@ include file="../etc/color.jspf"%> 

<%
 String cart_id = request.getParameter("cart_id");
 String buy_count = request.getParameter("buy_count");
 String food_kind = request.getParameter("food_kind");
 

 if(session.getAttribute("id")==null){
	response.sendRedirect("shopMain.jsp");        
 }else{
%>
<html>
<head>
<title>food Shopping Mall</title>
<link href="../etc/style.css" rel="stylesheet" type="text/css">
</head>
<body bgcolor="<%=bodyback_c%>">
<header>
<jsp:include page="../module/top.jsp" flush="false" /> 
</header>
<form method="POST" name="updateForm"  action="updateCart.jsp" > 
	 변경할 수량 : 
	 <input type="text" name="buy_count" size="5" value="<%=buy_count%>">
     <input type="hidden" name="cart_id" value="<%=cart_id%>">
     <input type="hidden" name="food_kind" value="<%=food_kind%>">
	 <input type="submit" value="변경" >  
</form>
</body>
</html>
<%}%>