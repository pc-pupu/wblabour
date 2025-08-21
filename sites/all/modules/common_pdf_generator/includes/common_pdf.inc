<?php

function myfun_qrcode($text , $qrpath) {
	//echo "inside"; exit;
  // Including the qrcode library and generating the code
  include("sites/all/libraries/phpqrcode/qrlib.php");
  QRcode::png($text, $qrpath);

  return $qrpath;
}


function acknowledgement_print_form($args,$year){ 

  include('mpdf/mpdf.php');
  global $user, $base_root, $base_path;
	
	
  $query = db_select('a_asset_mst','am');
  $query->leftJoin('users', 'u', 'u.uid = am.uid');  
  $query->leftJoin('a_user_details', 'ud', 'ud.uid = u.uid');  
  $query->leftJoin('a_directorate_mst', 'dm', 'dm.directorate_code = am.directorate_code');  
  $query->fields('am', array('id','uid','declaration_yr','designation','directorate_code','status','created_date','operator_uid'));
  $query->fields('u', array('uid','name','access','created','status'));
  $query->fields('ud', array('uid','fname'));
  $query->fields('dm', array('directorate_name'));
  $query->condition('am.uid', $args, '=');
  $query->condition('am.declaration_yr', $year, '=');
  $result = $query->execute();
  $rsData = $result->fetchAssoc();
  
  $operatorInfo = getLoginUserDetailForAsset($rsData['operator_uid']); 
  //print_r($operatorInfo); exit;
  
  $delaydate = strtotime($rsData['created_date']);
  $min_date = strtotime(date('01-05-2019'));
  $max_date = strtotime(date('31-05-2019'));
  $received_date = date('d-m-Y H:i:s',strtotime($rsData['created_date']));
  if(trim($delaydate) >= $min_date &&  trim($delaydate) <= $max_date){
	  $delay = 'Received "DECLARATION OF ASSETS AS THEY STOOD ON 01/01/'.$rsData['declaration_yr'].'" 
						in sealed envelope from <strong style="color:#2e4b90;">'.$rsData['fname'].', '.$rsData['designation'].', '.$rsData['directorate_name'].'
						<strong style="color:red;">**</strong></strong>';
      $footer_star_msg = '<strong style="color:red;">**</strong> <strong>NB : Submitted after due date</strong>';
	  $received_delaydate = ''.$received_date.' <strong style="color:red;">**</strong>';				
  }else { 
	 $delay = 'Received "DECLARATION OF ASSETS AS THEY STOOD ON 01/01/'.$rsData['declaration_yr'].'" 
						in sealed envelope from <strong style="color:#2e4b90;">'.$rsData['fname'].', '.$rsData['designation'].', '.$rsData['directorate_name'].'</strong>';
	 $received_delaydate = ''.$received_date.'';
  }
  
  $stamp_link = '';
  
  if($operatorInfo['directorate_code'] == 'DB'){
		$directorate_name = 'Directorate of Boilers';
		$daddress = 'New Secretariat Buildings (8th Floor), ‘A’–Block <br/> 1, K.S Roy Road, Kolkata – 700001';
		$stamp_link = 'bd_stamp.jpg';
	}elseif($operatorInfo['directorate_code'] == 'LC'){
		//$directorate_name = 'Labour Commissionerate';
		//$daddress = 'New Secretariat Buildings (11th Floor), ‘A’–Block <br/> 1, K.S Roy Road, Kolkata – 700001';
		//$stamp_link = 'lc_stamp.jpg';
		$office_address = getOfficeAddress($office_id);
		if($operatorInfo['office_id'] == 0){
			$operator_office_id = '117';
		}else{
			$operator_office_id = $operatorInfo['office_id'];
		}
		//echo $operatorInfo['office_id']."<br>"; exit;
		//print_r($office_address); exit;
		foreach($office_address as $val){
			//echo "-->".$operatorInfo['office_id']."-->".$val->office_id;
			if($operator_office_id == $val->office_id){
				if($operator_office_id == '117'){
					$directorate_name = 'Labour Commissionerate';
				}else{
					$directorate_name = $val->office_name;
				}
				$daddress = $val->office_address;
				
				//echo $directorate_name; exit;
			}
			//break;
		}
		//exit;
		
		$stamp_link = 'lc_stamp.jpg';
	}elseif($operatorInfo['directorate_code'] == 'DE'){
		$directorate_name = 'Directorate of Employment';
		$daddress = '67, Bentinck Street, Kolkata – 700069';
		$stamp_link = 'de_stamp.jpg';
	}elseif($operatorInfo['directorate_code'] == 'DF'){
		$directorate_name = 'Directorate of Factories';
		$daddress = 'New Secretariat Buildings (8th Floor), ‘A’–Block <br/> 1, K.S Roy Road, Kolkata – 700001';
		$stamp_link = 'df_stamp.jpg';
	}elseif($operatorInfo['directorate_code'] == 'ESI'){
		$directorate_name = 'Directorate of ESI (MB) Scheme';
		$daddress = 'Block - G.B. Sector - III, Salt Lake, Kolkata - 700097';
		$stamp_link = 'esi_stamp.jpg';
	}elseif($operatorInfo['directorate_code'] == 'LD'){
		$directorate_name = 'Labour Department';
		$daddress = 'New Secretariat Buildings (12th Floor), ‘A’–Block <br/> 1, K.S Roy Road, Kolkata – 700001';
		$stamp_link = 'ld_stamp.jpg';
	}elseif($operatorInfo['directorate_code'] == 'DIT'){
		$directorate_name = 'Directorate of Industrial Tribunal';
		$daddress = 'New Secretariat Buildings (2nd Floor), ‘A’–Block <br/> 1, K.S Roy Road, Kolkata – 700001';
		$stamp_link = 'dit_stamp.jpg';
	}elseif($operatorInfo['directorate_code'] == 'EIC'){
		$directorate_name = 'Employees Insurance Court';
		$daddress = 'New Secretariat Buildings (9th Floor), ‘B’–Block <br/> 1, K.S Roy Road, Kolkata – 700001';
		$stamp_link = 'eic_stamp.jpg';
	}elseif($operatorInfo['directorate_code'] == 'DEC'){
		$directorate_name = 'Directorate of Employees Compensation';
		$daddress = 'New Secretariat Buildings (12th Floor), ‘A’–Block <br/> 1, K.S Roy Road, Kolkata – 700001';
		$stamp_link = 'dec_stamp.jpg';
	}
  
	
	if(1){ 
	
	$qrpath = variable_get('file_public_path', conf_path() . '/files') . "/qrcode/ASSET-".$rsData['declaration_yr']."-".$rsData['uid']."-".$rsData['id'].'.png'; 
	$text = $rsData['fname'].', '.$rsData['designation'].', '.$rsData['directorate_name'].', '.$rsData['declaration_yr'].', '.$rsData['created_date'];
	if (!file_exists($qrpath)) {
		$qrpath =  myfun_qrcode($text , $qrpath);
	}

	$output = '';
	$content = '';
	$header = '<!DOCTYPE html>
			  <html>
			  <head>
				<meta charset="utf-8">
				<title>Acknowledgement</title>
				<link rel="stylesheet" href="'.$base_root.$base_path.'sites/all/modules/common_pdf_generator/includes/mpdfstyletables.css" media="all" />
			  </head>
			  <body>
				 <table width="100%" border="0" cellspacing="0" cellpadding="0">
					<tbody>
					 <tr>
						<td align="right" width="55%">
						<img src="./sites/all/modules/common_pdf_generator/includes/logo.png" style="width:120px;">
						</td>
						<td align="right" width="40%" style="padding-top:30px;">
						<img src="./'.$qrpath.'" style="width:120px; height=120px;">
						</td>
					  </tr>
					 <tr>
						<td colspan="2" align="center" style="font-size:22px;margin: 0;padding: 0;color:#2e4b90;">Government of West Bengal<br/>
<strong>'.$directorate_name.'</strong></td>
					  </tr>

					  <tr>
						<td colspan="2" align="center" style="font-size:16px;margin: 0;padding:0 0 20px;color:#676767;">'.$daddress.'</td>
					  </tr>
					  <tr>
						<td colspan="2" align="center" style="background:#2e4b90;padding:2px;"></td>
					  </tr>
					  <tr>
						<td colspan="2" style="font-size:20px;color:#0e783d;padding:40px 0 0;" align="center"><strong>ACKNOWLEDGEMENT</strong></td>
					  </tr>
					  <tr>
						<!--<td colspan="2" style="font-size:16px;padding:40px 0;">Received "DECLARATION OF ASSETS AS THEY STOOD ON 01/01/'.$rsData['declaration_yr'].'"
						 in sealed envelope from <strong style="color:#2e4b90;">'.$rsData['fname'].', '.$rsData['designation'].', '.$rsData['directorate_name'].'</strong></td>-->
						 <td colspan="2" style="font-size:16px;padding:40px 0;">'.$delay.'</td>
					  </tr>
					  
	';
	
	$signature ='<tr>
						<td colspan="2">
						<table width="900" border="0" cellspacing="0" cellpadding="0">
						  <tr>
							<td style="background-color: #f2f2f2;font-size:16px;border: 1px solid #ddd;padding: 8px;">Received By :</td>
							<td style="background-color: #f2f2f2;font-size:16px;border: 1px solid #ddd;padding: 8px;">'.$operatorInfo['fname'].'</td>
						  </tr>
						  <tr>
							<td style="font-size:16px;border: 1px solid #ddd;padding: 8px;">Designation :</td>
							<td style="font-size:16px;border: 1px solid #ddd;padding: 8px;">'.$operatorInfo['designation'].'</td>
						  </tr>
						  <tr>
							<td style="background-color: #f2f2f2;font-size:16px;border: 1px solid #ddd;padding: 8px;">Date and Time :</td>
							<td style="background-color: #f2f2f2;font-size:16px;border: 1px solid #ddd;padding: 8px;">'.$received_delaydate.'</td>
						  </tr> 
						  
						   <tr>
							<td colspan="2" style="font-size:16px;padding:40px 0;">'.$footer_star_msg.'</td>
					  	 </tr>   
						  
						</table>
						</td>
						<tr>
						<td colspan="2" align="center" style="padding-top:100px;"><img src="./sites/all/modules/common_pdf_generator/includes/'.$stamp_link.'" style="width:250px; opacity:0.5;"></td>
					  </tr>
					  </tr>
					 </tbody> 
				</table>
	';
	
	$last_footer ='<hr width="100%">
	<table width="100%">
	<tr>
	<td align="center" style="font-size:13; padding:10px 0;"><strong>Note:</strong> This is a system generated document. No signature required.</td>
	</tr>
	</table>
	';
	$footer = '
	</body>
	</html>';

	$output = $header.$signature;
	//return pdf_using_mpdf_api($output);
	$mpdf = new mPDF('utf-8', 'A4', '', '', 10, 10, 10, 8, 0, 0);
	/*$mpdf->SetDisplayMode('fullpage');
	
	$mpdf->list_indent_first_level = 1;*/
	$mpdf->SetHTMLFooter($last_footer);
	
	$mpdf->SetWatermarkText('Asset Declaration',0.1);
	$mpdf->showWatermarkText = true;
	//$mpdf->SetWatermarkImage('./sites/all/modules/common_pdf_generator/includes/stamp.png');
	//$mpdf->showWatermarkImage = true;
	
	/*$mpdf->debug = true;*/
	$mpdf->showImageErrors = true;
	
	$mpdf->WriteHTML($output);
	
	$mpdf->Output();
	
	}else{
		drupal_set_message('Still Now PDF is not generated. Please generate PDF first.', $type='warning');
		//drupal_goto('grn/list');
	}
 }


