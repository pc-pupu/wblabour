<?php

 function question_dashboard_submit($form, &$form_state) {

	//drupal_set_message('<pre>'.print_r($form_state['values'], TRUE).'</pre>');
	
	drupal_set_message("Your question has been successfully saved in the database!!!");
	
	$questionInfo = array('question'=>$form_state['values']['question']);
	db_insert('ld_question_master')->fields($questionInfo)->execute();
}


/*function payment_mode_edit_form_submit($form, &$form_state){
	$query = db_update('corr_payment_mode_mst');
	$query->fields(array('payment_mode' =>$form_state['values']['payment_mode_type']));
	$query->condition('id', $form_state['values']['payment_mode_id']);
	$rs = $query->execute();
	if($rs){
		drupal_set_message("Your data has been updated successfully");
		drupal_goto('payment-mode-dashboard');
	}
}*/
