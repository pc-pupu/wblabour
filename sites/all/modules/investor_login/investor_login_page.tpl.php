<script>
function pwd_handler_form(form){
	var x = btoa(btoa(btoa(form.pass.value)));
	if(form.pass.value != ""){
		jQuery("#edit-pass").val(x);
	}
}
</script>
<?php
  global $base_root,$base_path;
?>


<?php 
	#print $rendered;
	
	/*print '<form action="/investor/login" method="post" id="user-login" accept-charset="UTF-8">';
	print $rendered_hidden_investor_login_form;
	print $rendered_name;
	print $rendered_pass;
	print $rendered_captcha;
	print $rendered_form_build_id;
	print $rendered_form_id;
	print $rendered_actions;
	print '</form>'; */
 ?>

<?php
  //print drupal_render($form['name']);
  //print drupal_render($form['pass']);
  //print drupal_render($form['captcha']);
  //print drupal_render($form['form_build_id']);
  //print drupal_render($form['form_id']);
  //print drupal_render($form['actions']);
?>


<!DOCTYPE HTML>
<html lang="en">
<head>
<meta charset="utf-8">
<meta http-equiv="X-UA-Compatible" content="IE=edge">
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>Invester Login</title>
<link href="https://fonts.googleapis.com/css?family=Fjalla+One" rel="stylesheet"> 
 <link href="https://fonts.googleapis.com/css?family=PT+Sans" rel="stylesheet"> 
<!-- Latest compiled and minified CSS -->
<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css" integrity="sha384-BVYiiSIFeK1dGmJRAkycuHAHRg32OmUcww7on3RYdg4Va+PmSTsz/K68vbdEjh4u" crossorigin="anonymous">
<script src="https://ajax.googleapis.com/ajax/libs/jquery/1.12.4/jquery.min.js"></script>
<!-- Latest compiled and minified JavaScript -->
<script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js" integrity="sha384-Tc5IQib027qvyjSMfHjOMaLkfuWVxZxUPnCJA7l2mCWNIpG9mGCD8wGNIcPD7Txa" crossorigin="anonymous"></script>
<style>
body{background:url(<?php print $base_root.$base_path?>sites/all/modules/investor_login/investor.jpg) no-repeat no-repeat center center fixed;-webkit-background-size: cover;-moz-background-size: cover;-o-background-size: cover;background-size: cover; overflow:hidden;}
header{ background:#fff;}
.breadcrumb{ display:none;}
.investor_login{ margin:20px 0 40px; }
.investor_login_form{ width:50%; margin:0 auto; /*background:rgba(255, 255, 255, 0.73);*/ padding: 20px;border: 1px solid #f0f0f0;    

    margin: 150px 0px 0px 548px;
    border-radius: border-radius: 4px 4px 4px 4px;
    -moz-border-radius: 4px 4px 4px 4px;
    -webkit-border-radius: 4px 4px 4px 4px;
    box-shadow: -webkit-box-shadow: 0px 0px 23px 0px rgba(50, 50, 50, 0.75);
    -moz-box-shadow: 0px 0px 23px 0px rgba(50, 50, 50, 0.75);
    box-shadow: 0px 0px 23px 0px rgba(50, 50, 50, 0.75);
    background: #fff;



 }
.investor_login_form .description{ font-size:11px; color:#000;}
.investor_login h2{font-family: 'PT Sans', sans-serif;text-align: center;color: #fff;font-size: 30px;text-transform: uppercase;margin: 20px 0;text-shadow: 2px 2px 2px #000;font-weight: 600;}
.investor_login h2 img{width: 60px; height: 60px; margin: 12px auto;display: block;}
.form-item-captcha-response{float: right;}


.investor_login input[type="submit"]{ display: inline-block;padding: 10px;margin:20px 0 0;font-size: 15px;font-weight: 600;line-height: 1.42857143;text-align: centerwhite-space: nowrap;vertical-align: middle;-ms-touch-action: manipulation;touch-action: manipulation;cursor: pointer;-webkit-user-select: none;-moz-user-select: none;-ms-user-select: none;user-select: none;border-radius: 2px;-moz-border-radius: 2px;-webkit-border-radius: 2px;color: #fff;background-color:#146b64; border: 0px solid #232220;text-transform:uppercase; width:100%;}


.investor_login input[type="submit"]:hover{background-color: #0d766e;}
.investor_login .captcha img{ width: 115px; height: auto;margin: 17px 0 0 0;}
.investor_login .register-btn{float: right;}
.investor_login  .form-control:focus{border-color: #c2ced7;}
.investor_login  .register a{ color:#000; font-size:11px; font-weight:600;}
@media screen and (min-width: 1024px){
.investor_login_form {width: 500px;}	
}
@media screen and (max-width: 767px) {
.investor_login_form{ width:98%; }	
}
@media screen and (max-width: 680px) {
.investor_login .captcha img{ width: auto;}
.form-item-captcha-response{ float:none; }
}
</style>
</head>
<body>
<div class="investor_login">
<div class="container">
<!--<h2> <img src="<?php print $base_root.$base_path?>sites/all/modules/investor_login/user.png" width="" height="" alt=""> Entrepreneur Login</h2>-->
 <form onSubmit="pwd_handler_form(this);" action="" method="post" class="investor_login_form">
  <?php print $rendered_hidden_investor_login_form; ?>
  <?php print $rendered_name;?>
      <!--<input id="edit-name" name="name" value="" type="text"  class="form-control" placeholder="Username*">
      <div class="description">Enter your Department Of Labour username.</div>-->
   <?php print $rendered_pass;?>   
     <!-- <input id="edit-pass" name="pass" type="password" class="form-control" placeholder="Password*">
      <div class="description">Enter the password that accompanies your username.</div>-->
    <div class="captcha">
    <?php print $rendered_captcha;?>  
    
  <!--   <input name="captcha_sid" value="88471" type="hidden">
      <input name="captcha_token" value="1e4ae34f0319d17095795b6a6fb3cbc1" type="hidden">
      <img typeof="foaf:Image" src="image_captcha.jpg" alt="Image CAPTCHA" title="Image CAPTCHA" width="180" height="60">-->
      <!--<div class="form-item form-type-textfield form-item-captcha-response">-->
      <!--<label for="edit-captcha-response">What code is in the image? <span class="form-required" title="This field is required.">*</span></label>
        <input id="edit-captcha-response" name="captcha_response" value="" size="15" maxlength="128" class="form-text required" autocomplete="off" type="text">
        <div class="description">Enter the characters shown in the image.</div>-->
    <!--  </div>-->
      
    </div>
   <!-- <input name="form_build_id" value="form-uOVLu-secPuj8NqRhM9svAaLQBaB1JnSQcW4VPEVcWw" type="hidden">
    <input name="form_id" value="user_login" type="hidden">-->
    <div class="form-actions form-wrapper">
      <!--<input id="edit-submit" name="op" value="Log in" class="login-btm" type="submit">-->
      <?php
		 print $rendered_form_build_id;
 		 print $rendered_form_id;
  		 print $rendered_actions;
	?>
      <div class="register">
      No account? <a href="<?php print $base_root.$base_path?>applicant-registration" style="font-size:16px;">Create one!</a> 
      </div>
    </div>
  </form>
  </div>
</div>

</body>
</html>