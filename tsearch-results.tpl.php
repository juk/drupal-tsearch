<?php
// $Id: tsearch-results.tpl.php,v 1.1 2007/10/31 18:06:38 dries Exp $

/**
 * @file tsearch-results.tpl.php
 * Default theme implementation for displaying tsearch results.
 *
 * This template collects each invocation of theme_tsearch_result(). This and
 * the child template are dependant to one another sharing the markup for
 * definition lists.
 *
 * Note that modules may implement their own tsearch type and theme function
 * completely bypassing this template.
 *
 * Available variables:
 * - $tsearch_results: All results as it is rendered through
 *   tsearch-result.tpl.php
 * - $type: The type of tsearch, e.g., "node" or "user".
 *
 *
 * @see template_preprocess_tsearch_results()
 */
?>
<dl class="tsearch-results <?php print $type; ?>-results">
  <?php print $tsearch_results; ?>
</dl>
<?php print $pager; ?>
