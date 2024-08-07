<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ page import = "shopping.CartDataBean" %>
<%@ page import = "shopping.CartDBBean" %>
<%@ page import = "java.util.List" %>
<%@ page import = "java.text.NumberFormat" %>

<%@ include file="../etc/color.jspf"%>

<%
 String food_kind = request.getParameter("food_kind");
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
List<CartDataBean> cartLists = null;
CartDataBean cartList = null;
int count = 0;
int number = 0;
int total = 0;

if(session.getAttribute("id")==null){
   response.sendRedirect("shopMain.jsp");        
}else{
   CartDBBean foodProcess = CartDBBean.getInstance();
   count = foodProcess.getListCount(buyer);

   if(count == 0){
%>
   <h3><b>장바구니</b></h3>
   <table> 
     <tr><td >장바구니에 담긴 물품이 없습니다.</td> </tr>
   </table>
     <input type="button" value="쇼핑계속" 
     onclick="javascript:window.location='shopMain.jsp'">
<%
   }else{
     cartLists = foodProcess.getCart(buyer);
 %>
   <h3><b>장바구니</b></h3>
   <form name="cartform">
   <table> 
     <tr> 
       <td width="50">번호</td> 
       <td width="300">음식이름</td> 
       <td width="100">판매가격</td>
       <td width="150">수량</td> 
       <td width="150">금액</td>
     </tr>
      
<%
   for(int i=0;i<cartLists.size();i++){
     cartList = (CartDataBean)cartLists.get(i);
%>
     
     <tr> 
       <td width="50"><%=++number %></td> 
       <td  width="300" align="left">
         <img src="../../imageFile/<%=cartList.getFood_image()%>" 
             border="0" width="30" height="50" align="middle">
             <%=cartList.getFood_name()%>
       </td> 
       <td width="100"><%=NumberFormat.getInstance().format(cartList.getBuy_price())%></td>
       <td width="150">
          <input type="text" name="buy_count" size="5" value="<%=cartList.getBuy_count()%>">
          <% 
          String url = "updateCartForm.jsp?cart_id="+cartList.getCart_id()+
            "&food_kind="+food_kind + "&buy_count="+cartList.getBuy_count();
          
          %>
          <input type="button" value="수정"
            onclick="javascript:window.location='<%=url%>'">
       </td> 
       <td align="center"  width="150">
          <%total += cartList.getBuy_count()*cartList.getBuy_price();%>
            <%=NumberFormat.getInstance().format(cartList.getBuy_count()*cartList.getBuy_price()) %>
          <input type="button" value="삭제" 
            onclick="javascript:window.location=
            'cartListDel.jsp?list=<%=cartList.getCart_id()%>&food_kind=<%=food_kind%>'">
       </td>
     </tr>
<%}%>
     <tr>
       <td colspan="5" align="right"><b>총 금액 : <%=NumberFormat.getInstance().format(total)%></b></td>
     </tr>
     <tr>
       <td colspan="5">
         <input type="button" value="구매하기" 
            onclick="javascript:window.location='buyForm.jsp'">
         <input type="button" value="쇼핑계속" 
            onclick="javascript:window.location='list.jsp?food_kind=<%=food_kind%>'">
         <input type="button" value="장바구니비우기" 
            onclick="javascript:window.location='cartListDel.jsp?list=all&food_kind=<%=food_kind%>'">
       </td>
     </tr>
   </table>
   </form>
<%
  } 
}
%>
</body>
</html>