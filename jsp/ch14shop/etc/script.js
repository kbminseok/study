function checkForm(writeform){

	if(!writeform.food_kind.value){
	  alert("음식의 분류를 선택하십시오");
	  writeform.food_kind.focus();
	  return false;
	}
	if(!writeform.food_name.value){
	  alert("음식의 제목을 입력하십시오");
	  writeform.food_name.focus();
	  return false;
	}
	
	if(!writeform.food_price.value){
	  alert("음식의 가격을 입력하십시오");
	  writeform.food_price.focus();
	  return false;
	}
        
	if(!writeform.food_count.value){
	  alert("음식의 수량을 입력하십시오");
	  writeform.food_count.focus();
	  return false;
	}
		
	writeform.action = "foodRegisterPro.jsp";
    writeform.submit();
	
 } 
 
 function updateCheckForm(writeform){

	if(!writeform.food_kind.value){
	  alert("음식의 분류를 선택하십시오");
	  writeform.food_kind.focus();
	  return false;
	}
	if(!writeform.food_name.value){
	  alert("음식의 제목을 입력하십시오");
	  writeform.food_name.focus();
	  return false;
	}
	
	if(!writeform.food_price.value){
	  alert("음식의 가격을 입력하십시오");
	  writeform.food_price.focus();
	  return false;
	}
        
	if(!writeform.food_count.value){
	  alert("음식의 수량을 입력하십시오");
	  writeform.food_count.focus();
	  return false;
	}
		
	writeform.action = "foodUpdatePro.jsp";
    writeform.submit();
	
 } 
 