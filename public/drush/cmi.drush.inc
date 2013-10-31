<?php

/**
 * @file
 * CMI related drush commands.
 */

/**
 * Implementation of hook_drush_command().
 */
function cmi_drush_command() {
  $items = array();

  $items['config-export'] = array(
    'description' => 'Dump active configuration to the export directory.',
    'options' => array(),
    'examples' => array(),
    'aliases' => array('ce'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_CONFIGURATION,
  );

  $items['config-export-git'] = array(
    'description' => 'Dump active configuration to the export directory and run git -p',
    'aliases' => array('ceg'),
  );

  $items['config-copy'] = array(
    'description' => 'Copy configuration from one folder to another.',
    'arguments' => array(
      'src' => 'E.g. export',
      'dest' => 'E.g. staging',
    ),
  );

  return $items;
}

/**
 * Drush config export.
 */
function drush_cmi_config_export() {
  drush_cmi_config_copy('active', 'export');

  // Fix permissions.
  foreach (drush_scan_directory(config_get_config_directory('export'), '/\.(htaccess|yml)$/') as $file) {
    chmod($file->filename, 0664);
  }
}

/**
 * Drush config export + git prompt.
 */
function drush_cmi_config_export_git() {
  drush_cmi_config_export();
  drush_shell_exec_interactive('git add -p ' . config_get_config_directory('export'));
}

/**
 * Validate callback for config-copy.
 */
function drush_cmi_config_copy_validate($src, $dest) {
  if ($dest == CONFIG_ACTIVE_DIRECTORY) {
    drush_set_error('Do not hack active config.');
  }
}

/**
 * Copy config from one directory to another.
 *
 * @param $src
 *   The source directory.
 *
 * @param $dest
 *   The destination directory.
 */
function drush_cmi_config_copy($src, $dest) {
  drush_delete_dir(config_get_config_directory($dest));
  drush_copy_dir(config_get_config_directory($src), config_get_config_directory($dest));
}
