jQuery(document).ready(function(){
	//jQuery(".qutn_hide").css('display','none');
	jQuery('.lcsection ul li').hide().filter(':lt(1)').show();
	jQuery("#hid_1").val('1_ActiveBox');
	jQuery(".qstn_wizard_error_msg").hide();
	
	jQuery('.factorysection ul li').hide().filter(':lt(1)').show();
	jQuery("#hid_factory_23").val('23_ActiveBox');
	
	jQuery('.boilerssection ul li').hide().filter(':lt(1)').show();
	jQuery("#hid_boilers_40").val('40_ActiveBox');
});
//var myservice = [];
function callProgress(el,qs,nextqsn,yn,directorate_code){
		
		jQuery('.lcsection ul li').each(function(i){
			var str = jQuery(this).attr('id');
			var curr_id = str.split('_');
			//alert('qs->'+qs);
			//alert('curr_id->'+curr_id[1]);
			if(parseInt(qs) < parseInt(curr_id[1])){
				//alert(str);
				jQuery("#btn-no-"+curr_id[1]).removeClass('btn-danger');
				jQuery("#btn-no-"+curr_id[1]).removeClass('active');
				jQuery("#btn-yes-"+curr_id[1]).removeClass('btn-success');
				jQuery("#btn-yes-"+curr_id[1]).removeClass('active');
				//jQuery("#btn-no-"+curr_id[1]).addClass('btn btn-default');
				//jQuery("#btn-yes-"+curr_id[1]).addClass('btn btn-default');
				jQuery("#qstn_"+curr_id[1]).hide();
				jQuery("#hid_"+curr_id[1]).val('');
			}
		    //alert(jQuery(this).attr('id')); // This is your rel value
		});
		//alert(nextqsn);
		 var qstn_id = nextqsn.split('_');
		 //alert(trust_data_set[0]);
		//alert(jQuery("#"+el.id).attr('id'));
		
		if(yn == 'Y'){
			jQuery("#btn-yes-"+qs).addClass('btn-success');
			jQuery("#btn-no-"+qs).removeClass('btn-danger');
			
			
			if(qstn_id[0]==qstn_id[1]){
				jQuery("#qstn_"+qstn_id[0]).show();
				
				jQuery("#hid_"+qstn_id[0]).val(qstn_id[0]+'_ActiveBox');
			}else{
				jQuery("#qstn_"+qstn_id[0]).show();
				jQuery("#qstn_"+qstn_id[1]).hide();
				
				jQuery("#hid_"+qstn_id[0]).val(qstn_id[0]+'_ActiveBox');
				jQuery("#hid_"+qstn_id[1]).val('');
			}
			jQuery("#hid_"+qs).val(qs+'_Y_'+directorate_code);
			
		}
		if(yn == 'N'){
			jQuery("#btn-no-"+qs).addClass('btn-danger');
			jQuery("#btn-yes-"+qs).removeClass('btn-success');
			
			if(qstn_id[0]==qstn_id[1]){
				jQuery("#qstn_"+qstn_id[1]).show();
				
				jQuery("#hid_"+qstn_id[1]).val(qstn_id[1]+'_ActiveBox');
			}else{
				jQuery("#qstn_"+qstn_id[1]).show();
				jQuery("#qstn_"+qstn_id[0]).hide();
				
				jQuery("#hid_"+qstn_id[1]).val(qstn_id[1]+'_ActiveBox');
				jQuery("#hid_"+qstn_id[0]).val('');
			}
			jQuery("#hid_"+qs).val(qs+'_N_'+directorate_code);
		}
		
	}
	
