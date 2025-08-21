<?php

require 'PHPMailerAutoload.php';

$mail = new PHPMailer(true);

$mail->isSMTP();
$mail->Host = '164.100.14.95';
$mail->SMTPAuth = false;
$mail->Username = ''; //dlctu.lc-wb@gov.in
$mail->Password = ''; //Ks$190969
$mail->SMTPSecure = '';
$mail->Port = 25;

//$mail->From('dlctu.lc-wb@gov.in');
//$mail->setFrom('dlctu.lc-wb@gov.in', 'WBLC');
$mail->From = 'wblabour@gmail.com';
$mail->FromName = 'Labour Department';
$mail->addAddress('arnab.roy0220@gmail.com', '');
//$mail->addAddress('p.mitra@nic.in', 'Labour');
$mail->isHTML(true);

$mail->Subject = 'Test Subject4444';
$mail->Body    = '<html>
    <head>
        <title>Welcome to CodexWorld</title>
    </head>
    <body>
        <h1>Thanks you for joining with us!</h1>
        <table cellspacing="0" style="border: 2px dashed #FB4314; width: 300px; height: 200px;">
            <tr>
                <th>Name:</th><td>CodexWorld</td>
            </tr>
            <tr style="background-color: #e0e0e0;">
                <th>Email:</th><td>contact@codexworld.com</td>
            </tr>
            <tr>
                <th>Website:</th><td><a href="http://www.codexworld.com">www.codexworld.com</a></td>
            </tr>
        </table>
    </body>
    </html>';
$mail->SMTPDebug = 3;
if(!$mail->send()) {
    echo 'Message could not be sent.';
    echo 'Mailer Error: ' . $mail->ErrorInfo;
} else {
    echo 'Message has been sent';
}

