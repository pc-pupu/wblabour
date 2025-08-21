<?php global $base_root,$base_path,$user;?>
<?php
$query = db_select('ld_users_details', 'us');
$query->leftJoin('users', 'u', 'u.uid=us.uid');
$query ->fields('u', array( 'name','created'));
$query ->fields('us', array( 'fname','mname','lname','gender','dob','mobile','email','pincode','state','district','subdivision','areatype','block','panchayat','policestation','postoffice','address','ldapplicationflag'));
$query->condition('us.uid',trim($user->uid),'=');
$result = $query->execute();
$data = $result->fetchObject();
if($data->ldapplicationflag=='1'){
	drupal_goto('dashboard1');
}
?>
<!--start body here-->
<link href="<?php print $base_path ?>sites/all/modules/dashboard/vendors/font-awesome/css/font-awesome.min.css" rel="stylesheet">
<link href="<?php print $base_path ?>sites/all/modules/dashboard/vendors/font-awesome/css/font-awesome.css" rel="stylesheet">
<!-- NProgress -->
<link href="<?php print $base_path ?>sites/all/modules/dashboard/vendors/nprogress/nprogress.css" rel="stylesheet">
<!-- iCheck -->
<link href="<?php print $base_path ?>sites/all/modules/dashboard/vendors/iCheck/skins/flat/green.css" rel="stylesheet">

<!-- bootstrap-progressbar -->
<link href="<?php print $base_path ?>sites/all/modules/dashboard/vendors/bootstrap-progressbar/css/bootstrap-progressbar-3.3.4.min.css" rel="stylesheet">
<!-- JQVMap -->
<link href="<?php print $base_path ?>sites/all/modules/dashboard/vendors/jqvmap/dist/jqvmap.min.css" rel="stylesheet"/>
<!-- bootstrap-daterangepicker -->
<link href="<?php print $base_path ?>sites/all/modules/dashboard/vendors/bootstrap-daterangepicker/daterangepicker.css" rel="stylesheet">
<link href="<?php print $base_path ?>sites/all/modules/dashboard/build/css/tmpdashboard.css" rel="stylesheet">
<!-- Custom Theme Style -->
<link href="<?php print $base_path ?>sites/all/modules/dashboard/build/css/custom.css" rel="stylesheet">

<style>
 #divCountertemp{
	font-size: 20px;
    padding: 10px 0;
    font-weight: 600;
    color: #000;
    background: #ccc;
    display: block;
    clear: both;
    margin: 20px auto;
    width: 170px;
    border:2px solid #c3c3c3;
	}
</style>

