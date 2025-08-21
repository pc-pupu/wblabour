 /***************for auto complete *************/
jQuery(document).ready(function(){
 
  
  
/*  jQuery("#pincode_autocomplete").blur(function(e) {
	      var base_url = window.location.origin;
		  jQuery("#state_name").val(''); 
		  jQuery("#district_name").val('');
		  var pincode =jQuery("#pincode_autocomplete").val();
		  var pincode_type = pincode.split('-');
		  jQuery.ajax({
				url: base_url+"/type-search/"+pincode_type[0],
				success: function(result){
						var myarr = result.split('-');
						alert(myarr[1]); 
				}
		   });
	  
  });*/
  
    jQuery('#votercardu').keyup(function(){
        jQuery(this).val($(this).val().toUpperCase());
    });
 
    jQuery('#pancardu').keyup(function(){
        jQuery(this).val($(this).val().toUpperCase());
    });

  });  
  /***************End of  auto complete *************/
	