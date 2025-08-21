<?php
function daily_session($form, &$form_state){
	global $base_root,$base_path,$user;
	drupal_add_js('code/highstock.js');
	//drupal_add_js('code/highcharts.js');
	drupal_add_js('code/modules/exporting.js');
	drupal_add_js('code/modules/export-data.js');
	//drupal_add_js(drupal_get_path('module', 'news') . '/mychart.js');
	
	$form['#attributes']['class'][] = 'sky-form custom-form-main';
	$form = array();
	
	
	
	/*$query = db_query("select count(*) as total_user,to_date(to_char(to_timestamp(created),'YYYY-MM-DD'),'YYYY-MM-DD') as creation_date,ldu.ldapplicationflag
from 
users u
inner join ld_users_details ldu on u.uid=ldu.uid
where ldu.ldapplicationflag is not null
group by to_date(to_char(to_timestamp(created),'YYYY-MM-DD'),'YYYY-MM-DD'),ldu.ldapplicationflag
order by to_date(to_char(to_timestamp(created),'YYYY-MM-DD'),'YYYY-MM-DD')");*/

  $query = db_query("select count(*) as total_user,date_part('month',to_timestamp(created)) as months, date_part('year',to_timestamp(created)) as years,  date_part('month',to_timestamp(created))||'-'||date_part('year',to_timestamp(created)) as creation_month,ldu.ldapplicationflag
from 
users u
inner join ld_users_details ldu on u.uid=ldu.uid
where ldu.ldapplicationflag is not null
group by  months,years,date_part('month',to_timestamp(created))||'-'||date_part('year',to_timestamp(created)),ldu.ldapplicationflag
order by  years asc ,months asc,ldapplicationflag");

	$userData = $query->fetchAll();
	$my_new_arr = array();
	
	$creation_date_arr1 = "";
	$creation_date_arr = "";
	$temp_total_user = "";
	$per_total_user = "";
	$p = 0;
	$t = 0;
	
	//print_r($userData);
	//exit;
	foreach($userData as $key=>$val){
		if($userData[$key]->creation_month!="" && $userData[$key]->creation_month == $userData[$key+1]->creation_month){
			$my_new_arr['creation_month'][] = $userData[$key]->creation_month;
			if($userData[$key]->ldapplicationflag == 0){
				$t+=$userData[$key]->total_user;
				$my_new_arr['tmp_user'][] = $t;
			}
			if($userData[$key+1]->ldapplicationflag == 0){
				$t+=$userData[$key+1]->total_user;
				$my_new_arr['tmp_user'][] = $t;
			}
			if($userData[$key]->ldapplicationflag == 1){
				$p+=$userData[$key]->total_user;
				$my_new_arr['per_user'][] = $p;
			}
			if($userData[$key+1]->ldapplicationflag == 1){
				$p+=$userData[$key+1]->total_user;
				$my_new_arr['per_user'][] = $p;
			}
			unset($userData[$key]);
			unset($userData[$key+1]);
		}elseif($userData[$key]->creation_month!="" && $userData[$key]->creation_month != $userData[$key+1]->creation_month){
			$my_new_arr['creation_month'][] = $userData[$key]->creation_month;
			if($userData[$key]->ldapplicationflag == 0){
				$t+=$userData[$key]->total_user;
				$my_new_arr['tmp_user'][] = $t;
			}else{
				$my_new_arr['tmp_user'][] = $t;
			}
			if($userData[$key]->ldapplicationflag == 1){
				$p+=$userData[$key]->total_user;
				$my_new_arr['per_user'][] = $p;
			}else{
				$my_new_arr['per_user'][] = $p;
			}
			unset($userData[$key]);
			unset($userData[$key+1]);
		}
		//unset($userData[$key]);
		//unset($userData[$key+1]);
		
		
	}
	
	//print_r($my_new_arr);
	//exit;
	
	
	foreach($userData as $val){
		
		if($val->ldapplicationflag == 0){
			$t+=$val->total_user;
			$temp_total_user .= ",".$t;
			//$creation_date_arr1[]=$val->creation_month;
			//$creation_date_arr .= ",".date("m-Y",strtotime($val->creation_month));
		}
		if($val->ldapplicationflag == 1){
			$p+=$val->total_user;
			$per_total_user .= ",".$p;
			//$creation_date_arr1[]=$val->creation_month;
			//$creation_date_arr .= ",".date("m-Y",strtotime($val->creation_month));
		}
		$creation_date_arr1[]=$val->creation_month;
	}
	//$creation_date_arr = ltrim($creation_date_arr,","); 
	$temp_total_user = ltrim($temp_total_user,",");
	$per_total_user = ltrim($per_total_user,",");
	
	$creation_date_str=implode("','",$my_new_arr['creation_month']);
	$creation_date_str_new = "'".$creation_date_str."'";
	
	$my_new_arr_str_per=implode(',',$my_new_arr['per_user']);
	//$my_new_arr_str_per = "'".$my_new_arr_str_per."'";
	
	$my_new_arr_str_tmp=implode(',',$my_new_arr['tmp_user']);
	//$my_new_arr_str_tmp = "'".$my_new_arr_str_tmp."'";
	
	//echo $creation_date_str_new; exit;
	
	//echo $my_new_arr_str_tmp; exit;
	//echo $creation_date_arr; exit;
	//print_r($per_total_user);
	//exit;
	
	drupal_add_js("jQuery(function () {
	Highcharts.chart('container1', {
		credits: {
			enabled: false
		},
		exporting: {
			enabled: false
		},
		chart: {
			type: 'line'
		},
		title: {
			text: 'Monthly Total No. of Registered User'
		},
		subtitle: {
       		 text: 'Line Graph'
    	},
	
		xAxis: {
			title: {
				text: 'Months'
			},
			min:0,
			max:5,
			scrollbar:{
				enabled: true	
			},
			categories: [$creation_date_str_new] 
		},
		yAxis: {
			title: {
				text: 'Total no of user'
			}
		},
		plotOptions: {
			line: {
				dataLabels: {
					enabled: true
				},
				enableMouseTracking: true
			}
		},
		series: [{
			name: 'Permanent User',
			data: [$my_new_arr_str_per]
		}, {
			name: 'Temporary User',
			data: [$my_new_arr_str_tmp]
		}]
	});
});",'inline');
	  $form['chart'] = array(
		'#prefix' => '<div class="col-md-6"><div id="container1" style="min-width: 310px; height: 400px; margin: 0 auto">',
		'#suffix' => '</div></div>'
	  ); 


drupal_add_js("jQuery(function () {
	Highcharts.chart('container', {
    credits: {
			enabled: false
		},
		exporting: {
			enabled: false
		},
	chart: {
        type: 'column'
    },
    title: {
        text: 'Monthly Total No. of Registered User'
    },
    subtitle: {
        text: 'Column Graph'
    },
    xAxis: {
		title: {
				text: 'Months'
			},
		min:0,
		max:5,
		scrollbar:{
				enabled: true	
			},
        categories: [$creation_date_str_new],
        crosshair: true
    },
    yAxis: {
        min: 0,
        title: {
           text: 'Total no of user'
        }
    },
   
    plotOptions: {
        column: {
            pointPadding: 0.2,
            borderWidth: 0
        }
    },
    series: [{
       		name: 'Permanent User',
			data: [$my_new_arr_str_per]

    },  {
        	name: 'Temporary User',
			data: [$my_new_arr_str_tmp]

    }]
});
});",'inline');
	  $form['chart1'] = array(
		'#prefix' => '<div class="col-md-6"><div id="container" style="min-width: 310px; height: 400px; margin: 0 auto">',
		'#suffix' => '</div></div>'
	  ); 
	  

//'25-05-2017','27-05-2017','29-05-2017','30-05-2017','05-06-2017'	 
	/*$form['authority'] = array(
		'#title'=>'',
		'#type' => 'select',
		'#options' => authority_list(),
		'#attributes' => array('class'=>array('form-control')),
		'#prefix'=>'<fieldset class="form-group"><div class="col-md-4"><label for="authorityName form_error">Authority Name </label>',
		'#suffix' =>'</div>',
	); 
	
	$form['area'] = array(
		'#title'=>'',
		'#type' => 'select',
		'#options' => area_list(),
		'#attributes' => array('class'=>array('form-control')),
		'#prefix'=>'<div class="col-md-4"><label for="areaName">Area Name </label>',
		'#suffix' =>'</div>',
	); 
	
	$form['search'] = array (
		'#type' => 'submit',
		'#value' => 'Search',
		'#attributes' => array('class'=>array('btn','btn-primary')),
		'#prefix'=>'<div class="col-md-4" style="margin-top: 37px;">',
		'#suffix' =>'</div></fieldset>',
	);*/ 	
	return $form;
}