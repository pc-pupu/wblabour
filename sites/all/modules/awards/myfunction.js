
jQuery(document).ready(function(){
	  $('#dateshowfrom').hide();
	   $('#dateshowto').hide();  
  jQuery(".awarddate_radio").on('change', function() {
	  //alert($('.awarddate_radio').is(':checked'));
	   //alert($('.awarddate_radio:checked').val());
	   if($('.awarddate_radio:checked').val()=='D'){
		   $('#dateshowfrom').show();
		   $('#dateshowto').show();
		   $('#searchshow').hide();
	   }
	   if($('.awarddate_radio:checked').val()=='T'){
		   $('#searchshow').show();
		   $('#dateshowfrom').hide();
		   $('#dateshowto').hide();
	   }
	   //alert($(this).val());
	  // if($('.awarddate_radio').is(':checked')) { alert($(this).val()); }
	  
  });
});  