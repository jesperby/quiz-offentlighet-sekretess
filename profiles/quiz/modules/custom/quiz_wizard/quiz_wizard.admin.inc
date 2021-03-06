<?php
/**
 * Administration pages for the Quiz Wizard module.
 */

/**
 * The main administration form.
 */
function quiz_wizard_admin_form($form, &$form_state) {
  // Add a fieldset for the configuration settings.
  $form['configuration'] = array(
    '#type' => 'fieldset',
    '#title' => t('Configuration'),
    '#collapsible' => TRUE,
  );

  // Configure the number of questions.
  $options = array();
  for ($i = 1; $i <= quiz_wizard_get_num_questions_maximum(); $i++) {
    $options[$i] = $i;
  }
  $form['configuration']['quiz_questions'] = array(
    '#type' => 'select',
    '#title' => t('Number of questions'),
    '#description' => t('The number of questions that the user has to answer.'),
    '#required' => TRUE,
    '#options' => $options,
    '#default_value' => quiz_wizard_get_num_questions_configured(),
  );

  // Configure pass rate.
  $form['configuration']['quiz_pass_rate'] = array(
    '#type' => 'textfield',
    '#title' => t('Pass rate'),
    '#description' => t('The percentage of correct answers that the user has to reach in order to pass the test.'),
    '#required' => TRUE,
    '#default_value' => quiz_wizard_get_pass_rate(),
    '#size' => 3,
    '#maxlength' => 3,
  );

  // Configure the auto submit behavior.
  $form['configuration']['quiz_submit'] = array(
    '#type' => 'checkbox',
    '#title' => t('Auto submit the form'),
    '#description' => t('Will hide the submit button, and submit the form automatically as soon as the user picks an answer.'),
    '#default_value' => quiz_wizard_get_auto_submit(),
  );

  // Configure randomize order.
  $form['configuration']['quiz_randomize'] = array(
    '#type' => 'checkbox',
    '#title' => t('Randomize questions'),
    '#description' => t('Will randomize the order of questions. If you uncheck this, the questions will be used by publishing date starting with the oldest.'),
    '#default_value' => quiz_wizard_get_randomize(),
  );

  // Add a fieldset for the text settings.
  $form['text'] = array(
    '#type' => 'fieldset',
    '#title' => t('Texts'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  // Configure the quiz title.
  $form['text']['quiz_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Quiz title'),
    '#required' => TRUE,
    '#default_value' => quiz_wizard_get_title(),
  );

  // Configure the intro text.
  $intro_text = quiz_wizard_get_intro_text();
  $form['text']['quiz_intro_text'] = array(
    '#type' => 'text_format',
    '#title' => t('Intro text'),
    '#default_value' => $intro_text['value'],
    '#format' => $intro_text['format'],
    '#description' => t('A short text that will be displayed in the intro block, above the start link.'),
  );

  // Configure the fail title.
  $form['text']['quiz_fail_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Fail title'),
    '#required' => TRUE,
    '#default_value' => quiz_wizard_get_fail_title(),
    '#description' => t("The title to use when the user doesn't pass the test."),
  );

  // Configure the fail text.
  $fail_text = quiz_wizard_get_fail_text();
  $form['text']['quiz_fail_text'] = array(
    '#type' => 'text_format',
    '#title' => t('Fail text'),
    '#default_value' => $fail_text['value'],
    '#format' => $fail_text['format'],
    '#description' => t("Additional text that will be displayed when the user fails the test."),
  );

  // Configure the pass title.
  $form['text']['quiz_pass_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Pass title'),
    '#required' => TRUE,
    '#default_value' => quiz_wizard_get_pass_title(),
    '#description' => t("The title to use when the user passes the test."),
  );

  // Configure the pass text.
  $pass_text = quiz_wizard_get_pass_text();
  $form['text']['quiz_pass_text'] = array(
    '#type' => 'text_format',
    '#title' => t('Pass text'),
    '#default_value' => $pass_text['value'],
    '#format' => $pass_text['format'],
    '#description' => t("Additional text that will be displayed when the user passes the test."),
  );

  // Add the validate function the the form. This is done, because this form is
  // added to the installation procedure as well, and the validate function
  // needs to be specified in that case since the form will have a different
  // name
  $form['#validate'] = array('quiz_wizard_admin_form_validate');

  // Return the form using system settings.
  return system_settings_form($form);
}

/**
 * Validate callback for the administration form.
 */
function quiz_wizard_admin_form_validate($form, &$form_state) {
  // Validate that the pass rate is a number between 0 and 100.
  $pass_rate = $form_state['values']['quiz_pass_rate'];
  if (!is_numeric($pass_rate) || $pass_rate < 0 || $pass_rate > 100) {
    form_set_error('quiz_pass_rate', t('The pass rate must be a number between 0 and 100.'));
  }
}
