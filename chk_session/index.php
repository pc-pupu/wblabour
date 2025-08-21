
<form method="post" action="">
<p>Enter Username : <input type="test" name="username" value="" /></p>
<p>Enter Password : <input type="password" name="pass" value="" /></p>
<p><input type="submit" name="submit" value="Login"  /></p>
</form>

<?php

if(isset($_POST['submit']) && ($_POST['submit'] == 'Login')) {
	
	
	if(trim($_POST['username']) == 'wblabour' && trim($_POST['pass']) == 'wblabour')
	{
	session_start();
	$_SESSION['name'] = 'Admin User';
	header('Location:success.php');	
	} else 	{
		echo '<p style="color:red">Invalid Username or password</p>';
	}
	
	
} else {
	session_start();
	session_destroy();
}


?>





































