(function($){
	Drupal.behaviors.cofo_tokens = {
	    attach: function (context, settings) {
	      var token_suggestions = '<div><b>Previous response</b>: {previous-answer}</div>';
	      if (settings.cofo) {
	      	$.each(settings.cofo, function(k,v){
	      	  token_suggestions += '<div><b>'+v.field+'</b>: {'+v.token+'}</div>';
	        });
	      }
	      $('#cf-ques-available-tokens', context).after('<div id="token-suggestions">'+token_suggestions+'</div>').click(function(){
	      	$('#token-suggestions', context).toggle("slow");
	      	return false;
	      });
	    }
	};
})(jQuery);