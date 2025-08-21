<?php global  $base_root,$base_path,$base_url ;?>

<!-- Custom Theme Style -->
<link href="<?php print $base_path ?>sites/all/modules/dashboard/build/css/custom.css" rel="stylesheet">
<link href="<?php print $base_path ?>sites/all/modules/applicant_registration/css/sky-forms.css" rel="stylesheet">
<?php //print drupal_render_children($form); ?>
<?php //print drupal_render($form['first_name']); ?>

<div class="container body">
  <div class="main_container sky-form">
    <div class="x_panel">
      <div class="x_title">
        <h1><span>C</span>entralized Inspection</h1>
      </div>
      <div class="x_content">
       
              <center><img src="<?php print $base_path ?>sites/all/modules/central_inspection/central_inspection.png" class="img-fluid" style="margin:10px 0 10px 0;" /></center>
              
      
        <footer> <a href="<?php print $base_path ?>user/login" target="_parent">
          <button type="button" class="btn btn-success">Proceed</button>
          </a>
        </footer>
      </div>
    </div>
  </div>
</div>
