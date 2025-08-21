(function($){
	$('#processBtnDisabled').attr('disabled','disabled');
	$('#processBtnEnabled').removeAttr('disabled');
	$(".qstn_elligibility_error_msg").hide();
})(jQuery);	
	
function PrintDiv() {    
   var divToPrint = document.getElementById('divToPrint');
   var popupWin = window.open('', '_blank', 'width=600,height=600');
   popupWin.document.open();
   popupWin.document.write('<html><body onload="window.print()">' + divToPrint.innerHTML + '</html>');
	popupWin.document.close();
}

function checkingUncked(){
	jQuery('.chkelgbltbtn').each(function(i){
		
		var str = jQuery(this).attr('id');
		
		$("#"+str).change(function(){
			if($('.chkelgbltbtn:checked').length>0){
				$('#processBtnEnabled').removeAttr('disabled');
				$(".qstn_elligibility_error_msg").css("display","none");
			}else{
				$('#processBtnEnabled').attr('disabled','disabled');
				$(".qstn_elligibility_error_msg").css("display","block");
				$(".qstn_elligibility_error_msg").html("Please select at least one service");
			}
		});
		//alert(btnDsbl);
	});
	
}
