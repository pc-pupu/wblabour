<?php
function chkbadchar ($str, $title, $field_name) {
	$fieldskiplist = array("body");
	if(in_array($field_name, $fieldskiplist)){
		//Skip now
		$badch = array('<link', 'HTTP-', 'META','base64','iframe','SCRIPT','SELECT ','DROP ', 'INSERT ','DELETE ');
	}else{
		$badch = array('HTTP-', 'META','base64','iframe','SCRIPT','SELECT ','DROP ','--','INSERT ','DELETE ','#', '*', '^', '!',  '$', '~', '`');
		//Check for Non-Alphanumric characters	
		if(preg_match("/[^a-zA-Z0-9\@\,\.\_\-\:\s\/]+/", "$str")){
			form_set_error($field_name, t('%title field contains unsupported special characters. Please remove if any.', array('%title' => $title)));
			return;
		}else{
			//echo "inputs are good.";  exit;
		}
	
	}//End of skip list check
	if (!(is_null($str)) || trim($str)!="") {
		for ($i=0;$i<count($badch);$i++) {
			if (strpos(strtoupper($str),strtoupper($badch[$i])) !== false) {
				form_set_error($field_name, t('%title field contains unsupported characters or tags. Please remove if any (ie. %bad).', array('%title' => $title, '%bad' => $badch[$i])));
				return 0;
			}
		}
	}
}

// Telephone number validation
function telephone_validation ($str, $title, $field_name) {
	$goodchar = " 1234567890.-+";
	for ($i=0;$i<strlen($str);$i++) {
		if (strpos($goodchar,$str{$i}) == false) {
			form_set_error('title_length', $title . ' field doesn\'t contain valid telephone number.');
			return 0;
		}
	}
}



// date format validation


function isValidDate($date)
{
 if(preg_match("/^(\d{2})\/(\d{2})\/(\d{4})$/", $date, $matches))
 {
 
  if(checkdate($matches[2], $matches[1], $matches[3]))
  {
   return true;
  }
 }
}