function generateAssetPdf($args){
	//return "hi"; die();
	include('mpdf/mpdf.php');
	global $user, $base_root, $base_path;
	
	$result	= array();
	$resultData 		= array();
	
	$result		= getAllUidInfoFromPid($user->uid);
	$resultData = getAssetDataWithStatus($user->uid, 0);
	
	
	
	if(1){
		

		
	$output = '';
	$content = '';
	$header = '<!DOCTYPE html>
			<html>
			  <head>
				<meta charset="utf-8">
				<title>Asset</title>
				<link rel="stylesheet" href="'.$base_root.$base_path.'sites/all/modules/common_pdf_generator/includes/mpdfstyletables.css" media="all" />
			  </head>
			  <body>
				<header class="clearfix">
					
				  <!--<div id="logo">
					<img src="'.$base_root.$base_path.'sites/all/modules/custom/common_pdf_generator/logo.png">
				  </div>-->
				  <div id="company">
					<h6 class="name">West Bengal Form No. 34 A.</h6>
					<div align="center"><b>Declaration of Assets as they stood on : 1st January, '.$resultData['declaration_yr'].'</b></div>
				  </div>
				  <br>
				   <table border="0" cellpadding="0" cellspacing="0"  width="100%">
					  <tr>
						<td>Name (in full) of Officer : '.$result['fname'].'</td>
						<td>Service : '.$resultData['service_type'].'</td>
					  </tr>
					  <tr>
						<td>Designation: '.$resultData['designation'].'</td>
						<td>now appointed as : '.$resultData['appointed_as'].'</td>
					  </tr>
					  <tr>
						<td>Substantive Pay : '.$resultData['substantive_pay'].'</td>
						<td>&nbsp;</td>
					  </tr>
					  <tr>
						<td>Special Pay : '.$resultData['special_pay'].' </td>
						<td>&nbsp;</td>
					  </tr>
					</table>
				  </div>
				</header>
				<main>';
	$instruction = '<div align="center" style="font-size: 10pt; font-weight:bold;"> INSTRUCTIONS FOR FILLING UP THE DECLARATION </div> <br>
	<table style="border: 0px; font-size: 7.4pt; " class="" cellspacing="0" cellpadding="0" >
	  <tr>
	  
		<td style="text-align:justify">1.(a) Every Government employee employed under the administrative control of the Government of West Bengal, other than a person in inferior service, shall submit to the  				 proper authority an annual return of the movable and immovable properties owned, acquired or inherited by him, or his wife or dependants or held on lease or 	
		 		 mortgage either in his own name or in the name of any member of his family or of any other person. These orders will not apply to member of the All-India Services 	
				 who are governed by sub-rule 1 of Rule 16 of the All-India Service (Conduct) Rules, 1968.</td>
		<td>&nbsp;</td>
		<td style="text-align:justify">paid for under a hire- purchase scheme in instalments or are mortgaged while being acquired, the full particulars of such properties should he given even though the title to the property may not yet have devolved upon the Government employee making the declaration. It is incumbent upon the declarant in such cases to state the amount paid up to the relevant date for the purchase of the particular property.</td>
	  </tr>
	  <tr>
		<td style="text-align:justify">(b)	This Declaration of Assets must always refer to the 1st January of the current year. Any asset acquired between the 1st January and the date of declaration should not ordinarily be entered in the declaration. But in case of doubt regarding the exact date of the assets in question may be entered for the current year but should be repeated in the declaration of the next year too. It is best to submit the Declaration of Assets as soon after New Year\'s Day as possible.</td>
		<td>&nbsp;</td>
		<td style="text-align:justify">6. In declaring Insurance Policies, the number of policy or policies, the amount of Insurance, the name and address of the Company, the number of years during which premia have to be paid must be mentioned, Fully or partly paid-up Policies, Single or Limited Payment Policies must be described as such. Any omission in this respect will be liable to be interpreted as an attempt to conceal real assets. The names and addresses of the Banks of the declarant and his dependants together with the nature and number of the accounts should be given.</td>
	  </tr>
	  <tr>
		<td style="text-align:justify">(c)	A person who has entered Government Service for the first time should submit the return within three months of his joining Government Service and it should relate to his assets as they stood on the 1st of January immediately preceding his date of joining.</td>
		<td>&nbsp;</td>
		<td style="text-align:justify">7 . Every declaration must be made in the prescribed printed form and the prescribed declaration at the foot of every page must be signed.</td>
	  </tr>
	  <tr>
		<td style="text-align:justify">2.	If there is no change of assets on the 1st January of the previous year the declaration should never be nil. There should be a fresh Declaration of Assets in full as on the 1st January of every year.</td>
		<td>&nbsp;</td>
		<td style="text-align:justify">8 . If in the declaration it is not possible to give a correct statement of every assets as it stood exactly on the 1st January, the statement should be correct to the nearest date and that date should be mentioned. (Sometimes" it is difficult to get a precise statement of Bank-Accounts, for example, as they stood on the 1st January.)
	</td>
	  </tr>
	  <tr>
		<td style="text-align:justify">3.	The Declaration of Assets must show the assets belonging to the Government employee even though they may stand in the name of his wife (in the case of a male Government employee), children, other dependants or benamdars, and must also show the assets belonging to the wife of a male Government employee or to his dependants even though they are acquired by the wife or dependants in their own right.</td>
		<td>&nbsp;</td>
		<td style="text-align:justify">9.	A Government employee whose service is placed temporarily at the disposal of the Central or any other State Government or any other authority should be required to submit the Declaration of Assets to the Government of West Bengal.</td>
	  </tr>
	  <tr>
		<td style=" font-size: 6.5pt; text-align:justify;"><br><br><b><i>N.B.</i> —</b>If any difficulty arises regarding the declaration of assets of a Government employees wife (in the case of a male Government employee) or dependants, the matter should be reported to Government with full particulars and further instructions sought.</td>
		<td>&nbsp;</td>
		<td style="text-align:justify">10.	The categories of assets mentioned in brackets in the printed declaration form are merely illustrative and not meant to be exhaustive.</td>
	  </tr>
	  <tr>
		<td style="text-align:justify"><br><br>4. Any officer making a declaration discovered to be materially incomplete, misleading or false will earn for himself the penalty of immediate suspension, drawing up of proceedings, which may ultimately result in dismissal from Government Service with forfeiture of pension and all other discretionary benefits. A subsequent explanation that the failure strictly to comply with the instructions or the presence of material defects in the declaration were by oversight or ignorance will not be accepted. Ambiguity in a declaration must be avoided as any ambiguity will be liable to be interpreted against him.</td>
		<td>&nbsp;</td>
		<td style="text-align:justify">12.	In column 6 of Al and column 4 of A2, please state the full value of the land and the house. If the value has not yet been determined please state how much has generally been paid. In case of a building, state the actual amount of money that has been spent up to 1st January or as near that date as possible even if the construction may be incomplete or just started. In the case of land, please state the amount of loan, if any taken in cash, and in the case of house the amount of such loan in cash or kind including the value of materials purchased on credit.</td>
	  </tr>
	  <tr>
		<td style="text-align:justify"><br><br>5. In declaring shares and stocks and other securities, jewellery, motor cars, motor cycles, refrigerators, other valuable movable articles and immovable property, the actual price paid by an officer must be mentioned, whatever the face value or depreciation might be. Movable articles costing less than Rs. 500 for each item need not be mentioned. In columns 8 of Part A(1), 6 of Parts A(2) and A(3), and 5 of Parts B(1) and B(2) of the form of Declaration of Assets, the. manner of acquisition of the property must be clearly and unambiguously given, i.e., whether the property was acquired by means of savings from the Government employees salary or from income from any other source, or by loan in cash or kind, or by inheritance or by any other means to be specified. If an immovable or movable property is in the process of acquisition, for example, a piece of landed property which is being purchased in instalments or under one of the various mortgage schemes, or a car or a refrigerator or other pieces of furniture or jewellery are being</td>
		<td>&nbsp;</td>
		<td style="text-align:justify">13 . The last date of submission of this Declaration of Assets is the 30th April every year for assets as they stood on the previous 1 st. January of that year. Gazetted Officers will submit these declarations by registered post at Government expense in double sealed covers direct to their appointing authorities / Secretaries in charge of the administrative department concerned. The outer sealed cover will be addressed to the appointing authorities/ Secretaries in charge of administrative department concerned and should not contain any indication of the contents. The inner sealed cover should contain the name of the officer, his service, rank and address and a certificate of the date for which the declaration stands (in the form : Declaration of Assets as they stood on 1st January, 19 ). On receipt o the declarations the appointing authorities subordinate to Government should send them to the Secretary of the administrative department concerned who will maintain the declarations under his custody. Non-gazetted officers will submit their declarations in sealed cover to their respective heads of offices for safe custody, the above instructions being followed mutatis mutandis. Government employees are not required to supply more than one copy of the return, and instructions for submission of returns in duplicate, triplicate, etc., are unauthorised.</td>
	  </tr>
	</table> 
	';	
			
	$document .= get_immovable_land_list_for_pdf($resultData['id']);
	$document .= get_immovable_house_list_for_pdf($resultData['id']);
	$document .= get_immovable_other_list_for_pdf($resultData['id']);
	$document .= get_movable_property_list_for_pdf($resultData['id']);
	$document .= get_movable_other_list_for_pdf($resultData['id']);
				
	/*$content .= '<table border="0" cellpadding="0" cellspacing="0">
 				<thead><tr><th colspan="4" class="no">GRN Basic Details (all values are in</th></tr></thead>
				<tbody>
				 <tr>
					 <td><b>Purchase Order Number</b></td>
					 <td><b>Purchase Order Date</b></td>
					 <td><b>Delivery Challan Number</b></td>
					 <td><b>Delivery Challan Date</b></td> 
				 </tr>
 				
 				<tr>
				<td colspan="4">&nbsp;</td> 
				</tr>
 				<tr>
					<td><b>Arrival Date Time</b></td>
					<td><b>Unloading Date Time</b></td>
					<td><b>Carrier Reg No</b></td>
					<td><b>Transporter Name</b></td> 
				</tr>
 				
 				<tr>
					<td colspan="4">&nbsp;</td> 
				</tr>
 				<tr class="odd"><td><b>Driver Name</b></td>
					<td><b>Driver Mob No</b></td>
					<td><b>Vendor Name</b></td>
					<td><b>Goods Price As Per Invoice</b></td> 
				</tr>
 				
 				<tr>
					<td colspan="4">&nbsp;</td> 
				</tr>
 				<tr>
					<td colspan="3"><b>Over all Remarks</b></td>
					<td><b>Goods Price As Per Purchase Order</b></td> 
				</tr>
 			
 				<tr>
					<td><b>Vendor Address<b></b></b></td>
					<td colspan="3"></td> 
				</tr>
			</tbody>
		</table>';*/
	$signature ='<table width="100%"><tr><td align="left"><i>Date</i></td><td align="right"><i>Signature of Declarant</i></td></tr></table><hr width="100%"><table width="100%">
	<tr>
	<td width="33%" align="left"><style="font-family:monospace; font-style:; font-size:10">&nbsp;</style></td>
	<td width="33%" align="center"><style="font-family:serif; font-style:BI; font-size:18">- {PAGENO} -</style></td>
	<td width="33%" align="right"><style="font-family:monospace; font-style:;font-size:10">&nbsp;</style></td>
	</tr>
	</table>
	';
	$footer = '</main>
	<footer>
    </footer>
  </body>
</html>';

	
	$output = $header.$instruction.$content.$footer;
	$document = $document.$footer;
	
	//echo $output.$document.$signature; exit;
	
	//return pdf_using_mpdf_api($output);
	$mpdf = new mPDF('utf-8', 'A4', '', '', 10, 10, 10, 8, 0, 0);
	$mpdf->setTitle($resultData['document_no']);
	//$mpdf = new mPDF('utf-8', 'A4', '', '', 0, 0, 0, 0, 0, 0);
	//$mpdf->SetDisplayMode('fullpage');
	
	//$mpdf->list_indent_first_level = 1;
	//$mpdf->setHeader($arr);
	/*$mpdf->SetHTMLHeader('
<div style="padding-top:50px; text-align: right; font-weight: bold;">
    Page {PAGENO} of {nb}
</div>');*/
	//$mpdf->setFooter("Page {PAGENO} of {nb}");
	//$mpdf->defaultfooterline=0;
	$mpdf->SetWatermarkText('Draft PDF',0.1);
	$mpdf->showWatermarkText = true;
	//$mpdf->SetWatermarkImage($base_root.$base_path.'sites/all/modules/custom/common_pdf_generator/logo.png');
	//$mpdf->showWatermarkImage = true;
	//$stylesheet = file_get_contents($base_root.$base_path.'sites/all/modules/common_pdf_generator/includes/mpdfstyletables.css'); 
	if($resultData['file_pass']!=""){
		$mpdf->SetProtection(array(),'UserPassword',$resultData['file_pass']);
	}
	//$mpdf->WriteHTML($stylesheet,1); // The parameter 1 tells that this is css/style only and no body/html/text
	$mpdf->WriteHTML($output);
	
	
	
	
	$mpdf->AddPage('P','','','','',10,10,10,30,0,0);
	//$mpdf->SetDisplayMode('fullpage');
	$mpdf->SetHTMLFooter($signature);
	$mpdf->WriteHTML($document);
	
	
	
	$mpdf->Output('Form34A-'.$resultData['declaration_yr'].'.pdf','I');

	}else{
		drupal_set_message('Still Now PDF is not generated. Please generate PDF first.', $type='warning');
		//drupal_goto('grn/list');
	}
	
}


function bulkacknowledgement_print_form($args,$year) {	
  include('mpdf/mpdf.php');
  global $user, $base_root, $base_path;
	
  $operatorInfo = getLoginUserDetailForAsset($user->uid); 
  //print_r($operatorInfo); exit;
  /*echo "abc";
  echo "<pre>";
  print_r(unserialize(base64_decode($args)));
  die;*/
  //echo $args; exit;
  $uid_in = unserialize(base64_decode($args));
  
  //print_r($uid_in); exit;
 // $groupAlist = groupAofficer_list('F',$direc_code['directorate_code']);
	
	
  $bulkpdf = db_select('a_asset_mst','am');
  $bulkpdf->leftJoin('users', 'u', 'u.uid = am.uid');  
  $bulkpdf->leftJoin('a_user_details', 'ud', 'ud.uid = am.uid');  
  $bulkpdf->leftJoin('a_directorate_mst', 'dm', 'dm.directorate_code = am.directorate_code');  
  $bulkpdf->leftJoin('a_user_details_service', 'us', 'am.uid = us.uid'); 
  
  //$bulkpdf->leftJoin('a_transaction_history', 't', 'am.transaction_id = t.id'); 
  
  $bulkpdf->fields('am', array('id','uid','declaration_yr','designation','directorate_code','status','created_date','forward_status'));
  $bulkpdf->fields('u', array('name','access','created'));
  $bulkpdf->fields('ud', array('fname','status'));
  $bulkpdf->fields('dm', array('directorate_name'));
  $bulkpdf->fields('us', array('district_code','directorate_code','emp_group'));
  
  //$bulkpdf->fields('t', array('forwarding_no'));
  
  $bulkpdf->condition('am.uid',$uid_in,'IN');
  $bulkpdf->condition('am.declaration_yr',$year,'=');
  $bulkpdf->orderBy('am.created_date','asc');
  
  $result = $bulkpdf->execute();
  $rsData = $result->fetchAll();
  
  
  $str = "'";
  foreach($uid_in as $v){
	 $str .= $v.","; 
  }
  $str = rtrim($str,",");
  $newstr = $str."'";
 // echo $newstr; exit;
  
  $bulkpdf_transaction_no = db_query("select forwarding_no,transaction_date from a_transaction_history where asset_user_id = $newstr and declaration_year = $year and status= 'F'");	
  $rsData_transaction = $bulkpdf_transaction_no->fetchAll();
  
 if($rsData[0]->directorate_code == 'DB'){
		//$directorate_name = 'Directorate of Boilers';
		$daddress = 'New Secretariat Buildings (8th Floor), ‘A’–Block <br/> 1, K.S Roy Road, Kolkata – 700001';
	}elseif($rsData[0]->directorate_code == 'LC'){
		$daddress = 'New Secretariat Buildings (11th Floor), ‘A’–Block <br/> 1, K.S Roy Road, Kolkata – 700001';
	}elseif($rsData[0]->directorate_code == 'DE'){
		$daddress = '67, Bentinck Street, Kolkata – 700069';
	}elseif($rsData[0]->directorate_code == 'DF'){
		$daddress = 'New Secretariat Buildings (8th Floor), ‘A’–Block <br/> 1, K.S Roy Road, Kolkata – 700001';
	}elseif($rsData[0]->directorate_code == 'ESI'){
		$daddress = 'Block - G.B. Sector - III, Salt Lake, Kolkata - 700097';
	}elseif($rsData[0]->directorate_code == 'LD'){
		$daddress = 'New Secretariat Buildings (12th Floor), ‘A’–Block <br/> 1, K.S Roy Road, Kolkata – 700001';
	}
  
  
  $cntData = 0;
  $cntData = count($rsData);
  
	if(1){ 
	
	$i=0;
	$text = "";
	$qrpath = variable_get('file_public_path', conf_path() . '/files') . "/qrcode/ASSET-".$rsData[0]->declaration_yr."-".
							$rsData[0]->uid."-".$rsData[0]->id.'.png';
    foreach($rsData as $pdfresult){
	   //$i++;	
	$text .= $pdfresult->fname.', '.$pdfresult->designation.', '.$pdfresult->directorate_name.', '.$pdfresult->declaration_yr.',
		  '.$pdfresult->created_date;
	
   }
   //echo $text; exit;
   if (!file_exists($qrpath)) {
		$qrpath =  myfun_qrcode($text , $qrpath);
	}
	$output = '';
	$content = '';
	$header = '<!DOCTYPE html>
			  <html>
			  <head>
				<meta charset="utf-8">
				<title>Acknowledgement</title>
				<link rel="stylesheet" href="'.$base_root.$base_path.'sites/all/modules/common_pdf_generator/includes/mpdfstyletables.css" media="all" />
			  </head>
			  <body>
				 <table width="100%" border="0" cellspacing="0" cellpadding="0">
					<tbody>
					 <tr>
						<td align="right" width="55%">
						<img src="./sites/all/modules/common_pdf_generator/includes/logo.png" style="width:120px;">
						</td>
						<td align="right" width="40%" style="padding-top:30px;">
						<img src="./'.$qrpath.'" style="width:120px; height=120px;">
						</td>
					  </tr>
					 <tr>
						<td colspan="2" align="center" style="font-size:22px;margin: 0;padding: 0;color:#2e4b90;">Government of West Bengal<br/>
<strong>'.$rsData[0]->directorate_name.'</strong></td>
					  </tr>

					  <tr>
						<td colspan="2" align="center" style="font-size:16px;margin: 0;padding:0 0 20px;color:#676767;">'.$daddress.'</td>
					  </tr>
					  <tr>
						<td colspan="2" align="center" style="background:#2e4b90;padding:2px;"></td>
					  </tr>
					  <tr>
						<td align="left" style="font-size:15px;padding:30px 0;">No: <strong>'.$rsData_transaction[0]->forwarding_no.'</strong></td>
						<td align="right" style="font-size:15px;padding:30px 0;">Date: <strong>'.date('d-m-Y',strtotime($rsData_transaction[0]->transaction_date)).'</strong></td>
					  </tr>
					  <tr>
						<td colspan="2" style="font-size:15px;padding:0;">
							To,<br/>
							The Additional Chief Secretary / Principal Secretary / Secretary, <br/>
							Labour Department<br/>
						</td>
					  </tr>
					  
					  <tr>
						<td colspan="2" style="font-size:15px;color:#0e783d;padding:40px 0 0;" align="center"><strong>Sub: Forwarding of Declaration of Assets ON "01/01/'.$rsData[0]->declaration_yr.'" 
						in respect of the following '.$cntData.' <br/>Group A Officers under the '.$rsData[0]->directorate_name.' </strong></td>
					  </tr>
					  
					  <tr>
						<td colspan="2" style="font-size:15px;padding:40px 0;">
						<strong>Respected Sir,</strong><br/><br/>
						 DECLARATION OF ASSETS AS THEY STOOD ON 01/01/'.$rsData[0]->declaration_yr.' 
						in respect of the following '.$cntData.' Group A Officers under the '.$rsData[0]->directorate_name.' 
						are hereby forwarded in sealed envelopes (Contents Not Verified). 
						</td>
					  </tr></tbody></table>
	';
	
	$i=0;
	
	$signature ='';				 	  
				  
	$table_st = '<table width="900" border="0" cellspacing="0" cellpadding="0">
					<tr>
					 <th style="background-color: #2e4b90;font-size:14px;border: 1px solid #ddd;padding: 8px;color:#fff;">Sl. No.</th>
					  <th style="background-color: #2e4b90;font-size:14px;border: 1px solid #ddd;padding: 8px;color:#fff;">Name</th>
					  <th style="background-color: #2e4b90;font-size:14px;border: 1px solid #ddd;padding: 8px;color:#fff;">Designation </th>
					 <!-- <th style="background-color: #2e4b90;font-size:14px;border: 1px solid #ddd;padding: 8px;color:#fff;">Directorate Name </th>-->
					  <th style="background-color: #2e4b90;font-size:14px;border: 1px solid #ddd;padding: 8px;color:#fff;">Received On </th>
					</tr>';
	$table_end ='</table>';
	
	   
	   $pagecnt = 1;	
	   $i=0;
	   foreach($rsData as $pdfresult){
	   	
		if($i==0){
			$signature .= $table_st;
		}else if($pagecnt == 1){
		  // for first page	
		  if($i>7){
			$pagecnt++;
			//$i=0;
			$signature .= $table_end;
			$signature .= $table_st;
			$signature .='<pagebreak>';
		  }
		}else if($pagecnt > 1){
		  // for second page	
		  if($i>20){
			$pagecnt++;
			//$i=0;
			$signature .= $table_end;
			$signature .= $table_st;
			$signature .='<pagebreak>';
		  }
		}
		$i++;
		$signature .='<tr>
					  <td style="background-color: #f2f2f2;font-size:14px;border: 1px solid #ddd;padding: 8px;">'.$i.'</td>
					  <td style="background-color: #f2f2f2;font-size:14px;border: 1px solid #ddd;padding: 8px;">'.$pdfresult->fname.'</td>
					  <td style="background-color: #f2f2f2;font-size:14px;border: 1px solid #ddd;padding: 8px;">'.$pdfresult->designation.'</td>
					  <!--<td style="background-color: #f2f2f2;font-size:14px;border: 1px solid #ddd;padding: 8px;">'.$pdfresult->directorate_name.'</td>-->
					  <td style="background-color: #f2f2f2;font-size:14px;border: 1px solid #ddd;padding: 8px;">'.date('d-m-Y h:i:s', strtotime($pdfresult->created_date)).'</td>
					</tr>
					';
		}
		
		$signature .= $table_end;
		
		$signature .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">
						<tr>
						<td align="right" style="padding-top:0px;">
						  <table width="100%" border="0" cellspacing="0" cellpadding="0">	
						  <tr>
							<td style="font-size:13; padding:3px;">SD/-</td>
						  </tr>
						  <tr>
							<td style="border-top:1px solid #ccc;font-size:13; padding:3px;"><strong>Nodal Offical</strong></td>
						  </tr>
						  </table>
						  </td>
						  </tr>
						</table>'; 
		
		
	
	$last_footer ='<hr width="100%">
	<table width="100%">
	<tr>
	<td align="center" style="font-size:13; padding:10px 0;"><strong>Note:</strong> This is a system generated document. No signature required. (Page {PAGENO} of {nb})</td>
	</tr>
	</table>
	';
	$footer = '
	</body>
	</html>';

	$output = $header.$signature;
	//return pdf_using_mpdf_api($output);
	$mpdf = new mPDF('utf-8', 'A4', '', '', 10, 10, 10, 8, 0, 0);
	/*$mpdf->SetDisplayMode('fullpage');
	
	$mpdf->list_indent_first_level = 1;*/
	$mpdf->SetHTMLFooter($last_footer);
	
	$mpdf->SetWatermarkText('Asset Declaration',0.1);
	$mpdf->showWatermarkText = true;
	//$mpdf->SetWatermarkImage('./sites/all/modules/common_pdf_generator/includes/stamp.png');
	//$mpdf->showWatermarkImage = true;
	
	/*$mpdf->debug = true;*/
	$mpdf->showImageErrors = true;
	
	$mpdf->WriteHTML($output);
	
	$mpdf->Output();
	
	}else{
		drupal_set_message('Still Now PDF is not generated. Please generate PDF first.', $type='warning');
		//drupal_goto('grn/list');
	}
}


function bulkacknowledgement_received_form($args,$submit_yr='') {	
  include('mpdf/mpdf.php');
  global $user, $base_root, $base_path;
  $mpdf = new mPDF('utf-8', 'A4', '', '', 10, 10, 10, 8, 0, 0);	
  $operatorInfo = getLoginUserDetailForAsset($user->uid); 
  //print_r($operatorInfo); exit;
  /*echo "abc";
  echo "<pre>";
  print_r(unserialize(base64_decode($args)));
  die;*/
  //echo $args; exit;
  $uid_in = unserialize(base64_decode($args));
  //print_r($uid_in); exit;
  
  	/*$bulkpdf = db_select('users', 'u');
	$bulkpdf->leftJoin('a_user_details', 'ud', 'u.uid = ud.uid');
	$bulkpdf->leftJoin('a_user_details_service', 'us', 'u.uid = us.uid');
	$bulkpdf->leftJoin('a_directorate_mst', 'd', 'd.directorate_code = us.directorate_code');  
	
	$bulkpdf->fields('us', array('designation','district_code','directorate_code','emp_group'));
	$bulkpdf->fields('d', array('directorate_name')); 
	$bulkpdf->leftJoin('district_master', 'dis', 'dis.district_code = us.district_code'); 
	$bulkpdf->fields('dis', array('district_name')); 
	$bulkpdf->fields('u', array('uid','name','access','created'));
	$bulkpdf->fields('ud', array('fname','hrms_id','status'));
	$bulkpdf->condition('u.uid', $uid_in,'IN');
	$result = $bulkpdf->execute();
	$rsData = $result->fetchAll();*/
	
	
  $bulkpdf = db_select('a_asset_mst','am');
  $bulkpdf->leftJoin('users', 'u', 'u.uid = am.uid');  
  $bulkpdf->leftJoin('a_user_details', 'ud', 'ud.uid = am.uid');  
  $bulkpdf->leftJoin('a_directorate_mst', 'dm', 'dm.directorate_code = am.directorate_code');  
  $bulkpdf->leftJoin('a_user_details_service', 'us', 'am.uid = us.uid'); 
  
  $bulkpdf->leftJoin('a_transaction_history', 't', 'am.transaction_id = t.id'); 
  
  $bulkpdf->fields('am', array('id','uid','declaration_yr','designation','directorate_code','status','created_date','forward_status'));
  $bulkpdf->fields('u', array('name','access','created'));
  $bulkpdf->fields('ud', array('fname','status'));
  $bulkpdf->fields('dm', array('directorate_name'));
  $bulkpdf->fields('us', array('district_code','directorate_code','emp_group'));
  
  $bulkpdf->fields('t', array('forwarding_no','transaction_date','status'));
  
  $bulkpdf->condition('am.uid',$uid_in,'IN');
  $bulkpdf->condition('am.declaration_yr',$submit_yr,'=');
  $bulkpdf->orderBy('am.created_date','asc');
  $result = $bulkpdf->execute();
  $rsData = $result->fetchAll();
  
  
  
   
  //print_r($rsData); exit;
  
  $str = "'";
  foreach($uid_in as $v){
	 $str .= $v.","; 
  }
  $str = rtrim($str,",");
  $newstr = $str."'";
  //echo $newstr; exit;
  
  $bulkpdf_transaction_no = db_query("select forwarding_no, status, remarks from a_transaction_history where asset_user_id = $newstr and declaration_year = ".date('Y')." order by id desc");	
  $rsData_transaction = $bulkpdf_transaction_no->fetchAll();
  
  $cntData = 0;
  $cntData = count($rsData);
  
	if(1){ 
	
	$i=0;
	$text = "";
	$qrpath = variable_get('file_public_path', conf_path() . '/files') . "/qrcode/ASSET-".$rsData[0]->declaration_yr."-".
							$rsData[0]->uid."-".$rsData[0]->id.'.png';
    foreach($rsData as $pdfresult){
	   //$i++;	
	$text .= $pdfresult->fname.', '.$pdfresult->designation.', '.$pdfresult->directorate_name.', '.$pdfresult->declaration_yr.',
		  '.$pdfresult->created_date;
	
   }
   //echo $text; exit;
   if (!file_exists($qrpath)) {
		$qrpath =  myfun_qrcode($text , $qrpath);
	}
	
  if($rsData_transaction[0]->status == 'R'){
	  if($rsData_transaction[0]->remarks == '1'){
		  $cause = 'Mutilated';
	  }elseif($rsData_transaction[0]->remarks == '2'){
		  $cause = 'Not Properly Sealed';
	  }elseif($rsData_transaction[0]->remarks == '3'){
		  $cause = 'Apparently Blank';
	  }
	  $received_reject = 'rejected, because it is '.$cause;
  }else{
	  $received_reject = 'received, in sealed envelopes (Contents Not Verified) at the Labour Department';
  }
	$output = '';
	$content = '';
	$header = '<!DOCTYPE html>
			  <html>
			  <head>
				<meta charset="utf-8">
				<title>Acknowledgement</title>
				<link rel="stylesheet" href="'.$base_root.$base_path.'sites/all/modules/common_pdf_generator/includes/mpdfstyletables.css" media="all" />
			  </head>
			  <body>
				 <table width="100%" border="0" cellspacing="0" cellpadding="0">
					<tbody>
					 <tr>
						<td align="right" width="55%">
						<img src="./sites/all/modules/common_pdf_generator/includes/logo.png" style="width:120px;">
						</td>
						<td align="right" width="40%" style="padding-top:30px;">
						<img src="./'.$qrpath.'" style="width:120px; height=120px;">
						</td>
					  </tr>
					 <tr>
						<td colspan="2" align="center" style="font-size:22px;margin: 0;padding: 0;color:#2e4b90;">Government of West Bengal<br/>
<strong>Labour Department</strong></td>
					  </tr>

					  <tr>
						<td colspan="2" align="center" style="font-size:16px;margin: 0;padding:0 0 20px;color:#676767;">New Secretariat Buildings (12th Floor), ‘A’–Block <br/> 1, K.S Roy Road, Kolkata – 700001</td>
					  </tr>
					  <tr>
						<td colspan="2" align="center" style="background:#2e4b90;padding:2px;"></td>
					  </tr>
					   <tr>
						<td align="left" style="font-size:15px;padding:30px 0;">No: <strong>'.$rsData[0]->forwarding_no.'</strong></td>
						<td align="right" style="font-size:15px;padding:30px 0;">Date: <strong>'.date('d-m-Y',strtotime($rsData[0]->transaction_date)).'</strong></td>
					  </tr>
					  <tr>
						<td colspan="2" style="font-size:15px;padding:0;">
							To,<br/>
							The Director, <br/>
							'.$rsData[0]->directorate_name.' <br/>
						</td>
					  </tr>
					  <tr>
						<td colspan="2" style="font-size:20px;color:#0e783d;padding:40px 0 0;" align="center"><strong>ACKNOWLEDGEMENT</strong></td>
					  </tr>
					 <!-- <tr>
						<td colspan="2" style="font-size:15px;color:#0e783d;padding:0;" align="center"><strong>Ref: <strong>'.$rsData_transaction[0]->forwarding_no.'</strong></td>
					  </tr>-->
					  <tr>
						<td colspan="2" style="font-size:16px;padding:40px 0;">
						"DECLARATION OF ASSETS AS THEY STOOD ON 01/01/'.$rsData[0]->declaration_yr.'" 
						in respect of the following '.$cntData.' Group A Officers under '.$rsData[0]->directorate_name.'  
						are hereby '.$received_reject.'  
						</td>
					  </tr> 
					  </tbody> 
				</table>
					  
	';
	
	/*$signature ='<tr>
				  <td colspan="2">';
	
	$signature .='</td>
						</tr>
						<tr>
						<td colspan="2" align="right" style="padding-top:0px;">
						<!--<table width="100%" border="0" cellspacing="0" cellpadding="0">
						  <tr>
							<td style="font-size:13; padding:3px;">SD</td>
						  </tr>
						  <tr>
							<td style="border-top:1px solid #ccc;font-size:13; padding:3px;"><strong>Nodal Offical</strong></td>
						  </tr>
						</table>-->
						</td>
					  </tr>
					 </tbody> 
				</table>
					 ';	*/	
	
	//print_r($rsData); exit;
	$signature ='';				 	  
				  
	$table_st = '<table width="900" border="0" cellspacing="0" cellpadding="0">
					<tr>
					 <th style="background-color: #2e4b90;font-size:14px;border: 1px solid #ddd;padding: 8px;color:#fff;">Sl. No.</th>
					  <th style="background-color: #2e4b90;font-size:14px;border: 1px solid #ddd;padding: 8px;color:#fff;">Name</th>
					  <th style="background-color: #2e4b90;font-size:14px;border: 1px solid #ddd;padding: 8px;color:#fff;">Designation </th>
					  <th style="background-color: #2e4b90;font-size:14px;border: 1px solid #ddd;padding: 8px;color:#fff;">Directorate Name </th>
					  <th style="background-color: #2e4b90;font-size:14px;border: 1px solid #ddd;padding: 8px;color:#fff;">Received On </th>
					</tr>';
	$table_end ='</table>';				
	
	//$signature .= $table_st;
	   $pagecnt = 1;	
	   $i=0;
	   foreach($rsData as $pdfresult){
	   	
		if($i==0){
			$signature .= $table_st;
		}else if($pagecnt == 1){
		  // for first page	
		  if($i>5){
			$pagecnt++;
			//$i=0;
			$signature .= $table_end;
			$signature .= $table_st;
			$signature .='<pagebreak>';
		  }
		}else if($pagecnt > 1){
		  // for second page	
		  if($i>20){
			$pagecnt++;
			//$i=0;
			$signature .= $table_end;
			$signature .= $table_st;
			$signature .='<pagebreak>';
		  }
		}
		$i++;
		$signature .='<tr>
					  <td style="background-color: #f2f2f2;font-size:14px;border: 1px solid #ddd;padding: 8px;">'.$i.'</td>
					  <td style="background-color: #f2f2f2;font-size:14px;border: 1px solid #ddd;padding: 8px;">'.$pdfresult->fname.'</td>
					  <td style="background-color: #f2f2f2;font-size:14px;border: 1px solid #ddd;padding: 8px;">'.$pdfresult->designation.'</td>
					  <td style="background-color: #f2f2f2;font-size:14px;border: 1px solid #ddd;padding: 8px;">'.$pdfresult->directorate_name.'</td>
					  <td style="background-color: #f2f2f2;font-size:14px;border: 1px solid #ddd;padding: 8px;">'.date('d-m-Y h:i:s', strtotime($pdfresult->created_date)).'</td>
					</tr>
					';
		}
		
		$signature .= $table_end;
		
		$signature .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">
						<tr>
						<td align="right" style="padding-top:0px;">
						  <table width="100%" border="0" cellspacing="0" cellpadding="0">	
						  <tr>
							<td style="font-size:13; padding:3px;">SD/-</td>
						  </tr>
						  <tr>
							<td style="border-top:1px solid #ccc;font-size:13; padding:3px;"><strong>Nodal Offical</strong></td>
						  </tr>
						  </table>
						  </td>
						  </tr>
						</table>'; 
		 
			
	
	$last_footer ='<hr width="100%">
	<table width="100%">
	<tr>
	<td align="center" style="font-size:13; padding:10px 0;"><strong>Note:</strong> This is a system generated document. No signature required. (Page {PAGENO} of {nb})</td>
	</tr>
	</table>
	';
	$footer = '
	</body>
	</html>';

	$output = $header.$signature;
	//return pdf_using_mpdf_api($output);
	
	//$mpdf->SetDisplayMode('fullpage');
	
	/*$mpdf->list_indent_first_level = 1;*/
	$mpdf->SetHTMLFooter($last_footer);
	
	$mpdf->SetWatermarkText('Asset Declaration',0.1);
	$mpdf->showWatermarkText = true;
	//$mpdf->SetWatermarkImage('./sites/all/modules/common_pdf_generator/includes/stamp.png');
	//$mpdf->showWatermarkImage = true;
	
	/*$mpdf->debug = true;*/
	$mpdf->showImageErrors = true;
	
	$mpdf->WriteHTML($output);
	
	$mpdf->Output();
	
	}else{
		drupal_set_message('Still Now PDF is not generated. Please generate PDF first.', $type='warning');
		//drupal_goto('grn/list');
	}
}

function showcause_print_form($args,$year){ 

  include('mpdf/mpdf.php');
  global $user, $base_root, $base_path;
	
	
	$query = db_select('a_showcause_notice', 'assetmst');
	$query ->fields('assetmst', array('showcause_id','uid','message','send_by','created_date','status'));
	$query->condition('assetmst.status','1','=');
	$query->condition('assetmst.showcause_id', $args, '='); 
	$result = $query->execute();
	$rsData = $result->fetchAssoc();
  
  $operatorInfo = getLoginUserDetailForAsset($rsData['send_by']); 
  $userInfo = getLoginUserDetailForAsset($rsData['uid']); 
  //print_r($operatorInfo); exit;
  
  $stamp_link = '';
  
  if($operatorInfo['directorate_code'] == 'DB'){
		$directorate_name = 'Directorate of Boilers';
		$daddress = 'New Secretariat Buildings (8th Floor), ‘A’–Block <br/> 1, K.S Roy Road, Kolkata – 700001';
		$stamp_link = 'bd_stamp.jpg';
	}elseif($operatorInfo['directorate_code'] == 'LC'){
		$directorate_name = 'Labour Commissionerate';
		$daddress = 'New Secretariat Buildings (11th Floor), ‘A’–Block <br/> 1, K.S Roy Road, Kolkata – 700001';
		$stamp_link = 'lc_stamp.jpg';
	}elseif($operatorInfo['directorate_code'] == 'DE'){
		$directorate_name = 'Directorate of Employment';
		$daddress = '67, Bentinck Street, Kolkata – 700069';
		$stamp_link = 'de_stamp.jpg';
	}elseif($operatorInfo['directorate_code'] == 'DF'){
		$directorate_name = 'Directorate of Factories';
		$daddress = 'New Secretariat Buildings (8th Floor), ‘A’–Block <br/> 1, K.S Roy Road, Kolkata – 700001';
		$stamp_link = 'df_stamp.jpg';
	}elseif($operatorInfo['directorate_code'] == 'ESI'){
		$directorate_name = 'Directorate of ESI (MB) Scheme';
		$daddress = 'Block - G.B. Sector - III, Salt Lake, Kolkata - 700097';
		$stamp_link = 'esi_stamp.jpg';
	}elseif($operatorInfo['directorate_code'] == 'LD'){
		$directorate_name = 'Labour Department';
		$daddress = 'New Secretariat Buildings (12th Floor), ‘A’–Block <br/> 1, K.S Roy Road, Kolkata – 700001';
		$stamp_link = 'ld_stamp.jpg';
	}elseif($operatorInfo['directorate_code'] == 'DIT'){
		$directorate_name = 'Directorate of Industrial Tribunal';
		$daddress = 'New Secretariat Buildings (3rd Floor), ‘A’–Block <br/> 1, K.S Roy Road, Kolkata – 700001';
		$stamp_link = 'dit_stamp.jpg';
	}elseif($operatorInfo['directorate_code'] == 'EIC'){
		$directorate_name = 'Employees Insurance Court';
		$daddress = 'New Secretariat Buildings (9th Floor), ‘B’–Block <br/> 1, K.S Roy Road, Kolkata – 700001';
		$stamp_link = 'eic_stamp.jpg';
	}elseif($operatorInfo['directorate_code'] == 'DEC'){
		$directorate_name = 'Directorate of Employees Compensation';
		$daddress = 'New Secretariat Buildings (12th Floor), ‘A’–Block <br/> 1, K.S Roy Road, Kolkata – 700001';
		$stamp_link = 'dec_stamp.jpg';
	}
  
	
	if(1){ 
	
	/*$qrpath = variable_get('file_public_path', conf_path() . '/files') . "/qrcode/ASSET-".$rsData['declaration_yr']."-".$rsData['uid']."-".$rsData['id'].'.png'; 
	$text = $rsData['fname'].', '.$rsData['designation'].', '.$rsData['directorate_name'].', '.$rsData['declaration_yr'].', '.$rsData['created_date'];
	if (!file_exists($qrpath)) {
		$qrpath =  myfun_qrcode($text , $qrpath);
	}*/

	$output = '';
	$content = '';
	$header = '<!DOCTYPE html>
			  <html>
			  <head>
				<meta charset="utf-8">
				<title>Acknowledgement</title>
				<link rel="stylesheet" href="'.$base_root.$base_path.'sites/all/modules/common_pdf_generator/includes/mpdfstyletables.css" media="all" />
			  </head>
			  <body>
				 <table width="100%" border="0" cellspacing="0" cellpadding="0">
					<tbody>
					 <!--<tr>
						<td align="right" width="55%">
						<img src="./sites/all/modules/common_pdf_generator/includes/logo.png" style="width:120px;">
						</td>
						<td align="right" width="40%" style="padding-top:30px;">
						<img src="./'.$qrpath.'" style="width:120px; height=120px;">
						</td>
					  </tr>-->
					 <tr>
						<td colspan="2" align="center" style="font-size:22px;margin: 0;padding: 0;color:#2e4b90;">Government of West Bengal<br/>
<strong>'.$directorate_name.'</strong></td>
					  </tr>

					  <tr>
						<td colspan="2" align="center" style="font-size:16px;margin: 0;padding:0 0 20px;color:#676767;">'.$daddress.'</td>
					  </tr>
					  <tr>
						<td colspan="2" align="center" style="background:#2e4b90;padding:2px;"></td>
					  </tr>
					  <tr>
						<td colspan="2" style="font-size:20px;color:#0e783d;padding:40px 0 0;" align="center"><strong>SHOW CAUSE NOTICE</strong></td>
					  </tr>
					  <tr>
						<td colspan="2" style="font-size:16px;padding:40px 0;"><strong style="color:#2e4b90;"> To <br>'.$userInfo['fname'].',<br> '.$userInfo['designation'].', <br>'.$userInfo['directorate_name'].'</strong></td>
					  </tr>
					  <tr>
						<td colspan="2" style="font-size:16px;color:#0e783d;padding:40px 0 0;" align="center"><strong>Sub: Seeking explanation for non-submission of Declaration of Assets for 2019</strong></td>
					  </tr>
					  <tr>
						<td colspan="2" style="font-size:16px;color:#232323;padding:40px 0 0;" align="left">Mr/Ms/Mrs '.$userInfo['fname'].' whereas Declaration of Assets as  they stood on 01/01/'.date('Y').' have not been received by this Department. </td></tr> 
					<tr>
					<td colspan="2" style="font-size:16px;color:#232323;padding:20px 0 0;" align="left"> 
					You are thus requested to cite reasons why Department should not consider initiating proceeding, as per existing rules, against you. <br> You are requested to reply to this letter withing 15 days from the date of receipt '.date('d-m-Y',strtotime($rsData['created_date'])).'</td>
					  </tr>
					  <tr>
						<td colspan="2" style="font-size:16px;color:#232323;padding:20px 0 0;" align="left">In the event of not receiving any reply or upload any evidance cited being non-admissible, this Department may initiate proceeding against you as per existing rules.</td>
					  </tr>
					  <tr>
						<td colspan="2" style="font-size:16px;color:#232323;padding:20px 0 0;" align="left">This has the approval of the Additional Chief Secretary, Labour Department</td>
					  </tr>
					  <tr>
						<td colspan="2" style="font-size:16px;color:#232323;padding:20px 0 0;" align="left">Assistant Secretary (Vigillance) & Nodal Officer (DoAMS)</td>
					  </tr>
					  
	</tbody></table>';
	
	$signature ='';
	$signature .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">
						<tr>
						<td align="right" style="padding-top:0px;">
						  <table width="100%" border="0" cellspacing="0" cellpadding="0">	
						  <tr>
							<td style="font-size:13; padding:3px;">SD/-</td>
						  </tr>
						  <tr>
							<td style="border-top:1px solid #ccc;font-size:13; padding:3px;"><strong>Nodal Offical</strong></td>
						  </tr>
						  </table>
						  </td>
						  </tr>
						</table>';
	/*$signature ='<tr>
						<td colspan="2">
						<table width="900" border="0" cellspacing="0" cellpadding="0">
						  <tr>
							<td style="background-color: #f2f2f2;font-size:16px;border: 1px solid #ddd;padding: 8px;">Received By :</td>
							<td style="background-color: #f2f2f2;font-size:16px;border: 1px solid #ddd;padding: 8px;">'.$operatorInfo['fname'].'</td>
						  </tr>
						  <tr>
							<td style="font-size:16px;border: 1px solid #ddd;padding: 8px;">Designation :</td>
							<td style="font-size:16px;border: 1px solid #ddd;padding: 8px;">'.$operatorInfo['designation'].'</td>
						  </tr>
						  <tr>
							<td style="background-color: #f2f2f2;font-size:16px;border: 1px solid #ddd;padding: 8px;">Date and Time :</td>
							<td style="background-color: #f2f2f2;font-size:16px;border: 1px solid #ddd;padding: 8px;">'.date('d-m-Y H:i:s',strtotime($rsData['created_date'])).'</td>
						  </tr>  
						  
						</table>
						</td>
						<!--<tr>
						<td colspan="2" align="center" style="padding-top:100px;"><img src="./sites/all/modules/common_pdf_generator/includes/'.$stamp_link.'" style="width:250px; opacity:0.5;"></td>
					  </tr>-->
					  </tr>
					 </tbody> 
				</table>
	';*/
	
	$last_footer ='<hr width="100%">
	<table width="100%">
	<tr>
	<td align="center" style="font-size:13; padding:10px 0;"><strong>Note:</strong> This is a system generated document. No signature required.</td>
	</tr>
	</table>
	';
	$footer = '
	</body>
	</html>';

	$output = $header.$signature;
	//return pdf_using_mpdf_api($output);
	$mpdf = new mPDF('utf-8', 'A4', '', '', 10, 10, 10, 8, 0, 0);
	/*$mpdf->SetDisplayMode('fullpage');
	
	$mpdf->list_indent_first_level = 1;*/
	$mpdf->SetHTMLFooter($last_footer);
	
	$mpdf->SetWatermarkText('Asset Declaration',0.1);
	$mpdf->showWatermarkText = true;
	//$mpdf->SetWatermarkImage('./sites/all/modules/common_pdf_generator/includes/stamp.png');
	//$mpdf->showWatermarkImage = true;
	
	/*$mpdf->debug = true;*/
	$mpdf->showImageErrors = true;
	
	$mpdf->WriteHTML($output);
	
	$mpdf->Output();
	
	}else{
		drupal_set_message('Still Now PDF is not generated. Please generate PDF first.', $type='warning');
		//drupal_goto('grn/list');
	}
 }


/******************************************************* need to upload ******************************************/

function bulkacknowledgement_field_print_form($args,$year) {	
  include('mpdf/mpdf.php');
  global $user, $base_root, $base_path;
	
  $operatorInfo = getLoginUserDetailForAsset($user->uid); 
  //print_r($operatorInfo); exit;
  /*echo "abc";
  echo "<pre>";
  print_r(unserialize(base64_decode($args)));
  die;*/
  //echo $args; exit;
  $uid_in = unserialize(base64_decode($args));
  
  //print_r($uid_in); exit;
 // $groupAlist = groupAofficer_list('F',$direc_code['directorate_code']);
	
	
  $bulkpdf = db_select('a_asset_mst','am');
  $bulkpdf->leftJoin('users', 'u', 'u.uid = am.uid');  
  $bulkpdf->leftJoin('a_user_details', 'ud', 'ud.uid = am.uid');  
  $bulkpdf->leftJoin('a_directorate_mst', 'dm', 'dm.directorate_code = am.directorate_code');  
  $bulkpdf->leftJoin('a_user_details_service', 'us', 'am.uid = us.uid'); 
  
  $bulkpdf->fields('am', array('id','uid','declaration_yr','designation','directorate_code','status','created_date','forward_status'));
  $bulkpdf->fields('u', array('name','access','created'));
  $bulkpdf->fields('ud', array('fname','status'));
  $bulkpdf->fields('dm', array('directorate_name'));
  $bulkpdf->fields('us', array('district_code','directorate_code','emp_group','office_id'));
  
  //$bulkpdf->fields('t', array('forwarding_no'));
  
  $bulkpdf->condition('am.uid',$uid_in,'IN');
  $bulkpdf->condition('am.declaration_yr',$year,'=');
  $bulkpdf->orderBy('am.created_date','asc');
  
  $result = $bulkpdf->execute();
  $rsData = $result->fetchAll();
  
  
  $str = "'";
  foreach($uid_in as $v){
	 $str .= $v.","; 
  }
  $str = rtrim($str,",");
  $newstr = $str."'";
 // echo $newstr; exit;
  
  $bulkpdf_transaction_no = db_query("select forwarding_no,transaction_date from a_transaction_history where asset_user_id = $newstr and declaration_year = $year and status= 'F'");	
  $rsData_transaction = $bulkpdf_transaction_no->fetchAll();
  
 if($rsData[0]->directorate_code == 'LC'){
	 	$office_address = getOfficeAddress($office_id);
		if($rsData[0]->office_id == 0){
			$operator_office_id = '117';
		}else{
			$operator_office_id = $rsData[0]->office_id;
		}
		foreach($office_address as $val){
			if($operator_office_id == $val->office_id){
				if($operator_office_id == '117'){
					$directorate_name = 'Labour Commissionerate';
				}else{
					 $directorate_name = $val->office_name; 
				}
				$daddress = $val->office_address;
			}
	 
		//$daddress = 'New Secretariat Buildings (8th Floor), ‘A’–Block <br/> 1, K.S Roy Road, Kolkata – 700001';
	}
 }

  
  
  $cntData = 0;
  $cntData = count($rsData);
  
	if(1){ 
	
	$i=0;
	$text = "";
	$qrpath = variable_get('file_public_path', conf_path() . '/files') . "/qrcode/ASSET-".$rsData[0]->declaration_yr."-".
							$rsData[0]->uid."-".$rsData[0]->id.'.png';
    foreach($rsData as $pdfresult){
	   //$i++;	
	$text .= $pdfresult->fname.', '.$pdfresult->designation.', '.$pdfresult->directorate_name.', '.$pdfresult->declaration_yr.',
		  '.$pdfresult->created_date;
	
   }
   //echo $text; exit;
   if (!file_exists($qrpath)) {
		$qrpath =  myfun_qrcode($text , $qrpath);
	}
	$output = '';
	$content = '';
	$header = '<!DOCTYPE html>
			  <html>
			  <head>
				<meta charset="utf-8">
				<title>Acknowledgement</title>
				<link rel="stylesheet" href="'.$base_root.$base_path.'sites/all/modules/common_pdf_generator/includes/mpdfstyletables.css" media="all" />
			  </head>
			  <body>
				 <table width="100%" border="0" cellspacing="0" cellpadding="0">
					<tbody>
					 <tr>
						<td align="right" width="55%">
						<img src="./sites/all/modules/common_pdf_generator/includes/logo.png" style="width:120px;">
						</td>
						<td align="right" width="40%" style="padding-top:30px;">
						<img src="./'.$qrpath.'" style="width:120px; height=120px;">
						</td>
					  </tr>
					 <tr>
						<td colspan="2" align="center" style="font-size:22px;margin: 0;padding: 0;color:#2e4b90;">Government of West Bengal<br/>
<strong>'.$directorate_name.'</strong></td>

					  </tr>

					  <tr>
						<td colspan="2" align="center" style="font-size:16px;margin: 0;padding:0 0 20px;color:#676767;">'.$daddress.'</td>
					  </tr>
					  <tr>
						<td colspan="2" align="center" style="background:#2e4b90;padding:2px;"></td>
					  </tr>
					  <tr>
						<td align="left" style="font-size:15px;padding:30px 0;">No: <strong>'.$rsData_transaction[0]->forwarding_no.'</strong></td>
						<td align="right" style="font-size:15px;padding:30px 0;">Date: <strong>'.date('d-m-Y',strtotime($rsData_transaction[0]->transaction_date)).'</strong></td>
					  </tr>
					  <tr>
						<td colspan="2" style="font-size:15px;padding:0;">
							To,<br/>
							The Director, <br/>
							Labour Commissionerate<br/>
						</td>
					  </tr>
					  
					  <tr>
						<td colspan="2" style="font-size:15px;color:#0e783d;padding:40px 0 0;" align="center"><strong>Sub: Forwarding of Declaration of Assets ON "01/01/'.$rsData[0]->declaration_yr.'" 
						in respect of the following '.$cntData.' <br/>'.$rsData[0]->emp_group.' Officers under the '.$directorate_name.' </strong></td>
					  </tr>
					  
					  <tr>
						<td colspan="2" style="font-size:15px;padding:40px 0;">
						<strong>Respected Sir,</strong><br/><br/>
						 DECLARATION OF ASSETS AS THEY STOOD ON 01/01/'.$rsData[0]->declaration_yr.' 
						in respect of the following '.$cntData.' Officers under the '.$directorate_name.' 
						are hereby forwarded in sealed envelopes (Contents Not Verified). 
						</td>
					  </tr></tbody></table>
	';
	
	$i=0;
	
	$signature ='';				 	  
				  
	$table_st = '<table width="900" border="0" cellspacing="0" cellpadding="0">
					<tr>
					 <th style="background-color: #2e4b90;font-size:14px;border: 1px solid #ddd;padding: 8px;color:#fff;">Sl. No.</th>
					  <th style="background-color: #2e4b90;font-size:14px;border: 1px solid #ddd;padding: 8px;color:#fff;">Name</th>
					  <th style="background-color: #2e4b90;font-size:14px;border: 1px solid #ddd;padding: 8px;color:#fff;">Designation </th>
					 <!-- <th style="background-color: #2e4b90;font-size:14px;border: 1px solid #ddd;padding: 8px;color:#fff;">Directorate Name </th>-->
					  <th style="background-color: #2e4b90;font-size:14px;border: 1px solid #ddd;padding: 8px;color:#fff;">Received On </th>
					</tr>';
	$table_end ='</table>';
	
	   
	   $pagecnt = 1;	
	   $i=0;
	   foreach($rsData as $pdfresult){
	   	
		if($i==0){
			$signature .= $table_st;
		}else if($pagecnt == 1){
		  // for first page	
		  if($i>7){
			$pagecnt++;
			//$i=0;
			$signature .= $table_end;
			$signature .= $table_st;
			$signature .='<pagebreak>';
		  }
		}else if($pagecnt > 1){
		  // for second page	
		  if($i>20){
			$pagecnt++;
			//$i=0;
			$signature .= $table_end;
			$signature .= $table_st;
			$signature .='<pagebreak>';
		  }
		}
		$i++;
		$signature .='<tr>
					  <td style="background-color: #f2f2f2;font-size:14px;border: 1px solid #ddd;padding: 8px;">'.$i.'</td>
					  <td style="background-color: #f2f2f2;font-size:14px;border: 1px solid #ddd;padding: 8px;">'.$pdfresult->fname.'</td>
					  <td style="background-color: #f2f2f2;font-size:14px;border: 1px solid #ddd;padding: 8px;">'.$pdfresult->designation.'</td>
					  <!--<td style="background-color: #f2f2f2;font-size:14px;border: 1px solid #ddd;padding: 8px;">'.$pdfresult->directorate_name.'</td>-->
					  <td style="background-color: #f2f2f2;font-size:14px;border: 1px solid #ddd;padding: 8px;">'.date('d-m-Y h:i:s', strtotime($pdfresult->created_date)).'</td>
					</tr>
					';
		}
		
		$signature .= $table_end;
		
		$signature .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">
						<tr>
						<td align="right" style="padding-top:0px;">
						  <table width="100%" border="0" cellspacing="0" cellpadding="0">	
						  <tr>
							<td style="font-size:13; padding:3px;">SD/-</td>
						  </tr>
						  <tr>
							<td style="border-top:1px solid #ccc;font-size:13; padding:3px;"><strong>Field Nodal Offical</strong></td>
						  </tr>
						  </table>
						  </td>
						  </tr>
						</table>'; 
		
		
	
	$last_footer ='<hr width="100%">
	<table width="100%">
	<tr>
	<td align="center" style="font-size:13; padding:10px 0;"><strong>Note:</strong> This is a system generated document. No signature required. (Page {PAGENO} of {nb})</td>
	</tr>
	</table>
	';
	$footer = '
	</body>
	</html>';

	$output = $header.$signature;
	//return pdf_using_mpdf_api($output);
	$mpdf = new mPDF('utf-8', 'A4', '', '', 10, 10, 10, 8, 0, 0);
	/*$mpdf->SetDisplayMode('fullpage');
	
	$mpdf->list_indent_first_level = 1;*/
	$mpdf->SetHTMLFooter($last_footer);
	
	$mpdf->SetWatermarkText('Asset Declaration',0.1);
	$mpdf->showWatermarkText = true;
	//$mpdf->SetWatermarkImage('./sites/all/modules/common_pdf_generator/includes/stamp.png');
	//$mpdf->showWatermarkImage = true;
	
	/*$mpdf->debug = true;*/
	$mpdf->showImageErrors = true;
	
	$mpdf->WriteHTML($output);
	
	$mpdf->Output();
	
	}else{
		drupal_set_message('Still Now PDF is not generated. Please generate PDF first.', $type='warning');
		//drupal_goto('grn/list');
	}
}


function bulkacknowledgement_field_received_form($args) {	
  include('mpdf/mpdf.php');
  global $user, $base_root, $base_path;
  $mpdf = new mPDF('utf-8', 'A4', '', '', 10, 10, 10, 8, 0, 0);	
  $operatorInfo = getLoginUserDetailForAsset($user->uid); 
  //print_r($operatorInfo); exit;
  /*echo "abc";
  echo "<pre>";
  print_r(unserialize(base64_decode($args)));
  die;*/
  //echo $args; exit;
  $uid_in = unserialize(base64_decode($args));
  //print_r($uid_in); exit;
	
  $bulkpdf = db_select('a_asset_mst','am');
  $bulkpdf->leftJoin('users', 'u', 'u.uid = am.uid');  
  $bulkpdf->leftJoin('a_user_details', 'ud', 'ud.uid = am.uid');  
  $bulkpdf->leftJoin('a_directorate_mst', 'dm', 'dm.directorate_code = am.directorate_code');  
  $bulkpdf->leftJoin('a_user_details_service', 'us', 'am.uid = us.uid'); 
  
  $bulkpdf->leftJoin('a_transaction_history', 't', 'am.transaction_id = t.id'); 
  
  $bulkpdf->fields('am', array('id','uid','declaration_yr','designation','directorate_code','status','created_date','forward_status'));
  $bulkpdf->fields('u', array('name','access','created'));
  $bulkpdf->fields('ud', array('fname','status'));
  $bulkpdf->fields('dm', array('directorate_name'));
  $bulkpdf->fields('us', array('district_code','directorate_code','emp_group','office_id'));
  
  $bulkpdf->fields('t', array('forwarding_no','transaction_date','status'));
  
  $bulkpdf->condition('am.uid',$uid_in,'IN');
  $bulkpdf->condition('am.declaration_yr',date('Y'),'=');
  $bulkpdf->orderBy('am.created_date','asc');
  
  $result = $bulkpdf->execute();
  $rsData = $result->fetchAll();
  
  //print_r($rsData);exit;
  if($operatorInfo['directorate_code'] == 'LC'){
		
		$office_address = getOfficeAddress($office_id);
		if($rsData[0]->office_id == 0){
			$operator_office_id = '117';
		}else{
			$operator_office_id = $rsData[0]->office_id;
		}
		//echo $rsData[0]->office_id."<br>"; exit;
		//print_r($office_address); exit;
		foreach($office_address as $val){
			//echo "-->".$operatorInfo['office_id']."-->".$val->office_id;
			if($operator_office_id == $val->office_id){
				if($operator_office_id == '117'){
					$directorate_name = 'Labour Commissionerate';
				}else{
					$directorate_name = $val->office_name;
				}
				$daddress = $val->office_address;
				
				//echo $directorate_name; exit;
			}
			//break;
		}
	}
  
   
  //print_r($rsData); exit;
  
  $str = "'";
  foreach($uid_in as $v){
	 $str .= $v.","; 
  }
  $str = rtrim($str,",");
  $newstr = $str."'";
  //echo $newstr; exit;
  
  $bulkpdf_transaction_no = db_query("select forwarding_no, status, remarks from a_transaction_history where asset_user_id = $newstr and declaration_year = ".$rsData[0]->declaration_yr." order by id desc");	
  $rsData_transaction = $bulkpdf_transaction_no->fetchAll();
  
  $cntData = 0;
  $cntData = count($rsData);
  
	if(1){ 
	
	$i=0;
	$text = "";
	$qrpath = variable_get('file_public_path', conf_path() . '/files') . "/qrcode/ASSET-".$rsData[0]->declaration_yr."-".
							$rsData[0]->uid."-".$rsData[0]->id.'.png';
    foreach($rsData as $pdfresult){
	   //$i++;	
	$text .= $pdfresult->fname.', '.$pdfresult->designation.', '.$pdfresult->directorate_name.', '.$pdfresult->declaration_yr.',
		  '.$pdfresult->created_date;
	
   }
   //echo $text; exit;
   if (!file_exists($qrpath)) {
		$qrpath =  myfun_qrcode($text , $qrpath);
	}
	
  if($rsData_transaction[0]->status == 'R'){
	  if($rsData_transaction[0]->remarks == '1'){
		  $cause = 'Mutilated';
	  }elseif($rsData_transaction[0]->remarks == '2'){
		  $cause = 'Not Properly Sealed';
	  }elseif($rsData_transaction[0]->remarks == '3'){
		  $cause = 'Apparently Blank';
	  }
	  $received_reject = 'rejected, because it is '.$cause;
  }else{
	  $received_reject = 'received, in sealed envelopes (Contents Not Verified) at the Labour Commisionerate';
  }
	$output = '';
	$content = '';
	$header = '<!DOCTYPE html>
			  <html>
			  <head>
				<meta charset="utf-8">
				<title>Acknowledgement</title>
				<link rel="stylesheet" href="'.$base_root.$base_path.'sites/all/modules/common_pdf_generator/includes/mpdfstyletables.css" media="all" />
			  </head>
			  <body>
				 <table width="100%" border="0" cellspacing="0" cellpadding="0">
					<tbody>
					 <tr>
						<td align="right" width="55%">
						<img src="./sites/all/modules/common_pdf_generator/includes/logo.png" style="width:120px;">
						</td>
						<td align="right" width="40%" style="padding-top:30px;">
						<img src="./'.$qrpath.'" style="width:120px; height=120px;">
						</td>
					  </tr>
					 <tr>
						<td colspan="2" align="center" style="font-size:22px;margin: 0;padding: 0;color:#2e4b90;">Government of West Bengal<br/>
<strong>Labour Commissionerate</strong></td>
					  </tr>

					  <tr>
						<td colspan="2" align="center" style="font-size:16px;margin: 0;padding:0 0 20px;color:#676767;">New Secretariat Buildings (11th Floor), ‘A’–Block <br/> 1, K.S Roy Road, Kolkata – 700001</td>
					  </tr>
					  <tr>
						<td colspan="2" align="center" style="background:#2e4b90;padding:2px;"></td>
					  </tr>
					   <tr>
						<td align="left" style="font-size:15px;padding:30px 0;">No: <strong>'.$rsData[0]->forwarding_no.'</strong></td>
						<td align="right" style="font-size:15px;padding:30px 0;">Date: <strong>'.date('d-m-Y',strtotime($rsData[0]->transaction_date)).'</strong></td>
					  </tr>
					  <tr>
						<td colspan="2" style="font-size:15px;padding:0;">
							To,<br/>
							'.$directorate_name.', <br/>
							'.$daddress.' <br/>
						</td>
					  </tr>
					  <tr>
						<td colspan="2" style="font-size:20px;color:#0e783d;padding:40px 0 0;" align="center"><strong>ACKNOWLEDGEMENT</strong></td>
					  </tr>
					 <!-- <tr>
						<td colspan="2" style="font-size:15px;color:#0e783d;padding:0;" align="center"><strong>Ref: <strong>'.$rsData_transaction[0]->forwarding_no.'</strong></td>
					  </tr>-->
					  <tr>
						<td colspan="2" style="font-size:16px;padding:40px 0;">
						"DECLARATION OF ASSETS AS THEY STOOD ON 01/01/'.$rsData[0]->declaration_yr.'" 
						in respect of the following '.$cntData.' Officers under '.$directorate_name.'  
						are hereby '.$received_reject.'  
						</td>
					  </tr> 
					  </tbody> 
				</table>
					  
	';
	
		
	$signature ='';				 	  
				  
	$table_st = '<table width="900" border="0" cellspacing="0" cellpadding="0">
					<tr>
					 <th style="background-color: #2e4b90;font-size:14px;border: 1px solid #ddd;padding: 8px;color:#fff;">Sl. No.</th>
					  <th style="background-color: #2e4b90;font-size:14px;border: 1px solid #ddd;padding: 8px;color:#fff;">Name</th>
					  <th style="background-color: #2e4b90;font-size:14px;border: 1px solid #ddd;padding: 8px;color:#fff;">Designation </th>
					  <th style="background-color: #2e4b90;font-size:14px;border: 1px solid #ddd;padding: 8px;color:#fff;">Directorate Name </th>
					  <th style="background-color: #2e4b90;font-size:14px;border: 1px solid #ddd;padding: 8px;color:#fff;">Received On </th>
					</tr>';
	$table_end ='</table>';				
	
	   $pagecnt = 1;	
	   $i=0;
	   foreach($rsData as $pdfresult){
	   	
		if($i==0){
			$signature .= $table_st;
		}else if($pagecnt == 1){
		  // for first page	
		  if($i>7){
			$pagecnt++;
			//$i=0;
			$signature .= $table_end;
			$signature .= $table_st;
			$signature .='<pagebreak>';
		  }
		}else if($pagecnt > 1){
		  // for second page	
		  if($i>20){
			$pagecnt++;
			//$i=0;
			$signature .= $table_end;
			$signature .= $table_st;
			$signature .='<pagebreak>';
		  }
		}
		$i++;
		$signature .='<tr>
					  <td style="background-color: #f2f2f2;font-size:14px;border: 1px solid #ddd;padding: 8px;">'.$i.'</td>
					  <td style="background-color: #f2f2f2;font-size:14px;border: 1px solid #ddd;padding: 8px;">'.$pdfresult->fname.'</td>
					  <td style="background-color: #f2f2f2;font-size:14px;border: 1px solid #ddd;padding: 8px;">'.$pdfresult->designation.'</td>
					  <td style="background-color: #f2f2f2;font-size:14px;border: 1px solid #ddd;padding: 8px;">'.$pdfresult->directorate_name.'</td>
					  <td style="background-color: #f2f2f2;font-size:14px;border: 1px solid #ddd;padding: 8px;">'.date('d-m-Y h:i:s', strtotime($pdfresult->created_date)).'</td>
					</tr>
					';
		}
		
		$signature .= $table_end;
		
		$signature .= '<table width="100%" border="0" cellspacing="0" cellpadding="0">
						<tr>
						<td align="right" style="padding-top:0px;">
						  <table width="100%" border="0" cellspacing="0" cellpadding="0">	
						  <tr>
							<td style="font-size:13; padding:3px;">SD/-</td>
						  </tr>
						  <tr>
							<td style="border-top:1px solid #ccc;font-size:13; padding:3px;"><strong>Nodal Offical</strong></td>
						  </tr>
						  </table>
						  </td>
						  </tr>
						</table>'; 
		 
			
	
	$last_footer ='<hr width="100%">
	<table width="100%">
	<tr>
	<td align="center" style="font-size:13; padding:10px 0;"><strong>Note:</strong> This is a system generated document. No signature required. (Page {PAGENO} of {nb})</td>
	</tr>
	</table>
	';
	$footer = '
	</body>
	</html>';

	$output = $header.$signature;
	//return pdf_using_mpdf_api($output);
	
	//$mpdf->SetDisplayMode('fullpage');
	
	/*$mpdf->list_indent_first_level = 1;*/
	$mpdf->SetHTMLFooter($last_footer);
	
	$mpdf->SetWatermarkText('Asset Declaration',0.1);
	$mpdf->showWatermarkText = true;
	//$mpdf->SetWatermarkImage('./sites/all/modules/common_pdf_generator/includes/stamp.png');
	//$mpdf->showWatermarkImage = true;
	
	/*$mpdf->debug = true;*/
	$mpdf->showImageErrors = true;
	
	$mpdf->WriteHTML($output);
	
	$mpdf->Output();
	
	}else{
		drupal_set_message('Still Now PDF is not generated. Please generate PDF first.', $type='warning');
		//drupal_goto('grn/list');
	}
}

/******************************************************* need to upload ******************************************/


function sar_print_form($args) {

  include('mpdf/mpdf.php');
  global $user, $base_root, $base_path;
	
  //$status = getUserProfileStatus($user->uid);
  $userData = getLoginUserDetailForAsset($user->uid);
  
  //print_r($userData); exit;
	
	if(1){ 
	
	$i=0;
	
	$biodetails = '';
	$output = '';
	$content = '';
	
	$header = '<!DOCTYPE html>
			  <html>
			  <head>
				<meta charset="utf-8">
				<title>Acknowledgement</title>
				<link rel="stylesheet" href="'.$base_root.$base_path.'sites/all/themes/asset/css/style.css" media="all" />
				<link rel="stylesheet" href="'.$base_root.$base_path.'sites/all/modules/common_pdf_generator/includes/mpdfstyletables.css" media="all" />
			  </head>
			  <body>
				 ';
	
	$content = serviceDetails($user->uid).educationDetails($user->uid).postingDetails($user->uid).inserviceTrainingDetails($user->uid).foreignTrainingDetails($user->uid).awardpubDetails($user->uid);
	
	
	$signature ='';
	
	$last_footer ='<hr width="100%">
	<table width="100%">
	<tr>
	<td align="center" style="font-size:13; padding:10px 0;"><strong>Note:</strong> This is a system generated document. No signature required.</td>
	</tr>
	</table>
	';
	$footer = '
	</body>
	</html>';

	$output = $header.$content.$signature.$footer;
	//echo $output; die();
	//return pdf_using_mpdf_api($output);
	$mpdf = new mPDF('utf-8', 'A4', '', '', 10, 10, 10, 8, 0, 0);
	/*$mpdf->SetDisplayMode('fullpage');
	
	$mpdf->list_indent_first_level = 1;*/
	$mpdf->SetHTMLFooter($last_footer);
	
	$mpdf->SetWatermarkText('ERMS Labour Department',0.1);
	$mpdf->showWatermarkText = true;
	//$mpdf->SetWatermarkImage('./sites/all/modules/common_pdf_generator/includes/stamp.png');
	//$mpdf->showWatermarkImage = true;
	
	/*$mpdf->debug = true;*/
	$mpdf->showImageErrors = true;
	
	$mpdf->WriteHTML($output);
	
	$mpdf->Output();
	
	}else{
		drupal_set_message('Still Now PDF is not generated. Please generate PDF first.', $type='warning');
		//drupal_goto('grn/list');
	}
}