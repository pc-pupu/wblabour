(function($) {
  Drupal.behaviors.applicant_registration = {
  attach: function (context, settings) { 
  	$("#applicant-registration-form").validationEngine('attach', {
    	promptPosition : "bottomLeft",
		autoHidePrompt:true
     });
	}};
})(jQuery);


