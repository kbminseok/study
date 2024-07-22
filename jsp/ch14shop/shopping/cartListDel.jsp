<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ page import = "shopping.CartDBBean" %>

<%@ include file="../etc/color.jspf"%> 

<%
 String list = request.getParameter("list");
 String buyer = (String)session.getAttribute("id");
 String food_kind = request.getParameter("food_kind");
   
 if(session.getAttribute("id")==null){
	response.sendRedirect("shopMain.jsp");        
 }else{
	CartDBBean foodProcess = CartDBBean.getInstance();
	   
	if(list.equals("all"))
	   foodProcess.deleteAll(buyer);
	else
	   foodProcess.deleteList(Integer.parseInt(list));
	
	response.sendRedirect("cartList.jsp?food_kind=" + food_kind);
 }
%>