<div class="whitebg2">
  <div class="about_body"> 
    <!-- container starts here -->
    <div class="container">
      <div class="row">
        <?php //print $breadcrumb; ?>
        <div class="col-md-12 col-sm-9 col-xs-12 profile_details">
          <div class="col-sm-12"> 
            <!-- <h4 class="brief"><i>Welcome on Board</i></h4>-->
            <div class="right col-xs-5 text-center"> 
              
              <!-- <div class="temporary-id-panel"><a href="#" class="btn temporary-id">Temporary ID - <?php if(!empty($data->name)){ echo $data->name;}else{ echo "N/A";}?>(48hr valid)</a></div>-->
              <div class="text-center myprofilepic"> <img src="<?php print $base_path ?>sites/all/modules/dashboard/images/user.png" alt="" class="img-circle img-responsive#"></div>
              <div class="sidebar-widget"> 
                <!-- <h4>Profile Completion</h4>--> 
                <!--<canvas width="150" height="80" id="chart_gauge_01" class="" style="width: 160px; height: 100px;"></canvas>-->
                <h2>
                  <?php if(!empty($data->fname) && (!empty($data->lname))){echo $data->fname." ".$data->mname." ".$data->lname;}else{ echo "N/A";}?>
                </h2>
                <a href="<?php echo $base_root.$base_path?>wizard" class="btn btn-warning eservice services-dashboard">Apply for E-services</a> 
                <!--<canvas width="150" height="80" id="chart_gauge_01" class="custom-spedo-meter"></canvas>
                <div class="goal-wrapper"> <span id="gauge-text" class="gauge-value pull-left">0</span> <span class="gauge-value pull-left">%</span> <span id="goal-text" class="goal-value pull-right">100%</span> </div>--> 
                 <div id="divCountertemp"></div>
              </div>
            </div>
            <div class="left col-xs-7"> 
              <!-- <h2><?php if(!empty($data->fname) && (!empty($data->lname))){echo $data->fname." ".$data->mname." ".$data->lname;}else{ echo "N/A";}?></h2>-->
              <div class="temporary-id-panel">
                <div class="temporary-id">Temporary ID -
                  <?php if(!empty($data->name)){ echo $data->name;}else{ echo "N/A";}?>
                </div>
                <div class="temporary-id-pane-note">This Id is valid for 48hrs & after 48hrs you will not be eligible to avail these services.</div>
              </div>
              <table class="data table table-striped no-margin">
                <thead>
                  <tr>
                    <th><i class="fa fa-birthday-cake"></i> DOB :
                      <?php if(!empty($data->dob)){ echo format_date(strtotime($data->dob), 'custom', 'd-m-Y');}else{ echo "N/A";}?>
                      </li></th>
                  </tr>
                  <tr>
                    <th><i class="fa fa-envelope"></i> Email :
                      <?php if(!empty($data->email)){ echo $data->email;}else{ echo "N/A";}?></th>
                  </tr>
                  <tr>
                    <th><i class="fa fa-phone"></i> Phone :
                      <?php if(!empty($data->mobile)){ echo $data->mobile;}else{ echo "N/A";}?></th>
                  </tr>
                  <tr>
                    <th class="hidden-phone"><i class="fa fa-map-marker"></i> Pin :
                      <?php if(!empty($data->pincode)){ echo $data->pincode;}else{ echo "N/A";}?></th>
                  </tr>
                  <tr>
                    <th><i class="fa fa-building"></i> Address:
                      <?php if(!empty($data->address)){ echo $data->address;}else{ echo "N/A";}?></th>
                  </tr>
                </thead>
              </table>
              <!-- <a href="<?php echo $base_root.$base_path?>wizard" class="btn btn-warning eservice">Apply for E-services</a>--> 
            </div>
          </div>
        </div>
        <div class="container">
          <div class="row">
            <div class="col-sm-12 tabbable-panel Main_tab">
              <h3>Comprehensive Information Sheet</h3>
              <div class="tabbable-line MTab_nav_holder">
                <ul class="nav nav-tabs MTab_nav">
                  <li class="active sop"> <a href="#sop" data-toggle="tab">Standard Operating Procedure</a> </li>
                  <li class="timeline"> <a href="#timeline" data-toggle="tab">Timelines</a> </li>
                  <li class="checklist"> <a href="#checklist" data-toggle="tab">Checklists</a> </li>
                  <li class="sip"> <a href="#sip" data-toggle="tab">Standard Inspection Procedure</a> </li>
                  <li class="inspection"> <a href="#checklist-for-inspection" data-toggle="tab">Checklist for Inspection</a> </li>
                </ul>
              </div>
              <div class="tab-content Main_tab_content">
                <div class="tab-pane active" id="sop">
                  <div class="tabbable tabs-left">
                    <ul class=" col-sm-2 nav nav-tabs" role="tablist">
                      <li role="presentation" class="active"><a href="#Pre-Operation" aria-controls="home" role="tab" data-toggle="tab">Pre Operation</a></li>
                      <li role="presentation"><a href="#Pre-Establishment" aria-controls="home" role="tab" data-toggle="tab">Pre Establishment</a></li>
                      <li role="presentation"><a href="#Post-Operation" aria-controls="home" role="tab" data-toggle="tab">Others</a></li>
                    </ul>
                    <div class="col-sm-10 tab-content STab_content">
                      <div class="tab-pane active" id="Pre-Operation">
                        <div class="tabbable-panel InTopTab">
                          <div class="tabbable-line">
                            <ul class="nav nav-tabs tabtop  tabsetting">
                              <li class="active"> <a href="#Pre-Operation-Boilers" data-toggle="tab">Directorate of Boilers</a> </li>
                              <li> <a href="#Pre-Operation-Commissionerate" data-toggle="tab">Labour Commissionerate</a> </li>
                              <li> <a href="#Pre-Operation-Factory" data-toggle="tab">Directorate of Factories</a> </li>
                              <li> <a href="#Pre-Operation-Shop" data-toggle="tab">Shops and Establishment</a> </li>
                            </ul>
                          </div>
                          <div class="tab-content InTTab_content">
                            <div class="tab-pane active fade in" id="Pre-Operation-Boilers">
                              <div class="panel-group Custom_AC_tab" id="boiler-sop">
                                <div class="panel panel-default panel-faq">
                                  <div class="panel-heading">
                                    <h4 class="panel-title"><a data-toggle="collapse" data-parent="#boiler-sop" href="#section1" class="collapsed">Standard Operating Procedure for Registration of Boilers <span class="glyphicon glyphicon-minus pull-right"></span></a> </h4>
                                  </div>
                                  <div id="section1" class="panel-collapse collapse in">
                                    <div class="panel-body">
                                      <p>1) Submission of registration folder along with application for registration/erection of boiler.</p>
                                      <p>2) Erection Meeting for registration/erection of the boiler.</p>
                                      <p>3) Submission of requisite fees and Travelling Allowances for registration/erection.</p>
                                      <p>4) Approval of drawing of pipe lines.</p>
                                      <p>5) Approval of contractor/erector.</p>
                                      <p>6) Welding Procedure Specification approval.</p>
                                      <p>7) Simulation Test of Welders.</p>
                                      <p>8) Material inspection of boiler and pipe lines.</p>
                                      <p>9) Physical and chemical testing of pipe lines</p>
                                      <p>10) Fit-up inspection of pressure parts of boiler and pipe lines.</p>
                                      <p>11) Inspection after completion of welding and NDT marking for boiler and pipe lines.</p>
                                      <p>12) Submission of satisfactory NDT report.</p>
                                      <p>13) Post weld heat treatment if required.</p>
                                      <p>14) PMI testing for all alloy steel materials of boiler and pipe lines.</p>
                                      <p>15) Approval of pressure parts calculation of boiler.</p>
                                      <p>16) Hydraulic test of boiler and pipe lines.</p>
                                      <p>17) Approval of form-IIIA of pipe lines.</p>
                                      <p>18) Issue of Provisional certificate of boiler.</p>
                                      <p>19) Steam Test of boiler.</p>
                                      <p>20) Allotment of registration number of boiler.</p>
                                      <p>21) Engraving of registration number of boiler.</p>
                                    </div>
                                  </div>
                                </div>
                                <div class="panel panel-default panel-faq">
                                  <div class="panel-heading">
                                    <h4 class="panel-title"><a data-toggle="collapse" data-parent="#boiler-sop" href="#section2" class="collapsed"> Standard Operating Procedure for Renewal of certificate of Boilers <span class="glyphicon pull-right glyphicon-plus"></span></a> </h4>
                                  </div>
                                  <div id="section2" class="panel-collapse collapse">
                                    <div class="panel-body">
                                      <p>1) Application for renewal of certificate along with <strong>Form-B No.1</strong> duly filled in.</p>
                                      <p>2) Submission of requisite fees for inspection of boiler in the head of accounts: “<strong>0230-00-103-001-14</strong>” – Service fees (14) online by <strong>IFMS-GRIPS</strong> portal in <a href="http://www.wbfin.nic.in/" target="_blank">www.wbfin.nic.in</a>.</p>
                                      <p>3) Submission of requisite Travelling Allowance in the head of accounts: “<strong>0230-00-103-002-27</strong>” – Other Receipts (27) online by <strong>IFMS-GRIPS</strong> portal in <a href="http://www.wbfin.nic.in/" target="_blank">www.wbfin.nic.in</a></p>
                                      <p>4) Dry and thorough inspection of boiler.</p>
                                      <p>5) Hydraulic Test of Boiler.</p>
                                      <p>6) Issuance of Provisional Certificate of the boiler after satisfactory hydraulic test.</p>
                                      <p>7) Issuance of Final Certificate of the boiler.</p>
                                    </div>
                                  </div>
                                </div>
                                <div class="panel panel-default panel-faq">
                                  <div class="panel-heading">
                                    <h4 class="panel-title"><a data-toggle="collapse" data-parent="#boiler-sop" href="#section3" class="collapsed"> Standard Operating Procedure for Repair of Boiler <span class="glyphicon pull-right glyphicon-plus"></span></a></h4>
                                  </div>
                                  <div id="section3" class="panel-collapse collapse">
                                    <div class="panel-body">
                                      <p>1) Submission of requisite fees for re-inspection under repair of boiler in the head of accounts: “<strong>0230-00-103-001-14</strong>” – Service fees (14) online by <strong>IFMS-GRIPS</strong> portal in <a href="http://www.wbfin.nic.in/" target="_blank">www.wbfin.nic.in</a>.</p>
                                      <p>2) Submission of requisite Travelling Allowance in the head of accounts: “0230-00-103-002-27” – Other Receipts (27) online by IFMS-GRIPS portal in <a href="http://www.wbfin.nic.in/" target="_blank">www.wbfin.nic.in</a>.</p>
                                      <p>3) Approval of contractor/repairer.</p>
                                      <p>4) Welding Procedure Specification approval.</p>
                                      <p>5) Simulation Test of Welders.</p>
                                      <p>6) Material inspection for repair of boiler.</p>
                                      <p>7) Physical and chemical testing of materials to be used for repair.</p>
                                      <p>8) Fit-up inspection of pressure parts of boiler under repair.</p>
                                      <p>9) Inspection after completion of welding and NDT marking for boiler under repair.</p>
                                      <p>10) Submission of satisfactory NDT report.</p>
                                      <p>11) Post weld heat treatment if required.</p>
                                      <p>12) PMI testing for all alloy steel materials of boiler under repair.</p>
                                      <p>13) Hydraulic test of boiler under repair.</p>
                                      <p>14) Issuance of Provisional certificate of boiler.</p>
                                      <p>15) Issuance of Final Certificate of boiler.</p>
                                    </div>
                                  </div>
                                </div>
                                <div class="panel panel-default panel-faq">
                                  <div class="panel-heading">
                                    <h4 class="panel-title"><a data-toggle="collapse" data-parent="#boiler-sop" href="#section4" class="collapsed"> Standard Operating Procedure for Transfer of Ownership of Boiler <span class="glyphicon pull-right glyphicon-plus"></span></a> </h4>
                                  </div>
                                  
                                  <!--<div id="section1" class="panel-collapse collapse in">-->
                                  <div id="section4" class="panel-collapse collapse">
                                    <div class="panel-body">
                                      <p>1) Application for transfer of ownership of boiler by the proposed owner.</p>
                                      <p>2) Submission of requisite fees in the head of accounts: “<strong>0230-00-103-001-14</strong>” –Service fees (14) online by IFMS-GRIPS portal in <a href="http://www.wbfin.nic.in/" target="_blank">www.wbfin.nic.in</a>.</p>
                                      <p>3) Submission of requisite documents as per Check List.</p>
                                      <p>4) Scrutiny of Documents.</p>
                                      <p>5) Physical Verification of boiler along with documents proposed owners’ premises.</p>
                                      <p>6) Physical Verification of documents in the previous owners’ premises.</p>
                                      <p>7) Hearing of previous owners, if required.</p>
                                      <p>8) Hearing of Proposed owners.</p>
                                      <p>9) Issuance of Transfer of ownership order in favour of the proposed owners.</p>
                                      <p>10) Issuance of certificate of boiler in favour of the new owners after satisfactory inspection in the prescribed manner.</p>
                                    </div>
                                  </div>
                                </div>
                                <div class="panel panel-default panel-faq">
                                  <div class="panel-heading">
                                    <h4 class="panel-title"><a data-toggle="collapse" data-parent="#boiler-sop" href="#section5" class="collapsed"> Standard Operating Procedure for Remnant Life Assessment (RLA) of Boiler <span class="glyphicon pull-right glyphicon-plus"></span></a> </h4>
                                  </div>
                                  
                                  <!--<div id="section1" class="panel-collapse collapse in">-->
                                  <div id="section5" class="panel-collapse collapse">
                                    <div class="panel-body">
                                      <p>1) Meeting for RLA study with the Owners along with Approved RLA Organisation and approved contractor.</p>
                                      <p>2) Submission of requisite fees for inspection under RLA of boiler in the head of accounts: “<strong>0230-00-103-001-14</strong>” – Service fees (14) online by IFMS-GRIPS portal in <a href="http://www.wbfin.nic.in/" target="_blank">www.wbfin.nic.in</a>.</p>
                                      <p>3) Submission of requisite Travelling Allowance in the head of accounts: “<strong>0230-00-103-002-27</strong>” – Other Receipts (27) online by <strong>IFMS-GRIPS</strong> portal in<a href="http://www.wbfin.nic.in/" target="_blank">www.wbfin.nic.in</a></p>
                                      <p>4) Approval RLA scheme.</p>
                                      <p>5) Dry and thorough inspection of boiler.</p>
                                      <p>6) Inspection for RLA study with approved RLA organisation.</p>
                                      <p>7) Necessary tests for RLA.</p>
                                      <p>8) Submission of report by the RLA organisation.</p>
                                      <p>9) Issuance of certificate of boiler.</p>
                                    </div>
                                  </div>
                                </div>
                                <div class="panel panel-default panel-faq">
                                  <div class="panel-heading">
                                    <h4 class="panel-title"><a data-toggle="collapse" data-parent="#boiler-sop" href="#section6" class="collapsed"> Standard Operating Procedure for Registration of Economiser <span class="glyphicon pull-right glyphicon-plus"></span></a> </h4>
                                  </div>
                                  
                                  <!--<div id="section1" class="panel-collapse collapse in">-->
                                  <div id="section6" class="panel-collapse collapse">
                                    <div class="panel-body">
                                      <p>1) Submission of registration folder along with application for registration/erection of economiser.</p>
                                      <p>2) Erection Meeting for registration/erection of the economiser.</p>
                                      <p>3) Submission of requisite fees and Travelling Allowances for registration/erection.</p>
                                      <p>4) Approval of drawing of pipe lines.</p>
                                      <p>5) Approval of contractor/erector.</p>
                                      <p>6) Welding Procedure Specification approval.</p>
                                      <p>7) Simulation Test of Welders.</p>
                                      <p>8) Material inspection of economiser and pipe lines.</p>
                                      <p>9) Physical and chemical testing of pipe lines</p>
                                      <p>10) Fit-up inspection of pressure parts of economiser and pipe lines.</p>
                                      <p>11) Inspection after completion of welding and NDT marking for economiser and pipe lines.</p>
                                      <p>12) Submission of satisfactory NDT report.</p>
                                      <p>13) Post weld heat treatment if required.</p>
                                      <p>14) PMI testing for all alloy steel materials of economiser and pipe lines.</p>
                                      <p>15) Approval of pressure parts calculation of economiser.</p>
                                      <p>16) Hydraulic test of economiser and pipe lines.</p>
                                      <p>17) Approval of form-IIIA of pipe lines.</p>
                                      <p>18) Issue of Provisional certificate of economiser.</p>
                                      <p>19) Allotment of registration number of economiser.</p>
                                      <p>20) Engraving of registration number of economiser.</p>
                                    </div>
                                  </div>
                                </div>
                                <div class="panel panel-default panel-faq">
                                  <div class="panel-heading">
                                    <h4 class="panel-title"><a data-toggle="collapse" data-parent="#boiler-sop" href="#section7" class="collapsed"> Standard Operating Procedure for Erection of Steam and Feed Pipe Lines <span class="glyphicon pull-right glyphicon-plus"></span></a></h4>
                                  </div>
                                  
                                  <!--<div id="section1" class="panel-collapse collapse in">-->
                                  <div id="section7" class="panel-collapse collapse">
                                    <div class="panel-body">
                                      <p>1) Erection Meeting for installation of pipe lines.</p>
                                      <p>2) Approval of drawing of pipe lines.</p>
                                      <p>3) Submission of application for erection of pipe lines.</p>
                                      <p>4) Submission of requisite Travelling Allowances for erection of pipe lines.</p>
                                      <p>5) Approval of contractor/erector.</p>
                                      <p>6) Welding Procedure Specification approval.</p>
                                      <p>7) Simulation Test of Welders.</p>
                                      <p>8) Material inspection of pipe lines.</p>
                                      <p>9) Physical and chemical testing of pipe lines</p>
                                      <p>10) Fit-up inspection of pressure parts of pipe lines.</p>
                                      <p>11) Inspection after completion of welding and NDT marking for pipe lines.</p>
                                      <p>12) Submission of satisfactory NDT report.</p>
                                      <p>13) Post weld heat treatment if required.</p>
                                      <p>14) PMI testing for all alloy steel materials of pipe lines.</p>
                                      <p>15) Hydraulic test of pipe lines.</p>
                                      <p>16) Submission of form-IIIA of pipe lines along with requisite fees for inspection.</p>
                                      <p>17) Approval of form-IIIA of pipe lines.</p>
                                      <p>18) Issue of Identification Number for pipe lines.</p>
                                      <p>19) Engraving of Identification number of pipe lines.</p>
                                    </div>
                                  </div>
                                </div>
                                <div class="panel panel-default panel-faq">
                                  <div class="panel-heading">
                                    <h4 class="panel-title"><a data-toggle="collapse" data-parent="#boiler-sop" href="#section8" class="collapsed"> Standard Operating Procedure for Erection of Boilers <span class="glyphicon pull-right glyphicon-plus"></span></a> </h4>
                                  </div>
                                  <div id="section8" class="panel-collapse collapse">
                                    <div class="panel-body">
                                      <p>1) Submission of registration folder along with application for registration/erection of boiler.</p>
                                      <p>2) Erection Meeting for registration/erection of the boiler.</p>
                                      <p>3) Submission of requisite fees and Travelling Allowances for registration/erection.</p>
                                      <p>4) Approval of drawing of pipe lines.</p>
                                      <p>5) Approval of contractor/erector.</p>
                                      <p>6) Welding Procedure Specification approval.</p>
                                      <p>7) Simulation Test of Welders.</p>
                                      <p>8) Material inspection of boiler and pipe lines.</p>
                                      <p>9) Physical and chemical testing of pipe lines</p>
                                      <p>10) Fit-up inspection of pressure parts of boiler and pipe lines.</p>
                                      <p>11) Inspection after completion of welding and NDT marking for boiler and pipe lines.</p>
                                      <p>12) Submission of satisfactory NDT report.</p>
                                      <p>13) Post weld heat treatment if required.</p>
                                      <p>14) PMI testing for all alloy steel materials of boiler and pipe lines.</p>
                                      <p>15) Approval of pressure parts calculation of boiler.</p>
                                      <p>16) Hydraulic test of boiler and pipe lines.</p>
                                      <p>17) Issue of FORM II C.</p>
                                    </div>
                                  </div>
                                </div>
                                <div class="panel panel-default panel-faq">
                                  <div class="panel-heading">
                                    <h4 class="panel-title"><a data-toggle="collapse" data-parent="#boiler-sop" href="#section9" class="collapsed"> Standard Operating Procedure for Erection of Economiser <span class="glyphicon pull-right glyphicon-plus"></span></a> </h4>
                                  </div>
                                  
                                  <!--<div id="section1" class="panel-collapse collapse in">-->
                                  <div id="section9" class="panel-collapse collapse">
                                    <div class="panel-body">
                                      <p>1) Submission of registration folder along with application for registration/erection of economiser.</p>
                                      <p>2) Erection Meeting for registration/erection of the economiser.</p>
                                      <p>3) Submission of requisite fees and Travelling Allowances for registration/erection.</p>
                                      <p>4) Approval of drawing of pipe lines.</p>
                                      <p>5) Approval of contractor/erector.</p>
                                      <p>6) Welding Procedure Specification approval.</p>
                                      <p>7) Simulation Test of Welders.</p>
                                      <p>8) Material inspection of economiser and pipe lines.</p>
                                      <p>9) Physical and chemical testing of pipe lines</p>
                                      <p>10) Fit-up inspection of pressure parts of economiser and pipe lines.</p>
                                      <p>11) Inspection after completion of welding and NDT marking for economiser and pipe lines.</p>
                                      <p>12) Submission of satisfactory NDT report.</p>
                                      <p>13) Post weld heat treatment if required.</p>
                                      <p>14) PMI testing for all alloy steel materials of economiser and pipe lines.</p>
                                      <p>15) Approval of pressure parts calculation of economiser.</p>
                                      <p>16) Hydraulic test of economiser and pipe lines.</p>
                                      <p>17) Issue of FORM II C.</p>
                                    </div>
                                  </div>
                                </div>
                                <div class="panel panel-default panel-faq">
                                  <div class="panel-heading">
                                    <h4 class="panel-title"><a data-toggle="collapse" data-parent="#boiler-sop" href="#section10" class="collapsed">Standard Operating Procedure for Manufacturing of Boilers <span class="glyphicon pull-right glyphicon-plus"></span></a></h4>
                                  </div>
                                  <div id="section10" class="panel-collapse collapse">
                                    <div class="panel-body">
                                      <p>1) Submission of application with fees and approved drawing.</p>
                                      <p>2) Welding Procedure Specification approval.</p>
                                      <p>3) Welder qualification test.</p>
                                      <p>4) Material inspection of boiler and pipe lines.</p>
                                      <p>5) Physical and chemical testing of Raw Materials if not directly purchased from manufacturer.</p>
                                      <p>6) Fit-up inspection of pressure parts of boiler and pipe lines.</p>
                                      <p>7) Inspection after completion of welding and NDT marking for boiler and pipe lines.</p>
                                      <p>8) Submission of satisfactory NDT report.</p>
                                      <p>9) Post weld heat treatment if required.</p>
                                      <p>10) PMI testing for all alloy steel materials of boiler and pipe lines.</p>
                                      <p>11) Hydraulic test of boiler and pipe lines.</p>
                                      <p>12) Final Inspection and Stamping.</p>
                                      <p>13) Issue of Manufacturer Certificate.</p>
                                    </div>
                                  </div>
                                </div>
                                <div class="panel panel-default panel-faq">
                                  <div class="panel-heading">
                                    <h4 class="panel-title"><a data-toggle="collapse" data-parent="#boiler-sop" href="#section11" class="collapsed"> Standard Operating Procedure for Manufacturing of Economiser <span class="glyphicon pull-right glyphicon-plus"></span></a></h4>
                                  </div>
                                  
                                  <!--<div id="section1" class="panel-collapse collapse in">-->
                                  <div id="section11" class="panel-collapse collapse">
                                    <div class="panel-body">
                                      <p>1) Submission of application with fees and approved drawing.</p>
                                      <p>2) Welding Procedure Specification approval.</p>
                                      <p>3) Welder qualification test.</p>
                                      <p>4) Material inspection.</p>
                                      <p>5) Physical and chemical testing of Raw Materials if not directly purchased from manufacturer.</p>
                                      <p>6) Fit-up inspection of pressure parts.</p>
                                      <p>7) Inspection after completion of welding and NDT marking.</p>
                                      <p>8) Submission of satisfactory NDT report.</p>
                                      <p>9) Post weld heat treatment if required.</p>
                                      <p>10) PMI testing for all alloy steel materials.</p>
                                      <p>11) Hydraulic test.</p>
                                      <p>12) Final Inspection and Stamping.</p>
                                      <p>13) Issue of Manufacturer Certificate.</p>
                                    </div>
                                  </div>
                                </div>
                                <div class="panel panel-default panel-faq">
                                  <div class="panel-heading">
                                    <h4 class="panel-title"><a data-toggle="collapse" data-parent="#boiler-sop" href="#section12" class="collapsed"> Standard Operating Procedure for Approval / Recognition of Manufacturer <span class="glyphicon pull-right glyphicon-plus"></span></a></h4>
                                  </div>
                                  
                                  <!--<div id="section1" class="panel-collapse collapse in">-->
                                  <div id="section12" class="panel-collapse collapse">
                                    <div class="panel-body">
                                      <p>1) Submission of application in Standard Format.</p>
                                      <p>2) Inspection of Premises, Verification of Manpower along with their Experience and Machineries.</p>
                                      <p>3) Report Submission to the Director.</p>
                                      <p>4) Issue of Approval Letter by Director after necessary interaction.</p>
                                    </div>
                                  </div>
                                </div>
                                <div class="panel panel-default panel-faq">
                                  <div class="panel-heading">
                                    <h4 class="panel-title"><a data-toggle="collapse" data-parent="#boiler-sop" href="#section13" class="collapsed"> Standard Operating Procedure for Approval of Erectors <span class="glyphicon pull-right glyphicon-plus"></span></a></h4>
                                  </div>
                                  
                                  <!--<div id="section1" class="panel-collapse collapse in">-->
                                  <div id="section13" class="panel-collapse collapse">
                                    <div class="panel-body">
                                      <p>1) Submission of Application in standard format (FORM - XVIII as per IBR).</p>
                                      <p>2) Submission of requisite fees for inspection of boiler in the head of accounts : "0230-00-103-001-14"- Service fees (14) online by IFMS-GRIPS portal in <a href="http://www.wbifms.gov.in">www.wbifms.gov.in</a>.</p>
                                      <p>3) Submission of requisite Travelling Allowance in the head of accounts : "0230-00-103-002-27"- Other Receipts (27) online by IFMS-GRIPS portal in <a href="http://www.wbifms.gov.in">www.wbifms.gov.in</a>.</p>
                                      <p>4) Inspection of machineries available as per submitted doucuments, premises at the given address.</p>
                                      <p>5) Verification of Technical Personnel as per submitted list and their experience.</p>
                                      <p>6) Submission of report to the Director.</p>
                                      <p>7) Issue of Approval Letter by Director after necessary interaction.</p>
                                    </div>
                                  </div>
                                </div>
                              </div>
                            </div>
                            <div class="tab-pane fade in" id="Pre-Operation-Commissionerate">
                              <h2>Not Applicable</h2>
                              <!--<div class="panel-group Custom_AC_tab" role="tablist" aria-multiselectable="true">
                                  <div class="panel panel-default">
                                    <div class="panel-heading" role="tab">
                                      <h4 class="panel-title"> <a data-toggle="collapse" data-parent="#accordion" href="#MTab_1-STab_1-InTTab_1-AC1" aria-expanded="true">REGISTRATION OF PRINCIPAL EMPLOYER UNDER CONTRACT LABOUR (REGULATION & ABOLITION) ACT, 1970</a> </h4>
                                    </div>
                                    <div id="MTab_1-STab_1-InTTab_1-AC1" class="panel-collapse collapse in" role="tabpanel" >
                                      <div class="panel-body">
                                        <div class="sop_cntainer_box">
                                          <div class="sop_content">
                                            <div class="step_ord">Step-1</div>
                                            <div class="res_activity"> <strong>Responsibility: </strong><span title="Principal Employer...">Principal Employer</span>.<br>
                                              <strong>Activity:- </strong>The applicant shall open ‘www.wblc.gov.in’ and will select e services and Registration of <span title="Principal Employer...">Principal Employer</span> thereafter. A guide line will appear agreeing which he/she will land up in the log in page. If the applicant is an already registered user, he/she will log in using the credentials. For a new user he/she fills up a Common Application Form(CAF) in the Portal of wblc.gov.in, which includes mainly applicant’s Personal Information including PAN/Voters ID/Aadhar/Driving License, Trade License Number, any other unique number tagged with that establishment, Contact Information, Establishment Information, Number of workers employed, Login Information etc. with Preferred User name &amp; Password and create a User Credential. </div>
                                          </div>
                                          <div class="sop_content">
                                            <div class="step_ord">Step-2</div>
                                            <div class="res_activity"> <strong>Responsibility: </strong><span title="Principal Employer...">Principal Employer</span>.<br>
                                              <strong>Activity:- </strong>Logs into the system with the valid credentials and captcha and lands up in the Dashboard. </div>
                                          </div>
                                          <div class="sop_content">
                                            <div class="step_ord">Step-3</div>
                                            <div class="res_activity"> <strong>Responsibility: </strong><span title="Principal Employer...">Principal Employer</span>.<br>
                                              <strong>Activity:- </strong>Selects NEW REGISTRATION from menu and applies for online Registration of <span title="Principal Employer...">Principal Employer</span> under the Contract Labour (Regulation and Abolition) Act , 1970 by filling up necessary information in the Form and uploads self-certified copies of required documents.<br>
                                              <strong>Documents Involved: </strong>I.Valid Trade License, II.Articles of Association and Memorandum of Association/Partnership Deed, III.Factory License if any, IV.Other certificates of registration in case of other than company, proprietorship or partnership firm like cooperative, Trustees etc., V.Any other document in support of correctness of the particulars mentioned in the application if required </div>
                                          </div>
                                          <div class="sop_content">
                                            <div class="step_ord">Step-4</div>
                                            <div class="res_activity"> <strong>Responsibility: </strong><span title="Principal Employer...">Principal Employer</span>.<br>
                                              <strong>Activity:- </strong>Add valid contractor information into the system. </div>
                                          </div>
                                          <div class="sop_content">
                                            <div class="step_ord">Step-5</div>
                                            <div class="res_activity"> <strong>Responsibility: </strong><span title="Principal Employer...">Principal Employer</span>.<br>
                                              <strong>Activity:- </strong>Views the Filled in Information in the Application Preview Section before Final Submission or in case of correction rolls back to earlier sections and makes corrections and submit the application. The application is then reverted back to concerned officials according to jurisdiction  for verification. </div>
                                          </div>
                                          <div class="sop_content">
                                            <div class="step_ord">Step-6</div>
                                            <div class="res_activity"> <strong>Responsibility: </strong>Inspector concerned<br>
                                              <strong>Activity:- </strong>Logs into the system with credentials and lands up in the Dashboard and selects the application from the Application List. </div>
                                          </div>
                                          <div class="sop_content">
                                            <div class="step_ord">Step-7</div>
                                            <div class="res_activity"> <strong>Responsibility: </strong>Inspector concerned<br>
                                              <strong>Activity:- </strong>He views the application and verifies details along with uploaded documents one by one and marks Tick (√) which he finds correct and leaves the one as not verified which he finds Incorrect. </div>
                                          </div>
                                          <div class="sop_content">
                                            <div class="step_ord">Step-8</div>
                                            <div class="res_activity"> <strong>Responsibility: </strong>Inspector concerned<br>
                                              <strong>Activity:- </strong>He may reverts back to applicant for Correction / Rectification with remarks in case any correction or rectification is required or can forward it to the ALC for approval or rejection. </div>
                                          </div>
                                          <div class="sop_content">
                                            <div class="step_ord">Step-9</div>
                                            <div class="res_activity"> <strong>Responsibility: </strong><span title="Principal Employer...">Principal Employer</span>.<br>
                                              <strong>Activity:- </strong>Logs into the system with the credentials and views the status of application marked for correction if sent back by the Inspector, makes the corrections and resubmits the application. </div>
                                          </div>
                                          <div class="sop_content">
                                            <div class="step_ord">Step-10</div>
                                            <div class="res_activity"> <strong>Responsibility: </strong>Inspector concerned<br>
                                              <strong>Activity:- </strong>Logs into the system with Credentials, verifies or re-verifies the application as in the case may be, if found satisfactory forwards the same to the ALC concerned.. </div>
                                          </div>
                                          <div class="sop_content">
                                            <div class="step_ord">Step-11</div>
                                            <div class="res_activity"> <strong>Responsibility: </strong>ALC of the Subdivision/RLO<br>
                                              <strong>Activity:- </strong>Logs into the system with the credentials and views all the applications forwarded by Inspectors and if found satisfactory allows for Payment by the applicant. In case ALC finds something that is not satisfactory in the application he may revert it back either to the applicant or the Inspector as he deems fit.<br>
                                              ALC can also reject the application if finds so after observing principles of natural justice. </div>
                                          </div>
                                          <div class="sop_content">
                                            <div class="step_ord">Step-12</div>
                                            <div class="res_activity"> <strong>Responsibility: </strong><span title="Principal Employer...">Principal Employer</span>.<br>
                                              <strong>Activity:- </strong>Views application status in the Dashboard marked as PAYMENT (PAY NOW) by ALC and makes payment Online through GRIPS. <br>
                                              After successfull payment of fees statutory FORM-I is automatically generated. Applicant can digitally/in-hand signs the FORM-I and upload it. After FORM-I is successfully uploaded, an acknowledgement is generated. <br>
                                              In case it is returned back by the ALC he views on the Dashboard the status of application marked for correction and makes the necessary corrections and resubmits the application.<br>
                                              <strong>Documents Involved: </strong>FORM-I </div>
                                          </div>
                                          <div class="sop_content">
                                            <div class="step_ord">Step-13</div>
                                            <div class="res_activity"> <strong>Responsibility: </strong>ALC of the Subdivision/RLO<br>
                                              <strong>Activity:- </strong>Logs into the system with the credentials. After satisfactory payment and correct FORM-I is uploaded with signature, ALC issues Digitally signed Registration Certificate&ndash; FORM-II and Uploads in the system. FORM-Vs for Contractors engaged under the <span title="Principal Employer...">Principal Employer</span> are automatically generated. </div>
                                          </div>
                                          <div class="sop_content">
                                            <div class="step_ord">Step-14</div>
                                            <div class="res_activity"> <strong>Responsibility: </strong><span title="Principal Employer...">Principal Employer</span>.<br>
                                              <strong>Activity:- </strong>Logs into the system with the Credentials and Views the FORM-V, digitally/in-hand signs and send via e-mail or through SMS the Unique number of Form-V to Contractors for applying of License. </div>
                                          </div>
                                          <div class="sop_content">
                                            <div class="step_ord">Note:</div>
                                            <div class="res_activity"> <strong>Responsibility: </strong><span title="Principal Employer...">Principal Employer</span>.<br>
                                              <strong>Activity:- </strong>Track Status of Application through SMS Alerts generated through the System starting from Creating Login Credentials, Submission of Application, Correction Required, Payment of Fees , Status of Approval or Rejection , Status on Issue of Registration Certificate and viewing through his dashboard. </div>
                                          </div>
                                        </div>
                                      </div>
                                    </div>
                                  </div>
                                  <div class="panel panel-default">
                                    <div class="panel-heading" role="tab">
                                      <h4 class="panel-title"> <a class="collapsed" data-toggle="collapse" data-parent="#accordion" href="#MTab_1-STab_1-InTTab_1-AC2" aria-expanded="false">LICENSING OF CONTRACTORS UNDER CONTRACT LABOUR (REGULATION & ABOLITION) ACT, 1970</a> </h4>
                                    </div>
                                    <div id="MTab_1-STab_1-InTTab_1-AC2" class="panel-collapse collapse" role="tabpanel">
                                      <div class="panel-body"> Coming Soon </div>
                                    </div>
                                  </div>
                                  <div class="panel panel-default">
                                    <div class="panel-heading" role="tab">
                                      <h4 class="panel-title"> <a class="collapsed" data-toggle="collapse" data-parent="#accordion" href="#MTab_1-STab_1-InTTab_1-AC3" aria-expanded="false">REGISTRATION OF ESTABLISHMENT UNDER BUILDING AND OTHER CONSTRUCTION WORKERS ACT 1996 AND RULES 2004</a> </h4>
                                    </div>
                                    <div id="MTab_1-STab_1-InTTab_1-AC3" class="panel-collapse collapse" role="tabpanel">
                                      <div class="panel-body">Coming Soon</div>
                                    </div>
                                  </div>
                                  <div class="panel panel-default">
                                    <div class="panel-heading" role="tab">
                                      <h4 class="panel-title"> <a class="collapsed" data-toggle="collapse" data-parent="#accordion" href="#MTab_1-STab_1-InTTab_1-AC4" aria-expanded="false">REGISTRATION OF PRINCIPAL EMPLOYER UNDER INTER STATE MIGRANT WORKMEN (REGULATION OF EMPLOYMENT AND CONDITIONS OF SERVICE) ACT, 1979</a> </h4>
                                    </div>
                                    <div id="MTab_1-STab_1-InTTab_1-AC4" class="panel-collapse collapse" role="tabpanel">
                                      <div class="panel-body">Coming Soon</div>
                                    </div>
                                  </div>
                                  <div class="panel panel-default">
                                    <div class="panel-heading" role="tab">
                                      <h4 class="panel-title"> <a class="collapsed" data-toggle="collapse" data-parent="#accordion" href="#MTab_1-STab_1-InTTab_1-AC5" aria-expanded="false">INSPECTION NOTE - UPLOAD BY INSPECTORS & DOWNLOAD BY APPLICANT</a> </h4>
                                    </div>
                                    <div id="MTab_1-STab_1-InTTab_1-AC5" class="panel-collapse collapse" role="tabpanel">
                                      <div class="panel-body">Coming Soon</div>
                                    </div>
                                  </div>
                                  <div class="panel panel-default">
                                    <div class="panel-heading" role="tab">
                                      <h4 class="panel-title"> <a class="collapsed" data-toggle="collapse" data-parent="#accordion" href="#MTab_1-STab_1-InTTab_1-AC6" aria-expanded="false">INSPECTOR RANDOMIZATION - FOR DEPUTY LABOUR COMMISSIONER (DLC) & ASSISTANT LABOUR COMMISSIONER (ALC)</a> </h4>
                                    </div>
                                    <div id="MTab_1-STab_1-InTTab_1-AC6" class="panel-collapse collapse" role="tabpanel">
                                      <div class="panel-body">Coming Soon</div>
                                    </div>
                                  </div>
                                </div>--> 
                            </div>
                            <div class="tab-pane fade in" id="Pre-Operation-Factory">
                              <div class="panel-group Custom_AC_tab" id="Pre-Operation-Factory-sop">
                                <div class="panel panel-default panel-faq">
                                  <div class="panel-heading">
                                    <h4 class="panel-title"> <a data-toggle="collapse" data-parent="#Pre-Operation-Factory-sop" href="#sop-pre-op-factory1">Registration and Grant of Factory licence <span class="glyphicon pull-right glyphicon-minus"></span></a> </h4>
                                  </div>
                                  <div id="sop-pre-op-factory1" class="panel-collapse collapse in">
                                    <div class="panel-body">
                                      <p> a) Persons authorised by the designated officer (as approved by the controlling officer) shall receive the application and issue acknowledgement in Form No.1 prescribed under The West Bengal Right to Public Services act. 2013 & rules framed thereunder, subject to receipt of the enclosures as per annexed checklist.</p>
                                      <p>b) The designated officer as well as officers higher in rank as per existing office procedure shall verify the application and other documents and visit the site as per requirement.</p>
                                      <p>c) Information regarding recommendation or rectification or rejection of the application (with reasons stated thereof), as applicable during the entire process of verification of application will be intimated to the applicant within the stipulated period of service.</p>
                                      <p>d) Information regarding rectification shall be informed to the applicant by way of "Letter for rectification" which is to be complied by the applicant within 7 days of the issue of the same, so as to provide the aforesaid service within the stipulated period, failing which the application will be liable for rejection.</p>
                                      <p>e) The rejection under this Act (i.e. West Bengal Right to Public Services Act, 2013) shall not entail the applicant to claim any aberration from the provisions of the Factories Act, 1948 and Rules framed thereunder.</p>
                                      <p>f) Once the application is rejected, the applicant will he required to submit a fresh application forthwith in compliance of the provisions of the Factories Act. 1948 and Rules framed there under alongwith the details of fees deposited in the earlier applications together with supporting documents.</p>
                                      <p>g) Registration and licence is to be collected from the Head office of the designated officer by the applicant or by his authorised representative.</p>
                                    </div>
                                  </div>
                                </div>
                              </div>
                            </div>
                            <div class="tab-pane fade in" id="Pre-Operation-Shop">
                              <h2>Coming Soon</h2>
                            </div>
                          </div>
                        </div>
                      </div>
                      <div class="tab-pane" id="Pre-Establishment">
                        <div class="tabbable-panel InTopTab">
                          <div class="tabbable-line">
                            <ul class="nav nav-tabs tabtop  tabsetting">
                              <li class="active"> <a href="#Pre-Establishment-Boilers" data-toggle="tab">Directorate of Boilers</a> </li>
                              <li> <a href="#Pre-Establishment-Commissionerate" data-toggle="tab">Labour Commissionerate</a> </li>
                              <li> <a href="#Pre-Establishment-Factory" data-toggle="tab">Directorate of Factories</a> </li>
                              <li> <a href="#Pre-Establishment-Shop" data-toggle="tab">Shops and Establishment</a> </li>
                            </ul>
                          </div>
                          <div class="tab-content InTTab_content">
                            <div class="tab-pane active fade in" id="Pre-Establishment-Boilers">
                              <h2>Not Applicable</h2>
                            </div>
                            <div class="tab-pane fade" id="Pre-Establishment-Commissionerate">
                              <h2>Not Applicable</h2>
                            </div>
                            <div class="tab-panel fade" id="Pre-Establishment-Factory">
                             <div class="panel-group Custom_AC_tab" id="Pre-Establishment-Factory-sop">
                              <div class="panel panel-default panel-faq">
                                <div class="panel-heading">
                                  <h4 class="panel-title"> <a data-toggle="collapse" data-parent="#Pre-Establishment-Factory-sop" href="#sop-pre-est-factory1">Approval of Factory Plan <span class="glyphicon pull-right glyphicon-minus"></span></a> </h4>
                                </div>
                                <div id="sop-pre-est-factory1" class="panel-collapse collapse in">
                                  <div class="panel-body">
                                    <p> a) Persons authorised by the designated officer (as approved by the controlling officer) shall receive the application and issue acknowledgement in Form No.1 prescribed under The West Bengal Right to Public Services act. 2013 & rules framed thereunder, subject to receipt of the enclosures as per annexed checklist..</p>
                                    <p>b)The designated officer as well as officers higher in rank as per existing office procedure shall scrutinize the plan and other documents and visit the site as per requirement.</p>
                                    <p>c) Information regarding recommendation or rectification or rejection of a plan (with reasons stated thereof), as applicable during the entire process of plan scrutiny will be intimated to the applicant within the stipulated period of service.</p>
                                    <p>d) Information regarding rectification shall be informed to the applicant by way of "Letter for rectification" which is to be complied by the applicant within 7 days of the issue of the same, so as to provide the aforesaid service within the stipulated period, failing which the application will be liable for rejection.</p>
                                    <p>e) The rejection under this Act (i.e. West Bengal Right to Public Services Act, 2013) shall not entail the applicant to claim any aberration from the provisions of the Factories Act, 1948 and Rules framed thereunder.</p>
                                    <p>f) Once the application is rejected, the applicant will be required to submit a fresh application forthwith in compliance of the provisions of the Factories Act. 1948 and Rules framed thereunder.</p>
                                    <p>g) Approved plan is to he collected from the Head office of the designated officer by the applicant or by his authorised representative.</p>
                                  </div>
                                </div>
                              </div>
                              </div>
                            </div>
                            <div class="tab-pane fade" id="Pre-Establishment-Shop">
                              <h2>Coming Soon</h2>
                            </div>
                          </div>
                        </div>
                      </div>
                      <div class="tab-pane" id="Post-Operation">
                        <div class="tabbable-panel InTopTab">
                          <div class="tabbable-line">
                            <ul class="nav nav-tabs tabtop  tabsetting">
                              <li class="active"> <a href="#Post-Operation-Boilers" data-toggle="tab">Directorate of Boilers</a> </li>
                              <li> <a href="#Post-Operation-Commissionerate" data-toggle="tab">Labour Commissionerate</a> </li>
                              <li> <a href="#Post-Operation-Factory" data-toggle="tab">Directorate of Factories</a> </li>
                              <li> <a href="#Post-Operation-Shop" data-toggle="tab">Shops and Establishment</a> </li>
                            </ul>
                          </div>
                          <div class="tab-content InTTab_content">
                            <div class="tab-pane active fade in" id="Post-Operation-Boilers">
                              <div class="panel-group Custom_AC_tab" role="tablist" aria-multiselectable="true">
                                <h2>Not Applicable</h2>
                              </div>
                            </div>
                            <div class="tab-pane fade in" id="Post-Operation-Commissionerate">
                              <div class="panel-group Custom_AC_tab" id="other-Commissionerate-sop">
                                <div class="panel panel-default panel-faq">
                                  <div class="panel-heading">
                                    <h4 class="panel-title"><a data-toggle="collapse" data-parent="#other-Commissionerate-sop" href="#sectionpoc" class="collapsed"> 
                                    Registration of establishment of Principal Employer and amendment thereof under Contract Labour (Regulation and Abolition) Act, 1970 
                                    <span class="glyphicon glyphicon-minus pull-right"></span></a> </h4>
                                  </div>
                                  <div id="sectionpoc" class="panel-collapse collapse in">
                                    <div class="panel-body">
                                      <div class="timeline">
                                        <table border="1" cellpadding="0" cellspacing="0" class="table" style="width:100%">
                                          <thead>
                                            <tr>
                                              <th rowspan="2">Step</th>
                                              <th rowspan="2">Activity</th>
                                              <th rowspan="2">Responsibility</th>
                                              <th rowspan="2">Documents Involved</th>
                                            </tr>
                                            <!--  <tr>
                                                <th>Designation</th>
                                                <th>Stipulated Time Limit</th>
                                                <th>Designation</th>
                                                <th>Stipulated Time Limit</th>
                                              </tr>-->
                                          </thead>
                                          <tbody>
                                            <tr>
                                              <td>1.</td>
                                              <td><strong>FOR  NEW REGISTRATION</strong></br>
                                                1.	The applicant shall open ‘www.wblc.gov.in’.</br>
                                                2.	 Click on e-services from menu bar or from icon.</br>
                                                3.	Page containing list of e-services will open. </br>
                                                4.	Click on ‘Apply’ button adjacent to Registration of Principal Employer under CL(R&A) Act1970. </br>
                                                5.	A guide line will appear agreeing to which he/she will land up in the log in page. </br>
                                                6.	For a new user he/she fills up a Common Application Form (CAF) in the Portal of ‘www.wblc.gov.in’, which includes mainly 	
                                                applicant’s Name, Address, Contact Details, e- mail, PAN, Voters ID, Aadhaar number, Driving License , Trade License Number, 
                                                any other unique number tagged with that establishment, establishment name and details including address, etc. along with 	
                                                Preferred User name & Password and creates a User Credential. </br>
                                                7.	If the applicant is an already registered user and has User Credential following step-6, he/she will log in using the 
                                                credentials. </br></td>
                                              <td>Principal Employer</td>
                                            </tr>
                                            <tr>
                                              <td>2.</td>
                                              <td>Logs into the System with the Valid Credentials and Captcha.</td>
                                              <td>Principal Employer</td>
                                            </tr>
                                            <tr>
                                              <td>3.</td>
                                              <td>Lands up into the Dashboard.</td>
                                              <td>Principal Employer</td>
                                            </tr>
                                            <tr>
                                              <td>4.</td>
                                              <td>Selects New Registration from menu and applies for online Registration of Principal Employer under the Contract Labour (Regulation and Abolition) Act, 1970 by filling up Application Details in the Form and uploads self-certified copies of required documents in PDF format.</td>
                                              <td>Principal Employer</td>
                                              <td>a)	Valid Trade License.</br>
                                                b)	Articles of Association and Memorandum of Association / Partnership Deed.</br>
                                                c)	Factory License if any.</br>
                                                d)	Other certificates of registration in case of other than company, proprietorship or partnership firm like Cooperative,
                                                Trustees etc.</br>
                                                e)   Any other document in support of correctness of the particulars mentioned in the application if required.</br></td>
                                            </tr>
                                            <tr>
                                              <td>5.</td>
                                              <td>1. Fills up Trade Union Details in Relation to Establishment.</br>
                                                2. Fills up valid Contractor Information into the system or Imports the list from pre filled Excel Sheet in the format available in 													    the system.</br></td>
                                              <td>Principal Employer</td>
                                              <td></td>
                                            </tr>
                                            <tr>
                                              <td>6.</td>
                                              <td>Views the Filled in Information in the Application Preview section before Final Submission or in case of correction rolls back to 	
                                                earlier sections and makes corrections and Saves the application.</td>
                                              <td>Principal Employer</td>
                                              <td></td>
                                            </tr>
                                            <tr>
                                              <td>7.</td>
                                              <td> Final Submission of the application.</td>
                                              <td>Principal Employer</td>
                                              <td></td>
                                            </tr>
                                            <tr>
                                              <td>8.</td>
                                              <td>Logs into the system with User Credentials.</td>
                                              <td>Inspector concerned</td>
                                              <td></td>
                                            </tr>
                                          </tbody>
                                        </table>
                                      </div>
                                    </div>
                                  </div>
                                </div>
                                <div class="panel panel-default panel-faq">
                                  <div class="panel-heading">
                                    <h4 class="panel-title"><a data-toggle="collapse" data-parent="#other-Commissionerate-sop" href="#sectionpoc1" class="collapsed"> Licensing of contractors under Contract Labour (Regulation and Abolition) Act, 1970 <span class="glyphicon glyphicon-plus pull-right"></span></a> </h4>
                                  </div>
                                  <div id="sectionpoc1" class="panel-collapse collapse">
                                    <div class="panel-body">
                                      <div class="timeline">
                                        <table border="1" cellpadding="0" cellspacing="0" class="table" style="width:100%">
                                          <thead>
                                            <tr>
                                              <th rowspan="2">Step</th>
                                              <th rowspan="2">Activity</th>
                                              <th rowspan="2">Responsibility</th>
                                              <th rowspan="2">Documents Involved</th>
                                            </tr>
                                            <!--  <tr>
                                                <th>Designation</th>
                                                <th>Stipulated Time Limit</th>
                                                <th>Designation</th>
                                                <th>Stipulated Time Limit</th>
                                              </tr>-->
                                          </thead>
                                          <tbody>
                                            <tr>
                                              <td>1.</td>
                                              <td> 1.	The applicant shall open ‘www.wblc.gov.in’.</br>
                                                2.	Click on e-services from menu bar or from icon.</br>
                                                3.	Page containing list of e-services will open. </br>
                                                4.	Click on ‘Apply’ button adjacent to Registration of Principal Employer under CL(R&A) Act1970. </br>
                                                5.	A guide line will appear agreeing to which he/she will land up in the log in page. </br>
                                                6.	For a new user he/she fills up a Common Application Form(CAF) in the Portal of ‘www.wblc.gov.in’, which includes mainly 		
                                                applicant’s Name, Address, Contact Details, e- mail, PAN, Voters ID, Aadhaar number, Driving License , Trade License Number, 
                                                any other unique number tagged with that establishment, establishment name and details including address, etc. along with 
                                                Preferred User name & Password and creates a User Credential. </br>
                                                7.	If the applicant is an already registered user and has User Credential following step-6, he/she will log in using the 
                                                credentials. </br></td>
                                              <td>Contractor</td>
                                              <td></td>
                                            </tr>
                                            <tr>
                                              <td>2.</td>
                                              <td>Logs into the System with the Valid Credentials and Captcha.</td>
                                              <td>Contractor</td>
                                              <td></td>
                                            </tr>
                                            <tr>
                                              <td>3.</td>
                                              <td>Lands up into the Dashboard.</td>
                                              <td>Contractor</td>
                                              <td></td>
                                            </tr>
                                            <tr>
                                              <td>4.</td>
                                              <td>If the contractor is yet to be provided with the system generated unique Form-V number by the Principal Employer as mentioned in 
                                                item 25 of the process for registration of establishment, the Principal Employer may Log into the system with the Credentials.</td>
                                              <td>Principal Employer</td>
                                              <td></td>
                                            </tr>
                                            <tr>
                                              <td>5.</td>
                                              <td>Views the Form-V, digitally signs or can sign manually in the hard copy and send via e mail or through SMS the Unique number of 
                                                Form V to Contractors for applying for License..</br></td>
                                              <td>Principal Employer </td>
                                              <td></td>
                                            </tr>
                                            <tr>
                                              <td>6.</td>
                                              <td>1.After getting the system generated number of Form-V from the Principal Employer, enters the system generated Unique 
                                                Form-V number issued by Principal Employer.</br>
                                                2. The Contractor will be able to view some relevant fields in the Application page which are auto-populated and non-editable based 													   on the information given by the Principal Employer about the Contractor at the time of filling up application for Registration 
                                                of Establishment under CL(R&A) Act, 1970. </br></td>
                                              <td>Contractor</td>
                                              <td> Valid Form V </td>
                                            </tr>
                                            <tr>
                                              <td>7.</td>
                                              <td> 1. Fills up the Additional Information as required in the Application Proforma. </br>
                                                2. Uploads self-certified copies of required documents in PDF format.</br></td>
                                              <td>Contractor</td>
                                              <td> a) Valid Form V.</br>
                                                b) Valid Work  Order. </br>
                                                c) Trade license.</br>
                                                d) Any other documents in support of correctness of particulars furnished in application form.</br></td>
                                            </tr>
                                            <tr>
                                              <td>8.</td>
                                              <td>Views the Filled in Information in the Application Preview section before Final Submission or in case of correction rolls back to 
                                                earlier sections and makes corrections and Saves the application.</td>
                                              <td>Contractor</td>
                                              <td></td>
                                            </tr>
                                            <tr>
                                              <td>9.</td>
                                              <td>Final Submission of the application.</td>
                                              <td>Contractor</td>
                                              <td></td>
                                            </tr>
                                            <tr>
                                              <td>10.</td>
                                              <td>Logs into the system with Credentials.</td>
                                              <td>Inspector concerned</td>
                                              <td></td>
                                            </tr>
                                            <tr>
                                              <td>11.</td>
                                              <td>Lands up in the Dashboard and selects the Application List from the Left hand Panel.</td>
                                              <td>Inspector concerned</td>
                                              <td></td>
                                            </tr>
                                            <tr>
                                              <td>12.</td>
                                              <td>He/she views list of Applications that has been submitted by the Applicants.</td>
                                              <td>Inspector concerned</td>
                                              <td></td>
                                            </tr>
                                            <tr>
                                              <td>13.</td>
                                              <td>He opens the application and verifies details one by one and marks Tick (√) which he finds correct and leaves the one as not 	
                                                verified which he finds Incorrect.</td>
                                              <td>Inspector concerned</td>
                                              <td></td>
                                            </tr>
                                            <tr>
                                              <td>14.</td>
                                              <td>1.	He/she may send the application back to applicant for necessary Correction or Rectification with remarks in case any correction 														or rectification is required.
                                                OR</br>
                                                2. He/she can forward it to the Registering Authority for approval or rejection or further correction.</br></td>
                                              <td>Inspector concerned</td>
                                              <td></td>
                                            </tr>
                                            <tr>
                                              <td>15.</td>
                                              <td>Logs into the system with the Credentials.</td>
                                              <td>Contractor</td>
                                              <td></td>
                                            </tr>
                                            <tr>
                                              <td>16.</td>
                                              <td>Views on the Dashboard the status of application, sent back by the Inspector, marked for correction and resubmits the application 
                                                after making corrections along with uploading of documents, if any.</td>
                                              <td>Contractor </td>
                                              <td>Documents as required :- </br>
                                                a) Valid Work Order </br>
                                                b) Any other documents in support of correctness of particulars furnished in application form</br>
                                                c) Valid Form V </br>
                                                d) Trade license </br></td>
                                            </tr>
                                            <tr>
                                              <td>17.</td>
                                              <td>Logs into the system with Credentials.</td>
                                              <td>Inspector concerned</td>
                                              <td></td>
                                            </tr>
                                            <tr>
                                              <td>18.</td>
                                              <td>Verifies or re-verifies the application as the case may be and if found satisfactory forwards the same to the
                                                Licensing Authority.</td>
                                              <td>Inspector concerned</td>
                                              <td></td>
                                            </tr>
                                            <tr>
                                              <td>19.</td>
                                              <td>Logs into the system with the Credentials.</td>
                                              <td>ALC of the Subdivision as Licensing Authority</td>
                                              <td></td>
                                            </tr>
                                            <tr>
                                              <td>20.</td>
                                              <td>1. Lands up in the Dashboard. </br>
                                                2. Views the list of applications forwarded by Inspectors. </br>
                                                3. Clicks on Application and verifies details along with the documents uploaded one by one and marks Tick (√) which he/she finds 
                                                correct and leaves the ones as not verified which he finds Incorrect. </br>
                                                4. If the application is found satisfactory, then, he/she Approves the Application and Allows for Payment of Fees to be paid by the 													    applicant.
                                                OR </br>
                                                5. In case the Licensing Authority finds something that is not satisfactory in the application he/she may send it back either to 	
                                                the applicant or to the Inspector as he deems fit.
                                                OR </br>
                                                6. Licensing Authority can also reject the application after observing principles of natural justice. </td>
                                              <td>ALC of the Subdivision as Licensing Authority </td>
                                              <td></td>
                                            </tr>
                                            <tr>
                                              <td>21.</td>
                                              <td>Logs into the system with the Credentials.</td>
                                              <td>Contractor </td>
                                              <td></td>
                                            </tr>
                                            <tr>
                                              <td>22.</td>
                                              <td><strong>1. When the Application is Approved by Licensing Authority:-</strong></br>
                                                (i)Views on the Dashboard the status of application marked for PAYMENT (PAY NOW) by the Licensing Authority and makes payment 
                                                Online through GRIPS or offline through counter payment after generating challans from GRIPS portal.</br>
                                                (ii) After successful payment of fees the applicant will receive a system generated statutory acknowledgement.</br>
                                                (iii)The applicant signs system generated Form IV digitally using DSC and uploads it or signs manually and uploads scanned copy of 
                                                it in to the system. In case the applicant cannot sign the application digitally through DSC, he is required to submit the 
                                                signed hard copy of the application form before the Licensing Authority.
                                                (The applicant can get the system generated filled up application printed if he so desires.)</br>
                                                OR</br>
                                                <strong>2.If the Application is sent back by the Registering Authority:-</strong></br>
                                                Views on the Dashboard the status of application, sent back by the Licensing Authority, marked for correction and resubmits the 
                                                application after making corrections along with uploading of documents, if any. </td>
                                              <td>Contractor </td>
                                              <td> a)	FORM IV</br>
                                                b)	Proof of submission of fees and security deposit </br></td>
                                            </tr>
                                            <tr>
                                              <td>23.</td>
                                              <td>Logs into the system with the Credentials.</td>
                                              <td>ALC of the Subdivision as Licensing Authority</td>
                                              <td></td>
                                            </tr>
                                            <tr>
                                              <td>24.</td>
                                              <td>1. Views signed copy of Form-IV uploaded by the Contractor.</br>
                                                2. Satisfies himself/herself about the status of Fees and security deposit paid by the Contractor as Success.</br>
                                                3. Licensing Authority issues system generated FORM-VI (Certificate of License) 
                                                signed digitally using DSC and Uploads in to the system.</br></td>
                                              <td>ALC of the Subdivision as Licensing Authority</td>
                                              <td>FORM-VI(Certificate of License)</td>
                                            </tr>
                                            <tr>
                                              <td>25.</td>
                                              <td>Logs into the system with the Credentials & downloads the Digitally signed License Certificate.</td>
                                              <td>Contractor</td>
                                              <td></td>
                                            </tr>
                                            <tr>
                                              <td>26.</td>
                                              <td>Track Status of Application through SMS Alerts generated through the System starting from Creating Login Credentials, Submission of 													Application, Correction Required, Payment of Fees, Status of Approval or Rejection, Status on issue of License.</td>
                                              <td>Contractor</td>
                                              <td></td>
                                            </tr>
                                          </tbody>
                                        </table>
                                      </div>
                                    </div>
                                  </div>
                                </div>
                                <div class="panel panel-default panel-faq">
                                  <div class="panel-heading">
                                    <h4 class="panel-title"><a data-toggle="collapse" data-parent="#other-Commissionerate-sop" href="#sectionpoc2" class="collapsed"> Renewal of licences of contractors thereof under Contract Labour (Regulation and Abolition) Act, 1970 <span class="glyphicon glyphicon-plus pull-right"></span></a> </h4>
                                  </div>
                                  <div id="sectionpoc2" class="panel-collapse collapse" aria-expanded="true">
                                    <div class="panel-body">
                                      <div class="timeline">
                                        <table border="1" cellpadding="0" cellspacing="0" class="table" style="width:100%">
                                          <thead>
                                            <tr>
                                              <th rowspan="2">Step</th>
                                              <th rowspan="2">Activity</th>
                                              <th rowspan="2">Responsibility</th>
                                              <th rowspan="2">Documents Involved</th>
                                            </tr>
                                            <!--  <tr>
                                                <th>Designation</th>
                                                <th>Stipulated Time Limit</th>
                                                <th>Designation</th>
                                                <th>Stipulated Time Limit</th>
                                              </tr>-->
                                          </thead>
                                          <tbody>
                                            <tr>
                                              <td>1.</td>
                                              <td> 1.	The applicant shall open ‘www.wblc.gov.in’.</br>
                                                2.	Click on e-services from menu bar or from icon.</br>
                                                3.	Page containing list of e-services will open. </br>
                                                4.	Click on ‘Apply’ button adjacent to Registration of Principal Employer under CL(R&A) Act1970. </br>
                                                5.	A guide line will appear agreeing to which he/she will land up in the log in page. </br>
                                                6.	For a new user he/she fills up a Common Application Form(CAF) in the Portal of ‘www.wblc.gov.in’, which includes mainly 		
                                                applicant’s Name, Address, Contact Details, e- mail, PAN, Voters ID, Aadhaar number, Driving License , Trade License Number, 
                                                any other unique number tagged with that establishment, establishment name and details including address, etc. along with 
                                                Preferred User name & Password and creates a User Credential. </br>
                                                7.	If the applicant is an already registered user and has User Credential following step-6, he/she will log in using the 
                                                credentials. </br></td>
                                              <td>Contractor</td>
                                              <td></td>
                                            </tr>
                                            <tr>
                                              <td>2.</td>
                                              <td>Logs into the System with the Valid Credentials and Captcha.</td>
                                              <td>Contractor</td>
                                              <td></td>
                                            </tr>
                                            <tr>
                                              <td>3.</td>
                                              <td>Lands up into the Dashboard.</td>
                                              <td>Contractor</td>
                                              <td></td>
                                            </tr>
                                            <tr>
                                              <td>4.</td>
                                              <td><strong> For Contractor Already having License Offline:-</strong></br>
                                                1.a)The Contractor already having license from the Licensing Authority through manual process (Offline), is required to click on 	
                                                the ‘Apply for Renewal for License’ link. </br>
                                                b) A new page will open wherein the contractor is required to provide Reference No. obtained from the Principal Employer and 
                                                Offline License No. issued manually by the Licensing Authority and Click on the Submit button.</br>
                                                c) The contractor will be taken to a new page wherein the contractor will be able to view some relevant fields in the Application 
                                                page containing Primary Information, Particulars of Contract Labour some of the fields of which are auto-populated and 
                                                non-editable based on the information given by the Principal Employer about the Contractor at the time of filling up application 														for Registration of Establishment under CL(R&A) Act, 1970. </br>
                                                d) The Contractor provides additional information as required under the Tabs viz;-Primary Information, Particulars of Contract 
                                                Labour and then uploads self-certified copies of required documents in PDF format.</br>
                                                e) Views the Filled in Information in the Application Preview section before Final Submission or in case of correction rolls back 
                                                to earlier sections and makes corrections and Saves the application.</br>
                                                <strong> For Contractor having License Online :-</strong></br>
                                                2. a)The contractor may click on List of Renewal of License and can apply for Renewal within the specified period when the Renewal 
                                                button is automatically ACTIVE within a stipulated time limit.</br>
                                                b) The Contractor will fill up additional information and uploads self-certified copies of required documents in PDF format.</br>
                                                c) Views the Filled in Information in the Application Preview section before Final Submission or in case of correction rolls back 
                                                to earlier sections and makes corrections and Saves the application.</br></td>
                                              Contractor
                                              <td></td>
                                              <td>a) Earlier Copy of License Certificate</br>
                                                b) Work order</br>
                                                c) Order from the Principal Employer for extension of time of work</br></td>
                                            </tr>
                                            <tr>
                                              <td>5.</td>
                                              <td>Final Submission of the application. </td>
                                              <td>Contractor </td>
                                              <td></td>
                                            </tr>
                                            <tr>
                                              <td>6.</td>
                                              <td>Logs into the system with Credentials.</td>
                                              <td>Inspector concerned</td>
                                              <td></td>
                                            </tr>
                                            <tr>
                                              <td>7.</td>
                                              <td>Lands up in the Dashboard and selects the Application List from the Left hand Panel.</td>
                                              <td>Inspector concerned </td>
                                              <td></td>
                                            </tr>
                                            <tr>
                                              <td>8.</td>
                                              <td>He views all the Applications that has been submitted by the Applicants along with Uploaded PDF Files.</td>
                                              <td>Inspector concerned </td>
                                              <td></td>
                                            </tr>
                                            <tr>
                                              <td>9.</td>
                                              <td>He/she opens the application and verifies details one by one and marks Tick (√) which he finds correct and leaves the ones as not 
                                                verified which he finds Incorrect.</td>
                                              <td>Inspector concerned </td>
                                              <td></td>
                                            </tr>
                                            <tr>
                                              <td>10.</td>
                                              <td>1. He/she may send the application back to applicant for necessary Correction or Rectification with remarks in case any correction 														or rectification is required.
                                                OR</br>
                                                2. He/she can forward it to the Licensing Authority for approval or rejection or further correction. </td>
                                              <td>Inspector concerned</td>
                                              <td></td>
                                            </tr>
                                            <tr>
                                              <td>11.</td>
                                              <td>Logs into the system with the Credentials.</td>
                                              <td>Contractor</td>
                                              <td></td>
                                            </tr>
                                            <tr>
                                              <td>12.</td>
                                              <td>Views on the Dashboard the status of application marked for correction by Inspector if any and resubmits the application after 
                                                making corrections along with uploading of documents, if any.</td>
                                              <td>Contractor</td>
                                              <td> a) Earlier Copy of License Certificate</br>
                                                b) Work order </br>
                                                c) Order from the Principal Employer for extension of time of work </br>
                                                d) Any or more from the above mentioned documents </br></td>
                                            </tr>
                                            <tr>
                                              <td>13.</td>
                                              <td>Logs into the system with Credentials.</td>
                                              <td>Inspector concerned</td>
                                              <td></td>
                                            </tr>
                                            <tr>
                                              <td>14.</td>
                                              <td>Verifies or re-verifies the application as the case may be and if found satisfactory forwards the same to the Licensing Authority. </td>
                                              <td>Inspector concerned</td>
                                              <td></td>
                                            </tr>
                                            <tr>
                                              <td>15.</td>
                                              <td>Logs into the system with the Credentials.</td>
                                              <td>ALC of the Subdivision as Licensing Authority</td>
                                              <td></td>
                                            </tr>
                                            <tr>
                                              <td>16.</td>
                                              <td>1 .Lands up in the Dashboard.</br>
                                                2. Views the list of applications forwarded by Inspectors.</br>
                                                3. Clicks on Application and verifies details along with the documents uploaded one by one and marks Tick (√) which he/she finds 
                                                correct and leaves the ones as not verified which he finds Incorrect.</br>
                                                4. If the application is found satisfactory, then, he/she Approves the Application and Allows for Payment of Fees to be paid by the 														applicant.
                                                OR </br>
                                                5. In case the Licensing Authority finds something that is not satisfactory in the application he/she may send it back either to 
                                                the applicant or to the Inspector as he deems fit.
                                                OR</br>
                                                6. Licensing Authority can also reject the application after observing principles of natural justice.</br></td>
                                              <td>ALC of the Subdivision as Licensing Authority </td>
                                              <td></td>
                                            </tr>
                                            <tr>
                                              <td>17.</td>
                                              <td>Logs into the system with Credentials.</td>
                                              <td>Contractor</td>
                                              <td></td>
                                            </tr>
                                            <tr>
                                              <td>18.</td>
                                              <td><strong>1. When the Application is Approved by Licensing Authority:-</strong> (i)Views on the Dashboard the status of application marked for PAYMENT (PAY NOW) by the Licensing Authority and makes payment Online 	
                                                through GRIPS or offline through counter payment after generating challans from GRIPS portal.</br>
                                                (ii) After successful payment of fees the applicant will receive a system generated statutory acknowledgement.</br>
                                                (iii)The applicant signs system generated Form VII digitally using DSC and uploads it or signs manually and uploads scanned copy of it 
                                                in to the system. In case the applicant cannot sign the application digitally through DSC, he is required to submit the signed 
                                                hard copy of the application form before the Licensing Authority.
                                                (The applicant can get the system generated filled up application printed if he so desires.)
                                                OR</br>
                                                <strong>2.If the Application is sent back by the Licensing Authority:-</strong></br>
                                                Views on the Dashboard the status of application, sent back by the Licensing Authority, marked for correction and resubmits the 
                                                application after making corrections alongwith uploading of documents, if any.</br></td>
                                              <td>Contractor</td>
                                              <td> a)	FORM VII</br>
                                                b) Proof of submission of fees </br></td>
                                            </tr>
                                            <tr>
                                              <td>19.</td>
                                              <td>Logs into the system with the Credentials.</td>
                                              <td>ALC of the Subdivision as Licensing Authority</td>
                                              <td></td>
                                            </tr>
                                            <tr>
                                              <td>20.</td>
                                              <td>1.Views signed copy of Form-VII uploaded by the Contractor.</br>
                                                2. Satisfies himself/herself about the status of Fees and security deposit paid by the Contractor as Success.</br>
                                                3. Licensing Authority issues system generated FORM-VI (Certificate of Renewal of License) signed digitally using DSC and Uploads 													   														in to  the system.</br></td>
                                              <td>ALC of the Subdivision as Licensing Authority </td>
                                              <td>FORM-VI(Certificate of Renewal of License)</td>
                                            </tr>
                                            <tr>
                                              <td>21.</td>
                                              <td>Logs into the system with the Credentials & downloads the Digitally signed License Renewal Certificate.</td>
                                              <td>Contractor </td>
                                              <td></td>
                                            </tr>
                                            <tr>
                                              <td>22.</td>
                                              <td>Track Status of Application through SMS Alerts generated through the System starting from Creating Login Credentials, Submission of				
                                                Application, Correction Required, Payment of Fees, Status of Approval or Rejection, Status on issue of License Renewal Certificate. </td>
                                              <td>Contractor </td>
                                              <td></td>
                                            </tr>
                                            <tr>
                                              <td>23.</td>
                                              <td>If the application is reverted back to the Inspector by the ALC, he will view the application along with remarks, if any, from the 
                                                ALC, after logging into the system with credentials. He can either sent back the application to the applicant or forward the same 		
                                                to the ALC with remarks if any. </td>
                                              <td>Inspector Concerned </td>
                                              <td></td>
                                            </tr>
                                          </tbody>
                                        </table>
                                      </div>
                                    </div>
                                  </div>
                                </div>
                                <div class="panel panel-default panel-faq">
                                  <div class="panel-heading">
                                    <h4 class="panel-title"><a data-toggle="collapse" data-parent="#other-Commissionerate-sop" href="#sectionpoc3" class="collapsed"> Registration of establishment by Principal Employer under The Interstate Migrant Workmen Act 1979. <span class="glyphicon glyphicon-plus pull-right"></span></a> </h4>
                                  </div>
                                  <div id="sectionpoc3" class="panel-collapse collapse">
                                    <div class="panel-body">
                                      <div class="timeline">
                                        <table border="1" cellpadding="0" cellspacing="0" class="table" style="width:100%">
                                          <thead>
                                            <tr>
                                              <th rowspan="2">Step</th>
                                              <th rowspan="2">Activity</th>
                                              <th rowspan="2">Responsibility</th>
                                              <th rowspan="2">Documents Involved</th>
                                            </tr>
                                            <!--  <tr>
                                                <th>Designation</th>
                                                <th>Stipulated Time Limit</th>
                                                <th>Designation</th>
                                                <th>Stipulated Time Limit</th>
                                              </tr>-->
                                          </thead>
                                          <tbody>
                                            <tr>
                                              <td>1.</td>
                                              <td><strong>FOR NEW REGISTRATION</strong> 1.	The applicant shall open <strong>'www.wblc.gov.in'</strong>. </br>
                                                2.	Click on e-services from menu bar or from icon.</br>
                                                3.	Page containing list of e-services will open.</br>
                                                4.	Click on ‘Apply’ button adjacent to Registration of Principal Employer under ISMW(RE&CS) Act1979. </br>
                                                5.	A guide line will appear agreeing to which he/she will land up in the log in page. </br>
                                                6.	For a new user he/she fills up a Common Application Form(CAF) in the Portal of ‘www.wblc.gov.in’, which includes mainly 
                                                applicant’s Name, Address, Contact Details, e- mail, PAN, Voters ID, Aadhaar number, Driving License , Trade License Number, 
                                                any other unique number tagged with that establishment, establishment name and details including address, etc. alongwith 
                                                Preferred User name & Password and creates a User Credential. </br>
                                                7.	If the applicant is an already registered user and has User Credential following step-6, he/she will log in using the 
                                                credentials. </br></td>
                                              <td>Principal Employer</td>
                                              <td></td>
                                            </tr>
                                            <tr>
                                              <td>2.</td>
                                              <td>Logs into the System with the Valid Credentials and Captcha.</td>
                                              <td>Principal Employer</td>
                                              <td></td>
                                            </tr>
                                            <tr>
                                              <td>3.</td>
                                              <td>Lands up into the Dashboard.</td>
                                              <td>Principal Employer</td>
                                              <td></td>
                                            </tr>
                                            <tr>
                                              <td>4.</td>
                                              <td>Selects <strong>New Registration</strong> from menu and applies for online Registration of Principal Employer under the Interstate 	
                                                Migrant Workmen (RE&CS) Act, 1979 by filling up <strong>Application For Registration of Establishment Employing Migrant 
                                                Workmen</strong> and uploads self-certified copies of required documents in PDF format. </td>
                                              <td> Principal Employer </td>
                                              <td>a) Valid Trade License</br>
                                                b) Articles of Association and Memorandum of Association / Partnership Deed</br>
                                                c) Factory License if any</br>
                                                d) Other certificates of registration in case of other than company, proprietorship or partnership firm like Cooperative, 
                                                Trustees etc</br>
                                                e) Any other document in support of correctness of the particulars mentioned in the application if required</br></td>
                                            </tr>
                                            <tr>
                                              <td>5.</td>
                                              <td>Fills up valid Particulars of Contractor & Migrant Workmen into the system or Imports the list from pre filled Excel Sheet in the 
                                                format available in the system.</td>
                                              <td>Principal Employer</td>
                                              <td></td>
                                            </tr>
                                            <tr>
                                              <td>6.</td>
                                              <td>Views the Filled in Information in the Application Preview section before Final Submission or in case of correction rolls back to 	
                                                earlier sections and makes corrections and Saves the application.</td>
                                              <td>Principal Employer</td>
                                              <td></td>
                                            </tr>
                                            <tr>
                                              <td>7.</td>
                                              <td>Final Submission of the application.</td>
                                              <td>Principal Employer</td>
                                              <td></td>
                                            </tr>
                                          </tbody>
                                        </table>
                                      </div>
                                    </div>
                                  </div>
                                </div>
                                <div class="panel panel-default panel-faq">
                                  <div class="panel-heading">
                                    <h4 class="panel-title"><a data-toggle="collapse" data-parent="#other-Commissionerate-sop" href="#sectionpoc4" class="collapsed">
                                     Registration of Establishment under Building and Other Construction Workers (Regulation of Employment and Conditions of Service) Act, 1996 
                                     <span class="glyphicon glyphicon-plus pull-right"></span>
                                    </a> </h4>
                                  </div>
                                  <div id="sectionpoc4" class="panel-collapse collapse" aria-expanded="true">
                                    <div class="panel-body">
                                      <div class="timeline">
                                        <table border="1" cellpadding="0" cellspacing="0" class="table" style="width:100%">
                                          <thead>
                                            <tr>
                                              <th rowspan="2">Step</th>
                                              <th rowspan="2">Activity</th>
                                              <th rowspan="2">Responsibility</th>
                                              <th rowspan="2">Documents Involved</th>
                                            </tr>
                                            <!--  <tr>
                                                <th>Designation</th>
                                                <th>Stipulated Time Limit</th>
                                                <th>Designation</th>
                                                <th>Stipulated Time Limit</th>
                                              </tr>-->
                                          </thead>
                                          <tbody>
                                            <tr>
                                              <td>1.</td>
                                              <td><strong>FOR NEW REGISTRATION</strong> 1.	The applicant shall open <strong>'www.wblc.gov.in'</strong>. </br>
                                                2.	 Click on e-services from menu bar or from icon. </br>
                                                3.	Page containing list of e-services will open. </br>
                                                4.	Click on ‘Apply’ button adjacent to Registration of Establishment under BOCWA (RE&CS) Act 1996. </br>
                                                5.	A guide line will appear agreeing to which he/she will land up in the log in page. </br></td>
                                              <td>Employer</td>
                                              <td></td>
                                            </tr>
                                            <tr>
                                              <td>2.</td>
                                              <td>Logs into the System with the Valid Credentials and Captcha.</td>
                                              <td>Employer</td>
                                              <td></td>
                                            </tr>
                                            <tr>
                                              <td>3.</td>
                                              <td>Lands up into the Dashboard.</td>
                                              <td>Employer</td>
                                              <td></td>
                                            </tr>
                                            <tr>
                                              <td>4.</td>
                                              <td>1. Selects ‘BOCWA Application’ from Left Hand Panel.</br>
                                                2. Online Application Form for Registration of Establishment opens.</br>
                                                3. Fills up necessary information about Establishment and uploads self-certified copies of required documents in PDF format.</br></td>
                                              <td>Employer </td>
                                              <td> a) Valid Trade License</br>
                                                b)	Article of Association and Memorandum of Association / Partnership Deed</br>
                                                c) Work Order</br>
                                                d) Form-I for assessment of CESS</br>
                                                e) Documents in Support of Payment of welfare CESS</br>
                                                f) Documents in Support of Correctness of Application</br>
                                                g) Address Proof</br>
                                                </br></td>
                                            </tr>
                                            <tr>
                                              <td>5.</td>
                                              <td>Views the Filled in Information in the Application Preview section before Final Submission or in case of correction rolls back to 
                                                earlier sections and makes corrections and Saves the application.</td>
                                              <td>Employer</td>
                                              <td></td>
                                            </tr>
                                            <tr>
                                              <td>6.</td>
                                              <td>Final Submission of the application.</td>
                                              <td>Employer</td>
                                              <td></td>
                                            </tr>
                                            <tr>
                                              <td>7.</td>
                                              <td>Logs into the system with Credentials.</td>
                                              <td>Inspector concerned</td>
                                              <td></td>
                                            </tr>
                                            <tr>
                                              <td>8.</td>
                                              <td>Lands up in the Dashboard and selects the Application List </td>
                                              <td>Inspector concerned</td>
                                              <td></td>
                                            </tr>
                                            <tr>
                                              <td>9.</td>
                                              <td>He/She views all the Applications that has been submitted by the Applicants along with Uploaded PDF Files.</td>
                                              <td>Inspector concerned</td>
                                              <td></td>
                                            </tr>
                                            <tr>
                                              <td>10.</td>
                                              <td>He/She opens the application and verifies  details  one by one and marks Tick (√) which he/she finds correct and leaves the one as 													not verified which he/she finds  Incorrect</td>
                                              <td>Inspector concerned</td>
                                              <td></td>
                                            </tr>
                                            <tr>
                                              <td>11.</td>
                                              <td> 1. He/she may send the application back to applicant for necessary Correction or Rectification with remarks in case any correction or 
                                                rectification is required.</br>
                                                2. He/she can forward it to the Registering Authority for approval or rejection or further correction.</br></td>
                                              <td>Inspector concerned</td>
                                              <td></td>
                                            </tr>
                                          </tbody>
                                        </table>
                                      </div>
                                    </div>
                                  </div>
                                </div>
                              </div>
                            </div>
                            
                            <div class="tab-pane fade in" id="Post-Operation-Factory">
                              <h2>Not Applicable</h2>
                            </div>
                            
                            <div class="tab-pane fade in" id="Post-Operation-Shop">
                             <div class="panel-group Custom_AC_tab" id="other-shop-sop">
                            
                            <!------Registration of Shop Excluding shops in Kolkata Begin !-----> 
                                <div class="panel panel-default panel-faq">
                                  <div class="panel-heading">
                                    <h4 class="panel-title"><a data-toggle="collapse" data-parent="#other-shop-sop" href="#shop1" class="collapsed"> 
                                      Registration of Shop / Establishment under West Bengal Shops and Establishments Act, 1963 (Excluding shops in Kolkata)
                                     <span class="glyphicon glyphicon-minus pull-right"></span></a> </h4>
                                  </div>
                                  <div id="shop1" class="panel-collapse collapse in">
                                    <div class="panel-body">
                                      <p>1) The applicant can apply through any of the options, i.e. Common Service Centres / Kiosk / on his own through internet.</p>
                                      <p>2) The user will search for the url <strong>'edistrict.wb.gov.in'</strong> in the web browser. </p>
                                      <p>3) If the user is a citizen, he will click <strong>'citizen registration'</strong> to register into the system.</p>
                                      <p>4) After successful registration into the system the user will Log in to the system using his user credentials.</p>
                                      <p>5) For convenience it is advised that the user should, at first, down load the user manual   available under download > Manual for 
                                        registration of shops and establishments where every details are mentioned in a very illustrative way.</p>
                                      <p>6) Click on the service name Registration od shops and establishments under 'Services of Labour Department' module.</p>
                                      <p>7) The applicant will have to click on Apply button in order to apply for <strong>'Registration of Shops and Establishments'</strong> in 		
                                        Instruction and Requirements for Registration of Shops and Establishments page</p>
                                      <p>8) Applicant should fill up the application form available for new registration and for correct entry he should continue by clicking 'save 
                                        and next' button for proceeding to next page.</p>
                                      <p>9) After the applicant fills up the application form and clicks Save & Next button, application details become visible. The applicant can 
                                        either proceed further by attaching supporting documents, or can edit or cancel it, or might take a print out of this page.</p>
                                      <p>10) After satisfactory filling up of application form the applicant should attach and upload scanned copies of required documents as per 
                                        check list. The applicant can view the application details and supporting document list before the submission of
                                        the application form for Registration of Shops and Establishments.</p>
                                      <p>11) Finally the applicant is required to submit the application form and will get an system generated acknowledgement of receipt of 	
                                        application bearing AIN.</p>
                                      <p>12) The Inspector will verify the application and supporting documents. If the application and documents are found correct, the Inspector 
                                        will forward it to the ALC for further verification. If the application is not correct, the Inspector will send back the application to 
                                        the applicant for correction or can reject it with reason.</p>
                                      <p>13) After the Inspector forwards the application, the ALC will have to conduct further verification. The ALC will verify the application and 											  										  supporting documents forwarded from the Inspector. If the application is not correct, the ALC can either reject it or send back to the 	
                                        applicant for correction. If the application is correct the ALC will notify the applicant for proper payment.</p>
                                      <p>14) When an application is accepted for payment, the applicant is automatically notified. In this case the applicant (citizen/ CSC/ kiosk 	
                                        operator) is required to login to the system. For payment procedure, the applicant will have to click on 'Payment Pending Application'. 	
                                        'List of Payment-Pending Application' page will open. The user is required to click the 'Registration of Shops and Establishments' 	
                                        service from the drop down list of 'Please Select Service Name' list-field. After the user has selected 'Registration of Shops and 
                                        Establishments' service, he/she will have to click on 'Search' button to view the list of payment pending 
                                        application for that service. </p>
                                      <p>15)The user will have to select the proper application having same AIN from the list of payment pending applications for 'Registration of 
                                        Shops and Establishments' and click on the button under 'Action' column for payment. Applicant can opt for online payment 
                                        and proceed.</p>
                                      <p>16) After successful payment the inspector will digitally sign the registration certificate.</p>
                                      <p>17) In order to get the certificate of Registration of Shops and Establishments, the applicant (Citizen/ CSC/ Kiosk Operator) will have to 	
                                        login to the system again and to click on 'Approved Application'. The 'List of Approved Applications' page will open, where the 
                                        applicant will have to select the service name from 'Please Select Service Name' list field. After the applicant selects 'Renewal of 
                                        Registration of Shops and Establishments' as service name and clicks on 'Search' button, the list of approved applications for the 
                                        service will be displayed. The user will have to click on the ‘Certificate’ icon for a particular application to get the digitally 
                                        signed registration certificate.</p>
                                    </div>
                                  </div>
                                </div>
                               <!------Registration of Shop Excluding shops in Kolkata End !----->  
                               
                               <!------Registration of Shop Including shops in Kolkata Begin !----->  
                               
                               <div class="panel panel-default panel-faq">
                                  <div class="panel-heading">
                                    <h4 class="panel-title"><a data-toggle="collapse" data-parent="#other-shop-sop" href="#shop2" class="collapsed">
                                      Registration of Shop / Establishment under West Bengal Shops and Establishments Act, 1963 (For shops in Kolkata)
                                     <span class="glyphicon glyphicon-plus pull-right"></span></a> </h4>
                                  </div>
                                  <div id="shop2" class="panel-collapse collapse">
                                    <div class="panel-body">
                                      <p>1) The user will search for the url <strong>'wbshopsonline.in'</strong> in the web browser.</p>
                                      <p>2) Click to Online Apply for applying online to get Registration Certificate in the home page of the portal. </p>
                                      <p>3) If the applicant employer or shopkeeper is a  New User, click on REGISTER and register himself after submitting some credentials</p>
                                      <p>4) After successful registration user will receive a verification mail in his mail box.</p>
                                      <p>5) User has to click on the link sent to his mail for verification. Till the verification of e mail is completed user registration will not 
                                        be successful.</p>
                                      <p>6) User has to verify this within 2 hours of registration otherwise user registration will be cancelled and the user have to register 	
                                        afresh.</p>
                                      <p>7) After successful verification user will receive an SMS as well as e-mail containing the 'Username' and 'Password' for Log In.</p>
                                      <p>8) Now the user is to log in using the user id and password received.</p>
                                      <p>9) Now to apply online user is to click on 'Form' menu to view list of forms. There are 3 types of forms :-</br>
                                        a) From-B (New Registration)</br>
                                        b) Form-D (Renewal)</br>
                                        c) Form-C (Notice of Change)</br>
                                        d) Form E (for winding up of business)</br>
                                      </p>
                                      <p>10) It is advisable for the user to see the guidelines and the user manuals available in the website before starting the process of applying					
                                        online. </p>
                                      <p>11) Now to click on 'Apply Online' to get the digital application form. The user has to fill up the form step by step.</p>
                                      <p>12) The user is also to upload supporting documents after filling up the form.</p>
                                      <p>13) The user can edit the particulars submitted by him at any stage before final submission of the application.</p>
                                      <p>14) After filling up User will print the application form & sign on it, he can use his DSC also if available. The user then upload the PDF 	
                                        copy of the signed application form. </p>
                                      <p>15) By clicking Apply Now the applicant finally submit the application form. The documents required will also be uploaded.</p>
                                      <p>16) User can see application status log (For applied applications only).</p>
                                      <p>17) The Inspector or the Assistant Labour Commissioner can suggest for some correction or seek clarification by sending back to the 
                                        applicant or can take necessary action for approval as the case may be. </p>
                                      <p>18) User can view the remarks of the Inspector or the Assistant Labour Commissioner and take necessary steps regarding any correction or 
                                        remarks sent from the Inspector or ALC.</p>
                                      <p>19) After rectification as suggested the user can re-submit the updated application form.</p>
                                      <p>20) Regarding corrections relating to attached documents user can see the status of required attachments, if any, and he can upload the 
                                        required document accordingly. </p>
                                      <p>21) After approval from the ALC, the user can pay the fees online through GRIPS portal. </p>
                                      <p>22) After payment the user will upload the documents in support of payment of fees. However in case of submission of application form 	
                                        without Digital Signature or in case of offline payment the user has to submit the original signed copies of the same before the 
                                        Registering Authority. </p>
                                      <p>23) After successful payment the Registration certificate will be issued and made available in the user’s dash board. The final 	
                                        registration certificate can be viewed and downloaded by the user. The detail procedure is available in the user manual available in 	
                                        the website itself. </p>
                                      </br>
                                      <p><strong>However a detailed user manual is available in the <a href="https://wbshopsonline.in/" target="_blank"> <strong style="color:#C30">West Bengal Shops and Establishments Portal</strong></a> <br>
                                        </strong></p>
                                    </div>
                                  </div>
                                </div>
                                
                              <!------Registration of Shop Including shops in Kolkata End !----->  
                              
                              <!------------- Shops Renewal Begin (For Shops Excluding Kolkata)---------> 
                              
                              <div class="panel panel-default panel-faq">
                                  <div class="panel-heading">
                                    <h4 class="panel-title"><a data-toggle="collapse" data-parent="#other-shop-sop" href="#shop3" class="collapsed"> 
                                     Renewal under West Bengal Shops and Establishments Act, 1963 (For Shops outside Kolkata)
                                    <span class="glyphicon glyphicon-plus pull-right"></span></a> </h4>
                                  </div>
                                  <div id="shop3" class="panel-collapse collapse">
                                    <div class="panel-body">
                                      <p>The general procedure for application for renewal of registration certificate of shops and establishments located in West Bengal other than 
                                        Kolkata region under the ’edistrict.wb.gov.in’ portal is as follows:</br>
                                      </p>
                                      <p>1) The citizen/CSC/kiosk operator will log in to the system to apply for Renewal of Registration of Shops and Establishments.</p>
                                      <p>2) For convenience it is advised that the user should, at first, down load the user manual available under download > Manual for renewal of 
                                        registration of shops and establishments where every details are mentioned in a very illustrative way. </p>
                                      <p>3) User is to choose the 'Renewal of Registration of Shops and Establishments' Service by clicking on the service name which is available 	
                                        under the column 'Department'.</p>
                                      <p>4) The user at first is to insert the Registration No and Name of the Shop / Establishment in the application form for searching in the data 	
                                        base. The 'Renewal effective from’ and 'Renewal valid upto', these two fields are also part of the basic information required. After 	
                                        correct entry and submission the applicant can view the application details and is also required to upload the required documents. After 
                                        successful submission the system will generate a receipt having AIN (Application Identification Number).</p>
                                      <p> 5) The Inspector will verify the application and supporting documents. If the application and documents are correct, the Inspector will 	
                                        approve it and a notice will be generated for payment. If the application is not correct, the Inspector will reject it with reason.</p>
                                      <p>6) When an application is accepted for payment, the applicant is automatically notified. In this case the applicant (citizen/ CSC/ kiosk 
                                        operator) will have to login to the system. In order complete the payment procedure, the applicant will have to click on 'Payment Pending 
                                        Application'. 'List of Payment-Pending Application' page will open. The user will have to click the 'Renewal of Registration of Shops and 
                                        Establishments' service from the drop down list of 'Please Select Service Name' list-field. After the user has selected service, he/ she 	
                                        will have to click on 'Search' button to view the list of payment pending application for that service. The user will have to select the 
                                        proper application with same AIN from the list of payment pending applications for 'Renewal of Registration of Shops and Establishments'
                                        and click on the button under 'Action' column to proceed for payment. The applicant can pay the requisite fees online through payment 
                                        gateway.</p>
                                      <p>7) After the applicant makes the correct payment, final approval is done by the Inspector. If the payment amount is not correct the Inspecto 
                                        will send back the application to the applicant for repayment of correct amount. If the payment is made correctly, the Inspector will 	
                                        approve the application for renewal of registration with digital signature.</p>
                                      <p>8) In order to get the certificate for Renewal of Registration of Shops and Establishments, the applicant (Citizen/ CSC/ Kiosk Operator) will 	
                                        have to login to the system again and to click on 'Approved Application'. The 'List of Approved Applications' page will open, where the 	
                                        applicant will have to select the service name from 'Please Select Service Name' list field. After the applicant selects 'Renewal of 		
                                        Registration of Shops and Establishments' as service name and clicks on 'Search' button, the list of approved applications for the service 
                                        will be displayed. The user will have to click on the 'Certificate' icon for a particular application to get the digitally signed renewed 
                                        certificate of Registration.</p>
                                    </div>
                                  </div>
                                </div>
                                
                             <!------------- Shops Renewal End (For Shops Excluding Kolkata)--------->  
                             
                             
                             <!------------- Shops Renewal Begin (For Shops in Kolkata)---------> 
                             
                             <div class="panel panel-default panel-faq">
                                  <div class="panel-heading">
                                    <h4 class="panel-title"><a data-toggle="collapse" data-parent="#other-shop-sop" href="#shop4" class="collapsed"> 
                                      Renewal under West Bengal Shops and Establishments Act, 1963 (For Shops in Kolkata) 
                                    <span class="glyphicon glyphicon-plus pull-right"></span></a> </h4>
                                  </div>
                                  <div id="shop4" class="panel-collapse collapse">
                                    <div class="panel-body">
                                      <p>1) The user will search for the url <strong>'wbshopsonline.in'</strong> in the web browser.</p>
                                      <p>2) Click to Online Apply for applying online to get Registration Certificate in the home page of the portal.</p>
                                      <p>3) If the applicant employer or shopkeeper is a  New User, click on REGISTER and register himself after submitting some credentials.</p>
                                      <p>4) After successful registration user will receive a verification mail in his mail box.</p>
                                      <p>5) User has to click on the link sent to his mail for verification. Till the verification of e-mail is completed user registration will not 	
                                        be successful.</p>
                                      <p>6) User has to verify this within 2 hours of registration otherwise user registration will be cancelled and the user have to register 
                                        afresh.</p>
                                      <p>7) After successful verification user will receive an SMS as well as e-mail containing the 'Username' and 'Password' for Log In;</p>
                                      <p>8) Now the user is to log in using the user id and password received.</p>
                                      <p>9) Now to apply online user is to click on 'Form' menu to view list of forms. There are 3 types of forms :-</br>
                                        a) From-B (New Registration)</br>
                                        b) Form-D (Renewal)</br>
                                        c) Form-C (Notice of Change)</br>
                                        d) Form E (For winding up of business)</br>
                                      </p>
                                      <p>10) Then select for renewal option.</p>
                                      <p>11) Enter the registration certificate number and press on GO button. The whole application as it stood previously will be populated if the 	
                                        data of the shop or establishment is already available in the data base. If no such data is available in the data base i.e. for history		
                                        data, blank application form will appear and it should be filled up in the same way as New Registration for validation and further 
                                        processing when ever asked by the system to do so. </p>
                                      <p>12) User has to check the details in application form and submit the form. After filling up, User will print the application form & sign on 	
                                        it, he can use his DSC also if available. The user then upload the PDF copy of the signed application form for renewal.</p>
                                      <p>13) After filling up User will print the application form & sign on it, he can use his DSC also if available. The user then upload the PDF 
                                        copy of the signed application form.</p>
                                      <p>14) By clicking Apply Now the applicant finally submit the application form. The documents required will also be uploaded. </p>
                                      <p>15) User can see application status log (For applied applications only).</p>
                                      <p>16) The Inspector or the Assistant Labour Commissioner can suggest for some correction or seek clarification by sending back to the 
                                        applicant or can take necessary action for approval as the case may be. </p>
                                      <p>17) User can view the remarks of the Inspector or the Assistant Labour Commissioner and take necessary steps regarding any correction or 
                                        remarks sent from the Inspector or ALC. </p>
                                      <p>18) After rectification as suggested the user can re-submit the updated application form.</p>
                                      <p>19) Regarding corrections relating to attached documents user can see the status of required attachments, if any, and he can upload the 
                                        required document accordingly</p>
                                      <p>20) After approval from the ALC, the user will pay the fees online through GRIPS portal. </p>
                                      <p>21) After payment the user will upload the documents in support of payment of fees. However in case of submission of application form 
                                        without Digital Signature or in case of offline payment the user has to submit the original signed copies of the same before the 	
                                        Registering Authority. </p>
                                      <p>22) The final registration certificate can be viewed and downloaded by the user. The detail procedure is available in the user manual 
                                        available in the website itself. </p>
                                      <p><strong>However a detailed user manual is available in the <a href="https://wbshopsonline.in/" target="_blank"> <strong style="color:#C30">
                                         West Bengal Shops and Establishments Portal</strong></a> <br>
                                        </strong></p>
                                    </div>
                                  </div>
                                </div>
                             
                             <!------------- Shops Renewal End (For Shops in Kolkata)---------> 
                                
                             </div>   
                            </div>
                          </div>
                        </div>
                      </div>
                    </div>
                  </div>
                </div>
                <div class="tab-pane" id="timeline">
                  <div class="tabbable tabs-left">
                    <ul class=" col-sm-2 nav nav-tabs" role="tablist">
                      <li role="presentation" class="active"><a href="#Pre-Operation-timeline" aria-controls="home" role="tab" data-toggle="tab">Pre Operation</a></li>
                      <li role="presentation"><a href="#Pre-Establishment-timeline" aria-controls="home" role="tab" data-toggle="tab">Pre Establishment</a></li>
                      <li role="presentation"><a href="#Post-Operation-timeline" aria-controls="home" role="tab" data-toggle="tab">Others</a></li>
                    </ul>
                    <div class="col-sm-10 tab-content STab_content">
                      <div class="tab-pane active" id="Pre-Operation-timeline">
                        <div class="tabbable-panel InTopTab">
                          <div class="tabbable-line">
                            <ul class="nav nav-tabs tabtop  tabsetting">
                              <li class="active"> <a href="#Pre-Operation-Boilers-timeline" data-toggle="tab">Directorate of Boilers</a> </li>
                              <li> <a href="#Pre-Operation-Commissionerate-timeline" data-toggle="tab">Labour Commissionerate</a> </li>
                              <li> <a href="#Pre-Operation-Factory-timeline" data-toggle="tab">Directorate of Factories</a> </li>
                              <li> <a href="#Pre-Operation-Shop-timeline" data-toggle="tab">Shops and Establishment</a> </li>
                            </ul>
                          </div>
                          <div class="tab-content InTTab_content">
                            <div class="tab-pane active fade in" id="Pre-Operation-Boilers-timeline">
                              <div class="panel-group Custom_AC_tab" role="tablist" aria-multiselectable="true">
                                <div class="panel panel-default panel-faq">
                                  <div class="panel-heading">
                                    <h4 class="panel-title"> <a data-toggle="collapse" data-parent="#accordion" href="#Pre-Operation-Boilers-timeline1">Timeline for Service Delivery, Directorate of Boilers (GoWB) <span class="glyphicon pull-right glyphicon-minus"></span></a> </h4>
                                  </div>
                                  <div id="Pre-Operation-Boilers-timeline1" class="panel-collapse collapse in">
                                    <div class="panel-body">
                                      <div class="timeline">
                                        <table border="1" cellpadding="0" cellspacing="0" class="table" style="width:100%">
                                          <thead>
                                            <tr>
                                              <th rowspan="2">Sl. No.</th>
                                              <th rowspan="2">Services</th>
                                              <th rowspan="2">Designated Officer</th>
                                              <th rowspan="2">Stipulated Time Limit</th>
                                              <th colspan="2">Appellate Officer</th>
                                              <th colspan="2">Reviewing Officer</th>
                                            </tr>
                                            <tr>
                                              <th>Designation</th>
                                              <th>Stipulated Time Limit</th>
                                              <th>Designation</th>
                                              <th>Stipulated Time Limit</th>
                                            </tr>
                                          </thead>
                                          <tbody>
                                            <tr>
                                              <td>1.</td>
                                              <td>Issuance of provisional order of Boiler under Form V.</td>
                                              <td>Assistant Director of Boilers/Deputy Director of Boilers as applicable.</td>
                                              <td>15days after satisfactory inspection</td>
                                              <td>Joint Director of Boilers</td>
                                              <td>45Days</td>
                                              <td>Director of Boilers</td>
                                              <td>60Days</td>
                                            </tr>
                                            <tr>
                                              <td>2.</td>
                                              <td>Issuance of Final Certificate of Boiler under Form VI.</td>
                                              <td>Assistant Director of Boilers/Deputy Director of Boilers as applicable.</td>
                                              <td>6 months after satisfactory inspection</td>
                                              <td>Joint Director of Boilers</td>
                                              <td>45Days</td>
                                              <td>Director of Boilers</td>
                                              <td>60Days</td>
                                            </tr>
                                            <tr>
                                              <td>3.</td>
                                              <td>Examination of Boiler under Registration.</td>
                                              <td>Assistant Director of Boilers/Deputy Director of Boilers as applicable.</td>
                                              <td>30days from the date of receipt of the application for Registration</td>
                                              <td>Joint Director of Boilers</td>
                                              <td>45Days</td>
                                              <td>Director of Boilers</td>
                                              <td>60Days</td>
                                            </tr>
                                            <tr>
                                              <td>4.</td>
                                              <td>Inspection of Boilers for renewal of certificates.</td>
                                              <td>Assistant Director of Boilers/Deputy Director of Boilers as applicable.</td>
                                              <td>15days from the date of receipt of the application.</td>
                                              <td>Joint Director of Boilers</td>
                                              <td>45Days</td>
                                              <td>Director of Boilers</td>
                                              <td>60Days</td>
                                            </tr>
                                          </tbody>
                                        </table>
                                        <br />
                                        <p><strong>Click <a href="https://wbboilers.gov.in/sites/default/files/time-lines-for-service-delivery.pdf" target="_blank"> <strong style="color:#C30">HERE</strong></a> to view / download the timeline for the delivery of different services of Directorate of Boilers (GoWB) - Part 1 <br>
                                          </strong></p>
                                        <br />
                                        <table border="1" cellpadding="0" cellspacing="0" class="table" style="width:100%">
                                          <thead>
                                            <tr>
                                              <th rowspan="2">Sl. No.</th>
                                              <th rowspan="2">Services</th>
                                              <th rowspan="2">Designated Officer</th>
                                              <th rowspan="2">Stipulated Time Limit</th>
                                              <th colspan="2">Appellate Officer</th>
                                              <th colspan="2">Reviewing Officer</th>
                                            </tr>
                                            <tr>
                                              <th>Designation</th>
                                              <th>Stipulated Time Limit</th>
                                              <th>Designation</th>
                                              <th>Stipulated Time Limit</th>
                                            </tr>
                                          </thead>
                                          <tbody>
                                            <tr>
                                              <td>5.</td>
                                              <td>Issuance of Certificate of Boilers/Economiser, their components, etc. during manufacturing.</td>
                                              <td>Assistant Director of Boilers/Dy.Director of Boilers as applicable.</td>
                                              <td>30days after submission of complete authentic documents and fees.</td>
                                              <td>Joint Director of Boilers</td>
                                              <td>45Days</td>
                                              <td>Director of Boilers</td>
                                              <td>60Days</td>
                                            </tr>
                                            <tr>
                                              <td>6.</td>
                                              <td>Examination and approval of Drawings.</td>
                                              <td>Assistant Director of Boilers/Dy.Director of Boilers as applicable.</td>
                                              <td>45days after submission of complete authentic drawings, documents and fees.</td>
                                              <td>Joint Director of Boilers</td>
                                              <td>45Days</td>
                                              <td>Director of Boilers</td>
                                              <td>60Days</td>
                                            </tr>
                                            <tr>
                                              <td>7.</td>
                                              <td>Change of Ownership of Boilers/Economiser.</td>
                                              <td>Assistant Director of Boilers/Dy.Director of Boilers as applicable.</td>
                                              <td>60days after submission of complete authentic documents and fees.</td>
                                              <td>Joint Director of Boilers</td>
                                              <td>45Days</td>
                                              <td>Director of Boilers</td>
                                              <td>60Days</td>
                                            </tr>
                                            <tr>
                                              <td>8.</td>
                                              <td>Approval of Repairer/Erectors/MAnufacturer of Boiler and Pipe Line/Endorsement of Repairer/Erectors of Boiler and Pipe Line.</td>
                                              <td>Assistant Director of Boilers/Dy.Director of Boilers as applicable.</td>
                                              <td>30days after submission of complete authentic documents and fees.</td>
                                              <td>Joint Director of Boilers</td>
                                              <td>45Days</td>
                                              <td>Director of Boilers</td>
                                              <td>60Days</td>
                                            </tr>
                                            <tr>
                                              <td>9.</td>
                                              <td>Registration Of Steam and Feed Pipe Lines.</td>
                                              <td>Assistant Director of Boilers/Dy.Director of Boilers as applicable.</td>
                                              <td>30days after submission of complete authentic documents and fees.</td>
                                              <td>Joint Director of Boilers</td>
                                              <td>45Days</td>
                                              <td>Director of Boilers</td>
                                              <td>60Days</td>
                                            </tr>
                                            <tr>
                                              <td>10.</td>
                                              <td>Testing of Materials at Testing Laboratory.</td>
                                              <td>Inspecting Officer/Superintendent of testing laboratory.</td>
                                              <td>7days after completion of testing.</td>
                                              <td>Joint Director of Boilers</td>
                                              <td>45Days</td>
                                              <td>Director of Boilers</td>
                                              <td>60Days</td>
                                            </tr>
                                            <tr>
                                              <td>11.</td>
                                              <td>Issuance of Erection Certificate of Boilers/Economiser.</td>
                                              <td>Assistant Director of Boilers/Dy.Director of Boilers as applicable.</td>
                                              <td>30days after completion of hydraulic test of Boilers/Econamiser.</td>
                                              <td>Joint Director of Boilers</td>
                                              <td>45Days</td>
                                              <td>Director of Boilers</td>
                                              <td>60Days</td>
                                            </tr>
                                          </tbody>
                                        </table>
                                        <br />
                                        <p><strong>Click <a href="https://wbboilers.gov.in/sites/default/files/time-lines-for-service-delivery-rest.pdf" target="_blank"> <strong style="color:#C30">HERE</strong></a> to view / download the timeline for the delivery of different services of Directorate of Boilers (GoWB) - Part 2</strong></p>
                                        <br />
                                      </div>
                                    </div>
                                  </div>
                                </div>
                              </div>
                            </div>
                            <div class="tab-pane fade in" id="Pre-Operation-Commissionerate-timeline">
                             <div class="panel-group Custom_AC_tab" role="tablist" aria-multiselectable="true">
                              <div class="panel panel-default panel-faq">
                                  <div class="panel-heading">
                                    <h4 class="panel-title"> <a>Registration of Motor Transport undertaking under Motor Transport Workers Act, 1979
                                     <strong style="float:right">30 Days</strong></a> </h4>
                                  </div>
                                </div>
                             </div>
                            </div>
                            <div class="tab-pane fade in" id="Pre-Operation-Factory-timeline">
                              <div class="panel-group Custom_AC_tab" role="tablist" aria-multiselectable="true">
                                <div class="panel panel-default panel-faq">
                                  <div class="panel-heading">
                                    <h4 class="panel-title"> <a>Registration and Grant of Factory licence <strong style="float:right">65 DAYS</strong></a> </h4>
                                  </div>
                                </div>
                              </div>
                            </div>
                            <div class="tab-pane fade in" id="Pre-Operation-Shop-timeline">
                              <h2>Coming Soon</h2>
                            </div>
                          </div>
                        </div>
                      </div>
                      <div class="tab-pane" id="Pre-Establishment-timeline">
                        <div class="tabbable-panel InTopTab">
                          <div class="tabbable-line">
                            <ul class="nav nav-tabs tabtop  tabsetting">
                              <li class="active"> <a href="#Pre-Establishment-Boilers-timeline" data-toggle="tab">Directorate of Boilers</a> </li>
                              <li> <a href="#Pre-Establishment-Commissionerate-timeline" data-toggle="tab">Labour Commissionerate</a> </li>
                              <li> <a href="#Pre-Establishment-Factory-timeline" data-toggle="tab">Directorate of Factories</a> </li>
                              <li> <a href="#Pre-Establishment-Shop-timeline" data-toggle="tab">Shops and Establishment</a> </li>
                            </ul>
                          </div>
                          <div class="tab-content InTTab_content">
                            <div class="tab-pane active fade in" id="Pre-Establishment-Boilers-timeline">
                              <h2>Not Applicable</h2>
                            </div>
                            <div class="tab-pane fade in" id="Pre-Establishment-Commissionerate-timeline">
                              <h2>Coming Soon</h2>
                            </div>
                            <div class="tab-pane fade in" id="Pre-Establishment-Factory-timeline">
                              <div class="panel-group Custom_AC_tab" role="tablist" aria-multiselectable="true">
                                <div class="panel panel-default panel-faq">
                                  <div class="panel-heading">
                                    <h4 class="panel-title"> <a>Approval of Factory Plan <strong style="float:right">50 DAYS</strong></a> </h4>
                                  </div>
                                </div>
                              </div>
                            </div>
                            <div class="tab-pane fade in" id="Pre-Establishment-Shop-timeline">
                              <h2>Coming Soon</h2>
                            </div>
                          </div>
                        </div>
                      </div>
                      <div class="tab-pane" id="Post-Operation-timeline">
                        <div class="tabbable-panel InTopTab">
                          <div class="tabbable-line">
                            <ul class="nav nav-tabs tabtop  tabsetting">
                              <li class="active"> <a href="#Post-Operation-Boilers-timeline" data-toggle="tab">Directorate of Boilers</a> </li>
                              <li> <a href="#Post-Operation-Commissionerate-timeline" data-toggle="tab">Labour Commissionerate</a> </li>
                              <li> <a href="#Post-Operation-Factory-timeline" data-toggle="tab">Directorate of Factories</a> </li>
                              <li> <a href="#Post-Operation-Shop-timeline" data-toggle="tab">Shops and Establishment</a> </li>
                            </ul>
                          </div>
                          <div class="tab-content InTTab_content">
                              <div class="tab-pane active fade in" id="Post-Operation-Boilers-timeline">
                              <h2>Not Applicable</h2>
                            </div>  
                            
                           <div class="tab-pane fade" id="Post-Operation-Commissionerate-timeline">
                            <div class="panel-group Custom_AC_tab" role="tablist" aria-multiselectable="true">
                              <div class="panel panel-default panel-faq">
                                  <div class="panel-heading">
                                    <h4 class="panel-title"> <a>Registration of establishment of Principal Employer and amendment thereof under Contract Labour</br>
                                      (Regulation and Abolition) Act, 1970 <strong style="float:right">30 Days</strong></a> </h4>
                                  </div>
                                </div>
                             </div>
                             
                             <div class="panel-group Custom_AC_tab" role="tablist" aria-multiselectable="true">
                              <div class="panel panel-default panel-faq">
                                  <div class="panel-heading">
                                    <h4 class="panel-title"> <a>Licensing of contractors under Contract Labour (Regulation and Abolition) Act, 1970
                                     <strong style="float:right">30 Days</strong></a> </h4>
                                  </div>
                                </div>
                             </div>
                             
                             <div class="panel-group Custom_AC_tab" role="tablist" aria-multiselectable="true">
                              <div class="panel panel-default panel-faq">
                                  <div class="panel-heading">
                                    <h4 class="panel-title"> <a>Renewal of licences of contractors thereof under Contract Labour (Regulation and Abolition) Act, 1970
                                     <strong style="float:right">30 Days</strong></a> </h4>
                                  </div>
                                </div>
                             </div>
                             
                             <div class="panel-group Custom_AC_tab" role="tablist" aria-multiselectable="true">
                              <div class="panel panel-default panel-faq">
                                  <div class="panel-heading">
                                    <h4 class="panel-title"> <a>Registration of establishment by Principal Employer under The Inter-state Migrant Workmen Act 1979
                                     <strong style="float:right">30 Days</strong></a> </h4>
                                  </div>
                                </div>
                             </div>
                             
                             <div class="panel-group Custom_AC_tab" role="tablist" aria-multiselectable="true">
                              <div class="panel panel-default panel-faq">
                                  <div class="panel-heading">
                                    <h4 class="panel-title"> <a>Registration of Establishment under Building and Other Construction Workers </br>
                                    (Regulation of Employment and Conditions of Service) Act, 1996 <strong style="float:right">30 Days</strong></a> </h4>
                                  </div>
                                </div>
                             </div>
                             
                            </div>
                              <div class="tab-pane fade" id="Post-Operation-Factory-timeline">
                              <h2>Not Applicable</h2>
                            </div>
                            
                              <div class="tab-pane fade" id="Post-Operation-Shop-timeline">
                               <div class="panel-group Custom_AC_tab" role="tablist" aria-multiselectable="true">
                                  <div class="panel panel-default panel-faq">
                                    <div class="panel-heading">
                                      <h4 class="panel-title"> <a>Registration under West Bengal Shops and Establishments Act, 1963
                                           <strong style="float:right">1 Day</strong></a> </h4>
                                    </div>
                                  </div>
                                </div>
                                
                                <div class="panel-group Custom_AC_tab" role="tablist" aria-multiselectable="true">
                                <div class="panel panel-default panel-faq">
                                  <div class="panel-heading">
                                    <h4 class="panel-title"> <a>Renewal under West Bengal Shops and Establishments Act, 1963 
                                    	 <strong style="float:right">1 Day</strong></a> </h4>
                                  </div>
                                </div>
                              </div>
                            </div>
                            </div>
                           
                          </div>
                        </div>
                      </div>
                    </div>
                  </div>
                <div class="tab-pane" id="checklist">
                  <div class="tabbable tabs-left">
                    <ul class=" col-sm-2 nav nav-tabs" role="tablist">
                      <li role="presentation" class="active"><a href="#Pre-Operation-checklist" aria-controls="home" role="tab" data-toggle="tab">Pre Operation</a></li>
                      <li role="presentation"><a href="#Pre-Establishment-checklist" aria-controls="home" role="tab" data-toggle="tab">Pre Establishment</a></li>
                      <li role="presentation"><a href="#Post-Operation-checklist" aria-controls="home" role="tab" data-toggle="tab">Others</a></li>
                    </ul>
                    <div class="col-sm-10 tab-content STab_content">
                      <div class="tab-pane active" id="Pre-Operation-timeline">
                        <div class="tabbable-panel InTopTab">
                          <div class="tabbable-line">
                            <ul class="nav nav-tabs tabtop  tabsetting">
                              <li class="active"> <a href="#Pre-Operation-Boilers-checklist" data-toggle="tab">Directorate of Boilers</a> </li>
                              <li> <a href="#Pre-Operation-Commissionerate-checklist" data-toggle="tab">Labour Commissionerate</a> </li>
                              <li> <a href="#Pre-Operation-Factory-checklist" data-toggle="tab">Directorate of Factories</a> </li>
                              <li> <a href="#Pre-Operation-Shop-checklist" data-toggle="tab">Shops and Establishment</a> </li>
                            </ul>
                          </div>
                          <div class="tab-content InTTab_content">
                            <div class="tab-pane active fade in" id="Pre-Operation-Boilers-checklist">
                              <div class="panel-group Custom_AC_tab" id="boiler-checkList">
                                <div class="panel panel-default panel-faq">
                                  <div class="panel-heading">
                                    <h4 class="panel-title"><a data-toggle="collapse" data-parent="#boiler-checkList" href="#boiler-checkList1" class="collapsed">Check List for Registration of Boiler <span class="glyphicon pull-right glyphicon-minus"></span></a></h4>
                                  </div>
                                  <div id="boiler-checkList1" class="panel-collapse collapse in">
                                    <div class="panel-body">
                                      <p>1) Application for registration of the Boilers addressed to the Director of Boilers, W.B</p>
                                      <p>2) Registration Folder containing form-II, form-III and form-IVA of IBR, original drawings of boiler and other relevant documents.</p>
                                      <p>3) Requisite fees for registration of the boiler in the head of accounts: “0230-00-103-001-14” – Service fees(14) online by IFMS-GRIPS portal in <a href="http://www.wbfin.nic.in">www.wbfin.nic.in</a>.</p>
                                      <p>4) Requisite T.A for inspection of the boiler in the head of accounts: “<strong>0230-00-103-002-27</strong>” – Other Receipts(27) online by IFMS-GRIPS portal in <a href="http://www.wbfin.nic.in">www.wbfin.nic.in</a>.</p>
                                      <p>5) Original Certificates of all Mountings and Fittings.</p>
                                    </div>
                                  </div>
                                </div>
                                <div class="panel panel-default panel-faq">
                                  <div class="panel-heading">
                                    <h4 class="panel-title"><a data-toggle="collapse" data-parent="#boiler-checkList" href="#boiler-checkList2" class="collapsed">Check List for approval of Drawings <span class="glyphicon pull-right glyphicon-plus"></span></a></h4>
                                  </div>
                                  <div id="boiler-checkList2" class="panel-collapse collapse">
                                    <div class="panel-body">
                                      <p>1) Application for approval of drawing.</p>
                                      <p>2) Three copies of all relevant drawings.</p>
                                      <p>3) Requisite fees for scrutiny of drawings in the head of accounts:</p>
                                      <p>“<strong>0230-00-103-001-14</strong>” – Service fees(14) online by IFMS-GRIPS portal in <a href="http://www.wbfin.nic.in">www.wbfin.nic.in</a></p>
                                      <p>4) All relevant reference drawings.</p>
                                      <p>5) Flexibility analysis report, if required.</p>
                                      <p>6) Valve schedule</p>
                                      <p>7) Pressure parts calculation.</p>
                                      <p>8) P &amp; I Diagram of the whole system.</p>
                                      <p>9) Feed pump characteristic curve.</p>
                                      <p>10) Copy of Existing Drawings.</p>
                                    </div>
                                  </div>
                                </div>
                                <div class="panel panel-default panel-faq">
                                  <div class="panel-heading">
                                    <h4 class="panel-title"><a data-toggle="collapse" data-parent="#boiler-checkList" href="#boiler-checkList3" class="collapsed">Check List for Renewal of Certificate of boiler <span class="glyphicon pull-right glyphicon-plus"></span></a></h4>
                                  </div>
                                  <div id="boiler-checkList3" class="panel-collapse collapse">
                                    <div class="panel-body">
                                      <p>1) Application for renewal of certificate along with form-B No.1 duly filled in.</p>
                                      <p>2) Requisite fees for inspection of boiler in the head of accounts: “<strong>0230-00-103-001-14</strong>” – <strong>Service fees (14)</strong> online by <strong>IFMS-GRIPS</strong> portal in <a href="http://www.wbfin.nic.in">www.wbfin.nic.in</a></p>
                                      <p>3) Requisite Travelling Allowance in the head of accounts: “<strong>0230-00-103-002-27</strong>” – Other Receipts (27) online by IFMS-GRIPS portal in <a href="http://www.wbfin.nic.in">www.wbfin.nic.in</a></p>
                                    </div>
                                  </div>
                                </div>
                                <div class="panel panel-default panel-faq">
                                  <div class="panel-heading">
                                    <h4 class="panel-title"> <a data-toggle="collapse" data-parent="#boiler-checkList" href="#boiler-checkList4" class="collapsed">Check List for Transfer of Ownership of Boiler <span class="glyphicon pull-right glyphicon-plus"></span></a></h4>
                                  </div>
                                  <div id="boiler-checkList4" class="panel-collapse collapse">
                                    <div class="panel-body">
                                      <p>1) Application for change of ownership by the proposed owner.</p>
                                      <p>2) Sell letter.</p>
                                      <p>3) Self Declaration for No Objection Certificate from the seller of the boiler for change of ownership of boiler.</p>
                                      <p>4) Self Declaration of the proposed owner for change of ownership of boiler.</p>
                                      <p>5) Requisite fees for change of ownership in the head of accounts: “<strong>0230-00-103-001-14</strong>” – Service fees(14) online by <strong>IFMS-GRIPS</strong> portal in <a href="http://www.wbfin.nic.in">www.wbfin.nic.in</a></p>
                                      <p>6) Copy of Trade license, Electric Bill, Voter Card, PAN Card etc.</p>
                                      <p>7) Passport size Photograph of proposed owner.</p>
                                      <p>8) Other relevant documents if required.</p>
                                    </div>
                                  </div>
                                </div>
                                <div class="panel panel-default panel-faq">
                                  <div class="panel-heading">
                                    <h4 class="panel-title"><a data-toggle="collapse" data-parent="#boiler-checkList" href="#boiler-checkList5" class="collapsed">Check List for endorsement of contractor / erector of boiler <span class="glyphicon pull-right glyphicon-plus"></span></a></h4>
                                  </div>
                                  <div id="boiler-checkList5" class="panel-collapse collapse">
                                    <div class="panel-body">
                                      <p>1) Forwarding letter by the owner.</p>
                                      <p>2) Application in prescribed format.</p>
                                      <p>3) Requisite fees for endorsement in the head of accounts: “<strong>0230-00-103-001-14</strong>” – Service fees(14) online by IFMS-GRIPS portal in <a href="http://www.wbfin.nic.in">www.wbfin.nic.in</a></p>
                                      <p>4) Copy of drawing approval letter in case of new erection or modification of boiler / pipe line.</p>
                                      <p>5) Copy of repairing report in case of repairing.</p>
                                      <p>6) Documents of manpower of the contractor/erector.</p>
                                      <p>7) List of machineries of the contractor.</p>
                                      <p>8) Documents of experience of the contractor/erector.</p>
                                    </div>
                                  </div>
                                </div>
                                <div class="panel panel-default panel-faq">
                                  <div class="panel-heading">
                                    <h4 class="panel-title"><a data-toggle="collapse" data-parent="#boiler-checkList" href="#boiler-checkList6" class="collapsed">Check List for Remnant Life Assessment of Boiler <span class="glyphicon pull-right glyphicon-plus"></span></a></h4>
                                  </div>
                                  <div id="boiler-checkList6" class="panel-collapse collapse">
                                    <div class="panel-body">
                                      <p>1) Application for RLA study.</p>
                                      <p>2) Submission of scheme of RLA for the proposed boiler.</p>
                                      <p>3) Submission of requisite fees for inspection of boiler in the head of accounts: “<strong>0230-00-103-001-14</strong>” – Service fees(14) online by <strong>IFMS-GRIPS</strong> portal in <strong><a href="http://www.wbfin.nic.in">www.wbfin.nic.in</a></strong></p>
                                      <p>4) Requisite T.A for inspection of the boiler in the head of accounts:“<strong>0230-00-103-002-27</strong>” – Other Receipts(27) online by <strong>IFMS-GRIPS</strong> portal in <a href="http://www.wbfin.nic.in">www.wbfin.nic.in</a></p>
                                      <p>5) Submission of documents of the approved RLA organisation who will conduct the <strong>RLA studies</strong>.</p>
                                    </div>
                                  </div>
                                </div>
                                <div class="panel panel-default panel-faq">
                                  <div class="panel-heading">
                                    <h4 class="panel-title"><a data-toggle="collapse" data-parent="#boiler-checkList" href="#boiler-checkList7" class="collapsed">Check List for submission of Form-IIIA for Identification Number of Pipe Lines <span class="glyphicon pull-right glyphicon-plus"></span></a></h4>
                                  </div>
                                  <div id="boiler-checkList7" class="panel-collapse collapse">
                                    <div class="panel-body">
                                      <p>1) Application for approval of Form-IIIA.</p>
                                      <p>2) Submission of requisite fees for inspection of pipe lines in the head of accounts: “<strong>0230-00-103-001-14</strong>” – Service fees(14) online by IFMS-GRIPS portal in <a href="http://www.wbfin.nic.in">www.wbfin.nic.in</a>.</p>
                                      <p>3) Submission of Form-IIIA for steam pipe line duly filled in.</p>
                                      <p>4) Submission of Form-IIIA for feed pipe lines duly filled in.</p>
                                      <p>5) copy of all relevant drawings of steam and feed pipe lines.</p>
                                      <p>6) Copy of Drawing approval letter.</p>
                                      <p>7) IBR certificates of all components of pipes and fittings ( like- Form IIIA, Form-IIIB, Form IIIC, Form-IIID, Form-IIIE, Form-IIIF, Form-IIIG etc.)</p>
                                      <p>8) Copy of Contractor’s approval letter.</p>
                                      <p>9) All NDT reports.</p>
                                      <p>10) Post weld heat treatment report and stress relieving charts</p>
                                      <p>11) PMI report.</p>
                                      <p>12) Copy of all inspection reports of pipe lines under erection.</p>
                                    </div>
                                  </div>
                                </div>
                                <div class="panel panel-default panel-faq">
                                  <div class="panel-heading">
                                    <h4 class="panel-title"><a data-toggle="collapse" data-parent="#boiler-checkList" href="#boiler-checkList8" class="collapsed">Check List for Registration of Economiser <span class="glyphicon pull-right glyphicon-plus"></span></a></h4>
                                  </div>
                                  <div id="boiler-checkList8" class="panel-collapse collapse">
                                    <div class="panel-body">
                                      <p>1) Application for registration of the economiser addressed to the Director of Boilers, W.B</p>
                                      <p>2) Registration Folder containing form-VII, form-VIII, original drawings of economiser and other relevant documents.</p>
                                      <p>3) Requisite fees for registration of the economiser in the head of accounts: “<strong>0230-00-103-001-14</strong>” – Service fees(14) online by <strong>IFMS-GRIPS</strong> portal in <strong><a href="http://www.wbfin.nic.in">www.wbfin.nic.in</a></strong></p>
                                      <p>4) Requisite T.A for inspection of the boiler in the head of accounts: “<strong>0230-00-103-002-27</strong>” – Other Receipts(27) online by IFMS-GRIPS portal in <strong> <a href="http://www.wbfin.nic.in">www.wbfin.nic.in</a></strong></p>
                                      <p>5) Original Certificates of all Mountings and Fittings.</p>
                                    </div>
                                  </div>
                                </div>
                                <div class="panel panel-default panel-faq">
                                  <div class="panel-heading">
                                    <h4 class="panel-title"><a data-toggle="collapse" data-parent="#boiler-checkList" href="#boiler-checkList9" class="collapsed">Check List for Erection of Boiler <span class="glyphicon pull-right glyphicon-plus"></span></a></h4>
                                  </div>
                                  <div id="boiler-checkList9" class="panel-collapse collapse">
                                    <div class="panel-body">
                                      <p>1) Application for erection of the Boilers addressed to the Director of Boilers, W.B</p>
                                      <p>2) Registration Folder containing form-II, form-III and form-IVA of IBR, original drawings of boiler and other relevant documents.</p>
                                      <p>3) Requisite fees for erection of the boiler in the head of accounts: “0230-00-103-001-14” – Service fees(14) online by IFMS-GRIPS portal in <a href="http://www.wbfin.nic.in">www.wbfin.nic.in</a>.</p>
                                      <p>4) Requisite T.A for inspection of the boiler in the head of accounts: “<strong>0230-00-103-002-27</strong>” – Other Receipts(27) online by IFMS-GRIPS portal in <a href="http://www.wbfin.nic.in">www.wbfin.nic.in</a>.</p>
                                      <p>5) Original Certificates of all Mountings and Fittings.</p>
                                    </div>
                                  </div>
                                </div>
                                <div class="panel panel-default panel-faq">
                                  <div class="panel-heading">
                                    <h4 class="panel-title"><a data-toggle="collapse" data-parent="#boiler-checkList" href="#boiler-checkList10" class="collapsed">Check List for Manufacturing of Boiler <span class="glyphicon pull-right glyphicon-plus"></span></a></h4>
                                  </div>
                                  <div id="boiler-checkList10" class="panel-collapse collapse">
                                    <div class="panel-body">
                                      <p>1) Application addressed to DOB.</p>
                                      <p>2) Requisite Fees.</p>
                                      <p>3) Original Approved Drawings.</p>
                                      <p>4) Original Certificate of all Raw Materials.</p>
                                      <p>5) Certificate of Welding Consumables and Welders.</p>
                                      <p>6) Approved WPS.</p>
                                      <p>7) Calibration Certificate of Instruments.</p>
                                    </div>
                                  </div>
                                </div>
                                <div class="panel panel-default panel-faq">
                                  <div class="panel-heading">
                                    <h4 class="panel-title"><a data-toggle="collapse" data-parent="#boiler-checkList" href="#boiler-checkList11" class="collapsed"> Check List for Erection of Economiser <span class="glyphicon pull-right glyphicon-plus"></span></a></h4>
                                    </h4>
                                  </div>
                                  <div id="boiler-checkList11" class="panel-collapse collapse">
                                    <div class="panel-body">
                                      <p>1) Application for erection of the economiser addressed to the Director of Boilers, W.B</p>
                                      <p>2) Registration Folder containing form-VII, form-VIII, original drawings of economiser and other relevant documents.</p>
                                      <p>3) Requisite fees for erection of the economiser in the head of accounts: “<strong>0230-00-103-001-14</strong>” – Service fees(14) online by <strong>IFMS-GRIPS</strong> portal in <strong><a href="http://www.wbfin.nic.in">www.wbfin.nic.in</a></strong></p>
                                      <p>4) Requisite T.A for inspection of the economiser&nbsp;in the head of accounts: “<strong>0230-00-103-002-27</strong>” – Other Receipts(27) online by IFMS-GRIPS portal in <strong> <a href="http://www.wbfin.nic.in">www.wbfin.nic.in</a></strong></p>
                                      <p>5) Original Certificates of all Mountings and Fittings.</p>
                                      <p>6) Experience Certificate in the related field.</p>
                                    </div>
                                  </div>
                                </div>
                                <div class="panel panel-default panel-faq">
                                  <div class="panel-heading">
                                    <h4 class="panel-title"><a data-toggle="collapse" data-parent="#boiler-checkList12" href="#boiler-checkList1" class="collapsed">Check List for Manufacturing of Economizer <span class="glyphicon pull-right glyphicon-plus"></span></a></h4>
                                  </div>
                                  <div id="boiler-checkList12" class="panel-collapse collapse">
                                    <div class="panel-body">
                                      <p>1) Application addressed to DOB.</p>
                                      <p>2) Requisite Fees.</p>
                                      <p>3) Original Approved Drawings.</p>
                                      <p>4) Original Certificate of all Raw Materials.</p>
                                      <p>5) Certificate of Welding Consumables and Welders.</p>
                                      <p>6) Approved WPS.</p>
                                      <p>7) Calibration Certificate of Instruments.</p>
                                    </div>
                                  </div>
                                </div>
                                <div class="panel panel-default panel-faq">
                                  <div class="panel-heading">
                                    <h4 class="panel-title"><a data-toggle="collapse" data-parent="#boiler-checkList" href="#boiler-checkList13" class="collapsed">Check List for Approval and Renewal of Manufacturer <span class="glyphicon pull-right glyphicon-plus"></span></a></h4>
                                  </div>
                                  <div id="boiler-checkList13" class="panel-collapse collapse">
                                    <div class="panel-body">
                                      <p>1) Forwarding Letter by the applicant.</p>
                                      <p>2) Application to Director along with duly filled Form in prescribed format.</p>
                                      <p>3) Copy of Trade License, Lease Deed (if applicable), Tenancy Deed (if applicable), Photo Identity Proof.</p>
                                      <p>4) List of Machineries as mentioned in the Form.</p>
                                      <p>5) List of Technical Personnel along with experience.</p>
                                    </div>
                                  </div>
                                </div>
                                <div class="panel panel-default panel-faq">
                                  <div class="panel-heading">
                                    <h4 class="panel-title"><a data-toggle="collapse" data-parent="#boiler-checkList14" href="#boiler-checkList1" class="collapsed">Check List for Approval and Renewal of Erector <span class="glyphicon pull-right glyphicon-plus"></span></a></h4>
                                  </div>
                                  <div id="boiler-checkList14" class="panel-collapse collapse">
                                    <div class="panel-body">
                                      <p>1) Forwarding Letter by the applicant.</p>
                                      <p>2) Application to Director along with duly filled Form in prescribed format.</p>
                                      <p>3) Copy of Trade License, Lease Deed (if applicable), Tenancy Deed (if applicable), Photo Identity Proof.</p>
                                      <p>4) List of Machineries as mentioned in the Form.</p>
                                      <p>5) List of Technical Personnel along with experience.</p>
                                    </div>
                                  </div>
                                </div>
                              </div>
                            </div>
                            <div class="tab-pane fade in" id="Pre-Operation-Commissionerate-checklist">
                              <div class="panel-group Custom_AC_tab" id="lcpre-checkList">
                               
                               <div class="panel panel-default panel-faq">
                                  <div class="panel-heading">
                                    <h4 class="panel-title"><a data-toggle="collapse" data-parent="#lcpre-checkList" href="#lcpre-checkList1" class="collapsed">
                                     Registration of Motor Transport undertaking under Motor Transport Workers Act, 1979
                                    <span class="glyphicon pull-right glyphicon-minus"></span></a></h4>
                                  </div>
                                  <div id="lcpre-checkList1" class="panel-collapse collapse in">
                                    <div class="panel-body">
                                    <p>Scanned copies of the following documents which ever is applicable :-</p>
                                    <p>1) Trade License.</p>
                                    <p>2) Article of Association and Memorandum of Association / Partnership Deed.</p>
                                    <p>3) Blue Book / Smart Card Issued by Motor Vehicles.</p>
                                    <p>4) Insurance Certificate of Motor Vehicles.</p>
                                    <p>5) Documents in support of correctness of application.</p>
                                    <p>6) Address proof.</p>
                                    <p>7) Form I.</p>
                                    </div>
                                  </div>
                                </div>
                               
                               </div>
                            </div>
                            <div class="tab-pane fade in" id="Pre-Operation-Factory-checklist">
                              <div class="panel-group Custom_AC_tab" id="boiler-checkList">
                                <div class="panel panel-default panel-faq">
                                  <div class="panel-heading">
                                    <h4 class="panel-title"> <a data-toggle="collapse" data-parent="#factory-checkList" href="#factory-checkList1" class="collapsed"> Registration & Licensing of Factories <span class="glyphicon pull-right glyphicon-minus"></span></a> </h4>
                                  </div>
                                  <div id="factory-checkList1" class="panel-collapse collapse in">
                                    <div class="panel-body">
                                      <p>a) Duly filled in Common Application Form in duplicate.</p>
                                      <p>b) Authenticated documents regarding deposition of fees.</p>
                                      <p>c) Authenticated copy of Consent to operate issued by West Bengal pollution control Board for the factories having a hazardous process a 
                                        defined under section 2 (cb) read with Schedule-I of the Factories Act, 1948 as amended or a Declaration for Exempted Category industries as 										   notified by West Bengal pollution control Board.</p>
                                      <p>d) Authenticated copy of Purchase Deed/Lease Deed/Rent Receipt as the case may be in respect of the premises to be used as factory.</p>
                                      <p>e) Authenticated copy of Trade Licence.</p>
                                      <p>f) For Limited and Private Limited company-Authenticated copy of Memorandum of Article of Association For Partnership Firm-Authenticated copy 
                                        of Partnership Deed.</p>
                                      <p>g) Declaration duly signed by the occupier. showing the date of starting of manufacturing process (exact date) along with no. of workers 
                                        engaged therein on that date and installed power, as applicable.</p>
                                      <p>h) List of machineries along with HP/KW duly signed by the occupier.</p>
                                      <p>i) Health and Safety policy, in case a hazardous process.</p>
                                    </div>
                                  </div>
                                </div>
                              </div>
                            </div>
                            <div class="tab-pane fade in" id="Pre-Operation-Shop-checklist">
                              <h2>Coming Soon</h2>
                            </div>
                          </div>
                        </div>
                      </div>
                      <div class="tab-pane" id="Pre-Establishment-checklist">
                        <div class="tabbable-panel InTopTab">
                          <div class="tabbable-line">
                            <ul class="nav nav-tabs tabtop  tabsetting">
                              <li class="active"> <a href="#Pre-Establishment-Boilers-checklist" data-toggle="tab">Directorate of Boilers</a> </li>
                              <li> <a href="#Pre-Establishment-Commissionerate-checklist" data-toggle="tab">Labour Commissionerate</a> </li>
                              <li> <a href="#Pre-Establishment-Factory-checklist" data-toggle="tab">Directorate of Factories</a> </li>
                              <li> <a href="#Pre-Establishment-Shop-checklist" data-toggle="tab">Shops and Establishment</a> </li>
                            </ul>
                          </div>
                          <div class="tab-content InTTab_content">
                            <div class="tab-pane active fade in" id="Pre-Establishment-Boilers-checklist">
                              <h2>Not Applicable</h2>
                            </div>
                            <div class="tab-pane fade in" id="Pre-Establishment-Commissionerate-checklist">
                                <h2>Not Applicable</h2>
                            </div>
                            <div class="tab-pane fade in" id="Pre-Establishment-Factory-checklist">
                              <div class="panel-group Custom_AC_tab" id="boiler-checkList">
                                <div class="panel panel-default panel-faq">
                                  <div class="panel-heading">
                                    <h4 class="panel-title"> <a data-toggle="collapse" data-parent="#factory-checkList" href="#factory-checkList2" class="collapsed">Approval of Factory Plan <span class="glyphicon pull-right glyphicon-minus"></span></a> </h4>
                                  </div>
                                  <div id="factory-checkList2" class="panel-collapse collapse in">
                                    <div class="panel-body">
                                      <p> a) Duly filled in Common Application Form (Part A & Part B).</p>
                                      <p> b) Flow chart of the manufacturing process along with brief description.</p>
                                      <p> c) Authenticated copy of Consent to establish from WBPCB.</a>.</p>
                                      <p> d) Factory plan in duplicate for Kolkata/Howrah and 3 copies for regional offices.</a>.</p>
                                      <p> e) Declaration, duly signed by the occupier, stating whether any process or activity of the factory is a hazardous process as defined under                                                section 2(cb) read with Schedule 1 of the Factories Act.1948 as amended.</p>
                                    </div>
                                  </div>
                                </div>
                              </div>
                            </div>
                            <div class="tab-pane fade in" id="Pre-Establishment-Shop-checklist">
                              <h2>Coming Soon</h2>
                            </div>
                          </div>
                        </div>
                      </div>
                      <div class="tab-pane" id="Post-Operation-checklist">
                        <div class="tabbable-panel InTopTab">
                          <div class="tabbable-line">
                            <ul class="nav nav-tabs tabtop  tabsetting">
                              <li class="active"> <a href="#Post-Operation-Boilers-checklist" data-toggle="tab">Directorate of Boilers</a> </li>
                              <li> <a href="#Post-Operation-Commissionerate-checklist" data-toggle="tab">Labour Commissionerate</a> </li>
                              <li> <a href="#Post-Operation-Factory-checklist" data-toggle="tab">Directorate of Factories</a> </li>
                              <li> <a href="#Post-Operation-Shop-checklist" data-toggle="tab">Shops and Establishment</a> </li>
                            </ul>
                          </div>
                          <div class="tab-content InTTab_content">
                            <div class="tab-pane active fade in" id="Post-Operation-Boilers-checklist">
                              <div class="panel-group Custom_AC_tab" role="tablist" aria-multiselectable="true">
                                <h2>Not Applicable</h2>
                              </div>
                            </div>
                            <div class="tab-pane fade in" id="Post-Operation-Commissionerate-checklist">
                             <div class="panel-group Custom_AC_tab" id="lc-checkList">
                               
                               <div class="panel panel-default panel-faq">
                                  <div class="panel-heading">
                                    <h4 class="panel-title"><a data-toggle="collapse" data-parent="#lc-checkList" href="#lc-checkList1" class="collapsed">
                                      Registration of establishment of Principal Employer and amendment thereof under Contract Labour (Regulation and Abolition) Act, 1970
                                    <span class="glyphicon pull-right glyphicon-minus"></span></a></h4>
                                  </div>
                                  <div id="lc-checkList1" class="panel-collapse collapse in">
                                    <div class="panel-body">
                                    <p>Scanned copies of the following documents which ever is applicable :-</p>
                                    <p>1) Trade License.</p>
                                    <p>2) Article of Association and Memorandum of Association / Partnership Deed.</p>
                                    <p>3) Factory License if any.</p>
                                    <p>4) Previous Registration Certificate (IF ALREADY REGISTERED USER FOR REGISTRATION).</p>
                                    <p>5) Any other document in support of correctness of the particulars mentioned in the application if required.</p>
                                    <p>6) Other certificates of registration in case of other than company, proprietorship or partnership firm like cooperative, Trustees etc.</p>
                                    <p>7) Form I.</p>
                                    </div>
                                  </div>
                                </div>
                                
                              <div class="panel panel-default panel-faq">
                                  <div class="panel-heading">
                                    <h4 class="panel-title"><a data-toggle="collapse" data-parent="#lc-checkList" href="#lc-checkList2" class="collapsed">
                                      Licensing of contractors, renewal and amendment there of under Contract Labour (Regulation and Abolition) Act, 1970
                                    <span class="glyphicon pull-right glyphicon-plus"></span></a></h4>
                                  </div>
                                  <div id="lc-checkList2" class="panel-collapse collapse">
                                    <div class="panel-body">
                                        <p>Scanned copies of the following documents which ever is applicable :-</p>
                                        <p>1) Work Order.</p>
                                        <p>2) Form V.</p>
                                        <p>3) Trade License / Address proof Certificate.</p>
                                        <p>4) License Certificate or Last Renewal Certificate.</p>
                                        <p>5) Other.</p>
                                        <p>6) Form IV/Form VII</p>
                                    </div>
                                  </div>
                                </div>
                             
                             <div class="panel panel-default panel-faq">
                                  <div class="panel-heading">
                                    <h4 class="panel-title"><a data-toggle="collapse" data-parent="#lc-checkList" href="#lc-checkList3" class="collapsed">
                                    Registration of establishment by Principal Employer under the Inter-State Migrant Workmen Act 1979
                                    <span class="glyphicon pull-right glyphicon-plus"></span></a></h4>
                                  </div>
                                  <div id="lc-checkList3" class="panel-collapse collapse">
                                    <div class="panel-body">
                                      <p>Scanned copies of the following documents which ever is applicable :-</p>
                                        <p>1) Trade License.</p>
                                        <p>2) Article of Association and Memorandum of Association / Partnership Deed.</p>
                                        <p>3) Factory License if any.</p>
                                        <p>4) Certificate issued by Authorities from other state.</p>
                                        <p>5) Documents substantiating correctness of particulars mentioned in the application.</p>
                                        <p>6) Form I.</p>
                                    </div>
                                  </div>
                                </div>
                             
                             <div class="panel panel-default panel-faq">
                                  <div class="panel-heading">
                                    <h4 class="panel-title"> <a data-toggle="collapse" data-parent="#lc-checkList" href="#lc-checkList4" class="collapsed">
                                      Registration of Establishment under Building and Other Construction Workers (Regulation of Employment and Conditions of Service) Act, 1996
                                    <span class="glyphicon pull-right glyphicon-plus"></span></a></h4>
                                  </div>
                                  <div id="lc-checkList4" class="panel-collapse collapse">
                                    <div class="panel-body">
                                        <p>Scanned copies of the following documents which ever is applicable :-</p>
                                        <p>1) Trade License.</p>
                                        <p>2) Article of Association and Memorandum of Association / Partnership Deed.</p>
                                        <p>3) Work Order.</p>
                                        <p>4) Challan.</p>
                                        <p>5) Documents in support of Payment of CESS.</p>
                                        <p>6) Address Proof.</p>
                                        <p>7) Documents in support of correctness of the Application.</p>
                                        <p>8) Any other document in support of correctness of the particulars mentioned in the application if required.</p>
                                        <p>9) Other certificates of registration in case of other than company, proprietorship or partnership firm like cooperative, Trustees etc.</p>
                                        <p>10) Form I for Assessment of CESS.</p>
                                        <p>11) Form I.</p>
                                    </div>
                                  </div>
                                </div>
                                
                             </div>
                            </div>
                            
                            <div class="tab-pane fade in" id="Post-Operation-Factory-checklist">
                              <h2>Not Applicable</h2>
                            </div>
                            
                            <div class="tab-pane fade in" id="Post-Operation-Shop-checklist">
                             <div class="panel-group Custom_AC_tab" id="shop-checkList">
                                <div class="panel panel-default panel-faq">
                                  <div class="panel-heading">
                                    <h4 class="panel-title"><a data-toggle="collapse" data-parent="#shop-checkList" href="#shop-checkList1" class="collapsed">
                                      Registration under West Bengal Shops and Establishments Act, 1963 <span class="glyphicon pull-right glyphicon-minus"></span></a></h4>
                                  </div>
                                  <div id="shop-checkList1" class="panel-collapse collapse in">
                                    <div class="panel-body">
                                    <p>1) Application in Part I of Form B duly signed.</p>
                                    <p>2) Copy of T.R-7 through which requisite fees, as specified in schedule I of the Rules is to be paid during the process of registration under 
                                          appropriate Head of Account. Or the receipt received from GRIPS having BRN.</p></br>
                                    <p>Others related documents as may be asked to furnish along with the application if required :-</p></br>
                                    <p>1) Copies of appointment letters in Form X, duly received and signed by the employees concerned (to ascertain that all the employees have been 
                                          given the appointment letters).</p>
                                    <p>2) Copy of Latest Trade License (to ascertain the exact location, postal address, nature of business, category of the shop/establishment 
                                          and name of the Proprietor, in case of Proprietorship Concern).The copy of first Trade License application of Trade License 
                                          (to ascertain the date of commencement of business) if available.</p>
                                    <p>3) Copy of Voter Identity Card/ Bank Pass Book/ Aadhar Card as proof of residential address of shop-keeper/employer, in case of Proprietorship 	
                                          Concern.</p>
                                    <p>4) Copy of Registered/Notarial Partnership Deed, in case of Partnership Concern.</p>
                                    <p>5) Copy of Certificate of Incorporation, Memorandum and Article of Association from Registrar of Companies, Ministry of Corporate Affairs, in 	
                                          case of Limited / Private Limited Company.</p>
                                    <p>6) Form 32/ Dir. 12 from Registrar of Companies (R.O.C.), Ministry of Corporate Affairs for appointment of and changes among Directors, in case 
                                          of Ltd. /Pvt. Ltd. Company or other document substantiating the correctness.</p>
                                    <p>7) Form 18 from Registrar of Companies, Ministry of Corporate Affairs as proof of address of registered office, in case of Limited /Private 
                                          Limited Company.</p>
                                    <p>8) A List containing name and residential address of Directors, in case of Limited /Private Limited company, in company letter head.</p>
                                    <p>9) Certificate of Incorporation and Deed of Partnership, in case of Limited Liability Partners Firm.</p>
                                    <p>10) Copy of Tenancy Agreement wherever applicable.</p>
                                    <p>11.) Document in support of allowed nature of business like in case of Non-Banking Financial Institution- RBI Authorisation, in case of 
                                            Insurance agency- IRDA Authorisation etc.</p>
                                    <p>12) Any Other documents to substantiate the correctness of the particulars.</p>
                                    </div>
                                  </div>
                                </div>
                             
                              <div class="panel panel-default panel-faq">
                                  <div class="panel-heading">
                                    <h4 class="panel-title"><a data-toggle="collapse" data-parent="#shop-checkList" href="#shop-checkList2" class="collapsed">
                                    Renewal under West Bengal Shops and Establishments Act, 1963 <span class="glyphicon pull-right glyphicon-plus"></span></a></h4>
                                  </div>
                                  <div id="shop-checkList2" class="panel-collapse collapse">
                                    <div class="panel-body">
                                      <p>1)	Application in Form D along with the Current Registration Certificate.</p>
  									  <p>2) Copy of T.R-7 through which requisite fees, as specified in schedule I of the Rules is to be paid during the process of registration under 
                                            appropriate Head of Account. Or the receipt received from GRIPS having BRN.</p></br>
                                     <p> Others related documents as may be asked to furnish along with the application :-</p></br>
                                     <p>1)	A declaration containing name and date of appointment of all the employees employed as on date of application of renewal (to ascertain 
                                           changes, if any, in respect of employees).</p>
                                     <p>2) Copy of renewed Trade License (to ascertain that the shop/establishment is currently, in operation).</p>
                                    </div>
                                  </div>
                                </div>
                             </div>
                            </div>
                          </div>
                        </div>
                      </div>
                    </div>
                  </div>
                </div>
                <div class="tab-pane" id="sip">
                  <div class="tabbable tabs-left">
                    <ul class="col-sm-2 nav nav-tabs" role="tablist">
                      <li role="presentation" class="active"><a href="#Pre-Operation-sip" aria-controls="home" role="tab" data-toggle="tab">Pre Operation</a></li>
                      <li role="presentation"><a href="#Pre-Establishment-sip" aria-controls="home" role="tab" data-toggle="tab">Pre Establishment</a></li>
                      <li role="presentation"><a href="#Post-Operation-sip" aria-controls="home" role="tab" data-toggle="tab">Others</a></li>
                    </ul>
                    <div class="col-sm-10 tab-content STab_content">
                      <div class="tab-pane active" id="Pre-Operation-sip">
                        <div class="tabbable-panel InTopTab">
                          <div class="tabbable-line">
                            <ul class="nav nav-tabs tabtop  tabsetting">
                              <li class="active"> <a href="#Pre-Operation-Boilers-sip" data-toggle="tab">Directorate of Boilers</a> </li>
                              <li> <a href="#Pre-Operation-Commissionerate-sip" data-toggle="tab">Labour Commissionerate</a> </li>
                              <li> <a href="#Pre-Operation-Factory-sip" data-toggle="tab">Directorate of Factories</a> </li>
                              <li> <a href="#Pre-Operation-Shop-sip" data-toggle="tab">Shops and Establishment</a> </li>
                            </ul>
                          </div>
                          <div class="tab-content InTTab_content">
                            <div class="tab-pane active fade in" id="Pre-Operation-Boilers-sip">
                              <div class="panel-group Custom_AC_tab" id="boiler-sip">
                                <div class="panel panel-default panel-faq">
                                  <div class="panel-heading active-faq">
                                    <h4 class="panel-title"><a data-toggle="collapse" data-parent="#boiler-sip" href="#boiler-sip1">Standard Inspection Procedure for Dry and Thorough Inspection <span class="glyphicon pull-right glyphicon-minus"></span></a></h4>
                                  </div>
                                  <div id="boiler-sip1" class="panel-collapse collapse in">
                                    <div class="panel-body">
                                      <p>a) Checking Registration Number of the Boiler.</p>
                                      <p>b) Carry out thorough visual inspection of boiler inside and outside after proper cleaning.</p>
                                      <p>c) Checking defects like crack, erosion, corrosion, bulging, pitting, deformation of pressure parts etc.</p>
                                      <p>d) Checking of thickness of pressure parts.</p>
                                      <p>e) Checking of Mountings and Fittings.</p>
                                      <p>f) Witnessing Non-destructive Testing if required</p>
                                    </div>
                                  </div>
                                </div>
                                <div class="panel panel-default panel-faq">
                                  <div class="panel-heading">
                                    <h4 class="panel-title"><a data-toggle="collapse" data-parent="#boiler-sip" href="#boiler-sip2">Standard Inspection Procedure for Ground Inspection of Boiler under Registration / Erection <span class="glyphicon pull-right glyphicon-plus"></span></a></h4>
                                  </div>
                                  <div id="boiler-sip2" class="panel-collapse collapse">
                                    <div class="panel-body">
                                      <p>a) Verification of documents of pressure parts with relevant IBR certificates.</p>
                                      <p>b) Verification of the approved drawings and documents.</p>
                                      <p>c) Checking of the facsimile of the makers’ stamp and other identification marking with Form-II or other relevant IBR certificates.</p>
                                      <p>d) Checking of the leading dimension of the pressure parts with the approved drawing.</p>
                                      <p>e) Checking of the general condition of the pressure parts (like denting, deformation, crack pitting etc.).</p>
                                      <p>f) Checking of all Mountings and Fittings with relevant IBR document.</p>
                                    </div>
                                  </div>
                                </div>
                                <div class="panel panel-default panel-faq">
                                  <div class="panel-heading">
                                    <h4 class="panel-title"><a data-toggle="collapse" data-parent="#boiler-sip" href="#boiler-sip3">Standard Inspection Procedure for Material Inspection <span class="glyphicon pull-right glyphicon-plus"></span></a></h4>
                                  </div>
                                  <div id="boiler-sip3" class="panel-collapse collapse">
                                    <div class="panel-body">
                                      <p>a) Verification of the approved drawing corresponding to the material and documents.</p>
                                      <p>b) Checking of the pressure part material with relevant IBR certificate and approved drawing (Name of Part, Material Specification, Heat No., Cast No., Class, Size, Identification Number, Stamping etc.)</p>
                                      <p>c) Checking of leading dimension of the pressure parts with the approved drawing.</p>
                                      <p>d) Checking of the general condition of the pressure parts visually.</p>
                                      <p>e) Selection of Samples for Physical and Chemical testing if required.</p>
                                    </div>
                                  </div>
                                </div>
                                <div class="panel panel-default panel-faq">
                                  <div class="panel-heading">
                                    <h4 class="panel-title"><a data-toggle="collapse" data-parent="#boiler-sip" href="#boiler-sip4">Standard Inspection Procedure for Fit-up / Tack weld Inspection <span class="glyphicon pull-right glyphicon-plus"></span></a></h4>
                                  </div>
                                  <div id="boiler-sip4" class="panel-collapse collapse">
                                    <div class="panel-body">
                                      <p>a) Verification of the approved drawing.</p>
                                      <p>b) Verification of the Welder’s Certificate.</p>
                                      <p>c) Verification of the certificates of the Welding Consumables.</p>
                                      <p>d) Verification of the approval of the Contractor for the particular job.</p>
                                      <p>e) Verification of the approved Welding Procedure Specification.</p>
                                      <p>f) Verification of the satisfactory result of the site Simulation Test.</p>
                                      <p>g) Verification of the satisfactory Check Test result of the pipe/tube/plate.</p>
                                      <p>h) Checking of the Root gap, Weld groove profile, Alignment of the pressure parts to be welded as per approved drawing etc.</p>
                                      <p>i) Ensure weld joint area to be free from rust, scale, oil, grease, crack etc.</p>
                                      <p>j) Check provision for baking of electrode for low hydrogen electrode.</p>
                                      <p>k) Check weld joint identification number.</p>
                                    </div>
                                  </div>
                                </div>
                                <div class="panel panel-default panel-faq">
                                  <div class="panel-heading">
                                    <h4 class="panel-title"><a data-toggle="collapse" data-parent="#boiler-sip" href="#boiler-sip5">Standard Inspection Procedure for Visual Inspection of Welding <span class="glyphicon pull-right glyphicon-plus"></span></a></h4>
                                  </div>
                                  <div id="boiler-sip5" class="panel-collapse collapse">
                                    <div class="panel-body">
                                      <p>a) Visual inspection for checking the general condition of welding (like Spatter, Undercut, Reinforcement, Surface Crack, Leg length, Surface condition etc.)</p>
                                      <p>b) Checking alignment of the pressure parts.</p>
                                      <p>c) Witnessing Magnetic Particle Test, Dye Penetrant Test, Hardness Test etc. if required.</p>
                                      <p>d) Selection of welded joints for Non-destructive Testing like Radiographic Testing, Ultrasonic Testing etc.</p>
                                    </div>
                                  </div>
                                </div>
                                <div class="panel panel-default panel-faq">
                                  <div class="panel-heading">
                                    <h4 class="panel-title"><a data-toggle="collapse" data-parent="#boiler-sip" href="#boiler-sip6">Standard Inspection Procedure for Hydraulic Test <span class="glyphicon pull-right glyphicon-plus"></span> </a> </h4>
                                  </div>
                                  <div id="boiler-sip6" class="panel-collapse collapse">
                                    <div class="panel-body">
                                      <p>a) Verification of the satisfactory Non-destructive Testing report of the welded joints.</p>
                                      <p>b) Verification of the Positive Material Identification (PMI) Report.</p>
                                      <p>c) Verification of the Pressure Parts Calculation approval.</p>
                                      <p>d) Verification of all previous Inspection Reports and PWHT Charts.</p>
                                      <p>e) Checking of calibration certificate of pressure gauge.</p>
                                      <p>f) Witnessing Hydraulic Test carried out as per Indian Boiler Regulations. 1950.</p>
                                      <p>g) Checking of Deflection, Distortion and extension of pressure parts during Hydraulic Test.</p>
                                      <p>h) Thorough Checking of the pressure parts during Hydraulic Test for detecting any leakage or sweating.</p>
                                    </div>
                                  </div>
                                </div>
                                <div class="panel panel-default panel-faq">
                                  <div class="panel-heading">
                                    <h4 class="panel-title"><a data-toggle="collapse" data-parent="#boiler-sip" href="#boiler-sip7">Standard Inspection Procedure for Steam Test of Boiler <span class="glyphicon pull-right glyphicon-plus"></span></a></h4>
                                  </div>
                                  <div id="boiler-sip7" class="panel-collapse collapse">
                                    <div class="panel-body">
                                      <p>a) Verification of the Provisional Order of the Boiler.</p>
                                      <p>b) Witnessing the Steam Test as per Indian Boiler Regulations, 1950.</p>
                                      <p>c) Checking of the Popping Pressure, Reset Pressure, Percentage Blow Down, Accumulation, Lift, Chattering etc. during Steam Test.</p>
                                      <p>d) Checking of the performance of all Mountings and Fittings during Steam Test.</p>
                                    </div>
                                  </div>
                                </div>
                                <div class="panel panel-default panel-faq">
                                  <div class="panel-heading">
                                    <h4 class="panel-title"><a data-toggle="collapse" data-parent="#boiler-sip" href="#boiler-sip8">Standard Inspection Procedure for Final Inspection <span class="glyphicon pull-right glyphicon-plus"></span></a></h4>
                                  </div>
                                  <div id="boiler-sip8" class="panel-collapse collapse">
                                    <div class="panel-body">
                                      <p>a) To carry out thorough visual inspection.</p>
                                      <p>b) Checking dimension and configuration as per approved drawing.</p>
                                      <p>c) Check the Identification Mark on the job.</p>
                                      <p>d) Stamp the pressure part with the Official Seal (Ashoka Emblem).</p>
                                    </div>
                                  </div>
                                </div>
                                <div class="panel panel-default panel-faq">
                                  <div class="panel-heading">
                                    <h4 class="panel-title"><a data-toggle="collapse" data-parent="#boiler-sip" href="#boiler-sip9">Standard Inspection Procedure for Forming Operation (Bending, Forging, Swaging etc.) <span class="glyphicon pull-right glyphicon-plus"></span></a></h4>
                                  </div>
                                  <div id="boiler-sip9" class="panel-collapse collapse">
                                    <div class="panel-body">
                                      <p>a) Witness forming process as per approved drawing.</p>
                                      <p>b) Check starting and finishing temperature of forming operation, R/D ratio, ovality for tube/pipe, forging ratio etc. as per approved drawing.</p>
                                      <p>c) Suggest post forming heat treatment, if required.</p>
                                      <p>d) Select and stamp test pieces for check test.</p>
                                      <p>e) Review heat treatment chart and all testing reports.</p>
                                      <p>f) Carry out visual inspection, hardness, thickness test etc. and measure final dimension as per approved drawing.</p>
                                      <p>g) Check the identification mark and stamp it with the official seal (Ashoka Emblem).</p>
                                    </div>
                                  </div>
                                </div>
                                <div class="panel panel-default panel-faq">
                                  <div class="panel-heading">
                                    <h4 class="panel-title"><a data-toggle="collapse" data-parent="#boiler-sip" href="#boiler-sip10">Standard Procedure for Scrutiny of Drawing <span class="glyphicon pull-right glyphicon-plus"></span></a></h4>
                                  </div>
                                  <div id="boiler-sip10" class="panel-collapse collapse">
                                    <div class="panel-body">
                                      <p><strong>a) Verification of the following reference documents:</strong></p>
                                      <p>i) P&amp;I Diagram</p>
                                      <p>ii) Feed pump characteristic curve</p>
                                      <p>iii) Flexibility analysis report</p>
                                      <p>iv) Copy of existing drawing.</p>
                                      <p>&nbsp;</p>
                                      <p><strong>b) Checking of title block with the following:</strong></p>
                                      <p>&nbsp;</p>
                                      <p>i) Owners / Makers name and address.</p>
                                      <p>ii) Title of drawing</p>
                                      <p>iii) Drawing No. and revision No.</p>
                                      <p>&nbsp;</p>
                                      <p><strong>c) Checking of the following Design data:</strong></p>
                                      <p>&nbsp;</p>
                                      <p>i) Code of design, inspection and testing.</p>
                                      <p>ii) Design Pressure of component.</p>
                                      <p>iii) Design Temperature of component.</p>
                                      <p>iv) Hydraulic test pressure.</p>
                                      <p>v) Related boiler Number.</p>
                                      <p>vi) Boiler design pressure.</p>
                                      <p>vii) Boiler design temperature.</p>
                                      <p>&nbsp;</p>
                                      <p><strong>d) Notes to be checked:</strong></p>
                                      <p>&nbsp;</p>
                                      <p>i) Process of forming</p>
                                      <p>ii) Post forming heat treatment requirement.</p>
                                      <p>iii) Testing of welded joints.</p>
                                      <p>iv) Post weld heat treatment requirement.</p>
                                      <p>v) Location of hydraulic test.</p>
                                      <p>vi) Slope of piping.</p>
                                      <p>vii) Revision Note</p>
                                      <p>&nbsp;</p>
                                      <p><strong>e) Bill of materials to be checked:</strong></p>
                                      <p>&nbsp;</p>
                                      <p>i) Part Number.</p>
                                      <p>ii) Description of part.</p>
                                      <p>iii) Size or Dimension of part (O/D, thickness, length etc.) in mm.</p>
                                      <p>iv) Quantity of material.</p>
                                      <p>v) Class / Rating of part etc.</p>
                                      <p>&nbsp;</p>
                                      <p><strong>f) Other details to be checked: </strong></p>
                                      <p>&nbsp;</p>
                                      <p>i) Design Criteria.</p>
                                      <p>ii) Selection of proper material</p>
                                      <p>iii) Strength calculation.</p>
                                      <p>iv) Part no. marking.</p>
                                      <p>v) Support type and location.</p>
                                      <p>vi) Drainage.</p>
                                      <p>vii) Venting.</p>
                                      <p>viii) Direction of flow.</p>
                                      <p>ix) Reference welding figure no with configuration.</p>
                                    </div>
                                  </div>
                                </div>
                                <div class="panel panel-default panel-faq">
                                  <div class="panel-heading">
                                    <h4 class="panel-title"><a data-toggle="collapse" data-parent="#boiler-sip" href="#boiler-sip11">Standard Inspection Procedure for Approval / Recognition of Manufacturer <span class="glyphicon pull-right glyphicon-plus"></span></a></h4>
                                  </div>
                                  <div id="boiler-sip11" class="panel-collapse collapse">
                                    <div class="panel-body">
                                      <p>a) Scrutiny if Submitted Documents.</p>
                                      <p>b) Inspection of Premises, Verification of Manpower along with their Experience and Machineries.</p>
                                      <p>c) Submission of Report</p>
                                      <p>d) Technical Discussion.</p>
                                      <p>e) Issuance of Recognition Certificate.</p>
                                    </div>
                                  </div>
                                </div>
                                <div class="panel panel-default panel-faq">
                                  <div class="panel-heading">
                                    <h4 class="panel-title"><a data-toggle="collapse" data-parent="#boiler-sip" href="#boiler-sip12">Standard Inspection Procedure for Approval of Erectors <span class="glyphicon pull-right glyphicon-plus"></span></a></h4>
                                  </div>
                                  <div id="boiler-sip12" class="panel-collapse collapse">
                                    <div class="panel-body">
                                      <p>a) Scrutiny if Submitted Documents.</p>
                                      <p>b) Inspection of Premises, Verification of Manpower along with their Experience and Machineries.</p>
                                      <p>c) Submission of Report</p>
                                      <p>d) Technical Discussion.</p>
                                      <p>e) Issuance of Recognition Certificate.</p>
                                    </div>
                                  </div>
                                </div>
                              </div>
                            </div>
                            <div class="tab-pane fade in" id="Pre-Operation-Commissionerate-sip">
                              <h2>Coming Soon</h2>
                            </div>
                            <div class="tab-pane fade in" id="Pre-Operation-Factory-sip">
                              <h2>Coming Soon</h2>
                            </div>
                            <div class="tab-pane fade in" id="Pre-Operation-Shop-sip">
                              <h2>Coming Soon</h2>
                            </div>
                          </div>
                        </div>
                      </div>
                      <div class="tab-pane" id="Pre-Establishment-sip">
                        <div class="tabbable-panel InTopTab">
                          <div class="tabbable-line">
                            <ul class="nav nav-tabs tabtop  tabsetting">
                              <li class="active"> <a href="#Pre-Establishment-Boilers-sip" data-toggle="tab">Directorate of Boilers</a> </li>
                              <li> <a href="#Pre-Establishment-Commissionerate-sip" data-toggle="tab">Labour Commissionerate</a> </li>
                              <li> <a href="#Pre-Establishment-Factory-sip" data-toggle="tab">Directorate of Factories</a> </li>
                              <li> <a href="#Pre-Establishment-Shop-sip" data-toggle="tab">Shops and Establishment</a> </li>
                            </ul>
                          </div>
                          <div class="tab-content InTTab_content">
                            <div class="tab-pane active fade in" id="Pre-Establishment-Boilers-sip">
                              <h2>Not Applicable</h2>
                            </div>
                            <div class="tab-pane fade in" id="Pre-Establishment-Commissionerate-sip">
                              <h2>Coming Soon</h2>
                            </div>
                            <div class="tab-pane fade in" id="Pre-Establishment-Factory-sip">
                              <h2>Coming Soon</h2>
                            </div>
                            <div class="tab-pane fade in" id="Pre-Establishment-Shop-sip">
                              <h2>Coming Soon</h2>
                            </div>
                          </div>
                        </div>
                      </div>
                      <div class="tab-pane" id="Post-Operation-sip">
                        <div class="tabbable-panel InTopTab">
                          <div class="tabbable-line">
                            <ul class="nav nav-tabs tabtop  tabsetting">
                              <li class="active"> <a href="#Post-Operation-Boilers-sip" data-toggle="tab">Directorate of Boilers</a> </li>
                              <li> <a href="#Post-Operation-Commissionerate-sip" data-toggle="tab">Labour Commissionerate</a> </li>
                              <li> <a href="#Post-Operation-Factory-sip" data-toggle="tab">Directorate of Factories</a> </li>
                              <li> <a href="#Post-Operation-Shop-sip" data-toggle="tab">Shops and Establishment</a> </li>
                            </ul>
                          </div>
                          <div class="tab-content InTTab_content">
                            <div class="tab-pane active fade in" id="Post-Operation-Boilers-sip">
                              <div class="panel-group Custom_AC_tab" role="tablist" aria-multiselectable="true">
                                <h2>Not Applicable</h2>
                              </div>
                            </div>
                            <div class="tab-pane fade in" id="Post-Operation-Commissionerate-sip">
                              
                              <div class="panel-group Custom_AC_tab" id="lc-sip">
                               
                               <div class="panel panel-default panel-faq">
                                  <div class="panel-heading">
                                    <h4 class="panel-title"><a data-toggle="collapse" data-parent="#lc-sip" href="#lc-sip1" class="collapsed">
                                    Common SOP for Inspection under various Labour Laws administered by Labour Commissionerate
                                    <span class="glyphicon pull-right glyphicon-minus"></span></a></h4>
                                  </div>
                                  <div id="lc-sip1" class="panel-collapse collapse in">
                                    <div class="panel-body">
                                    <p><strong>General Procedure for Inspection under various Labour Laws administered by Labour Commissionerate:- </strong> </p> <br />
                                   <p> <b>1.</b>a) In  the  present  system,an inspector, under normal circumstances, is  directed by  the appropriate authority through computerised 	
                                       allocation to conduct inspection in establishment(s) selected on the basis of computerised assessment of risk of the establishments in a 	
                                       particular geographical area. </p> 
 
                                <p>b) The inspectors may also be directed to conduct inspection under  particular labour laws to enforce compliance in the form of Special Drive from 
                                time to time.</p>  
                                 
                                <p>c) Sometimes,  on receipt of complaint of violation of labour laws in establishment(s),the inspectors are also required to conduct inspection.</p>  
                                <br /> 
                                <p><b>2.</b>a) Before the inspection, the inspector visits the  URL:http://www.wblc.gov.in and logs in using user credential.</p>     
                                 
                                <p>b) The inspector will land up in his/her dashboard. </p>    
                                 
                                <p>c) The inspector is required to click on the  INSPECTION menu from the Left Hand Menu Bar in his/her dashboard. </p>    
                                 
                                <p>d) The inspector will then click on BLANK INSPECTION NOTE UNDER VARIOUS ACT & PRINT button to take a print out of the inspection notes of the Acts 
                                  and Rules under which he is going to conduct inspection. </p>  
                                 
                                <p>e) He/She is also required to obtain from office a Memo No and Date.</p>   
                                <br /> 
                                <p><b>3.</b> The inspector now will visit the establishment allotted to  him  randomly for conduct of inspection  under  various  labour  laws.  
                                  He/She  will enter  the  premises  with  or  without prior intimation to the employer and operating trade union ,if any.</p>   
                                <br /> 
                                <p><b>4.</b> The inspector may discuss with or interrogate the employees employed the rein in respect of compliance of various provisions of the
                                  labour laws relevant to the establishment.</p>  <br /> 
                                <p><b>5.</b>The inspector will preferably make  entries  in  the  inspection  note,  which  shall  be prepared in duplicate,the following;-   </p>
                                 
                                <p>a) The details of the establishment with nature of business carried on </p>  
                                 
                                <p>b) Categories of employees/workmen   </p>
                                 
                                <p>c) Name of the persons present at the time of inspection    </p>
                                 
                                <p>d) The  name(s)  ,nature  of  work  ,designation  address  etc.  of  the  workers/employees engaged therein </p>  
                                 
                                <p>e) Details of ownership of the establishment</p>   
                                <br /> 
                                
                                <p><b>6.</b> After  obtaining  the  basic  information  about  the  establishment,  the  inspector  will physically  verify  the  compliance  under  
                                  various  provisions  of  the  Acts  and  Rules  made there under including maintenance of Statutory Registers and Filing of Returns etc. In case of 
                                  detection of any infringements, the inspector shall mandatorily mention those in the Inspection Note. </p>
                                 <br /> 
                                <p><b>7.</b> Thus the inspector shall prepare the inspection note ,in duplicate ,and on being satisfied about the completeness of inspection  note, 
                                  shall sign on both the copies and hand over  one  copy  to  the  employer/representative  of  the  employer  with  due  acknowledgement. Normally,  
                                  the employer /owner  of  the  establishment  is/are  requested  to  remove the defects detected during inspection and report compliance thereof 
                                  within a specified date and time as mentioned in the inspection note. </p>
                                 <br />   
                                <p><b>8.</b>  a) The inspector from his/her hand-held device, will now again log in with his/her user credential to land up into his/her dashboard and 
                                 click on the NEW INSPECTION button in the  Left  Menu  Bar.After  selecting  the  relevant  Act  under  which  he/she  has  conducted inspection,a 
                                 blank Inspection Note page will appear. </p>  
                                <p>b) On the basis of information collected and infringements/violations detected during inspection, the inspector is now required to  	
                                    fill up the fields with relevant data in ESTABLISHMENT DETAILS, OWNERSHIP/EMPLOYER DETAILS and INFRINGEMENTS tabs under Online 
                                    inspection note.</p>    
                                <p>c) After verifying all the information with the hard copy of the original inspection note, the inspector will mention the date, 
                                      time and place where compliance could be reported and submit the online inspection note .</p>   
                                <p>d) The inspector then will upload the scanned copy of the original inspection note and click on the SUBMIT & SEND SMS button. This will trigger the 
                                   system to send SMS containing reference  no  in  respect  of  the  inspection  to  the  mobile  no  of  the  employer/owner or representative of 
                                   employer/owner.  </p>  
                                <p>e) The  employer/owner  of  the  establishment  may  click  on  the  View  & Download on the  Homepage of URL:<strong> http://wblc/gov.in</strong> 
                                     and after providing the reference no. may view and   also  download the inspection report.  </p>  
                                  <br />  
                                <p><b>9.</b>The inspector is required to upload the inspection report within 48 hours of conducting such inspection. </p>   
                                   <br /> 
                                <p><b>10.</b>After the submission of inspection note and uploading thereof, the Employer/Owner of  the establishment in which inspection
                                    was conducted will normally report for compliance  on the date,time and place  as mentioned in the inspection note by the inspector. However, 
                                    there are some responses that the employer/owner may take recourse to based on which the inspector will take further action;-  </p>  
                                 
                                     <p> <p>  </p>  
                                     <p> <strong>A.  The Employer/Owner reports for compliance:- </strong> <br />  
                                          i)The employer /owner removes the defects fully:-  
                                         Action to be taken by the Inspector:-   
                                         The  inspector will  initiate  procedure for  approval from the appropriate authority for Let-off of the defects/infringements which have been 										  complied with. A system  generated proposal for let-off containing a comprehensive report generated by the inspector using his/her user 		
                                          credential may be forwarded online to the appropriate  authority along with all the necessary attachments. The Appropriate Authority, after 
                                          verifying the  report of the inspector may approve the Let-off or may send back for further correction or further action.  </p>  
                                            
                                    <p> ii) The employer /owner remove the defects partially:-   
                                         Action to be taken by the Inspector:-   
                                       <p>    a)The inspector may allow further time for compliance. </p>   
                                       <p>    b)The inspector will initiate procedure for approval from the appropriate authority for Let-off of the defects/infringements which have 	
                                                been complied with. A system  generated proposal for let-off containing a comprehensive report generated by the inspector using his/her 											    user credential may be forwarded online to the appropriate authority along with all the necessary attachments.  The Appropriate 
                                                Authority, after verifying the  report of the inspector may approve the Let-off or may send back for further correction or further 
                                                action.  </p>  
                                       <p>    c)The  inspector  will simultaneously initiate procedure for approval from the appropriate authority for launching court–case in respect 	
                                               of defects/infringements for which compliance has not been received from the employer/owner even after providing reasonable 
                                               opportunity. </p>   
                                        <p>   d) After  receipt  of  approval  from  the  appropriate  authority,  the  inspector shall generate computerised court case challan,take 	
                                                 print–out of the same and launch the case in the appropriate court.  </p> 
                                            
                                   <p>  <strong>B.  The Employer/Owner does not report for compliance:-  </strong>  </p>
                                      <p>   Action to be taken by the inspector:-  
                                       <p>    i)In this  situation the  inspector will log in to the system  and select the particular inspection  from  the  INSPECTION  LIST  and  
                                                issue  a  system  generated  show-cause notice  which  will  be  signed  and  uploaded  by  the  inspector  and  subsequently  be   
                                                forwarded to the Employer/Owner. The Show-cause notice may be verified  by the employer/owner from the dashboard.  </p>  
                                            
                                 
                                <p><strong>Response of the employer/owner after the receipt of Show-cause Notice:- </strong>  </p> 
                                   
                                <p><strong>i)The employer /owner removes the defects fully:- </strong>  </p> 
                                <p> Action to be taken by the Inspector:-   
                                    The  inspector will  initiate  procedure for approval from the appropriate authority for Let-off of the defects/infringements which have been 	
                                    complied with. A system generated proposal for let-off containing a comprehensive report generated by the inspector using his/her user credential 
                                    may be forwarded online to the appropriate authority along with all the necessary attachments. The Appropriate Authority, after verifying the  
                                    report of the inspector may approve the Let-off or may send back for further correction or further action. </p>  
                                   
                                 <p><strong>ii) The employer /owner remove the defects partially:- </strong> </p> 
                                      <p>  Action to be taken by the Inspector:- 
                                        <p>a)The inspector may allow further time for compliance. </p>   
                                        <p>b)The inspector will initiate procedure for approval from the appropriate authority  for Let-off of the defects/infringements which have 	
                                         been complied with. A system generated proposal for let-off containing a comprehensive report generated by the inspector using his/her user 
                                         credential may be forwarded online to the appropriate authority along with all the necessary attachments. The Appropriate Authority, after 
                                         verifying the report of the inspector may approve the Let-off or may send back for further 
                                        correction or further action.   </p> 
                                        <p>c)The inspector will simultaneously initiate procedure in the form of a proposal for approval  from  the  appropriate  authority  for  
                                             launching  court–case  in  respect  of defects/infringements  for  which  compliance  has  not  been  received  from  the employer/owner 
                                             even after providing reasonable opportunity. The Appropriate Authority, after verifying the report of the inspector may approve onlilne  
                                             the  proposal for launching of court–case  or  may  send  back for further correction or further action. </p> 
                                        <p>d) After receipt of approval from the appropriate authority, the inspector shall  log  in to land up in his/her dashboard and generate 
                                        computerised court case challan, take print–out of the same and launch the case in the appropriate court. </p> 
                                           
                                        <p><strong>iii) The employer/owner does not make a response to the Show-cause Notice:- </strong> </p>  
                                        <p>a) The inspector will initiate  procedure in the form of a proposal for approval from  the  appropriate authority for launching 
                                         court–case in respect of defects/infringements  for  which   compliance  has  not  been  received  from  the employer/owner even after 
                                         providing reasonable opportunity.   </p> 
                                        <p>b) The Appropriate  Authority,  after  verifying  the  report  of  the  inspector  may approve  online the proposal for launching  of  												                                              court–case  or  may  send  back  for further correction or further action.   </p> 
                                        <p>c) After receipt of approval from the appropriate authority, the inspector shall log in to land up in his/her dashboard and generate 	
                                             computerised court case challan, take print–out of the same and launch the case in the appropriate court.   </p> 
                                    </div>
                                  </div>
                                </div>
                               
                               </div>
                              
                            </div>
                            <div class="tab-pane fade in" id="Post-Operation-Factory-sip">
                              <h2>Coming Soon</h2>
                            </div>
                            <div class="tab-pane fade in" id="Post-Operation-Shop-sip">
                              <h2>Coming Soon</h2>
                            </div>
                          </div>
                        </div>
                      </div>
                    </div>
                  </div>
                </div>
                <div class="tab-pane" id="checklist-for-inspection">
                  <div class="tabbable tabs-left">
                    <ul class=" col-sm-2 nav nav-tabs" role="tablist">
                      <li role="presentation" class="active"><a href="#Pre-Operation-checklist-for-inspection" aria-controls="home" role="tab" data-toggle="tab">Pre Operation</a></li>
                      <li role="presentation"><a href="#Pre-Establishment-checklist-for-inspection" aria-controls="home" role="tab" data-toggle="tab">Pre Establishment</a></li>
                      <li role="presentation"><a href="#Post-Operation-checklist-for-inspection" aria-controls="home" role="tab" data-toggle="tab">Others</a></li>
                    </ul>
                    <div class="col-sm-10 tab-content STab_content">
                      <div class="tab-pane active" id="Pre-Operation-checklist-for-inspection">
                        <div class="tabbable-panel InTopTab">
                          <div class="tabbable-line">
                            <ul class="nav nav-tabs tabtop  tabsetting">
                              <li class="active"> <a href="#Pre-Operation-Boilers-checklist-for-inspection" data-toggle="tab">Directorate of Boilers</a> </li>
                              <li> <a href="#Pre-Operation-Commissionerate-checklist-for-inspection" data-toggle="tab">Labour Commissionerate</a> </li>
                              <li> <a href="#Pre-Operation-Factory-checklist-for-inspection" data-toggle="tab">Directorate of Factories</a> </li>
                              <li> <a href="#Pre-Operation-Shop-checklist-for-inspection" data-toggle="tab">Shops and Establishment</a> </li>
                            </ul>
                          </div>
                          <div class="tab-content InTTab_content">
                            <div class="tab-pane active fade in" id="Pre-Operation-Boilers-checklist-for-inspection">
                              <div class="panel-group Custom_AC_tab" id="boiler-checklist-for-inspection">
                                <div class="panel panel-default panel-faq">
                                  <div class="panel-heading active-faq">
                                    <h4 class="panel-title"><a data-toggle="collapse" data-parent="#boiler-checklist-for-inspection" href="#boiler-checklist-for-inspection1">Registration of Boilers under The Boilers Act, 1923 <span class="glyphicon pull-right glyphicon-minus"></span></a></h4>
                                  </div>
                                  <div id="boiler-checklist-for-inspection1" class="panel-collapse collapse in">
                                    <div class="panel-body">
                                      <p><strong>a)	Check List for Registration of Boiler</strong></p>
                                      <p>i).	Application for registration of the Boilers addressed to the Director of Boilers, W.B</p>
                                      <p>ii).	Registration Folder containing form-II, form-III and form-IVA of IBR, original drawings of boiler and other relevant documents.</p>
                                      <p>iii).	Requisite fees for registration of the boiler in the head of accounts: “0230-00-103-001-14” – Service fees(14) online by IFMS-GRIPS portal in www.wbfin.nic.in.</p>
                                      <p>iv).	Requisite T.A for inspection of the boiler in the head of accounts: “0230-00-103-002-27” – Other Receipts(27) online by IFMS-GRIPS portal in www.wbfin.nic.in.</p>
                                      <p>v).	Original Certificates of all Mountings and Fittings.</p>
                                      <p><strong>b)	Check List for approval of Drawings </strong></p>
                                      <p>i).	Application for approval of drawing.</p>
                                      <p>ii).	Three copies of all relevant drawings.</p>
                                      <p>iii).	Requisite fees for scrutiny of drawings in the head of accounts:“0230-00-103-001-14” – Service fees(14) online by IFMS-GRIPS portal in www.wbfin.nic.in</p>
                                      <p>iv).	All relevant reference drawings.</p>
                                      <p>v).	Flexibility analysis report, if required.</p>
                                      <p>vi).	Valve schedule</p>
                                      <p>vii).	Pressure parts calculation.</p>
                                      <p>viii).	P & I Diagram of the whole system.</p>
                                      <p>ix).	Feed pump characteristic curve.</p>
                                      <p>x).	Copy of Existing Drawings.</p>
                                      <p><strong>c)	Check List for submission of Form-IIIA for Identification Number of Pipe Lines</strong></p>
                                      <p>i).	Application for approval of Form-IIIA.</p>
                                      <p>ii).	Submission of requisite fees for inspection of pipe lines in the head of accounts: “0230-00-103-001-14” – Service fees(14) online by IFMS-GRIPS portal in www.wbfin.nic.in.</p>
                                      <p>iii).	Submission of Form-IIIA for steam pipe line duly filled in.</p>
                                      <p>iv).	Submission of Form-IIIA for feed pipe lines duly filled in.</p>
                                      <p>v).	copy of all relevant drawings of steam and feed pipe lines.</p>
                                      <p>vi).	Copy of Drawing approval letter.</p>
                                      <p>vii).	IBR certificates of all components of pipes and fittings ( like- Form IIIA, Form-IIIB, Form IIIC, Form-IIID, Form-IIIE, Form-IIIF, Form-IIIG etc.)</p>
                                      <p>viii).	Copy of Contractor’s approval letter.</p>
                                      <p>ix).	All NDT reports.</p>
                                      <p>x).	Post weld heat treatment report and stress relieving charts</p>
                                      <p>xi).	PMI report.</p>
                                      <p>xii).	Copy of all inspection reports of pipe lines under erection.</p>
                                      <p><strong>d)	Check List for Erection of Boiler</strong></p>
                                      <p>i).	Application for erection of the Boilers addressed to the Director of Boilers, W.B</p>
                                      <p>ii).	Registration Folder containing form-II, form-III and form-IVA of IBR, original drawings of boiler and other relevant documents.</p>
                                      <p>iii).	Requisite fees for erection of the boiler in the head of accounts: “0230-00-103-001-14” – Service fees(14) online by IFMS-GRIPS portal in www.wbfin.nic.in.</p>
                                      <p>iv).	Requisite T.A for inspection of the boiler in the head of accounts: “0230-00-103-002-27” – Other Receipts(27) online by IFMS-GRIPS portal in www.wbfin.nic.in.</p>
                                      <p>v).	Original Certificates of all Mountings and Fittings.</p>
                                    </div>
                                  </div>
                                </div>
                                <div class="panel panel-default panel-faq">
                                  <div class="panel-heading">
                                    <h4 class="panel-title"><a data-toggle="collapse" data-parent="#boiler-checklist-for-inspection" href="#boiler-checklist-for-inspection2">Renewal of Certificate of Boilers under The Boilers Act, 1923 <span class="glyphicon pull-right glyphicon-plus"></span></a></h4>
                                  </div>
                                  <div id="boiler-checklist-for-inspection2" class="panel-collapse collapse">
                                    <div class="panel-body">
                                      <p><strong>a)	Check List for Renewal of Certificate of boiler</strong></p>
                                      <p>i).	Application for renewal of certificate along with form-B No.1 duly filled in.</p>
                                      <p>ii).	Requisite fees for inspection of boiler in the head of accounts: “0230-00-103-001-14” – Service fees (14) online by IFMS-GRIPS portal in www.wbfin.nic.in</p>
                                      <p>iii).	Requisite Travelling Allowance in the head of accounts: “0230-00-103-002-27” – Other Receipts (27) online by IFMS-GRIPS portal in www.wbfin.nic.in</p>
                                      <p><strong>b)	Check List for Remnant Life Assessment of Boiler</strong></p>
                                      <p>i).	Application for RLA study.</p>
                                      <p>ii).	Submission of scheme of RLA for the proposed boiler.</p>
                                      <p>iii).	Submission of requisite fees for inspection of boiler in the head of accounts: “0230-00-103-001-14” – Service fees(14) online by IFMS-GRIPS portal in www.wbfin.nic.in</p>
                                      <p>iv).	Requisite T.A for inspection of the boiler in the head of accounts:“0230-00-103-002-27” – Other Receipts(27) online by IFMS-GRIPS portal in www.wbfin.nic.in</p>
                                      <p>v).	Submission of documents of the approved RLA organization who will conduct the RLA studies.</p>
                                    </div>
                                  </div>
                                </div>
                                <div class="panel panel-default panel-faq">
                                  <div class="panel-heading">
                                    <h4 class="panel-title"><a data-toggle="collapse" data-parent="#boiler-checklist-for-inspection" href="#boiler-checklist-for-inspection3">Approval of Boiler manufacture & Renewal there of <span class="glyphicon pull-right glyphicon-plus"></span></a></h4>
                                  </div>
                                  <div id="boiler-checklist-for-inspection3" class="panel-collapse collapse">
                                    <div class="panel-body">
                                      <p><strong>a)	Check List for Approval and Renewal of Manufacturer</strong></p>
                                      <p>i).	Forwarding Letter by the applicant.</p>
                                      <p>ii).	Application to Director along with duly filled Form in prescribed format.</p>
                                      <p>iii).Copy of Trade License, Lease Deed (if applicable), Tenancy Deed (if applicable), and Photo Identity Proof.</p>
                                      <p>iv).	List of Machineries as mentioned in the Form.</p>
                                      <p>v).	List of Technical Personnel along with experience.</p>
                                    </div>
                                  </div>
                                </div>
                                <div class="panel panel-default panel-faq">
                                  <div class="panel-heading">
                                    <h4 class="panel-title"><a data-toggle="collapse" data-parent="#boiler-checklist-for-inspection" href="#boiler-checklist-for-inspection4">Approval of Boiler Erector & Renewal there of <span class="glyphicon pull-right glyphicon-plus"></span></a></h4>
                                  </div>
                                  <div id="boiler-checklist-for-inspection4" class="panel-collapse collapse">
                                    <div class="panel-body">
                                      <p><strong>a)	Check List for Approval and Renewal of Erector</strong></p>
                                      <p>i).	Forwarding Letter by the applicant.</p>
                                      <p>ii).	Application to Director along with duly filled Form in prescribed format.</p>
                                      <p>iii).	Copy of Trade License, Lease Deed (if applicable), Tenancy Deed (if applicable), and Photo Identity Proof.</p>
                                      <p>iv).	List of Machineries as mentioned in the Form.</p>
                                      <p>v).	 List of Technical Personnel along with experience.</p>
                                    </div>
                                  </div>
                                </div>
                              </div>
                            </div>
                            <div class="tab-pane fade in" id="Pre-Operation-Commissionerate-checklist-for-inspection">
                              <h2>Coming Soon</h2>
                            </div>
                            <div class="tab-pane fade in" id="Pre-Operation-Factory-checklist-for-inspection">
                              <h2>Coming Soon</h2>
                            </div>
                            <div class="tab-pane fade in" id="Pre-Operation-Shop-checklist-for-inspection">
                              <h2>Coming Soon</h2>
                            </div>
                          </div>
                        </div>
                      </div>
                      <div class="tab-pane" id="Pre-Establishment-checklist-for-inspection">
                        <div class="tabbable-panel InTopTab">
                          <div class="tabbable-line">
                            <ul class="nav nav-tabs tabtop  tabsetting">
                              <li class="active"> <a href="#Pre-Establishment-Boilers-checklist-for-inspection" data-toggle="tab">Directorate of Boilers</a> </li>
                              <li> <a href="#Pre-Establishment-Commissionerate-checklist-for-inspection" data-toggle="tab">Labour Commissionerate</a> </li>
                              <li> <a href="#Pre-Establishment-Factory-checklist-for-inspection" data-toggle="tab">Directorate of Factories</a> </li>
                              <li> <a href="#Pre-Establishment-Shop-checklist-for-inspection" data-toggle="tab">Shop and Establishment</a> </li>
                            </ul>
                          </div>
                          <div class="tab-content InTTab_content">
                            <div class="tab-pane active fade in" id="Pre-Establishment-Boilers-checklist-for-inspection">
                              <h2>Not Applicable</h2>
                            </div>
                            <div class="tab-pane fade in" id="Pre-Establishment-Commissionerate-checklist-for-inspection">
                              <h2>Coming Soon</h2>
                            </div>
                            <div class="tab-pane fade in" id="Pre-Establishment-Factory-checklist-for-inspection">
                              <h2>Coming Soon</h2>
                            </div>
                            <div class="tab-pane fade in" id="Pre-Establishment-Shop-checklist-for-inspection">
                              <h2>Coming Soon</h2>
                            </div>
                          </div>
                        </div>
                      </div>
                      <div class="tab-pane" id="Post-Operation-checklist-for-inspection">
                        <div class="tabbable-panel InTopTab">
                          <div class="tabbable-line">
                            <ul class="nav nav-tabs tabtop  tabsetting">
                              <li class="active"> <a href="#Post-Operation-Boilers-checklist-for-inspection" data-toggle="tab">Directorate of Boilers</a> </li>
                              <li> <a href="#Post-Operation-Commissionerate-checklist-for-inspection" data-toggle="tab">Labour Commissionerate</a> </li>
                              <li> <a href="#Post-Operation-Factory-checklist-for-inspection" data-toggle="tab">Directorate of Factories</a> </li>
                              <li> <a href="#Post-Operation-Shop-checklist-for-inspection" data-toggle="tab">Shop and Establishment</a> </li>
                            </ul>
                          </div>
                          <div class="tab-content InTTab_content">
                            <div class="tab-pane active fade in" id="Post-Operation-Boilers-checklist-for-inspection">
                              <div class="panel-group Custom_AC_tab" role="tablist" aria-multiselectable="true">
                                <h2>Not Applicable</h2>
                              </div>
                            </div>
                            <div class="tab-pane fade in" id="Post-Operation-Commissionerate-checklist-for-inspection">
                              <h2>Coming Soon</h2>
                            </div>
                            <div class="tab-pane fade in" id="Post-Operation-Factory-checklist-for-inspection">
                              <h2>Coming Soon</h2>
                            </div>
                            <div class="tab-pane fade in" id="Post-Operation-Shop-checklist-for-inspection">
                              <h2>Coming Soon</h2>
                            </div>
                          </div>
                        </div>
                      </div>
                    </div>
                  </div>
                </div>
              </div>
            </div>
            <!--Main_tab_content---> 
          </div>
          <!--Main_tab---> 
        </div>
        <!--end_row--> 
        
      </div>
    </div>
  </div>
  <!--end body here--> 
  
