<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
    
<%@ page import = "shopping.CartDBBean" %>

<% request.setCharacterEncoding("utf-8");%>

<%
   String food_kind = request.getParameter("food_kind");
   String buy_count = request.getParameter("buy_count");
   String food_id = request.getParameter("food_id");
   String food_name = request.getParameter("food_name");
   String food_image = request.getParameter("food_image");
   String buy_price = request.getParameter("buy_price");
   String buyer = (String)session.getAttribute("id");
%>

<jsp:useBean id="cart" scope="page"
           class="shopping.CartDataBean">
</jsp:useBean>

<%
  cart.setFood_id(Integer.parseInt(food_id));
  cart.setFood_image(food_image);
  cart.setFood_name(food_name);
  cart.setBuy_count(Byte.parseByte(buy_count));
  cart.setBuy_price(Integer.parseInt(buy_price));
  cart.setBuyer(buyer);
  
  CartDBBean foodProcess = CartDBBean.getInstance();
  foodProcess.insertCart(cart);
  response.sendRedirect("cartList.jsp?food_kind="+food_kind);
%>