<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ page import = "shopping.BuyDataBean" %>
<%@ page import = "shopping.BuyDBBean" %>
<%@ page import = "java.util.List" %>
<%@ page import = "java.text.NumberFormat" %>

<%@ include file="../etc/color.jspf"%> 

<%
  String buyer = (String)session.getAttribute("id");
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
List<BuyDataBean> buyLists = null;
BuyDataBean buyList = null;
int count = 0;
int number = 0;
int total = 0;
long compareId=0;
long preId=0;

if(session.getAttribute("id")==null){
   response.sendRedirect("shopMain.jsp");        
}else{
   BuyDBBean buyProcess = BuyDBBean.getInstance();
   count = buyProcess.getListCount(buyer);

   if(count == 0){
%>
   <h3><b>구매목록</b></h3>
   
   <table> 
     <tr><td align="center" >구매목록이 없습니다.</td> </tr>
   </table>
      <input type="button" value="메인으로" 
         onclick="javascript:window.location='shopMain.jsp'">
<%
  }else{
    buyLists = buyProcess.getBuyList(buyer);
%>
    <h3><b>구매목록</b></h3>
    <table><tr><td>
<%
    for(int i=0;i<buyLists.size();i++){
       buyList = buyLists.get(i);
    	 
       if(i<buyLists.size()-1){
    	  BuyDataBean compare = buyLists.get(i+1);
    	  compareId = compare.getBuy_id();
    		 
    	  BuyDataBean pre = buyLists.get(buyLists.size()-2);
    	  preId = pre.getBuy_id();
       }  	 
%>
   <table> 
      <tr> 
        <td width="150">번호</td>
        <td width="300">음식이름</td> 
        <td width="100">판매가격</td>
        <td width="50">수량</td> 
        <td width="150">금액</td>
      </tr>
      <tr> 
        <td align="center"  width="150"><%=buyList.getBuy_id()%></td> 
        <td  width="300" align="left">
           <img src="../../imageFile/<%=buyList.getFood_image()%>" 
               border="0" width="30" height="50" align="middle">
             <%=buyList.getfood_name() %>
        </td> 
        <td width="100">\<%=NumberFormat.getInstance().format(buyList.getBuy_price())%></td>
        <td width="50"><%=buyList.getBuy_count()%></td> 
        <td width="150" >
           <%total += buyList.getBuy_count()*buyList.getBuy_price();%>
           \<%=NumberFormat.getInstance().format(buyList.getBuy_count()*buyList.getBuy_price()) %>
       </td>
      </tr>
<%
    if( buyList.getBuy_id() != compareId || 
      (i == buyLists.size()-1) && preId != buyList.getBuy_id() ) {
%> 
      <tr>
       <td colspan="5" align="right">
         <b>총 금액 : \<%=NumberFormat.getInstance().format(total)%></b></td>
      </tr></table>
<% 
      compareId = buyList.getBuy_id();
       total = 0;
   }else{
%>
   </td></tr></table><br>
<%
   }
 }
%>
<input type="button" value="메인으로" 
  onclick="javascript:window.location='shopMain.jsp'">
<%
 }
}
%>
</body>
</html>