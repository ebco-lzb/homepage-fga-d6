<?php

function user_activemenu($settings) {
  $items = array();
  
  if (! empty($settings['user']['enable'])) {
    $items[$settings['user']['type']]['#block-user-1'] = 'activemenu/menu';
  }
  
  return $items;
}

/**
 * Implementation of hook_activemenu_settings().
 */
function user_activemenu_settings($settings) {
  $form = array(
    '#type' => 'fieldset',
    '#title' => t('Navigation'),
  );
  
  $form['enable'] = array(
    '#type' => 'checkbox',
    '#title' => t('Activate AJAX menu for navigation menu'),
    '#default_value' => isset($settings['enable']) ? $settings['enable'] : 0,
  );
  
  $form['type'] = array(
    '#type' => 'select',
    '#title' => t('Menu type'),
    '#options' => activemenu_get_menu_types(),
    '#default_value' => isset($settings['type']) ? $settings['type'] : 'tree',
  );
  
  return $form;
}