function callProgressFactory(el,qs,nextqsn,yn,directorate_code){
		jQuery('.factorysection ul li').each(function(i){
			var str = jQuery(this).attr('id');
			var curr_id = str.split('_');
			//alert('qs->'+qs);
			//alert('curr_id->'+curr_id[2]);
			if(parseInt(qs) < parseInt(curr_id[2])){
				//alert(str);
				jQuery("#btn-no-factory-"+curr_id[2]).removeClass('btn-danger');
				jQuery("#btn-no-factory-"+curr_id[2]).removeClass('active');
				jQuery("#btn-yes-factory-"+curr_id[2]).removeClass('btn-success');
				jQuery("#btn-yes-factory-"+curr_id[2]).removeClass('active');
				//jQuery("#btn-no-"+curr_id[1]).addClass('btn btn-default');
				//jQuery("#btn-yes-"+curr_id[1]).addClass('btn btn-default');
				jQuery("#qstn_factory_"+curr_id[2]).hide();
				jQuery("#hid_factory_"+curr_id[2]).val('');
			}
		    //alert(jQuery(this).attr('id')); // This is your rel value
		});
		//alert(nextqsn);
		 var qstn_id = nextqsn.split('_');
		 //alert(trust_data_set[0]);
		//alert(jQuery("#"+el.id).attr('id'));
		
		if(yn == 'Y'){
			jQuery("#btn-yes-factory-"+qs).addClass('btn-success');
			jQuery("#btn-no-factory-"+qs).removeClass('btn-danger');
			
			
			if(qstn_id[0]==qstn_id[1]){
				jQuery("#qstn_factory_"+qstn_id[0]).show();
				
				jQuery("#hid_factory_"+qstn_id[0]).val(qstn_id[0]+'_ActiveBox');
			}else{
				jQuery("#qstn_factory_"+qstn_id[0]).show();
				jQuery("#qstn_factory_"+qstn_id[1]).hide();
				
				jQuery("#hid_factory_"+qstn_id[0]).val(qstn_id[0]+'_ActiveBox');
				jQuery("#hid_factory_"+qstn_id[1]).val('');
			}
			jQuery("#hid_factory_"+qs).val(qs+'_Y_'+directorate_code);
			
		}
		if(yn == 'N'){
			jQuery("#btn-no-factory-"+qs).addClass('btn-danger');
			jQuery("#btn-yes-factory-"+qs).removeClass('btn-success');
			
			if(qstn_id[0]==qstn_id[1]){
				jQuery("#qstn_factory_"+qstn_id[1]).show();
				
				jQuery("#hid_factory_"+qstn_id[1]).val(qstn_id[1]+'_ActiveBox');
			}else{
				jQuery("#qstn_factory_"+qstn_id[1]).show();
				jQuery("#qstn_factory_"+qstn_id[0]).hide();
				
				jQuery("#hid_factory_"+qstn_id[1]).val(qstn_id[1]+'_ActiveBox');
				jQuery("#hid_factory_"+qstn_id[0]).val('');
			}
			jQuery("#hid_factory_"+qs).val(qs+'_N_'+directorate_code);
		}
		
	}
	

function callProgressBoilers(el,qs,nextqsn,yn,directorate_code){
		if(parseInt(qs) == 40 || parseInt(qs) == 41 || parseInt(qs) == 49 || parseInt(qs) == 50){
		jQuery('.boilerssection ul li').each(function(i){
			var str = jQuery(this).attr('id');
			//alert(str);
			var curr_id = str.split('_');
			//alert('qs->'+qs);
			//alert('curr_id->'+curr_id[2]);
			if(parseInt(qs) < parseInt(curr_id[2])){
				//alert(str);
				jQuery("#btn-no-boilers-"+curr_id[2]).removeClass('btn-danger');
				jQuery("#btn-no-boilers-"+curr_id[2]).removeClass('active');
				jQuery("#btn-yes-boilers-"+curr_id[2]).removeClass('btn-success');
				jQuery("#btn-yes-boilers-"+curr_id[2]).removeClass('active');
				//jQuery("#btn-no-"+curr_id[1]).addClass('btn btn-default');
				//jQuery("#btn-yes-"+curr_id[1]).addClass('btn btn-default');
				jQuery("#qstn_boilers_"+curr_id[2]).hide();
				jQuery("#hid_boilers_"+curr_id[2]).val('');
			}
		    //alert(jQuery(this).attr('id')); // This is your rel value
		});
		}
		//alert(nextqsn);
		 var qstn_id = nextqsn.split('_');
		 //alert(qstn_id[1].length);
		 //alert(trust_data_set[0]);
		//alert(jQuery("#"+el.id).attr('id'));
		
		if(yn == 'Y'){
			
			jQuery("#btn-yes-boilers-"+qs).addClass('btn-success');
			jQuery("#btn-no-boilers-"+qs).removeClass('btn-danger');
			
			if(qstn_id[0].indexOf(',') !== -1){
				var yes_next_array = qstn_id[0].split(',');
				var no_next_array = qstn_id[1].split(',');
				for(var i = 0; i < yes_next_array.length; i++) {
				   // Trim the excess whitespace.
				   //yes_next_array[i] = yes_next_array[i].replace(/^\s*/, "").replace(/\s*$/, "");
				   // Add additional code here, such as:
				   //alert(yes_next_array[i]);
				   jQuery("#qstn_boilers_"+yes_next_array[i]).show();
				   jQuery("#hid_boilers_"+yes_next_array[i]).val(yes_next_array[i]+'_ActiveBox');
				}
				
				for(var j = 0; j < no_next_array.length; j++) {
				   jQuery("#qstn_boilers_"+no_next_array[j]).hide();
				   jQuery("#hid_boilers_"+no_next_array[j]).val('');
				}
			}else{
			
			   //alert('single'+qstn_id[0]);
			
				if(qstn_id[0]==qstn_id[1]){
					jQuery("#qstn_boilers_"+qstn_id[0]).show();
					
					jQuery("#hid_boilers_"+qstn_id[0]).val(qstn_id[0]+'_ActiveBox');
				}else{
					jQuery("#qstn_boilers_"+qstn_id[0]).show();
					jQuery("#qstn_boilers_"+qstn_id[1]).hide();
					
					jQuery("#hid_boilers_"+qstn_id[0]).val(qstn_id[0]+'_ActiveBox');
					jQuery("#hid_boilers_"+qstn_id[1]).val('');
				}
			}
			jQuery("#hid_boilers_"+qs).val(qs+'_Y_'+directorate_code);
			
		}
		if(yn == 'N'){
			jQuery("#btn-no-boilers-"+qs).addClass('btn-danger');
			jQuery("#btn-yes-boilers-"+qs).removeClass('btn-success');
			
			if(qstn_id[1].indexOf(',') !== -1){
				var yes_next_array = qstn_id[0].split(',');
				var no_next_array = qstn_id[1].split(',');
				for(var i = 0; i < no_next_array.length; i++) {
				   jQuery("#qstn_boilers_"+no_next_array[i]).show();
				   jQuery("#hid_boilers_"+no_next_array[i]).val(no_next_array[i]+'_ActiveBox');
				}
				
				for(var j = 0; j < yes_next_array.length; j++) {
				   jQuery("#qstn_boilers_"+yes_next_array[j]).hide();
				   jQuery("#hid_boilers_"+yes_next_array[j]).val('');
				}
			}else{
			
				if(qstn_id[0]==qstn_id[1]){
					jQuery("#qstn_boilers_"+qstn_id[1]).show();
					
					jQuery("#hid_boilers_"+qstn_id[1]).val(qstn_id[1]+'_ActiveBox');
				}else{
					jQuery("#qstn_boilers_"+qstn_id[1]).show();
					jQuery("#qstn_boilers_"+qstn_id[0]).hide();
					
					jQuery("#hid_boilers_"+qstn_id[1]).val(qstn_id[1]+'_ActiveBox');
					jQuery("#hid_boilers_"+qstn_id[0]).val('');
				}
			}
			jQuery("#hid_boilers_"+qs).val(qs+'_N_'+directorate_code);
		}
		
	}	
	
