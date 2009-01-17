<?php
// $Id: tsearch.pages.inc,v 1.4 2007/12/06 09:51:01 goba Exp $

/**
 * @file
 * User page callbacks for the tsearch module.
 */

/**
 * Menu callback; presents the tsearch form and/or tsearch results.
 */
function tsearch_view($type = 'node') {
  // TSearch form submits with POST but redirects to GET. This way we can keep
  // the tsearch query URL clean as a whistle:
  // tsearch/type/keyword+keyword
  if (!isset($_POST['form_id'])) {
    if ($type == '') {
      // Note: tsearch/node can not be a default tab because it would take on the
      // path of its parent (tsearch). It would prevent remembering keywords when
      // switching tabs. This is why we drupal_goto to it from the parent instead.
      drupal_goto('tsearch/node');
    }

    // Construct the tsearch form.
    $output = drupal_get_form('tsearch_form', NULL, $keys, $type);;

    $keys = tsearch_get_keys();
    // Only perform tsearch if there is non-whitespace tsearch term:
    if (trim($keys)) {
      // Log the tsearch keys:
      watchdog('tsearch', '%keys (@type).', array('%keys' => $keys, '@type' => module_invoke($type, 'tsearch', 'name')), WATCHDOG_NOTICE, l(t('results'), 'tsearch/'. $type .'/'. $keys));

      // Collect the tsearch results:
      $results = tsearch_data($keys, $type);

      if (!empty($results)) {
        $rendered_results = theme('tsearch_results', $results, $type);
        $output .= theme('box', t('TSearch results'), $rendered_results);
      }
      else {
        $output .= theme('box', t('Your tsearch yielded no results'), tsearch_help('tsearch#noresults', drupal_help_arg()));
      }
    }

    return $output;
  }

  return drupal_get_form('tsearch_form', NULL, empty($keys) ? '' : $keys, $type);
}

/**
 * Process variables for tsearch-results.tpl.php.
 *
 * The $variables array contains the following arguments:
 * - $results
 * - $type
 *
 * @see tsearch-results.tpl.php
 */
function template_preprocess_tsearch_results(&$variables) {
  $variables['tsearch_results'] = '';
  foreach ($variables['results'] as $result) {
    $variables['tsearch_results'] .= theme('tsearch_result', $result, $variables['type']);
  }
  $variables['pager'] = theme('pager', NULL, 10, 0);
  // Provide alternate tsearch results template.
  $variables['template_files'][] = 'tsearch-results-'. $variables['type'];
}

/**
 * Process variables for tsearch-result.tpl.php.
 *
 * The $variables array contains the following arguments:
 * - $result
 * - $type
 *
 * @see tsearch-result.tpl.php
 */
function template_preprocess_tsearch_result(&$variables) {
  $result = $variables['result'];
  $variables['url'] = check_url($result['link']);
  $variables['title'] = check_plain($result['title']);

  $info = array();
  if (!empty($result['type'])) {
    $info['type'] = check_plain($result['type']);
  }
  if (!empty($result['user'])) {
    $info['user'] = $result['user'];
  }
  if (!empty($result['date'])) {
    $info['date'] = format_date($result['date'], 'small');
  }
  if (isset($result['extra']) && is_array($result['extra'])) {
    $info = array_merge($info, $result['extra']);
  }
  // Check for existence. User tsearch does not include snippets.
  $variables['snippet'] = isset($result['snippet']) ? $result['snippet'] : '';
  // Provide separated and grouped meta information..
  $variables['info_split'] = $info;
  $variables['info'] = implode(' - ', $info);
  // Provide alternate tsearch result template.
  $variables['template_files'][] = 'tsearch-result-'. $variables['type'];
}

/**
 * As the tsearch form collates keys from other modules hooked in via
 * hook_form_alter, the validation takes place in _submit.
 * tsearch_form_validate() is used solely to set the 'processed_keys' form
 * value for the basic tsearch form.
 */
function tsearch_form_validate($form, &$form_state) {
  form_set_value($form['basic']['inline']['processed_keys'], trim($form_state['values']['keys']), $form_state);
}

/**
 * Process a tsearch form submission.
 */
function tsearch_form_submit($form, &$form_state) {
  $keys = $form_state['values']['processed_keys'];
  if ($keys == '') {
    form_set_error('keys', t('Please enter some keywords.'));
    // Fall through to the drupal_goto() call.
  }

  $type = $form_state['values']['module'] ? $form_state['values']['module'] : 'node';
  $form_state['redirect'] = 'tsearch/'. $type .'/'. $keys;
  return;
}
