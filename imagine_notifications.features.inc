<?php
/**
 * @file
 * imagine_notifications.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function imagine_notifications_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function imagine_notifications_views_api() {
  return array("api" => "3.0");
}

/**
 * Implements hook_flag_default_flags().
 */
function imagine_notifications_flag_default_flags() {
  $flags = array();
  // Exported flag: "Follow".
  $flags['follow'] = array(
    'content_type' => 'node',
    'title' => 'Follow',
    'global' => 0,
    'types' => array(
      0 => 'blog',
      1 => 'forum',
      2 => 'image',
      3 => 'news',
    ),
    'flag_short' => 'Follow',
    'flag_long' => '',
    'flag_message' => '',
    'unflag_short' => 'Unfollow',
    'unflag_long' => '',
    'unflag_message' => '',
    'unflag_denied_text' => '',
    'link_type' => 'toggle',
    'roles' => array(
      'flag' => array(
        0 => 2,
      ),
      'unflag' => array(
        0 => 2,
      ),
    ),
    'weight' => 0,
    'show_on_form' => 0,
    'access_author' => '',
    'show_on_page' => 1,
    'show_on_teaser' => 0,
    'show_contextual_link' => 0,
    'i18n' => 0,
    'api_version' => 2,
    'module' => 'imagine_notifications',
    'locked' => array(
      0 => 'name',
    ),
  );
  return $flags;

}

/**
 * Implements hook_default_message_type().
 */
function imagine_notifications_default_message_type() {
  $items = array();
  $items['activity_notification'] = entity_import('message_type', '{
    "name" : "activity_notification",
    "description" : "Activity Notification",
    "argument_keys" : [ "@username", "!url", "@node" ],
    "argument" : [],
    "category" : "message_type",
    "data" : {
      "token options" : { "clear" : 0 },
      "purge" : { "override" : 0, "enabled" : 0, "quota" : "", "days" : "" }
    },
    "language" : "",
    "arguments" : null,
    "message_text" : { "und" : [
        {
          "value" : "\\u003Cp\\u003E@username commented on \\u003Ca href=\\u0022!url\\u0022\\u003E@node.\\u003C\\/p\\u003E\\r\\n",
          "format" : "filtered_html",
          "safe_value" : "\\u003Cp\\u003E@username commented on \\u003Ca href=\\u0022!url\\u0022\\u003E@node.\\u003C\\/a\\u003E\\u003C\\/p\\u003E\\n"
        }
      ]
    },
    "rdf_mapping" : []
  }');
  return $items;
}
