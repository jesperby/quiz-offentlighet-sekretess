<?php
/**
 * @file
 *
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function quiz_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "ds" && $api == "ds") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_ds_field_settings_info().
 */
function quiz_ds_field_settings_info() {
  $export = array();

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|quiz_round|default';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'quiz_round';
  $ds_fieldsetting->view_mode = 'default';
  $ds_fieldsetting->settings = array(
    'quiz_result' => array(
      'weight' => '0',
      'label' => 'inline',
      'format' => 'default',
    ),
  );
  $export['node|quiz_round|default'] = $ds_fieldsetting;

  return $export;
}

/**
 * Implements hook_ds_custom_fields_info().
 */
function quiz_ds_custom_fields_info() {
  $export = array();

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'quiz_result';
  $ds_field->label = 'Score';
  $ds_field->field_type = 5;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = 'quiz_round|*';
  $ds_field->properties = array(
    'code' => array(
      'value' => '[node:field_number_of_correct_answers] / [node:field_number_of_questions]',
      'format' => 'plain_text',
    ),
    'use_token' => 1,
  );
  $export['quiz_result'] = $ds_field;

  return $export;
}

/**
 * Implements hook_ds_layout_settings_info().
 */
function quiz_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|question|answer';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'question';
  $ds_layout->view_mode = 'answer';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'field_case_help_texts',
        1 => 'field_scenario',
        2 => 'field_answers',
      ),
    ),
    'fields' => array(
      'field_case_help_texts' => 'ds_content',
      'field_scenario' => 'ds_content',
      'field_answers' => 'ds_content',
    ),
    'classes' => array(),
    'wrappers' => array(),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => TRUE,
  );
  $export['node|question|answer'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|question|question';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'question';
  $ds_layout->view_mode = 'question';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'field_scenario',
      ),
    ),
    'fields' => array(
      'field_scenario' => 'ds_content',
    ),
    'classes' => array(),
    'wrappers' => array(),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => TRUE,
  );
  $export['node|question|question'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|quiz_round|default';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'quiz_round';
  $ds_layout->view_mode = 'default';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'quiz_result',
        1 => 'field_new_round_link',
        2 => 'field_correct_answers_link',
        3 => 'field_score_text',
      ),
    ),
    'fields' => array(
      'quiz_result' => 'ds_content',
      'field_new_round_link' => 'ds_content',
      'field_correct_answers_link' => 'ds_content',
      'field_score_text' => 'ds_content',
    ),
    'classes' => array(),
    'wrappers' => array(
      'ds_content' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
  );
  $export['node|quiz_round|default'] = $ds_layout;

  return $export;
}

/**
 * Implements hook_ds_view_modes_info().
 */
function quiz_ds_view_modes_info() {
  $export = array();

  $ds_view_mode = new stdClass();
  $ds_view_mode->api_version = 1;
  $ds_view_mode->view_mode = 'answer';
  $ds_view_mode->label = 'Answer';
  $ds_view_mode->entities = array(
    'node' => 'node',
  );
  $export['answer'] = $ds_view_mode;

  $ds_view_mode = new stdClass();
  $ds_view_mode->api_version = 1;
  $ds_view_mode->view_mode = 'question';
  $ds_view_mode->label = 'Question';
  $ds_view_mode->entities = array(
    'node' => 'node',
  );
  $export['question'] = $ds_view_mode;

  return $export;
}
