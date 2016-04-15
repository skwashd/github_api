<?php

/**
 * @file
 * Contains Drupal\github_api\Form\SettingsForm
 */

namespace Drupal\github_api\Form;

use Drupal\Core\Config\ConfigFormBase;
use Drupal\Core\Form\FormStateInterface;

/**
 * Class SettingsForm
 * @package Drupal\github_api\Form
 */
class SettingsForm extends ConfigFormBase {

  /**
   * {@inheritdoc}
   */
  public function getEditableConfigNames() {
    return [
      'github_api.settings'
    ];
  }

  /**
   * {@inheritdoc}
   */
  public function getFormId() {
    return 'github_api_settings';
  }

  /**
   * {@inheritdoc}
   */
  public function build(array $form, FormStateInterface $form_state) {
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
      '#required' => TRUE,
      '#description' => t('This password is not stored it only used for generating the authentication token.'),
    );

    $form['actions'] = array();
    $form['actions']['submit'] = array(
     '#type' => 'submit',
     '#value' => t('Generate and store token'),
    );

    return $form;
  }

  /**
   * {@inheritdoc}
   */
  public function submit(array $form, FormStateInterface $form_state) {
    parent::submitForm($form, $form_state);

    $username = $form_state->getValue['github_api_username'];
    $password = $form_state->getValue['github_api_password'];
    try {
      $config = $this->config('github_api.settings');
      $token = github_api_get_token($username, $password);
      $config->set('github_api_token', $token);
      $config->set('github_api_username', $username);
      $config->set('github_api_password', $password);
      drupal_set_message(t('Generated and stored github authentication token'));
    }
    catch (Exception $e) {
      drupal_set_message(t('Unable to generate token. Error: @error', array('@error' => $e->getMessage())), 'error');
    }
  }
}