<?php
/**
 * @file
 * Github API rules.
 */

/**
 * Implements hook_rules_action_info().
 */
function github_api_rules_action_info() {
  $defaults = array(
    'parameter' => github_api_rules_action_get_default_parameters(),
    'group' => t('Github API'),
    'access callback' => 'user_access',
  );

  $items['github_api_delete_branch'] = $defaults + array(
    'label' => t('Delete branch'),
    'base' => 'github_api_delete_branch',
  );

  // Adds destination branch parameter to actions below.
  $defaults['parameter']['destination'] = array(
    'label' => t('Destination branch'),
    'type' => 'text',
    'description' => t('This can be a branch name or a commit SHA1.'),
    'default_value' => '',
  );

  $items['github_api_create_branch'] = $defaults + array(
    'label' => t('Create branch'),
    'base' => 'github_api_create_branch',
  );

  // Adds message parameter to actions below.
  $defaults['parameter']['message'] = array(
    'label' => t('Message'),
    'type' => 'text',
    'description' => t('This is the commit message.'),
  );

  $items['github_api_merge'] = $defaults + array(
    'label' => t('Merge'),
    'base' => 'github_api_merge',
  );

  $items['github_api_create_or_merge_branch'] = $defaults + array(
    'label' => t('Create or merge branch'),
    'base' => 'github_api_create_or_merge_branch',
  );

  return $items;
}

/**
 * Returns the github api rules action default parameters.
 */
function github_api_rules_action_get_default_parameters() {
  return array(
    'username' => array(
      'label' => t('Username'),
      'type' => 'text',
      'description' => t('The username of the owner of the github repsitory.  If empty the default owner will be used.'),
      'optional' => TRUE,
    ),
    'repository' => array(
      'label' => t('Repository'),
      'type' => 'text',
      'description' => t('Repository at github.'),
    ),
    'source' => array(
      'label' => t('Source branch'),
      'type' => 'text',
      'description' => t('Source branch from the repository at github.'),
    ),
  );
}
