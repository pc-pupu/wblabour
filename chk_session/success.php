<?php

session_start();

if(!empty($_SESSION['name']))
echo 'You are '.$_SESSION['name'];
else
echo 'Session not working...';
?>

