<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ page import="master.ShopFoodDBBean" %>
<%@ page import="java.sql.Timestamp" %>
<%@ page import="com.oreilly.servlet.MultipartRequest"%>
<%@ page import="com.oreilly.servlet.multipart.DefaultFileRenamePolicy"%>
<%@ page import="java.util.*"%>
<%@ page import="java.io.*"%>

<% request.setCharacterEncoding("utf-8");%>

<%
String realFolder = "";//웹 어플리케이션상의 절대 경로
String filename ="";
MultipartRequest imageUp = null;

String saveFolder = "/imageFile";//파일이 업로드되는 폴더
String encType = "utf-8"; //엔코딩타입
int maxSize = 2*1024*1024;  //최대 업로될 파일크기 5Mb

//현재 jsp페이지의 웹 어플리케이션상의 절대 경로를 구한다
ServletContext context = getServletContext();
realFolder = context.getRealPath(saveFolder);  

try{
   
   //전송을 담당할 콤포넌트를 생성하고 파일을 전송한다.
   //전송할 파일명을 가지고 있는 객체, 서버상의 절대경로,최대 업로드될 파일크기, 문자코드, 기본 보안 적용
   imageUp = new MultipartRequest(request,realFolder,
		   maxSize,encType,new DefaultFileRenamePolicy());
   
   //전송한 파일 정보를 가져와 출력한다
   Enumeration<?> files = imageUp.getFileNames();
   
   //파일 정보가 있다면
   while(files.hasMoreElements()){
    //input 태그의 속성이 file인 태그의 name 속성값 :파라미터이름
      String name = (String)files.nextElement();
   
   //서버에 저장된 파일 이름
      filename = imageUp.getFilesystemName(name);
   }
}catch(IOException ioe){
 System.out.println(ioe);
}catch(Exception ex){
 System.out.println(ex);
}
%>

<jsp:useBean id="food" scope="page" 
     class="master.ShopFoodDataBean">
</jsp:useBean>

<%
 int food_id= Integer.parseInt( imageUp.getParameter("food_id"));
 String food_kind = imageUp.getParameter("food_kind");
 String food_title = imageUp.getParameter("food_name");
 String food_price = imageUp.getParameter("food_price");
 String food_count = imageUp.getParameter("food_count");

 food.setFood_kind(food_kind);
 food.setFood_name(food_title);
 food.setFood_price(Integer.parseInt(food_price));
 food.setFood_count(Short.parseShort(food_count));
 food.setFood_image(filename);

 ShopFoodDBBean foodProcess = ShopFoodDBBean.getInstance();
foodProcess.updateFood(food, food_id); 

response.sendRedirect("foodList.jsp?food_kind="+food_kind);

%>