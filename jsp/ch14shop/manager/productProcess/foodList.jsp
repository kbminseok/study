<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ page import = "master.ShopFoodDBBean" %>
<%@ page import = "master.ShopFoodDataBean" %>
<%@ page import = "java.util.List" %>
<%@ page import = "java.text.SimpleDateFormat" %>

<%@ include file="../../etc/color.jspf"%> 

<%
String managerId ="";
try{
	managerId = (String)session.getAttribute("managerId");
	if(managerId==null || managerId.equals("")){
       response.sendRedirect("../logon/managerLoginForm.jsp");
	}else{
%> 


<%
    List<ShopFoodDataBean> foodList = null; 
    int number =0;
    String food_kind="";
    
    food_kind = request.getParameter("food_kind");
 
    ShopFoodDBBean foodProcess = ShopFoodDBBean.getInstance();
    int count = foodProcess.getFoodCount();
    
    if (count > 0) {
    	foodList = foodProcess.getFoods(food_kind);
    }
%>
<html>
<head>
<title>등록된 책 목록</title>
<link href="../../etc/style.css" rel="stylesheet" type="text/css">
</head>
<body bgcolor="<%=bodyback_c%>">
<%
   String food_kindName="";
   if(food_kind.equals("100")){
	   food_kindName="한식";
   }else if(food_kind.equals("200")){
	   food_kindName="중식";  
   }else if(food_kind.equals("300")){
	   food_kindName="일식";
   }else if(food_kind.equals("400")){
		   food_kindName="양식";
	}
	else if(food_kind.equals("500")){
		   food_kindName="치킨";
	}
	else if(food_kind.equals("600")){
		   food_kindName="면";
	 }
	else if(food_kind.equals("700")){
		  food_kindName="만두";
	}else if(food_kind.equals("all")){
	   food_kindName="전체";
   }
%>
<a href="../managerMain.jsp"> 관리자 메인으로</a> &nbsp;
<p><%=food_kindName%> 분류의 목록: 
<%if(food_kind.equals("all")){%> 
    <%=count%>개
<%}else{%>
    <%=foodList.size() %>개
<%} %>
</p>
<table>
<tr>
    <td align="right" bgcolor="<%=value_c%>">
       <a href="foodRegisterForm.jsp">음식 등록</a>
    </td>
</table>

<%
  if (count == 0) {
%>
<table>
<tr>
   <td align="center">
           등록된 음식이 없습니다.
   </td>
</table>

<%} else {%>
<table> 
    <tr height="30" bgcolor="<%=value_c%>"> 
      <td align="center"  width="30">번호</td> 
      <td align="center"  width="30">음식종류</td> 
      <td align="center"  width="100">음식 이름</td>
      <td align="center"  width="50">가격</td> 
      <td align="center"  width="50">수량</td> 
      <td align="center"  width="50">이미지</td>
      <td align="center"  width="50">수정</td>
      <td align="center"  width="50">삭제</td>         
    </tr>
<%  
    for (int i = 0 ; i <foodList.size() ; i++) {
    	ShopFoodDataBean food = 
    		  (ShopFoodDataBean)foodList.get(i);
%>
   <tr height="30">
      <td width="30"><%=++number%></td> 
      <td width="30"><%=food.getFood_kind()%></td> 
      <td width="100" align="left">
           <%=food.getFood_name()%></td>
      <td width="50" align="right"><%=food.getFood_price()%></td> 
      <td width="50" align="right">
      <% if(food.getFood_count()==0) {%>
         <font color="red"><%="일시품절"%></font>
      <% }else{ %>
         <%=food.getFood_count()%>
      <%} %>
      </td> 
      <td width="50"><%=food.getFood_image()%></td>
      <td width="50">
         <a href="foodUpdateForm.jsp?food_id=<%=food.getFood_id()%>&food_kind=<%=food.getFood_kind()%>">수정</a></td>
      <td width="50">
         <a href="foodDeleteForm.jsp?food_id=<%=food.getFood_id()%>&food_kind=<%=food.getFood_kind()%>">삭제</a></td>    
   </tr>
<%}%>
</table>
<%}%>
<br>
<a href="../managerMain.jsp"> 관리자 메인으로</a> 
</body>
</html>

<% 
   }
}catch(Exception e){
   e.printStackTrace();
}
%>