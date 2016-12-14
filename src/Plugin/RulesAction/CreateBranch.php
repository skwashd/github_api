<?php

namespace Drupal\github_api\Plugin\RulesAction;

use Drupal\rules\Core\RulesActionBase;

/**
 * Provides a 'Create Branch' action.
 *
 * @RulesAction(
 *   id = "github_create_branch,
 *   label = @Translation("Create Branch"),
 *   category = @Translation("Github API"),
 *   context = {
 *     "username" = @ContextDefinition("string",
 *       label = @Translation("Username"),
 *       description = @Translation("The username of the owner of the github repsitory.")
 *     ),
 *     "repository" = @ContextDefinition("string",
 *       label = @Translation("Repository"),
 *       description = @Translation("Repository at github"),
 *     ),
 *     "source" = @ContextDefinition("string",
 *       label = @Translation("Source Branch"),
 *       description = @Translation("Source branch from the repository at github."),
 *     ),
 *     "destination" = @ContextDefinition("string",
 *       label = @Translation("Destination"),
 *       description = @Translation("This can be a branch name or a commit SHA1."),
 *     )
 *   }
 * )
 */
class CreateBranch extends RulesActionBase {

  /**
   * Create the branch.
   *
   * @param string $username
   *   Username of the owner of the github repository.
   * @param string $repository
   *   Repsository at github.
   * @param string $source
   *   Source branch from the repository at github.
   * @param string $destination
   *   This can be a branch name or a commit SHA1.
   */
  protected function doExecute($username, $repository, $source, $destination) {
    github_api_create_branch($username, $repository, $source, $destination);
  }

}
