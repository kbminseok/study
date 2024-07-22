<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ page import = "master.ShopFoodDBBean" %>
<%@ page import = "master.ShopFoodDataBean" %>
<%@ page import = "java.text.NumberFormat" %>

<%@ include file="../etc/color.jspf"%> 

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
<%
ShopFoodDataBean foodLists[] = null;
  int number =0;
  String food_kindName="";
  
  ShopFoodDBBean foodProcess = ShopFoodDBBean.getInstance();
  for(int i=1; i<=7;i++){
	  foodLists = foodProcess.getFoods(i+"00",1);
     
     if(foodLists[0].getFood_kind().equals("100")){
	      food_kindName="한식";
     }else if(foodLists[0].getFood_kind().equals("200")){
	      food_kindName="중식";  
     }else if(foodLists[0].getFood_kind().equals("300")){
	      food_kindName="일식";
     }else if(foodLists[0].getFood_kind().equals("400")){
	      food_kindName="양식";
    }else if(foodLists[0].getFood_kind().equals("500")){
	      food_kindName="치킨";
   }else if(foodLists[0].getFood_kind().equals("600")){
	      food_kindName="면";
  }else if(foodLists[0].getFood_kind().equals("700")){
      food_kindName="만두";
 }
     
%>
  <br><font size="+1"><b><%=food_kindName%> 분류의 음식목록: 
  <a href="list.jsp?food_kind=<%=foodLists[0].getFood_kind()%>">더보기</a>
  </b></font>
<%             
  for(int j=0;j<foodLists.length;j++){
%>
    <table > 
      <tr height="100" bgcolor="<%=value_c%>"> 
        <td rowspan="4">
          <a href="foodContent.jsp?food_id=<%=foodLists[j].getFood_id()%>&food_kind=<%=foodLists[0].getFood_kind()%>">
             <img src="../../imageFile/<%=foodLists[j].getFood_image()%>"  
             border="0" width="150" height="180"></a></td> 
       <td width="500"><font size="+1"><b>
          <a href="foodContent.jsp?food_id=<%=foodLists[j].getFood_id()%>&food_kind=<%=foodLists[0].getFood_kind()%>">
              <%=foodLists[j].getFood_name() %></a></b></font></td> 
       <td rowspan="4" width="100"  align="center"  valign="middle">
          <%if(foodLists[j].getFood_count()==0){ %>
              <b>일시품절</b>
          <%}else{ %>
               &nbsp;
          <%} %>
       </td>
     </tr>        
     <tr height="30" bgcolor="<%=value_c%>"> 
       <td width="350">정가 :<%=NumberFormat.getInstance().format(foodLists[j].getFood_price())%>원<br>
     </tr> 
     </table>
     <br>
<%
  }
}
%>

</body>
</html>