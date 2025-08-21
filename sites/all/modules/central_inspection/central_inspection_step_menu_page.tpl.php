<?php
  global $base_root,$base_path;
?>
<style>
.inspection_report{background: #e6e6e6;font-size: 20px;text-align: center;padding: 25px;margin-top: 60px;font-weight: 600;border: 5px solid #dad7d7;border-radius: 15px;    }
.inspection_report img{width: 90px;height: 90px;border: 5px solid #dad7d7;margin: 0 auto;background: #fff;border-radius: 50%;padding: 6px;margin-top: -70px;}
.inspection_report a{ text-decoration: none; color: #000; }
.inspection_report a:hover{ text-decoration: none; color: #093f94; }
.about_one {min-height:500px;}
</style>
<div class="about_one">
            <h1><span>View</span> Inspection</h1>
              <div class="content">
                <div class="row">
                <div class="col-md-4">
                 <div class="inspection_report"><img src="<?php print $base_root.$base_path?>sites/all/modules/central_inspection/inspection_report.png" class="img-responsive"><span><a href="<?php print $base_root.$base_path?>inspection-data"> Last 3 years </br>Inspection Report</a></span></div>
                </div>
                <div class="col-md-4">
                <div class="inspection_report"><img src="<?php print $base_root.$base_path?>sites/all/modules/central_inspection/inspection_schedule.png" class="img-responsive"><span><a href="<?php print $base_root.$base_path?>joint-inspection-schedule"> Joint </br>Inspection Schedule </a></span></div>
                </div>
                <div class="col-md-4"><div class="inspection_report"><img src="<?php print $base_root.$base_path?>sites/all/modules/central_inspection/centralize_inspection_report.png" class="img-responsive"><span><a href="<?php print $base_root.$base_path?>central-inspection-schedule">View Centralize </br>Inspection Report</a></span></div></div>
              </div>
              </div>
            </div>