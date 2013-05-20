<?php
/**
 * @file
 * imagine_notifications.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function imagine_notifications_default_rules_configuration() {
  $items = array();
  $items['rules_follow_content'] = entity_import('rules_config', '{ "rules_follow_content" : {
      "LABEL" : "Follow Content",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "flag" ],
      "REQUIRES" : [ "flag", "comment" ],
      "ON" : [ "comment_insert" ],
      "IF" : [
        { "NOT flag_flagged_node" : {
            "flag" : "follow",
            "node" : [ "comment:node" ],
            "flagging_user" : [ "comment:author" ]
          }
        }
      ],
      "DO" : [
        { "flag_flagnode" : {
            "flag" : "follow",
            "node" : [ "comment:node" ],
            "flagging_user" : [ "comment:author" ],
            "permission_check" : 0
          }
        }
      ]
    }
  }');
  $items['rules_pm_followers'] = entity_import('rules_config', '{ "rules_pm_followers" : {
      "LABEL" : "PM Followers",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "flag", "follow", "private message" ],
      "REQUIRES" : [ "rules", "flag", "comment" ],
      "ON" : [ "comment_insert" ],
      "IF" : [
        { "data_is" : {
            "data" : [ "comment:node:type" ],
            "op" : "IN",
            "value" : { "value" : { "blog" : "blog", "forum" : "forum", "image" : "image", "news" : "news" } }
          }
        }
      ],
      "DO" : [
        { "flag_fetch_users_node" : {
            "USING" : { "flag" : "follow", "node" : [ "comment:node" ] },
            "PROVIDE" : { "users" : { "users" : "Users who flagged" } }
          }
        },
        { "LOOP" : {
            "USING" : { "list" : [ "users" ] },
            "ITEM" : { "user" : "Current user" },
            "DO" : [
              { "component_rules_send_follower_messages" : { "comment" : [ "comment" ], "user" : [ "user" ] } }
            ]
          }
        }
      ]
    }
  }');
  $items['rules_send_follower_messages'] = entity_import('rules_config', '{ "rules_send_follower_messages" : {
      "LABEL" : "Send Follower Messages",
      "PLUGIN" : "rule",
      "TAGS" : [ "flag", "follow", "private message" ],
      "REQUIRES" : [ "rules" ],
      "USES VARIABLES" : {
        "comment" : { "label" : "Comment", "type" : "comment" },
        "user" : { "label" : "User", "type" : "user" }
      },
      "IF" : [
        { "NOT data_is" : { "data" : [ "comment:author" ], "value" : [ "user" ] } }
      ],
      "DO" : [
        { "entity_create" : {
            "USING" : {
              "type" : "message",
              "param_type" : "activity_notification",
              "param_user" : [ "user" ]
            },
            "PROVIDE" : { "entity_created" : { "message" : "Message" } }
          }
        },
        { "data_set" : { "data" : [ "message:arguments:username" ], "value" : "[comment:name]" } },
        { "data_set" : { "data" : [ "message:arguments:url" ], "value" : "[comment:url]" } },
        { "data_set" : {
            "data" : [ "message:arguments:node" ],
            "value" : "[comment:node]: Comment [comment:cid]"
          }
        },
        { "entity_save" : { "data" : [ "message" ], "immediate" : 1 } }
      ]
    }
  }');
  return $items;
}
