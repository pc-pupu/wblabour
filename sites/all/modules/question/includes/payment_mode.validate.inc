<?php

function payment_mode_entry_validate($form, &$form_state) {
  if (!$form_state['values']['payment_mode']) {
    form_set_error('payment_mode', 'You must enter the mode of payment before continuing');    
  }

}

