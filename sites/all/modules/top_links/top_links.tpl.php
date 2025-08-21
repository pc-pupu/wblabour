<?php 
 drupal_add_js(drupal_get_path('module', 'top_links') .'/js/top_menu.js');
 
 $query = db_select('menu_links', 'ml');
 $query->leftJoin('url_alias', 'ua', 'ml.link_path = ua.source');
 $query->fields('ml', array('menu_name', 'link_path', 'link_title', 'has_children', 'mlid', 'options'));
 $query->fields('ua', array('alias'));
 $query->condition('ml.menu_name', 'main-menu');
 $query->condition('ml.depth', 1);
 $query->condition('ml.hidden', 0);
 $query->orderBy('ml.weight', 'asc');
 $result = $query->execute();
 $top_links ='';
 $cnt = 0;
 
?>

 <ul class="nav navbar-nav">
 <?php 
 		while($record = $result->fetchObject()) {
			
		   /* echo '<pre>';
			print_r($record);*/
			$cnt++;
			if($record->alias)
				$first_level_path = $record->alias;
			else 
				$first_level_path = $record->link_path;
				
			if( $first_level_path == "<front>")
				$first_level_path = "";
 ?>
 	    
        <?php  if($record->has_children == 1 ){ 
		?>
        <?php /*?><li class="dropdown"><?php echo l($record->link_title.'<span class="caret"></span>', $first_level_path, array('html' => TRUE, )); ?><?php */?>
        <li class="dropdown"><?php echo $record->link_title.'<span class="caret"></span>';?>
        
<!--       <a href="<?php echo $first_level_path; ?>" ><?php echo $record->link_title; ?><span class="caret"></span></a>-->
        	  <ul class="dropdown-menu">  
			        <?php 
							$query2 = db_select('menu_links', 'ml');
                            $query2->leftJoin('url_alias', 'ua', 'ml.link_path = ua.source');
                            $query2->fields('ml', array('menu_name', 'link_path', 'link_title', 'has_children', 'mlid', 'options'));
							$query2->fields('ua', array('alias'));
							$query2->condition('ml.menu_name', 'main-menu');
							$query2->condition('ml.depth', 2);
							$query2->condition('ml.plid', $record->mlid);
							$query2->condition('ml.hidden', 0);
							$query2->orderBy('ml.weight', 'asc');
							$result2 = $query2->execute();

							while($record2 = $result2->fetchObject()) { 
							
							
								//echo '<pre>';
								//print_r($record2);
								
								if($record2->alias)
									$second_level_path = $record2->alias;
								else 
									$second_level_path = $record2->link_path;
								if( $second_level_path == "<front>")
				                	$second_level_path = "";	
					?><?php
					//$arr1 = array();
					//$arr1 = unserialize($record2->options);
					
					?>
              				<li ><?php
							if(mb_substr_count($record2->options,"_blank") > 0)
							echo l($record2->link_title, $second_level_path , array('attributes' => array('target'=>'_blank'))); 
							else
							echo l($record2->link_title, $second_level_path ); 
							?></li>
                    <?php }  // End of 2nd level <li> ?>
              </ul>
        <?php } else { ?>
        
 
  <li><?php echo l($record->link_title, $first_level_path); ?>
	 <?php	
	 }
		} // End of 1st level <li>
  ?>  
  		</li>
 </ul>
