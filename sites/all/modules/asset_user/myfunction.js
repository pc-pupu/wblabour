(function ($) {
	$.fn.myJqueryDatePiker = function(data) {
		jQuery('.datepiker').datepicker({
                        //minViewMode: 'years',
						orientation: 'auto',
                        autoclose: true,
                        format: 'dd-mm-yyyy',
						//endDate: '+0d'
                    });
	};
	$.fn.myJqueryDateTimePiker = function(data) {
		jQuery('.datepiccal').datetimepicker({
                        format: 'DD-MM-YYYY hh:mm A',
                    });
	};
	
})(jQuery);

/*jQuery.getScript('https://203.193.130.236/sites/all/themes/labourdept/js/crypto-js.min.js', function pass_encrypt(){
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
	
	alert('hell');
	jQuery("#sub_click").click(function(){
		alert('hello');
	});
	
	var key = "123456";
	var encrypted = CryptoJS.AES.encrypt(JSON.stringify("value to encrypt"), key, {format: CryptoJSAesJson}).toString();
	console.log(encrypted);
	var decrypted = JSON.parse(CryptoJS.AES.decrypt(encrypted, key, {format: CryptoJSAesJson}).toString(CryptoJS.enc.Utf8));
	console.log("decryyepted: "+decrypted);
	
});*/

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



function pass_encrypt(){
	var new_pass = $("#new_pass").val();
	var confirm_pass = $("#confirm_pass").val();
	var key = "WbAdmLb#4321";
	var encrypted = CryptoJS.AES.encrypt(JSON.stringify(new_pass), key, {format: CryptoJSAesJson}).toString();
	var n = JSON.parse(encrypted);
	
	var confirm_encrypted = CryptoJS.AES.encrypt(JSON.stringify(confirm_pass), key, {format: CryptoJSAesJson}).toString();
	var c = JSON.parse(confirm_encrypted);
	
	jQuery("#new_pass").val(n.iv);
	jQuery("#new_pass_ct_val").val(n.ct);
	jQuery("#new_pass_s_val").val(n.s);
	
	jQuery("#confirm_pass").val(c.iv);
	jQuery("#confirm_pass_ct_val").val(c.ct);
	jQuery("#confirm_pass_s_val").val(c.s);
}

function add_user_pass_encrypt(){
	var new_pass = $("#new_pass").val();
	var confirm_pass = $("#confirm_pass").val();
	var key = "WbAdmLb#4321";
	var encrypted = CryptoJS.AES.encrypt(JSON.stringify(new_pass), key, {format: CryptoJSAesJson}).toString();
	var n = JSON.parse(encrypted);
	
	var confirm_encrypted = CryptoJS.AES.encrypt(JSON.stringify(confirm_pass), key, {format: CryptoJSAesJson}).toString();
	var c = JSON.parse(confirm_encrypted);
	
	jQuery("#new_pass").val(n.iv);
	jQuery("#new_pass_ct_val").val(n.ct);
	jQuery("#new_pass_s_val").val(n.s);
	
	jQuery("#confirm_pass").val(c.iv);
	jQuery("#confirm_pass_ct_val").val(c.ct);
	jQuery("#confirm_pass_s_val").val(c.s);
}