(function($){

	Drupal.behaviors.cofo_conditionals = {
		attach: function (context, settings) {
			var condition = {};
			var callback;
			var value = [];
			if (Drupal.settings.webform && Drupal.settings.webform.conditionals) {
				$.each(Drupal.settings.webform.conditionals, function (formKey, settings) {
		    		$.each(settings.ruleGroups, function(rgid_key, rule_group){
							value = [];
		    			$.each(rule_group.rules, function(m, rule){
		    				condition.source = rule.source;
		    				value.push(rule.value);
		    				callback = rule.callback;
		    			});
							condition.value = value.join('||');
		    			$.each(rule_group.actions, function(m, action){
								condition.callback = callback;
		    				condition.action = action.action;
		    				condition.target = action.target;
		    				condition.invert = action.invert;
		    				condition.argument = action.argument;
								// Process every condition.
			    			cofo_conditional(condition);
		    			});
		    		});
		    	});
			}

			function cofo_conditional(condition) {
				var name;
				name = $('.'+condition.source+' input').first().attr('name');
				type = $('.'+condition.source+' input').first().attr('type');
				// Manage 'isnt' condition/condition.invert.
				if (condition.invert == '1') {
					switch(condition.callback){
						case 'conditionalOperatorStringEqual':
						  condition.callback = 'conditionalOperatorStringNotEqual';
						  break;

						case 'conditionalOperatorStringNotEqual':
						  condition.callback = 'conditionalOperatorStringEqual';
						  break;

						case 'conditionalOperatorStringDoesNotContain':
						  condition.callback = 'conditionalOperatorStringContains';
						  break;

						case 'conditionalOperatorStringContains':
						  condition.callback = 'conditionalOperatorStringDoesNotContain';
						  break;

						case 'conditionalOperatorStringBeginsWith':
						  condition.callback = 'conditionalOperatorStringNegateBeginsWith';
						  break;

						case 'conditionalOperatorStringEndsWith':
						  condition.callback = 'conditionalOperatorStringNegateEndsWith';
						  break;

						case 'conditionalOperatorStringEmpty':
						  condition.callback = 'conditionalOperatorStringNotEmpty';
						  break;

						case 'conditionalOperatorStringNotEmpty':
						  condition.callback = 'conditionalOperatorStringEmpty';
						  break;
					}

				}

				switch(condition.callback){
					case 'conditionalOperatorStringEqual':
					  if (type == 'text') {
					  	value = '^'+condition.value+'$';
					  }
					  else {
					  	value = condition.value;
					  }
					  break;

					case 'conditionalOperatorStringNotEqual':
					  value = '^(?!'+condition.value+'$)';
					  break;

					case 'conditionalOperatorStringDoesNotContain':
					  value = '^(?!.*'+condition.value+'.*)';
					  break;

					case 'conditionalOperatorStringBeginsWith':
					  value = '^'+condition.value;
					  break;

					case 'conditionalOperatorStringNegateBeginsWith':  // Custom callback for invert condition.
					  value = '^(?!^'+condition.value+'.*)';
					  break;

					case 'conditionalOperatorStringEndsWith':
					  value = condition.value+'$';
					  break;

					case 'conditionalOperatorStringNegateEndsWith': // Custom callback for invert condition.
					  value = '^(?!.*'+condition.value+'$)';
					  break;

					case 'conditionalOperatorStringEmpty':
					  value = '^\s*$';
					  break;

					case 'conditionalOperatorStringNotEmpty':
					  value = '(?!^\s*$)';
					  break;

					case 'conditionalOperatorStringContains':
					default:
					  value = condition.value;
				}

				$('.'+condition.target).find('input').attr('cf-conditional-'+name, value);

			}

		}
	};

	Drupal.behaviors.cofo_alter_webform = {
	    attach: function (context, settings) {
	      $('form').find('input').removeAttr('disabled');
		  $('form').find('input').show();
		  $('.webform-component').show();
		}
	};

})(jQuery);
