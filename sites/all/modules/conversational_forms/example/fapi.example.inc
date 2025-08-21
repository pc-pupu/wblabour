<?php

/**
 * @file
 *  Example of using conversational forms with drupal's FAPI.
 */

/**
 * Implements hook_form().
 */
function conversational_forms_fapi_example_form() {
	$form = array();

	$form['#attached']['js'] = array(
	  CONVERSATIONAL_FORMS_LIB,
	);
	$form['#attributes'] = array(
	  	  'cf-form' => 'cf-form',
	  	  'cf-context' => 'cf-context',
	  	);
	$form['learn'] = array(
	  '#type' => 'textfield',
	  '#title' => t('Learn'),
	  '#attributes' => array(
	  	  'cf-questions' => t('Hi. Do you want to learn about Conversational forms?'),
	  	),
	);
	$form['about_this_example'] = array(
	  '#type' => 'radios',
	  '#title' => t('About this example'),
	  '#options' => array('yes' => 'Yes'),
	  '#attributes' => array(
	  	  'cf-questions' => t('This is an example of conversational form built on drupal form API. You can browse the code of this page inside the module directory at "example/fapi.example.inc". Follow the documentation to convert your custom forms to a form like this. Do you want to know how to theme it better?'),
	  	),
	);
	$form['how_to_theme'] = array(
	  '#type' => 'textfield',
	  '#title' => t('About this example'),
	  '#attributes' => array(
	  	  'cf-questions' => t('You can overwrite the CSS like any other page. You may need to use the "!important" to overwite certain parts.'),
	  	),
	);
	$form['more'] = array(
	  '#type' => 'radios',
	  '#title' => t('More about this example'),
	  '#options' => array('ok' => 'Ok'),
	  '#attributes' => array(
	  	  'cf-questions' => t('To know more about the module, checkout the module page. If you find and isssue, please contribute to the issue queue at https://www.drupal.org/project/issues/conversational_forms?categories=All'),
	  	),
	);

	$form['submit'] = array(
		  '#type' => 'submit',
		  '#value' => t('Submit'),
		);

	return $form;
}

/**
 * Submit handler for conversational_forms_fapi_example_form().
 */
function conversational_forms_fapi_example_form_submit($form, &$form_state) {
	$form_state['redirect'] = '/admin/config/content/conversational-forms';
}
