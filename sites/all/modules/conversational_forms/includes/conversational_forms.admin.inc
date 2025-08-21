<?php

/**
 * Implements hook_form().
 * Admin settings.
 */
function conversational_forms_admin_settings() {
	$form = array();

	$form['conversational_forms_library_url'] = array(
		  '#type' => 'textfield',
		  '#title' => t('Path to conversational forms library'),
		  '#description' => t('Get the url of latest library from !github', array('!github' => l('github', 'https://github.com/space10-community/conversational-form/'))),
		  '#default_value' => CONVERSATIONAL_FORMS_LIB,
		);

	return system_settings_form($form);
}
