<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>

<%@ page import = "master.ShopFoodDBBean" %>

<% request.setCharacterEncoding("utf-8");%>

<%
  int food_id = Integer.parseInt(request.getParameter("food_id"));
  String food_kind = request.getParameter("food_kind");
 
  ShopFoodDBBean foodProcess = ShopFoodDBBean.getInstance();
  foodProcess.deleteFood(food_id); 

  response.sendRedirect("foodList.jsp?food_kind="+food_kind);
%>