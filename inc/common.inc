<?php
function _couperChaine($chaine, $nbc = 100) {
	$tl = strlen($chaine);
        if ($tl < $nbc) {return $chaine;}
	
	$coupe = substr($chaine,0,$nbc);
	$sortir = (substr($coupe,($nbc-1),1) == ' ');
	while (!$sortir) {
		$nbc = $nbc - 1;
		$coupe = substr($chaine,0,$nbc);
		$sortir = (substr($coupe,($nbc-1),1) == ' ');
	}
	return $coupe . '...';
}
/**
 * Transformer une date au format jj/mm/aaaa en sa valeur en microtemps pour la retourner
 * @param string $date : la date au format string
 */
function _getTime($date) {
    $df = 0;
    if ($date){
        $fin = explode("-",$date);
        $df = mktime(0,0,0,$fin[1],$fin[2],$fin[0]);
    }
    return $df;
}

function _formaterNombre($nbr){
	$tl = strlen($nbr);
	$rs = $tl % 3;
	$j = 0;
	$nbFinal = '';
	for ($ii = $rs; $ii < $tl; $ii++) {
		$nbFinal.= substr($nbr,$ii,1);
		$j++;
		if ($j == 3) {
			$j = 0;
			if ($ii < ($tl - 1)) $nbFinal.= '.';
		}
	}
        if ($rs) {$nbFinal = substr($nbr,0,$rs) . (($nbFinal) ? '.' . $nbFinal : '');}
	return $nbFinal;
}
function _supprDernier($chaine) {return substr($chaine,0,(strlen($chaine)-1));}

/**
 * Ajout de message pour le dialogue avec l'utilisateur.
 * @param String $txt : il s'agit du texte de l'erreur
 * @param int $type : type de l'erreur. 1 pour un message de succès après une opération et 0 pour un échec
 */
function _ajoutMessage($txt, $type = 0) {
        if (isset($_SESSION['var_message'])) {$message = $_SESSION['var_message'];} else {$message = '';}
	$class = 'danger';
	$i = '<i class="fa fa-remove"></i> ';
	if ($type == 1) {$class = 'success';$i = '<i class="fa fa-check-square"></i> ';}
	elseif ($type == 2) {$class = 'info';$i = '<i class="fa fa-info-circle"></i> ';}
	elseif ($type == 3) {$class = 'warning';$i = '<i class="fa fa-warning"></i> ';}
	
	$message.= '<div class="alert alert-' . $class . '">' . $i . $txt . '</div>';
	$_SESSION['var_message'] = $message;
}

function _ajoutMessages($arr, $type = 0) {foreach ($arr as $msg) {_ajoutMessage($msg,$type);}}

function _recupMessage() {
        if (!isset($_SESSION['var_message'])) {return '';}
	return '<div class="messages m-0"><br /><ul class="pl-0">' . _recupSession('var_message','',1) . '</ul></div>';
}

function _recupSession($var, $def = '', $eff = 0) {
	$ret = (isset($_SESSION[$var])) ? $_SESSION[$var] : $def;
        if ($eff) {$_SESSION[$var] = '';}
	return $ret;
}

function _i($nm, $cl = '', $tx = '', $fa = 'fa') {
    return '<i class="' . $fa . ' fa-' . $nm . ' '. $cl . '"> ' . $tx . '</i>';
}