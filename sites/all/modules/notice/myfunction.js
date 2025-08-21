
jQuery(document).ready(function(){
	  $('#dateshowfrom').hide();
	   $('#dateshowto').hide();  
  jQuery(".noticedate_radio").on('change', function() {
	  //alert($('.noticedate_radio').is(':checked'));
	   //alert($('.awarddate_radio:checked').val());
	   if($('.noticedate_radio:checked').val()=='N'){
		   $('#dateshowfrom').show();
		   $('#dateshowto').show();
		   $('#searchshow').hide();
	   }
	   if($('.noticedate_radio:checked').val()=='T'){
		   $('#searchshow').show();
		   $('#dateshowfrom').hide();
		   $('#dateshowto').hide();
	   }
	   //alert($(this).val());
	  // if($('.awarddate_radio').is(':checked')) { alert($(this).val()); }
	  
  });
});  