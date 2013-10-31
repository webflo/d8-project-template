# Template for Drupal 8 Projects

This is a template for Drupal 8 projects which integrates CMI in the DEV and CI
workflow.

- Each developer has its own working copy and database.
- Developers dump their active configuration to config/export
- Developers import the configuration from config/staging

Only config/export is kept in version control.

## Commands to export configuration

```
// Dump active configuration to export. ('ce' is a alias for 'config-export')
drush ce

// Commit the config files that are in export
git add ../config/export

// Or do it all in one step (export + git add -p)
drush ceg
```

## Commands to import configuration

```
// Copy the configuration from export to staging
drush config-copy export staging

// Import configuration from staging
drush config-import
```
