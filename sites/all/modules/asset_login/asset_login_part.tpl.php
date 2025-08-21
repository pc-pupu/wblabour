<style>
.asset-login{background: #eaeaea;margin:0 auto 60px;width: 100%;display: block;overflow: hidden; max-width: 900px;}
.asset-login-img{ background:#493d89; }
.asset-login h2{font-size: 25px;margin-bottom: 30px; border: none;font-style: normal;text-transform: capitalize;color: #2e4b90;}
.asset-login .form-text{padding: 10px;width: 100%;font-size: 14px;border: 1px solid #dcdcdc;margin-bottom: 20px;}
.asset-login .ota-form{ padding:40px 25px;}
.asset-login label{font-size: 14px;text-transform: capitalize;margin-bottom: 5px;font-weight: 300;color: #000;}
.asset-login .form-submit{background-color: #4CAF50;color: #ffffff;border: none;padding:6px 20px;font-size: 16px;cursor: pointer;text-transform: capitalize; float:left;margin-right: 20px;}
.asset-login .send-otp{ background: #e86f4b;}
.asset-login .form-submit:hover{ background:#666;}
.asset-login .register{ float: left;width: 100%;text-align: left;margin: 20px 0 0 auto;font-size: 14px;}
.asset-login .register a{color: #07618c;font-weight: 600;}
.asset-login #success_div{ padding: 0 15px;color: #027b07;font-size: 13px;font-weight: 600;float: left;width: 100%; margin-top: -10px;margin-bottom: 15px;}
.asset-login #error_div{ padding: 0 15px;color: #f00;font-size: 13px;font-weight: 600;float: left;width: 100%; margin-top: -10px;margin-bottom: 15px;}
.asset-login #divCounter{position: absolute;right: 18px;color: #bf0202;font-size: 14px;font-weight: 600;}
input[type="submit"].send-otp:disabled {opacity: 0.4;background: #e86f4b !important;}
.asset-login .mobile-time{ position:relative;float: left;width: 100%;}
.asset-login #divEndTimer{float: left;width: 100%;padding: 0 15px 10px;color: #000;font-weight: 600;}
</style>

<?php //print drupal_render($form['mobile']); ?>
<?php //print drupal_render($form['otp']); ?>
<?php //print drupal_render($form['sent_otp']); ?>
<?php //print drupal_render($form['submit_send']); ?>
<?php //print drupal_render_children($form); ?>
<?php
  // print drupal_render($form['mobile']);
  //print drupal_render($form['otp']);
  // print drupal_render($form['sent_otp']);
  //print drupal_render($form['submit_send']);
  print drupal_render($form['form_build_id']);
  print drupal_render($form['form_id']);
  print drupal_render($form['actions']);
?>

<div class="asset-login">
<div class="col-md-5 asset-login-img">
  <img src="<?php print $base_path ?>sites/all/modules/asset_login/otp-login.jpg" alt="" />
</div> 
<div class="col-md-7 ota-form">
<div class="col-md-12"><h2>Asset Login</h2></div>
<?php print drupal_render($form['mobile']); ?>
<?php print drupal_render($form['showmsg_success']); ?>
<?php print drupal_render($form['showmsg_error']); ?>
<div class="mobile-time">
<?php print drupal_render($form['otp']); ?>
<?php print drupal_render($form['showtimer']); ?>
<?php print drupal_render($form['endtimer']); ?>
</div>
<div class="col-md-12">
<?php print drupal_render($form['sent_otp']); ?>
<?php print drupal_render($form['submit_send']); ?> 

<!--<div class="register">
      No account? <a href="<?php print $base_root.$base_path?>service_flow">Create one!</a> 
</div>-->
</div>
</div>
</div>

<script>
function getTimer(){
localStorage.removeItem("end1");
localStorage.clear();	
//var hoursleft = 0;
var minutesleft = 5; //give minutes you wish
var secondsleft = 00; // give seconds you wish
var finishedtext = "Your OTP has expired. Please Re-Generate to Login!";
var end1;
if(localStorage.getItem("end1")) {
end1 = new Date(localStorage.getItem("end1"));
} else {
end1 = new Date();
end1.setMinutes(end1.getMinutes()+minutesleft);
end1.setSeconds(end1.getSeconds()+secondsleft);

}
var counter = function () {
var now = new Date();
var diff = end1 - now;

diff = new Date(diff);

var milliseconds = parseInt((diff%1000)/100)
    var sec = parseInt((diff/1000)%60)
	var mins = parseInt((diff/(1000*60))%60)
    //var hours = parseInt((diff/(1000*60*60))%24);

if (mins < 10) {
    mins = "0" + mins;
}
if (sec < 10) { 
    sec = "0" + sec;
}     
if(now >= end1) {     
    clearTimeout(interval);
   // localStorage.setItem("end", null);
     localStorage.removeItem("end1");
     localStorage.clear();
    document.getElementById('divEndTimer').innerHTML = finishedtext;
     //if(confirm("TIME UP!"))
	 document.getElementById('genotp').value = 'RE-Generate OTP';
	 document.getElementById('genotp').disabled = false;
     //window.location.href= "timeup.php";
} else {
    var value = mins + ":" + sec;
    localStorage.setItem("end1", end1);
    document.getElementById('divCounter').innerHTML = value;
	document.getElementById('genotp').disabled = true;
}
}
var interval = setInterval(counter, 1000);

}
</script>

