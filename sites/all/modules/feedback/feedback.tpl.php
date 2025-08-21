<?php $arr = authority_list();?>
<div class="about_body_main col-md-12">
        
        	<!-- about_one starts here -->
            <div class="about_one">
            	<!--<h1><span>M</span>ay we help You?</h1>-->
                   <div class="form_box">
                            <form name="myForm" action="submit" onsubmit="return(validate());" method="post">
                              <fieldset class="form-group">
                                <label for="exampleInputEmail1">Name</label>
                                <input type="name" class="form-control" id="exampleInputName" name="feedback_applicant_name" placeholder="Enter Name">
                                <small class="text-muted">We'll never share your email with anyone else.</small>
                              </fieldset>
                              <fieldset class="form-group">
                                <label for="exampleInputPassword1">Email address</label>
                                <input type="email" class="form-control" id="exampleInputEmail1" name="feedback_email" placeholder="Enter Email">
                              </fieldset>
                              
                              <fieldset class="form-group">
                                <label for="exampleSelect1">Select Directorate</label>
                                <select class="form-control" id="exampleSelect1" name="feedback_select_directorate">
                                	<?php foreach($arr as $key=>$val){?>
                                  <option value="<?php print $key;?>"><?php print $val;?></option>
                                  <?php }?>
                                </select>
                              </fieldset>
                              
                              <fieldset class="form-group">
                                <label for="exampleTextarea">Comment</label>
                                <textarea class="form-control" id="exampleTextarea" name="feedback_comment" rows="3"></textarea>
                              </fieldset>
                              
                              <button type="reset" class="btn btn-primary">Reset</button>
                              <button type="submit" class="btn btn-primary">Submit</button>
                              
                            </form>
                   </div>
                </div>
             </div>
             
<script type="text/javascript">
            
 function validate()
      {
    		// alert("hiiii");
        if( document.myForm.feedback_applicant_name.value == "" )
         {
            alert( "Please provide your name!" );
            document.myForm.feedback_applicant_name.focus() ;
            return false;
         }
         
         if( document.myForm.feedback_email.value == "" )
         {
             var emailID = document.myForm.feedback_email.value;
         	 atpos = emailID.indexOf("@");
         	 dotpos = emailID.lastIndexOf(".");
             if (atpos < 1 || ( dotpos - atpos < 2 )) 
        	 {
            	alert("Please enter correct email ID")
            	document.myForm.feedback_email.focus() ;
            	return false;
         	}
         }
    	
		 if( document.myForm.feedback_select_directorate.value == "" )
         {
            alert( "Please Select a Directorate!" );
            document.myForm.feedback_select_directorate.focus() ;
            return false;
         }
		 
		  if( document.myForm.feedback_comment.value == "" )
         {
            alert( "Please provide your Comment!" );
            document.myForm.feedback_comment.focus() ;
            return false;
         }
     
         return( true );
      }
</script>