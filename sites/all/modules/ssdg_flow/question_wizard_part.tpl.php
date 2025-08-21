<?php //print_r($form['#estid']);
if ((isset($form['#estid'])) && (!empty($form['#estid']))){
	$estid_val = $form['#estid'];
} 
else{
	$estid_val = '';
}
/*print_r($estid_val);
exit;*/
?>
<style>
.wizard_steps a {
	background:none;
	color:#34495e !important;
}
.custom_margin {
	margin-left:0px !important;
}
.custom-top-margin {
	margin-top:21px;
}
.stepContainer{
	height:auto !important;
}
.displaynone{ display:none; }
ul.messages .question-error .message_wrapper blockquote{border-left:5px solid #cc0101; color: #cc0101; }
.not-active {
   pointer-events: none;
   cursor: default;
}

 .buttongreen {
  text-align: center;
  padding:6px 10px 6px 10px;
  font-size: 12px;
  line-height:15px;
  border-radius: 15px;
  border:none;
  box-shadow:none;
}


.modal-dialog {
    width: 1000px !important;
    margin: 30px auto;
}
</style>
<?php global  $user,$base_root,$base_path,$base_url ;?>
<?php
	$query = db_delete('ld_elligibility_question_answer');
	$query->condition('current_session_id', $_SESSION['CURRENT_SESSION']);
	$rs = $query->execute();
	
	unset($_SESSION['CURRENT_SESSION']);
	$current_session=session_id();
	$_SESSION['CURRENT_SESSION']=$current_session;
	// check if user is permanent or not
	/*$query = db_select('ld_users_details', 'ud');
	$query ->fields('ud', array('ldapplicationflag'));
	$query->condition('ud.uid',$user->uid,'=');
	$result = $query->execute();
	$data = $result->fetchAssoc();*/
	/*if(!empty($data)){
		if($data['ldapplicationflag'] == 1){
			drupal_goto('dashboard1');
		}else{
			// for temporary user delete all data from ld_elligibility_question_answer
			$query = db_delete('ld_elligibility_question_answer');
			$query->condition('uid', $user->uid);
			$rs = $query->execute();
		}
	}else{
		drupal_set_message('You are not authorized user');
		drupal_goto('disclaimer');
	}*/

	if(@$_REQUEST["lcqstnsubmit"] == "SubmitData"){
		
		//print_r($_REQUEST['hidval']);
		foreach($_REQUEST['hidval'] as $val){
			if(!empty($val)){
				$myArr = explode("_",$val);
				//print_r($myArr);
				//exit;
				
				/*$query = db_select('ld_elligibility_question_answer', 'us');
				$query ->fields('us', array('id'));
				$query->condition('us.question_id',trim($myArr[0]),'=');
				$query->condition('us.answer',trim($myArr[1]),'=');
				$query->condition('us.directorate_code','LC','=');
				$query->condition('us.uid',trim($user->uid),'=');
				$result = $query->execute();
				$data = $result->fetchAssoc();
				if(empty($data)){*/
					
					/*$query = db_select('ld_elligibility_question_answer', 'us');
					$query ->fields('us', array('id'));
					$query->condition('us.question_id',trim($myArr[0]),'=');
					$query->condition('us.directorate_code','LC','=');
					$query->condition('us.uid',trim($user->uid),'=');
					$result = $query->execute();
					$data = $result->fetchAssoc();
					if(!empty($data)){
						
						$qsAns = db_update('ld_elligibility_question_answer');
						$qsAns->fields(array('answer' => $myArr[1]));
						$qsAns->condition('question_id', $myArr[0]);
						$qsAns->condition('directorate_code', 'LC');
						$qsAns->condition('uid', $user->uid);
						$rs = $qsAns->execute();
						
					}else{*/
					
						$qsAns 		= 	array(
							'question_id' 	=> $myArr[0], 
							'answer' 		=> $myArr[1], 
							'directorate_code' => $myArr[2],
							//'uid' 			=> $user->uid,
							'uid' 			=> NULL,
							'current_session_id' => $current_session
						);
						db_insert('ld_elligibility_question_answer')->fields($qsAns)->execute();
					//}
				//}
			}
		}
		if($estid_val != ''){
		drupal_goto('elligibility_entitlements/'.$estid_val);
		} else {
			drupal_goto('elligibility_entitlements');
		}
		
	}
 	/*if(@$_REQUEST["questionsubmit"]){
		header("location:http://wblabour.gov.in/elligibility_entitlements");
		exit;
	}*/
  ?>
<link href="<?php print $base_path ?>sites/all/modules/dashboard/build/css/custom.css" rel="stylesheet">
<div class="messages error qstn_wizard_error_msg" style="display:none"></div>
<div class="container body">
  <div class="main_container">
    <div class="x_panel">
      <div class="x_title"><div><h1><span>Q</span>uestion Wizard</h1></div></div>
      <!--<div style="width:40%;float:left;margin: -38px 0px 0px 434px;"><a href="<?php print $base_root.$base_path?>elligibility_entitlements">Skip Question Wizard</a></div>-->
      <div class="x_content">
      <fieldset>
      <input type="hidden" name="questionsubmit" value="questionsubmit" />
        <!--<div class="progress progress_sm">
          <div id="progressBar" class="progress-bar bg-green" role="progressbar" data-transitiongoal="0"></div>
        </div>-->
        <div id="wizard" class="form_wizard wizard_horizontal question_wizar">
          <ul class="wizard_steps">
            <li> <a href="#step-1" class="not-active"> <span class="step_no">1</span> <span class="step_descr"> Part 1<br />
              <!--<small>Step 1 description</small> </span>--> </a> </li>
            <li> <a href="#step-2" class="not-active"> <span class="step_no">2</span> <span class="step_descr"> Part 2<br />
              <!--<small>Step 2 description</small>--> </span> </a> </li>
            <li> <a href="#step-3" class="not-active"> <span class="step_no">3</span> <span class="step_descr"> Part 3<br />
             <!-- <small>Step 3 description</small>--> </span> </a> </li>
            <!--<li> <a href="#step-4"> <span class="step_no">4</span> <span class="step_descr"> Step 4<br />
              <small>Step 4 description</small> </span> </a> </li>-->
          </ul>
          <form name="frm" method="post" action="">
          





          <div id="step-1" class="lcsection">
            <ul class="messages">
            <?php
			$sort='ASC';
			$query = db_select('ld_question_master', 'q');
			//$query->leftJoin('ld_question_answer_transaction', 'qa', 'qa.question_id=q.id');
			$query ->fields('q', array( 'id','question'));
			//$query ->fields('qa', array( 'question_id','answer','next_question_id','service_id'));
			//$query->condition('us.uid',trim($user->uid),'=');
			$query->condition('q.directorate_code','LC','=');
			$query->orderBy('id',$sort);
			$question = $query->execute();
			$questiondata = $question->fetchAll();
			$i = 0;
			foreach($questiondata as $val){
				$i++;	
			
			$query1 = db_select('ld_question_answer_transaction', 'qa');	
			$query1 ->fields('qa', array( 'question_id','answer','next_question_id','service_id'));
			$query1->condition('qa.question_id',trim($val->id),'=');
			$query1->condition('qa.answer','Y','=');
			$query1->condition('qa.directorate_code','LC','=');
			$answer1 = $query1->execute();
			$answerdata1 = $answer1->fetchAssoc();
			
			
			$query2 = db_select('ld_question_answer_transaction', 'qa');	
			$query2 ->fields('qa', array( 'question_id','answer','next_question_id','service_id'));
			$query2->condition('qa.question_id',trim($val->id),'=');
			$query2->condition('qa.answer','N','=');
			$query2->condition('qa.directorate_code','LC','=');
			$answer2 = $query2->execute();
			$answerdata2 = $answer2->fetchAssoc();
			//print_r($answerdata2); exit;
			
			$sort='ASC';
			$query_popup_lc = db_select('ld_question_list', 'ql');	
			$query_popup_lc ->fields('ql', array( 'id','question_id','list_description'));
			$query_popup_lc->condition('ql.question_id',trim($val->id),'=');
			$query_popup_lc->condition('ql.directorate_code','LC','=');
			$query_popup_lc->orderBy('id',$sort);
			$answer_popup_lc = $query_popup_lc->execute();
			$answerpopupdata_lc = $answer_popup_lc->fetchAll();
			?>
            
            
              <li class="qutn_hide" id="qstn_<?php print $val->id;?>">
                <div class="message_date custom-top-margin">
                  <div class="btn-group" data-toggle="buttons">
                    <label class="btn btn-default" id="btn-yes-<?php print $val->id;?>" onclick="callProgress(this,'<?php print $val->id;?>','<?php echo $answerdata1['next_question_id']."_".$answerdata2['next_question_id'];?>','Y','LC')">
                      <input type="radio" name="qs1" id="option1" value="1">
                      YES </label>
                    <label class="btn btn-default" id="btn-no-<?php print $val->id;?>" onclick="callProgress(this,'<?php print $val->id;?>','<?php echo $answerdata1['next_question_id']."_".$answerdata2['next_question_id'];?>','N','LC')">
                      <input type="radio" name="qs1" id="option2" value="0">
                      No </label>
                      <input type="hidden" name="hidval[]" id="hid_<?php print $val->id;?>" value="" />
                  </div>
                </div>
                <div class="message_wrapper custom_margin">
                  <h4 class="heading">Question <?php //print $val->id;?></h4>
                  <!--<blockquote class="message"><?php print $val->question;?></blockquote>-->
                  <blockquote class="message"><?php print $val->question;?>
					  <?php
                        if(!empty($answerpopupdata_lc)){ ?>
                        <!--<button type="button" class="btn-primary btn-circle btn-lg" data-toggle="modal" data-target="<?php echo '#myModal_'.$val->id;?>">
                           <i class="" aria-hidden="true"> </i> 
                        </button>-->
                        <button type="button" class="btn-primary btn-circle btn-lg buttongreen" data-toggle="modal" data-target="<?php echo '#myModal_'.$val->id;?>">
                        <i class="fa fa-info">
                        </i> Click Here</button>
                         <div id="<?php echo 'myModal_'.$val->id;?>" class="modal fade" role="dialog" data-backdrop="static">
                          <div class="modal-dialog">
                            <!-- Modal content-->
                            <div class="modal-content">
                              <div class="modal-header">
                                <button type="button" class="close" data-dismiss="modal">&times;</button>
                                <h4 class="modal-title">Information</h4>
                              </div>
                                      <div class="modal-body">
                                <?php
                                    foreach($answerpopupdata_lc as $list1){
                             ?>
                                    <p><?php echo trim($list1->list_description);?></p>
                              <?php /*?><span class="tooltiptext"><?php echo trim($list->list_description);?></span><?php */?>
                              <?php }?>
                               </div>
                          <div class="modal-footer">
                            <button type="button" class="btn btn-danger" data-dismiss="modal">Close</button>
                          </div>
                        </div>
                      </div>
                    </div>	
                     <?php }?>
                  </blockquote>
                  <br />
                </div>
              </li>
            <?php }?>
            </ul>
          </div>
          
          <div id="step-2" class="factorysection">
            <ul class="messages">
            <?php
			$sort='ASC';
			$query = db_select('ld_question_master', 'q');
			$query ->fields('q', array( 'id','question'));
			$query->condition('q.directorate_code','F','=');
			$query->orderBy('id',$sort);
			$question = $query->execute();
			$questiondata = $question->fetchAll();
			$i = 0;
			foreach($questiondata as $val){
				$i++;	
			
			$query1 = db_select('ld_question_answer_transaction', 'qa');	
			$query1 ->fields('qa', array( 'question_id','answer','next_question_id','service_id'));
			$query1->condition('qa.question_id',trim($val->id),'=');
			$query1->condition('qa.answer','Y','=');
			$query1->condition('qa.directorate_code','F','=');
			$answer1 = $query1->execute();
			$answerdata1 = $answer1->fetchAssoc();
			
			
			$query2 = db_select('ld_question_answer_transaction', 'qa');	
			$query2 ->fields('qa', array( 'question_id','answer','next_question_id','service_id'));
			$query2->condition('qa.question_id',trim($val->id),'=');
			$query2->condition('qa.answer','N','=');
			$query2->condition('qa.directorate_code','F','=');
			$answer2 = $query2->execute();
			$answerdata2 = $answer2->fetchAssoc();
			//print_r($answerdata2); exit;
			
			$query_popup = db_select('ld_question_list', 'ql');	
			$query_popup ->fields('ql', array( 'id','question_id','list_description'));
			$query_popup->condition('ql.question_id',trim($val->id),'=');
			$query_popup->condition('ql.directorate_code','F','=');
			$answer_popup = $query_popup->execute();
			$answerpopupdata = $answer_popup->fetchAll();
			
			?>
              <li class="qutn_hide" id="qstn_factory_<?php print $val->id;?>">
                <div class="message_date custom-top-margin">
                  <div class="btn-group" data-toggle="buttons">
                    <label class="btn btn-default" id="btn-yes-factory-<?php print $val->id;?>" onclick="callProgressFactory(this,'<?php print $val->id;?>','<?php echo $answerdata1['next_question_id']."_".$answerdata2['next_question_id'];?>','Y','F')">
                      <input type="radio" name="qs1" id="option1" value="1">
                      YES </label>
                    <label class="btn btn-default" id="btn-no-factory-<?php print $val->id;?>" onclick="callProgressFactory(this,'<?php print $val->id;?>','<?php echo $answerdata1['next_question_id']."_".$answerdata2['next_question_id'];?>','N','F')">
                      <input type="radio" name="qs1" id="option2" value="0">
                      No </label>
                      <input type="hidden" name="hidval[]" id="hid_factory_<?php print $val->id;?>" value="" />
                  </div>
                </div>
                <div class="message_wrapper custom_margin">
                  <h4 class="heading">Question <?php //print $val->id;?></h4>
                  <blockquote class="message"><?php print $val->question;?>
					  <?php
                        if(!empty($answerpopupdata)){ ?>
                        <!--<button type="button" class="btn-primary btn-circle btn-lg" data-toggle="modal" data-target="<?php echo '#myModal_'.$val->id;?>">
                           <i class="" aria-hidden="true"> </i> 
                        </button>-->
                        <button type="button" class="btn-primary btn-circle btn-lg buttongreen" data-toggle="modal" data-target="<?php echo '#myModal_'.$val->id;?>">
                        <i class="fa fa-info">
                        </i> Click Here</button>
                         <div id="<?php echo 'myModal_'.$val->id;?>" class="modal fade" role="dialog" data-backdrop="static">
                          <div class="modal-dialog">
                            <!-- Modal content-->
                            <div class="modal-content">
                              <div class="modal-header">
                                <button type="button" class="close" data-dismiss="modal">&times;</button>
                                <h4 class="modal-title">Information</h4>
                              </div>
                                      <div class="modal-body">
                                <?php
                                    foreach($answerpopupdata as $list){
                             ?>
                                    <p><?php echo trim($list->list_description);?></p>
                              <?php /*?><span class="tooltiptext"><?php echo trim($list->list_description);?></span><?php */?>
                              <?php }?>
                               </div>
                          <div class="modal-footer">
                            <button type="button" class="btn btn-danger" data-dismiss="modal">Close</button>
                          </div>
                        </div>
                      </div>
                    </div>	
                     <?php }?>
                  </blockquote>
                  <br />
                </div>
              </li>
            <?php }?>
            </ul>
          </div>
          
          
          <div id="step-3" class="boilerssection">
            <ul class="messages">
            <?php
			$sort='ASC';
			$query = db_select('ld_question_master', 'q');
			$query ->fields('q', array( 'id','question'));
			$query->condition('q.directorate_code','B','=');
			$query->orderBy('id',$sort);
			$question = $query->execute();
			$questiondata = $question->fetchAll();
			$i = 0;
			foreach($questiondata as $val){
				$i++;	
			
			$query1 = db_select('ld_question_answer_transaction', 'qa');	
			$query1 ->fields('qa', array( 'question_id','answer','next_question_id','service_id'));
			$query1->condition('qa.question_id',trim($val->id),'=');
			$query1->condition('qa.answer','Y','=');
			$query1->condition('qa.directorate_code','B','=');
			$answer1 = $query1->execute();
			$answerdata1 = $answer1->fetchAssoc();
			
			
			$query2 = db_select('ld_question_answer_transaction', 'qa');	
			$query2 ->fields('qa', array( 'question_id','answer','next_question_id','service_id'));
			$query2->condition('qa.question_id',trim($val->id),'=');
			$query2->condition('qa.answer','N','=');
			$query2->condition('qa.directorate_code','B','=');
			$answer2 = $query2->execute();
			$answerdata2 = $answer2->fetchAssoc();
			//print_r($answerdata2); exit;
			?>
              <li class="qutn_hide" id="qstn_boilers_<?php print $val->id;?>">
                <div class="message_date custom-top-margin">
                  <div class="btn-group" data-toggle="buttons">
                    <label class="btn btn-default" id="btn-yes-boilers-<?php print $val->id;?>" onclick="callProgressBoilers(this,'<?php print $val->id;?>','<?php echo $answerdata1['next_question_id']."_".$answerdata2['next_question_id'];?>','Y','B')">
                      <input type="radio" name="qs1" id="option1" value="1">
                      YES </label>
                    <label class="btn btn-default" id="btn-no-boilers-<?php print $val->id;?>" onclick="callProgressBoilers(this,'<?php print $val->id;?>','<?php echo $answerdata1['next_question_id']."_".$answerdata2['next_question_id'];?>','N','B')">
                      <input type="radio" name="qs1" id="option2" value="0">
                      No </label>
                      <input type="hidden" name="hidval[]" id="hid_boilers_<?php print $val->id;?>" value="" />
                  </div>
                </div>
                <div class="message_wrapper custom_margin">
                  <h4 class="heading">Question <?php //print $val->id;?></h4>
                  <blockquote class="message"><?php print $val->question;?></blockquote>
                  <br />
                </div>
              </li>
            <?php }?>
              
            </ul>
            
          </div>
          <div class="actionBar"><input type="hidden" name="lcqstnsubmit" value="SubmitData"  /></div>
          </form>
          <!--<div id="step-4">
            <h2 class="StepTitle">Question No. 11</h2>
            <p> do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu
              fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.</p>
            <label class="switch switch-flat">
						<input class="switch-input" type="checkbox" />
						<span class="switch-label" data-on="Yes" data-off="No"></span> <span class="switch-handle"></span> 
                </label>
          </div>-->
        </div>
      </fieldset>  
      </div>
    </div>
  </div>
</div>
<script language="javascript" src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/js/jquery.min.js"></script> 

<!-- Bootstrap --> 
<script src="<?php print $base_path ?>sites/all/modules/dashboard/vendors/bootstrap/dist/js/bootstrap.min.js"></script> 
<!-- jQuery Smart Wizard --> 
<script src="<?php print $base_path ?>sites/all/modules/dashboard/vendors/jQuery-Smart-Wizard/js/jquery.smartWizard.js"></script> 
<!-- bootstrap-progressbar --> 
<script src="<?php print $base_path ?>sites/all/modules/dashboard/vendors/bootstrap-progressbar/bootstrap-progressbar.min.js"></script> 
<!-- Custom Theme Scripts --> 
<script src="<?php print $base_path ?>sites/all/modules/dashboard/build/js/custom.min.js"></script> 
<script src="<?php print $base_path ?>sites/all/modules/ssdg_flow/js/question_wizard.js"></script> 
 
<script>
   jQuery(document).ready(function() {
	//jQuery('#menu').menu();
	var timer;
	
        jQuery('li.dropdown').on('mouseenter', function (event) {

			//alert('ok');
            event.stopImmediatePropagation();
            event.stopPropagation();

            jQuery(this).removeClass('open menu-animating').addClass('menu-animating');
            var that = this;


            if (timer) {
                clearTimeout(timer);
                timer = null;
            }


            timer = setTimeout(function () {

                jQuery(that).removeClass('menu-animating');
                jQuery(that).addClass('open');

            }, 300);   // 300ms as animation end time


        });

        // on mouse leave

        jQuery('li.dropdown').on('mouseleave', function (event) {

            var that = this;

            jQuery(this).removeClass('open menu-animating').addClass('menu-animating');


            if (timer) {
                clearTimeout(timer);
                timer = null;
            }

            timer = setTimeout(function () {

                jQuery(that).removeClass('menu-animating');
                jQuery(that).removeClass('open');

            }, 300);  // 300ms as animation end time

        });
	
});
    </script>