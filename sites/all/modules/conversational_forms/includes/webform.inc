<?php

function conversational_forms_webform_component_render_alter(&$element, &$component) {

	$cf_enabled = conversational_forms_is_enabled($component['nid']);
	if ($cf_enabled == FALSE) return;
	$element['#attributes'] = array(
		  'cf-questions' => $component['extra']['cf-questions'],
		  'cf-error' => $component['extra']['cf-error'],
		  'cf-input-placeholder' => $component['extra']['cf-input-placeholder'],
		);
	if (!empty($component['extra']['cf-pattern'])) {
		$element['#attributes']['pattern'] = $component['extra']['cf-pattern'];
	}

	if ($component['required']) {
		$element['#attributes']['required'] = 'required';
	}
}

function conversational_forms_webform_component_defaults_alter(&$defaults, $type) {

  // Add a default for a new field added via hook_form_alter() or
  // hook_form_FORM_ID_alter() for all component types.
  $defaults['extra']['cf-questions'] = '';
  $defaults['extra']['cf-error'] = '';
  $defaults['extra']['cf-pattern'] = '';
  $defaults['extra']['cf-add-to-webform'] = '';
  $defaults['extra']['cf-input-placeholder'] = '';

}

function conversational_forms_form_webform_component_edit_form_alter(&$form, &$form_state, $form_id) {

	$cf_add = conversational_forms_is_enabled($form['#node']->nid);
	if (!$cf_add) {
		return;
	}

	$cf_questions = $cf_pattern = $cf_placeholder = $cf_error = '';

	$cid = $form['cid']['#value'];
	$components = $form['#node']->webform['components'];

	if (isset($components[$cid])) {
		$cf_pattern = $components[$cid]['extra']['cf-pattern'];
		$cf_questions = $components[$cid]['extra']['cf-questions'];
		$cf_error = $components[$cid]['extra']['cf-error'];
		$cf_placeholder = $components[$cid]['extra']['cf-input-placeholder'];
	}

	$form['#attached']['js'] = array(
		drupal_get_path('module', 'conversational_forms') . "/js/conversational_forms_form.js",
		);
    $form['#attached']['js'][] = array(
	  'data' => array(
	  	'cofo' => conversational_forms_id_tokens($components, $cid)
	  	),
	  'type' => 'setting',
	);

	$form['extra']['cf-questions'] = array(
	  '#type' => 'textarea',
	  '#title' => t('CF Questions'),
	  '#default_value' => $cf_questions,
	  '#description' => t("<p>If specified, this question will be presented to the user instead of the label.</p>Seperate with || to allow for more questions, library will shuffle. e.g. <em>Q1||Q2||Q3</em>. Seperate with && to allow for chained questions. Also you can use tokens to include previous user input.</p>!tokens",
	  	    array(
	  	    	'!tokens' => l('Available Tokens', '', array(
	  	    		'fragment' => 'cf-ques-available-tokens',
	  	    		'external' => TRUE,
	  	    		'attributes' => array('id' => 'cf-ques-available-tokens'),
	  	    	  )
	  	    	)
	  	      )
	  	    ),
	);
	$form['extra']['cf-input-placeholder'] = array(
	  '#type' => 'textarea',
	  '#title' => t('CF Placeholder'),
	  '#default_value' => $cf_placeholder,
	  '#description' => t('This text will show as placeholder in the user input field. You can customize it to provide help text or answering tips to the user.'),
	);
	$form['extra']['cf-pattern'] = array(
	  '#type' => 'textarea',
	  '#title' => t('CF Pattern'),
	  '#default_value' => $cf_pattern,
	  '#description' => t('!regex for field validation.', array('!regex' => l('Regex', 'http://www.html5pattern.com', array('attributes' => array('target'=>'_blank'))))),
	);
	$form['extra']['cf-error'] = array(
	  '#type' => 'textarea',
	  '#title' => t('CF Error'),
	  '#default_value' => $cf_error,
	  '#description' => t("<p>Configure the error message in case there is incorrect input.</p>Multiple errors can be defined to be shown randomly using a pipe e.g. <em>Question1|Question2|Question3</em>"),
	);
}


function conversational_forms_id_tokens($components, $cid) {
	$tokens = array();
	foreach ($components as $key => $component) {
		// Do not include components yet to be filled.
		if ($key == $cid) {
			break;
		}

		// This should cover almost every case. If it doesn't, use same logic
		// as in webform.module to create the id attribute.
		$id = 'edit-submitted-' . str_replace('_', '-', $component['form_key']);

		switch ($component['type']) {
			case 'select':
			    $options = _webform_select_options_from_text($component['extra']['items']);
			    $i = 0;
			    foreach ($options as $option) {
			    	$i++;
			    	$tokens[] = [
				    	  'field' => $option,
				    	  'token' => $id . '-' . $i,
				    	];
			    }
				break;

			default:
				$tokens[] = [
			    	  'field' => $component['name'],
			    	  'token' => $id,
			    	];
				break;
		}
	}
	return $tokens;
}
