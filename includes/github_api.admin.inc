<?php
/**
 * @file
 * Github API module administration functions.
 */

/**
 * Admin settings form.
 */
function github_api_settings() {
  $form = array();

  $form['github_api_username'] = array(
    '#type' => 'textfield',
    '#title' => t('GitHub username'),
    '#required' => TRUE,
    '#default_value' => variable_get('github_api_username'),
  );

  $form['github_api_password'] = array(
    '#type' => 'password',
    '#title' => t('Password'),
    '#description' => t('This password is not stored it only used for generating the authentication token.'),
  );

  $form['github_api_default_owner'] = array(
    '#type' => 'textfield',
    '#title' => t('Default owner'),
    '#required' => TRUE,
    '#description' => t('Default repository owner (user or organization).'),
    '#default_value' => variable_get('github_api_default_owner'),
  );

  $form['actions'] = array();
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Generate and store token'),
  );

  return $form;
}

/**
 * Handles submission of the GitHub settings form.
 */
function github_api_settings_submit($form, &$form_state) {
  if (!empty($form_state['values']['github_api_password'])) {
    $username = $form_state['values']['github_api_username'];
    $password = $form_state['values']['github_api_password'];
    try {
      $token = github_api_get_token($username, $password);
      variable_set('github_api_token', $token);
      variable_set('github_api_username', $username);
      drupal_set_message(t('Generated and stored github authentication token'));
    }
    catch (Exception $e) {
      drupal_set_message(t('Unable to generate token. Error: @error', array('@error' => $e->getMessage())), 'error');
    }
  }
  variable_set('github_api_default_owner', $form_state['values']['github_api_default_owner']);
}
