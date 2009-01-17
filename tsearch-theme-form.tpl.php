<?php
// $Id: tsearch-theme-form.tpl.php,v 1.1 2007/10/31 18:06:38 dries Exp $

/**
 * @file tsearch-theme-form.tpl.php
 * Default theme implementation for displaying a tsearch form directly into the
 * theme layout. Not to be confused with the tsearch block or the tsearch page.
 *
 * Available variables:
 * - $tsearch_form: The complete tsearch form ready for print.
 * - $tsearch: Array of keyed tsearch elements. Can be used to print each form
 *   element separately.
 *
 * Default keys within $tsearch:
 * - $tsearch['tsearch_theme_form']: Text input area wrapped in a div.
 * - $tsearch['submit']: Form submit button.
 * - $tsearch['hidden']: Hidden form elements. Used to validate forms when submitted.
 *
 * Since $tsearch is keyed, a direct print of the form element is possible.
 * Modules can add to the tsearch form so it is recommended to check for their
 * existance before printing. The default keys will always exist.
 *
 *   <?php if (isset($tsearch['extra_field'])): ?>
 *     <div class="extra-field">
 *       <?php print $tsearch['extra_field']; ?>
 *     </div>
 *   <?php endif; ?>
 *
 * To check for all available data within $tsearch, use the code below.
 *
 *   <?php print '<pre>'. check_plain(print_r($tsearch, 1)) .'</pre>'; ?>
 *
 * @see template_preprocess_tsearch_theme_form()
 */
?>
<div id="tsearch" class="container-inline">
  <?php print $tsearch_form; ?>
</div>
