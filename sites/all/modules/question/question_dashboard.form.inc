<?php

//for add of Question

function question_dashboard($form, &$form_state) {
     
	 global $base_root, $base_path;	
	 drupal_add_css(drupal_get_path('module', 'question_dashboard') . '/css/sky-forms.css');
     drupal_add_css(drupal_get_path('module', 'question_dashboard') . '/css/form-design.css');
	
	$form['#attributes']['class'][] = 'sky-form custom-form-main';

	 $form['question'] = array(
		'#title' => t(''),
	    '#rows'=> 3,
	    '#type' => 'textarea',
		'#attributes' => array('class'=>array(''), 'placeholder'=>'Question Entry', 'autocomplete' => 'off'),
		'#required' => TRUE,
		'#prefix'=>'<div class="x_panel"><div class="x_title"><h1><span>W</span>izard Entry</h1></div><div class="x_content"><fieldset>
		  			  <div class="row"><section><label class="textarea"><i class="icon-prepend fa-question"></i>Question Entry',
	     '#suffix' => '</label></section></div></fieldset>'
	);	

	$form['submit'] = array (
        '#type' => 'submit',
        '#value' => 'Submit',
		'#attributes' => array('class'=>array('btn btn-success pull-right')),
		'#prefix' => '<footer>',
  		'#suffix' => '</footer>',
     );
	
  	$form['reset'] = array(
	   '#type' => 'markup',
	   '#markup' => '<input type="reset" value="Reset" class="btn btn-success pull-right">',
  	   '#suffix' => '</div></div>',
   );		
    
  return $form;
}


// for dashboard of Question

function question_dashboard_form() {
    
	 $header = array(
	        array('data'=> 'SL.NO'),
           	//array('data'=> 'Question', 'field' => 'question', 'sort' => 'asc'),
			array('data'=> 'Question'),
			array('data'=> 'Edit'),
			array('data'=> 'Status'),
	  );
  //$sort = 'ASC';
  $query = db_select('ld_question_master', 'q');
  $query->fields('q', array('id', 'question', 'status'));
  //$query->orderBy($sort);
  $table_sort = $query->extend('TableSort') // Add table sort extender.
                      ->orderByHeader($header); // Add order by headers.
  $pager = $table_sort->extend('PagerDefault')
                      ->limit(10);
  $result = $pager->execute();
  
  $i=0;
  foreach ($result as $dbrow) {
  $i++;
		if($dbrow->status==1){
			$status_img = "status_on.png";
		}else if($dbrow->status==0){
			$status_img = "status_off.png";
		}else{
			$status_img = "status_off.png";
		}
		
        $rows[] =array(
						$i,
       				    $dbrow->question,
						array('data' => l(t('<img src="'.$GLOBALS['base_url']."/".drupal_get_path('theme', 'labourdept').'/images/edit.png">'), 
		      			'question-dashboard/edit/'.$dbrow->id, array('html' => TRUE, 'attributes'=>array('title' => 'Edit')))),
						array('data' => l(t('<img src="'.$GLOBALS['base_url']."/".drupal_get_path('theme', 'labourdept').'/images/'.$status_img.'">'), 
		      			'question-dashboard/changeStatus/'.$dbrow->id.'/'.$dbrow->status, array('html' => TRUE, 'attributes'=>array('title' => 'Status')))),
      				 );
    }
	
  // If rows are not empty theme and display the rows.
  $output = '';
  $output .= l(t('<img src="'.$GLOBALS['base_url']."/".drupal_get_path('theme', 'labourdept').'/images/addbtn.png">'), 'question-dashboard/add', array('html' => TRUE, 'attributes'=>array('class' => 'addbtn')));
  if (!empty($rows)) {
   	 $output .= theme('table', array('header' => $header, 
									'rows' => $rows,
									'attributes' => array('class' => array('table', 'table-bordered')),
									'sticky' => true,
									'caption' => "",
									'colgroups' => array(),
									'empty' => t("Table has no rows")));
	$output .= theme('pager');
  }
  else {
    $output .= t("No results found.");
  }
  
  return $output;
}

// for edit of question

 function question_dashboard_edit_form($form, &$form_state, $args=''){
	 
	$query = db_select('ld_question_master','q')
 			->fields('q',array('id', 'question'))
 			->condition('q.id',trim($args),'=');
	$result = $query->execute();
	$question_mode_rs = $result->fetchAll();
	/*echo "<pre>";
	print_r($trust_type_rs);
	exit;*/
  
  global $base_root, $base_path;	
	 drupal_add_css(drupal_get_path('module', 'question_dashboard') . '/css/sky-forms.css');
     drupal_add_css(drupal_get_path('module', 'question_dashboard') . '/css/form-design.css');
	
	$form['#attributes']['class'][] = 'sky-form custom-form-main';

	 $form['question'] = array(
		'#title' => t(''),
	    '#rows'=> 3,
	    '#type' => 'textarea',
		'#attributes' => array('class'=>array(''), 'placeholder'=>'Question Entry', 'autocomplete' => 'off'),
		'#required' => TRUE,
		'#default_value' => isset($question_mode_rs[0]->question) ? $question_mode_rs[0]->question : NULL,
		'#prefix'=>'<div class="x_panel"><div class="x_title"><h1><span>W</span>izard Edit</h1></div><div class="x_content"><fieldset>
		  			  <div class="row"><section><label class="textarea"><i class="icon-prepend fa-question"></i>Edit Question',
	     '#suffix' => '</label></section></div>'
	);	
	
	$form['question_id'] = array(
		'#title' => t('Question Id'),
		'#type' => 'textfield',
		'#default_value' => isset($question_mode_rs[0]->id) ? $question_mode_rs[0]->id : NULL,
		'#prefix'=>'<div class="row"><section><label class="textarea">Edit Question',
	    '#suffix' => '</label></section></div></fieldset>'
	);	

	$form['submit'] = array (
        '#type' => 'submit',
        '#value' => 'Submit',
		'#attributes' => array('class'=>array('btn btn-success pull-right')),
		'#prefix' => '<footer>',
  		'#suffix' => '</footer>',
     );
	
  	$form['reset'] = array(
	   '#type' => 'markup',
	   '#markup' => '<input type="reset" value="Reset" class="btn btn-success pull-right">',
  	   '#suffix' => '</div></div>',
   );		
    
  return $form;
}


// for status Change

function question_dashboard_status_change($question_id='',$status=''){
	if($status==1){
		$status = 0;
	}else{
		$status = 1;
	}
	$query = db_update('ld_question_master');
	$query->fields(array('status' => $status));
	$query->condition('id', $question_id);
	$rs = $query->execute();
	drupal_set_message("Your data has been updated successfully");
	drupal_goto('question-dashboard');
}
