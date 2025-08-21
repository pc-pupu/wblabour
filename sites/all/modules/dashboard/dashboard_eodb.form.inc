<?php

function dashboard_eodb_form($form, &$form_state) {
	
	global $base_root,$base_path,$user;
	//drupal_add_css(drupal_get_path('module', 'dashboard') . '/vendors/font-awesome/css/font-awesome.min.css');
	//drupal_add_css(drupal_get_path('module', 'dashboard') . '/vendors/font-awesome/css/font-awesome.css');
	drupal_add_css(drupal_get_path('module', 'dashboard') . '/build/css/tmpdashboard.css');
	drupal_add_css(drupal_get_path('module', 'dashboard') . '/build/css/custom.css');
	drupal_add_css(drupal_get_path('module', 'dashboard') . '/build/css/zozo.tabs.min.css');
	drupal_add_css(drupal_get_path('module', 'dashboard') . '/build/css/zozo.tabs.flat.min.css');
    drupal_add_js(drupal_get_path('module', 'dashboard') . '/build/js/zozo.tabs.min.js');
	//drupal_add_js(drupal_get_path('module', 'dashboard') . '/vendors/bootstrap/dist/js/bootstrap.min.js');
	drupal_add_js(drupal_get_path('module', 'dashboard') . '/build/js/extra.js');
  	
	$form['form_begin'] = array( 
		'#prefix' => '<div class="whitebg2">
						<div class="about_body">
							<div class="container">
								<div class="row">
									<div class="col-sm-12 col-md-12">
										<h3 style="font-size: 26px;color: black;font-weight: 600;">Online dashboard for EODB e-services w.e.f <b style="color: 										#0d6e94">1st November, 2020</b></h3>',
		'#suffix' => '' ,
	);
	
 $form['top_header_begin'] = array(
 		'#prefix' => '<div class="main-tab">
                            <ul>
                                <li><a>Directorate of Boilers</a></li>
                                <li><a>Labour Commissionerate</a></li>
                                <li><a>Directorate of Factories</a></li>
                            </ul>' ,
		'#suffix' => '',
 	);	
	
  $form['sub_header_boiler_begin'] = array(
 		'#prefix' => ' <div><div>
                                    <div class="sub-header">
                                        <ul>
                                            <li><a><span>Registration of</span> Boiler / Economiser</a></li>
                                            <li><a><span>Renewal of Certificate of</span> Boiler / Economiser</a></li>
                                            <li><a><span>Approval of Certificate of</span> Boiler Manufacturer [Registration]</a></li>
                                            <li><a><span>Approval of Certificate of </span>Boiler Manufacturer [Renewal]</a></li>
                                        </ul>' ,
		'#suffix' => '',
 	);
	
 
  $form['boiler_reg_begin'] = array(
 		'#prefix' => '<div> <div>
                                                <div class="nested-tabs">
                                                    <div>
                                                            <table class="table" style="width:100%;" cellspacing="0" cellpadding="0" border="1">
	<thead>
		<tr>
			<th>Particulars</th>
			<th>Details</th>
		</tr>
	</thead>
	<tbody>
		<tr>
			<td>Time Limit (in days) prescribed as per the Public Service Guarantee Act [To issue the certificate (Form V) to run the boiler after completion of all satisfactory inspection]</td>
			<td>15</td>
		</tr>
		<tr>
			<td>Total Number of applications received</td>
			<td>4</td>
		</tr>
		<tr>
			<td>Total Number of applications approved</td>
			<td>4</td>
		</tr>
		<tr>
			<td>Average time taken to obtain registration</td>
			<td>2.25</td>
		</tr>
		<tr>
			<td>Median time taken to obtain registration</td>
			<td>Same Day</td>
		</tr>
		<tr>
			<td>Minimum time taken to obtain registration</td>
			<td>Same Day</td>
		</tr>
		<tr>
			<td>Maximum time taken to obtain registration</td>
			<td>6</td>
		</tr>' ,
		'#suffix' => '',
 	);	
	
 $form['boiler_reg_end'] = array(
 		'#prefix' => '' ,
		'#suffix' => '</tbody>
	</table>
                                                    </div>
                                                </div>
                                            </div><div>',
 	);			
	
  
  $form['sub_header_end'] = array(
 		'#prefix' => '' ,
		'#suffix' => '</div></div></div>',
 	);	

		
  $form['top_header_end'] = array(
 		'#prefix' => '' ,
		'#suffix' => '</div>',
 	);	
	
 $form['form_end'] = array( 
  '#prefix' => '',
  '#suffix' => '</div>
                </div>
            </div>
        </div>
    </div>',
 );
	  
  return  $form;
	
}
