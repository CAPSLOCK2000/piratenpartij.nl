<div<?php print $attributes; ?>>
  <div<?php print $content_attributes; ?>>
	<?php 
		$breadcrumb = drupal_get_breadcrumb();
		if (!empty($breadcrumb)) {
			// Provide a navigational heading to give context for breadcrumb links to
			// screen-reader users. Make the heading invisible with .element-invisible.
			$crumbs = '<h2 class="element-invisible">' . t('You are here') . '</h2>';
			$crumbs .= '<div id="breadcrumb" >';
			$crumbs .= '<ul class="breadcrumb clearfix">';
			$array_size = count($breadcrumb);
			$i = 0;
			while ( $i < $array_size) {
				$crumbs .= '<li class="breadcrumb-' . $i;
				if ($i == 0) {
					$crumbs .= ' first';
				}
				if ($i+1 == $array_size) {
					$crumbs .= ' last';
				}
				$crumbs .=  '">' . $breadcrumb[$i] . '</li>';
				$crumbs .=  '<li class="seperator" >/</li>';
				$i++;
			}
			$crumbs .= '<li class="active">'. drupal_get_title() .'</li>';
			$crumbs .= '</ul></div>';
			echo $crumbs;
		}
	?>
  </div>
</div>