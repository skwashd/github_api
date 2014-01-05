<?php
/**
 * @file
 * Github API module administration functions.
 */

/**
 * Github API admin settings form.
 */
function github_api_settings() {
  $form = array();

  $form['github_api_username'] = array(
    '#type' => 'textfield',
    '#title' => t('GitHub username'),
    '#required' => TRUE,
    '#default_value' => variable_get('github_api_username'),
  );

  $password = variable_get('github_api_password');
  $form['github_api_password'] = array(
    '#type' => 'password',
    '#title' => t('Password'),
    '#required' => empty($password),
  );

  $form['github_api_current_password'] = array(
    '#type' => 'value',
    '#value' => $password,
  );

  $form['github_api_use_cache'] = array(
    '#type' => 'select',
    '#title' => t('Use caching'),
    '#options' => array(
      0 => t('No'),
      1 => t('Yes'),
    ),
    '#default_value' => variable_get('github_api_use_cache', TRUE),
    '#description' => t('Cache responses from the github API to reduce number of calls made.'),
  );

  return system_settings_form($form);
}

/**
 * Validates submission of the GitHub API settings form.
 */
function github_api_settings_validate($form, &$form_state) {
  $password = $form_state['values']['github_api_password'];
  if (!$password) {
    $form_state['values']['github_api_password'] = $form_state['values']['github_api_current_password'];
  }

  unset($form_state['values']['github_api_current_password']);
}
