<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ page import = "master.ShopFoodDBBean" %>
<%@ page import = "master.ShopFoodDataBean" %>
<%@ page import = "java.util.List" %>
<%@ page import = "java.text.NumberFormat" %>

<%@ include file="../etc/color.jspf"%> 

<%
  String food_kind = request.getParameter("food_kind");
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
 List<ShopFoodDataBean> foodLists = null;
ShopFoodDataBean foodList = null;
 String food_kindName="";
  
 ShopFoodDBBean foodProcess = ShopFoodDBBean.getInstance();
 
 foodLists = foodProcess.getFoods(food_kind);
 if(food_kind.equals("100")) 
	      food_kindName=" 한식";
 else if(food_kind.equals("200"))
	      food_kindName="중식";  
 else if(food_kind.equals("300"))
	      food_kindName="일식";
 else if(food_kind.equals("400"))
     food_kindName="양식";
 else if(food_kind.equals("500"))
     food_kindName="치킨";
 else if(food_kind.equals("600"))
     food_kindName="면";
 else if(food_kind.equals("700"))
     food_kindName="만두";
 else if(food_kind.equals("all"))
	      food_kindName="전체";
%>
 <h3><b><%=food_kindName%> 분류의 목록</b></h3>
    <a href="shopMain.jsp">메인으로</a>
<%
 for(int i=0;i<foodLists.size();i++){
    foodList = (ShopFoodDataBean)foodLists.get(i);
%>
  <table> 
    <tr height="100" bgcolor="<%=value_c%>"> 
      <td rowspan="4">
         <a href="foodContent.jsp?food_id=<%=foodList.getFood_id()%>&food_kind=<%=food_kind%>">
         <img src="../../imageFile/<%=foodList.getFood_image()%>" border="0" width="150" height="180"></a></td> 
      <td width="500"><font size="+1"><b>
         <a href="foodContent.jsp?food_id=<%=foodList.getFood_id()%>&food_kind=<%=food_kind%>">
         <%=foodList.getFood_name() %></a></b></font></td> 
      <td rowspan="4" width="100"  align="center"  valign="middle">
        <%if(foodList.getFood_count()==0){ %>
              <b>일시품절</b>
        <%}else{ %>
              &nbsp;
        <%} %>
      </td>
    </tr>        
    <tr height="30" bgcolor="<%=value_c%>"> 
       <td width="350">정가 : <%=NumberFormat.getInstance().format(foodList.getFood_price())%><br>
       </td>
    </tr> 
  </table>
  <br>
<%
 } 
%>

</body>
</html>