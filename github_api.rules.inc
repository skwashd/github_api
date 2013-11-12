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
    'parameter' => array(
      'username' => array(
        'label' => t('Username'),
        'type' => 'text',
        'description' => t('The username of the owner of the github repsitory.'),
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
      'destination' => array(
        'label' => t('Destination branch'),
        'type' => 'text',
        'description' => t('This can be a branch name or a commit SHA1.'),
        'default_value' => '',
      ),
    ),
    'group' => t('Github API'),
    'access callback' => 'user_access',
  );

  $items['github_api_create_branch'] = $defaults + array(
    'label' => t('Create branch'),
    'base' => 'github_api_create_branch',
  );

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
