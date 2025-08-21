<?php //print_r($rows); exit;?>
<?php global $base_root,$base_path;?>

            <div class="section_headding3">
              <h1>From the Desk of</h1>
            </div>
            <div class="pinkbg">
              <ul>
                	<?php foreach($rows as $val){ if($val["filename"]!=""){ $filename = $val["filename"];}else {$filename = 'c_img.png';}?> 
                  <li>
                  <div class="row clearfix">
                    <div class="col-xs-3"><img src="<?php print $base_root.$base_path?>sites/default/files/<?php print $filename;?>" alt="" class="img-circle" style="max-width:65px;"></a> </div>
                    <div class="col-xs-9">
                      <h4 class="media-heading"> <?php print $val['field_body_title_new']; ?> </h4> 
                         
                              <?php print $val['body']; ?> 
                              <?php if($val['filename_1'] != ""){?>
                              <p><i class="fa fa-caret-right" aria-hidden="true"></i><a target="_blank" href="<?php print $base_root.$base_path?>sites/default/files/<?php print $val['filename_1']; ?>">Read More</a></p>
                              <?php }?>
                    </div>
                  </div>
                </li>
                 <?php	 }	?>	
              </ul>
            </div>