</div>

<!-- jQuery (necessary for Bootstrap's JavaScript plugins) -->
<?php /*?><script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.3/jquery.min.js"></script> 
<script src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/js/textresize.js"></script> 
<!-- Include all compiled plugins (below), or include individual files as needed --> 
<script src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/js/bootstrap.min.js"></script> 
<script src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/js/news.js"></script> 
<script src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/js/news2.js"></script> 
<script src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/js/owl.carousel.min.js"></script> 
<script src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/js/jquery.scrollUp.js"></script> 
<script src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/js/script.js"></script> 
<script type="text/javascript" src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/js/tickerme.min.js"></script> 
<script src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/js/wow.min.js"></script> 

<!----slid4e_menu-----> 
<script src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/js/jasny-bootstrap.min.js"></script> 
<script src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/js/main.js"></script> 

<!-- jQuery --> 
<script src="<?php print $base_path ?>sites/all/modules/dashboard/vendors/jquery/dist/jquery.min.js"></script> 
<!-- Bootstrap --> 
<script src="<?php print $base_path ?>sites/all/modules/dashboard/vendors/bootstrap/dist/js/bootstrap.min.js"></script> 
<!-- FastClick --> 
<script src="<?php print $base_path ?>sites/all/modules/dashboard/vendors/fastclick/lib/fastclick.js"></script> 
<!-- NProgress --> 
<script src="<?php print $base_path ?>sites/all/modules/dashboard/vendors/nprogress/nprogress.js"></script> 
<!-- Chart.js --> 
<script src="<?php print $base_path ?>sites/all/modules/dashboard/vendors/Chart.js/dist/Chart.min.js"></script> <?php */?>
<!-- gauge.js --> 
<script src="<?php print $base_path ?>sites/all/modules/dashboard/vendors/gauge.js/dist/gauge.min.js"></script> 
<!-- bootstrap-progressbar -->
<?php /*?><script src="<?php print $base_path ?>sites/all/modules/dashboard/vendors/bootstrap-progressbar/bootstrap-progressbar.min.js"></script> 
<!-- iCheck --> 
<script src="<?php print $base_path ?>sites/all/modules/dashboard/vendors/iCheck/icheck.min.js"></script> 
<!-- Skycons --> 
<script src="<?php print $base_path ?>sites/all/modules/dashboard/vendors/skycons/skycons.js"></script> 
<!-- Flot -->
<script src="<?php print $base_path ?>sites/all/modules/dashboard/vendors/Flot/jquery.flot.js"></script> 
<script src="<?php print $base_path ?>sites/all/modules/dashboard/vendors/Flot/jquery.flot.pie.js"></script> 
<script src="<?php print $base_path ?>sites/all/modules/dashboard/vendors/Flot/jquery.flot.time.js"></script> 
<script src="<?php print $base_path ?>sites/all/modules/dashboard/vendors/Flot/jquery.flot.stack.js"></script> 
<script src="<?php print $base_path ?>sites/all/modules/dashboard/vendors/Flot/jquery.flot.resize.js"></script> 
<!-- Flot plugins --> 
<script src="<?php print $base_path ?>sites/all/modules/dashboard/vendors/flot.orderbars/js/jquery.flot.orderBars.js"></script> 
<script src="<?php print $base_path ?>sites/all/modules/dashboard/vendors/flot-spline/js/jquery.flot.spline.min.js"></script> 
<script src="<?php print $base_path ?>sites/all/modules/dashboard/vendors/flot.curvedlines/curvedLines.js"></script> 
<!-- DateJS --> 
<script src="<?php print $base_path ?>sites/all/modules/dashboard/vendors/DateJS/build/date.js"></script> 
<!-- JQVMap --> 
<script src="<?php print $base_path ?>sites/all/modules/dashboard/vendors/jqvmap/dist/jquery.vmap.js"></script> 
<script src="<?php print $base_path ?>sites/all/modules/dashboard/vendors/jqvmap/dist/maps/jquery.vmap.world.js"></script> 
<script src="<?php print $base_path ?>sites/all/modules/dashboard/vendors/jqvmap/examples/js/jquery.vmap.sampledata.js"></script> 
<!-- bootstrap-daterangepicker --> <?php */?>
<script src="<?php print $base_path ?>sites/all/modules/dashboard/vendors/moment/min/moment.min.js"></script> 
<script src="<?php print $base_path ?>sites/all/modules/dashboard/vendors/bootstrap-daterangepicker/daterangepicker.js"></script> 

<!-- Custom Theme Scripts --> 
<script src="<?php print $base_root.$base_path?>sites/all/modules/dashboard/build/js/custom.min.js"></script> 

<!-- sticky header starts--> 
<script>
$(window).scroll(function() {
    if ($(this).scrollTop() > 1){  
        $('.header').addClass("sticky");
    }
    else{
        $('.header').removeClass("sticky");
    }
});
</script> 
<!-- sticky header ends--> 

<!-- js for the tooltip starts--> 
<script>
$(document).ready(function(){
    $('[data-toggle="tooltip"]').tooltip();  
	
	$('.boxbgcolor1sub').each(function() {
        animationHover(this, 'bounce');
		animationClick(this, 'bounce');
    }); 
	
});

</script> 

<!-- js for the tooltip ends--> 

<script>
// Carousel Auto-Cycle
  $(document).ready(function() {
    $('.carousel').carousel({
      interval: 1000
    })
	
	 $('.carousel1').carousel({
      interval: 3000
    })
	
	
	$('.toggle').click(function (event) {
        event.preventDefault();
        var target = $(this).attr('href');
        $(target).toggleClass('hidden show');
	 });
	
  });
  
  
  
$(function() {
	var Accordion = function(el, multiple) {
		this.el = el || {};
		this.multiple = multiple || false;

		// Variables privadas
		var links = this.el.find('.link');
		// Evento
		links.on('click', {el: this.el, multiple: this.multiple}, this.dropdown)
	}

	Accordion.prototype.dropdown = function(e) {
		var $el = e.data.el;
			$this = $(this),
			$next = $this.next();

		$next.slideToggle();
		$this.parent().toggleClass('open');

		if (!e.data.multiple) {
			$el.find('.submenu').not($next).slideUp().parent().removeClass('open');
		};
	}	

	var accordion = new Accordion($('#accordion'), false);
	var accordion = new Accordion($('#accordion1'), true);
});

  
</script> 
<script type="text/javascript">
jQuery('.collapse').on('shown.bs.collapse', function(){
jQuery(this).parent().find(".glyphicon-plus").removeClass("glyphicon-plus").addClass("glyphicon-minus");
}).on('hidden.bs.collapse', function(){ 
jQuery(this).parent().find(".glyphicon-minus").removeClass("glyphicon-minus").addClass("glyphicon-plus");
});
</script>

<script>
var hoursleft1 = 48;
var minutesleft1 = 00; //give minutes you wish
var secondsleft1 = 00; // give seconds you wish
var finishedtext1 = "Countdown finished!";
var end2;
if(localStorage.getItem("end2")) {
end2 = new Date(localStorage.getItem("end2"));
} else {
end2 = new Date('<?php echo date( 'Y-m-d H:i:s', $data->created )?>');
end2.setHours(end2.getHours()+hoursleft1);
end2.setMinutes(end2.getMinutes()+minutesleft1);
end2.setSeconds(end2.getSeconds()+secondsleft1);

}

var counter1 = function () {
var now1 = new Date();
var diff1 = end2 - now1;

diff1 = new Date(diff1);

    var milliseconds1 = parseInt((diff1%1000)/100);
    var sec1 = parseInt((diff1/1000)%60); 
	var mins1 = parseInt((diff1/(1000*60))%60); 
	var hours1 = parseInt((diff1/(1000*60*60))%60); 
   // var hours = parseInt((diff/(1000*60*60))%24); alert ("hours" + hours );

if (hours1 < 10) { 
    hours1 = "0" + hours1;
}  
if (mins1 < 10) {
    mins1 = "0" + mins1;
}
if (sec1 < 10) { 
    sec1 = "0" + sec1;
}   
if(now1 >= end2) {     
    clearTimeout(interval1);
   // localStorage.setItem("end", null);
     localStorage.removeItem("end2");
     localStorage.clear();
    document.getElementById('divCountertemp').innerHTML = finishedtext1;
     //if(confirm("TIME UP!"))
	 alert("TIME UP!");
     //window.location.href= "timeup.php";
	  window.location.href= "tmpcountdownfinish";
} else {
    var value1 = hours1 + ":" + mins1 + ":" + sec1;
    localStorage.setItem("end2", end2);
    document.getElementById('divCountertemp').innerHTML = value1;
	//document.getElementById('timer1').disabled = true;
	//alert('first');
}
}
var interval1 = setInterval(counter1, 1000);
</script>
