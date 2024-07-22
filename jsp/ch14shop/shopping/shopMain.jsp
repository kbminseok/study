<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
    
<%@ include file="../etc/color.jspf"%> 

<html>
<head>
<meta charset="UTF-8">
<title>Book Shopping Mall</title>
<link href="../etc/style.css" rel="stylesheet" type="text/css">

</head>
<body>
<header>
<jsp:include page="../module/top.jsp" flush="false" /> 
</header>
<div>
 <jsp:include page="introList.jsp" flush="false"/>
</div>
<footer>
 <jsp:include page="../module/bottom.jsp" flush="false" />
</footer>
</body>
</html>
