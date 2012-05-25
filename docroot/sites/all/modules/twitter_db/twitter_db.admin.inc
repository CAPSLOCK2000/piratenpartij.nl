<?php

/**
 * @file
 * Contains administration related functions.
 */


/**
 * Admin settings form
 */
function twitter_db_settings() {

  $udate_table = '<h2>' . l(t('Update Twitter table'), TWITTER_DB_SETTINGS . '/update', array('query' => array('destination' => TWITTER_DB_SETTINGS))) . '</h2>';
  $udate_table .= '<div class="description">' . t('This will download the last tweets.') . '</div>';

  $form['twitter_db_update'] = array(
    '#markup' => $udate_table,
    '#weight' => -3,
  );

  $form['twitter_db_what_to_retrieve'] = array(
    '#type' => 'select',
    '#title' => t('What do you want to retrieve?'),
    '#options' => array(
      'user' => t('User timeline'),
      'hashtag' => t('Hashtag'),
    ),
    '#default_value' => variable_get('twitter_db_what_to_retrieve', 'user'),
    '#description' => t('Select what you want to retrieve.'),
    '#weight' => -2,
  );
  $form['twitter_db_retrieve_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#default_value' => variable_get('twitter_db_retrieve_name', ''),
    '#size' => 30,
    '#description' => t('Name of the user or hashtag without "@" and "#". Ex: "drupal_modules" (user) or "drupal" (hashtag).'),
    '#weight' => -1,
  );
  $form['twitter_db_update_frequency'] = array(
    '#type' => 'select',
    '#title' => t('Minimum update period'),
    '#options' => array(
      60 => t('1 min'),
      300 => t('5 min'),
      900 => t('15 min'),
      1800 => t('30 min'),
      3600 => t('1 hour'),
      10800 => t('3 hours'),
      21600 => t('6 hours'),
      43200 => t('12 hours'),
      86400 => t('1 day'),
      259200 => t('3 day'),
      604800 => t('1 week'),
      2419200 => t('4 weeks'),
    ),
    '#default_value' => variable_get('twitter_db_update_frequency', 3600),
    '#description' => t('This is the minimum time that must elapse before new tweets may be downloaded.'),
    '#weight' => 0,
  );
  
  
  $form['twitter_db_tweet_display'] = array(
    '#type' => 'fieldset',
    '#title' => t('Tweet display'),
    '#weight' => 2,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#weight' => 1,
  );
  
  $form['twitter_db_tweet_display']['twitter_db_number_of_tweets_to_display'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of tweets to display (max 10)'),
    '#default_value' => variable_get('twitter_db_number_of_tweets_to_display', 3),
    '#size' => 10,
    '#required' => TRUE,
    '#description' => t('Number of tweets to display in the Last tweets block. Set it to 0 if you want to display all tweets. Use this carefully, because your layout can be destroyed if too many tweets are displayed.'),
  );
  
  $form['twitter_db_tweet_display']['twitter_db_display_user_picture'] = array(
    '#type' => 'checkbox',
    '#title' => t("Display user picture"),
    '#description' => t('If enabled, the Twitter profile picture for the user will be displayed.'),
    '#default_value' => variable_get('twitter_db_display_user_picture', FALSE),
  );
  
  $form['twitter_db_tweet_display']['twitter_db_display_datetime'] = array(
    '#type' => 'checkbox',
    '#title' => t("Display date/time"),
    '#description' => t('If enabled, the date/time the tweet was created will be displayed.'),
    '#default_value' => variable_get('twitter_db_display_datetime', FALSE),
  );
  
  $form['twitter_db_tweet_display']['twitter_db_datetime_format'] = array(
    '#type' => 'select',
    '#title' => t('Date/time format'),
    '#options' => array(
      'relative' => t('Relative'),
      'month_day' => t('Month and day'),
      'day_month' => t('Day and month'),
    ),
    '#default_value' => variable_get('twitter_db_datetime_format', 'relative'),
    '#description' => t('Set the format for date/time. Relative means the relative time between created date and the current time. Ex: "2 days ago."'),
  );
  

  $jquery_plugin = module_exists('jquery_plugin') ? TRUE : FALSE;

  $title = $jquery_plugin ? t('jQuery Plugin') : t('jQuery Plugin is not installed - Install the jQuery Plugin module to use these settings');

  $form['twitter_db_cycle'] = array(
    '#type' => 'fieldset',
    '#title' => $title,
    '#weight' => 2,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['twitter_db_cycle']['twitter_db_cycle_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t("Enable jQuery Cycle"),
    '#description' => t('If enabled, the tweets will be display as a slideshow.'),
    '#default_value' => variable_get('twitter_db_cycle_enabled', FALSE),
    '#disabled' => !$jquery_plugin,
  );

  $form['twitter_db_cycle']['twitter_db_cycle_effect'] = array(
    '#type' => 'select',
    '#title' => t('Cycle effect'),
    '#options' => array(
      'cover' => t('Cover'),
      'fade' => t('Fade'),
      'scrollUp' => t('Scroll Up'),
      'scrollDown' => t('Scroll Down'),
      'shuffle' => t('Shuffle'),
    ),
    '#default_value' => variable_get('twitter_db_cycle_effect', 'fade'),
    '#description' => t('Set the effect to be used when showing the tweets.'),
    '#disabled' => !$jquery_plugin,
  );

  $form['twitter_db_save_note'] = array(
    '#markup' => '<p>' . t('Note that if you have changed the username/hashtag, you may need to click update on the top of this page to download the new tweets, after you have saved this configuration.') . '</p>',
    '#weight' => 20,
  );
  
  $form['#validate'][] = 'twitter_db_settings_validate';
  $form['#submit'][] = 'twitter_db_settings_submit';

  return system_settings_form($form);
}

/**
 * Admin settings form validate
 */
function twitter_db_settings_validate($form, &$form_state) {
  if ($form_state['input']['twitter_db_number_of_tweets_to_display'] > 10) {
    form_set_error('twitter_db_number_of_tweets_to_display', t('You can not display more than 10 tweets.'));
  }
}

/**
 * Admin settings form submit
 */
function twitter_db_settings_submit($form, &$form_state) {
  _twitter_db_set_job($form_state['values']['twitter_db_update_frequency']);
  drupal_set_message(t('You may need to update the Twitter DB table in case you changed the user or hashtag. <a href="@link">Click here</a> to update the table and retrieve the last tweets.', array('@link' => url('admin/config/media/twitter-db/update', array('query' => array('destination' => TWITTER_DB_SETTINGS))))), 'status');
}



