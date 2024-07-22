<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ page import = "java.sql.Timestamp" %>
<%@ page import = "master.ShopFoodDBBean" %>
<%@ page import = "master.ShopFoodDataBean" %>

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
int food_id = Integer.parseInt(request.getParameter("food_id"));
String food_kind = request.getParameter("food_kind");
try{
	ShopFoodDBBean foodProcess = ShopFoodDBBean.getInstance();
	ShopFoodDataBean food =  foodProcess.getFood(food_id); 
%>
<html>
<head>
<title>상품수정</title>
<link href="../../etc/style.css" rel="stylesheet" type="text/css">
<script type="text/javascript" src="../../etc/script.js"></script>
</head>
<body bgcolor="<%=bodyback_c%>">
<p>책 수정</p>
<br>

<form method="post" name="writeform" 
   action="foodUpdatePro.jsp"  enctype="multipart/form-data">
<table>
   <tr>
    <td align="right" colspan="2" bgcolor="<%=value_c%>">
	    <a href="../managerMain.jsp"> 관리자 메인으로</a> &nbsp;
	    <a href="foodList.jsp?food_kind=<%=food_kind%>">목록으로</a>
   </td>
   </tr>
   <tr>
    <td  width="100"  bgcolor="<%=value_c%>">분류 선택</td>
    <td  width="400"  align="left">
       <select name="food_kind">
           <option value="100" 
             <%if (food.getFood_kind().equals("100")) {%>selected<%} %>
              >한식</option>
           <option value="200" 
             <%if (food.getFood_kind().equals("200")) {%>selected<%} %>
             >중식</option>
           <option value="300" 
             <%if (food.getFood_kind().equals("300")) {%>selected<%} %>
             >일식</option>
             <option value="400" 
             <%if (food.getFood_kind().equals("400")) {%>selected<%} %>
             >양식</option>
             <option value="500" 
             <%if (food.getFood_kind().equals("500")) {%>selected<%} %>
             >치킨</option>
             <option value="600" 
             <%if (food.getFood_kind().equals("600")) {%>selected<%} %>
             >면</option>
             <option value="700" 
             <%if (food.getFood_kind().equals("700")) {%>selected<%} %>
             >만두</option>
       </select>
    </td>
  </tr>
  <tr>
    <td  width="100"  bgcolor="<%=value_c%>">음식 이름</td>
    <td  width="400" align="left">
        <input type="text" size="50" maxlength="50" name="food_name" 
            value="<%=food.getFood_name() %>">
        <input type="hidden" name="food_id" value="<%=food_id%>"></td>
  </tr>
  <tr>
    <td  width="100"  bgcolor="<%=value_c%>">가 격</td>
    <td  width="400" align="left">
        <input type="text" size="10" maxlength="9" name="food_price" 
          value="<%=food.getFood_price() %>">원</td>
  </tr>
  <tr>
    <td  width="100"  bgcolor="<%=value_c%>">수량</td>
    <td  width="400" align="left">
        <input type="text" size="10" maxlength="5" name="food_count" 
          value="<%=food.getFood_count() %>">권</td>
  </tr>

  <tr>
  <tr>
    <td  width="100"  bgcolor="<%=value_c%>">이미지</td>
    <td  width="400" align="left">
        <input type="file" name="food_image"><%=food.getFood_image() %></td>
  </tr> 
  <tr>
 <td colspan=2 bgcolor="<%=value_c%>" align="center"> 
  <input type="button" value="책수정" onclick="updateCheckForm(this.form)">  
  <input type="reset" value="다시작성">
</td></tr></table>         
</form>   
<%
}catch(Exception e){
	e.printStackTrace();
}%>         
</body>
</html>
<% 
  }
}catch(Exception e){
	e.printStackTrace();
}
%>