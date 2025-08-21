<?php global $base_root,$base_path; ?>
<script src="<?php print $base_root.$base_path?>sites/all/themes/labourdept/js/crypto-js.min.js"></script> 
<script>
var CryptoJSAesJson = {
    stringify: function (cipherParams) {
        var j = {ct: cipherParams.ciphertext.toString(CryptoJS.enc.Base64)};
        if (cipherParams.iv) j.iv = cipherParams.iv.toString();
        if (cipherParams.salt) j.s = cipherParams.salt.toString();
        return JSON.stringify(j);
    },
    parse: function (jsonStr) {
        var j = JSON.parse(jsonStr);
        var cipherParams = CryptoJS.lib.CipherParams.create({ciphertext: CryptoJS.enc.Base64.parse(j.ct)});
        if (j.iv) cipherParams.iv = CryptoJS.enc.Hex.parse(j.iv)
        if (j.s) cipherParams.salt = CryptoJS.enc.Hex.parse(j.s)
        return cipherParams;
    }
}
var key = "123456";
var encrypted = CryptoJS.AES.encrypt(JSON.stringify("value to encrypt"), key, {format: CryptoJSAesJson}).toString();
//console.log(encrypted);
var decrypted = JSON.parse(CryptoJS.AES.decrypt(encrypted, key, {format: CryptoJSAesJson}).toString(CryptoJS.enc.Utf8));
//console.log("decryyepted: "+decrypted); 

function pwd_handler(form){
<<<<<<< HEAD
  //var x = form.pass.value;
  var password = document.getElementById('edit-pass').value;
  
  //var y = encrpt(x);
  //alert(y);
  //alert(password);
  var key = "WbAdmLb#4321";
  var encrypted = CryptoJS.AES.encrypt(JSON.stringify(password), key, {format: CryptoJSAesJson}).toString();
  
  var j = JSON.parse(encrypted);
  
  jQuery("#edit-pass").val(j.iv);
  jQuery("#ct_val").val(j.ct);
  jQuery("#s_val").val(j.s);
  //alert(j.ct);
  //document.getElementById("password").value = encrypted;
  //alert(encrypted);
  //jQuery("#edit-pass").val(y);
}

function pwd_handler_form(form){
  var base_url = window.location.origin;
  var x = form.pass.value;
   $.ajax({
           type: "POST",
       async: false,
=======
	//var x = form.pass.value;
	var password = document.getElementById('edit-pass').value;
	
	//var y = encrpt(x);
	//alert(y);
	//alert(password);
	var key = "WbAdmLb#4321";
	var encrypted = CryptoJS.AES.encrypt(JSON.stringify(password), key, {format: CryptoJSAesJson}).toString();
	
	var j = JSON.parse(encrypted);
	
	jQuery("#edit-pass").val(j.iv);
	jQuery("#ct_val").val(j.ct);
	jQuery("#s_val").val(j.s);
	//alert(j.ct);
	//document.getElementById("password").value = encrypted;
	//alert(encrypted);
	//jQuery("#edit-pass").val(y);
}

function pwd_handler_form(form){
	var base_url = window.location.origin;
	var x = form.pass.value;
	 $.ajax({
           type: "POST",
		   async: false,
>>>>>>> 14d853556ffd3e8fabc4403330a38ba0b5494614
           url: base_url+"/sites/all/themes/labourdept/templates/passwordencrypt.php",
           data: {pass: x},

             // ------v-------use it as the callback function
           success: function(returnValue){
               jQuery("#edit-pass").val(returnValue);
            },
            error: function(request,error) {
                alert('An error occurred attempting to get new e-number');
                // console.log(request, error);
            }
    });
<<<<<<< HEAD
  /*var x = btoa(btoa(btoa(form.pass.value)));
  if(form.pass.value != ""){
    jQuery("#edit-pass").val(x);
  }*/
}
</script>

<script>
jQuery(document).ready(function () {
  // Use event delegation to handle future DOM replacements
  jQuery(document).on('click', '#refresh-captcha', function () {
    jQuery.ajax({
      url: window.location.href,
      type: 'GET',
      success: function (response) {
        var refreshedCaptcha = jQuery(response).find('.captcha-wrapper').html();
        jQuery('.captcha-wrapper').html(refreshedCaptcha);
      }
    });
  });
});


</script>

<?php 
  
=======
	/*var x = btoa(btoa(btoa(form.pass.value)));
	if(form.pass.value != ""){
		jQuery("#edit-pass").val(x);
	}*/
}
</script>
<?php 
	
>>>>>>> 14d853556ffd3e8fabc4403330a38ba0b5494614
  /*print drupal_render($form['name']);
  print drupal_render($form['pass']);
  print drupal_render($form['captcha']);
  print drupal_render($form['form_build_id']);
  print drupal_render($form['form_id']);
  print drupal_render($form['actions']);*/
?>


<!-- copy -->
<div class="login-bg-big">   
<!--end body here-->
<div class="container">
<div class="login-box-mid">
<div class="user-login-top"></div>
<div class="col-lg-3 col-md-2 col-sm-6 col-xs-12 user-login-left-block">&nbsp;</div>
<div class="col-lg-6 col-md-8 col-sm-12 col-xs-12">

<!--login form section start-->
<!--<form id="user-login" action="/user" method="post" accept-charset="UTF-8">-->
<div class="user-login user-login-section">
<?php print drupal_render($form['name']);?>
<!--<input id="edit-name" class="form-text required input-login-username" name="name" maxlength="60" type="text" placeholder="Username">
<span class="user-login-info">Enter your Department of Labour username.</span>-->
</div>
<div class="user-pass">
<?php print drupal_render($form['pass']);?>
<!--<input id="edit-pass" class="form-text required input-login-password" name="name" maxlength="60" type="Password" placeholder="Password">
<span class="user-login-info">Enter the password that accompanies your username.</span>-->
</div>
<div class="user-captcha">
<!--<div class="col-lg-4 col-md-4 col-sm-12 col-xs-12">Captcha Code</div>
<div class="col-lg-8  col-md-8 col-sm-12 col-xs-12">
<input id="captcha" class="form-text required input-login-captcha" name="name" type="text" placeholder="Captcha Code">
<span class="user-login-info">Enter the characters shown in the image.</span>
</div>-->
<?php print drupal_render($form['s_val']);?>
<?php print drupal_render($form['ct_val']);?>

<<<<<<< HEAD
<div class="captcha-wrapper">
  <?php print drupal_render($form['captcha']); ?>
  <a href="javascript:void(0);" id="refresh-captcha" title="Refresh Captcha">
    <img src="<?php print $base_root . $base_path; ?>sites/all/themes/labourdept/images/captcha-refresh.png" alt="Refresh CAPTCHA" style="height: 25px; margin-left: 10px;" />
  </a>
</div>

</div>

<a href="<?php print $base_root.$base_path?>forgot-password/" style="font-size: 20px!important; color: white">Forgot password?</a>
=======
<?php print drupal_render($form['captcha']);?>
</div>
>>>>>>> 14d853556ffd3e8fabc4403330a38ba0b5494614
<div class="user-btn-box user-login-btn">
<!--<input id="edit-submit" class="user-login-btn" name="op" value="Login" type="submit">-->
<?php
 print drupal_render($form['form_build_id']);
  print drupal_render($form['form_id']);
  print drupal_render($form['actions']);
?>
</div>
<!--</form>-->
<!--login form section end-->
</div>
<div class="col-lg-3 col-md-2 col-sm-6 col-xs-12 user-login-left-block">&nbsp;</div>
</div>
</div>


</div>

<!-- end copy -->