function lcValidate(){
	jQuery(".qstn_wizard_error_msg").css("display","none");
	var rt = 1;
	jQuery('.lcsection ul li').each(function(i){
		var str = jQuery(this).attr('id');
		var curr_id = str.split('_');
		var qsans = "";
		var qsans = jQuery("#hid_"+curr_id[1]).val();
		var ansValid = qsans.split('_');
		if(ansValid[1] == "ActiveBox"){
			jQuery("#qstn_"+curr_id[1]).addClass('question-error');
			jQuery(".qstn_wizard_error_msg").css("display","block");
			jQuery(".qstn_wizard_error_msg").html("Please answer the question");
			rt = 0;
		}else{
			jQuery("#qstn_"+curr_id[1]).removeClass('question-error');
			//jQuery(".qstn_wizard_error_msg").hide();
			//jQuery(".qstn_wizard_error_msg").empty();
			//
			//rt = 1;
		}
	});
	if(rt == 0){
		return false;
	}else{
		return true;	
	}
}


function factoryValidate(){
	jQuery(".qstn_wizard_error_msg").css("display","none");
	var factory = 1;
	jQuery('.factorysection ul li').each(function(i){
		var str = jQuery(this).attr('id');
		var curr_id = str.split('_');
		var qsans = "";
		var qsans = jQuery("#hid_factory_"+curr_id[2]).val();
		var ansValid = qsans.split('_');
		if(ansValid[1] == "ActiveBox"){
			jQuery("#qstn_factory_"+curr_id[2]).addClass('question-error');
			jQuery(".qstn_wizard_error_msg").css("display","block");
			jQuery(".qstn_wizard_error_msg").html("Please answer the question");
			factory = 0;
		}else{
			jQuery("#qstn_factory_"+curr_id[2]).removeClass('question-error');
			//jQuery(".qstn_wizard_error_msg").hide();
			//jQuery(".qstn_wizard_error_msg").empty();
			//
			//rt = 1;
		}
	});
	if(factory == 0){
		return false;
	}else{
		return true;	
	}
}

function boilersValidate(){
	jQuery(".qstn_wizard_error_msg").css("display","none");
	var boilers = 1;
	jQuery('.boilerssection ul li').each(function(i){
		var str = jQuery(this).attr('id');
		var curr_id = str.split('_');
		var qsans = "";
		var qsans = jQuery("#hid_boilers_"+curr_id[2]).val();
		var ansValid = qsans.split('_');
		if(ansValid[1] == "ActiveBox"){
			jQuery("#qstn_boilers_"+curr_id[2]).addClass('question-error');
			jQuery(".qstn_wizard_error_msg").css("display","block");
			jQuery(".qstn_wizard_error_msg").html("Please answer the question");
			boilers = 0;
		}else{
			jQuery("#qstn_boilers_"+curr_id[2]).removeClass('question-error');
			//jQuery(".qstn_wizard_error_msg").hide();
			//jQuery(".qstn_wizard_error_msg").empty();
			//
			//rt = 1;
		}
	});
	if(boilers == 0){
		return false;
	}else{
		return true;	
	}
}

