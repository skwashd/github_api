<?php
/**
 * @file
 * Drupal Cache implementation of the Github API library cache.
 */

use Github\HttpClient\Cache\CacheInterface,
  Guzzle\Http\Message\Response;

/**
 * Drupal Cache class for Github API.
 */
class DrupalGithubApiHttpClientCacheDrupalNativeCache implements CacheInterface {

  /**
   * @var int
   * Caches data loaded during cache lookups.
   */
  static protected $lookup = array();

  /**
   * {@inheritdoc}
   */
  public function has($id) {
    $cached = $this->loadRaw($id);
    return (bool) $cached;
  }

  /**
   * {@inheritdoc}
   */
  public function getModifiedSince($id) {
    $cached = $this->loadRaw($id);
    if ($cached) {
      return $cached['modified_since'];
    }

    return NULL;
  }

  /**
   * {@inheritdoc}
   */
  public function getETag($id) {
    $cached = $this->loadRaw($id);
    if ($cached) {
      return $cached['etag'];
    }

    return NULL;
  }

  /**
   * {@inheritdoc}
   */
  public function get($id) {
    $cached = $this->loadRaw($id);
    if (!$cached) {
      throw new \InvalidArgumentException("Unable to load {$id}");
    }

    return $cached['response'];
  }

  /**
   * {@inheritdoc}
   */
  public function set($id, Response $response) {
    $key = "response_{$id}";
    $data = array(
      'response' => $response,
      'etag' => $response->getHeader('ETag'),
      'modified_since' => time(),
    );

    // cache_set can fail silently, so we have no way of knowing if this fails.
    cache_set($key, $data, 'cache_github_api');
  }

  /**
   * Retreieves raw cached objects from the backend.
   *
   * @param string $id The id of the cached resource
   *
   * @return bool|Guzzle\Http\Message\Response
   *   Returns FALSE if not found, otherwise the Guzzle response object.
   */
  protected function loadRaw($id) {
    $key = "response_{$id}";
    if (empty(self::$lookup[$key])) {
      $cached = cache_get($key, 'cache_github_api');
      self::$lookup[$id] = $cached;
    }

    if (!empty(self::$lookup[$key])) {
      return self::$lookup[$key];
    }

    return NULL;
  }
}
