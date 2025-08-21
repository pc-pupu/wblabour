<?php

function webservicemap_services_resource() {
  $api = array(
	'customLogin' => array(
  	'operations' => array(
    	
		 'create' => array(
          'help' => 'Create a login',
          'callback' => 'custom_login',
          'file' => array('type' => 'inc', 'module' => 'webservicemap', 'name' => 'includes/webservicemap.services'),
          'access callback' => 'user_access',
          'access arguments' => array('access content'),
          'access arguments append' => FALSE,
          'args' => array(
            array(
              'name' => 'account',
              'type' => 'array',
              'description' => 'The user object',
              'source' => 'data',
              'optional' => FALSE,
            ),
          ),
        ),
      	),
	),
	
	'locationInsert' => array(
  	'operations' => array(
    	
		 'create' => array(
          'help' => 'Create a login',
          'callback' => 'insert_location',
          'file' => array('type' => 'inc', 'module' => 'webservicemap', 'name' => 'includes/webservicemap.services'),
          'access callback' => 'user_access',
          'access arguments' => array('access content'),
          'access arguments append' => FALSE,
          'args' => array(
            array(
              'name' => 'account',
              'type' => 'array',
              'description' => 'The user object',
              'source' => 'data',
              'optional' => FALSE,
            ),
          ),
        ),
      	),
	),
	
	
	'fetchLocation' => array(
  	'operations' => array(
    	
		 'create' => array(
          'help' => 'Create a login',
          'callback' => 'fetch_location',
          'file' => array('type' => 'inc', 'module' => 'webservicemap', 'name' => 'includes/webservicemap.services'),
          'access callback' => 'user_access',
          'access arguments' => array('access content'),
          'access arguments append' => FALSE,
          'args' => array(
            array(
              'name' => 'account',
              'type' => 'array',
              'description' => 'The user object',
              'source' => 'data',
              'optional' => FALSE,
            ),
          ),
        ),
      	),
	),
	
	);
	
	return $api;
}
	
function custom_login($user_arr = NULL){
	//$role = trim($user_arr['userRole']);
	$user = trim($user_arr['userName']);
	$pass = trim($user_arr['userPass']);
	$access_granted_for_user = FALSE;
	$access_granted_for_admin = FALSE;
	//return $user;
	
	//if($role == 6){
		if(user_authenticate($user, $pass)){
		  $user_obj = user_load_by_name($user);
		  $access_granted = in_array('maptrackuser', $user_obj->roles);
		  $access_granted_for_admin = in_array('adminmanager', $user_obj->roles);
		}
		if ($access_granted){
			return array('code'=>0, 'content'=>array('Uid' => $user_obj->uid, 'Username' => $user_arr['userName'], 'Role' => 'maptrackuser' ,'msg'=>'User is successfully logged in.'));	
		}else if($access_granted_for_admin){
			return array('code'=>0, 'content'=>array('Uid' => $user_obj->uid, 'Username' => $user_arr['userName'], 'Role' => 'adminmanager' ,'msg'=>'User is successfully logged in.'));	
		}else{
			return array('code'=>1, 'content'=>array('Uid' => '','Username' => $user_arr['userName'], 'Role' => 'NA','msg'=>'Invalid credential.'));	
		}
		/*$user_exist_arr = db_select('users', 'u')
		->fields('u', array('name'))
		->condition('u.name', $user_arr['userName'], '=')
		->execute()
		->fetchAssoc();
	
		if($user_exist_arr){
			 return array('code'=>0, 'content'=>array('Username' => $user_arr['userName'], 'Role' => $user_arr['userRole'],'msg'=>'User is successfully logged in.'));	
		}else{
			return array('code'=>1, 'content'=>array('Username' => $user_arr['userName'], 'Role' => $user_arr['userRole'],'msg'=>'Invalid credential.'));	
		}*/
	/*}else{
		return array('code'=>1, 'content'=>array('Username' => $user_arr['userName'], 'Role' => $user_arr['userRole'],'msg'=>'Invalid credential.'));	
	}*/
}

function insert_location($user_arr = NULL){
	
	$Uid = trim($user_arr['Uid']);
	$Lat = trim($user_arr['Lat']);
	$Long = trim($user_arr['Long']);
	$DeviceId = trim($user_arr['DeviceId']);
	
	$maptrackinfo = array('uid'=>$Uid,
						'device_id'=>$DeviceId,
						'latt' => $Lat,
						'longg' => $Long,
						'insert_date_time' => date('Y-m-d h:i:s'));
						
	$id = db_insert('maptrack_location')->fields($maptrackinfo)->execute();
	if($id){
		return array('code'=>0, 'content'=>array('msg'=>'User is successfully inserted.'));	
	}else{
		return array('code'=>1, 'content'=>array('msg'=>'Unable to insert.'));	
	}
	
}


function fetch_location($user_arr = NULL){
	$result_data = array();
	$Uid = trim($user_arr['Uid']);
	if(!empty($Uid)){
		 $query = db_select('maptrack_location', 'ml');
		 $query->fields('ml', array('id','uid','device_id','latt','longg','insert_date_time'));
		 $query->condition('ml.uid',trim($Uid),'=');
		 $result = $query->execute();
		 $result_data = $result->fetchAll();
	}
	
	if(!empty($result_data)){
		return array('code'=>0, 'content'=>array('result'=>$result_data));	
	}else{
		return array('code'=>1, 'content'=>array('result'=>'empty.'));	
	}
}